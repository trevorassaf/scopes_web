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

    var experiment_model = new MyExperimentModel(
      0,
      'Title',
      'Description',
      10,
      5,
      null,
      null,
      null,
      0,
      0,
      null,
      null
    );

    var my_experiments_page_model = centerPageModel.getMyExperimentsPageModel();
    my_experiments_page_model.addExperiment(experiment_model);
  };

  this.showFeedbackPage = function() {
    centerPageView.showFeedbackPage();
  };

  this.showTechnicianPage = function() {
    centerPageView.showTechnicianPage();
  };
};
