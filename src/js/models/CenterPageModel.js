var CenterPageModel = function() {

  /**
   * Private state
   */
  var newExperimentPageModel = null;

  /**
   * Private functions
   */
  var initNewExperimentPageModel = function() {
    newExperimentPageModel = new NewExperimentPageModel();
    newExperimentPageModel.init();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    initNewExperimentPageModel();
  };

  // Getters
  this.getNewExperimentPageModel = function() {
    return newExperimentPageModel;
  };
};
