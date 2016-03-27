var CenterPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template node id
   */
  var TEMPLATE_ID = 'center-page-template';

  /**
   * Root node class name
   */
  var ROOT_NODE_CLASS = 'center-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var rootNode = null;

  var newExperimentPageView = null;

  /**
   * Dom nodes
   */
  var pageTitleNode = {
    className: 'center-page-title-label',
    node: null
  };

  var centerPanelPageContainerNode = {
    className: 'center-panel-page-container',
    node: null
  };

  var adminButtonContainerNode = {
    className: 'admin-btn-container',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    pageTitleNode.node = Utils.bindNode(
      rootNode,
      pageTitleNode.className
    ); 

    centerPanelPageContainerNode.node = Utils.bindNode(
      rootNode,
      centerPanelPageContainerNode.className
    );

    adminButtonContainerNode.node = Utils.bindNode(
      rootNode,
      adminButtonContainerNode.className
    );
  };

  var initPageViews = function() {
    // Init new experiment page view
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );     

    newExperimentPageView.init();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_NODE_CLASS
    );

    bindNodes();

    return this;
  };

  this.setTitle = function(title) {
    pageTitleNode.node.innerHTML = title;
    return this;
  };
};
