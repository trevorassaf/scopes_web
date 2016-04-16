var ShortCodeFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'short-code-form-template';

  /**
   * Root wrapper class
   */
  var ROOT_CLASS = 'short-code-form-wrapper';

  /**
   * Short code drop-down icon
   */
  var ICON_NAME = 'payment';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var shortCodePickerView = null;

  /**
   * DOM nodes
   */
  var shortCodePickerNode = {
    className: 'short-code-picker',
    node: null
  };

  /**
   * Private functions
   */
  var initFormElements = function(drop_down_controller) {
    // Bind short-code drop-down node
    Utils.bindNodeInfo(rootNode, shortCodePickerNode);  

    // Initialize drop-down view
    shortCodePickerView = new DropDownView(
      templateStore,
      shortCodePickerNode.node
    );

    shortCodePickerView.init(
      drop_down_controller.getModel(),
      ICON_NAME
    );

    drop_down_controller.setView(shortCodePickerView);
  };


  /**
   * Privileged functions
   */
  this.init = function(drop_down_controller) {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements
    initFormElements(drop_down_controller);
  };

  this.getDropDownView = function() {
    return shortCodePickerView;
  };

};
