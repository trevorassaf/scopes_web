var MyExperimentController = function() {

  /**
   * Private state
   */
  var myExperimentView = null;
  var myExperimentModel = null; 

  /**
   * Protected functions
   */
  var changeTitle = function(title) {
    // Update model
    myExperimentModel.setTitle(title);

    // TODO persist...
  };

  var changeDescription = function(description) {
    // Update model
    myExperimentModel.setDescription(description);

    // TODO persist...
  };

  var deleteExperiment = function() {
    isActive = false;

    myExperimentView.remove();
    
    // TODO... persist
  };

  var configureCallbacks = function() {
     
  };

  /**
   * Privileged functions
   */
  this.init = function(
    view,
    model
  ) {
    myExperimentView = view;
    myExperimentModel = model;

    configureCallbacks();
  };
};
