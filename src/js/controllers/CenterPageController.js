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

  var handleConfirmOrder = function() {
    var new_experiment_model = newExperimentPageController.getModel();  
    
    // Time input
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

    // Short code
    var short_code_model = new_experiment_model.getShortCodePickerModel(); 
    var selected_short_code_model = short_code_model.getSelectedItem();
    
    var experiment_model = new MyExperimentModel(
      0,
      null,
      null,
      new_experiment_model.getScopesCountModel().getCurrentValue(),
      new_experiment_model.getExperimentDurationModel().getCurrentValue(),
      start_time,
      selected_short_code_model.getLabel(),
      "Pending",
      "Pending"
    );

    var my_experiments_page_model = centerPageModel.getMyExperimentsPageModel();
    my_experiments_page_model.addExperiment(experiment_model);
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
