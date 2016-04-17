var CenterPageModel = function() {

  /**
   * Private state
   */
  var newExperimentPageModel = null;
  var myExperimentsPageModel = null;

  /**
   * Private functions
   */
  var initNewExperimentPageModel = function() {
    newExperimentPageModel = new NewExperimentPageModel();
    newExperimentPageModel.init();
  };

  var initMyExperimentsPageModel = function() {
    myExperimentsPageModel = new MyExperimentsPageModel();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    initNewExperimentPageModel();
    initMyExperimentsPageModel();
  };

  // Getters
  this.getNewExperimentPageModel = function() {
    return newExperimentPageModel;
  };

  this.getMyExperimentsPageModel = function() {
    return myExperimentsPageModel;
  };
};
