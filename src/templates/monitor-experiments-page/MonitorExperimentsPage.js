function MonitorExperimentsPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#monitor-experiments-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-monitor-experiments-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Root node
  var monitorExperimentsPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'monitor-experiments-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = monitorExperimentsPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeMonitorExperimentsPageTemplate()
   * - copy monitor-experiments-page template and insert into main dom tree
   * @pre-condition: 'monitorExperimentsPageRootNode' must be initialized
   */
  function synthesizeMonitorExperimentsPageTemplate() {
    // Bind monitor-experiments-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    monitorExperimentsPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = monitorExperimentsPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
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
   * - initialize monitor experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level monitor-experiments-page node (we're going to copy the template into this!)
    monitorExperimentsPageRootNode.node = document.getElementById(monitorExperimentsPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeMonitorExperimentsPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the monitor-experiments-page
   */
  this.hide = function() {
    monitorExperimentsPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the monitor-experiments-page
   */
  this.show = function() {
    monitorExperimentsPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

};
