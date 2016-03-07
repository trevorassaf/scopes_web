function SidePanelTab(
  template_store,
  parent_node,
  button_title,
  iron_icon_type
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = "#side-panel-tab-template";

  /**
   * Ui attributes
   */
  var SELECTED_ATTR = "selected-side-panel-tab";
  var IRON_ICON_TYPE_ATTR = "icon";

  /**
   * Private state
   */
  var _this = this;
  var templateStore = template_store;
  var buttonTitle = button_title;
  var ironIconType = iron_icon_type;
  var onClickListeners = [];

  // Root dom node
  var rootNode = {
    className: 'dash-nav-panel-btn',
    node: null
  };

  var ironIconNode = {
    className: 'nav-btn-icon',
    node: null
  };

  var buttonTitleNode = {
    className: 'nav-btn-label',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = rootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  function synthesizeSidePanelTemplate() {
    var tab_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var tab_clone = document.importNode(tab_template.content, true);
    parent_node.appendChild(tab_clone);

    // Initialize root node and configure event listener
    var tabs = parent_node.getElementsByClassName(rootNode.className);
    rootNode.node = tabs[tabs.length - 1];

    rootNode.node.onclick = function() {
      for (var i = 0; i < onClickListeners.length; ++i) {
        onClickListeners[i]();
      }
    };
  };

  /**
   * bindInternalNodes()
   * @pre-condition: 'rootNode' must already be bound
   */
  function bindInternalNodes() {
    bindClassBoundNode(ironIconNode); 
    bindClassBoundNode(buttonTitleNode);
  };

  /**
   * initDisplay()
   * - initializes text/graphics for this tab
   * @pre-condition: all internal nodes bound
   */
  function initDisplay() {
    ironIconNode.node.setAttribute(IRON_ICON_TYPE_ATTR, ironIconType);
    buttonTitleNode.node.innerHTML = buttonTitle; 
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize template and append to parent dom node
    synthesizeSidePanelTemplate();

    // Initialize pointers to internal nodes
    bindInternalNodes();

    // Initialize the ui
    initDisplay();
  }; 

  this.select = function() {
    rootNode.node.setAttribute(SELECTED_ATTR, ''); 
  };

  this.deselect = function() {
    rootNode.node.removeAttribute(SELECTED_ATTR);
  };

  /**
   * registerOnClickListener()
   * @param FuncPtr callback: function(_this) {...}
   */
  this.registerOnClickListener = function(callback) {
    onClickListeners.push(callback); 
  };
};
