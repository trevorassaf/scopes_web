var DropDownItemView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'dropdown-item-template';

  /**
   * Root wrapper class
   */
  var ROOT_WRAPPER_CLASS = 'dropdown-item-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var dropDownItemRootNode = null;
  var dropDownItemIndex = null;
  var onClickCallbacks = [];

  /**
   * Dom nodes
   */
  var itemLabelNode = {
    className: 'item-label',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind item label node
    itemLabelNode.node = Utils.bindNode(
      dropDownItemRootNode,
      itemLabelNode.className
    );      

    // Configure onclick event listener
    dropDownItemRootNode.onclick = function() {
      onClickCallbacks.forEach(function(callback) {
        callback(dropDownItemIndex); 
      });
    };
  };

  var setLabel = function(label) {
    itemLabelNode.node.innerHTML = label;    
  };

  var setTooltip = function(tooltip) {
    // TODO...
  };

  var bindModel = function(drop_down_item_model) {
    drop_down_item_model
      .bindLabel(setLabel)
      .bindTooltip(setTooltip);
  };

  /**
   * Privileged functions
   */
  this.init = function(index, drop_down_item_model) {
    // Synthesize template into document
    dropDownItemRootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    ); 
    
    dropDownItemIndex = index;

    // Bind nodes and configure event listeners
    bindNodes();

    // Bind model and init ui
    bindModel(drop_down_item_model);

    return this;
  };

  this.bindClick = function(callback) {
    onClickCallbacks.push(callback);
    return this;
  };
};
