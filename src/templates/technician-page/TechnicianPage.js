function TechnicianPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#technician-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-technician-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Root node
  var TechnicianPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'technician-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeTechnicianPageTemplate()
   * - copy technician-page template and insert into main dom tree
   * @pre-condition: 'TechnicianPageRootNode' must be initialized
   */
  function synthesizeTechnicianPageTemplate() {
    // Bind technician-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    TechnicianPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(internal_node.className);
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
   * - initialize technician page and put it in starting state
   */
  this.init = function() {
    // Bind top-level technician-page node (we're going to copy the template into this!)
    TechnicianPageRootNode.node = document.getElementById(TechnicianPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeTechnicianPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the technician-page
   */
  this.hide = function() {
    TechnicianPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the technician-page
   */
  this.show = function() {
    TechnicianPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

};
