var MyExperimentsPageController = function() {

  /**
   * Private state
   */
  var myExperimentsControllers = new Map(); // Map<int id, Obj MyExperimentController>
  var getConfirmedOrdersApiWrapper = null;

  var myExperimentsPageView = null;
  var myExperimentsPageModel = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathway
    myExperimentsPageModel.bindAddExperiment(handleNewExperiment);     
    myExperimentsPageModel.bindRemoveExperiment(handleRemoveExperiment);
    myExperimentsPageModel.bindSetExperiments(handleSetExperiments);
  };

  var handleNewExperiment = function(experiment_model) {
    // Create new-experiment ui element and bind to controller
    var experiment_view = myExperimentsPageView.spawnNewExperiment();
    var experiment_controller = new MyExperimentController();
    experiment_controller.init(
      experiment_view,
      experiment_model
    );

    // Cache controller
    myExperimentsControllers.set(
      experiment_model.getId(),
      experiment_controller  
    );

    experiment_view.init();
  };

  // TODO
  var handleRemoveExperiment = function(experiment_model) {};
 

  var handleSetExperiments = function(experiments) {
    // Delete all previous experiments in ui
    myExperimentsPageView.removeExperiments(); 

    // Render new experiments
    experiments.forEach(handleNewExperiment);
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    myExperimentsPageView = view; 
    myExperimentsPageModel = model; 

    configureCallbacks();
  };
};
