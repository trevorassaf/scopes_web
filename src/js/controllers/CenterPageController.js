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
