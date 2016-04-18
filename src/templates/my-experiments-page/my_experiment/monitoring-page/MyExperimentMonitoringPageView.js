var MyExperimentMonitoringPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-monitor-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-monitor-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

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
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };
};
