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

  var initNewExperimentPageView = function() {
    newExperimentPageView = new NewExperimentPageView(
      templateStore,
      centerPanelPageContainerNode.node
    ); 
    newExperimentPageView.init();
  };

  var initMyExperimentsPageView = function() {
    myExperimentsPageView = new MyExperimentsPageView(
      templateStore,
      centerPanelPageContainerNode.node
    );
    myExperimentsPageView.init();
  };

  var initPages = function() {
    initNewExperimentPageView(); 
    initMyExperimentsPageView();
  };

  var bindNodes = function() {
    // Bind page nodes
    Utils.bindNodeInfo(rootNode, pageTitleNode);
    Utils.bindNodeInfo(rootNode, adminButtonContainerNode);
    Utils.bindNodeInfo(rootNode, centerPanelPageContainerNode);

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
    // Synthesize template into document and initialize
    // root DOM element
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_NODE_CLASS
    );

    // Bind ui elements and attach event listeners
    bindNodes();
    
    // Initialize pages
    initPages();

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

  this.getNewExperimentPageView = function() {
    return newExperimentPageView;
  };

  this.getMyExperimentsPageView = function() {
    return myExperimentsPageView;
  };
};
