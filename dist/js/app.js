window.onload = function() {

  /**
   * Configure page settings
   */
  document.execCommand('defaultParagraphSeparator', false, 'p');

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Init application controller
   */
  var app_controller = new ApplicationController(template_store);
  app_controller.init();
};

var ApiController = function() {

  /**
   * Private state
   */
  // Apis
  var getStartupDataApiController = null;

  // Event listeners
  var lostConnectionListeners = [];
  var badRequestListeners = [];

  /**
   * Private functions
   */
  // Bind generic event listeners
  var initApiController = function(api) {};

  var configureGetStartupDataApi = function() {
    // Initialize api controller and bind generic handler logic
    getStartupDataApiController = new GetStartupDataApiController();
    initApiController(getStartupDataApiController);
  };

  var configureApis = function() {
    configureGetStartupDataApi(); 
  };

  /**
   * Public functions
   */
  // Lazy loader api controllers
  this.getGetStartupDataApiController = function() {
    return getStartupDataApiController;
  };

  // Register event listeners
  this.bindLostConnection = function(callback) {
    lostConnectionListeners.push(callback);
    return this;
  };

  this.bindBadRequest = function(callback) {
    badRequestListeners.push(callback);
    return this;
  };

  this.init = function() {
    configureApis();
  };
};

var ApplicationController = function(template_store) {

  /**
   * Private state
   */
  var templateStore = template_store;

  var _this = this;

  // Controllers
  var centerPageController = null;
  var sidePanelController = null;
  var apiController = null;

  // Models
  var applicationModel = null;

  /**
   * Private functions
   */
  var initCenterPageController = function() {
    // Init center page view
    var center_page_node = document.getElementById('center-panel');

    var center_page_view = new CenterPageView(
      templateStore,
      center_page_node
    );
    center_page_view.init();

    // Init center page controller
    centerPageController = new CenterPageController();
    centerPageController.init(
      center_page_view,
      applicationModel.getCenterPageModel(),
      apiController
    );
  };

  var initSidePanelController = function() {
    // Init side panel view
    var side_panel_parent_root = document.getElementById('side-panel');

    var side_panel_view = new SidePanelView(
      templateStore,
      side_panel_parent_root
    );
    side_panel_view.init();

    // Init side panel controller
    sidePanelController = new SidePanelController();
    sidePanelController.init(
      side_panel_view,
      applicationModel.getUserModel(),
      apiController
    );
  };

  var initApiController = function() {
    apiController = new ApiController();
    apiController.init();
  };

  var configureControllers = function() {
    // Navigate to proper page when side panel tab is clicked
    sidePanelController.bindNewExperimentTabSelection(_this.showNewExperimentPage);
    sidePanelController.bindMyExperimentsTabSelection(_this.showMyExperimentsPage);
    sidePanelController.bindTechnicianTabSelection(_this.showTechnicianPage);
    sidePanelController.bindFeedbackTabSelection(_this.showFeedbackPage);
    
    // Navigate to 'MyExperiments' page on new experiment
    centerPageController.bindNewExperiment(_this.showMyExperimentsPage);
  };

  var initControllers = function() {
    // Init individual controllers
    initApiController();
    initCenterPageController();
    initSidePanelController();

    // Configure controllers with mutual responsibilities
    configureControllers(); 
  };

  var initUi = function() {
    sidePanelController.selectNewExperimentTab();
  };

  var initModels = function() {
    applicationModel = new ApplicationModel();
    applicationModel.init();
  };

  /**
   * Public functions
   */
  this.init = function(template_store) {
    initModels();
    initControllers();     
    initUi();

    // Fetch startup data
    apiController.getGetStartupDataApiController().fetch();

    // Configure initial ui
    _this.showNewExperimentPage();
  };

  this.showNewExperimentPage = function() {
    sidePanelController.selectNewExperimentTab();
    centerPageController.showNewExperimentPage();
  };

  this.showMyExperimentsPage = function() {
    sidePanelController.selectMyExperimentsTab();
    centerPageController.showMyExperimentsPage();
  };

  this.showTechnicianPage = function() {
    sidePanelController.selectTechnicianTab();
    centerPageController.showTechnicianPage();
  };

  this.showFeedbackPage = function() {
    sidePanelController.selectFeedbackTab();
    centerPageController.showFeedbackPage();
  };
};

var CenterPageController = function() {

  /**
   * Private state
   */
  var _this = this;

  // Child controllers
  var newExperimentPageController = null;
  var myExperimentsPageController = null;
  var technicianPageController = null;
  var apiController = null;

  // Models
  var centerPageModel = null;

  // Views
  var centerPageView = null;

  // Event listeners
  var newExperimentListeners = [];

  /**
   * Private functions
   */
  var initNewExperimentPageController = function() {
    newExperimentPageController = new NewExperimentPageController();
    newExperimentPageController.init(
      centerPageView.getNewExperimentPageView(),
      centerPageModel.getNewExperimentPageModel(),
      apiController
    );

    newExperimentPageController.bindConfirmOrder(handleConfirmOrder);
  };

  var initTechnicianPageController = function() {
    technicianPageController = new TechnicianPageController();
    technicianPageController.init(
      centerPageView.getTechnicianPageView(),
      centerPageView.getFeedbackPageView()
    );
  };

  var createNewExperimentModel = function(
    scopes_count,
    experiment_duration,
    start_time,
    short_code
  ) {
    // Make deep copy of the complex parameters!
    var start_time_copy = new Date(start_time.getTime());
    var short_code_copy = short_code.deepCopy();

    // Create new my experiment shadow
    return new NewMyExperimentModelBuilder()
      .setScopesCount(scopes_count)
      .setExperimentDuration(experiment_duration)
      .setStartTime(start_time_copy)
      .setShortCode(short_code_copy)
      .build();
  };

  var persistNewExperiment = function(
    scopes_count,
    experiment_duration,
    start_time,
    short_code,
    new_my_experiment_shadow_model,
    successful_callback
  ) {
    // Assemble api request
    var start_time_api_obj = new TimestampApiObjectBuilder()
      .setTimestampWithDate(start_time)
      .build();

    var confirm_order_api = new ConfirmOrderApi(ScopesNetwork);
    confirm_order_api
      .setScopesCount(scopes_count)
      .setExperimentDuration(experiment_duration)
      .setStartTimestamp(start_time_api_obj)
      .setShortCodeId(short_code.getId())
      .setSuccessfulApiCallback(function(json_response) {
        successful_callback(
          new_my_experiment_shadow_model,
          json_response
        );
      })
      .send();
  };

  var handleConfirmOrder = function() {
    var new_experiment_model = newExperimentPageController.getModel();  

    // Extract data from new-experiment model
    // Scopes count data
    var scopes_count = new_experiment_model.getScopesCountModel().getCurrentValue();

    // Experiment duration data
    var experiment_duration = new_experiment_model.getExperimentDurationModel().getCurrentValue();

    // Time data
    var start_date_model = new_experiment_model.getExperimentDatePickerModel();
    var start_time_model = new_experiment_model.getExperimentTimePickerModel();
    var selected_time_model = start_time_model.getSelectedItem();
    
    var start_time = new Date(
      start_date_model.getSelectedYear(),
      start_date_model.getSelectedMonth(),
      start_date_model.getSelectedDate(),
      selected_time_model.getData().getHours(),
      selected_time_model.getData().getMinutes()
    );

    // Short code data
    var short_code_picker_model = new_experiment_model.getShortCodePickerModel(); 
    var short_code_model = short_code_picker_model.getSelectedItem();
    var short_code = short_code_model.getData();

    var new_experiment_model = createNewExperimentModel(
      scopes_count,
      experiment_duration,
      start_time,
      short_code
    );

    // Send new experiment request to server and navigate to MyExperiment page
    persistNewExperiment(
      scopes_count,
      experiment_duration,
      start_time,
      short_code,
      new_experiment_model,
      handleSuccessfulNewExperimentPersist
    );
  };

  var handleSuccessfulNewExperimentPersist = function(
    new_experiment_model,
    json_response,
    api_keys
  ) {
    // Update model with new id
    new_experiment_model.setId(json_response.id);   

    // Add to my-experiment page model 
    var my_experiments_page_model = centerPageModel.getMyExperimentsPageModel();
    my_experiments_page_model.addExperiment(new_experiment_model);

    // Navigate to my-experiments page
    newExperimentListeners.forEach(function(callback) {
      callback();
    });
  };

  var initMyExperimentsPageController = function() {
    myExperimentsPageController = new MyExperimentsPageController();
    myExperimentsPageController.init(
      centerPageView.getMyExperimentsPageView(),
      centerPageModel.getMyExperimentsPageModel()
    );
  };

  /**
   * Privileged functions
   */
  this.init = function(
      center_page_view,
      center_page_model,
      api_controller
    ) {
    centerPageView = center_page_view;
    centerPageModel = center_page_model;
    apiController = api_controller;

    // Initialize child controllers
    initNewExperimentPageController();
    initMyExperimentsPageController();
    initTechnicianPageController();
  };

  /**
   * Functions for showing main pages
   */
  this.showNewExperimentPage = function() {
    centerPageView.showNewExperimentPage();
  };

  this.showMyExperimentsPage = function() {
    centerPageView.showMyExperimentsPage();
  };

  this.showFeedbackPage = function() {
    centerPageView.showFeedbackPage();
  };

  this.showTechnicianPage = function() {
    centerPageView.showTechnicianPage();
  };

  this.bindNewExperiment = function(callback) {
    newExperimentListeners.push(callback); 
    return this;
  };
};

var ConfirmOrderController = function() {

  /**
   * Private state
   */
  // Model
  var confirmOrderView = null;
  var experimentDurationModel = null;
  var pricingModel = null;

  // Event listeners
  var cancelOrderCallbacks = [];
  var confirmOrderCallbacks = [];

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathway
    experimentDurationModel.bindCurrentValue(refreshPriceDisplay);
    pricingModel.bindPricePerHour(refreshPriceDisplay);

    // Register button click callbacks
    confirmOrderView.bindCancelOrder(handleCancelOrderClick);
    confirmOrderView.bindConfirmOrder(handleConfirmOrderClick);
  };

  var refreshPriceDisplay = function() {
    var hours = experimentDurationModel.getCurrentValue();
    var hourly_price = pricingModel.getPricePerHour();
    var total_cost = hours * hourly_price

    confirmOrderView.setPricingInformation(
      hours,
      hourly_price,
      total_cost
    );
  };

  var handleConfirmOrderClick = function() {
    for (var i = 0; i < confirmOrderCallbacks.length; ++i) {
      confirmOrderCallbacks[i]();
    }
  };

  var handleCancelOrderClick = function() {
    for (var i = 0; i < cancelOrderCallbacks.length; ++i) {
      cancelOrderCallbacks[i]();
    }
  };

  /**
   * Privileged functions
   */
  this.init = function(
    confirm_order_view,
    experiment_duration_model,
    pricing_model
  ) {
    confirmOrderView = confirm_order_view;
    experimentDurationModel = experiment_duration_model;
    pricingModel = pricing_model;

    // Attach models to views
    configureCallbacks(); 

    return this;
  };

  this.bindConfirmOrder = function(callback) {
    confirmOrderCallbacks.push(callback);
    return this;
  };

  this.bindCancelOrder = function(callback) {
    cancelOrderCallbacks.push(callback);
    return this;
  };

  this.getPricingModel = function() {
    return pricingModel;
  };
};

var DatePickerController = function() {

  /**
   * Private state
   */
  var currentDate = new Date();
  var datePickerView = null;
  var datePickerModel = null;

  /**
   * Private functions
   */
  var handleDateSelection = function(view, date) {
    // Exit early if we're no longer using this view
    if (view != datePickerView) {
      return;
    }

    // Handle date selection
    datePickerModel
      .setSelectedDate(date)
      .setSelectedMonth(datePickerModel.getViewedMonth())
      .setSelectedYear(datePickerModel.getViewedYear());
  };

  var handleMonthNavigation = function(view, is_decrement) {
    if (view != datePickerView) {
      return; 
    }

    var month_displacement = is_decrement
      ? -1
      : 1;

    // Check current date, fix date if necessary
    var current_date = new Date();
    if (current_date.getUTCFullYear() != currentDate.getUTCFullYear() ||
        current_date.getMonth() != currentDate.getMonth() ||
        current_date.getDate() != currentDate.getDate()) {
      currentDate = current_date;    
    }

    // Adjust year and reset month if we extend beyond calendar bounds
    var current_month = datePickerModel.getViewedMonth();
    var current_year = datePickerModel.getViewedYear();

    var next_month = current_month + month_displacement;
    var next_year = current_year;

    switch (next_month) {
      case -1:
        next_month = 11;
        --next_year;
        break;
      case 12:
        next_month = 0;
        ++next_year;
        break;
    }

    // Exit early if invalid month displacement
    if (!isValidMonth(next_month, next_year)) {
      return;
    }

    // Update viewed month/date in model
    datePickerModel.setViewedMonthAndYear(next_month, next_year);
    
    // Check if previous month is illegal. If so, disable decrement month
    // navigation arrow
    var previous_month = new Date(next_year, next_month - 1);
    datePickerView.toggleMonthDecrementNavButtonActiveState(
      isValidMonth(previous_month.getMonth(), previous_month.getFullYear())    
    );

    // Check if next month is illegal. If so, disable increment month
    // navigation arrow
    var next_month = new Date(next_year, next_month + 1);
    datePickerView.toggleMonthIncrementNavButtonActiveState(
      isValidMonth(next_month.getMonth(), next_month.getFullYear())   
    );

    return this;
  };

  var isValidMonth = function(month, year) {
    var start_date = new Date(); 
    start_date.setDate(
      start_date.getDate() + datePickerModel.getMinAdvanceDayCount()
    );

    // Calculate month-displacement between new-date and start-date
    var month_displacement = 12 * (year - start_date.getFullYear()) + month - start_date.getMonth();

    return month_displacement >= 0 &&
      month_displacement <= datePickerModel.getMaxAdvanceMonthCount();
  };

  var handleCalendarRefresh = function() {
    datePickerView.refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear(),
      datePickerModel.getMinAdvanceDayCount(),
      datePickerModel.getInvalidDaysOfTheWeek(),
      datePickerModel.getInvalidDates()
    ); 
  };


  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    datePickerView = view;
    datePickerModel = model;

    // Configure view --> model data pathway
    datePickerView
      .bindDateSelection(handleDateSelection)
      .bindMonthNavigation(handleMonthNavigation);

    // Configure model --> view data pathway
    datePickerModel
      .bindSelectedDate(datePickerView.setSelectedDate)
      .bindSelectedMonth(datePickerView.setSelectedMonth)
      .bindSelectedYear(datePickerView.setSelectedYear)
      .bindViewedMonth(handleCalendarRefresh)
      .bindMinAdvanceDayCount(handleCalendarRefresh)
      .bindMaxAdvanceMonthCount(handleCalendarRefresh)
      .bindInvalidDaysOfTheWeek(handleCalendarRefresh)
      .bindInvalidDates(handleCalendarRefresh);
    
    // Initialize model/ui
    this.renderDefaultUi();

  };

  this.renderDefaultUi = function() {
    this.selectFirstAvailableDate();  
  };

  this.selectFirstAvailableDate = function() {
    // Identify first available date
    var starting_date = new Date();
    starting_date.setDate(
      starting_date.getDate() + datePickerModel.getMinAdvanceDayCount()    
    );

    var max_month = starting_date.getMonth() + datePickerModel.getMaxAdvanceMonthCount();

    while (
      (
        Utils.contains(starting_date.getDay(), datePickerModel.getInvalidDaysOfTheWeek())
        ||
        Utils.contains(starting_date, datePickerModel.getInvalidDates())
      )
      && starting_date.getMonth() < max_month
    ) {
      starting_date.setDate(starting_date.getDate() + 1);
    }

    if (starting_date.getMonth() == max_month) {
      // TODO handle case in which NO legal starting dates exist!
      console.assert(false, 'Unhandled case!');
    }

    // Set date on DatePickerModel
    datePickerModel
      .setSelectedDate(starting_date.getDate())
      .setSelectedMonth(starting_date.getMonth())
      .setSelectedYear(starting_date.getFullYear())
      .setViewedMonthAndYear(
        starting_date.getMonth(),
        starting_date.getFullYear()
      );
  };

  this.getModel = function() {
    return datePickerModel;
  };
};

var DropDownController = function() {

  /**
   * Private state
   */
  var dropDownView = null;
  var dropDownModel = null;

  /**
   * Private functions
   */
  var handleClick = function(view, idx) {
    // Exit early if we're no longer monitoring this view
    if (view != dropDownView) {
      return;
    }

    // Handle click
    dropDownModel.setSelectedItemIdx(idx);
  }

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    dropDownView = view;
    dropDownModel = model;

    // Configure model --> view data pathway
    dropDownModel
      .bindSelectedItem(dropDownView.setSelectedItem)
      .bindDropDownItemModels(dropDownView.setDropDownItemModels);

    // Configure view --> model data pathway
    dropDownView.bindClick(handleClick);
  };

  this.renderDefaultUi = function() {
    dropDownModel.setSelectedItemIdx(0); 
  };

  this.setView = function(view) {
    dropDownView = view;

    // Bind event listeners
    dropDownView.bindClick(handleClick); 
    return this;
  };

  this.setModel = function(model) {
    dropDownModel = model;
    return this;
  };

  this.getView = function() {
    return dropDownView;
  };

  this.getModel = function() {
    return dropDownModel;
  };
};

var MyExperimentController = function() {

  /**
   * Private state
   */
  var myExperimentView = null;
  var myExperimentModel = null; 

  // Page controllers
  var frontPageController = null;

  /**
   * Protected functions
   */
  var handleModelTitleChange = function(title) {
    if (title == null) {
      myExperimentView.setTitlePlaceholder(); 
    } else {
      myExperimentView.setTitle(title);
    }
  };

  var handleViewTitleChange = function(new_title) {
    if (new_title == null || Utils.isWhiteSpace(new_title)) {
      // User removed title. Now, delete title in model and 
      // update ui with default title
      myExperimentModel.setTitle(null);
    } else {
      // Update model
      myExperimentModel.setTitle(new_title.trim());
    }
  };

  var handleExperimentStatusForVideo = function(experiment_status) {
    if (experiment_status == 'Complete') {
      myExperimentView.showVideo();
    }
  };

  var configureCallbacks = function() {
    /**
     * Model --> view data pathways
     */
    myExperimentModel
      .bindTitle(handleModelTitleChange)
      .bindExperimentStatus(handleExperimentStatusForVideo);

    /**
     * View --> model data pathways
     */
    // Attach title change listeners
    myExperimentView.bindTitle(handleViewTitleChange);

    // Attach page nav event listeners
    myExperimentView.bindFrontPageNav(function() {
      myExperimentView.showFrontPage();
    });

    myExperimentView.bindDescriptionNav(function() {
      myExperimentView.showDescriptionPage();
    });

    myExperimentView.bindMonitorNav(function() {
      myExperimentView.showMonitorPage();
    });

    myExperimentView.bindRecordingNav(function() {
      myExperimentView.showRecordingPage();
    });
  };

  var initPageControllers = function() {
    frontPageController = new MyExperimentFrontPageController();
    frontPageController.init(
      myExperimentView.getFrontPageView(),
      myExperimentModel
    );
  };

  /**
   * Privileged functions
   */
  this.init = function(
    view,
    model
  ) {
    myExperimentView = view;
    myExperimentModel = model;

    // Initialize controllers for pages, e.g. front, description
    initPageControllers();

    // Set up data pathways
    configureCallbacks();
  };
};

var MyExperimentFrontPageController = function() {

  /**
   * Private state
   */
  var frontPageView = null;
  var myExperimentModel = null;

  /**
   * Private functions
   */
  var handleStartTimeChange = function(start_time) {
    frontPageView.setStartTime(start_time) 
  };

  var configureCallbacks = function() {
    // Model --> view data pathway
    myExperimentModel
      .bindScopesCount(frontPageView.setScopesCount)
      .bindExperimentDuration(frontPageView.setExperimentDuration)
      .bindStartTime(handleStartTimeChange)
      .bindShortCode(frontPageView.setShortCode)
      .bindExperimentStatus(frontPageView.setExperimentStatus)
      .bindPaymentStatus(frontPageView.setPaymentStatus);
  };

  /**
   * Privileged functions
   */
  this.init = function(
    front_page_view,
    my_experiment_model
  ) {
    frontPageView = front_page_view;
    myExperimentModel = my_experiment_model;

    configureCallbacks();
  };
};

var MyExperimentsPageController = function() {

  /**
   * Private state
   */
  var myExperimentsControllers = new Map(); // Map<int id, Obj MyExperimentController>
  var getConfirmedOrdersApiWrapper = null;

  var myExperimentsPageView = null;
  var myExperimentsPageModel = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathway
    myExperimentsPageModel.bindAddExperiment(handleNewExperiment);     
    myExperimentsPageModel.bindRemoveExperiment(handleRemoveExperiment);
    myExperimentsPageModel.bindSetExperiments(handleSetExperiments);
  };

  var handleNewExperiment = function(experiment_model) {
    // Create new-experiment ui element and bind to controller
    var experiment_view = myExperimentsPageView.spawnNewExperiment();
    var experiment_controller = new MyExperimentController();
    experiment_controller.init(
      experiment_view,
      experiment_model
    );

    // Cache controller
    myExperimentsControllers.set(
      experiment_model.getId(),
      experiment_controller  
    );
  };

  // TODO
  var handleRemoveExperiment = function(experiment_model) {};
 

  var handleSetExperiments = function(experiments) {
    // Delete all previous experiments in ui
    myExperimentsPageView.removeExperiments(); 

    // Render new experiments
    experiments.forEach(handleNewExperiment);
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    myExperimentsPageView = view; 
    myExperimentsPageModel = model; 

    configureCallbacks();
  };
};

var NewExperimentPageController = function() {
  
  /**
   * Private state
   */
  var _this = this;
  
  // Child controllers
  var scopesCountController = null;
  var experimentDurationController = null;
  var experimentTimePickerController = null;
  var experimentDatePickerController = null;
  var shortCodePickerController = null;
  var confirmOrderController = null;
  var apiController = null;

  // Models
  var newExperimentPageModel = null;

  // Views
  var newExperimentPageView = null;

  // Callbacks
  var confirmOrderCallbacks = [];

  /**
   * Privileged functions
   */
  var initScopesCountController = function() {
    var scopes_count_view = newExperimentPageView.getScopesCountFormView(); 
    var scopes_count_model = newExperimentPageModel.getScopesCountModel();

    scopesCountController = new SliderController();
    scopesCountController.init(
      scopes_count_view,
      scopes_count_model
    );
  };

  var initExperimentDurationController = function() {
    var experiment_duration_view = newExperimentPageView.getExperimentDurationFormView();
    var experiment_duration_model = newExperimentPageModel.getExperimentDurationModel();

    experimentDurationController = new SliderController();
    experimentDurationController.init(
      experiment_duration_view,
      experiment_duration_model
    );
  };

  var initExperimentTimePickerController = function() {
    var experiment_time_form_view = newExperimentPageView.getExperimentTimeFormView();
    var experiment_time_picker_model = newExperimentPageModel.getExperimentTimePickerModel();

    experimentTimePickerController = new DropDownController();
    experimentTimePickerController.init(
      experiment_time_form_view.getTimePickerView(),
      experiment_time_picker_model
    );
  };

  var initExperimentDatePickerController = function() {
    var experiment_time_form_view = newExperimentPageView.getExperimentTimeFormView();
    var experiment_date_picker_model = newExperimentPageModel.getExperimentDatePickerModel();

    experimentDatePickerController = new DatePickerController();
    experimentDatePickerController.init(
      experiment_time_form_view.getDatePickerView(),
      experiment_date_picker_model
    );
  };

  var initShortCodePickerController = function() {
    var short_code_form_view = newExperimentPageView.getShortCodeFormView();
    var short_code_picker_model = newExperimentPageModel.getShortCodePickerModel();

    shortCodePickerController = new DropDownController();
    shortCodePickerController.init(
      short_code_form_view.getDropDownView(),
      short_code_picker_model
    );
  };

  var initConfirmOrderController = function() {
    confirmOrderController = new ConfirmOrderController();

    confirmOrderController
      .bindConfirmOrder(handleConfirmOrder)
      .bindCancelOrder(handleCancelOrder)
      .init(
        newExperimentPageView.getConfirmExperimentFormView(),
        newExperimentPageModel.getExperimentDurationModel(),
        newExperimentPageModel.getPricingModel() 
      );
  };

  var handleConfirmOrder = function() {
    confirmOrderCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleCancelOrder = function() {
    scopesCountController.renderDefaultUi();
    experimentDurationController.renderDefaultUi();
    experimentTimePickerController.renderDefaultUi();
    shortCodePickerController.renderDefaultUi();
    experimentDatePickerController.renderDefaultUi();
  };

  var routeMaxScopesApiField = function(max_scopes) {
    var scopes_count_model = scopesCountController.getModel();
    scopes_count_model.setMaxValue(max_scopes);
  };

  var routeMaxExperimentDurationApiField = function(max_hours) {
    var experiment_duration_model = experimentDurationController.getModel();
    experiment_duration_model.setMaxValue(max_hours);
  };

  var routeShortCodeApiField = function(short_codes, api_keys) {
    var short_codes_model = shortCodePickerController.getModel();

    var drop_down_item_models = [];

    for (var i = 0; i < short_codes.length; ++i) {
      var json_short_code = short_codes[i];
      var short_code = new ShortCode(
        json_short_code[api_keys.id],
        json_short_code[api_keys.code],
        json_short_code[api_keys.alias]
      );

      var drop_down_item_model = new DropDownItemModel(
        short_code.getAlias(),
        short_code.getCode(),
        short_code
      );

      drop_down_item_models.push(drop_down_item_model);
    }

    short_codes_model.setDropDownItems(drop_down_item_models);
  };

  var routeExperimentStartingTimesApiField = function(
    json_start_time,
    json_end_time,
    start_time_interval,
    time_keys
  ) {
    var experiment_time_picker_model = experimentTimePickerController.getModel(); 

    // Deserialize time objects
    var start_time = new Time(
      json_start_time[time_keys.hours],
      json_start_time[time_keys.minutes],
      json_start_time[time_keys.seconds]
    );
    var end_time = new Time(
      json_end_time[time_keys.hours],
      json_end_time[time_keys.minutes],
      json_end_time[time_keys.seconds]
    );

    // Generate list of valid time intervals
    var current_date_time = start_time.toDate();
    var stopping_date_time = end_time.toDate();

    var drop_down_items = [];

    while (current_date_time.getTime() <= stopping_date_time.getTime()) {
      // Create new time model and add it to drop-down list model
      var time_data = new Time(
        current_date_time.getHours(),
        current_date_time.getMinutes(),
        current_date_time.getSeconds()
      );

      var time_string = Utils.toHoursAndMinutesString(current_date_time);

      drop_down_items.push(new DropDownItemModel(
        time_string,
        time_string,
        time_data
      ));

      // Advance by perscribed time interval (minutes)
      current_date_time.setMinutes(
        current_date_time.getMinutes() + start_time_interval
      );
    }

    experiment_time_picker_model.setDropDownItems(drop_down_items);

  };

  var routeCalendarApiFields = function(
    min_days_in_advance,
    max_months_in_advance
  ) {
    var calendar_model = experimentDatePickerController.getModel();
    calendar_model.setMinAdvanceDayCount(min_days_in_advance);
    calendar_model.setMaxAdvanceMonthCount(max_months_in_advance);
  };

  var routePricingInfoApiFields = function(price_per_hour) {
    var pricing_model = confirmOrderController.getPricingModel();
    pricing_model.setPricePerHour(price_per_hour);
  };

  var configureStartupDataApi = function() {
    var startup_data_api = apiController.getGetStartupDataApiController();

    startup_data_api.bindSuccess(function(json_response, api_keys) {
      // Configure max scopes
      routeMaxScopesApiField(json_response[api_keys.max_scopes]);

      // Configure max experiment duration
      routeMaxExperimentDurationApiField(json_response[api_keys.max_hours]);

      // Configure short codes
      routeShortCodeApiField(
        json_response[api_keys.short_codes],
        api_keys.short_code_fields
      );
      
      // Configure starting/ending time and time interval
      routeExperimentStartingTimesApiField(
        json_response[api_keys.start_time],
        json_response[api_keys.end_time],
        json_response[api_keys.start_time_interval],
        api_keys.time
      );
      
      // Configure calendar 
      routeCalendarApiFields(
        json_response[api_keys.min_days_in_advance],
        json_response[api_keys.max_months_in_advance]
      ); 

      // Configure pricing
      routePricingInfoApiFields(json_response[api_keys.hourly_price]);
    });
  };

  var configureApiCalls = function() {
    configureStartupDataApi(); 
  };

  /**
   * Private functions
   */
  this.init = function(
      new_experiment_view,
      new_experiment_model,
      api_controller
    ) {
    // TODO, handle case where init is called twice (model and view already bound)
    newExperimentPageView = new_experiment_view;
    newExperimentPageModel = new_experiment_model;
    apiController = api_controller;

    // Initialize child controllers
    initScopesCountController();
    initExperimentDurationController();
    initExperimentTimePickerController();
    initExperimentDatePickerController();
    initShortCodePickerController();
    initConfirmOrderController();

    // Attach controllers to api calls
    configureApiCalls();
  };

  this.getScopesCountController = function() {
    return scopesCountController;
  };

  this.getExperimentDurationController = function() {
    return experimentDurationController;
  };

  this.getExperimentTimePickerController = function() {
    return experimentTimePickerController;
  };

  this.getExperimentDatePickerController = function() {
    return experimentDatePickerController;
  };

  this.getShortCodePickerController = function() {
    return shortCodePickerController;
  };

  this.getConfirmOrderController = function() {
    return confirmOrderController;
  };

  this.getModel = function() {
    return newExperimentPageModel;
  };

  this.bindConfirmOrder = function(callback) {
    confirmOrderCallbacks.push(callback);
    return this;
  };
};

var PageController = function(
  side_panel_view,
  new_experiment_view
) {

  /**
   * Ui Views
   */
  var sidePanelView = side_panel_view;
  var newExperimentView = new_experiment_view;

  var currentPageView = null;

  /**
   * Private functions
   */
  var hideCurrentPage = function() {
    console.assert(currentPageView != null);
    currentPageView.hide();
    currentPageView = null;
  };

  var changePage = function(next_page_view) {
    hideCurrentPage();
    showPage(next_page_view);
  };

  var showPage = function(next_page_view) {
    console.assert(currentPageView == null);
    next_page_view.show();
    currentPageView = next_page_view;
  };

  var bindSidePanelButtons = function() {
    sidePanelView.bindNewExperimentTabClick(function() {
      changePage(newExperimentView); 
    });
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Select initial page
    sidePanelView.selectNewExperimentTab();
    showPage(newExperimentView);

    // Bind event listeners to side-panel button clicks
    bindSidePanelButtons();
  };
};

var SidePanelController = function() {

  /**
   * Private state
   */
  var _this = this;

  // Views
  var sidePanelView = null;

  // Controllers
  var apiController = null;

  // Models
  var userModel = null;

  // Tab selection callbacks
  var selectNewExperimentTabCallbacks = [];
  var selectMyExperimentsTabCallbacks = [];
  var selectTechnicianTabCallbacks = [];
  var selectFeedbackTabCallbacks = [];

  /**
   * Private functions
   */
  var configureGetStartupDataApi = function() {
    // Bind custom handler logic
    var get_startup_data_api_controller = apiController.getGetStartupDataApiController();

    // Update user model startup data response
    get_startup_data_api_controller.bindSuccess(function(json_response, api_keys) {
      // Update first and last name
      userModel.setName(
        json_response[api_keys.first_name],
        json_response[api_keys.last_name]
      );

      // Update email
      userModel.setEmail(json_response[api_keys.email]);
    });
  };

  var configureCallbacks = function() {
    // Register model callbacks
    userModel.bindSetName(sidePanelView.setUserName);

    // Register network callbacks
    configureGetStartupDataApi();

    // Register tab-selection callbacks
    sidePanelView.bindNewExperimentTabClick(handleNewExperimentTabClick);
    sidePanelView.bindMyExperimentsTabClick(handleMyExperimentsTabClick);
    sidePanelView.bindFeedbackTabClick(handleTechnicianTabClick);
    sidePanelView.bindTechnicianTabClick(handleFeedbackTabClick);
  };

  var handleNewExperimentTabClick = function() {
    selectNewExperimentTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleMyExperimentsTabClick = function() {
    selectMyExperimentsTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleTechnicianTabClick = function() {
    selectTechnicianTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleFeedbackTabClick = function() {
    selectFeedbackTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  /**
   * Privileged functions
   */
  this.init = function(
    side_panel_view,
    user_model,
    api_controller
  ) {
    sidePanelView = side_panel_view;
    userModel = user_model;
    apiController = api_controller;

    // Bind event listeners
    configureCallbacks();
  };


  this.selectNewExperimentTab = function() {
    sidePanelView.selectNewExperimentTab();
  };
  
  this.selectMyExperimentsTab = function() {
    sidePanelView.selectMyExperimentsTab();
  };

  this.selectFeedbackTab = function() {
    sidePanelView.selectFeedbackTab();
  };

  this.selectTechnicianTab = function() {
    sidePanelView.selectTechnicianTab();
  };

  /**
   * Register tab selection callbacks
   */
  this.bindNewExperimentTabSelection = function(callback) {
    selectNewExperimentTabCallbacks.push(callback);
    return this;
  };
  
  this.bindMyExperimentsTabSelection = function(callback) {
    selectMyExperimentsTabCallbacks.push(callback);
    return this;
  };

  this.bindTechnicianTabSelection = function(callback) {
    selectTechnicianTabCallbacks.push(callback);
    return this;
  };

  this.bindFeedbackTabSelection = function(callback) {
    selectFeedbackTabCallbacks.push(callback);
    return this;
  };
};

var SliderController = function() {

  /**
   * Private state
   */
  var sliderView = null;
  var sliderModel = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Configure model --> view data pathway
    sliderModel
      .bindMinValue(sliderView.setMinValue)
      .bindMaxValue(sliderView.setMaxValue)
      .bindStep(sliderView.setStep)
      .bindCurrentValue(sliderView.setValue);

    // Configure view --> model data pathway
    sliderView.bindValueChange(updateValue);
  };

  var updateValue = function(value) {
    sliderModel.setCurrentValue(value);
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    sliderView = view;
    sliderModel = model;

    // Attach view to model
    configureCallbacks();
  };

  this.renderDefaultUi = function() {
    updateValue(sliderModel.getMinValue()); 
  };

  this.getModel = function() {
    return sliderModel;
  };

  this.getView = function() {
    return sliderView;
  };
};

var TechnicianPageController = function() {

  /**
   * Private vars
   */
  var technicianPageView = null;
  var feedbackPageView = null;
  var questionIndex = 0;

  /**
   * Private functions
   */
  var handleNewQuestion = function() {
    var question = technicianPageView.getNewQuestionText();
    addNewQuestion(question);
  };

  var handleCancel = function(question_view) {
    var index = question_view.getIndex();
    question_view.remove();
    feedbackPageView.removeQuestion(index);
  };

  var addNewQuestion = function(question_text) {
    // Update technician ui
    var new_question = technicianPageView.spawnNewQuestion();
    new_question.setText(question_text);
    new_question.setIndex(questionIndex++);
    new_question.bindCancel(handleCancel);

    technicianPageView.clearNewQuestionText();
    
    // Update feedback page ui
    feedbackPageView.addQuestion(question_text);
  };

  var configureCallbacks = function() {
    technicianPageView.bindNewQuestion(handleNewQuestion);
  };

  var initUi = function() {
    addNewQuestion("What was one thing MVS did especially well? Why?");  
    addNewQuestion("What is one thing that you would like MVS to change going forward? Why?");  
    addNewQuestion("Any other comments/suggestions?");  
  };

  /**
   * Privileged functions
   */
  this.init = function(
    technician_page_view,
    feedback_page_view     
  ) {
    technicianPageView = technician_page_view;
    feedbackPageView = feedback_page_view;

    configureCallbacks();
    
    initUi();
  };
};

function ConfirmedOrder(
  id,
  num_scopes,
  start_timestamp,
  end_timestamp,
  title,
  description,
  time_ordered,
  price,
  short_code
) {
  this.id = id;
  this.scopesCount = num_scopes;
  this.startTimestamp = start_timestamp;
  this.endTimestamp = end_timestamp;
  this.title = title;
  this.description = description;
  this.timeOrdered = time_ordered;
  this.price = price;
  this.shortCode = short_code;
};

ConfirmedOrder.prototype.getId = function() {
  return this.id;
};

ConfirmedOrder.prototype.getScopesCount = function() {
  return this.scopesCount;
};

ConfirmedOrder.prototype.getStartTimestamp = function() {
  return this.startTimestamp;
};

ConfirmedOrder.prototype.getEndTimestamp = function() {
  return this.endTimestamp;
};

ConfirmedOrder.prototype.getTitle = function() {
  return this.title;
};

ConfirmedOrder.prototype.getDescription = function() {
  return this.description;
};

ConfirmedOrder.prototype.getTimeOrdered = function() {
  return this.timeOrdered;
};

ConfirmedOrder.prototype.getPrice = function() {
  return this.price;
};

ConfirmedOrder.prototype.getShortCode = function() {
  return this.shortCode;
};

var DateApiObjectBuilder = function() {

  /**
   * Api object field keys
   */
  var YEAR_KEY = 'year';
  var MONTH_KEY = 'month';
  var DAY_KEY = 'day';

  /**
   * Private vars
   */
  var date = null;

  /**
   * Privileged functions
   */
  this.build = function() {
    console.assert(date != null);

    var date_obj = {};
    date_obj[YEAR_KEY] = date.getYear();
    date_obj[MONTH_KEY] = date.getMonth();
    date_obj[DAY_KEY] = date.getDay();

    return date_obj;
  };

  /**
   * setDateObject()
   * @param DateObject _date 
   */
  this.setDateObject = function(_date) {
    date = _date; 
    return this;
  };

  /**
   * setDate()
   * @param Date _date 
   */
  this.setDate = function(_date) {
    date = new DateObject(
      _date.getFullYear(),
      _date.getMonth() + 1, // Date.month is 0 indexed
      _date.getDate()
    );
    return this;
  };
};

var DateObject = function(
  _year,
  _month,
  _day
) {
  
  /**
   * Private vars
   */
  var year = _year;
  var month = _month;
  var day = _day;

  // Validate input
  console.assert(month > 0 && month <= 12);
  console.assert(day > 0 && day <= 31);

  /**
   * Privileged functions
   */
  this.getYear = function() {
    return year;
  };

  this.getMonth = function() {
    return month;
  };

  this.getDay = function() {
    return day;
  };
};

DateObject.prototype.fromDate = function(date) {
  return new DateObject(
    date.getFullYear(),
    date.getMonth() + 1,
    date.getDate()
  );
};

var DateOperator = (function() {

  // Date constants
  var HOURS_IN_MICROSECONDS = 3.6e6;

  /**
   * Privileged methods
   */

  this.getDifferenceInHours = function(
    date_a,
    date_b
  ) {
    return Math.abs(date_a - date_b) / HOURS_IN_MICROSECONDS; 
  };

  return {
    getDifferenceInHours: getDifferenceInHours
  };

})();

var ExperimentStatus = {
  PENDING : 0,
  APPROVED : 1,
  COMPLETED : 2
};

var OrderStatus = function(_value = this.PENDING) {

  // Order statuses
  this.PENDING = 1;
  this.APPROVED = 2;
  this.COMPLETED = 3;

  // Private state 
  var value = _value;

  this.isPending = function() {
    return value == this.PENDING;
  };

  this.isApproved = function() {
    return value == this.APPROVED;
  };

  this.isCompleted = function() {
    return value == this.COMPLETED;
  };

  this.getValue = function() {
    return value; 
  };

  this.compare = function(order_status) {
    return value == order_status.getValue();
  };
};

var PaymentStatus = function(_value = this.PENDING) {

  // Payment statuses
  this.PENDING = 1;
  this.APPROVED = 2;
  this.COMPLETED = 3;

  // Private state 
  var value = _value;

  this.isPending = function() {
    return value == this.PENDING;
  };

  this.isApproved = function() {
    return value == this.APPROVED;
  };

  this.isCompleted = function() {
    return value == this.COMPLETED;
  };

  this.getValue = function() {
    return value; 
  };

  this.compare = function(payment_status) {
    return value == payment_status.getValue();
  };
};

function SerializeableDate(
  year,
  month,
  date
) {

  // Ui constants
  this.DATE_DELIMITER = ',';

  this.SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  /**
   * getShortMonthName()
   * @param uint month: 0 < month < 11
   */
  this.getShortMonthName = function(month) {
    return this.SHORT_MONTH_NAMES[month];
  };

  // Private state
  this.year = year;

  console.assert(month >= 0 && month < 12);
  this.month = month;

  console.assert(date >= 0 && date < 31);
  this.date = date;
};

SerializeableDate.prototype.serialize = function() {
  return this.getShortMonthName(this.month) + ' ' + this.date
    + this.DATE_DELIMITER + ' ' + this.year;
};

function SerializeableTime(
  hours,    // military time
  minutes,
  seconds
) {

  this.TIME_DELIMITER = ':';
  this.AM_TOKEN = 'am';
  this.PM_TOKEN = 'pm';

  this.convertHourToNonMilitaryTime = function(military_hours) {
    return (military_hours > 12)
      ? military_hours - 12
      : military_hours;
  };

  this.getMeridianToken = function(military_hours) {
    return (military_hours >= 12 && military_hours !== 24)
      ? this.PM_TOKEN
      : this.AM_TOKEN;
  };

  this.hours = hours;
  this.minutes = minutes;
  this.seconds = seconds;
};

SerializeableTime.prototype.serialize = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.seconds, 2) + " " + meridian_token;
};

SerializeableTime.prototype.serializeWithoutSeconds = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) +
    " " + meridian_token;
};

function ShortCode(
  id,
  code,
  alias
) {
  this.id = id;
  this.code = code;
  this.alias = alias;
};

ShortCode.prototype.getId = function() {
  return this.id;
};

ShortCode.prototype.getCode = function() {
  return this.code;
};

ShortCode.prototype.getAlias = function() {
  return this.alias;
};

ShortCode.prototype.deepCopy = function() {
  return new ShortCode(
    this.id,
    this.code,
    this.alias
  );
};

var Time = function(
  _hours,
  _minutes,
  _seconds
) {
 
  /**
   * Private vars
   */
  var hours = (_hours == null) ? 0 : _hours;
  var minutes = (_minutes == null) ? 0 : _minutes;
  var seconds = (_seconds == null) ? 0 : _seconds;

  // Validate input
  console.assert(hours >= 0 && hours < 24);
  console.assert(minutes >= 0 && minutes < 60);
  console.assert(seconds >= 0 && seconds < 60);

  /**
   * Public functions
   */
  this.getHours = function() {
    return hours;
  };

  this.getMinutes = function() {
    return minutes;
  };

  this.getSeconds = function() {
    return seconds;
  };

  this.toDate = function() {
    var current_time = new Date(0, 0, 0);
    current_time.setHours(hours);
    current_time.setMinutes(minutes);
    current_time.setSeconds(seconds);
    return current_time;
  };
};

Time.prototype.fromDate = function(date) {
  return new Time(
    date.getHours(),
    date.getMinutes(),
    date.getSeconds()
  );
};

var TimeApiObjectBuilder = function() {

  /**
   * Api object field keys
   */
  var HOUR_KEY = 'hours';
  var MINUTE_KEY = 'minutes';
  var SECOND_KEY = 'seconds';

  /**
   * Initial values
   */
  var INITIAL_HOUR = 0;
  var INITIAL_MINUTE = 0;
  var INITIAL_SECOND = 0;

  /**
   * Private vars
   */
  var time = new Time(
    this.INITIAL_HOUR,
    this.INITIAL_MINUTE,
    this.INITIAL_SECOND
  );

  /**
   * Privileged functions
   */
  this.build = function() {
    var time_obj = {};
    time_obj[HOUR_KEY] = time.getHours();
    time_obj[MINUTE_KEY] = time.getMinutes();
    time_obj[SECOND_KEY] = time.getSeconds();

    return time_obj;
  };

  this.setTime = function(_time) {
    time = _time;
    return this;
  };

  /**
   * setTimeWithDate()
   * @param Date date
   */
  this.setTimeWithDate = function(date) {
    time = new Time(
      date.getHours(),
      date.getMinutes(),
      date.getSeconds()
    );
    return this;
  };
};

var Timestamp = function(
  _date,
  _time
) {

  /**
   * Private state
   */
  var date = _date;
  var time = _time;

  /**
   * Privileged functions
   */
  this.getDate = function() {
    return date;
  };

  this.getTime = function() {
    return time;
  };
};

/**
 * fromDate()
 * @param Date date
 */
Timestamp.prototype.fromDate = function(date) {
  return new Timestamp(
    DateObject.fromDate(date),
    Time.fromDate(date)
  );
};

var TimestampApiObjectBuilder = function() {

  /**
   * Api keys
   */
  var DATE_KEY = 'date';
  var TIME_KEY = 'time';

  /**
   * Private state
   */
  var dateBuilder = new DateApiObjectBuilder();
  var timeBuilder = new TimeApiObjectBuilder();

  /**
   * Privileged functions
   */
  this.setTimestamp = function(timestamp) {
    dateBuilder.setDateObject(timestamp.getDate());
    timeBuilder.setTime(timestamp.getTime());
    return this;
  };

  this.setTimestampWithDate = function(date) {
    dateBuilder.setDate(date);
    timeBuilder.setTimeWithDate(date);
    return this;
  };

  this.build = function() {
    var timestamp_obj = {};
    timestamp_obj[DATE_KEY] = dateBuilder.build();
    timestamp_obj[TIME_KEY] = timeBuilder.build();

    return timestamp_obj;
  };
};

var UpdateConfirmedOrderRequestBuilder = function() {

  this.orderId = null;
  this.title = null;
  this.removeTitle = false;
  this.description = null;
  this.removeDescription = false;
};

UpdateConfirmedOrderRequestBuilder.prototype.setId = function(id) {
  this.orderId = id;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.setTitle = function(title) {
  this.title = title;
  this.removeTitle = false;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.removeTitle = function() {
  this.title = null;
  this.removeTitle = true;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.setDescription = function(description) {
  this.description = description;
  this.removeDescription = false;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.removeDescription = function() {
  this.description = null;
  this.removeDescription = true;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.build = function() {
  // Check: id must be set!
  console.assert(this.orderId != null);

  // Check: at least one other field must be set 
  console.assert(
      this.title != null ||
      this.isTitleRemoved != null ||
      this.description != null ||
      this.isDescriptionRemoved != null
  );

  return new UpdateConfirmedOrderRequest(
    this.orderId,
    this.title,
    this.isTitleRemoved,
    this.description,
    this.isDescriptionRemoved
  );
};

var ApplicationModel = function() {
  
  /**
   * Private state
   */
  var userModel = null;
  var centerPageModel = null;

  /**
   * Private functions
   */
  var initUserModel = function() {
    userModel = new UserModel(); 
  };

  var initCenterPageModel = function() {
    centerPageModel = new CenterPageModel();
    centerPageModel.init();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    initUserModel();
    initCenterPageModel();
  };

  // Getters
  this.getUserModel = function() {
    return userModel;
  };

  this.getCenterPageModel = function() {
    return centerPageModel;
  };
};

var CenterPageModel = function() {

  /**
   * Private state
   */
  var newExperimentPageModel = null;
  var myExperimentsPageModel = null;

  /**
   * Private functions
   */
  var initNewExperimentPageModel = function() {
    newExperimentPageModel = new NewExperimentPageModel();
    newExperimentPageModel.init();
  };

  var initMyExperimentsPageModel = function() {
    myExperimentsPageModel = new MyExperimentsPageModel();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    initNewExperimentPageModel();
    initMyExperimentsPageModel();
  };

  // Getters
  this.getNewExperimentPageModel = function() {
    return newExperimentPageModel;
  };

  this.getMyExperimentsPageModel = function() {
    return myExperimentsPageModel;
  };
};

var ConfirmedOrderModel = function() {

  // Order state
  this.id = null;
  this.title = null;
  this.description = null;
  this.price = null;
  this.scopesCount = null;
  this.experimentDuration = null;
  this.startTime = null;
  this.startDate = null;
  this.paymentStatus = null;
  this.shortCode = null;

  // State change event listeners
  this.titleChangeListeners = [];
  this.descriptionChangeListeners = [];
  this.priceChangeListeners = [];
  this.scopesCountChangeListeners = [];
  this.experimentDurationChangeListeners = [];
  this.startTimeChangeListeners = [];
  this.startDateChangeListeners = [];
  this.shortCodeChangeListeners = [];
};

/**
 * ConfirmedOrder state getters
 */
ConfirmedOrderModel.prototype.getId = function() {
  return this.id;
};

ConfirmedOrderModel.prototype.getTitle = function() {
  return this.title;
};

ConfirmedOrderModel.prototype.getDescription = function() {
  return this.description;
};

/**
 * Setters w/callbacks
 */
ConfirmedOrderModel.prototype.setId = function(id) {
  this.id = id;
  return this;
}

ConfirmedOrderModel.prototype.setTitle = function(title) {
  this.title = title;

  for (var i = 0; i < this.titleChangeListeners.length; ++i) {
    this.titleChangeListeners[i](title);
  }

  return this;
};

ConfirmedOrderModel.prototype.setDescription = function(description) {
  this.description = description;

  for (var i = 0; i < this.descriptionChangeListeners.length; ++i) {
    this.descriptionChangeListeners[i](description);
  }

  return this;
};

ConfirmedOrderModel.prototype.setPrice = function(price) {
  this.price = price;

  for (var i = 0; i < this.priceChangeListeners.length; ++i) {
    this.priceChangeListeners[i](price);
  }

  return this;
};

ConfirmedOrderModel.prototype.setScopesCount = function(scopesCount) {
  this.scopesCount = scopesCount;

  for (var i = 0; i < this.scopesCountChangeListeners.length; ++i) {
    this.scopesCountChangeListeners[i](scopesCount);
  }

  return this;
};

ConfirmedOrderModel.prototype.setExperimentDuration = function(experimentDuration) {
  this.experimentDuration = experimentDuration;

  for (var i = 0; i < this.experimentDurationChangeListeners.length; ++i) {
    this.experimentDurationChangeListeners[i](experimentDuration);
  }

  return this;
};

ConfirmedOrderModel.prototype.setStartTime = function(startTime) {
  this.startTime = startTime;

  for (var i = 0; i < this.startTimeChangeListeners.length; ++i) {
    this.startTimeChangeListeners[i](startTime);
  }

  return this;
};

ConfirmedOrderModel.prototype.setStartDate = function(startDate) {
  this.startDate = startDate;

  for (var i = 0; i < this.startDateChangeListeners.length; ++i) {
    this.startDateChangeListeners[i](startDate);
  }

  return this;
};

ConfirmedOrderModel.prototype.setShortCode = function(shortCode) {
  this.shortCode = shortCode;

  for (var i = 0; i < this.shortCodeChangeListeners.length; ++i) {
    this.shortCodeChangeListeners[i](shortCode);
  }

  return this;
};

/**
 * Register state change listeners
 */
ConfirmedOrderModel.prototype.bindTitle = function(callback) {
  callback(this.title);
  this.titleChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindDescription = function(callback) {
  callback(this.description);
  this.descriptionChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindPrice = function(callback) {
  callback(this.price);
  this.priceChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindScopesCount = function(callback) {
  callback(this.scopesCount);
  this.scopesCountChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindExperimentDuration = function(callback) {
  callback(this.experimentDuration);
  this.experimentDurationChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindStartTime = function(callback) {
  callback(this.startTime);
  this.startTimeChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindStartDate = function(callback) {
  callback(this.startDate);
  this.startDateChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindShortCode = function(callback) {
  callback(this.shortCode);
  this.shortCodeChangeListeners.push(callback);
  return this;
};

var DatePickerModel = function() {

  // Private state
  this.selectedDate = null;
  this.selectedMonth = null;
  this.selectedYear = null;
  this.viewedMonth = null;
  this.viewedYear = null;

  this.minAdvanceDayCount = null;
  this.maxAdvanceMonthCount = null;
  this.invalidDaysOfTheWeek = [];
  this.invalidDates = [];

  // Callbacks
  this.selectedDateCallbacks = []; 
  this.selectedMonthCallbacks = []; 
  this.selectedYearCallbacks = []; 
  this.viewedMonthCallbacks = []; 

  this.minAdvanceDayCountCallbacks = [];
  this.maxAdvanceMonthCountCallbacks = [];
  this.invalidDaysOfTheWeekCallbacks = [];
  this.invalidDatesCallbacks = [];
};

// Setters
DatePickerModel.prototype.setSelectedDate = function(selected_date) {
  this.selectedDate = selected_date;
  this.selectedDateCallbacks.forEach(function(callback) {
    callback(this.selectedDate);
  }, this);
  return this;
};

DatePickerModel.prototype.setSelectedMonth = function(selected_month) {
  this.selectedMonth = selected_month;
  this.selectedMonthCallbacks.forEach(function(callback) {
    callback(this.selectedMonth);
  }, this);
  return this;
};

DatePickerModel.prototype.setSelectedYear = function(selected_year) {
  this.selectedYear = selected_year;
  this.selectedYearCallbacks.forEach(function(callback) {
    callback(this.selectedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedMonthAndYear = function(viewed_month, viewed_year) {
  this.viewedMonth = viewed_month;
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedMonth = function(viewed_month) {
  this.viewedMonth = viewed_month;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedYear = function(viewed_year) {
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setMinAdvanceDayCount = function(count) {
  this.minAdvanceDayCount = count;
  this.minAdvanceDayCountCallbacks.forEach(function(callback) {
    callback(this.minAdvanceDayCount);
  }, this);
  return this;
};

DatePickerModel.prototype.setMaxAdvanceMonthCount = function(count) {
  this.maxAdvanceMonthCount = count;
  this.maxAdvanceMonthCountCallbacks.forEach(function(callback) {
    callback(this.maxAdvanceMonthCount);
  }, this);
  return this;
};

DatePickerModel.prototype.setInvalidDaysOfTheWeek = function(invalid_days) {
  this.invalidDaysOfTheWeek = invalid_days;
  this.invalidDaysOfTheWeekCallbacks.forEach(function(callback) {
    callback(this.invalidDaysOfTheWeek);
  }, this);
  return this;
};

DatePickerModel.prototype.setInvalidDates = function(invalid_dates) {
  this.invalidDates = invalid_dates;
  this.invalidDatesCallbacks.forEach(function(callback) {
    callback(this.invalidDates);
  }, this);
  return this;
};

// Callback listeners
DatePickerModel.prototype.bindSelectedDate = function(callback) {
  this.selectedDateCallbacks.push(callback);
  callback(this.selectedDate);
  return this;
};

DatePickerModel.prototype.bindSelectedMonth = function(callback) {
  this.selectedMonthCallbacks.push(callback);
  callback(this.selectedMonth);
  return this;
};

DatePickerModel.prototype.bindSelectedYear = function(callback) {
  this.selectedYearCallbacks.push(callback);
  callback(this.selectedYear);
  return this;
};

DatePickerModel.prototype.bindViewedMonth = function(callback) {
  this.viewedMonthCallbacks.push(callback);
  callback(this.viewedMonth, this.viewedYear);
  return this;
};

DatePickerModel.prototype.bindMinAdvanceDayCount = function(callback) {
  this.minAdvanceDayCountCallbacks.push(callback);
  callback(this.minAdvanceDayCount);
  return this;
};

DatePickerModel.prototype.bindMaxAdvanceMonthCount = function(callback) {
  this.maxAdvanceMonthCountCallbacks.push(callback);
  callback(this.maxAdvanceMonthCount);
  return this;
};

DatePickerModel.prototype.bindInvalidDaysOfTheWeek = function(callback) {
  this.invalidDaysOfTheWeekCallbacks.push(callback);
  callback(this.invalidDaysOfTheWeek);
  return this;
};

DatePickerModel.prototype.bindInvalidDates = function(callback) {
  this.invalidDatesCallbacks.push(callback);
  callback(this.invalidDates);
  return this;
};

// Getters
DatePickerModel.prototype.getSelectedDate = function() {
  return this.selectedDate;
};

DatePickerModel.prototype.getSelectedMonth = function() {
  return this.selectedMonth;
};

DatePickerModel.prototype.getSelectedYear = function() {
  return this.selectedYear;
};

DatePickerModel.prototype.getViewedMonth = function() {
  return this.viewedMonth;
};

DatePickerModel.prototype.getViewedYear = function() {
  return this.viewedYear;
};

DatePickerModel.prototype.getMinAdvanceDayCount = function() {
  return this.minAdvanceDayCount;
};

DatePickerModel.prototype.getMaxAdvanceMonthCount = function() {
  return this.maxAdvanceMonthCount;
};

DatePickerModel.prototype.getInvalidDaysOfTheWeek = function() {
  return this.invalidDaysOfTheWeek;
};

DatePickerModel.prototype.getInvalidDates = function() {
  return this.invalidDates;
};

var DropDownItemModel = function(
  label,
  tooltip,
  data
) {
  // Private state
  this.label = label
  this.tooltip = tooltip;
  this.data = data;

  // Event listeners
  this.labelChangeCallbacks = [];
  this.tooltipChangeCallbacks = [];
};

// Setters
DropDownItemModel.prototype.setLabel = function(label) {
  this.label = label;
  this.labelChangeCallbacks.forEach(function(callback) {
    callback(label);
  });
  return this;
};

DropDownItemModel.prototype.setTooltip = function(tooltip) {
  this.tooltip = tooltip;
  this.tooltipChangeCallbacks.forEach(function(callback) {
    callback(tooltip);
  });
  return this;
};

// Bind event listeners
DropDownItemModel.prototype.bindLabel = function(callback) {
  this.labelChangeCallbacks.push(callback);
  callback(this.label);
  return this;
};

DropDownItemModel.prototype.bindTooltip = function(callback) {
  this.tooltipChangeCallbacks.push(callback);
  callback(this.tooltip);
  return this;
};

// Getters
DropDownItemModel.prototype.getLabel = function() {
  return this.label;
};

DropDownItemModel.prototype.getTooltip = function() {
  return this.tooltip;
};

DropDownItemModel.prototype.getData = function() {
  return this.data;
};

var DropDownModel = function() {
  // Private state
  this.selectedItemIdx = 0;
  this.dropDownItemModels = [];

  // Callback listeners
  this.selectedItemChangeCallbacks = [];
  this.dropDownItemModelsChangeCallbacks = [];
};

// Callback functions
DropDownModel.prototype.bindSelectedItem = function(callback) {
  this.selectedItemChangeCallbacks.push(callback);
  callback(this.dropDownItemModels[this.selectedItemIdx]);

  // Handle click
  return this;
};

DropDownModel.prototype.bindDropDownItemModels = function(callback) {
  this.dropDownItemModelsChangeCallbacks.push(callback);
  callback(this.dropDownItemModels);
  return this;
};

// Setters
DropDownModel.prototype.setSelectedItemIdx = function(index) {
  // Check: 'index' isn't out of bounds
  console.assert(index < this.dropDownItemModels.length);

  this.selectedItemIdx = index;
  this.selectedItemChangeCallbacks.forEach(function(callback) {
    callback(this.dropDownItemModels[this.selectedItemIdx]);
  }, this);
  return this;
};

DropDownModel.prototype.setDropDownItems = function(drop_down_item_models) {
  this.dropDownItemModels = drop_down_item_models;
  this.dropDownItemModelsChangeCallbacks.forEach(function(callback) {
    callback(this.dropDownItemModels);
  }, this);

  this.setSelectedItemIdx(0);
  return this;
};

// Getters
DropDownModel.prototype.getSelectedItem = function() {
  return this.dropDownItemModels[this.selectedItemIdx];
};

DropDownModel.prototype.getDropDownItemModels = function() {
  return this.dropDownItemModels;
};

var MyExperimentModel = function(
  id,    
  title,
  description,
  scopes_count,
  experiment_duration,
  start_time,
  short_code,
  experiment_status,
  payment_status,
  is_persisted
) {

  /**
   * Private state
   */
  this.id = id;
  this.title = title;
  this.description = description;
  this.scopesCount = scopes_count;
  this.experimentDuration = experiment_duration;
  this.startTime = start_time;
  this.shortCode = short_code;
  this.experimentStatus = experiment_status;
  this.paymentStatus = payment_status;
  this.isPersisted = is_persisted

  // Callbacks
  this.titleCallbacks = [];
  this.descriptionCallbacks = [];
  this.scopesCountCallbacks = [];
  this.experimentDurationCallbacks = [];
  this.startTimeCallbacks = [];
  this.experimentStatusCallbacks = [];
  this.paymentStatusCallbacks = [];
  this.shortCodeCallbacks = [];
  this.isPersistedCallbacks = [];
};

// Setters
MyExperimentModel.prototype.setId = function(id) {
  this.id = id;
  return this;
};

MyExperimentModel.prototype.setTitle = function(title) {
  this.title = title;
  this.titleCallbacks.forEach(function(callback) {
    callback(this.title); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setDescription = function(description) {
  this.description = description;
  this.descriptionCallbacks.forEach(function(callback) {
    callback(this.description); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setScopesCount = function(scopesCount) {
  this.scopesCount = scopesCount;
  this.scopesCountCallbacks.forEach(function(callback) {
    callback(this.scopesCount); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setExperimentDuration = function(experimentDuration) {
  this.experimentDuration = experimentDuration;
  this.experimentDurationCallbacks.forEach(function(callback) {
    callback(this.experimentDuration); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setStartTime = function(startTime) {
  this.startTime = startTime;
  this.startTimeCallbacks.forEach(function(callback) {
    callback(this.startTime); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setShortCode = function(shortCode) {
  this.shortCode = shortCode;
  this.shortCodeCallbacks.forEach(function(callback) {
    callback(this.shortCode); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setExperimentStatus = function(experimentStatus) {
  this.experimentStatus = experimentStatus;
  this.experimentStatusCallbacks.forEach(function(callback) {
    callback(this.experimentStatus); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setPaymentStatus = function(paymentStatus) {
  this.paymentStatus = paymentStatus;
  this.paymentStatusCallbacks.forEach(function(callback) {
    callback(this.paymentStatus); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setIsPersisted = function(is_persisted) {
  this.isPersisted = is_persisted;
  this.isPersistedCallbacks.forEach(function(callback) {
    callback(this.isPersisted);
  }, this);
  return this;
};

// Bind callbacks
MyExperimentModel.prototype.bindTitle = function(callback) {
  this.titleCallbacks.push(callback);
  callback(this.title);
  return this;
};

MyExperimentModel.prototype.bindDescription = function(callback) {
  this.descriptionCallbacks.push(callback);
  callback(this.description);
  return this;
};

MyExperimentModel.prototype.bindExperimentDuration = function(callback) {
  this.experimentDurationCallbacks.push(callback);
  callback(this.experimentDuration);
  return this;
};

MyExperimentModel.prototype.bindScopesCount = function(callback) {
  this.scopesCountCallbacks.push(callback);
  callback(this.scopesCount);
  return this;
};

MyExperimentModel.prototype.bindStartTime = function(callback) {
  this.startTimeCallbacks.push(callback);
  callback(this.startTime);
  return this;
};

MyExperimentModel.prototype.bindShortCode = function(callback) {
  this.shortCodeCallbacks.push(callback);
  callback(this.shortCode);
  return this;
};

MyExperimentModel.prototype.bindExperimentStatus = function(callback) {
  this.experimentStatusCallbacks.push(callback);
  callback(this.experimentStatus);
  return this;
};

MyExperimentModel.prototype.bindPaymentStatus = function(callback) {
  this.paymentStatusCallbacks.push(callback);
  callback(this.paymentStatus);
  return this;
};

MyExperimentModel.prototype.bindIsPersisted = function(callback) {
  this.isPersistedCallbacks.push(callback);
  return this;
};

// Getters
MyExperimentModel.prototype.getId = function() {
  return this.id;
};

MyExperimentModel.prototype.getDescription = function() {
  return this.description;
};

MyExperimentModel.prototype.getScopesCount = function() {
  return this.scopesCount;
};

MyExperimentModel.prototype.getExperimentDuration = function() {
  return this.experimentDuration;
};

MyExperimentModel.prototype.getStartTime = function() {
  return this.startTime;
};

MyExperimentModel.prototype.getShortCode = function() {
  return this.shortCode;
};

MyExperimentModel.prototype.getExperimentStatus = function() {
  return this.experimentStatus;
};

MyExperimentModel.prototype.getPaymentStatus = function() {
  return this.paymentStatus;
};

MyExperimentModel.prototype.getIsPerisisted = function() {
  return this.isPersisted;
};

var MyExperimentModelBuilder = function() {

  /**
   * Private state
   */
  var id = null;
  var title = null;
  var description = null;
  var scopesCount = null;
  var experimentDuration = null;
  var startTime = null;
  var shortCode = null;
  var experimentStatus = null;
  var paymentStatus = null;
  var isPersisted = null;

  /**
   * Privileged functions
   */
  this.build = function() {
    return new MyExperimentModel(
      id,
      title,
      description,
      scopesCount,
      experimentDuration,
      startTime,
      shortCode,
      experimentStatus,
      paymentStatus,
      isPersisted
    );
  };

  this.setId = function(_id) {
    id = _id;
    return this;
  };

  this.setTitle = function(_title) {
    title = _title;
    return this;
  };

  this.setDescription = function(_description) {
    description = _description;
    return this;
  };

  this.setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;
    return this;
  };

  this.setExperimentDuration = function(experiment_duration) {
    experimentDuration = experiment_duration;
    return this;
  };
  
  this.setStartTime = function(start_time) {
    startTime = start_time;
    return this;
  };

  this.setShortCode = function(short_code) {
    shortCode = short_code;
    return this;
  };

  this.setExperimentStatus = function(experiment_status) {
    experimentStatus = experiment_status;
    return this;
  };

  this.setPaymentStatus = function(payment_status) {
    paymentStatus = payment_status;
    return this;
  };

  this.setIsPersisted = function(is_persisted) {
    isPersisted = is_persisted;
    return this;
  };
};

var MyExperimentsPageModel = function() {

  /**
   * Private vars
   */
  this.myExperiments = [];

  /**
   * Callbacks
   */
  this.newExperimentCallbacks = []; 
  this.removeExperimentCallbacks = [];
  this.setExperimentsCallbacks = [];
};

MyExperimentsPageModel.prototype.addExperiment = function(experiment) {
  this.myExperiments.push(experiment);
  this.newExperimentCallbacks.forEach(function(callback) {
    callback(experiment);
  });
  return this;
};

MyExperimentsPageModel.prototype.removeExperiment = function(experiment) {
  // TODO: Need to rethink this
  Utils.removeElementFromArray(experiment, this.myExperiments);  
  this.removeExperimentsCallbacks.forEach(function(callback) {
    callback(experiment);
  });
  return this;
};

MyExperimentsPageModel.prototype.setExperiments = function(my_experiments) {
  this.myExperiments = my_experiments;
  this.setExperimentsCallbacks.forEach(function(callback) {
    callback(my_experiments);
  });
  return this;
};

// Bind Callbacks
MyExperimentsPageModel.prototype.bindAddExperiment = function(callback) {
  this.newExperimentCallbacks.push(callback);
  return this;
};

MyExperimentsPageModel.prototype.bindRemoveExperiment = function(callback) {
  this.removeExperimentCallbacks.push(callback);
  return this;
};

MyExperimentsPageModel.prototype.bindSetExperiments = function(callback) {
  this.setExperimentsCallbacks.push(callback);
  return this;
};

// Getters
MyExperimentsPageModel.prototype.getExperiments = function() {
  return this.myExperiments;
};

var NewExperimentModel = function() {

  this.scopeCountPickerModel = null;
  this.experimentDurationPickerModel = null;
  this.startTimePickerModel = null;
  this.startDatePickerModel = null;
  this.shortCodePickerModel = null;
};

var NewExperimentPageModel = function() {

  /**
   * Default starting state
   */
  var DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS = {
    min_value: 0,
    max_value: 15,
    step: 1,
    value: 0
  };

  var DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS = {
    min_value: 0,
    max_value: 15,
    step: 1,
    value: 0
  };

  /**
   * Private state
   */
  var scopesCountModel = null;
  var experimentDurationModel = null;
  var experimentTimePickerModel = null;
  var experimentDatePickerModel = null;
  var shortCodePickerModel = null;
  var pricingModel = null;

  /**
   * Private functions
   */
  var initializeScopesCountModel = function() {
    var slider_model = new SliderModel();
    return slider_model
      .setMinValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.min_value)
      .setMaxValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.max_value)
      .setStep(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.step)
      .setCurrentValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.value);
  };

  var initializeExperimentDurationModel = function() {
    var slider_model = new SliderModel();
    return slider_model
      .setMinValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.min_value)
      .setMaxValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.max_value)
      .setStep(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.step)
      .setCurrentValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.value);
  };

  var initializeExperimentDatePickerModel = function() {
    // Create data model
    var min_advance_day_count = 14;
    var max_advance_month_count = 4;
    var invalid_days_of_the_week = [0, 6];
    var invalid_dates = [
      new Date(2016, 4, 3),
      new Date(2016, 4, 4),
      new Date(2016, 4, 5)
    ];
    
    // Create model
    var date_picker_model = new DatePickerModel();
    return date_picker_model
      .setMinAdvanceDayCount(min_advance_day_count)
      .setMaxAdvanceMonthCount(max_advance_month_count)
      .setInvalidDaysOfTheWeek(invalid_days_of_the_week)
      .setInvalidDates(invalid_dates);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize models
    scopesCountModel = initializeScopesCountModel();
    experimentDurationModel = initializeExperimentDurationModel();
    experimentDatePickerModel = initializeExperimentDatePickerModel();
    experimentTimePickerModel = new DropDownModel();
    shortCodePickerModel = new DropDownModel();
    pricingModel = new PricingModel();
  };

  // Getters
  this.getScopesCountModel = function() {
    return scopesCountModel;
  };

  this.getExperimentDurationModel = function() {
    return experimentDurationModel;
  };

  this.getExperimentTimePickerModel = function() {
    return experimentTimePickerModel;
  };

  this.getExperimentDatePickerModel = function() {
    return experimentDatePickerModel;
  };

  this.getShortCodePickerModel = function() {
    return shortCodePickerModel;
  };

  this.getPricingModel = function() {
    return pricingModel;
  };
};

var NewMyExperimentModelBuilder = function() {

  /**
   * Default constants
   */
  var INITIAL_TITLE = '';
  var INITIAL_DESCRIPTION = '';
  var INITIAL_EXPERIMENT_STATUS = new OrderStatus();
  var INITIAL_PAYMENT_STATUS = new PaymentStatus();
  var INITIAL_IS_PERSISTED = false;

  /**
   * Private state
   */
  var builder = new MyExperimentModelBuilder();

  // Initialize builder with default data
  builder
    .setTitle(INITIAL_TITLE)
    .setDescription(INITIAL_DESCRIPTION)
    .setExperimentStatus(INITIAL_EXPERIMENT_STATUS)
    .setPaymentStatus(INITIAL_PAYMENT_STATUS)
    .setIsPersisted(INITIAL_IS_PERSISTED);

  /**
   * Privileged functions
   */
  this.build = function() {
    return builder.build(); 
  };

  this.setScopesCount = function(scopes_count) {
    builder.setScopesCount(scopes_count);
    return this;
  };

  this.setExperimentDuration = function(experiment_duration) {
    builder.setExperimentDuration(experiment_duration);
    return this;
  };
  
  this.setStartTime = function(start_time) {
    builder.setStartTime(start_time);
    return this;
  };

  this.setShortCode = function(short_code) {
    builder.setShortCode(short_code);
    return this;
  };
};

var OrderRequestModel = function() {

  // Order request state
  this.scopesCount = null;
  this.experimentDuration = null; // num hours
  this.startTime = null; // seconds from start of day
  this.startDate = null; // DateObj
  this.shortCodeId = null;

  // State change listeners
  this.scopesCountChangeListeners = [];
  this.experimentDurationChangeListeners = [];
  this.startTimeChangeListeners = [];
  this.startDateChangeListeners = [];
  this.shortCodeIdChangeListeners = [];
};

/**
 * Getters
 */
OrderRequestModel.prototype.getScopesCount = function() {
  return this.scopesCount;
};

OrderRequestModel.prototype.getExperimentDuration = function() {
  return this.experimentDuration;
};

OrderRequestModel.prototype.getStartTime = function() {
  return this.startTime;
};

OrderRequestModel.prototype.getStartDate = function() {
  return this.startDate;
};

OrderRequestModel.prototype.getShortCodeId = function() {
  return this.shortCodeId;
};

/**
 * Setters
 */

/**
 * Register event listeners
 */
OrderRequestModel.prototype.bindScopesCount = function(callback) {
  this.scopesCountChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindExperimentDuration = function(callback) {
  this.experimentDurationChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindStartTime = function(callback) {
  this.startTimeChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindStartDate = function(callback) {
  this.startDateChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindShortCode = function(callback) {
  this.shortCodeChangeListeners.push(callback);
  return this;
};

var PricingModel = function() {
  
  // Private state
  this.pricePerHour = 0;

  // Field listeners
  this.pricePerHourListeners = [];
};

/**
 * PricingModel state getters
 */
PricingModel.prototype.getPricePerHour = function() {
  return this.pricePerHour;
};

/**
 * Setters w/callbacks
 */
PricingModel.prototype.setPricePerHour = function(price) {
  this.pricePerHour = price;

  this.pricePerHourListeners.forEach(function(callback) {
    callback(this.pricePerHour);
  }, this); 
  return this;
};

/**
 * Register listeners
 */
PricingModel.prototype.bindPricePerHour = function(callback) {
  this.pricePerHourListeners.push(callback);
  callback(this.pricePerHour);
  return this;
};

var SliderModel = function() {
  // State
  this.minValue = 0;
  this.maxValue = 0;
  this.step = 0;
  this.currentValue = 0;

  // Callback listeners
  this.minValueCallbacks = [];
  this.maxValueCallbacks = [];
  this.stepCallbacks = [];
  this.currentValueCallbacks = [];
};

// Callback registration
SliderModel.prototype.bindMinValue = function(callback) {
  this.minValueCallbacks.push(callback);
  callback(this.minValue);
  return this;
};

SliderModel.prototype.bindMaxValue = function(callback) {
  this.maxValueCallbacks.push(callback);
  callback(this.maxValue);
  return this;
};

SliderModel.prototype.bindStep = function(callback) {
  this.stepCallbacks.push(callback);
  callback(this.step);
  return this;
};

SliderModel.prototype.bindCurrentValue = function(callback) {
  this.currentValueCallbacks.push(callback);
  callback(this.currentValue);
  return this;
};

// Setters
SliderModel.prototype.setMinValue = function(value) {
  this.minValue = value;
  this.minValueCallbacks.forEach(function(callback) {
    callback(this.minValue);
  }, this);
  return this;
};

SliderModel.prototype.setMaxValue = function(value) {
  this.maxValue = value;
  this.maxValueCallbacks.forEach(function(callback) {
    callback(this.maxValue);
  }, this);
  return this;
};

SliderModel.prototype.setStep = function(value) {
  this.step = value;
  this.stepCallbacks.forEach(function(callback) {
    callback(this.step);
  }, this);
  return this;
};

SliderModel.prototype.setCurrentValue = function(value) {
  this.currentValue = value;
  this.currentValueCallbacks.forEach(function(callback) {
    callback(this.currentValue);
  }, this);
  return this;
};

// Getters
SliderModel.prototype.getMinValue = function() {
  return this.minValue;
};

SliderModel.prototype.getMaxValue = function() {
  return this.maxValue;
};

SliderModel.prototype.getStep = function() {
  return this.step;
};

SliderModel.prototype.getCurrentValue = function() {
  return this.currentValue;
};

var UserModel = function() {

  // User state
  this.id = null;
  this.firstName = null;
  this.lastName = null;
  this.email = null;

  // State set event listeners
  this.nameSetListeners = [];
  this.emailSetListeners = [];

  // State change event listeners
  this.nameChangeListeners = [];
  this.emailChangeListeners = [];
};

/**
 * User state getters
 */
UserModel.prototype.getId = function() {
  return this.id;
};

UserModel.prototype.getFirstName = function() {
  return this.firstName;
};

UserModel.prototype.getLastName = function() {
  return this.lastName;
};

UserModel.prototype.getEmail = function() {
  return this.email;
};

/**
 * User state setters w/callbacks
 */
UserModel.prototype.setId = function(id) {
  this.id = id;
  return this;
};

UserModel.prototype.setName = function(first_name, last_name) {
  this.firstName = first_name;
  this.lastName = last_name;

  for (var i = 0; i < this.nameSetListeners.length; ++i) {
    this.nameSetListeners[i](this.firstName, this.lastName);
  }

  return this;
};

UserModel.prototype.setEmail = function(email) {
  this.email = email;

  for (var i = 0; i < this.emailSetListeners.length; ++i) {
    this.emailSetListeners[i](this.email);
  }

  return this;
};

/**
 * Bind "field set" event listeners 
 */
UserModel.prototype.bindSetName = function(callback) {
  this.nameSetListeners.push(callback); 
  return this;
};

UserModel.prototype.bindSetEmail = function(callback) {
  this.emailSetListeners.push(callback); 
  return this;
};

/**
 * "Field change" functions
 */
UserModel.prototype.changeName = function(first_name, last_name) {
  this.firstName = first_name;
  this.lastName = last_name;
  
  // Notify 'set listeners'
  for (var i = 0; i < this.nameSetListeners.length; ++i) {
    this.nameSetListeners[i](this.firstName, this.lastName);
  }

  // Notify 'change listeners'
  for (var i = 0; i < this.nameChangeListeners.length; ++i) {
    this.nameChangeListeners[i](this.firstName, this.lastName);
  }
  
  return this;
};

UserModel.prototype.changeEmail = function(email) {
  this.email = email;
  
  // Notify 'set' listeners
  for (var i = 0; i < this.emailSetListeners.length; ++i) {
    this.emailSetListeners[i](this.email);
  }

  // Notify 'change' listeners
  for (var i = 0; i < this.emailChangeListeners.length; ++i) {
    this.emailChangeListeners[i](this.email);
  }

  return this;
};

/**
 * Bind "field change" event listeners 
 */
UserModel.prototype.bindChangeName = function(callback) {
  this.nameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindChangeEmail = function(callback) {
  this.emailChangeListeners.push(callback); 
  return this;
};

var Utils = (function() {

  var CLASS_NAME_PROPERTY = "className";

  var HIDDEN_ATTR = 'hidden';
  var SELECTED_ATTR = 'selected';

  // Timestamp delimiters
  var DATE_DELIMITER = "-";
  var TIME_DELIMITER = ":";
  var DATE_TIME_SEPERATOR = " ";

  // Key codes
  var ENTER_KEY_CODE = 13;

  // Month names
  var POST_MERIDIAN = 'pm';
  var ANTE_MERIDIAN = 'am';

  var SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  this.hasClass = function(class_name, node) {
    console.assert(node != null);
    return 'classList' in node && node.classList.contains(class_name);
  };
  
  this.makePriceString = function(price) {

    // Group thousands with commas 
    var price_str = "";
    var price_in_dollars = Math.floor(price);
    
    var i = 1;
    var j = 1000;

    while (j < price_in_dollars) {
      var codon = Math.floor((price_in_dollars % j) / i);
      price_str = "," + codon.toString().concat(price_str);
      i = j;
      j *= 1000;
    }

    var leading_digits = Math.floor(price_in_dollars / i);
    price_str = leading_digits.toString().concat(price_str);

    // Stringify decimal digits
    var cents = Math.floor(price * 100) % 100;
    var cents_str = cents.toString();
    if (cents_str.length === 1) {
      cents_str = "0".concat(cents_str);
    }
    console.assert(cents_str.length === 2);

    cents_str = ".".concat(cents_str);
    return price_str.concat(cents_str);
  };

  this.stringifyNumberWithEnforcedDigitCount = function(number, digit_count) {
    var number_string = number.toString();
    console.assert(number_string.length <= digit_count);

    if (number_string.length < digit_count) {
      var zero_prefix = "0".repeat(digit_count - number_string.length);
      number_string = zero_prefix.concat(number_string);
    }

    return number_string;
  };

  /**
   * makeTimestampString()
   * @param DateObj date: {year, month, date}
   * @param TimeObj time: {hours, minutes, seconds}
   *   - 'hours' is in military time
   */
  this.makeTimestampString = function(date, time) {
    return date.year.toString() + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.month, 2) + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.date, 2) + DATE_TIME_SEPERATOR +
      stringifyNumberWithEnforcedDigitCount(time.hours, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.minutes, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.seconds, 2);
  };

  this.makeDateString = function(timestamp) {
    var js_date = new Date(timestamp);
    var serializeable_date = new SerializeableDate(
      js_date.getUTCFullYear(),
      js_date.getUTCMonth(),
      js_date.getUTCDate()
    );
    return serializeable_date.serialize();
  };

  /**
   * removeDomChildren()
   *   - remove all children from dom node
   * @param DOMElemet dom_node: some dom node
   */
  this.removeDomChildren = function(dom_node) {
    while (dom_node.firstChild) {
      dom_node.removeChild(dom_node.firstChild);
    }
  };

  this.makeTimestampIntervalString = function(starting_timestamp, ending_timestamp) {
    // Convert to native js date objects
    var starting_js_date = new Date(starting_timestamp);
    var ending_js_date = new Date(ending_timestamp);

    var serializeable_starting_date = new SerializeableDate(
      starting_js_date.getUTCFullYear(),
      starting_js_date.getUTCMonth(),
      starting_js_date.getUTCDate()
    );

    var serializeable_starting_time = new SerializeableTime(
      starting_js_date.getHours(),
      starting_js_date.getMinutes(),
      starting_js_date.getSeconds()
    );

    var interval_string = serializeable_starting_date.serialize() + ' ' +
        serializeable_starting_time.serializeWithoutSeconds() + ' - ';

    var serializeable_ending_time = new SerializeableTime(
      ending_js_date.getHours(),
      ending_js_date.getMinutes(),
      ending_js_date.getSeconds()
    );

    if (starting_js_date.getUTCFullYear() == ending_js_date.getUTCFullYear() &&
        starting_js_date.getUTCMonth() == ending_js_date.getUTCMonth() &&
        starting_js_date.getUTCDate() == ending_js_date.getUTCDate()
    ) {
      return interval_string + serializeable_ending_time.serializeWithoutSeconds(); 
    }
    
    var serializeable_ending_date = new SerializeableDate(
      ending_js_date.getUTCFullYear(),
      ending_js_date.getUTCMonth(),
      ending_js_date.getUTCDate()
    );

    return interval_string + serializeable_ending_date.serialize() + ' ' + 
        serializeable_ending_time.serializeWithoutSeconds();
  };

  this.synthesizeTemplate = function(
    template_store,
    template_id,
    parent_node,
    class_name
  ) {
    // Clear children from parent-node
    Utils.removeDomChildren(parent_node);

    // Clone template
    var raw_template = template_store.import.querySelector('#' + template_id);  
    var template_clone = document.importNode(raw_template.content, true);

    // Insert clone
    parent_node.appendChild(template_clone);
    var activated_clones = parent_node.getElementsByClassName(class_name);
    console.assert(activated_clones.length == 1);
    
    return activated_clones[0];
  };

  this.synthesizeTemplateIntoList = function(
    template_store,
    template_id,
    parent_node,
    class_name
  ) {
    // Clone template
    var raw_template = template_store.import.querySelector('#' + template_id);
    var template_clone = document.importNode(raw_template.content, true);

    // Insert clone
    parent_node.appendChild(template_clone);
    var activated_clones = parent_node.getElementsByClassName(class_name);
    console.assert(activated_clones.length > 0);

    return activated_clones[activated_clones.length - 1];
  };

  this.bindNode = function(
    parent_node,
    class_name
  ) {
    var node_list = parent_node.getElementsByClassName(class_name);
    console.assert(node_list.length == 1);
    return node_list[0];
  };

  this.bindNodeInfo = function(parent_node, node_info) {
    node_info.node = Utils.bindNode(
      parent_node,
      node_info.className
    );
  };

  this.hideNode = function(node) {
    node.setAttribute(HIDDEN_ATTR, ''); 
    markNode(node, HIDDEN_ATTR);
  };

  this.showNode = function(node) {
    unmarkNode(node, HIDDEN_ATTR);
  };
  
  this.selectNode = function(node) {
    markNode(node, SELECTED_ATTR); 
  };

  this.unselectNode = function(node) {
    unmarkNode(node, SELECTED_ATTR);
  };

  this.markNode = function(node, attr) {
    node.setAttribute(attr, '');
  };

  this.unmarkNode = function(node, attr) {
    node.removeAttribute(attr); 
  };

  this.bindClickBeyondNode = function(node, callback) {
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_idx in event.path) {
        var current_node = event.path[node_idx];
        // User clicked on the time-picker, so don't hide it!
        if (current_node == node) {
          return;
        }
      }    

      callback();
    });
  };

  var compareDates = function(date1, date2) {
    // Compare years
    if (date1.getFullYear() < date2.getFullYear()) {
      return -1;
    }

    if (date1.getFullYear() > date2.getFullYear()) {
      return 1;
    }

    // Compare months
    if (date1.getMonth() < date2.getMonth()) {
      return -1;
    }

    if (date1.getMonth() > date2.getMonth()) {
      return 1;
    }

    // Compare days
    if (date1.getDate() < date2.getDate()) {
      return -1;
    }

    if (date1.getDate() > date2.getDate()) {
      return 1;
    }

    // Dates are equal
    return 0;
  };

  var contains = function(needle, haystack) {
    return haystack.indexOf(needle) != -1; 
  };

  var trimLast = function(str) {
    return str.susbtring(0, str.length - 1);
  };

  var removeElementFromArray = function(needle, haystack) {
    var index = haystack.indexOf(needle);
    if (index != -1) {
      haystack.splice(index, 1);
    }
  };

  var selectTextRange = function(node) {
    var range = document.createRange();
    range.selectNodeContents(node);
    var sel = window.getSelection();
    sel.removeAllRanges();
    sel.addRange(range);
  };

  var unselectTextRange = function(node) {
    var selection = window.getSelection();
    if (hasClass(node.className, selection.anchorNode.parentElement)) {
      selection.removeAllRanges();
    }
  };

  var isEnterKeyPressed = function(event) {
    return 'charCode' in event && event.charCode == ENTER_KEY_CODE;
  };

  var isWhiteSpace = function(str) {
    return str.trim().length == 0;
  };

  var getShortMonthName = function(month_idx) {
    console.assert(month_idx < 12);
    return SHORT_MONTH_NAMES[month_idx];
  };

  var toCivilianHour = function(military_hour) {
    var civilian_hour = (military_hour > 12)
      ? military_hour - 12
      : military_hour;

    var meridian_designation = (military_hour > 11 && military_hour != 24)
      ? POST_MERIDIAN
      : ANTE_MERIDIAN;

    return civilian_hour.toString() + " " + meridian_designation; 
  };

  var toHoursAndMinutesString = function(start_time) {
    var military_hour = start_time.getHours();
    var time_str = (military_hour > 12)
      ? military_hour - 12
      : military_hour;

    time_str += TIME_DELIMITER + stringifyNumberWithEnforcedDigitCount(
      start_time.getMinutes(),
      2
    );

    var meridian_designation = (military_hour > 11 && military_hour != 24)
      ? POST_MERIDIAN
      : ANTE_MERIDIAN;

    return time_str + " " + meridian_designation;
  };

  return {
    hasClass: hasClass,
    makePriceString: makePriceString,
    makeTimestampString: makeTimestampString,
    makeDateString: makeDateString,
    removeDomChildren: removeDomChildren,
    stringifyNumberWithEnforcedDigitCount: stringifyNumberWithEnforcedDigitCount,
    makeTimestampIntervalString: makeTimestampIntervalString,
    synthesizeTemplate: synthesizeTemplate,
    synthesizeTemplateIntoList: synthesizeTemplateIntoList,
    bindNode: bindNode,
    bindNodeInfo: bindNodeInfo,
    hideNode: hideNode,
    showNode: showNode,
    bindClickBeyondNode: bindClickBeyondNode,
    compareDates: compareDates,
    contains: contains,
    trimLast : trimLast,
    removeElementFromArray : removeElementFromArray,
    selectNode: selectNode,
    unselectNode: unselectNode,
    markNode: markNode,
    unmarkNode: unmarkNode,
    selectTextRange : selectTextRange,
    unselectTextRange: unselectTextRange,
    isEnterKeyPressed : isEnterKeyPressed,
    isWhiteSpace: isWhiteSpace,
    getShortMonthName: getShortMonthName,
    toCivilianHour: toCivilianHour,
    toHoursAndMinutesString : toHoursAndMinutesString
  };
})();

function ApiControllerWrapper(api_object) {

  /**
   * Private state
   */
  var apiObject = api_object;

  var successListeners = [];
  var logicalFailureListeners = [];
  var nonLogicalFailureListeners = [];
  
  /**
   * Private functions
   */
  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successListeners.length; ++i) {
      successListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };
  
  var logicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < logicalFailureListeners.length; ++i) {
      logicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < nonLogicalFailureListeners.length; ++i) {
      nonLogicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  /**
   * Privileged functions
   */
  this.send = function() {
    console.assert(apiObject != null);

    // Bind api listeners
    apiObject.setSuccessfulApiCallback(successfulApiCallback); 
    apiObject.setLogicalApiFailureCallback(logicallyFailedApiCallback);
    apiObject.setNonLogicalApiFailureCallback(nonLogicallyFailedApiCallback);

    // Execute api call
    apiObject.send();
  };

  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindSuccess = function(callback) {
    successListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindLogicalFailure = function(callback) {
    logicalFailureListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  this.bindNonLogicalFailure = function(callback) {
    nonLogicalFailureListeners.push(callback);
    return this;
  };
};

var ConfirmOrderApiController = function() {

  /**
   * Private state
   */
  var confirmOrderApi = null;
  var successListeners = [];
  var logicalFailureListeners = [];
  var nonLogicalFailureListeners = [];

};

var GetStartupDataApiController = function() {

  /**
   * Private state
   */
  var getStartupDataApi = null;
  var successListeners = [];
  var logicalFailureListeners = [];
  var nonLogicalFailureListeners = [];

  /**
   * fetch()
   * - fetches startup data
   */
  this.fetch = function() {
    // Initialize api and bind event listeners
    if (getStartupDataApi === null) {
      getStartupDataApi = new GetStartupDataApi(ScopesNetwork);

      // Bind api listeners
      getStartupDataApi.setSuccessfulApiCallback(successfulApiCallback);
      getStartupDataApi.setLogicalApiFailureCallback(logicallyFailedApiCallback);
      getStartupDataApi.setNonLogicalApiFailureCallback(nonLogicallyFailedApiCallback);
    }

    // Fetch startup data from server
    getStartupDataApi.send();
  };

  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successListeners.length; ++i) {
      successListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };
  
  var logicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < logicalFailureListeners.length; ++i) {
      logicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < nonLogicalFailureListeners.length; ++i) {
      nonLogicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindSuccess = function(callback) {
    successListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindLogicalFailure = function(callback) {
    logicalFailureListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  this.bindNonLogicalFailure = function(callback) {
    nonLogicalFailureListeners.push(callback);
    return this;
  };
};

var UpdateConfirmedOrderApiController = (function() {

  /**
   * Private state
   */
  var updateConfirmedOrderApi = null;
  var successfulApiCallbackListeners = [];
  var failedLogicalApiCallbackListeners = [];
  var failedNonLogicalApiCallbackListeners = [];

  /**
   * update()
   * - update the specified confirmed order
   * @param UpdateConfirmedOrderRequest request: update request
   */
  var update = function(request) {
    
  };
  
  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successfulApiCallbackListeners.length; ++i) {
      successfulApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };
  
  var logicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < logicallyFailedApiCallbackListeners.length; ++i) {
      logicallyFailedApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    console.nonLog("WARNING: Logically failed api response!");
    console.nonLog(api_response); 
    
    for (var i = 0; i < nonLogicallyFailedApiCallbackListeners.length; ++i) {
      nonLogicallyFailedApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  var registerSuccessfulApiCallback = function(callback) {
    successfulApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  var registerLogicalFailedApiCallback = function(callback) {
    logicallyFailedApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  var registerNonLogicalFailedApiCallback = function(callback) {
    logicallyFailedApiCallbackListeners.push(callback);
    return this;
  };

  return {
    update: update,
    registerSuccessfulApiCallback: registerSuccessfulApiCallback,
    registerLogicalFailedApiCallback: registerLogicalFailedApiCallback,
    registerNonLogicalFailedApiCallback: registerNonLogicalFailedApiCallback
  };

})();

var UpdateConfirmedOrderRequest = function(
    order_id,
    title,
    is_title_removed,
    description,
   is_description_removed 
) {

  this.orderId = order_id;
  this.title = title;
  this.isTitleRemoved = is_title_removed;
  this.description = description;
  this.isDescriptionRemoved = is_description_removed;

  // Check: can't remove title and supply a new one
  console.assert(!this.isTitleRemoved || this.title == null);

  // Check: can't remove description and supply a new one
  console.assert(!this.isDescriptionRemoved || this.description == null);
};

UpdateConfirmedOrderRequest.prototype.getId = function() {
  return this.orderId;
};

UpdateConfirmedOrderRequest.prototype.isTitleRemoved = function() {
  return this.isTitleRemoved;
};

UpdateConfirmedOrderRequest.prototype.getTitle = function() {
  return this.title;
};

UpdateConfirmedOrderRequest.prototype.isDescriptionRemoved = function() {
  return this.isDescriptionRemoved;
};

UpdateConfirmedOrderRequest.prototype.getDescription = function() {
  return this.description;
};

var ConfirmOrderUiController = (function() {
  
  /**
   * Class-bound ui symbols
   */
  var MULTIPLIER_LABEL_SYMBOL_INFO = {
    className: 'payment-multiplier-label',
    symbol: 'x'
  };

  var ASSIGNMENT_LABEL_SYMBOL_INFO = {
    className: 'payment-assignment-label',
    symbol: '='
  };

  var CURRENCY_UNIT_SYMBOL_INFO = {
    className: 'payment-currency-unit-label',
    symbol: '$'
  };

  /**
   * Private state
   */
  var isInitialized = false;
  var hourlyCost = 0;
  var scopesCount = 0;
  var experimentDuration = 0;
  var totalPrice = 0;
  var confirmOrderButtonOnClickListeners = [];
  var cancelOrderButtonOnClickListeners = [];

  /**
   * Dom Nodes
   */
  var rootNode = {
    id: 'pricing-confirmation-form-container',
    node: null
  };

  var confirmOrderButtonNode = {
    id: 'confirm-payment-button',
    node: null
  };
  
  var cancelOrderButtonNode = {
    id: 'cancel-payment-button',
    node: null
  };

  var scopesCountNode = {
    number: {
      id: 'payment-scopes-count-amount-label',
      node: null
    },
    unit: {
      id: 'payment-scopes-count-unit-label',
      node: null,
      singular: 'scope',
      plural: 'scopes'
    }
  };

  var experimentDurationNode = {
    number: {
      id: 'payment-experiment-duration-amount-label',
      node: null
    },
    unit: {
      id: 'payment-experiment-duration-unit-label',
      node: null,
      singular: 'hour',
      plural: 'hours'
    }
  };

  var hourlyPriceNode = {
    number: {
      id: 'payment-hourly-price-amount-label',
      node: null
    }
  };

  var paymentAmountNode = {
    id: 'payment-total-price-label',
    node: null
  };

  /**
   * Private methods
   */
  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindPriceComponentNode = function(price_component_node) {
    bindInternalNode(price_component_node.number); 
    if (price_component_node.hasOwnProperty("unit")) {
      bindInternalNode(price_component_node.unit); 
    }
  };

  var bindNodes = function() {
    bindInternalNode(rootNode); 
    bindInternalNode(paymentAmountNode);

    bindInternalNode(confirmOrderButtonNode);
    confirmOrderButtonNode.node.onclick = function() {
      for (var i = 0; i < confirmOrderButtonOnClickListeners.length; ++i) {
        confirmOrderButtonOnClickListeners[i](); 
      }
    };

    bindInternalNode(cancelOrderButtonNode);
    cancelOrderButtonNode.node.onclick = function() {
      for (var i = 0; i < cancelOrderButtonOnClickListeners.length; ++i) {
        cancelOrderButtonOnClickListeners[i](); 
      }
    };

    bindPriceComponentNode(scopesCountNode);
    bindPriceComponentNode(experimentDurationNode);
    bindPriceComponentNode(hourlyPriceNode);
  };

  var populateClassBoundUiSymbol = function(class_bound_ui_symbol) {
    var dom_nodes = rootNode.node.getElementsByClassName(class_bound_ui_symbol.className);
    for (var i = 0; i < dom_nodes.length; ++i) {
      dom_nodes[i].innerHTML = class_bound_ui_symbol.symbol;
    }
  };
  
  var initDisplay = function() {
    // Populate dom nodes with ui symbols 
    populateClassBoundUiSymbol(MULTIPLIER_LABEL_SYMBOL_INFO);
    populateClassBoundUiSymbol(ASSIGNMENT_LABEL_SYMBOL_INFO);
    populateClassBoundUiSymbol(CURRENCY_UNIT_SYMBOL_INFO);

    // Initialize price label
    setHourlyCost(0);
    setScopesCount(0);
    setExperimentDuration(0);
    updatePrice();
  };
  
  var updatePrice = function() {
    // Recompute price
    totalPrice = scopesCount * experimentDuration * hourlyCost;

    // Update price display
    paymentAmountNode.node.innerHTML = Utils.makePriceString(totalPrice); 
  };

  var updatePriceContributingNodeIfInitialized = function(price_contributing_node, value) {
    if (isInitialized) {
      // Update value
      price_contributing_node.number.node.innerHTML = value;

      // Update unit
      if (price_contributing_node.hasOwnProperty("unit")) {
        price_contributing_node.unit.node.innerHTML = (value === 1)
          ? price_contributing_node.unit.singular
          : price_contributing_node.unit.plural;
      }

      // Recompute price and update ui
      updatePrice();
    } 
  };

  /**
   * Public methods
   */
  var setHourlyCost = function(hourly_cost) {
    hourlyCost = hourly_cost;
    updatePriceContributingNodeIfInitialized(hourlyPriceNode, Utils.makePriceString(hourly_cost));
    return this;
  };

  var setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;
    updatePriceContributingNodeIfInitialized(scopesCountNode, scopes_count);
    return this;
  };

  var setExperimentDuration = function(experiment_duration) {
    experimentDuration = experiment_duration; 
    updatePriceContributingNodeIfInitialized(experimentDurationNode, experiment_duration);
    return this;
  };

  var registerConfirmOrderOnClickListener = function(callback) {
    confirmOrderButtonOnClickListeners.push(callback);
  };

  var registerCancelOrderOnClickListener = function(callback) {
    cancelOrderButtonOnClickListeners.push(callback);
  };

  var getTotalPrice = function() {
    return totalPrice; 
  };

  var init = function() {
    console.assert(isInitialized === false, "ERROR: don't initialize ConfirmOrderUiController more than once!");
    isInitialized = true;

    // Bind all nodes and attach event listeners
    bindNodes(); 
    
    // Render dynamic ui elements
    initDisplay();
  };

  return {
    init: init,
    setHourlyCost: setHourlyCost,
    setScopesCount: setScopesCount,
    setExperimentDuration: setExperimentDuration,
    registerConfirmOrderOnClickListener: registerConfirmOrderOnClickListener,
    registerCancelOrderOnClickListener: registerCancelOrderOnClickListener,
    getTotalPrice: getTotalPrice
  };
})();

var ExperimentDurationUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var EXPERIMENT_DURATION_UNIT_SINGULAR = "hour";
  var EXPERIMENT_DURATION_UNIT_PLURAL = "hours";

  /**
   * Private state
   */
  var experimentDuration = 0;
  var onChangeCallback = function(duration) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'duration-form-container',
    node: null
  };

  var validIconNode = {
    id: 'duration-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'duration-invalid-icon',
    node: null
  };
  
  var experimentDurationValueNode = {
    id: 'duration-display',
    node: null
  };

  var experimentDurationUnitNode = {
    id: 'duration-display-unit',
    node: null
  };

  var experimentDurationSliderNode = {
    id: 'duration-input',
    node: null
  };

  /**
   * Private functions
   */
  var showProperValidationIcon = function() {
    if (isValidInput()) {
      showValidIcon();
    } else {
      showInvalidIcon();
    }
  };

  var showValidIcon = function() {
    hideValidationIcon(invalidIconNode);
    showValidationIcon(validIconNode);
  };

  var showInvalidIcon = function() {
    hideValidationIcon(validIconNode);
    showValidationIcon(invalidIconNode);
  };

  var hideBothValidationIcons = function() {
    hideValidationIcon(invalidIconNode);
    hideValidationIcon(validIconNode);
  };

  var hideValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.setAttribute(HIDDEN_VALIDATION_ICON_ATTR, '');
  };

  var showValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.removeAttribute(HIDDEN_VALIDATION_ICON_ATTR);
  }

  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindNodes = function() {
    // Bind internal nodes
    bindInternalNode(rootNode);
    bindInternalNode(experimentDurationValueNode);
    bindInternalNode(experimentDurationUnitNode);
    bindInternalNode(experimentDurationSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    experimentDurationSliderNode.node.onchange = function() {
      experimentDuration = this.immediateValue;
      updateDurationDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateDurationDisplay = function() {
    // Render scope count value
    experimentDurationValueNode.node.innerHTML = experimentDuration;

    // Update scope count unit
    experimentDurationUnitNode.node.innerHTML = (experimentDuration === 1)
      ? EXPERIMENT_DURATION_UNIT_SINGULAR
      : EXPERIMENT_DURATION_UNIT_PLURAL;

    // Notify listeners
    onChangeCallback(experimentDuration);
  };

  /**
   * Public functions
   */
  var setDuration = function(experiment_duration) {
    experimentDuration = experiment_duration;

    // Update ui
    experimentDurationSliderNode.node.value = experiment_duration;
    updateDurationDisplay();

    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getDuration = function() {
    return experimentDuration;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scopes count
    setInitialState();
  };
  
  var setInitialState = function() {
    setDuration(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return experimentDuration !== 0; 
  };

  var signalInvalidInput = function() {
    // Short circuit if valid input...
    if (isValidInput()) {
      return;
    }

    showInvalidIcon();
  };

  return {
    init: init,
    setDuration: setDuration,
    getDuration: getDuration,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput,
    setInitialState: setInitialState
  };
})();

var NewExperimentUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_PAGE_ATTR = 'hidden-new-experiment-page';

  /**
   * Dom info
   */
  var rootNode = {
    id: 'add-exp-center-page',
    node: null
  };

  /**
   * Private state
   */
  var shortCodePicker = null;
  var calendarPicker = null;
  var timePicker = null;
  var confirmedOrderListeners = [];

  /**
   * Private functions
   */
  var isValidInput = function() {
    return ScopesCountUiController.getScopesCount() !== 0 &&
      ExperimentCountUiController.getDuration() !== 0;
  };

  var registerOnClickListeners = function() {
    ConfirmOrderUiController.registerConfirmOrderOnClickListener(confirmOrder);

    ConfirmOrderUiController.registerCancelOrderOnClickListener(cancelOrder);  
  };

  var registerEventListeners = function() {
    registerOnClickListeners();
  };

  /**
   * Public methods
   */
  /**
   * confirmOrder()
   * - Ensure valid input states.
   *   - invalid input: prompt user to to fix invalid input
   *   - valid input: hit server confirm-order api 
   */
  var confirmOrder = function() {
    // Check for invalid input -- notify user of all invalid input
    var is_valid_input = true;

    if (!ScopesCountUiController.isValidInput()) {
      ScopesCountUiController.signalInvalidInput(); 
      is_valid_input = false; 
    } 

    if (!ExperimentDurationUiController.isValidInput()) {
      ExperimentDurationUiController.signalInvalidInput(); 
      is_valid_input = false; 
    }

    // Short-circuit due to invalid input
    if (!is_valid_input) {
      return;
    }

    // Send confirm-order request to server
    var confirm_order_api = new ConfirmOrderApi(ScopesNetwork);   
    confirm_order_api.setScopesCount(ScopesCountUiController.getScopesCount());
    confirm_order_api.setExperimentDuration(ExperimentDurationUiController.getDuration());
    confirm_order_api.setPrice(ConfirmOrderUiController.getTotalPrice());

    var timestamp = Utils.makeTimestampString(
      calendarPicker.getSelectedDate(),
      timePicker.getSelectedTime()
    );
    confirm_order_api.setStartTimestamp(timestamp);
    
    confirm_order_api.setShortCodeId(shortCodePicker.getSelectedShortCode().id);

    confirm_order_api.setSuccessfulApiCallback(function(api_response) {
      console.log(api_response);
      for (var i = 0; i < confirmedOrderListeners.length; ++i) {
        confirmedOrderListeners[i]();
      }
      
    });

    confirm_order_api.setLogicalApiFailureCallback(function(api_response) {
      console.log(api_response);
    });

    confirm_order_api.setNonLogicalApiFailureCallback(function(api_response) {
      console.log(api_response);
    });

    confirm_order_api.send();
    
    // Reset order ui
    cancelOrder();
  };

  /**
   * cancelOrder()
   * - revert all ui elements to original state
   */
  var cancelOrder = function() {
    ScopesCountUiController.setInitialState();  
    ExperimentDurationUiController.setInitialState();  
    calendarPicker.setInitialState();
    shortCodePicker.setInitialState();
    timePicker.setInitialState();
  };

  var init = function(template_store) {
    // Bind root node
    rootNode.node = document.getElementById(rootNode.id);
    console.assert(rootNode.node !== null);

    // Configure confirm-order controller
    ConfirmOrderUiController.init();

    // Configure scopes count ui contrller
    ScopesCountUiController.setOnChangeCallback(function(scopes_count) {
      ConfirmOrderUiController.setScopesCount(scopes_count);
    });
    ScopesCountUiController.init();
   
    // Configure experiment duration ui contrller
    ExperimentDurationUiController.setOnChangeCallback(function(experiment_duration) {
      ConfirmOrderUiController.setExperimentDuration(experiment_duration);
    });
    ExperimentDurationUiController.init();
  
    // Configure short code picker
    shortCodePicker = new ShortCodePicker(
      template_store,
      'existing-short-code-picker'
    );
    shortCodePicker.init();
    
    /**
     * Configure time-picker element
     */
    var start_time = {
      hours: 10,
      minutes: 00 
    };

    var end_time = {
      hours: 17,
      minutes: 30 
    };

    timePicker = new TimePicker(
      template_store,
      'exp-time-picker',
      start_time,
      end_time,
      30
    ); 
    timePicker.init();

    /**
     * Configure calendar element
     */
    var disallowed_week_days = new Set([0, 6]);
    calendarPicker = new Calendar(
        template_store,
        'exp-date-calendar',
        disallowed_week_days,
        {},
        3,
        7 
    );
    calendarPicker.init();

    // Register listeners on startup-data api call
    GetStartupDataApiController.registerSuccessfulApiCallback(function(json_response, api_keys) {
      shortCodePicker.setShortCodes(json_response[api_keys.short_codes]);
      ConfirmOrderUiController.setHourlyCost(json_response[api_keys.hourly_price]);
    }); 

    // Register event listeners
    registerEventListeners();
    
    // Initialize ui to 'show' state
    show();
  };

  var hide = function() {
    rootNode.node.setAttribute(HIDDEN_PAGE_ATTR, '');    
  };

  var show = function() {
    rootNode.node.removeAttribute(HIDDEN_PAGE_ATTR);
  };

  var registerOrderConfirmedListener = function(callback) {
    confirmedOrderListeners.push(callback);
  };

  return {
    init: init,
    confirmOrder: confirmOrder,
    cancelOrder: cancelOrder,
    hide: hide,
    show: show,
    registerOrderConfirmedListener: registerOrderConfirmedListener
  };
})();

var ScopesCountUiController = (function() {
  
  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var SCOPES_UNIT_SINGULAR = "scope";
  var SCOPES_UNIT_PLURAL = "scopes";

  /**
   * Private state
   */
  var scopesCount = 0;
  var onChangeCallback = function(num_scopes) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'scopes-count-input-container',
    node: null
  };
  
  var validIconNode = {
    id: 'scopes-count-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'scopes-count-invalid-icon',
    node: null
  };

  var scopesCountValueNode = {
    id: 'scopes-count-display',
    node: null
  };

  var scopesCountUnitNode = {
    id: 'scopes-count-display-unit',
    node: null
  };

  var scopesCountSliderNode = {
    id: 'scopes-count-input',
    node: null
  };

  /**
   * Private functions
   */
  var showProperValidationIcon = function() {
    if (isValidInput()) {
      showValidIcon();
    } else {
      showInvalidIcon();
    }
  };

  var showValidIcon = function() {
    hideValidationIcon(invalidIconNode);
    showValidationIcon(validIconNode);
  };

  var showInvalidIcon = function() {
    hideValidationIcon(validIconNode);
    showValidationIcon(invalidIconNode);
  };

  var hideBothValidationIcons = function() {
    hideValidationIcon(invalidIconNode);
    hideValidationIcon(validIconNode);
  };

  var hideValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.setAttribute(HIDDEN_VALIDATION_ICON_ATTR, '');
  };

  var showValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.removeAttribute(HIDDEN_VALIDATION_ICON_ATTR);
  }

  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindNodes = function() {
    // Bind internal nodes
    bindInternalNode(rootNode);
    bindInternalNode(scopesCountValueNode);
    bindInternalNode(scopesCountUnitNode);
    bindInternalNode(scopesCountSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    scopesCountSliderNode.node.onchange = function() {
      scopesCount = this.immediateValue;
      updateScopesCountDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateScopesCountDisplay = function() {
    // Render scope count value
    scopesCountValueNode.node.innerHTML = scopesCount;

    // Update scope count unit
    scopesCountUnitNode.node.innerHTML = (scopesCount === 1)
      ? SCOPES_UNIT_SINGULAR
      : SCOPES_UNIT_PLURAL;
      
    // Notify listeners
    onChangeCallback(scopesCount);
  };

  /**
   * Public functions
   */
  var setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;

    // Update ui
    scopesCountSliderNode.node.value = scopes_count;
    updateScopesCountDisplay();
    
    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getScopesCount = function() {
    return scopesCount;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scope count and ui
    setInitialState();
  };

  var setInitialState = function() {
    setScopesCount(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return scopesCount !== 0; 
  };

  var signalInvalidInput = function() {
    // Short circuit if valid input...
    if (isValidInput()) {
      return;
    }

    showInvalidIcon();
  };

  return {
    init: init,
    setScopesCount: setScopesCount,
    getScopesCount: getScopesCount,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput,
    setInitialState: setInitialState
  };
})();

var SidePanelUiController = (function() {

  /**
   * Ui attributes
   */
  var START_HIDDEN_ATTR = "start-hidden";
  
  /**
   * Ui node id's 
   */
  var CENTER_PAGE_TITLE_LABEL_ID = 'center-page-title-label';
  var NAVIGATION_BUTTON_CONTAINER_ID = 'nav-btns-container';
  var CENTER_PANEL_PAGE_CONTAINER = 'center-panel-page-container';

  /**
   * Private state
   */
  var currentlySelectedTabAndPageInfo = null;
  var centerPageTitleLabel = null;
  var centerPanelPageContainer = null;

  var newExperimentInfo = {
    tab_info: {
      button_title: 'Add Experiment',
      icon_type: 'add-circle-outline',
      tab: null
    },
    page_info: {
      page: null
    }
  };

  var myExperimentsInfo = {
    tab_info: {
      button_title: 'My Experiments',
      icon_type: 'group-work',
      tab: null
    },
    page_info: {
      id: 'my-exp-center-page',
      page: null
    }
  };

  var feedbackInfo = {
    tab_info: {
      button_title: 'Feedback',
      icon_type: 'question-answer',
      tab: null
    },
    page_info: {
      id: 'feedback-center-page',
      page: null
    }
  };

  var technicianInfo = {
    tab_info: {
      button_title: 'Technician',
      icon_type: 'build',
      tab: null
    },
    page_info: {
      id: 'technician-center-page',
      page: null
    }
  };

  var initTabInfo = function(
    template_store,
    tab_parent_node,
   tab_and_page_info 
  ) {
    var tab_info = tab_and_page_info.tab_info;

    // Initialize tab info
    tab_info.tab = new SidePanelTab(
      template_store,
      tab_parent_node,
      tab_info.button_title,
      tab_info.icon_type
    );

    tab_info.tab.registerOnClickListener(function() {
      selectNewTabAndShowNewPage(tab_and_page_info);
    });

    tab_info.tab.init();
  };

  var deselectCurrentTabAndHideCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.deselect();
    currentlySelectedTabAndPageInfo.page_info.page.hide();
  };

  var selectCurrentTabAndShowCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.select();
    currentlySelectedTabAndPageInfo.page_info.page.show();
    centerPageTitleLabel.innerHTML = currentlySelectedTabAndPageInfo.tab_info.button_title;
  };

  var selectNewTabAndShowNewPage = function(tab_and_page_info) {
    deselectCurrentTabAndHideCurrentPage();
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  var initTabAndPageInfos = function(template_store) {
    // Init side-panel-container node
    var tab_parent_node = document.getElementById(NAVIGATION_BUTTON_CONTAINER_ID);

    // Init new experiment page/tab info
    newExperimentInfo.page_info.page = NewExperimentUiController;
    newExperimentInfo.page_info.page.init(template_store);
   
    // Init my experiments page
    myExperimentsInfo.page_info.page = new MyExperimentsPage(
      template_store,
      myExperimentsInfo.page_info.id,
      false
    );
    myExperimentsInfo.page_info.page.init();

    // Init feedback experiment page
    feedbackInfo.page_info.page = new FeedbackPage(
      template_store,
      feedbackInfo.page_info.id,
      false
    );
    feedbackInfo.page_info.page.init();

    // Init technician page
    // technicianInfo.page_info.page = new TechnicianPage(
    //   template_store,
    //   technicianInfo.page_info.id,
    //   false
    // );
    // technicianInfo.page_info.page.init();

    // Configure tabs
    initTabInfo(template_store, tab_parent_node, newExperimentInfo); 
    initTabInfo(template_store, tab_parent_node, myExperimentsInfo); 
    initTabInfo(template_store, tab_parent_node, feedbackInfo); 
    // initTabInfo(template_store, tab_parent_node, technicianInfo); 
  };

  function initSelectedTabAndPage(tab_and_page_info) {
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  /**
   * init()
   * - initialize ui node bindings, event listeners, and starting
   *   ui state
   */
  var init = function(template_store) {
    // Init center-page title node
    centerPageTitleLabel = document.getElementById(CENTER_PAGE_TITLE_LABEL_ID);
    centerPanelPageContainer = document.getElementById(CENTER_PANEL_PAGE_CONTAINER);

    // Initialize tab and center page controllers and ui elements
    initTabAndPageInfos(template_store);

    initSelectedTabAndPage(newExperimentInfo);

    centerPanelPageContainer.removeAttribute(START_HIDDEN_ATTR);
  };

  var getMyExperimentsView = function() {
    console.assert(myExperimentsInfo.page_info.page !== null);
    return myExperimentsInfo.page_info.page;
  };

  return {
    init: init,
    getMyExperimentsView: getMyExperimentsView
  };
})();

ConfirmOrderApi.prototype = new ScopesApi();
ConfirmOrderApi.prototype.constructor = ConfirmOrderApi;

function ConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x3;

  // Api request field keys
  this.apiRequestKeys = {
    scopes_count: "scopes-count",
    experiment_duration: "duration",
    start_timestamp: "start-time",
    short_code_id: "short-code-id",
    price: "price"
  };

  // Api response field keys
  this.apiResponseKeys = {
    id : 'id'
  };
}

ConfirmOrderApi.prototype.getApiRequestKeys = function() {
  return this.apiRequestKeys; 
};

ConfirmOrderApi.prototype.getApiResponseKeys = function() {
  return this.apiResponseKeys;
};

ConfirmOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.apiRequestKeys.scopes_count] = scopes_count;
  return this;
};

ConfirmOrderApi.prototype.setExperimentDuration = function(duration) {
  this.data[this.apiRequestKeys.experiment_duration] = duration;
  return this;
};

ConfirmOrderApi.prototype.setStartTimestamp = function(start_timestamp) {
  this.data[this.apiRequestKeys.start_timestamp] = start_timestamp;
  return this;
};

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.apiRequestKeys.short_code_id] = short_code_id;
  return this;
};

ConfirmOrderApi.prototype.setPrice = function(price) {
  this.data[this.apiRequestKeys.price] = price;
  return this;
};

GetAllUsersApi.prototype = new ScopesApi();
GetAllUsersApi.prototype.constructor = GetAllUsersApi;

function GetAllUsersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xD;
}

GetConfirmedOrdersApi.prototype = new ScopesApi();
GetConfirmedOrdersApi.prototype.constructor = GetConfirmedOrdersApi;

function GetConfirmedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x9;
};

GetConfirmedOrdersApi.prototype.getApiKeys = function() {
  return {
    orders: 'orders',
    confirmed_order: {
      id: 'id',
      scopes_count: 'scopes-count',
      start_time: 'start',
      end_time: 'end',
      title: 'title',
      description: 'description',
      time_ordered: 'time-ordered',
      price: 'price',
      short_code: 'short-code'
    },
    short_code: {
      id: 'id',
      code: 'code',
      alias: 'alias'
    }
  };
};

GetOrderPricePolicyApi.prototype = new ScopesApi();
GetOrderPricePolicyApi.prototype.constructor = GetOrderPricePolicyApi;

function GetOrderPricePolicyApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x14;
}

GetStartupDataApi.prototype = new ScopesApi();
GetStartupDataApi.prototype.constructor = GetStartupDataApi;

function GetStartupDataApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x15;
}

GetStartupDataApi.prototype.getApiKeys = function() {
  return {
    first_name: 'first_name',
    last_name: 'last_name',
    email: 'email',
    hourly_price: 'hourly_price',
    short_codes: 'short_codes',
    max_scopes: 'max_scopes',
    max_hours: 'max_hours',
    short_code_fields: {
      alias: 'alias',
      code: 'code',
      id: 'id'
    },
    start_time: 'start-time',
    end_time: 'end-time',
    time: {
      hours: 'hours',
      minutes: 'minutes',
      seconds: 'seconds'
    },
    start_time_interval: 'start-time-interval',
    min_days_in_advance: 'min-days-in-advance',
    max_months_in_advance: 'max-months-in-advance'
  };
};

UpdateConfirmOrderApi.prototype = new ScopesApi();
UpdateConfirmOrderApi.prototype.constructor = UpdateConfirmOrderApi;

function UpdateConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x4;

  // Api request field keys
  this.apiKeys = {
    id: 'cid',
    title: 'title',
    description: 'desc',
    short_code_id: 'code'
  };
}

UpdateConfirmOrderApi.prototype.getApiKeys = function() {
  return this.apiKeys;
};

UpdateConfirmOrderApi.prototype.setConfirmedOrderId = function(id) {
  this.data[this.apiKeys.id] = id;
  return this;
};

UpdateConfirmOrderApi.prototype.setTitle = function(title) {
  this.data[this.apiKeys.title] = title;
  return this;
};

UpdateConfirmOrderApi.prototype.setDescription = function(description) {
  this.data[this.apiKeys.description] = description;
  return this;
};

UpdateConfirmOrderApi.prototype.setShortCodeId = function(id) {
  this.data[this.apiKeys.short_code_id] = id;
  return this;
};

/**
 * ScopesApi
 * - base class for all api calls.
 * @req: all child classes assign 'this.apiType' to corresponding api-type value
 *       in constructor.
 * @req: all child classes assign 'network_module' to 'this.networkModule'
 *       in constructor
 * @override: 
 *        - nonLogicalApiFailureCallback()
 *        - logicalApiFailureCallback()
 *        - successfulApiCallback()
 */
function ScopesApi(network_module) {

  /**
   * Api parameters 
   */
  this.IS_SUCCESSFUL_KEY = "is_successful";
  this.API_TYPE_KEY = "api_type";

  this.networkModule = network_module;
  this.data = {};
  this.isAsync = true;
  this.uploadedFile = null;

  /**
   * isWellFormedApiResponseWrapper()
   * - checks that 'json_response' contains the fields characteristic of all
   *   responses (both successful and failed)
   * @param JSON json_response: response payload
   */
  this.isWellFormedApiResponseWrapper = function(json_response) {
    return this.IS_SUCCESSFUL_KEY in json_response &&
      this.API_TYPE_KEY in json_response;
  };

  /**
   * handleMalformedApiResponseWrapper()
   * - callback for malformed api response
   */
  this.handleMalformedApiResponseWrapper = function(xhttp_response) {
    console.log("API ERROR: Malformed api response", xhttp_response);
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * handleJsonParseError()
   * - callback for json parse error in api call 
   */
  this.handleJsonParseError = function(xhttp_response) {
    console.log("API ERROR: Json parse error");
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * networkSuccessCallbackWrapper()
   * - callback for ScopesNetwork when network call succeeds
   */
  this.networkSuccessCallbackWrapper = function(xhttp_response) {
    var json_response = null

    try {
      // Deserialize json payload
      json_response = JSON.parse(xhttp_response.responseText);

    } catch (parse_exception) {
      // Failed to parse json api response
      this.handleJsonParseError(xhttp_response);
    }

    console.assert(json_response !== null);
     
    // Check that wrapper api keys are present (should be here whether api
    // call succeeded or not...)
    if (!this.isWellFormedApiResponseWrapper(json_response)) {
      this.handleMalformedApiResponseWrapper(xhttp_response);
    }

    // Check if api call succeeded
    if (!json_response[this.IS_SUCCESSFUL_KEY]) {
      // Api logical failure. Should have meaningful api failure code...
      this.logicalApiFailureCallback(json_response);
    }

    // Api call succeeded. Pass off to next handler
    this.successfulApiCallback(json_response);
  };

  /**
   * networkFailureCallbackWrapper()
   * - callback for network failure when making api call
   */
  this.networkFailureCallbackWrapper = function(xhttp_response) {
    console.log("API ERROR: Network failure durng api call");
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

}

ScopesApi.prototype.setIsAsync = function(is_async) {
  this.isAsync = is_async;
  return this;
}

ScopesApi.prototype.setSuccessfulApiCallback = function(callback) {
  this.successfulApiCallback = callback;
  return this;
}

ScopesApi.prototype.setLogicalApiFailureCallback = function(callback) {
  this.logicalApiFailureCallback = callback;
  return this;
}

ScopesApi.prototype.setNonLogicalApiFailureCallback = function(callback) {
  this.nonLogicalApiFailureCallback = callback;
  return this;
}

ScopesApi.prototype.setFile = function(file) {
  this.uploadedFile = file;
  return this;
}

ScopesApi.prototype.send = function() {
  return this.networkModule.request(
    this.apiType,
    this.data,
    this.isAsync,
    this.networkSuccessCallbackWrapper,
    this.networkFailureCallbackWrapper,
    this.uploadedFile,
    this
  );    
}

var ScopesNetwork = (function() {
  
  var ENDPOINT_PATH = "hhvm/endpoints/endpoint.hh";

  var API_TYPE_KEY = "api_type";

  var PAYLOAD_KEY = "payload";

  var VIDEO_UPLOAD_KEY = "video";

  var HTTP_REQUEST_TYPE = "POST";

  var CONTENT_TYPE_KEY = "Content-Type";

  var WWW_FORM_URLENCODED_CONTENT_TYPE = "application/x-www-form-urlencoded";

  var PARAMETER_ASSIGNMENT_TOKEN = "=";

  var PARAMETER_SEPARATOR_TOKEN = "&";

  return {
    /**
     * request()
     * @param int api_type: index of specified api 
     * @param array<string, mixed> payload_fields: payload parameters
     * @param bool is_async: is request synchronous
     * @param function(XMLHttpRequest xhttp) network_success_callback: callback function for when request finishes successfully
     * @param function(XMLHttpRequest xhttp) network_failure_callback: callback function for when request finishes with failure
     * @param File upload_file: optional file upload parameter
     */
    request: function(
     api_type,
     payload_fields,
     is_async,
     network_success_callback,
     network_failure_callback,
     upload_file,
     scopes_api_context
   ) {
      var xhttp = new XMLHttpRequest(); 
      
      // Bind callbacks
      if (is_async) {
        xhttp.onreadystatechange = function() {
          if (xhttp.readyState == 4) {
            if (xhttp.status == 200) {
              scopes_api_context.networkSuccessCallbackWrapper(xhttp); 
            } else {
              scopes_api_context.networkFailureCallbackWrapper(xhttp);
            }
          }
        };
      }

      // Bind http destination and request type
      xhttp.open(
        HTTP_REQUEST_TYPE,
        ENDPOINT_PATH,
        is_async
      );

      // Assemble payload
      var serialized_payload = JSON.stringify(payload_fields);

      var form_data = new FormData();
      
      if (upload_file != null) {
        form_data.append(VIDEO_UPLOAD_KEY, upload_file);
        console.log(VIDEO_UPLOAD_KEY);
        console.log(upload_file);
      }

      form_data.append(API_TYPE_KEY, api_type);
      form_data.append(PAYLOAD_KEY, serialized_payload);

      // Execute request 
      xhttp.send(form_data);

      if (!is_async) {
        return xhttp.responseText;
      }
    }  
  }
}());

var MyExperimentDescriptionPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-description-template'; 

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-description-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Attach event listeners
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
};

var MyExperimentFrontPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-front-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-front-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Dom node info
   */
  var experimentStatusValueNode = {
    className: 'experiment-status-value',
    node: null
  };

  var startTimeValueNode = {
    className: 'start-time-value',
    node: null
  };

  var experimentDurationValueNode = {
    className: 'experiment-duration-value',
    node: null
  };

  var scopesCountValueNode = {
    className: 'scopes-count-value',
    node: null
  };

  var paymentStatusValueNode = {
    className: 'payment-status-value',
    node: null
  };

  var experimentPriceValueNode = {
    className: 'experiment-price-value',
    node: null
  };

  var shortCodeValueNode = {
    className: 'short-code-value',
    node: null
  };

  /**
   * Private functions
   */
  var createExperimentStartTimeString = function(start_time) {
    var start_time_str = Utils.getShortMonthName(start_time.getMonth());
    start_time_str += " " + start_time.getDate();
    start_time_str += ", " + start_time.getFullYear();
    start_time_str += " @ " + Utils.toHoursAndMinutesString(start_time);
    return start_time_str;
  };

  var bindNodes = function() {
    // Bind dom node info    
    Utils.bindNodeInfo(rootNode, experimentStatusValueNode); 
    Utils.bindNodeInfo(rootNode, startTimeValueNode); 
    Utils.bindNodeInfo(rootNode, experimentDurationValueNode); 
    Utils.bindNodeInfo(rootNode, scopesCountValueNode); 
    Utils.bindNodeInfo(rootNode, paymentStatusValueNode); 
    Utils.bindNodeInfo(rootNode, experimentPriceValueNode); 
    Utils.bindNodeInfo(rootNode, shortCodeValueNode); 
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };

  // Setters
  this.setExperimentStatus = function(experiment_status) {
    experimentStatusValueNode.node.innerHTML = experiment_status;
  };

  this.setStartTime = function(start_time) {
    startTimeValueNode.node.innerHTML = createExperimentStartTimeString(start_time);
  };

  this.setExperimentDuration = function(duration) {
    experimentDurationValueNode.node.innerHTML = duration.toString() + " hr";
  };

  this.setScopesCount = function(count) {
    scopesCountValueNode.node.innerHTML = count;


    var price = count * 20;
    experimentPriceValueNode.node.innerHTML = "$" + Utils.makePriceString(price);
  };

  this.setPaymentStatus = function(payment_status) {
    paymentStatusValueNode.node.innerHTML = payment_status;
  };

  this.setExperimentPrice = function(price) {
    experimentPriceValueNode.node.innerHTML = price;
  };

  this.setShortCode = function(short_code) {
    shortCodeValueNode.node.innerHTML = short_code;
  };
};

var MyExperimentMonitoringPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-monitor-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-monitor-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
};

var MyExperimentRecordingPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-recording-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-recording-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Dom info
   */
  var videoNode = {
    className: 'experiment-recording',
    node: null
  };

  var absentVideoMessageNode = {
    className: 'absent-video-message',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, videoNode);
    Utils.bindNodeInfo(rootNode, absentVideoMessageNode);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
  
  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.showVideo = function() {
    Utils.hideNode(absentVideoMessageNode.node);
    Utils.showNode(videoNode.node);
  };

  this.showAbsentVideoMessage = function() {
    Utils.hideNode(videoNode.node);
    Utils.showNode(absentVideoMessageNode.node);
  };
};

var CenterPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template node id
   */
  var TEMPLATE_ID = 'center-page-template';

  /**
   * Root node class name
   */
  var ROOT_NODE_CLASS = 'center-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var rootNode = null;

  var currentPageView = null;

  var newExperimentPageView = null;
  var myExperimentsPageView = null;
  var feedbackPageView = null;
  var technicianPageView = null;

  /**
   * Dom nodes
   */
  var pageTitleNode = {
    className: 'title-label',
    node: null
  };

  var centerPanelPageContainerNode = {
    className: 'page-container',
    node: null
  };

  var adminButtonContainerNode = {
    className: 'admin-btn-container',
    node: null
  };

  /**
   * Private functions
   */

  var initNewExperimentPageView = function() {
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    ); 
    newExperimentPageView.init();
  };

  var initMyExperimentsPageView = function() {
    myExperimentsPageView = new MyExperimentsPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );
    myExperimentsPageView.init();
  };

  var initFeedbackPageView = function() {
    feedbackPageView = new FeedbackPage(
      templateStore,
      centerPanelPageContainerNode.node
    );
    feedbackPageView.init();
  };

  var initTechnicianPageView = function() {
    technicianPageView = new TechnicianPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );
    technicianPageView.init();
  };

  var initPages = function() {
    initNewExperimentPageView(); 
    initMyExperimentsPageView();
    initFeedbackPageView();
    initTechnicianPageView();
  };

  var bindNodes = function() {
    // Bind page nodes
    Utils.bindNodeInfo(rootNode, pageTitleNode);
    Utils.bindNodeInfo(rootNode, adminButtonContainerNode);
    Utils.bindNodeInfo(rootNode, centerPanelPageContainerNode);

  };

  var changePage = function(next_page_view) {
    console.assert(next_page_view != null);

    // Hide current page
    if (currentPageView != null) {
      currentPageView.hide();
    }

    // Show next page and update title
    currentPageView = next_page_view;
    pageTitleNode.node.innerHTML = currentPageView.getTitle();
    currentPageView.show();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document and initialize
    // root DOM element
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_NODE_CLASS
    );

    // Bind ui elements and attach event listeners
    bindNodes();
    
    // Initialize pages
    initPages();

    return this;
  };

  /**
   * Functions for showing main pages
   */
  this.showNewExperimentPage = function() {
    changePage(newExperimentPageView);       
  };

  this.showMyExperimentsPage = function() {
    changePage(myExperimentsPageView);       
  };

  this.showFeedbackPage = function() {
    changePage(feedbackPageView);       
  };

  this.showTechnicianPage = function() {
    changePage(technicianPageView);       
  };

  this.getNewExperimentPageView = function() {
    return newExperimentPageView;
  };

  this.getMyExperimentsPageView = function() {
    return myExperimentsPageView;
  };

  this.getTechnicianPageView = function() {
    return technicianPageView;
  };

  this.getFeedbackPageView = function() {
    return feedbackPageView;
  };
};

function Calendar(
  template_store,
  calendar_id,
  disallowed_week_days,
  irregular_disallowed_days,
  forward_month_limit,
  min_num_days_in_advance
) {

  /**
   * Date style tokens
   */
  var SHORT_DOW_ABBREVIATION_TOKEN = '.';
  var DOM_DELIMITER = ',';

  /**
   * Template name constants
   */
  var TEMPLATE_ID = '#calendar-template';

  /**
   * Html class names
   */
  var DATE_CLASS = 'date';
  var UNSELECTABLE_DATE_CLASS = 'unselectable-date';
  var SELECTABLE_DATE_CLASS = 'selectable-date';
  var DATE_LABEL_CLASS = 'date-label';
  var WEEK_CLASS = 'week';

  /**
   * Html attribute names
   */
  var SELECTED_DATE_ATTR = 'selected-date';
  var DISABLED_MONTH_NAV_ATTR = 'disabled';
  var HIDDEN_ATTR = 'hidden';
  var CLOSED_ATTR = 'closed';

  /**
   * Class constants
   */
  var JS_YEAR_OFFSET = 1900;
  var JS_DATE_LOCALE = 'en-us';

  var SHORT_DAY_OF_THE_WEEK_NAMES = [
    'Sun',
    'Mon',
    'Tue',
    'Wed',
    'Thu',
    'Fri',
    'Sat'
  ];

  var LONG_DAY_OF_THE_WEEK_NAMES = [
    'Sunday',
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday'
  ];
  
  var LONG_MONTH_NAMES = [
    'January',
    'February',
    'March',
    'April',
    'May',
    'June',
    'July',
    'August',
    'September',
    'October',
    'November',
    'December'
  ];

  var SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  // Js utility pointers
  var that = this;
  var jsDate = null;

  // Calendar State
  var templateStore = template_store;
  var minNumDaysInAdvance = min_num_days_in_advance;
  var disallowedWeekDays = disallowed_week_days;
  var irregularDisallowedDays = irregular_disallowed_days;
  var isEnabled = true;
  var isVisible = false;
  
  var monthDisplacement = 0;
  var maxMonthDisplacement = forward_month_limit;

  /**
   * Stores information for the current date
   */
  var currentDateObj = {
    date: null,
    month: null,
    year: null
  };

  /**
   * Stores information for the current *selected* date
   */
  var selectedDateObj = {
    date: null,
    month: null,
    year: null,
    selectedDateNode: null
  };

  /**
   * Stores information for the month that is currently displayed
   */
  var calendarMonthObj = {
    month: null,
    year: null,
    startingDayOfTheWeek: null
  };

  /**
   * Dom node info
   */
  // Calendar root
  var calendarRootNodeInfo = {
    id: calendar_id,
    node: null
  };

  var calendarWrapperNodeInfo = {
    className: 'calendar-wrapper',
    node: null
  };

  var selectedMonthLabelNodeInfo = {
    className: 'selected-month-label',
    node: null
  };
  
  var selectedDomLabelNodeInfo = {
    className: 'selected-dom-label',
    node: null
  };

  var selectedYearLabelNodeInfo = {
    className: 'selected-year-label',
    node: null
  };

  // Month nav node info
  var monthNavDisplayNodeInfo = {
    className: 'month-label',
    node: null
  };

  var decrementMonthNavNodeInfo = {
    className: 'decrement-month-container',
    node: null
  };
  
  var incrementMonthNavNodeInfo = {
    className: 'increment-month-container',
    node: null
  };
  
  // Selectable dates node info
  var selectableDaysContainerNodeInfo = {
    className: 'selectable-dates-container',
    node: null
  };

  var selectedDateDisplayContainer = {
    className: 'selected-date-display-container',
    node: null
  };

  var calendarMainContainerNodeInfo = {
    className: 'calendar-main-container',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * fetchClassBoundDomNode()
   * - fetch the dom node indicated by the provided class-name
   * @param Object node_info: datastructure for the node (see above for example)
   */
  function fetchClassBoundDomNode(node_info) {
    elements = calendarRootNodeInfo.node.getElementsByClassName(node_info.className);
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  /**
   * initInternalCalendarNodes()
   * - initialize dom node pointers
   * - binds event listeners
   */
  function initInternalCalendarNodes() {
    // Bind all nodes and init their event listeners
    fetchClassBoundDomNode(calendarWrapperNodeInfo);

    // Selected display date nodes
    fetchClassBoundDomNode(selectedYearLabelNodeInfo);
    fetchClassBoundDomNode(selectedDomLabelNodeInfo);
    fetchClassBoundDomNode(selectedMonthLabelNodeInfo);

    fetchClassBoundDomNode(calendarMainContainerNodeInfo);
    fetchClassBoundDomNode(selectedDateDisplayContainer);

    selectedDateDisplayContainer.node.onclick = function(event) {
      if (isVisible) {
        hideCalendar();
      } else {
        showCalendar();
      }
    };

    // Month nav nodes
    fetchClassBoundDomNode(monthNavDisplayNodeInfo);
    fetchClassBoundDomNode(decrementMonthNavNodeInfo);
    fetchClassBoundDomNode(incrementMonthNavNodeInfo);
    
    // Month navigation button event listeners
    decrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(false); 
    };
    
    incrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(true); 
    };

    // Selectable dates node info
    fetchClassBoundDomNode(selectableDaysContainerNodeInfo);

    // Selectable dates event listener
    selectableDaysContainerNodeInfo.node.onclick = function(event) {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }

      // Search event propagation list to find selectable-date node
      var date = null;
      for (var i = 0; i < event.path.length; ++i) {
        if (Utils.hasClass(SELECTABLE_DATE_CLASS, event.path[i])) {
          date = event.path[i];
          break;
        } 
      }

      // Kill event if a selectable-date wasn't clicked
      if (date == null) {
        return;
      }

      // Kill event here b/c this date is already selected!
      if (date.hasAttribute(SELECTED_DATE_ATTR)) {
        return;
      }

      // Extract the numerical date
      console.assert(date.childNodes.length == 1);
      var label = date.childNodes[0];
      console.assert(Utils.hasClass(DATE_LABEL_CLASS, label));

      var date_idx = parseInt(label.innerHTML);

      // Clear current selected date
      if (selectedDateObj.selectedDateNode != null) {
        selectedDateObj.selectedDateNode.removeAttribute(SELECTED_DATE_ATTR);
      } 

      // Render current selected date
      date.setAttribute(SELECTED_DATE_ATTR, '');
      selectedDateObj.selectedDateNode = date;
      selectedDateObj.date = date_idx;

      // Update selected date top-banner display
      updateSelectedDowDisplay(date_idx);
      updateSelectedMonthDisplay(calendarMonthObj.month);

      // Hide calendar body
      hideCalendar();
    };

    // Hide calendar if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the screen, so don't hide!
        if (node.id == calendarRootNodeInfo.node.id) {
          return;
        }
      }

      // User clicked off the calendar, so hide it!
      hideCalendar();
    });
  };

  function hideCalendar() {
    isVisible = false;  
    calendarMainContainerNodeInfo.node.setAttribute(HIDDEN_ATTR, ''); 
    calendarWrapperNodeInfo.node.setAttribute(CLOSED_ATTR, '');
  };

  function showCalendar() {
    isVisible = true; 
    calendarMainContainerNodeInfo.node.removeAttribute(HIDDEN_ATTR); 
    calendarWrapperNodeInfo.node.removeAttribute(CLOSED_ATTR);
  };

  /**
   * shiftMonth()
   * - increment/decrement month and update ui
   * @param: bool is_increment: true iff incrementing month
   */
  function shiftMonth(is_increment) {
    // Kill event if increments month past forward limit
    if (is_increment && monthDisplacement == maxMonthDisplacement) {
      return;
    }

    // Kill event if decrements month past current one
    if (!is_increment && monthDisplacement == 0) {
      return;
    }

    if (is_increment) {
      ++monthDisplacement; 
      if (monthDisplacement == maxMonthDisplacement) {
        // Update forward month-nav-arrow to signal that it can't go forward anymore 
        incrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');  
        decrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    } else {
      --monthDisplacement;
      if (monthDisplacement == 0) {
        // Update backward month-nav-arrow to signal that it can't go backward anymore 
        decrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');
        incrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    }

    // Render new grid for month
    var month_offset = monthDisplacement + selectedDateObj.month;
    var year_offset = Math.floor(month_offset / 12);
    var next_year = year_offset + selectedDateObj.year;
    var next_month = month_offset % 12;

    // Update internal calendar state
    calendarMonthObj.month = next_month;
    calendarMonthObj.year = next_year;
    var starting_day_of_week_obj = new Date(next_year, next_month, 1);
    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();

    updateMonthDisplayGrid(next_month, next_year);
    updateCurrentMonthDisplay(next_month);
  };

  function initDate() {
    // Capture today's date and initialize calendar state
    var current_date_js_obj = new Date(); 
    
    // Adjust first available day with min-num-days-in-advance offset
    current_date_js_obj = new Date(
      current_date_js_obj.getUTCFullYear(),
      current_date_js_obj.getMonth(),
      current_date_js_obj.getDate() + minNumDaysInAdvance
    );

    // Set current date
    currentDateObj.date = current_date_js_obj.getUTCDate();
    currentDateObj.month = current_date_js_obj.getUTCMonth();
    currentDateObj.year = current_date_js_obj.getUTCFullYear();
   
    // Initialize selected date to current date
    selectedDateObj.date = current_date_js_obj.getUTCDate();
    selectedDateObj.month = current_date_js_obj.getUTCMonth();
    selectedDateObj.year = current_date_js_obj.getUTCFullYear();

    // Initialize calendar grid state to current month
    calendarMonthObj.month = selectedDateObj.month;
    calendarMonthObj.year = selectedDateObj.year;

    // Determine starting day of the week for the selected date
    var starting_day_of_week_obj = new Date(
      calendarMonthObj.year,    
      calendarMonthObj.month,    
      1
    );

    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();
  };

  /**
   * updateSelectedDowDisplay()
   * - update the selected-date banner
   * @param Obj selected_date: {int date, int month, int year}
   */
  function updateSelectedDowDisplay(date) {
    // var date_label = computeSelectedDowLabel(date);
    // selectedDowLabelNodeInfo.node.innerHTML = date_label;
    selectedDomLabelNodeInfo.node.innerHTML = date + DOM_DELIMITER;
  };

  function updateSelectedMonthDisplay(month) {
    var month_label = computeSelectedMonthLabel(month);
    selectedMonthLabelNodeInfo.node.innerHTML = month_label;
  };

  function updateCurrentMonthDisplay(month) {
    var month_label = computeCurrentSelectedMonthLabel(month);
    monthNavDisplayNodeInfo.node.innerHTML = month_label; 
  };

  function updateSelectedYearDisplayLabel(year) {
    var year_label = computeSelectedYearLabel(year); 
    selectedYearLabelNodeInfo.node.innerHTML = year_label;
  };

  function generateDateNode() {
    var date_node = document.createElement('div');
    date_node.className = DATE_CLASS;
    return date_node;
  };

  function generateBlankDateNode() {
    return generateDateNode();
  };

  /**
   * generateDateLabelNode()
   * - dynamically generate html node for displaying an individual
   *   date in the calendar
   * @param int date: day of the month 
   */
  function generateDateLabelNode(date) {
    var date_label_node = document.createElement('div');
    var label = document.createElement('span');
    label.className = DATE_LABEL_CLASS;
    label.innerHTML = date;
    date_label_node.appendChild(label);
    return date_label_node;
  };

  /**
   * generateSelectableDateNode()
   * - dynamically generates html node representing date
   *   within this month that can be selected.
   */
  function generateSelectableDateNode(date) {
    var selectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = SELECTABLE_DATE_CLASS;
    selectable_date_node.appendChild(date_label_node);
    return selectable_date_node; 
  };

  /**
   * generateUnselectableDateNode()
   * - dynamically generates html node representing
   *   date wthin this month that can't be selected, 
   *   e.g. date has already passed or date is already
   *   booked
   */
  function generateUnselectableDateNode(date) {
    var unselectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = UNSELECTABLE_DATE_CLASS;
    unselectable_date_node.appendChild(date_label_node);
    return unselectable_date_node; 
  };

  /**
   * generateWeekNode()
   * - dynamically generate the node for 1 row in the calendar
   */
  function generateWeekNode() {
    var week_node = document.createElement('div');
    week_node.className = WEEK_CLASS;
    return week_node;
  };

  /**
   * updateMonthDisplayGrid()
   * - dynamically generate date cells for this month
   * @param int month: [0, 11] indicating month index
   * @param int year: any year
   */
  function updateMonthDisplayGrid(month, year) {
    // Clear existing week-nodes within the calendar grid
    while (selectableDaysContainerNodeInfo.node.hasChildNodes()) {
      selectableDaysContainerNodeInfo.node.removeChild(selectableDaysContainerNodeInfo.node.lastChild);
    }

    // Get starting day-of-week idx
    var new_date = new Date(year, month);
    var starting_day_idx = new_date.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0); // hacky :/
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate dynamic html nodes for days in last week of previous month that appear
    // in first week of this month, e.g. last few days
    var current_week = generateWeekNode();
    selectableDaysContainerNodeInfo.node.appendChild(current_week);

    for (var i = 0; i < starting_day_idx; ++i) {
      var blank_node = generateBlankDateNode();
      current_week.appendChild(blank_node);
    }
    
    // Generate dynamic html nodes for displaying selectable days in month
    for (var i = 1; i <= num_days_in_month; ++i) { // fewer ops with these loop conditions
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = generateWeekNode();
        selectableDaysContainerNodeInfo.node.appendChild(current_week);
      }

      // Create date node: date node is 'unselectable' iff it is on either
      // of the 'disallowed' lists or if it occurs before the specified
      // min-number-days-in-advance threshold
      var date_node = (disallowedWeekDays.has(current_week.childNodes.length)) || 
          (month == currentDateObj.month && i < currentDateObj.date)
        ? generateUnselectableDateNode(i)
        : generateSelectableDateNode(i);

      current_week.appendChild(date_node);
    }
  }

  /**
   * initDisplay()
   * - initialize calendar display
   * - generate and bind dynamic nodes
   * @pre-condition: 'selectedDateObj' must be initialized to current date
   */
  function initDisplay() {
    // Render grid of dates
    updateMonthDisplayGrid(selectedDateObj.month, selectedDateObj.year);

    // Render banner date label for current date
    updateSelectedDowDisplay(selectedDateObj.date);

    // Render banner month label for current date
    updateSelectedMonthDisplay(selectedDateObj.month);

    // Render banner year label for current date 
    updateSelectedYearDisplayLabel(selectedDateObj.year);

    // Render calendar month label for grid
    updateCurrentMonthDisplay(selectedDateObj.month);

    // Render or hide main calendar content on startup
    if (isVisible) {
      showCalendar();
    } else {
      hideCalendar();
    }
  };

  /**
   * computeCurrentSelectedMonthLabel()
   * - return the month label for the calendar title itself (not the banner)
   * @param int month: [0-11] month index
   */
  function computeCurrentSelectedMonthLabel(month) {
    return LONG_MONTH_NAMES[month]; 
  };

  /**
   * computeSelectedDowLabel()
   * - return date label: '<day of the week>, <numerical day of the month>'
   * @param int date: numerical day of the month
   */
  function computeSelectedDowLabel(date) {
    var day_of_week_idx = (date + calendarMonthObj.startingDayOfTheWeek - 1) % 7;
    return SHORT_DAY_OF_THE_WEEK_NAMES[day_of_week_idx] + SHORT_DOW_ABBREVIATION_TOKEN;
  };

  /**
   * computeSelectedMonthLabel()
   * - return short month label for top-banner displaying selected date
   * @param int month_idx: [0-11] month index of selected month
   */
  function computeSelectedMonthLabel(month_idx) {
    return SHORT_MONTH_NAMES[parseInt(month_idx)]; 
  };

  /**
   * computeSelectedYearLabel()
   * - return year label for top-banner displaying selected date
   * @param int year: year index (UTC)
   */
  function computeSelectedYearLabel(year) {
    // Must have valid date
    return year;
  };

  /**
   * setDate()
   * - set date state and update ui
   * @pre-condition: params must correspond to valid date
   * @param int day: day of the month index
   * @param int month: month index
   * @param int year: year index
   */
  function setDate(day, month, year) {
    // TODO: write api for setting date externally 
  };

  /**
   * synthesizeCalendarTemplate()
   * - copy calendar template and insert into main dom tree
   * @pre-condition: 'calendarRootNodeInfo' must be initialized
   */
  function synthesizeCalendarTemplate() {
    // Bind calendar dom template 
    var calendar_template = templateStore.import.querySelector(TEMPLATE_ID);
    var calendar_clone = document.importNode(calendar_template.content, true);
    calendarRootNodeInfo.node.appendChild(calendar_clone);
  };

  function setInitialStateInternal() {
    // Cache today's date
    initDate();

    // Load ui
    initDisplay();
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - bind all nodes, initialize state and ui
   * - bind event listeners
   */
  this.init = function() {
    // Initialize top-level calendar node (we're going to copy the template into this!)
    calendarRootNodeInfo.node = document.getElementById(calendarRootNodeInfo.id);

    // Copy the template and insert into root node
    synthesizeCalendarTemplate();

    // Initialize dom nodes internal to the calendar object
    initInternalCalendarNodes();

    // Initialize and configure calendar date
    setInitialStateInternal();
  };

  /**
   * disable()
   * - disable event listeners and render 'disabled' ui
   */
  this.disable = function() {
    isEnabled = false;
  };

  /**
   * enable()
   * - enable event listeners and render 'enabled' ui
   */
  this.enable = function() {
    isEnabled = true;
  };

  /**
   * getSelectedDate()
   * - return selected date
   */
  this.getSelectedDate = function() {
    return {
      year: selectedDateObj.year,
      month: selectedDateObj.month + 1, // b/c month is 0 indexed internally
      date: selectedDateObj.date
    };
  };

  /**
   * setInitialState()
   * - select initial date
   */
  this.setInitialState = function() {
    setInitialStateInternal();
  };
};

var DatePickerView = function(
  template_store,
  parent_node
) {

  /**
   * Template ids
   */
  var MAIN_TEMPLATE_ID = 'calendar-template';
  var WEEK_TEMPLATE_ID = 'date-picker-week-template';
  var DATE_TEMPLATE_ID = 'date-picker-date-template';

  /**
   * Class names
   */
  var ROOT_WRAPPER_CLASS = 'calendar-wrapper';
  var WEEK_WRAPPER_CLASS = 'week-wrapper';
  var DATE_WRAPPER_CLASS = 'date-wrapper';
  var DATE_LABEL_CLASS = 'date-label';

  /**
   * Attribute names
   */
  var UNSELECTABLE_DATE_ATTR = 'unselectable-date';
  var CLOSED_DATE_PICKER_ATTR = 'closed-calendar';
  var DISABLED_MONTH_NAV_ATTR = 'disabled-month-nav';

  /**
   * Month names
   */
  var SHORT_MONTH_NAMES = [
    'Jan.',
    'Feb.',
    'Mar.',
    'Apr.',
    'May',
    'Jun.',
    'Jul.',
    'Aug.',
    'Sep.',
    'Oct.',
    'Nov.',
    'Dec.'
  ];

  /**
   * Ui tokens
   */
  DATE_DELIMITER = ',';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var datePickerRootNode = null;

  // Ui state
  var isDatePickerClosed = true;
  var isActiveMonthDecrementNavButton = null;
  var isActiveMonthIncrementNavButton = null;

  var _this = this;

  // Callbacks
  var dateSelectionCallbacks = [];
  var monthNavigationCallbacks = [];

  /**
   * Dom nodes
   */
  // Top banner elements
  var selectedDateDisplayContainerNodeInfo = {
    className: 'selected-date-display-container',
    node: null
  };

  var selectedMonthLabelNodeInfo = {
    className: 'selected-month-label',
    node: null
  };
  
  var selectedDateLabelNodeInfo = {
    className: 'selected-dom-label',
    node: null
  };

  var selectedYearLabelNodeInfo = {
    className: 'selected-year-label',
    node: null
  };

  // Month nav node info (current month & left/right month controls)
  var monthNavDisplayNodeInfo = {
    className: 'month-label',
    node: null
  };

  var decrementMonthNavNodeInfo = {
    className: 'decrement-month-container',
    node: null
  };
  
  var incrementMonthNavNodeInfo = {
    className: 'increment-month-container',
    node: null
  };
  
  // Selectable dates node info
  var weeksContainerNodeInfo = {
    className: 'weeks-container',
    node: null
  };

  var calendarMainContainerNodeInfo = {
    className: 'calendar-main-container',
    node: null
  };

  /**
   * Private functions
   */

  var open = function() {
    isDatePickerClosed = false;
    selectedDateDisplayContainerNodeInfo.node.removeAttribute(CLOSED_DATE_PICKER_ATTR); 
    Utils.showNode(calendarMainContainerNodeInfo.node);
  };

  var close = function() {
    isDatePickerClosed = true;
    selectedDateDisplayContainerNodeInfo.node.setAttribute(CLOSED_DATE_PICKER_ATTR, '');
    Utils.hideNode(calendarMainContainerNodeInfo.node);
  };

  var bindNodes = function() {
    // Top banner nodes
    Utils.bindNodeInfo(parentNode, selectedDateDisplayContainerNodeInfo);
    Utils.bindNodeInfo(parentNode, selectedMonthLabelNodeInfo);
    Utils.bindNodeInfo(parentNode, selectedDateLabelNodeInfo);
    Utils.bindNodeInfo(parentNode, selectedYearLabelNodeInfo);


    // Month nav/display
    Utils.bindNodeInfo(parentNode, monthNavDisplayNodeInfo);
    Utils.bindNodeInfo(parentNode, decrementMonthNavNodeInfo);
    Utils.bindNodeInfo(parentNode, incrementMonthNavNodeInfo);

    // Selectable dates
    Utils.bindNodeInfo(parentNode, weeksContainerNodeInfo);
    Utils.bindNodeInfo(parentNode, calendarMainContainerNodeInfo);
    
    /**
     * Bind event listeners
     */
    // Hide/close banner
    selectedDateDisplayContainerNodeInfo.node.onclick = function() {
      if (isDatePickerClosed) {
        open(); 
      } else {
        close(); 
      }
    };

    // On ui click
    datePickerRootNode.onclick = function(event) {
      // Crawl node hierarchy
      for (var i = 0; i < event.path.length; ++i) {
        var node = event.path[i]; 
        
        // Event: date selection click
        // 1. Click has to be on date-wrapper
        // 2. Date-wrapper can't be marked 'unselectable'
        if (Utils.hasClass(DATE_WRAPPER_CLASS, node) && !node.hasAttribute(UNSELECTABLE_DATE_ATTR)) {
          // Extract date idx 
          var date_label_list = node.getElementsByClassName(DATE_LABEL_CLASS);
          console.assert(date_label_list.length == 1);

          var date_label = date_label_list[0];
          var date_idx = date_label.innerHTML;

          // Invok registered callbacks
          for (var j = 0; j < dateSelectionCallbacks.length; ++j) {
            var callback = dateSelectionCallbacks[j];   
            callback(_this, date_idx);
          }

          // Close date-picker
          close();
        }

        // Event: left month navigation
        if (node == decrementMonthNavNodeInfo.node) {
          _this.decrementMonth(); 
        }

        // Event: right month navigation
        if (node == incrementMonthNavNodeInfo.node) {
          _this.incrementMonth();
        }
      }
    };

    // Close date-picker if user clicks off the ui element
    Utils.bindClickBeyondNode(datePickerRootNode, close); 
  };

  this.refreshCalendar = function(
    month,
    year,
    min_advance_day_count,
    invalid_week_days,
    invalid_dates
  ) {
    // Remove previous date nodes
    Utils.removeDomChildren(weeksContainerNodeInfo.node); 

    // Update viewed month name
    monthNavDisplayNodeInfo.node.innerHTML = SHORT_MONTH_NAMES[month];

    // Render calendar for specified month/year
    // Get starting day-of-week idx
    var starting_day_obj = new Date(year, month);  
    var starting_day_idx = starting_day_obj.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0);
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate blank date nodes for days in final week of previous
    // month that appear in the first week of this calendar month
    var current_week = makeWeekNode();
    var day_count = 0;

    for (var i = 0; i < starting_day_idx; ++i) {
      var date = makeDateNode(current_week);
      date.setAttribute(UNSELECTABLE_DATE_ATTR, '');
      ++day_count;
    }

    // Determine which date is the first selectable one
    var first_selectable_date = new Date();
    first_selectable_date.setDate(
      first_selectable_date.getDate() + min_advance_day_count 
    );

    // Generate nodes for displaying selectable days
    for (var i = 1; i <= num_days_in_month; ++i) {
      // Insert rows for calendar weeks
      if (day_count == 7) {
        current_week = makeWeekNode();
        day_count = 0;
      }

      // Initialize date and insert into week
      var date = makeDateNode(current_week);

      // Create date node. Node is 'unselectable' iff it is...
      // 1. On either of the 'disallowed' lists *OR*
      // 2. It falls too close to the current date 
      var validation_check_date = new Date(year, month, i);

      if (
          Utils.compareDates(first_selectable_date, validation_check_date) > 0 ||
          isInvalidDate(validation_check_date, invalid_week_days, invalid_dates)
      ) {
        date.setAttribute(UNSELECTABLE_DATE_ATTR, '');     
      } 
      
      var date_labels = date.getElementsByClassName(DATE_LABEL_CLASS);
      console.assert(date_labels.length == 1);
      date_labels[0].innerHTML = i;

      ++day_count;
    }
  };

  var isInvalidDate = function(date, invalid_week_days, invalid_dates) {
    // Check if this date's 'day of the week' is marked invalid
    if (Utils.contains(date.getDay(), invalid_week_days)) {
      return true;
    }

    // Check if this date is one of the irregular dates marked invalid
    for (var i = 0; i < invalid_dates.length; ++i) {
      var invalid_date = invalid_dates[i];
      if (Utils.compareDates(date, invalid_date) == 0) {
        return true;
      }
    }

    return false;
  };

  var makeWeekNode = function() {
    return Utils.synthesizeTemplateIntoList(
      templateStore,
      WEEK_TEMPLATE_ID,
      weeksContainerNodeInfo.node,
      WEEK_WRAPPER_CLASS
    );
  };

  var makeDateNode = function(week_node) {
    return Utils.synthesizeTemplateIntoList(
      templateStore,
      DATE_TEMPLATE_ID,
      week_node,
      DATE_WRAPPER_CLASS
    );
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document
    datePickerRootNode = Utils.synthesizeTemplate(
      templateStore,
      MAIN_TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    ); 

    // Bind nodes
    bindNodes();

    // Initialize month-nav arrow states
    this.disableMonthDecrementNavButton(); 
    this.enableMonthIncrementNavButton();
  };

  this.bindDateSelection = function(callback) {
    dateSelectionCallbacks.push(callback);
    return this;
  };

  this.bindMonthNavigation = function(callback) {
    monthNavigationCallbacks.push(callback);
    return this;
  };

  this.decrementMonth = function() {
    monthNavigationCallbacks.forEach(function(callback) {
      callback(this, true);
    }, this);  
  };

  this.incrementMonth = function() {
    monthNavigationCallbacks.forEach(function(callback) {
      callback(this, false);
    }, this);  
  };
  
  this.disableMonthIncrementNavButton = function() {
    this.toggleMonthIncrementNavButtonActiveState(false); 
  };

  this.enableMonthIncrementNavButton = function() {
    this.toggleMonthIncrementNavButtonActiveState(true); 
  };

  this.toggleMonthIncrementNavButtonActiveState = function(is_active) {
    isActiveMonthIncrementNavButton = is_active; 

    // Update ui
    if (is_active) {
      incrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
    } else {
      incrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');
    }
  };

  this.disableMonthDecrementNavButton = function() {
    this.toggleMonthDecrementNavButtonActiveState(false); 
  };

  this.enableMonthDecrementNavButton = function() {
    this.toggleMonthDecrementNavButtonActiveState(true); 
  };

  this.toggleMonthDecrementNavButtonActiveState = function(is_active) {
    isActiveMonthDecrementNavButton = is_active; 

    // Update ui
    if (is_active) {
      decrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
    } else {
      decrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');
    }
  };
  
  this.setSelectedDate = function(selected_date) {
    selectedDateLabelNodeInfo.node.innerHTML = "" + selected_date + DATE_DELIMITER; 
  };

  this.setSelectedMonth = function(selected_month) {
    selectedMonthLabelNodeInfo.node.innerHTML = SHORT_MONTH_NAMES[selected_month];
  };

  this.setSelectedYear = function(selected_year) {
    selectedYearLabelNodeInfo.node.innerHTML = selected_year;
  };
};

function StaticCalendar(
  template_store,
  parent_node,
  selected_date_timestamp
) {

  /**
   * Template name constants
   */
  var TEMPLATE_ID = '#static-calendar-template';

  /**
   * Html class names
   */
  var DATE_CLASS = 'date';
  var DATE_LABEL_CLASS = 'date-label';
  var WEEK_CLASS = 'week';
  var SELECTABLE_DATE_CLASS = 'selectable-date';
  
  /**
   * Html attribute names
   */
  var SELECTED_DATE_ATTR = 'selected-date';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var selectedDateTimestamp = selected_date_timestamp;
  var staticCalendar = null;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'static-calendar-wrapper',
    node: null
  };

  var selectedDateDisplayNode = {
    className: 'selected-date-label',
    node: null
  };

  var domContainerNode = {
    className: 'dom-container',
    node: null
  }; 

  /**
   * Private functions
   */
  var bindClassBoundNode = function(node_info) {
    elements = parentNode.getElementsByClassName(node_info.className);
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var synthesizeTemplate = function() {
    // Copy and bind template
    var static_calendar_template = templateStore.import.querySelector(TEMPLATE_ID);
    var static_calendar_clone = document.importNode(static_calendar_template.content, true);
    parentNode.appendChild(static_calendar_clone);
  };

  var bindInternalNodes = function() {
    // Bind static html nodes
    bindClassBoundNode(rootNode);
    bindClassBoundNode(selectedDateDisplayNode);
    bindClassBoundNode(domContainerNode);
  };

  var generateDateLabelNode = function(date) {
    var date_label_node = document.createElement('div');
    var label = document.createElement('span');
    label.className = DATE_LABEL_CLASS;
    label.innerHTML = date;
    date_label_node.appendChild(label);
    return date_label_node;
  };

  var generateSelectableDateNode = function(date) {
    var selectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = SELECTABLE_DATE_CLASS;
    selectable_date_node.appendChild(date_label_node);
    return selectable_date_node; 
  };
  
  var generateDateNode = function() {
    var date_node = document.createElement('div');
    date_node.className = DATE_CLASS;
    return date_node;
  };

  var generateBlankDateNode = function() {
    return generateDateNode();
  };
  
  /**
   * generateWeekNode()
   * - dynamically generate the node for 1 row in the calendar
   */
  function generateWeekNode() {
    var week_node = document.createElement('div');
    week_node.className = WEEK_CLASS;
    return week_node;
  };

  /**
   * setMonthDisplayGrid()
   * @param DateObj selected_date: {year, month, date}
   */
  var setMonthDisplayGrid = function(year, month, selected_date) {
    // Clear existing children nodes 
    Utils.removeDomChildren(domContainerNode.node);

    // Assemble dynamic month display grid
    var new_date = new Date(year, month);
    var starting_day_idx = new_date.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0); // hacky :/
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate dynamic html nodes for days in last week of previous month that appear
    // in first week of this month, e.g. last few days
    var current_week = generateWeekNode();
    domContainerNode.node.appendChild(current_week);

    console.log('starting day idx');
    console.log(starting_day_idx);

    for (var i = 0; i < starting_day_idx; ++i) {
      var blank_node = generateBlankDateNode();
      current_week.appendChild(blank_node);
    }
    
    // Generate dynamic html nodes for displaying selectable days in month
    for (var i = 1; i <= num_days_in_month; ++i) { // fewer ops with these loop conditions
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = generateWeekNode();
        domContainerNode.node.appendChild(current_week);
      }
     
      var selectable_date = generateSelectableDateNode(i);

      if (i == selected_date) {
        selectable_date.setAttribute(SELECTED_DATE_ATTR, '');
        console.log(selectable_date);
      }

      current_week.appendChild(selectable_date);
    }
  };

  var initUi = function() {
    // Generate timestamp string and copy into display ui node
    selectedDateDisplayNode.node.innerHTML = Utils.makeDateString(selectedDateTimestamp);

    // Configure dynamic ui nodes
    var js_date = new Date(selectedDateTimestamp);
    setMonthDisplayGrid(
      js_date.getUTCFullYear(),
      js_date.getUTCMonth(),
      js_date.getUTCDate()
    );
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    synthesizeTemplate();
    bindInternalNodes();
    initUi();
  };
};

var DropDownItemView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'dropdown-item-template';

  /**
   * Root wrapper class
   */
  var ROOT_WRAPPER_CLASS = 'dropdown-item-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var dropDownItemRootNode = null;
  var dropDownItemIndex = null;
  var onClickCallbacks = [];

  /**
   * Dom nodes
   */
  var itemLabelNode = {
    className: 'item-label',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind item label node
    itemLabelNode.node = Utils.bindNode(
      dropDownItemRootNode,
      itemLabelNode.className
    );      

    // Configure onclick event listener
    dropDownItemRootNode.onclick = function() {
      onClickCallbacks.forEach(function(callback) {
        callback(dropDownItemIndex); 
      });
    };
  };

  var setLabel = function(label) {
    itemLabelNode.node.innerHTML = label;    
  };

  var setTooltip = function(tooltip) {
    // TODO...
  };

  var bindModel = function(drop_down_item_model) {
    drop_down_item_model
      .bindLabel(setLabel)
      .bindTooltip(setTooltip);
  };

  /**
   * Privileged functions
   */
  this.init = function(index, drop_down_item_model) {
    // Synthesize template into document
    dropDownItemRootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    ); 
    
    dropDownItemIndex = index;

    // Bind nodes and configure event listeners
    bindNodes();

    // Bind model and init ui
    bindModel(drop_down_item_model);

    return this;
  };

  this.bindClick = function(callback) {
    onClickCallbacks.push(callback);
    return this;
  };
};

var DropDownView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'dropdown-picker-template';

  /**
   * Revealed dropdown attribute
   */
  var REVEALED_DROPDOWN_ATTR = 'revealed-dropdown';

  /**
   * Root wrapper class
   */
  var ROOT_WRAPPER_CLASS = 'dropdown-picker-wrapper';

  /**
   * Icon type attribute
   */
  var ICON_TYPE_ATTR = 'icon';

  /**
   * Private vars
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var dropDownRootNode = null;

  var isDropDownOpen = false;
  var dropDownItemViews = [];
  var onClickCallbacks = [];

  var _this = this;

  /**
   * Dom nodes
   */
  var inputFieldWrapperNode = {
    className: 'input-field-wrapper',
    node: null
  };

  var inputFieldLabelNode = {
    className: 'input-field-label',
    node: null
  };

  var dropDownIconNode = {
    className: 'dropdown-icon',
    node: null
  }; 

  var dropDownListNode = {
    className: 'dropdown-list',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Input field wrapper
    inputFieldWrapperNode.node = Utils.bindNode(
      dropDownRootNode,
      inputFieldWrapperNode.className
    );

    // Input field label
    inputFieldLabelNode.node = Utils.bindNode(
      dropDownRootNode,
      inputFieldLabelNode.className
    );

    // Dropdown icon
    dropDownIconNode.node = Utils.bindNode(
      dropDownRootNode,
      dropDownIconNode.className
    );

    // Dropdown list
    dropDownListNode.node = Utils.bindNode(
      dropDownRootNode,
      dropDownListNode.className
    );

    // Attach click event listener
    dropDownRootNode.onclick = function() {
      if (isDropDownOpen) {
        closeDropDown();
      } else {
        openDropDown(); 
      }
    }; 

    // Close dropdown when user clicks away from ui element 
    Utils.bindClickBeyondNode(dropDownRootNode, closeDropDown);
  };

  var closeDropDown = function() {
    isDropDownOpen = false;
    Utils.hideNode(dropDownListNode.node);
    dropDownRootNode.removeAttribute(REVEALED_DROPDOWN_ATTR);
  };

  var openDropDown = function() {
    isDropDownOpen = true;
    Utils.showNode(dropDownListNode.node);
    dropDownRootNode.setAttribute(REVEALED_DROPDOWN_ATTR, '');
  };

  var configureDropDownItems = function(drop_down_data) {
    for (var i = 0; i < drop_down_data.length; ++i) {
      var label = drop_down_data[i]; 
      var drop_down_item_view = new DropDownItemView(
        templateStore,
        dropDownListNode.node
      );

      drop_down_item_view.init(label, i);
      drop_down_item_view.bindClick(invokeOnclickCallbacks);
      dropDownItemViews.push(drop_down_item_view);
    }
  };

  var invokeOnclickCallbacks = function(index) {
    onClickCallbacks.forEach(function(callback) {
      callback(this, index);
    }, _this); 
  };

  var setIcon = function(icon_type) {
    dropDownIconNode.node.setAttribute(ICON_TYPE_ATTR, icon_type); 
  };

  /**
   * Privileged functions 
   */
  this.init = function(icon_type) {
    // Synthesize template into document
    dropDownRootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    );  

    // Bind nodes
    bindNodes();

    // Configure icon
    setIcon(icon_type);
  };

  this.bindClick = function(callback) {
    onClickCallbacks.push(callback);
  };

  this.setSelectedItem = function(drop_down_item) {
    if (drop_down_item != null) {
      inputFieldLabelNode.node.innerHTML = drop_down_item.getLabel();
    }
  };

  // TODO maybe move this to controller
  this.setDropDownItemModels = function(drop_down_item_models) {
    // TODO clear list first?
    for (var i = 0; i < drop_down_item_models.length; ++i) {
      // Initialize drop down view
      var drop_down_item_view = new DropDownItemView(
        templateStore,
        dropDownListNode.node
      );

      drop_down_item_view.init(i, drop_down_item_models[i]);

      // Bind click event listeners
      drop_down_item_view.bindClick(invokeOnclickCallbacks);

      dropDownItemViews.push(drop_down_item_view);
    }
  };
};

function FeedbackPage(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'feedback-page-template';

  var ROOT_CLASS = 'feedback-page-wrapper';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-feedback-page";

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var _this = this;
  var feedbackQuestionList = [];

  /**
   * Dom nodes
   */
  // Root node
  var feedbackPageRootNode = {
    node: null
  };

  // Class-bound nodes
  var questionListNode = {
    className: 'questions-wrapper',
    node: null
  };

  var submitBtnNode = {
    className: 'submit-btn',
    node: null
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = feedbackPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeFeedbackPageTemplate()
   * - copy feedback-page template and insert into main dom tree
   * @pre-condition: 'feedbackPageRootNode' must be initialized
   */
  // function synthesizeFeedbackPageTemplate() {
  //   // Bind feedback-page dom template
  //   var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
  //   var page_clone = document.importNode(page_template.content, true);
  //   feedbackPageRootNode.node.appendChild(page_clone);
  // };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = feedbackPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    bindClassBoundNode(questionListNode);     
    bindClassBoundNode(submitBtnNode);     

    submitBtnNode.node.onclick = function() {
      for (var i = 0; i < feedbackQuestionList.length; ++i) {
        feedbackQuestionList[i].clearResponse();
      }
    };
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    // Initialize feedback questions
    feedbackQuestionList = [];
    Utils.removeDomChildren(questionListNode.node);

    // Question 1
    var question_1 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'What is one thing that MVS did especially well? Why?'
    );
    question_1.init();

    feedbackQuestionList.push(question_1);

    // Question 2
    var question_2 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'What is one thing that you would like to see MVS change going forward? Why?'
    );
    question_2.init();
    feedbackQuestionList.push(question_2);
    
    // Question 3
    var question_3 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'Any other comments/suggestions?'
    );
    question_3.init();

    feedbackQuestionList.push(question_3);
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize monitor experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level feedback-page node (we're going to copy the template into this!)
    feedbackPageRootNode.node = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    );

    // // Clone template and copy into wrapper
    // synthesizeFeedbackPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    // initDisplay();
  };

  /**
   * hide()
   * - hide the feedback-page
   */
  this.hide = function() {
    Utils.hideNode(feedbackPageRootNode.node);
    // feedbackPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the feedback-page
   */
  this.show = function() {
    Utils.showNode(feedbackPageRootNode.node);
    // feedbackPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

  this.getTitle = function() {
    return "Feedback";
  };

  this.addQuestion = function(question_text) {
    var question_view = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      question_text
    );
    question_view.init();
    feedbackQuestionList.push(question_view);
  };

  this.removeQuestion = function(question_idx) {
    feedbackQuestionList[question_idx].remove();
    feedbackQuestionList.splice(question_idx, 1); 
  };
};

function FeedbackQuestion(
  template_store,
  parent_node,
  question_title
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#feedback-question-template';

  /**
   * Default ui string
   */
  var DEFAULT_FEEDBACK_PROMPT = 'Add feedback...';

  /**
   * Ui attributes
   */
  var EDITING_RESPONSE_ATTR = 'editing-response';
  var CHANGED_RESPONSE_ATTR = 'changed-response';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var questionTitle = question_title;
  var isEditingResponse = false;
  var isChangedResponse = false;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'feedback-question-wrapper',
    node: null
  };

  var questionLabelNode = {
    className: 'question-label',
    node: null
  };

  var responseAreaNode = {
    className: 'response-area',
    node: null
  };

  var synthesizeTemplate = function() {
    // Clone pending-order template
    var feedback_question_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var feedback_question_clone = document.importNode(feedback_question_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(feedback_question_clone); 
    var feedback_question_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = feedback_question_list[feedback_question_list.length - 1];
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var bindInternalNodes = function() {
    bindClassBoundNode(questionLabelNode);
    bindClassBoundNode(responseAreaNode);

    responseAreaNode.node.onclick = function() {
      // Short circuit b/c we're already editing this
      if (isEditingResponse) {
        return;
      }

      isEditingResponse = true;
      responseAreaNode.node.setAttribute(EDITING_RESPONSE_ATTR, '');

      if (!isChangedResponse) {
        var range = document.createRange();
        range.selectNodeContents(responseAreaNode.node);
        var sel = window.getSelection();
        sel.removeAllRanges();
        sel.addRange(range);
      }
    };
    
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c question isn't being edited currently anyway
      if (!isEditingResponse) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(responseAreaNode.className, node)) {
          return;
        }
      }   

      if (responseAreaNode.node.innerHTML == '' || responseAreaNode.node.innerHTML == null ||
        responseAreaNode.node.innerHTML == DEFAULT_FEEDBACK_PROMPT
      ) {
        responseAreaNode.node.removeAttribute(CHANGED_RESPONSE_ATTR);
        responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
        isChangedResponse = false;
      } else {
        responseAreaNode.node.setAttribute(CHANGED_RESPONSE_ATTR, '');
        isChangedResponse = true;
      }

      isEditingResponse = false;
      responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);
    });
  }

  var initUi = function() {
    questionLabelNode.node.innerHTML = questionTitle; 
    responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
    isEditingResponse = false;
    responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);
  };

  this.clearResponse = function() {
    isEditingResponse = false;
    responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);

    isChangedResponse = false;
    responseAreaNode.node.removeAttribute(CHANGED_RESPONSE_ATTR);
    responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
  };

  this.getResponse = function() {
    return (isChangedResponse)
      ? responseAreaNode.node.innerHTML
      : null;
  };

  this.init = function() {
    synthesizeTemplate();
    bindInternalNodes();
    initUi();
  };

  this.remove = function() {
    rootNode.node.parentNode.removeChild(rootNode.node);    
  };

};

var MyExperimentView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-skeleton-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-wrapper';

  /**
   * Ui text
   */
  var DEFAULT_TITLE = 'Add title...';

  /**
   * Ui attributes
   */
  var CHANGED_TITLE_ATTR = 'changed-title';
  var EDITING_TITLE_ATTR = 'editing-title';

  /**
   * Private state
   */
  var templateStore = template_store;

  // Ui data
  var cachedTitle = null;
  var isUserDefinedTitle = false;
  var isEditingTitle = false;
 
  // Dom nodes
  var parentNode = parent_node;
  var rootNode = null;

  // Page views
  var frontPageView = null;
  var descriptionPageView = null;
  var monitorExperimentPageView = null;
  var recordingPageView = null;

  var selectedPageView = null;
  var selectedPageButtonNode = null;

  /**
   * Event listeners
   */
  // Title change listeners
  var titleChangeCallbacks = [];

  // Page nav listeners
  var frontPageNavCallbacks = [];
  var descriptionNavCallbacks = [];
  var monitorNavCallbacks = [];
  var recordingNavCallbacks = [];

  /**
   * Dom node infos
   */
  // Title
  var titleLabelNode = {
    className: 'title-label',
    node: null
  };

  var titleHeaderNode = {
    className: 'title-header-wrapper',
    node: null
  };

  // Page wrappers
  var frontPageNode = {
    className: 'front-page',
    node: null
  };

  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };

  var monitorPageNode = {
    className: 'monitor-page',
    node: null
  };

  var recordingPageNode = {
    className: 'recording-page',
    node: null
  };

  // Navigation bar
  var frontPageNavNode = {
    className: 'front-page-nav-wrapper',
    node: null
  };

  var descriptionNavNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var monitorNavNode = {
    className: 'monitor-nav-wrapper',
    node: null
  };

  var recordingNavNode = {
    className: 'recording-nav-wrapper',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind nodes    
    Utils.bindNodeInfo(rootNode, titleLabelNode);
    Utils.bindNodeInfo(rootNode, titleHeaderNode);

    Utils.bindNodeInfo(rootNode, frontPageNode);
    Utils.bindNodeInfo(rootNode, descriptionPageNode);
    Utils.bindNodeInfo(rootNode, monitorPageNode);
    Utils.bindNodeInfo(rootNode, recordingPageNode);

    Utils.bindNodeInfo(rootNode, frontPageNavNode);
    Utils.bindNodeInfo(rootNode, descriptionNavNode);
    Utils.bindNodeInfo(rootNode, monitorNavNode);
    Utils.bindNodeInfo(rootNode, recordingNavNode);

    /**
     * Attach event listeners
     */
    // Page nav listeners
    frontPageNavNode.node.onclick = function() {
      frontPageNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    descriptionNavNode.node.onclick = function() {
      descriptionNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    monitorNavNode.node.onclick = function() {
      monitorNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };
    
    recordingNavNode.node.onclick = function() {
      recordingNavCallbacks.forEach(function(callback) {
        callback();
      }); 
    };

    // Title event listeners
    titleLabelNode.node.onkeypress = function(event) {
      if (Utils.isEnterKeyPressed(event)) {
        setFinishedEditingTitle();
        return false;
      }
    };

    titleHeaderNode.node.onclick = function(event) {
      // Put title in 'editing' state if we're not editing it already
      if (!isEditingTitle) {
        setEditingTitle();
      }
    };

    Utils.bindClickBeyondNode(titleHeaderNode.node, function(event) {
      // Short circuit b/c we're not editing title anyhow
      if (!isEditingTitle) {
        return;
      }

      // Signal that we've finished editing the title
      setFinishedEditingTitle();
    });

  };

  var initPages = function() {
    // Initialize child pages
    frontPageView = new MyExperimentFrontPageView(
      templateStore,
      frontPageNode.node
    );
    frontPageView.init();

    descriptionPageView = new MyExperimentDescriptionPageView(
      templateStore,
      descriptionPageNode.node
    );
    descriptionPageView.init();

    monitorExperimentPageView = new MyExperimentMonitoringPageView(
      templateStore,
      monitorPageNode.node
    );
    monitorExperimentPageView.init();

    recordingPageView = new MyExperimentRecordingPageView(
      templateStore,
      recordingPageNode.node
    );
    recordingPageView.init();
  };
  
  var changePage = function(
    next_page_view,
    next_page_button
  ) {
    // Unselect current page
    selectedPageView.hide();
    Utils.unselectNode(selectedPageButtonNode);
  
    selectPage(next_page_view, next_page_button);
  };

  var selectPage = function(page_view, page_button_node) {
    // Update Ui
    page_view.show();
    Utils.selectNode(page_button_node);

    selectedPageView = page_view;
    selectedPageButtonNode = page_button_node; 
  };

  var setEditingTitle = function() {
    console.assert(!isEditingTitle);
    
    // Update ui
    Utils.markNode(titleHeaderNode.node, EDITING_TITLE_ATTR);

    if (isUserDefinedTitle) {
      // Highligh title field text
      Utils.selectTextRange(titleLabelNode.node); 
    } else {
      // Remove placeholder title 
      titleLabelNode.node.innerHTML = '';
    }

    isEditingTitle = true;
  };

  var setNotEditingTitle = function() {
    console.assert(isEditingTitle);

    // Update ui
    Utils.unmarkNode(titleHeaderNode.node, EDITING_TITLE_ATTR);

    // Unselect title
    Utils.unselectTextRange(titleLabelNode.node);
    titleLabelNode.node.blur();
    window.getSelection().removeAllRanges();

    isEditingTitle = false;
  };

  var setFinishedEditingTitle = function() {
    // Notify listeners that the title has changed! 
    var title = titleLabelNode.node.innerHTML;

    // Short circuit if title hasn't changed
    if (isUserDefinedTitle && title == cachedTitle) {
      return;
    }
    titleChangeCallbacks.forEach(function(callback) {
      callback(title); 
    }); 

    // Return title to non-editing state
    setNotEditingTitle();
  };

  var initUi = function() {
    // Select front page first
    selectPage(frontPageView, frontPageNavNode.node); 

    recordingPageView.showAbsentVideoMessage();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 

    // Initialize child pages
    initPages();

    // Initialize ui
    initUi();

    return this;
  };

  // Callback registers
  this.bindTitle = function(callback) {
    titleChangeCallbacks.push(callback); 
    return this;
  };

  this.bindFrontPageNav = function(callback) {
    frontPageNavCallbacks.push(callback);
    return this;
  };

  this.bindDescriptionNav = function(callback) {
    descriptionNavCallbacks.push(callback);
    return this;
  };

  this.bindMonitorNav = function(callback) {
    monitorNavCallbacks.push(callback);
    return this;
  };

  this.bindRecordingNav = function(callback) {
    recordingNavCallbacks.push(callback);
    return this;
  };

  // Show page functions
  this.showFrontPage = function() {
    changePage(frontPageView, frontPageNavNode.node);
  };

  this.showDescriptionPage = function() {
    changePage(descriptionPageView, descriptionNavNode.node);
  };

  this.showMonitorPage = function() {
    changePage(monitorExperimentPageView, monitorNavNode.node);
  };

  this.showRecordingPage = function() {
    changePage(recordingPageView, recordingNavNode.node);
  };
 
  // Ui setters
  this.setTitle = function(title) {
    // Handle title change
    titleLabelNode.node.innerHTML = title;
    cachedTitle = title;
    Utils.markNode(titleLabelNode.node, CHANGED_TITLE_ATTR);
    isUserDefinedTitle = true;
  };

  this.setTitlePlaceholder = function() {
    titleLabelNode.node.innerHTML = DEFAULT_TITLE;
    cachedTitle = null;
    Utils.unmarkNode(titleLabelNode.node, CHANGED_TITLE_ATTR);
    isUserDefinedTitle = false;
  };

  // Getters
  this.getFrontPageView = function() {
    return frontPageView;
  };

  this.getDescriptionPageView = function() {
    return descriptionPageView;
  };

  this.getMonitorPageView = function() {
    return monitorExperimentPageView;
  };

  this.getRecordingPageView = function() {
    return recordingPageView;
  };

  this.showVideo = function() {
    recordingPageView.showVideo(); 
  };
};

function MyExperimentsPageViewBackup(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var WRAPPER_TEMPLATE_ID_SELECTOR = '#my-experiments-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-my-experiments-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Pending experiment views
  var pendingExperimentViews = [];

  // Root node
  var myExperimentsPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'my-experiments-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeMyExperimentsPageTemplate()
   * - copy my-experiments-page template and insert into main dom tree
   * @pre-condition: 'myExperimentsPageRootNode' must be initialized
   */
  function synthesizeMyExperimentsPageTemplate() {
    // Bind my-experiments-page dom template
    var page_template = templateStore.import.querySelector(WRAPPER_TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    myExperimentsPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    // Bind internal nodes
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize my experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level my-experiments-page node (we're going to copy the template into this!)
    myExperimentsPageRootNode.node = document.getElementById(myExperimentsPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeMyExperimentsPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the my-experiments-page
   */
  this.hide = function() {
    pageWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the my-experiments-page
   */
  this.show = function() {
    pageWrapperNode.node.removeAttribute(HIDDEN_ATTR);
  };

  this.pushPendingOrder = function(confirmed_order) {
    var pending_experiment_view = new PendingExperimentView(
      templateStore,
      pageWrapperNode.node
    );     

    pendingExperimentViews.push(pending_experiment_view);

    pending_experiment_view.init(confirmed_order);
  };

  this.clearPendingOrders = function() {
    pendingExperimentViews = [];
    Utils.removeDomChildren(pageWrapperNode.node);
  };
};

var MyExperimentsPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'My Experiments';

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiments-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiments-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize my-experiments page 
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );
  };

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.spawnNewExperiment = function() {
    var my_experiment_view = new MyExperimentView(
      templateStore,
      rootNode
    ); 

    my_experiment_view.init();
    return my_experiment_view;
  };

  this.removeExperiments = function() {
    Utils.removeDomChildren(rootNode);
  };
};

function PendingExperimentView(
  template_store,
  parent_node
) {

  /**
   * Key code values
   */
  var ENTER_KEY_CODE = 13;

  /**
   * Default values 
   */
  var DEFAULT_TITLE = 'Add title...';
  var DEFAULT_DESCRIPTION = 'Add notes...';

  /**
   * Ui attributes
   */
  var SELECTED_BUTTON_ATTR = "selected-btn";
  var SELECTED_PAGE_ATTR = 'selected-page';
  var EDITING_TITLE_ATTR = 'editing-title';
  var EDITING_DESCRIPTION_ATTR = 'editing-description';
  var CHANGED_TITLE_ATTR = 'changed-title';
  var CHANGED_DESCRIPTION_ATTR = 'changed-description';

  /**
   * Unit tokens 
   */
  var PRICE_UNIT_TOKEN = '$ ';

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#pending-experiment-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var selectedButton = null;
  var selectedPageWrapper = null;
  var isEditingTitle = false;
  var isEditingDescription = false;
  var cachedTitle = null;
  var changedTitleListeners = [];
  var cachedDescription = null;
  var changedDescriptionListeners = [];
  var confirmedOrderModel = null;
  var isActive = false;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'pending-experiment-wrapper',
    node: null
  };

  /**
   * Header nodes
   */
  var headerNode = {
    className: 'header-wrapper',
    node: null
  };

  var titleNode = {
    className: 'title-label',
    node: null
  };

  /**
   * Page nodes 
   */
  var timePageNode = {
    className: 'time-page',
    node: null
  };

  var staticCalendarWrapperNode = {
    className: 'static-calendar',
    node: null
  };

  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };
  
  var recordingPageNode = {
    className: 'recording-page',
    node: null
  };
  
  var monitorPageNode = {
    className: 'monitor-page',
    node: null
  };
  
  /**
   * Footer button nodes
   */
  var descriptionButtonNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var recordingButtonNode = {
    className: 'recording-nav-wrapper',
    node: null
  };

  var timeButtonNode = {
    className: 'time-nav-wrapper',
    node: null
  };

  var monitorButtonNode = {
    className: 'monitor-nav-wrapper',
    node: null
  };

  /**
   * Main stage wrappers
   */
  var scopesCountNode = {
    className: 'scopes-count-value',
    node: null
  };

  var startTimeNode = {
    className: 'start-time-value',
    node: null
  };

  var durationNode = {
    className: 'experiment-duration-value',
    node: null
  };

  var durationUnitNode = {
    className: 'experiment-duration-unit',
    node: null,
    singular: 'hour',
    plural: 'hours'
  };

  var priceNode = {
    className: 'price-value',
    node: null
  };

  var shortCodeNode = {
    className: 'short-code-value',
    node: null
  };

  /**
   * Private functions
   */
  function synthesizeTemplate() {
    // Clone pending-order template
    var pending_order_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var pending_order_clone = document.importNode(pending_order_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(pending_order_clone); 
    var pending_order_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = pending_order_list[pending_order_list.length - 1];
  };

  /**
   * setTitle()
   * @param string title: title string
   */
  function setTitle(title) {
    if (title == null || title == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
      cachedTitle = null;
      titleNode.node.removeAttribute(CHANGED_TITLE_ATTR);
    } else {
      titleNode.node.innerHTML = title; 
      cachedTitle = title;
      titleNode.node.setAttribute(CHANGED_TITLE_ATTR, '');
    }
  };

  /**
   * setStartTime()
   * @param string start_time : timestamp string
   */
  function setStartTime(start_time) {
    startTimeNode.node.innerHTML = start_time; 
  };

  /**
   * setDescription()
   * @param string description
   */
  function setDescription(description) {
    if (description == null || description == '') {
      descriptionPageNode.node.innerHTML = DEFAULT_DESCRIPTION; 
      cachedDescription = null;
      descriptionPageNode.node.removeAttribute(CHANGED_DESCRIPTION_ATTR);
    } else {
      descriptionPageNode.node.innerHTML = description; 
      cachedDescription = description;
      descriptionPageNode.node.setAttribute(CHANGED_DESCRIPTION_ATTR, '');
    }
  };

  /**
   * setDuration()
   * @param uint duration : duration in hours
   */
  function setDuration(duration) {
    durationNode.node.innerHTML = duration;
    durationUnitNode.node.innerHTML = (duration == 1)
      ? durationUnitNode.singular
      : durationUnitNode.plural;
  };

  function setShortCode(short_code) {
    shortCodeNode.node.innerHTML = short_code.getAlias(); 
  };

  function setScopesCount(scopes_count) {
    scopesCountNode.node.innerHTML = scopes_count;
  };

  function setPrice(price) {
    priceNode.node.innerHTML = PRICE_UNIT_TOKEN + Utils.makePriceString(price);
  };

  function setOrderedDate(ordered_date) {
    orderedDateNode.node.innerHTML = ordered_date.serialize();
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var unselectButton = function() {
    console.assert(selectedButton !== null); 
    selectedButton.node.removeAttribute(SELECTED_BUTTON_ATTR);
    selectedButton = null;
  };

  var selectButton = function(selected_button) {
    console.assert(selectedButton === null);
    selectedButton = selected_button;
    selectedButton.node.setAttribute(SELECTED_BUTTON_ATTR, '');
  };

  var hideSelectedPage = function() {
    console.assert(selectedPageWrapper !== null);
    selectedPageWrapper.node.removeAttribute(SELECTED_PAGE_ATTR);
    selectedPageWrapper = null;
  };

  var selectPage = function(page) {
    console.assert(selectedPageWrapper === null);
    selectedPageWrapper = page;
    selectedPageWrapper.node.setAttribute(SELECTED_PAGE_ATTR, '');
  };

  var changePage = function(button, page) {
    // Deselect currently selected button/page
    unselectButton();
    hideSelectedPage();

    // Select new button/page
    selectButton(button);
    selectPage(page);
  };

  var setEditingDescription = function() {
    console.assert(!isEditingDescription);
    isEditingDescription = true;
    descriptionPageNode.node.setAttribute(EDITING_DESCRIPTION_ATTR, '');

    // Highlight default description if no description provided
    if (cachedDescription == null || '') {
      var range = document.createRange();
      range.selectNodeContents(descriptionPageNode.node);
      var sel = window.getSelection();
      sel.removeAllRanges();
      sel.addRange(range);
    }
  }

  var setNotEditingDescription = function() {
    console.assert(isEditingDescription);
    descriptionPageNode.node.removeAttribute(EDITING_DESCRIPTION_ATTR);
    isEditingDescription = false;

    // Restore default description if user removed the description
    if (cachedDescription == null || cachedDescription == '') {
      descriptionPageNode.node.innerHTML = DEFAULT_DESCRIPTION;
    }
  };

  var finishedEditingDescription = function() {
    // Notify listeners that the description has changed!
    if (cachedDescription != descriptionPageNode.node.innerHTML &&
        !(cachedDescription == null && descriptionPageNode.node.innerHTML == DEFAULT_DESCRIPTION) &&
        !(cachedDescription == null && descriptionPageNode.node.innerHTML == '')
    ) {
      // Update cached description value
      cachedDescription = descriptionPageNode.node.innerHTML;

      if (cachedDescription == '') {
        cachedDescription = null;
      }

      if (cachedDescription != null) {
        descriptionPageNode.node.setAttribute(CHANGED_DESCRIPTION_ATTR, '');
      } else {
        descriptionPageNode.node.removeAttribute(CHANGED_DESCRIPTION_ATTR); 
      }

      console.log(cachedDescription);

      for (var i = 0; i < changedDescriptionListeners.length; ++i) {
        changedDescriptionListeners[i](cachedDescription);
      }
    }

    // Return description to non-editing state
    setNotEditingDescription();
  };

  var bindTimeNodes = function() {
    bindClassBoundNode(timePageNode);
    bindClassBoundNode(staticCalendarWrapperNode);
    
    bindClassBoundNode(shortCodeNode);
    bindClassBoundNode(scopesCountNode);
    bindClassBoundNode(priceNode);
    bindClassBoundNode(startTimeNode);
    bindClassBoundNode(durationNode);
    bindClassBoundNode(durationUnitNode);
  };

  var bindDescriptionNodes = function() {
    // Bind dom nodes
    bindClassBoundNode(descriptionPageNode);

    // Bind event listeners
    descriptionPageNode.node.onclick = function() {
      // Short circuit b/c we're already editing the description
      if (isEditingDescription) {
        return;
      }

      setEditingDescription();
    }; 

    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c description isn't being edited currently anyway
      if (!isEditingDescription) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(descriptionPageNode.className, node)) {
          return;
        }
      }   

      // Signal that we've finished editing the description
      finishedEditingDescription();
    });
  };

  var bindPageNodes = function() {
    // Bind nodes
    bindTimeNodes();
    bindDescriptionNodes();
    bindClassBoundNode(recordingPageNode);
    bindClassBoundNode(monitorPageNode);
  };

  var bindFooterNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionButtonNode);
    bindClassBoundNode(recordingButtonNode);
    bindClassBoundNode(timeButtonNode);
    bindClassBoundNode(monitorButtonNode);

    // Configure event listeners
    descriptionButtonNode.node.onclick = function() {
      changePage(descriptionButtonNode, descriptionPageNode); 
    }; 
    recordingButtonNode.node.onclick = function() {
      changePage(recordingButtonNode, recordingPageNode); 
    }; 
    timeButtonNode.node.onclick = function() {
      changePage(timeButtonNode, timePageNode); 
    }; 
    monitorButtonNode.node.onclick = function() {
      changePage(monitorButtonNode, monitorPageNode); 
    }; 
  };

  var setEditingTitle = function() {
    console.assert(!isEditingTitle);
    headerNode.node.setAttribute(EDITING_TITLE_ATTR, '');  
    
    // Select text in title field
    var range = document.createRange();
    range.selectNodeContents(titleNode.node);
    var sel = window.getSelection();
    sel.removeAllRanges();
    sel.addRange(range);

    isEditingTitle = true;
  };

  var setNotEditingTitle = function() {
    console.assert(isEditingTitle);
    isEditingTitle = false;

    headerNode.node.removeAttribute(EDITING_TITLE_ATTR);
    titleNode.node.blur();

    var selection = window.getSelection();
    if (Utils.hasClass(titleNode.node.className, selection.anchorNode.parentElement)) {
      selection.removeAllRanges(); 
    }

    // Restore default title if user removed title
    if (cachedTitle == null || cachedTitle == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
    }
  };

  var finishedEditingTitle = function() {
    // Notify listeners that the title has changed!
    if (cachedTitle != titleNode.node.innerHTML &&
        !(cachedTitle == null && titleNode.node.innerHTML == DEFAULT_TITLE) &&
        !(cachedTitle == null && titleNode.node.innerHTML == '')
    ) {
      // Update cached title value
      cachedTitle = titleNode.node.innerHTML;

      if (cachedTitle == '') {
        cachedTitle = null;
      }

      if (cachedTitle != null) {
        titleNode.node.setAttribute(CHANGED_TITLE_ATTR, '');  
      } else {
        titleNode.node.removeAttribute(CHANGED_TITLE_ATTR);  
      }
      
      console.log(cachedTitle);

      for (var i = 0; i < changedTitleListeners.length; ++i) {
        changedTitleListeners[i](cachedTitle);
      }
    }
    
    // Return title to non-editing state
    setNotEditingTitle();
  };

  var bindHeaderNodes = function() {
    // Bind header nodes
    bindClassBoundNode(headerNode);
    bindClassBoundNode(titleNode); 

    // Bind header event listeners
    headerNode.node.onclick = function() {
      // Short circuit b/c we're already editing the title...
      if (isEditingTitle) {
        return;
      }

      setEditingTitle();
    };

    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c title isn't being edited currently anyway
      if (!isEditingTitle) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(headerNode.className, node)) {
          return;
        }
      }   

      // Signal that we've finished editing the title
      finishedEditingTitle();
    });

    titleNode.node.onkeypress = function(event) {
      // If 'return' pressed, then direct focus away from 'titleNode'
      if (event.charCode == ENTER_KEY_CODE) {
        finishedEditingTitle();
        return false;
      }
    };
  };

  var bindInternalNodes = function() {
    bindHeaderNodes();
    bindPageNodes();
    bindFooterNodes();
  };

  var initUiData = function(confirmed_order) {
    // Update header data
    setTitle(confirmed_order.getTitle());

    // Update time data
    staticCalendar = new StaticCalendar(
      templateStore,
      staticCalendarWrapperNode.node,
      confirmed_order.getStartTimestamp()
    );
    staticCalendar.init();
    
    setScopesCount(confirmed_order.getScopesCount());
    setPrice(confirmed_order.getPrice());
    setShortCode(confirmed_order.getShortCode());

    var experiment_start_time = new Date(confirmed_order.getStartTimestamp());
    var serializeable_experiment_start_time = new SerializeableTime(
      experiment_start_time.getHours(),
      experiment_start_time.getMinutes(),
      experiment_start_time.getSeconds()
    );

    setStartTime(serializeable_experiment_start_time.serializeWithoutSeconds());
    
    var experiment_end_time = new Date(confirmed_order.getEndTimestamp());

    setDuration(DateOperator.getDifferenceInHours(
      experiment_end_time,
      experiment_start_time
    ));

    // Init description-page data
    setDescription(confirmed_order.getDescription());
  };

  var bindModel = function(confirmed_order_model) {
    confirmedOrderModel = confirmed_order_model; 

    // Bind event listeners (also initializes ui data)
    confirmedOrderModel.bindTitle(setTitle);
    confirmedOrderModel.bindDescription(setDescription);
    confirmedOrderModel.bindPrice(setPrice);
    confirmedOderModel.bindScopesCount(setScopesCount);
    confirmedOderModel.bindExperimentDuration(setDuration);
    confirmedOderModel.bindStartTime(setStartTime);
    confirmedOderModel.bindStartDate(setOrderedDate);
    confirmedOderModel.bindShortCode(setShortCode);
  };

  /**
   * Privileged functions
   */
  this.init = function(confirmed_order_model) {
    // Check: view must be inactive to initialize!
    console.assert(!isActive);
    isActive = true;

    // Clone template and copy into pending-experiments list
    synthesizeTemplate();

    // Init dom pointers to internal nodes
    bindInternalNodes();

    // Place data in proper ui elements
    // initUiData(confirmed_order_model);
    bindModel(confirmed_order_model);

    selectButton(timeButtonNode);
    selectPage(timePageNode);
  };

  this.remove = function() {
    rootNode.node.remove();  
    isActive = false;
  };

  /**
   * registerChangedTitleListener()
   * @param FuncPtr callback: function(title) {...}
   */
  this.registerChangedTitleListener = function(callback) {
    changedTitleListeners.push(callback);
  }

  /**
   * registerChangedDescriptionListener()
   * @param FuncPtr callback: function(title) {...}
   */
  this.registerChangedDescriptionListener = function(callback) {
    changedDescriptionListeners.push(callback);
  };
};

var ScopesCountFormView = function(template_store) {

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Privileged functions
   */
  this.init = function(parent_node) {
    parentNode = parent_node;
  };
};

function ShortCodePicker(
  template_store,
  id,
  short_codes // {id, code, alias}, optional
) {

  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var INPUT_FIELD_WRAPPER_TOOLTIP_ATTR = 'tooltip';
  var OPTION_LOCAL_IDX_ATTR = 'local-idx';
  var OPTION_TOOLTIP_ATTR = 'tooltip';
  var OPTION_SELECTED_ATTR = 'selected-option';

  /**
   * Html class names
   */
  var SHORT_CODE_LABEL_CLASS = 'short-code-label';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-option';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-picker-option';

  /**
   * Html template id names
   */
  var MAIN_TEMPLATE_ID = '#short-code-picker-template';
  var OPTION_TEMPLATE_ID = '#short-code-picker-option-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var shortCodes = typeof short_codes == 'undefined' ? [] : short_codes;
  var isDropDownOpen = false;
  var selectedOptionIndex = null;

  /**
   * Dom nodes
   */
  var rootNode = {
    nodeId: id,
    node: null
  };

  var shortCodePickerWrapperNode = {
    class: 'short-code-picker-wrapper',
    node: null
  };
  
  var inputFieldLabelNode = {
    class: 'input-field-label',
    node: null
  };

  var inputFieldNode = {
    class: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    class: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    class: 'short-code-dropdown',
    node: null
  };

  // Private functions
  /**
   * synthesizeShortCodePickerTemplate()
   * - copy template and insert into root node
   * @pre-condition: root node is initialized 
   */
  var synthesizeShortCodePickerTemplate = function() {
    var short_code_picker_template = templateStore.import.querySelector(MAIN_TEMPLATE_ID);
    var short_code_picker_clone = document.importNode(short_code_picker_template.content, true);
    rootNode.node.appendChild(short_code_picker_clone);
  };

  /**
   * openDropDown()
   * - opens drop-down menu
   */
  var openDropDown = function() {
    isDropDownOpen = true;
    shortCodePickerWrapperNode.node.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };
 
  /**
   * closeDropDown()
   * - closes drop-down menu
   */
  var closeDropDown = function() {
    isDropDownOpen = false;    
    shortCodePickerWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * initOptionNode()
   * - clone new option node
   * - bind data and event listeners
   * - insert into drop-down
   * @param Object option: option struct provided in constructor
   */
  var initOptionNode = function(option) {
    // Clone new option node from template
    var short_code_picker_option_template = templateStore.import.querySelector(OPTION_TEMPLATE_ID);  
    var short_code_picker_option_clone = document.importNode(short_code_picker_option_template.content, true);

    // Add to drop-down (activates node so that we can now bind data/event listeners)
    dropDownNode.node.appendChild(short_code_picker_option_clone); 

    // Bind data
    var short_code_picker_option_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(short_code_picker_option_list.length > 0);
    var option_local_idx = short_code_picker_option_list.length - 1; 
    var short_code_picker_option = short_code_picker_option_list[option_local_idx];

    // Local index (index of short-code in local array of short-code objects)
    short_code_picker_option.setAttribute(OPTION_LOCAL_IDX_ATTR, option_local_idx);
   
    // Tooltip (actual short code number, not just name)
    short_code_picker_option.setAttribute(OPTION_TOOLTIP_ATTR, option.code);
   
    // Short code name (name given by user, not just number)
    var short_code_label_node_list = short_code_picker_option.getElementsByClassName(SHORT_CODE_LABEL_CLASS);
    console.assert(short_code_label_node_list.length == 1);
    short_code_label_node_list[0].innerHTML = option.alias;
  };

  /**
   * bindInternalNode()
   * - bind the specified dom node (must be internal to this short-code-picker)
   * @param: Obj internal_node: internal dom node (see 'inputFieldNode' for structure)
   * @pre-condition: root node bound 
   */
  var bindInternalNode = function(internal_node) {
    // We bind internal nodes once only!
    console.assert(internal_node.node == null); 

    // Fetch internal node by class
    var node_set = rootNode.node.getElementsByClassName(internal_node.class);

    // We should only find one *internal* node with this class
    console.assert(node_set.length == 1);

    internal_node.node = node_set[0];
  };

  /**
   * initMainNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initMainNodes = function() {
    // Bind top-level node in short-code-picker template
    bindInternalNode(shortCodePickerWrapperNode);
    
    // Bind input field and configure event listener
    bindInternalNode(inputFieldLabelNode);
    bindInternalNode(inputFieldNode);
    bindInternalNode(inputFieldWrapperNode);

    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    // Bind time dropdown field and configure event listener
    bindInternalNode(dropDownNode);

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected short-code 
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(SHORT_CODE_PICKER_OPTION_CLASS, node)) {
          // Capture selected option
          var local_idx_str = node.getAttribute(OPTION_LOCAL_IDX_ATTR);
          console.assert(local_idx_str != null);

          var local_idx = parseInt(local_idx_str);
          console.assert(local_idx != null);

          // Deselect previously selected option
          unselectOptionByIndex(selectedOptionIndex);

          // Select clicked option
          selectOptionByIndex(local_idx);

          return;
        }
      }
    };

    // Hide short-code picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        // User clicked on the time-picker, so don't hide it!
        if (Utils.hasClass(shortCodePickerWrapperNode.class, node)) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  }
 
  /**
   * initOptionNodes()
   * - initialize nodes for short code options
   */
  var initOptionNodes = function() {
    // Clear existing nodes
    Utils.removeDomChildren(dropDownNode.node);

    // Generate option nodes and insert into parent
    for (var i = 0; i < shortCodes.length; ++i) {
      initOptionNode(shortCodes[i]);
    }
  };
  
  /**
   * initDisplay()
   * - initialize the picker display
   */
  var initDisplay = function() {
    // Start with dropdown closed or open depending on initial value
    if (isDropDownOpen) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize starting short code 
    if (shortCodes.length !== 0) {
      selectOptionByIndex(0);
    }
  };

  /**
   * selectOptionByIndex()
   * - select the specified short-code option
   * @param uint option_index: index of the option that is selected
   */
  var selectOptionByIndex = function(option_index) {
    console.assert(option_index < shortCodes.length);

    // Bind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.setAttribute(OPTION_SELECTED_ATTR, '');
    
    inputFieldWrapperNode.node.setAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR, option.code);

    // Update main display
    inputFieldLabelNode.node.innerHTML = option.alias; 

    selectedOptionIndex = option_index;
  };

  /**
   * unselectOptionByIndex()
   * - unselect the specified short-code option
   * @param uint option_index: index of the option that is to be unselected
   */
  var unselectOptionByIndex = function(option_index) {
    console.assert(selectedOptionIndex != null);
    console.assert(option_index < shortCodes.length);

    // Unbind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.removeAttribute(OPTION_SELECTED_ATTR);

    inputFieldWrapperNode.node.removeAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR);

    // Update main display
    inputFieldLabelNode.node.innerHTML = '';

    selectedOptionIndex = null;
  };

  function setInitialStateInternal() {
    // Update ui with new short-codes
    initDisplay();
  };

  // Privileged functions
  /**
   * setShortCodes()
   * - set list of selectable short-codes
   * @param: array<ShortCode> short_codes: {id, code, alias}
   */
  this.setShortCodes = function(short_codes) {
    shortCodes = short_codes; 

    initOptionNodes();
    setInitialStateInternal();
  };

  /**
   * init()
   * - initialize short-code picker
   */
  this.init = function() {
    // We only init once!
    console.assert(rootNode.node == null);

    // Bind root node
    rootNode.node = document.getElementById(rootNode.nodeId);

    // Synthesize the template and copy into the root node
    synthesizeShortCodePickerTemplate();

    // Initialize nodes: dom elements and event listeners
    initMainNodes();

    // Initialize ui state
    initOptionNodes();
    setInitialStateInternal();
  };

  this.getSelectedShortCode = function() {
    console.assert(selectedOptionIndex !== null);
    console.assert(selectedOptionIndex < shortCodes.length);
    return shortCodes[selectedOptionIndex];
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };
};

var SidePanelView = function(
  template_store,
  parent_node
) {

  /**
   * Template node id
   */
  var TEMPLATE_ID = 'side-panel-template';

  /**
   * Root node class name
   */
  var ROOT_NODE_CLASS = 'side-panel-wrapper';
  
  /**
   * Ui attributes
   */
  var START_HIDDEN_ATTR = "start-hidden";
  
  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var currentlySelectedTabAndPageInfo = null;
  var centerPageTitleLabel = null;
  var centerPanelPageContainer = null;
  
  var currentlySelectedTab = null;
  var tabParentNode = null;

  /**
   * Tab infos
   */
  var tabContainerRootInfo = {
    className: 'nav-btns-container',
    node: null
  };

  var homeButtonNode = {
    className: 'home-nav-container',
    node: null
  };

  var userNameNode = {
    className: 'side-panel-user-label',
    node: null
  };

  var newExperimentInfo = {
    button_title: 'Add Experiment',
    icon_type: 'add-circle-outline',
    tab: null,
    callback_listeners: []
  };

  var myExperimentsInfo = {
    button_title: 'My Experiments',
    icon_type: 'group-work',
    tab: null,
    callback_listeners: []
  };

  var feedbackInfo = {
    button_title: 'Feedback',
    icon_type: 'question-answer',
    tab: null,
    callback_listeners: []
  };

  var technicianInfo = {
    button_title: 'Technician',
    icon_type: 'build',
    tab: null,
    callback_listeners: []
  };

  /**
   * Private functions
   */
  /**
   * initTabInfo()
   * - initialize SidePanelTab view
   * - bind event listeners
   * @param TabInfo (see above)
   */
  var initTabInfo = function(tab_info) {
    // Initialize tab view 
    tab_info.tab = new SidePanelTab(
      templateStore,
      tabContainerRootInfo.node,
      tab_info.button_title,
      tab_info.icon_type
    );    

    // Register 'onclick' callback
    tab_info.tab.registerOnClickListener(function() {
      // // Unselect previous tab
      // currentlySelectedTab.deselect();
      //
      // // Select new tab
      // currentlySelectedTab = tab_info.tab;
      // currentlySelectedTab.select();

      // Invoke callback listeners
      for (var i = 0; i < tab_info.callback_listeners.length; ++i) {
        tab_info.callback_listeners[i]();
      }
    });

    // Initialize tab ui
    tab_info.tab.init();
  };

  /**
   * initTabInfos()
   * - initialize all tabs (bind nodes and event listeners)
   */
  var initTabInfos = function() {
    // Initialize tab parent node
    tabContainerRootInfo.node = Utils.bindNode(
      rootNode,
      tabContainerRootInfo.className
    ); 

    // Initialize tab views
    initTabInfo(newExperimentInfo);
    initTabInfo(myExperimentsInfo);
    initTabInfo(technicianInfo);
    initTabInfo(feedbackInfo);
  };

  var selectTab = function(tab) {
    if (currentlySelectedTab != null) {
      currentlySelectedTab.deselect();
    }
    tab.select();
    currentlySelectedTab = tab;
  };

  var bindNodes = function() {
    // Initialize user-name ui node
    userNameNode.node = Utils.bindNode(
      rootNode,
      userNameNode.className
    );

    // Initialize home burron ui node
    homeButtonNode.node = Utils.bindNode(
      rootNode,
      homeButtonNode.className
    );

    // Initialize tabs
    initTabInfos();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize html template and insert into main document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_NODE_CLASS
    );    

    bindNodes();
  
    return this;
  };

  /**
   * Onclick event listeners for tabs
   */
  this.bindNewExperimentTabClick = function(callback) {
    newExperimentInfo.callback_listeners.push(callback); 
  };

  this.bindMyExperimentsTabClick = function(callback) {
    myExperimentsInfo.callback_listeners.push(callback); 
  };

  this.bindFeedbackTabClick = function(callback) {
    feedbackInfo.callback_listeners.push(callback); 
  };

  this.bindTechnicianTabClick = function(callback) {
    technicianInfo.callback_listeners.push(callback); 
  };

  /**
   * Select tab
   */
  this.selectNewExperimentTab = function() {
    selectTab(newExperimentInfo.tab);
  };

  this.selectMyExperimentsTab = function() {
    selectTab(myExperimentsInfo.tab);
  };

  this.selectFeedbackTab = function() {
    selectTab(feedbackInfo.tab);
  };

  this.selectTechnicianTab = function() {
    selectTab(technicianInfo.tab);
  };

  this.setUserName = function(first_name, last_name) {
    var name = first_name + ' ' + last_name;
    userNameNode.node.innerHTML = name;
    // TODO check the length and curtail name if char count exceeds max
    return this;
  };
};

function SidePanelTab(
  template_store,
  parent_node,
  button_title,
  iron_icon_type
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = "#side-panel-tab-template";

  /**
   * Ui attributes
   */
  var SELECTED_ATTR = "selected-side-panel-tab";
  var IRON_ICON_TYPE_ATTR = "icon";

  /**
   * Private state
   */
  var _this = this;
  var templateStore = template_store;
  var buttonTitle = button_title;
  var ironIconType = iron_icon_type;
  var onClickListeners = [];

  // Root dom node
  var rootNode = {
    className: 'dash-nav-panel-btn',
    node: null
  };

  var ironIconNode = {
    className: 'nav-btn-icon',
    node: null
  };

  var buttonTitleNode = {
    className: 'nav-btn-label',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = rootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  function synthesizeSidePanelTemplate() {
    var tab_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var tab_clone = document.importNode(tab_template.content, true);
    parent_node.appendChild(tab_clone);

    // Initialize root node and configure event listener
    var tabs = parent_node.getElementsByClassName(rootNode.className);
    rootNode.node = tabs[tabs.length - 1];

    rootNode.node.onclick = function() {
      for (var i = 0; i < onClickListeners.length; ++i) {
        onClickListeners[i]();
      }
    };
  };

  /**
   * bindInternalNodes()
   * @pre-condition: 'rootNode' must already be bound
   */
  function bindInternalNodes() {
    bindClassBoundNode(ironIconNode); 
    bindClassBoundNode(buttonTitleNode);
  };

  /**
   * initDisplay()
   * - initializes text/graphics for this tab
   * @pre-condition: all internal nodes bound
   */
  function initDisplay() {
    ironIconNode.node.setAttribute(IRON_ICON_TYPE_ATTR, ironIconType);
    buttonTitleNode.node.innerHTML = buttonTitle; 
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize template and append to parent dom node
    synthesizeSidePanelTemplate();

    // Initialize pointers to internal nodes
    bindInternalNodes();

    // Initialize the ui
    initDisplay();
  }; 

  this.select = function() {
    rootNode.node.setAttribute(SELECTED_ATTR, ''); 
  };

  this.deselect = function() {
    rootNode.node.removeAttribute(SELECTED_ATTR);
  };

  /**
   * registerOnClickListener()
   * @param FuncPtr callback: function(_this) {...}
   */
  this.registerOnClickListener = function(callback) {
    onClickListeners.push(callback); 
  };
};

function TechnicianPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#technician-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-technician-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Root node
  var TechnicianPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'technician-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeTechnicianPageTemplate()
   * - copy technician-page template and insert into main dom tree
   * @pre-condition: 'TechnicianPageRootNode' must be initialized
   */
  function synthesizeTechnicianPageTemplate() {
    // Bind technician-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    TechnicianPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize technician page and put it in starting state
   */
  this.init = function() {
    // Bind top-level technician-page node (we're going to copy the template into this!)
    TechnicianPageRootNode.node = document.getElementById(TechnicianPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeTechnicianPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the technician-page
   */
  this.hide = function() {
    TechnicianPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the technician-page
   */
  this.show = function() {
    TechnicianPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

};

var TechnicianPageFeedbackQuestionView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'technician-feedback-question-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'technician-feedback-question-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;
  var questionIndex = null;

  var cancelCallbacks = [];

  var _this = this;

  /**
   * Dom nodes
   */
  var cancelButtonNode = {
    className: 'delete-question-button',
    node: null
  };

  var textNode = {
    className: 'question-text',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, cancelButtonNode);
    Utils.bindNodeInfo(rootNode, textNode);

    cancelButtonNode.node.onclick = function(event) {
      cancelCallbacks.forEach(function(callback) {
        callback(this);
      }, _this);
    };
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui dom nodes
    bindNodes();
  };

  this.setText = function(text) {
    textNode.node.innerHTML = text;
  };

  this.bindCancel = function(callback) {
    cancelCallbacks.push(callback);
  };

  this.remove = function() {
    rootNode.parentNode.removeChild(rootNode);
  };

  this.setIndex = function(index) {
    questionIndex = index;
  };

  this.getIndex = function() {
    return questionIndex;
  };
};

var TechnicianPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'Technician';

  /**
   * Template id
   */
  var TEMPLATE_ID = 'technician-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'technician-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var addQuestionCallbacks = [];

  /**
   * Dom nodes
   */
  var existingQuestionsNode = {
    className: 'existing-questions',
    node: null
  };

  var addQuestionTextNode = {
    className: 'add-question-text-field',
    node: null
  };

  var addQuestionWrapperNode = {
    className: 'add-new-question-wrapper',
    node: null
  };

  var addQuestionButtonNode = {
    className: 'add-question-button',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, existingQuestionsNode);
    Utils.bindNodeInfo(rootNode, addQuestionTextNode);
    Utils.bindNodeInfo(rootNode, addQuestionWrapperNode);
    Utils.bindNodeInfo(rootNode, addQuestionButtonNode);

    addQuestionButtonNode.node.onclick = function() {
      addQuestionCallbacks.forEach(function(callback) {
        callback();
      });      
    };
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui dom nodes
    bindNodes();
  };

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.clearNewQuestionText = function() {
    addQuestionTextNode.node.innerHTML = ''; 
  };

  this.getNewQuestionText = function() {
    return addQuestionTextNode.node.innerHTML;
  };

  this.bindNewQuestion = function(callback) {
    addQuestionCallbacks.push(callback);
  };

  this.addQuestion = function(question) {
    feedback_question.setText(question);
  };

  this.spawnNewQuestion = function() {
    var feedback_question = new TechnicianPageFeedbackQuestionView(
      templateStore,
      existingQuestionsNode.node
    );

    feedback_question.init();
    return feedback_question;
  };
};

function TimePicker(
  template_store,
  parent_node,
  start_time, // {minute, hour}
  end_time,   // {minute, hour}
  time_interval // min
) {
  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var TIME_ATTR = 'time';

  /**
   * Html class names
   */
  var TIME_LABEL_CLASS = 'time-label';
  var TIME_PICKER_OPTION_CLASS = 'time-picker-option';
  var ROOT_WRAPPER_CLASS = 'time-picker-wrapper';

  /**
   * Html template id name
   */
  var MAIN_TEMPLATE_ID = 'time-picker-template';
  var OPTION_TEMPLATE_ID = 'time-picker-option-template';

  /**
   * Meridian designations 
   */
  var HOUR_MIN_SEPARATOR = ':';
  var AM_DESIGNATION = 'am';
  var PM_DESIGNATION = 'pm';

  /**
   * Initial state
   */
  var INITIAL_IS_DROP_DOWN_OPEN = false;

  // Private state
  var templateStore = template_store;
  var parentNode = parent_node;

  var startTime = start_time;
  var endTime = end_time;
  var timeInterval = time_interval; 
  var isDropDownOpen = false;
  var currentTime = null; // hours * 60 + minutes

  /**
   * Internal dom nodes
   */
  var inputFieldNode = {
    className: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    className: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    className: 'time-dropdown',
    node: null
  };

  // Private functions
  var openDropDown = function() {
    isDropDownOpen = true;    
    timePickerRootNode.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };

  var closeDropDown = function() {
    isDropDownOpen = false;    
    timePickerRootNode.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * configureAvailableTimes()
   * - compute available times and initialize ui elements
   * @pre-condition: root initialized and dom synthesized
   */
  var configureAvailableTimes = function() {
    var current_time = startTime.hours * 60 + startTime.minutes;
    var next_time = current_time + time_interval;
    var end_time = endTime.hours * 60 + endTime.minutes;

    while (next_time <= end_time) {
      // Synthesize time-picker-option template
      var time_picker_option = Utils.synthesizeTemplateIntoList(
        templateStore,
        OPTION_TEMPLATE_ID,
        dropDownNode.node,
        TIME_PICKER_OPTION_CLASS
      );

      // Hack!
      time_picker_option.time = current_time;
      var time_label = time_picker_option.querySelector('.' + TIME_LABEL_CLASS);
      time_label.innerHTML = stringifyTime(current_time);

      current_time = next_time;
      next_time += time_interval;
    }
  };

  var applyDoubleDigitTimeFormat = function(numeric_time_element) {
    return (numeric_time_element < 10)
      ? '0' + numeric_time_element 
      : numeric_time_element;
  };

  var stringifyTimeForInputField = function(time) {
    var string_time = stringifyTime(time);
    return string_time.replace(/&nbsp/gi, '');
  };

  /**
   * stringifyTime()
   * - convert numeric time to string format 
   * @param: uint time: hours * 60 + minutes
   * @return 'hh:mm' 
   */
  var stringifyTime = function(time) {
    // Stringify minutes
    var minutes = time % 60;
    var minutes_string = applyDoubleDigitTimeFormat(minutes);

    // Stringify hours
    var hours = (time - minutes) / 60;

    var meridian_designation = AM_DESIGNATION;
    if (hours > 12) {
      meridian_designation = PM_DESIGNATION;   
      hours = hours % 12;
    } 

    var hours_string = (hours < 10)
      ? '&nbsp&nbsp' + hours
      : hours;

    return hours_string + HOUR_MIN_SEPARATOR + minutes_string + ' ' + meridian_designation;
  };

  /**
   * initNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initNodes = function() {
    // Bind dom nodes
    inputFieldNode.node = Utils.bindNode(
      timePickerRootNode,
      inputFieldNode.className
    );
    
    inputFieldWrapperNode.node = Utils.bindNode(
      timePickerRootNode,
      inputFieldWrapperNode.className
    );
    
    dropDownNode.node = Utils.bindNode(
      timePickerRootNode,
      dropDownNode.className
    );

    // Configure event listeners
    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected time
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(TIME_PICKER_OPTION_CLASS, node)) {
          setTimeByIndex(node.picker_index);
          return;
        }
      }
    };

    // Hide time picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the time-picker, so don't hide it!
        if (node == timePickerRootNode) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  };

  // Start with closed or open drop-down (as specified by default param)
  var initDisplay = function() {
    if (INITIAL_IS_DROP_DOWN_OPEN) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize start time
    var time_picker_options = timePickerRootNode.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
    var starting_time_option = time_picker_options[0].getAttribute(TIME_ATTR);
    inputFieldNode.node.innerHTML = stringifyTimeForInputField(starting_time_option);
    currentTime = starting_time_option;
  };

  function setInitialStateInternal() {
    // Initialize the ui
    initDisplay();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize html template into document
    timePickerRootNode = Utils.synthesizeTemplate(
      templateStore,
      MAIN_TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    );

    // Initialize nodes: dom elements and event listeners
    initNodes(); 
  
    // Compute available times and initialize ui state
    configureAvailableTimes();
    setInitialStateInternal();
  };

  this.getSelectedTime = function() {
    var num_minutes = currentTime % 60;
    var num_hours = (currentTime - num_minutes) / 60;
    return {
      hours: num_hours,
      minutes: num_minutes,
      seconds: 0
    };
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };

  this.setTimeByIndex = function(time) {
    inputFieldNode.node.innerHTML = stringifyTimeForInputField(time);
    currentTime = time;
  };
};

var ConfirmOrderFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'confirm-order-form-template';

  /**
   * Root wrapper class
   */
  var ROOT_CLASS = 'confirm-order-form-wrapper';

  /**
   * UI text
   */
  var HOUR_UNIT = {
    singular: 'hour',
    plural: 'hours'
  };

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  // Callbacks
  var cancelOrderCallbacks = [];
  var confirmOrderCallbacks = [];

  // Cached 'this' pointer
  var _this = this;

  /**
   * Dom nodes
   */
  var cancelPaymentButtonNode = {
    className: 'cancel-payment-button',
    node: null
  };

  var confirmPaymentButtonNode = {
    className: 'confirm-payment-button',
    node: null
  };

  var hoursValueNode = {
    className: 'hours-value-field-label',
    node: null
  };

  var hoursUnitNode = {
    className: 'hours-unit-field-label',
    node: null
  };

  var hourlyRateValueNode = {
    className: 'hourly-rate-field-label',
    node: null
  }; 

  var totalPriceValueNode = {
    className: 'total-price-field-label',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, cancelPaymentButtonNode); 
    Utils.bindNodeInfo(rootNode, confirmPaymentButtonNode); 
    Utils.bindNodeInfo(rootNode, hoursValueNode); 
    Utils.bindNodeInfo(rootNode, hoursUnitNode); 
    Utils.bindNodeInfo(rootNode, hourlyRateValueNode); 
    Utils.bindNodeInfo(rootNode, totalPriceValueNode); 

    // Attach event listeners
    confirmPaymentButtonNode.node.onclick = function() {
      for (var i = 0; i < confirmOrderCallbacks.length; ++i) {
        var callback = confirmOrderCallbacks[i];
        callback(_this);
      } 
    };

    cancelPaymentButtonNode.node.onclick = function() {
      for (var i = 0; i < cancelOrderCallbacks.length; ++i) {
        var callback = cancelOrderCallbacks[i];
        callback(_this);
      } 
    };
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui dom nodes
    bindNodes();
  };

  this.bindCancelOrder = function(callback) {
    cancelOrderCallbacks.push(callback);
    return this;
  };

  this.bindConfirmOrder = function(callback) {
    confirmOrderCallbacks.push(callback);
    return this;
  };

  this.setPricingInformation = function(
    hours_count,
    hourly_rate,
    total_price
  ) {
    hoursValueNode.node.innerHTML = hours_count;
    hoursUnitNode.node.innerHTML = (hours_count == 1)
      ? HOUR_UNIT.singular
      : HOUR_UNIT.plural;
    hourlyRateValueNode.node.innerHTML = hourly_rate;
    totalPriceValueNode.node.innerHTML = total_price;
  };
};

var NewExperimentPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'Add Experiment';

  /**
   * New Experiments Template Id
   */
  var NEW_EXPERIMENT_PAGE_TEMPLATE_ID = 'new-experiment-page-template';

  /**
   * New Experiments Wrapper Class
   */
  var NEW_EXPERIMENT_WRAPPER_CLASS = 'new-experiment-page-wrapper';

  /**
   * Scopes count form view
   */
  var scopesCountNode = {
    className: 'scopes-count-form',
    node: null
  };

  var SCOPES_COUNT_TITLE_LABEL = 'How many scopes would you like?';

  var SCOPES_COUNT_UNIT_LABELS = {
    singular: 'scope',
    plural: 'scopes'
  };

  var SCOPES_COUNT_VALUE_RANGE = {
    min: 0,
    max: 15,
    step: 1
  };

  /**
   * Experiment duration form node 
   */
  var experimentDurationNode = {
    className: 'experiment-duration-form',
    node: null
  };

  var EXPERIMENT_DURATION_TITLE_LABEL = 'How long is your experiment?';

  var EXPERIMENT_DURATION_UNIT_LABELS = {
    singular: 'hour',
    plural: 'hours'
  };

  var EXPERIMENT_DURATION_VALUE_RANGE = {
    min: 0,
    max: 12,
    step: 1
  };

  var experimentDurationController = null;
  
  /**
   * Experiment time form node
   */
  var experimentTimeNode = {
    className: 'experiment-time-form',
    node: null
  };

  /**
   * Short code picker input field
   */
  var shortCodePickerNode = {
    className: 'short-code-form', 
    node: null
  };

  var SHORT_CODE_TITLE_LABEL = 'Select a payment method';

  /**
   * Confirm order form view dom node
   */
  var confirmOrderFormViewNode = {
    className: 'confirm-order-form',
    node: null
  };

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var rootNode = null;

  var scopesCountFormView = null;
  var experimentDurationFormView = null;
  var experimentTimeFormView = null;
  var shortCodePickerFormView = null;
  var confirmExperimentFormView = null;

  /**
   * Private functions
   */
  var initScopeCountView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,
      scopesCountNode.node,
      SCOPES_COUNT_TITLE_LABEL,
      SCOPES_COUNT_UNIT_LABELS
    ); 

    slider_form_view.init();
    return slider_form_view;
  };

  var initExperimentDurationView = function() {
    var slider_form_view = new SliderFormView(
      templateStore,    
      experimentDurationNode.node,
      EXPERIMENT_DURATION_TITLE_LABEL,
      EXPERIMENT_DURATION_UNIT_LABELS
    );

    slider_form_view.init();
    return slider_form_view;
  };

  var initExperimentTimeFormView = function() {
    var form_view = new ExperimentTimeFormView(
      templateStore,
      experimentTimeNode.node
    );

    form_view.init();
    return form_view;
  };

  var initShortCodePickerFormView = function() {
    // Initialize form view
    var form_view = new ShortCodeFormView(
      templateStore,
      shortCodePickerNode.node
    );
    form_view.init();
    return form_view;
  };

  var initConfirmExperimentFormView = function() {
    // Initialize form view
    var form_view = new ConfirmOrderFormView(
      templateStore,
      confirmOrderFormViewNode.node
    );

    form_view.init();
    return form_view;
  };

  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, scopesCountNode);
    Utils.bindNodeInfo(rootNode, experimentDurationNode);
    Utils.bindNodeInfo(rootNode, experimentTimeNode);
    Utils.bindNodeInfo(rootNode, shortCodePickerNode);
    Utils.bindNodeInfo(rootNode, confirmOrderFormViewNode);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      NEW_EXPERIMENT_PAGE_TEMPLATE_ID,
      parentNode,
      NEW_EXPERIMENT_WRAPPER_CLASS
    );

    // Bind all ui dom nodes
    bindNodes();
    
    // Initialize child views
    scopesCountFormView = initScopeCountView(); 
    experimentDurationFormView = initExperimentDurationView();
    experimentTimeFormView = initExperimentTimeFormView();
    shortCodePickerFormView = initShortCodePickerFormView();
    confirmExperimentFormView = initConfirmExperimentFormView();
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };

  this.getScopesCountFormView = function() {
    return scopesCountFormView;
  };
  
  this.getExperimentDurationFormView = function() {
    return experimentDurationFormView;
  };

  this.getExperimentTimeFormView = function() {
    return experimentTimeFormView;   
  };
  
  this.getShortCodeFormView = function() {
    return shortCodePickerFormView;
  };

  this.getConfirmExperimentFormView = function() {
    return confirmExperimentFormView;
  };
};

var ExperimentTimeFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'experiment-time-form-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'experiment-time-form-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var timePickerView = null;
  var datePickerView = null;

  /**
   * Dom nodes
   */
  var experimentTimePickerNode = {
    className: 'exp-time-picker',
    node: null
  };
  
  var experimentDatePickerNode = {
    className: 'exp-date-picker',
    node: null
  };

  /**
   * Private functions
   */
  var initExperimentTimePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentTimePickerNode);

    // Create view
    timePickerView = new DropDownView(
      templateStore,
      experimentTimePickerNode.node
    );

    timePickerView.init('device:access-time');
  };

  var initExperimentDatePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentDatePickerNode);

    // Create view
    datePickerView = new DatePickerView(
      templateStore,
      experimentDatePickerNode.node
    );

    datePickerView.init();
  };

  var initFormElements = function() {
    initExperimentTimePickerView();
    initExperimentDatePickerView();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements 
    initFormElements();
  };

  this.getTimePickerView = function() {
    return timePickerView;
  };

  this.getDatePickerView = function() {
    return datePickerView;
  };
};

var ShortCodeFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'short-code-form-template';

  /**
   * Root wrapper class
   */
  var ROOT_CLASS = 'short-code-form-wrapper';

  /**
   * Short code drop-down icon
   */
  var ICON_NAME = 'payment';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var shortCodePickerView = null;

  /**
   * DOM nodes
   */
  var shortCodePickerNode = {
    className: 'short-code-picker',
    node: null
  };

  /**
   * Private functions
   */
  var initFormElements = function() {
    // Bind short-code drop-down node
    Utils.bindNodeInfo(rootNode, shortCodePickerNode);  

    // Initialize drop-down view
    shortCodePickerView = new DropDownView(
      templateStore,
      shortCodePickerNode.node
    );

    shortCodePickerView.init(ICON_NAME);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements
    initFormElements();
  };

  this.getDropDownView = function() {
    return shortCodePickerView;
  };

};

var SliderFormView = function(
  template_store,
  parent_node,
  title_label,
  unit_labels // {singular, plural}
) {

  /**
   * Template Id
   */
  var TEMPLATE_ID = 'slider-input-form-template';

  /**
   * Wrapper root node
   */
  var WRAPPER_ROOT_NODE_CLASS = 'slider-input-form-wrapper';

  /**
   * Paper slider ui attributes
   */
  var PAPER_SLIDER_MIN_ATTR = 'min';
  var PAPER_SLIDER_MAX_ATTR = 'max';
  var PAPER_SLIDER_STEP_ATTR = 'step';
  var PAPER_SLIDER_VALUE_ATTR = 'value';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var unitLabels = unit_labels;
  var titleLabel = title_label;
  
  var _this = this;

  var rootNode = null;

  var changedValueListeners = [];

  /**
   * Dom node info
   */
  var formTitleNode = {
    class_name: 'form-title-label',
    node: null
  };

  var valueDisplayNode = {
    class_name: 'value-display',
    node: null
  };

  var unitDisplayNode = {
    class_name: 'unit-display',
    node: null
  };

  var sliderNode = {
    class_name: 'slider-input',
    node: null
  };

  var bindNodes = function() {
    // Bind nodes
    formTitleNode.node = Utils.bindNode(rootNode, formTitleNode.class_name); 
    valueDisplayNode.node = Utils.bindNode(rootNode, valueDisplayNode.class_name); 
    unitDisplayNode.node = Utils.bindNode(rootNode, unitDisplayNode.class_name); 
    sliderNode.node = Utils.bindNode(rootNode, sliderNode.class_name); 

    // Bind onchange event listeners
    sliderNode.node.onchange = function() {
     
      // Update display
      _this.setValue(this.immediateValue);  
     
      // Notify listeners
      for (var i = 0; i < changedValueListeners.length; ++i) {
        changedValueListeners[i](this.immediateValue);
      }
    };
  };

  var initUi = function() {
    // Initialize slider
    formTitleNode.node.innerHTML = titleLabel;
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize root node
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      WRAPPER_ROOT_NODE_CLASS
    );

    // Initialize nodes and bind event listeners
    bindNodes();

    // Init ui elements (e.g. form title)
    initUi();
  };

  this.setValue = function(value) {
    // Update slider
    sliderNode.node.value = value;  

    // Update value display
    valueDisplayNode.node.innerHTML = value; 

    // Update unit display
    unitDisplayNode.node.innerHTML = (value == 1)
      ? unitLabels.singular
      : unitLabels.plural;
  };

  this.setMinValue = function(min_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MIN_ATTR, min_value); 
  };

  this.setMaxValue = function(max_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MAX_ATTR, max_value); 
  };

  this.setStep = function(step) {
    sliderNode.node.setAttribute(PAPER_SLIDER_STEP_ATTR, step); 
  };

  this.bindValueChange = function(callback) {
    changedValueListeners.push(callback);  
  };
};
