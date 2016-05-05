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
    var confirm_order_form_view = newExperimentPageView.getConfirmExperimentFormView();
    var experiment_duration_model = newExperimentPageModel.getExperimentDurationModel();

    confirmOrderController = new ConfirmOrderController();
    confirmOrderController
      .bindConfirmOrder(handleConfirmOrder)
      .bindCancelOrder(handleCancelOrder)
      .init(
        confirm_order_form_view,
        experiment_duration_model
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

  var configureStartupDataApi = function() {
    var startup_data_api = apiController.getGetStartupDataApiController();

    startup_data_api.bindSuccess(function(json_response, api_keys) {
      // Set max scopes
      routeMaxScopesApiField(json_response[api_keys.max_scopes]);

      // Set max experiment duration
      routeMaxExperimentDurationApiField(json_response[api_keys.max_hours]);

      // Set short codes
      routeShortCodeApiField(
        json_response[api_keys.short_codes],
        api_keys.short_code_fields
      );
      
      // Set starting/ending time and time interval
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
