var MyExperimentDescriptionPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-description-template'; 

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-description-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Attach event listeners
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
};
