function MyExperimentsPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var WRAPPER_TEMPLATE_ID_SELECTOR = '#my-experiments-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-my-experiments-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Pending experiment views
  var pendingExperimentViews = [];

  // Root node
  var myExperimentsPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'my-experiments-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeMyExperimentsPageTemplate()
   * - copy my-experiments-page template and insert into main dom tree
   * @pre-condition: 'myExperimentsPageRootNode' must be initialized
   */
  function synthesizeMyExperimentsPageTemplate() {
    // Bind my-experiments-page dom template
    var page_template = templateStore.import.querySelector(WRAPPER_TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    myExperimentsPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    // Bind internal nodes
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize my experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level my-experiments-page node (we're going to copy the template into this!)
    myExperimentsPageRootNode.node = document.getElementById(myExperimentsPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeMyExperimentsPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the my-experiments-page
   */
  this.hide = function() {
    pageWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the my-experiments-page
   */
  this.show = function() {
    pageWrapperNode.node.removeAttribute(HIDDEN_ATTR);
  };

  this.pushPendingOrder = function(confirmed_order) {
    var pending_experiment_view = new PendingExperimentView(
      templateStore,
      pageWrapperNode.node
    );     

    pendingExperimentViews.push(pending_experiment_view);

    pending_experiment_view.init(confirmed_order);
  };

  this.clearPendingOrders = function() {
    pendingExperimentViews = [];
    Utils.removeDomChildren(pageWrapperNode.node);
  };
};
