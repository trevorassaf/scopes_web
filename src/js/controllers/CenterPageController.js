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

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    centerPageView = view;
    centerPageModel = model;

    // Initialize child controllers
    initNewExperimentPageController();
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
