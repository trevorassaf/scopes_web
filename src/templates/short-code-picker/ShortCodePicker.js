function ShortCodePicker(
  template_store,
  id,
  short_codes // { code: xxx, name: xxx}
) {

  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var OPTION_LOCAL_IDX_ATTR = 'local-idx';
  var TOOLTIP_ATTR = 'tooltip';

  /**
   * Html class names
   */
  var SHORT_CODE_LABEL_CLASS = 'short-code-label';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-option';

  /**
   * Html template id names
   */
  var MAIN_TEMPLATE_ID = '#short-code-picker-template';
  var OPTION_TEMPLATE_ID = '#short-code-picker-option-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var shortCodes = short_codes;
  var isDropDownOpen = false;
  var selectedOption = null;

  /**
   * Dom nodes
   */
  var rootNode = {
    nodeId: id,
    node: null
  };

  var shortCodePickerWrapperNode = {
    class: 'short-code-picker-wrapper',
    node: null
  };

  var inputFieldNode = {
    class: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    class: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    class: 'short-code-dropdown',
    node: null
  };

  // Private functions
  /**
   * synthesizeShortCodePickerTemplate()
   * - copy template and insert into root node
   * @pre-condition: root node is initialized 
   */
  var synthesizeShortCodePickerTemplate = function() {
    var short_code_picker_template = templateStore.import.querySelector(MAIN_TEMPLATE_ID);
    var short_code_picker_clone = document.importNode(short_code_picker_template.content, true);
    rootNode.node.appendChild(short_code_picker_clone);
  };

  /**
   * openDropDown()
   * - opens drop-down menu
   */
  var openDropDown = function() {
    isDropDownOpen = true;
    shortCodePickerWrapperNode.node.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };
 
  /**
   * closeDropDown()
   * - closes drop-down menu
   */
  var closeDropDown = function() {
    isDropDownOpen = false;    
    shortCodePickerWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * initOptionNode()
   * - initialize option node, e.g. add event listeners, bind data
   * @param Object option: option struct provided in constructor
   */
  var initOptionNode = function(option) {
  
  };

  /**
   * bindInternalNode()
   * - bind the specified dom node (must be internal to this short-code-picker)
   * @param: Obj internal_node: internal dom node (see 'inputFieldNode' for structure)
   * @pre-condition: root node bound 
   */
  var bindInternalNode = function(internal_node) {
    // We bind internal nodes once only!
    console.assert(internal_node.node == null); 

    // Fetch internal node by class
    var node_set = rootNode.node.getElementsByClassName(internal_node.class);

    // We should only find one *internal* node with this class
    console.assert(node_set.length == 1);

    internal_node.node = node_set[0];
  };

  /**
   * initNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initNodes = function() {
    // Bind top-level node in short-code-picker template
    bindInternalNode(shortCodePickerWrapperNode);
    
    // Bind input field and configure event listener
    bindInternalNode(inputFieldNode);
    bindInternalNode(inputFieldWrapperNode);

    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    // Bind time dropdown field and configure event listener
    bindInternalNode(dropDownNode);

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected time
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(SHORT_CODE_PICKER_OPTION_CLASS, node.className)) {
          // Capture selected option
          var local_idx_str = node.getAttribute(OPTION_LOCAL_IDX_ATTR);
          console.assert(local_idx_str != null);

          var local_idx = parseInt(local_idx_str);
          console.assert(local_idx != null);
          console.assert(shortCodes.length > local_idx);

          // Deselect previously selected option
          unselectOption(selectedOption);

          // Select clicked option
          selectedOption = shortCodes[local_idx];
          selectOption(selectedOption);

          return;
        }
      }
    };

    // Hide short-code picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the time-picker, so don't hide it!
        if (node.id == rootNode.node.id) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  }
  
  /**
   * initDisplay()
   * - initialize the picker display
   */
  var initDisplay = function() {
    // Start with dropdown closed or open depending on initial value
    if (isDropDownOpen) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Generate option nodes and insert into parent
    for (var i = 0; i < shortCodes; ++i) {
      var option_node = initOptionNode(shortCodes[i]);
      dropDownNode.node.appendChild(option_node);  
    }

    // Initialize starting short code 
    var first_option = shortCodes[0];
    selectOption(first_option);
  };

  /**
   * selectOptionByIndex()
   * - select the specified short-code option
   * @param uint option_index: index of the option that is selected
   */
  var selectOptionByIndex = function(option_index) {
    console.assert(option != null);    
  };

  /**
   * unselectOptionByIndex()
   * - unselect the specified short-code option
   * @param uint option_index: index of the option that is to be unselected
   */
  var unselectOption = function(option_index) {
    console.assert(option != null);    
   

  };

  // Privileged functions
  /**
   * init()
   * - initialize short-code picker
   */
  this.init = function() {
    // We only init once!
    console.assert(rootNode.node == null);

    // Bind root node
    rootNode.node = document.getElementById(rootNode.nodeId);

    // Synthesize the template and copy into the root node
    synthesizeShortCodePickerTemplate();

    // Initialize nodes: dom elements and event listeners
    initNodes();

    // Initialize the ui
    initDisplay();
  };
};
