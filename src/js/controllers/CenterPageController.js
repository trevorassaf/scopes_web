var CenterPageController = function() {

  /**
   * Private state
   */
  // Child controllers
  var newExperimentPageController = null;
  var myExperimentsPageController = null;
  var technicianPageController = null;
  var apiController = null;

  // Models
  var centerPageModel = null;

  // Views
  var centerPageView = null;

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

  var createShadowMyExperimentModel = function(
    scopes_count,
    experiment_duration,
    start_time,
    short_code
  ) {
    // Make deep copy of the complex parameters!
    var start_time_copy = new Date(start_time.getTime());
    var short_code_copy = short_code.deepCopy();

    // Create new my experiment shadow
    var new_my_experiment_shadow_model = new NewMyExperimentModelBuilder()
      .setScopesCount(scopes_count)
      .setExperimentDuration(experiment_duration)
      .setStartTime(start_time_copy)
      .setShortCode(short_code_copy)
      .build();

    return new_my_experiment_shadow_model;
  };

  var persistNewExperiment = function(
    scopes_count,
    experiment_duration,
    start_time,
    short_code,
    new_my_experiment_shadow_model 
  ) {

    var confirm_order_api = new ConfirmOrderApi(ScopesNetwork);
    confirm_order_api
      .setScopesCount(scopes_count)
      .setExperimentDuration(experiment_duration)
      .setStartTimestamp()
      .setShortCodeId(short_code.getId());
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
      selected_time_model.getData().hour,
      selected_time_model.getData().minute
    );

    // Short code data
    var short_code_picker_model = new_experiment_model.getShortCodePickerModel(); 
    var short_code_model = short_code_picker_model.getSelectedItem();
    var short_code = short_code_model.getData();

    var new_my_experiment_shadow_model = createShadowMyExperimentModel(
      scopes_count,
      experiment_duration,
      start_time,
      short_code
    );

    // Update ui and navigate user to my-experiments page
    // TODO...
    
    // Send new experiment request to server
    persistNewExperiment(
      scopes_count,
      experiment_duration,
      start_time,
      short_code,
      new_my_experiment_shadow_model
    );

    // var experiment_model = new MyExperimentModel(
    //   0,
    //   null,
    //   null,
    //   new_experiment_model.getScopesCountModel().getCurrentValue(),
    //   new_experiment_model.getExperimentDurationModel().getCurrentValue(),
    //   start_time,
    //   selected_short_code_model.getLabel(),
    //   "Pending",
    //   "Pending"
    // );
    //
    // var my_experiments_page_model = centerPageModel.getMyExperimentsPageModel();
    // my_experiments_page_model.addExperiment(experiment_model);
  };

  var initMyExperimentsPageController = function() {
    myExperimentsPageController = new MyExperimentsPageController();
    myExperimentsPageController.init(
      centerPageView.getMyExperimentsPageView(),
      centerPageModel.getMyExperimentsPageModel()
    );

    var start_time = new Date(2016, 2, 29, 10);

    var preloaded_experiment_model = new MyExperimentModel(
      1,
      "Angiogenesis Exp. #5",
      null,
      4,
      3,
      start_time,
      "SHORT",
      "Complete",
      "Complete"
    );
    
    var my_experiments_page_model = centerPageModel.getMyExperimentsPageModel();
    my_experiments_page_model.addExperiment(preloaded_experiment_model);
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
};
