function PendingExperimentView(
  template_store,
  parent_node
) {

  /**
   * Default values 
   */
  var DEFAULT_TITLE = 'Untitled';

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#pending-experiment-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'pending-experiment-wrapper',
    node: null
  };

  var titleNode = {
    className: 'title-label',
    node: null
  };
  
  var scopesCountNode = {
    className: 'scopes-count-label',
    node: null
  };

  var startDateNode = {
    className: 'start-date-label',
    node: null
  };

  var startTimeNode = {
    className: 'start-time-label',
    node: null
  };

  var durationNode = {
    className: 'duration-label',
    node: null
  };

  var descriptionNode = {
    className: 'description-label',
    node: null
  };

  var timeOrderedNode = {
    className: 'time-ordered-label',
    node: null
  };

  var priceNode = {
    className: 'price-label',
    node: null
  };

  var shortCodeNode = {
    className: 'short-code-label',
    node: null
  };

  /**
   * Private functions
   */
  function synthesizeTemplate() {
    // Clone pending-order template
    var pending_order_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var pending_order_clone = document.importNode(pending_order_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(pending_order_clone); 
    var pending_order_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = pending_order_list[pending_order_list.length - 1];
  };

  function setTitle(title) {
    if (title == null || title == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
    } else {
      titleNode.node.innerHTML = title; 
    }
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var bindInternalNodes = function() {
    bindClassBoundNode(titleNode); 
    bindClassBoundNode(scopesCountNode); 
    bindClassBoundNode(startDateNode); 
    bindClassBoundNode(startTimeNode); 
    bindClassBoundNode(durationNode); 
    bindClassBoundNode(descriptionNode); 
    bindClassBoundNode(timeOrderedNode); 
    bindClassBoundNode(priceNode); 
    bindClassBoundNode(shortCodeNode); 
  };

  /**
   * Privileged functions
   */
  this.init = function(confirmed_order) {
    // Clone template and copy into pending-experiments list
    synthesizeTemplate();

    // Init dom pointers to internal nodes
    bindInternalNodes();

    // Place data in proper ui elements
    setTitle(confirmed_order.getTitle());
  };
};
