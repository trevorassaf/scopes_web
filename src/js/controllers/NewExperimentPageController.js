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

  var configureStartupDataApi = function() {
    var startup_data_api = apiController.getGetStartupDataApiController();

    startup_data_api.bindSuccess(function(json_response, api_keys) {
      // Set max scopes
      var scopes_count_model = scopesCountController.getModel();
      scopes_count_model.setMaxValue(json_response[api_keys.max_scopes]);

      // Set max experiment duration
      var experiment_duration_model = experimentDurationController.getModel();
      experiment_duration_model.setMaxValue(json_response[api_keys.max_hours]);

      // Set short codes
      var short_codes_model = shortCodePickerController.getModel();

      var short_codes = json_response[api_keys.short_codes];
      var drop_down_item_models = [];

      for (var i = 0; i < short_codes.length; ++i) {
        var json_short_code = short_codes[i];
        var short_code = new ShortCode(
          json_short_code[api_keys.short_code_fields.id],
          json_short_code[api_keys.short_code_fields.code],
          json_short_code[api_keys.short_code_fields.alias]
        );

        var drop_down_item_model = new DropDownItemModel(
          short_code.getAlias(),
          short_code.getCode(),
          short_code
        );

        drop_down_item_models.push(drop_down_item_model);
      }

      short_codes_model.setDropDownItems(drop_down_item_models);
      
      
      // Set invalid dates
      
      // Set starting/ending time and time interval
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
