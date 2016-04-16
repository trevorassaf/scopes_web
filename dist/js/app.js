window.onload = function() {

  document.execCommand('defaultParagraphSeparator', false, 'p');

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Initialize pages
   */
  var center_page_node = document.getElementById('center-panel');

  var center_page_view = new CenterPageView(
    template_store,
    center_page_node
  );
  center_page_view.init();
  center_page_view.showNewExperimentPage();

  // New experiment page
  // var new_experiment_parent_node = null;
  // var new_experiment_page_view = new NewExperimentPageView(
  //   template_store,
  //   page_parent_node
  // );
  //
  // new_experiment_page_view.init();

  // Initialize side panel
  var side_panel_parent_root = document.getElementById('side-panel');

  var side_panel_view = new SidePanelView(
    template_store,
    side_panel_parent_root
  );
  side_panel_view.init();
  side_panel_view.selectNewExperimentTab();

  // Initialize page controller
  // var page_controller = new PageController(
  //   side_panel_view,
  //   new_experiment_page_view
  // );
  // page_controller.init();

  // Initialize pages

  // #<{(|*
  //  * Configure UI elements
  //  |)}>#
  // SidePanelUiController.init(template_store);
  //
  // #<{(|*
  //  * Fetch startup data and route to proper views 
  //  |)}>#
  // GetStartupDataApiController.fetch();
  //
  // var my_experiments_view = SidePanelUiController.getMyExperimentsView();
  // MyExperimentsLogicController.init(my_experiments_view);
  //
  // NewExperimentUiController.registerOrderConfirmedListener(function() {
  //   MyExperimentsLogicController.refreshData();
  // });
};

var ConfirmOrderFormController = function() {

  /**
   * Private state
   */
  var confirmOrderView = null;
  var experimentDurationModel = null;
  var pricePerHour = 20;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Bind to experiment-duration change 
    experimentDurationModel.bindCurrentValue(handleNewExperimentDuration);
  };

  var handleNewExperimentDuration = function(experiment_duration) {
    // Calculate price
    var total_price = pricePerHour * experiment_duration;
    confirmOrderView.setPricingInformation(
      experiment_duration,
      pricePerHour,
      total_price
    );
  };


  /**
   * Privileged functions
   */
  this.init = function(
    confirm_order_view,
    experiment_duration_model
  ) {
    confirmOrderView = confirm_order_view;
    experimentDurationModel = experiment_duration_model;

    // Attach models to views
    configureCallbacks(); 
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

    return month_displacement > 0 &&
      month_displacement <= datePickerModel.getMaxAdvanceMonthCount();
  };

  /**
   * Privileged functions
   */
  this.setView = function(view) {
    // Cache view
    datePickerView = view;

    // Bind event listeners
    datePickerView.bindDateSelection(handleDateSelection);
    datePickerView.bindMonthNavigation(handleMonthNavigation);

    return this;
  };

  this.setModel = function(model) {
    datePickerModel = model;
    return this;
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
  var isActive = false;

  /**
   * Protected functions
   */
  var changeTitle = function(title) {
    // Update model
    myExperimentModel.setTitle(title);

    // TODO persist...
  };

  var changeDescription = function(description) {
    // Update model
    myExperimentModel.setDescription(description);

    // TODO persist...
  };

  var deleteExperiment = function() {
    isActive = false;

    myExperimentView.remove();
    
    // TODO... persist
  };

  /**
   * Public functions
   */
  this.init = function(
    template_store,
    parent_node,
    model
  ) {
    // Check: controller must be inactive to initialize!
    console.assert(!isActive);
    this.isActive = true;

    // We need a reference to this model (we don't own!)
    myExperimentModel = model;

    // Create view and bind event listeners
    myExperimentView = new MyExperimentView(
      template_store,
      parent_node
    );

    myExperimentView.registerChangedTitleListener(changeTitle);
    myExperimentView.registerChangedDescriptionListener(changeDescription);


    // Init ui and bind model
    myExperimentView.init(model);
  };

  this.getModel = function() {
    return myExperimentModel;
  };
};

var MyExperimentsPageController = function() {

  /**
   * Private state
   */
  var isActive = false;
  var templateStore = null;
  var parentNode = null;
  var getConfirmedOrdersApiWrapper = null;
  var myExperimentControllers = []; // unordered_map keyed on experiment-id
  var myExperimentsPageView = null;

  /**
   * Private functions
   */
  var update = function(experiment_controller) {};

  var updateLocalExperiment = function(fresh_experiment, stale_experiment_controller) {
    var stale_model = stale_experiment_controller.getModel();

    // Check: must be same experiment!
    console.assert(fresh_experiment.getId() == stale_model.getId());

    // Diff fields and update accordingly
    if (fresh_experiment.getTitle() != stale_model.getTitle()) {
      stale_model.setTitle(fresh_experiment.getTitle());    
    }
    
    if (fresh_experiment.getDescription() != stale_model.getDescription()) {
      stale_model.setDescription(fresh_experiment.getDescription());    
    }

    if (fresh_experiment.getPrice() != stale_model.getPrice()) {
      stale_model.setPrice(fresh_experiment.getPrice());    
    }

    if (fresh_experiment.getScopesCount() != stale_model.getScopesCount()) {
      stale_model.setScopesCount(fresh_experiment.getScopesCount());    
    }

    if (fresh_experiment.getExperimentDuration() != stale_model.getExperimentDuration()) {
      stale_model.setExperimentDuration(fresh_experiment.getExperimentDuration());    
    }

    if (fresh_experiment.getStartTime() != stale_model.getStartTime()) {
      stale_model.setStartTime(fresh_experiment.getStartTime());    
    }

    if (fresh_experiment.getStartDate() != stale_model.getStartDate()) {
      stale_model.setStartDate(fresh_experiment.getStartDate());    
    }
    
    if (fresh_experiment.getPaymentStatus() != stale_model.getPaymentStatus()) {
      stale_model.setPaymentStatus(fresh_experiment.getPaymentStatus());    
    }
  };

  var createNewLocalExperiment = function(fresh_experiment) {
    // Check: can't have order with this id!
    console.assert(!myExperimentController.has(fresh_experiment.getId()));

    // Initialize new model
    var model = (new MyExperimentModel())
      .setId(fresh_experiment.getId())
      .setTitle(fresh_experiment.getTitle())
      .setDescription(fresh_experiment.getDescription())
      .setPrice(fresh_experiment.getPrice())
      .setScopesCount(fresh_experiment.getScopesCount())
      .setExperimentDuration(fresh_experiment.getExperimentDuration())
      .setStartTime(fresh_experiment.getStartTime())
      .setStartDate(fresh_experiment.getStartDate())
      .setPaymentStatus(fresh_experiment.getPaymentStatus())
      .setShortCode(fresh_experiment.getShortCode());

    // Create controller, initialize it, add it to local list
    var controller = new MyExperimentController();
    
    controller.init(
      templateStore,
      parentNode,
      model
    );

    myExperimentControllers.set(model.getId(), controller);
  };

  var fetchExperimentsCallback = function(experiments) {
    for (var i = 0; i < experiments.length; ++i) {
      var fresh_experiment = experiments[i];
      if (myExperimentControllers.has(fresh_experiment.getId())) {
        updateLocalExperiment(fresh_experiment, myExperimentControllers[fresh_experiment.getId()]);   
      } else {
      createNewLocalExperiment(fresh_experiment); 
      }
    }
  };

  var initApi = function() {
    console.assert(getConfirmedOrdersApiWrapper === null); 

    // Initialize get-confirmed-order api
    var get_confirmed_order_api = new GetConfirmedOrdersApi(ScopesNetwork);
    getConfirmedOrdersApiWrapper = new ApiControllerWrapper(get_confirmed_order_api);

    getConfirmedOrdersApiWrapper.registerSuccessfulApiCallback(function(json_response, response_keys) {
      // Deserialize orders
      var orders = json_response[response_keys.orders];
      var order_response_keys = response_keys.confirmed_order;
      var short_code_response_keys = response_keys.short_code;
     
      var confirmed_orders = [];

      for (var i = 0; i < orders.length; ++i) {
        var order = orders[i];
        var short_code = order[order_response_keys.short_code];

        var short_code = new ShortCode(
          short_code[short_code_response_keys.id],
          short_code[short_code_response_keys.code],
          short_code[short_code_response_keys.alias]
        );

        var confirmed_order = new ConfirmedOrder(
          order[order_response_keys.id],
          order[order_response_keys.scopes_count],
          order[order_response_keys.start_time],
          order[order_response_keys.end_time],
          order[order_response_keys.title],
          order[order_response_keys.description],
          order[order_response_keys.time_ordered],
          order[order_response_keys.price],
          short_code
        );
        
        confirmed_orders.push(confirmed_order);
      }

      fetchExperimentsCallback(confirmed_orders);
    });

    getConfirmedOrdersApiWrapper.registerLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders'); 
    });

    getConfirmedOrdersApiWrapper.registerNonLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders due to network error'); 
    });

  };

  /**
   * Privileged functions
   */
  this.refresh = function() {
    var successful_callback = function(experiments) {
      // TODO...
    };

    // Make api call
    fetchExperiments(successful_callback);
  };

  this.init = function(
    template_store,
    parent_node,
    is_displayed_initially
  ) {
    // Check: view must be inactive to initialize!
    console.assert(!isActive);
    isActive = true;

    templateStore = template_store;
    parentNode = parent_node;

    // Initialize view
    myExperimentsPageView = new MyExperimentsPageView(
      template_store,
      parent_node,
      is_displayed_initially
    );
  };

  this.show = function() {};
  this.hide = function() {};
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

var SidePanelController = function(
    template_store,
    new_experiment_page_controller,
    my_experiments_page_controller,
    feedback_page_controller,
    technician_page_controller
) {

  /**
   * Private state
   */
  var sidePanelView = null;
  var templateStore = template_store;

  var newExperimentPageController = new_experiment_page_controller;
  var myExperimentsPageController = my_experiments_page_controller;
  var feedbackPageController = feedback_page_controller;
  var technicianPageController = technician_page_controller;

  /**
   * Privileged functions
   */
  this.init = function() {
    /**
     * Initialize the tab views
     */
    sidePanelView = new SidePanelView(templateStore);
    sidePanelView.init();
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

  this.getModel = function() {
    return sliderModel;
  };

  this.getView = function() {
    return sliderView;
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

  // Privat state
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
    callback(dropDownItemModels);
  });
  return this;
};

// Getters
DropDownModel.prototype.getSelectedItem = function() {
  return this.dropDownItemModels[this.selectedItemIdx];
};

DropDownModel.prototype.getDropDownItemModels = function() {
  return this.dropDownItemModels;
};

var NewExperimentModel = function() {

  this.scopeCountPickerModel = null;
  this.experimentDurationPickerModel = null;
  this.startTimePickerModel = null;
  this.startDatePickerModel = null;
  this.shortCodePickerModel = null;
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

  // State change event listeners
  this.firstNameChangeListeners = [];
  this.lastNameChangeListeners = [];
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

UserModel.prototype.setFirstName = function(first_name) {
  this.firstName = first_name;

  for (var i = 0; i < this.firstNameChangeListeners.length; ++i) {
    this.firstNameChangeListeners[i](firstName);
  }

  return this;
};

UserModel.prototype.setLastName = function(last_name) {
  this.lastName = last_name;

  for (var i = 0; i < this.lastNameChangeListeners.length; ++i) {
    this.lastNameChangeListeners[i](lastName);
  }

  return this;
};

UserModel.prototype.setEmail = function(email) {
  this.email = email;

  for (var i = 0; i < this.emailChangeListeners.length; ++i) {
    this.emailChangeListeners[i](email);
  }

  return this;
};

/**
 * Register event listeners 
 */
UserModel.prototype.bindFirstName = function(callback) {
  this.firstNameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindLastName = function(callback) {
  this.lastNameChangeListeners.push(callback); 
  return this;
};

UserModel.prototype.bindEmail = function(callback) {
  this.emailChangeListeners.push(callback); 
  return this;
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

var Utils = (function() {

  var CLASS_NAME_PROPERTY = "className";

  var HIDDEN_ATTR = 'hidden';

  // Timestamp delimiters
  var DATE_DELIMITER = "-";
  var TIME_DELIMITER = ":";
  var DATE_TIME_SEPERATOR = " ";

  // this.hasClass = function(expected_class, node) {
  //   if (!(CLASS_NAME_PROPERTY in node)) {
  //     return false;
  //   }
  //
  //   var node_class = node[CLASS_NAME_PROPERTY];
  //   var class_idx = node_class.indexOf(expected_class);
  //   
  //   if (class_idx == -1) {
  //     return false;
  //   }
  //
  //   return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
  //     && (expected_class.length + class_idx == node_class.length
  //       || node_class.charAt(expected_class.length + class_idx) == ' ');
  // };

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
  };

  this.showNode = function(node) {
    node.removeAttribute(HIDDEN_ATTR);
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
  };

})();

function ApiControllerWrapper(api_object) {

  /**
   * Private state
   */
  var apiObject = api_object;
  var successfulApiCallbackListeners = [];
  var failedLogicalApiCallbackListeners = [];
  var failedNonLogicalApiCallbackListeners = [];

  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successfulApiCallbackListeners.length; ++i) {
      successfulApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };

  var logicallyFailedApiCallback = function(api_response) {
    for (var i = 0; i < failedLogicalApiCallbackListeners.length; ++i) {
      failedLogicalApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    for (var i = 0; i < failedNonLogicalApiCallbackListeners.length; ++i) {
      failedNonLogicalApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };
  
  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.registerSuccessfulApiCallback = function(callback) {
    successfulApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.registerLogicalFailedApiCallback = function(callback) {
    failedLogicalApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  this.registerNonLogicalFailedApiCallback = function(callback) {
    failedNonLogicalApiCallbackListeners.push(callback);
    return this;
  };
  
  /**
   * fetch()
   * - fetches startup data
   */
  this.fetch = function() {
    // Bind event listeners
    apiObject.setSuccessfulApiCallback(successfulApiCallback);
    apiObject.setLogicalApiFailureCallback(logicallyFailedApiCallback);
    apiObject.setNonLogicalApiFailureCallback(nonLogicallyFailedApiCallback);

    // Fire api request
    apiObject.send();
  };
};

var GetStartupDataApiController = (function() {

  /**
   * Private state
   */
  var getStartupDataApi = null;
  var successfulApiCallbackListeners = [];
  var failedLogicalApiCallbackListeners = [];
  var failedNonLogicalApiCallbackListeners = [];

  /**
   * fetch()
   * - fetches startup data
   */
  var fetch = function() {
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
    fetch: fetch,
    registerSuccessfulApiCallback: registerSuccessfulApiCallback,
    registerLogicalFailedApiCallback: registerLogicalFailedApiCallback,
    registerNonLogicalFailedApiCallback: registerNonLogicalFailedApiCallback
  };
})();

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

var MyExperimentsLogicController = (function() {

  /**
   * Private state
   */
  var myExperiments = [];
  var getConfirmedOrdersApiWrapper = null;
  var myExperimentsView = null;

  /**
   * Private functions
   */
  var initApi = function() {
    console.assert(getConfirmedOrdersApiWrapper === null); 

    // Initialize get-confirmed-order api
    var get_confirmed_order_api = new GetConfirmedOrdersApi(ScopesNetwork);
    getConfirmedOrdersApiWrapper = new ApiControllerWrapper(get_confirmed_order_api);

    // Bind event listeners to get-confirmed-orders api
    getConfirmedOrdersApiWrapper.registerSuccessfulApiCallback(function(json_response, response_keys) {
      clearConfirmedOrders();
      var orders = json_response[response_keys.orders];
      var order_response_keys = response_keys.confirmed_order;
      var short_code_response_keys = response_keys.short_code;
      
      for (var i = 0; i < orders.length; ++i) {
        var order = orders[i];
        var short_code = order[order_response_keys.short_code];

        var short_code = new ShortCode(
          short_code[short_code_response_keys.id],
          short_code[short_code_response_keys.code],
          short_code[short_code_response_keys.alias]
        );

        var confirmed_order = new ConfirmedOrder(
          order[order_response_keys.id],
          order[order_response_keys.scopes_count],
          order[order_response_keys.start_time],
          order[order_response_keys.end_time],
          order[order_response_keys.title],
          order[order_response_keys.description],
          order[order_response_keys.time_ordered],
          order[order_response_keys.price],
          short_code
        );

        addConfirmedOrder(confirmed_order); 
      }
    });

    getConfirmedOrdersApiWrapper.registerLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders'); 
    });

    getConfirmedOrdersApiWrapper.registerNonLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders due to network error'); 
    });
  };

  var addConfirmedOrder = function(confirm_order) {
    // Store in local cache
    myExperiments.push(confirm_order);  

    // Update MyExperiments view
    myExperimentsView.pushPendingOrder(confirm_order);
  };

  var clearConfirmedOrders = function() {
    // Clear local cache
    myExperiments = [];

    // Clear MyExperiments view
    // TODO...   
  };

  var init = function(my_experiments_view) {
    myExperimentsView = my_experiments_view;

    // Initialize api module
    initApi();

    refreshData(); 
  };

  var refreshData = function() {
    myExperimentsView.clearPendingOrders();
    getConfirmedOrdersApiWrapper.fetch(); 
  };

  var getMyExperiments = function() {
    return myExperiments;
  };

  return {
    init: init,
    refreshData: refreshData,
    getMyExperiments: getMyExperiments
  };
})();

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
  this.apiKeys = {
    scopes_count: "scopes-count",
    experiment_duration: "duration",
    start_timestamp: "start-timestamp",
    short_code_id: "short-code-id",
    price: "price"
  };
}

ConfirmOrderApi.prototype.getApiKeys = function() {
  return this.apiKeys; 
};

ConfirmOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.apiKeys.scopes_count] = scopes_count;
  return this;
};

ConfirmOrderApi.prototype.setExperimentDuration = function(duration) {
  this.data[this.apiKeys.experiment_duration] = duration;
  return this;
};

ConfirmOrderApi.prototype.setStartTimestamp = function(start_timestamp) {
  this.data[this.apiKeys.start_timestamp] = start_timestamp;
  return this;
};

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.apiKeys.short_code_id] = short_code_id;
  return this;
};

ConfirmOrderApi.prototype.setPrice = function(price) {
  this.data[this.apiKeys.price] = price;
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
    short_codes: 'short_codes'
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

      console.log(ENDPOINT_PATH);

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
   * Ui tokens
   */
  DATE_DELIMITER = ',';

  /**
   * Private state
   */
  var datePickerModel = null;

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

  var setSelectedDate = function(selected_date) {
    selectedDateLabelNodeInfo.node.innerHTML = "" + selected_date + DATE_DELIMITER; 
  };

  var setSelectedMonth = function(selected_month) {
    selectedMonthLabelNodeInfo.node.innerHTML = SHORT_MONTH_NAMES[selected_month];
  };

  var setSelectedYear = function(selected_year) {
    selectedYearLabelNodeInfo.node.innerHTML = selected_year;
  };

  var setViewedMonth = function(month, year) {
    refreshCalendar(month, year);
  }

  var refreshCalendar = function(month, year) {
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
      first_selectable_date.getDate() + datePickerModel.getMinAdvanceDayCount()
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

      if (Utils.compareDates(first_selectable_date, validation_check_date) > 0 ||
          isInvalidDate(validation_check_date)) {
        date.setAttribute(UNSELECTABLE_DATE_ATTR, '');     
      } 
      
      var date_labels = date.getElementsByClassName(DATE_LABEL_CLASS);
      console.assert(date_labels.length == 1);
      date_labels[0].innerHTML = i;

      ++day_count;
    }
  };

  var isInvalidDate = function(date) {
    // Check if this date's 'day of the week' is marked invalid
    if (Utils.contains(date.getDay(), datePickerModel.getInvalidDaysOfTheWeek())) {
      return true;
    }

    // if (datePickerModel.getInvalidDaysOfTheWeek().includes(date.getDay())) {
    //   return true;
    // }

    // Check if this date is one of the irregular dates marked invalid
    var invalid_dates = datePickerModel.getInvalidDates();
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

  var setMinAdvanceDayCount = function(count) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setMaxAdvanceMonthCount = function(count) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setInvalidDaysOfTheWeek = function(invalid_days) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setInvalidDates = function(dates) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var bindModel = function(date_picker_model) {
    datePickerModel = date_picker_model;
    datePickerModel 
      .bindSelectedDate(setSelectedDate)
      .bindSelectedMonth(setSelectedMonth)
      .bindSelectedYear(setSelectedYear)
      .bindViewedMonth(setViewedMonth)
      .bindMinAdvanceDayCount(setMinAdvanceDayCount)
      .bindMaxAdvanceMonthCount(setMaxAdvanceMonthCount)
      .bindInvalidDaysOfTheWeek(setInvalidDaysOfTheWeek)
      .bindInvalidDates(setInvalidDates);
  };

  /**
   * Privileged functions
   */
  this.init = function(date_picker_model) {
    // Synthesize template into document
    datePickerRootNode = Utils.synthesizeTemplate(
      templateStore,
      MAIN_TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    ); 

    // Bind nodes
    bindNodes();

    // Bind model and init ui
    bindModel(date_picker_model);

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

  var initNewExperimentPage = function() {
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    ); 
    newExperimentPageView.init();
  };

  var initPages = function() {
    initNewExperimentPage(); 
  };

  var bindNodes = function() {
    // Bind page title node
    pageTitleNode.node = Utils.bindNode(
      rootNode,
      pageTitleNode.className
    ); 

    // Bind container node for admin buttons
    adminButtonContainerNode.node = Utils.bindNode(
      rootNode,
      adminButtonContainerNode.className
    );
    
    // Bind node that contains the pages
    centerPanelPageContainerNode.node = Utils.bindNode(
      rootNode,
      centerPanelPageContainerNode.className
    );

    // Initialize pages
    initPages();
  };

  var initPageViews = function() {
    // Init new experiment page view
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );     

    newExperimentPageView.init();
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

  var bindModel = function(drop_down_model) {
    // Bind to model state
    drop_down_model
      .bindSelectedItem(setSelectedItem)
      .bindDropDownItemModels(setDropDownItemModels);
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

  var setSelectedItem = function(drop_down_item) {
    inputFieldLabelNode.node.innerHTML = drop_down_item.getLabel();
  };

  var setDropDownItemModels = function(drop_down_item_models) {
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

  /**
   * Privileged functions 
   */
  this.init = function(
      drop_down_model,
      icon_type
  ) {
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

    // Bind model
    bindModel(drop_down_model);
  };

  this.bindClick = function(callback) {
    onClickCallbacks.push(callback);
  };
};

function FeedbackPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#feedback-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-feedback-page";

  /**
   * Private state
   */
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;
  var feedbackQuestionList = [];

  /**
   * Dom nodes
   */
  // Root node
  var feedbackPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'feedback-page-wrapper',
    node: null 
  };

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
  function synthesizeFeedbackPageTemplate() {
    // Bind feedback-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    feedbackPageRootNode.node.appendChild(page_clone);
  };

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
    bindClassBoundNode(pageWrapperNode);     
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
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }

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
    feedbackPageRootNode.node = document.getElementById(feedbackPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeFeedbackPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the feedback-page
   */
  this.hide = function() {
    feedbackPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the feedback-page
   */
  this.show = function() {
    feedbackPageRootNode.node.removeAttribute(HIDDEN_ATTR);
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

};

function MyExperimentsPageView(
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
      // Unselect previous tab
      currentlySelectedTab.deselect();

      // Select new tab
      currentlySelectedTab = tab_info.tab;
      currentlySelectedTab.select();

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

  this.bindMyExperimentsTabClick = function() {
    myExperimentsInfo.callback_listeners.push(callback); 
  };

  this.bindFeedbackTabClick = function() {
    feedbackInfo.callback_listeners.push(callback); 
  };

  this.bindTechnicianTabClick = function() {
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
    // Initialize and configure slider model
    var slider_model = new SliderModel();
    slider_model
      .setMinValue(0)
      .setMaxValue(15)
      .setStep(1)
      .setCurrentValue(0);

    var slider_form_view = new SliderFormView(
      templateStore,
      scopesCountNode.node,
      SCOPES_COUNT_TITLE_LABEL,
      SCOPES_COUNT_UNIT_LABELS
    ); 

    slider_form_view.init(slider_model);
    return slider_form_view;
  };

  var initExperimentDurationView = function() {
    // Initialize and configure slider model
    var slider_model = new SliderModel();
    slider_model
      .setMinValue(0)
      .setMaxValue(15)
      .setStep(1)
      .setCurrentValue(0);

    var slider_form_view = new SliderFormView(
      templateStore,    
      experimentDurationNode.node,
      EXPERIMENT_DURATION_TITLE_LABEL,
      EXPERIMENT_DURATION_UNIT_LABELS
    );

    slider_form_view.init(slider_model);

    experimentDurationController = new SliderController();
    experimentDurationController.init(
      slider_form_view,
      slider_model
    );

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
   
    // Initialize drop-down model
    var drop_down_model = new DropDownModel();
    var drop_down_items = [
      new DropDownItemModel("SHORT", "SHORT", {}),
      new DropDownItemModel("CODE", "CODE", {}),
      new DropDownItemModel("SHIT", "SHIT", {})
    ];
    drop_down_model.setDropDownItems(drop_down_items);

    // Initialize drop-down model controller
    var drop_down_controller = new DropDownController();
    drop_down_controller.setModel(drop_down_model);

    form_view.init(drop_down_controller);

    return form_view;
  };

  var initConfirmExperimentFormView = function() {
    // Initialize form view
    var form_view = new ConfirmOrderFormView(
      templateStore,
      confirmOrderFormViewNode.node
    );

    form_view.init();

    // Initialize form controller
    var form_controller = new ConfirmOrderFormController();
    form_controller.init(
      form_view,
      experimentDurationController.getModel()
    );
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

  var experimentTimePickerView = null;
  var experimentTimePickerModel = null;
  var experimentTimePickerController = null;

  var experimentDatePickerController = null;

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


    // Create data model
    var drop_down_items = [
      new DropDownItemModel("10:00", "10:00", {}),
      new DropDownItemModel("10:30", "10:30", {}),
      new DropDownItemModel("11:00", "11:00", {})
    ];

    experimentTimePickerModel = new DropDownModel();
    experimentTimePickerModel.setDropDownItems(drop_down_items);

    // Create view
    experimentTimePickerView = new DropDownView(
      templateStore,
      experimentTimePickerNode.node
    );

    experimentTimePickerView.init(
      experimentTimePickerModel,
      'device:access-time'
    );

    // Create controller
    experimentTimePickerController = new DropDownController();
    experimentTimePickerController
      .setModel(experimentTimePickerModel)
      .setView(experimentTimePickerView);

    // Initialize view
    // experimentTimePickerView = new TimePicker(
    //   templateStore,
    //   experimentTimePickerNode.node,
    //   {minutes: 0, hours: 10},
    //   {minutes: 0, hours: 19},
    //   30
    // ); 
    //
    // experimentTimePickerView.init();
  };

  var initExperimentDatePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentDatePickerNode);

    // Create data model
    var min_advance_day_count = 14;
    var max_advance_month_count = 4;
    var invalid_days_of_the_week = [0, 6];
    var invalid_dates = [
      new Date(2016, 4, 3),
      new Date(2016, 4, 4),
      new Date(2016, 4, 5)
    ];

    // Determine first open date
    var starting_date = new Date();
    starting_date.setDate(
        starting_date.getDate() + min_advance_day_count
    );

    while (
      Utils.contains(starting_date.getDay(), invalid_days_of_the_week) ||
      Utils.contains(starting_date, invalid_dates)    
    ) {
      starting_date.setDate(starting_date.getDate() + 1); 
      // TODO handle case in which NO legal starting dates exist!
    }

    
    // Create model
    var date_picker_model = new DatePickerModel();
    date_picker_model
      .setSelectedDate(starting_date.getDate())
      .setSelectedMonth(starting_date.getMonth())
      .setSelectedYear(starting_date.getFullYear())
      .setViewedMonthAndYear(
        starting_date.getMonth(),
        starting_date.getFullYear()
      )
      .setMinAdvanceDayCount(min_advance_day_count)
      .setMaxAdvanceMonthCount(max_advance_month_count)
      .setInvalidDaysOfTheWeek(invalid_days_of_the_week)
      .setInvalidDates(invalid_dates);

    // Create view
    var date_picker_view = new DatePickerView(
      templateStore,
      experimentDatePickerNode.node
    );

    date_picker_view.init(date_picker_model);

    // Initialize controller
    experimentDatePickerController = new DatePickerController();   
    experimentDatePickerController
      .setModel(date_picker_model)
      .setView(date_picker_view);
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
  var initFormElements = function(drop_down_controller) {
    // Bind short-code drop-down node
    Utils.bindNodeInfo(rootNode, shortCodePickerNode);  

    // Initialize drop-down view
    shortCodePickerView = new DropDownView(
      templateStore,
      shortCodePickerNode.node
    );

    shortCodePickerView.init(
      drop_down_controller.getModel(),
      ICON_NAME
    );

    drop_down_controller.setView(shortCodePickerView);
  };


  /**
   * Privileged functions
   */
  this.init = function(drop_down_controller) {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements
    initFormElements(drop_down_controller);
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

  var setMinValue = function(min_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MIN_ATTR, min_value); 
  };

  var setMaxValue = function(max_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MAX_ATTR, max_value); 
  };

  var setStep = function(step) {
    sliderNode.node.setAttribute(PAPER_SLIDER_STEP_ATTR, step); 
  };

  var initUi = function() {
    // Initialize slider
    formTitleNode.node.innerHTML = titleLabel;
  };

  var bindModel = function(slider_model) {
    slider_model
      .bindMinValue(setMinValue)
      .bindMaxValue(setMaxValue)
      .bindStep(setStep)
      .bindCurrentValue(_this.setValue);
  };

  /**
   * Privileged functions
   */
  this.init = function(slider_model) {
    // Initialize root node
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      WRAPPER_ROOT_NODE_CLASS
    );

    // Initialize nodes and bind event listeners
    bindNodes();

    // Bind model and init ui
    bindModel(slider_model);

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

  this.bindValueChange = function(callback) {
    changedValueListeners.push(callback);  
  };
};
