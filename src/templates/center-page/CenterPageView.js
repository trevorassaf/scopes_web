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

  var currentPageView = null;

  var newExperimentPageView = null;
  var myExperimentsPageView = null;
  var feedbackPageView = null;
  var technicianPageView = null;

  /**
   * Dom nodes
   */
  var pageTitleNode = {
    className: 'title-label',
    node: null
  };

  var centerPanelPageContainerNode = {
    className: 'page-container',
    node: null
  };

  var adminButtonContainerNode = {
    className: 'admin-btn-container',
    node: null
  };

  /**
   * Private functions
   */

  var initNewExperimentPage = function() {
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    ); 
    newExperimentPageView.init();
  };

  var initPages = function() {
    initNewExperimentPage(); 
  };

  var bindNodes = function() {
    // Bind page title node
    pageTitleNode.node = Utils.bindNode(
      rootNode,
      pageTitleNode.className
    ); 

    // Bind container node for admin buttons
    adminButtonContainerNode.node = Utils.bindNode(
      rootNode,
      adminButtonContainerNode.className
    );
    
    // Bind node that contains the pages
    centerPanelPageContainerNode.node = Utils.bindNode(
      rootNode,
      centerPanelPageContainerNode.className
    );

    // Initialize pages
    initPages();
  };

  var initPageViews = function() {
    // Init new experiment page view
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );     

    newExperimentPageView.init();
  };

  var changePage = function(next_page_view) {
    console.assert(next_page_view != null);

    // Hide current page
    if (currentPageView != null) {
      currentPageView.hide();
    }

    // Show next page and update title
    currentPageView = next_page_view;
    pageTitleNode.node.innerHTML = currentPageView.getTitle();
    currentPageView.show();
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

  /**
   * Functions for showing main pages
   */
  this.showNewExperimentPage = function() {
    changePage(newExperimentPageView);       
  };

  this.showMyExperimentsPage = function() {
    changePage(myExperimentsPageView);       
  };

  this.showFeedbackPage = function() {
    changePage(feedbackPageView);       
  };

  this.showTechnicianPage = function() {
    changePage(technicianPageView);       
  };
};
