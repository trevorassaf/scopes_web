var CenterPageController = function() {

  /**
   * Private state
   */
  // Child controllers
  var newExperimentPageController = null;

  var centerPageModel = null;
  var centerPageView = null;

  /**
   * Private functions
   */
  var initNewExperimentPageController = function() {
    newExperimentPageController = new NewExperimentPageController();
    newExperimentPageController.init(
      centerPageModel.getNewExperimentPageModel(),
      centerPageView.getNewExperimentPageView()
    );

    newExperimentPageController.bindConfirmOrder(handleConfirmOrder);
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
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    centerPageView = view;
    centerPageModel = model;

    // Initialize child controllers
    initNewExperimentPageController();
    initMyExperimentsPageController();
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
