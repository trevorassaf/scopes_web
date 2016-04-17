var MyExperimentFrontPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-front-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-front-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Private functions
   */
  var bindNodes = function() {
    
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
};
