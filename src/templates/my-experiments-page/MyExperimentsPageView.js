var MyExperimentsPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'My Experiments';

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiments-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiments-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize my-experiments page 
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );
  };

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.spawnNewExperiment = function() {
    var my_experiment_view = new MyExperimentView(
      templateStore,
      rootNode
    ); 

    my_experiment_view.init();
    return my_experiment_view;
  };

  this.removeExperiments = function() {
    Utils.removeDomChildren(rootNode);
  };
};
