var NewExperimentPageController = function() {
  
  /**
   * Private state
   */
  // Child controllers
  var scopesCountController = null;
  var experimentDurationController = null;
  var experimentTimePickerController = null;
  var experimentDatePickerController = null;
  var shortCodePickerController = null;

  // Model and view
  var newExperimentPageModel = null;
  var newExperimentPageView = null;

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

  /**
   * Private functions
   */
  this.init = function(model, view) {
    // TODO, handle case where init is called twice (model and view already bound)
    newExperimentPageModel = model;
    newExperimentPageView = view;

    // Initialize child controllers
    scopesCountController = initScopesCountController();
    experimentDurationController = initExperimentDurationController();
    experimentTimePickerController = initExperimentTimePickerController();
    experimentDatePickerController = initExperimentDatePickerController();
    shortCodePickerController = initShortCodePickerController();
  };
};
