var MyExperimentController = function() {

  /**
   * Private state
   */
  var myExperimentView = null;
  var myExperimentModel = null; 
  var isActive = false;

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

  /**
   * Public functions
   */
  this.init = function(
    template_store,
    parent_node,
    model
  ) {
    // Check: controller must be inactive to initialize!
    console.assert(!isActive);
    this.isActive = true;

    // We need a reference to this model (we don't own!)
    myExperimentModel = model;

    // Create view and bind event listeners
    myExperimentView = new MyExperimentView(
      template_store,
      parent_node
    );

    myExperimentView.registerChangedTitleListener(changeTitle);
    myExperimentView.registerChangedDescriptionListener(changeDescription);


    // Init ui and bind model
    myExperimentView.init(model);
  };

  this.getModel = function() {
    return myExperimentModel;
  };
};
