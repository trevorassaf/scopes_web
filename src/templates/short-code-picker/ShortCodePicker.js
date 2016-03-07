function ShortCodePicker(
  template_store,
  id,
  short_codes // {id, code, alias}, optional
) {

  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var INPUT_FIELD_WRAPPER_TOOLTIP_ATTR = 'tooltip';
  var OPTION_LOCAL_IDX_ATTR = 'local-idx';
  var OPTION_TOOLTIP_ATTR = 'tooltip';
  var OPTION_SELECTED_ATTR = 'selected-option';

  /**
   * Html class names
   */
  var SHORT_CODE_LABEL_CLASS = 'short-code-label';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-option';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-picker-option';

  /**
   * Html template id names
   */
  var MAIN_TEMPLATE_ID = '#short-code-picker-template';
  var OPTION_TEMPLATE_ID = '#short-code-picker-option-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var shortCodes = typeof short_codes == 'undefined' ? [] : short_codes;
  var isDropDownOpen = false;
  var selectedOptionIndex = null;

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
  
  var inputFieldLabelNode = {
    class: 'input-field-label',
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
   * - clone new option node
   * - bind data and event listeners
   * - insert into drop-down
   * @param Object option: option struct provided in constructor
   */
  var initOptionNode = function(option) {
    // Clone new option node from template
    var short_code_picker_option_template = templateStore.import.querySelector(OPTION_TEMPLATE_ID);  
    var short_code_picker_option_clone = document.importNode(short_code_picker_option_template.content, true);

    // Add to drop-down (activates node so that we can now bind data/event listeners)
    dropDownNode.node.appendChild(short_code_picker_option_clone); 

    // Bind data
    var short_code_picker_option_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(short_code_picker_option_list.length > 0);
    var option_local_idx = short_code_picker_option_list.length - 1; 
    var short_code_picker_option = short_code_picker_option_list[option_local_idx];

    // Local index (index of short-code in local array of short-code objects)
    short_code_picker_option.setAttribute(OPTION_LOCAL_IDX_ATTR, option_local_idx);
   
    // Tooltip (actual short code number, not just name)
    short_code_picker_option.setAttribute(OPTION_TOOLTIP_ATTR, option.code);
   
    // Short code name (name given by user, not just number)
    var short_code_label_node_list = short_code_picker_option.getElementsByClassName(SHORT_CODE_LABEL_CLASS);
    console.assert(short_code_label_node_list.length == 1);
    short_code_label_node_list[0].innerHTML = option.alias;
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
   * initMainNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initMainNodes = function() {
    // Bind top-level node in short-code-picker template
    bindInternalNode(shortCodePickerWrapperNode);
    
    // Bind input field and configure event listener
    bindInternalNode(inputFieldLabelNode);
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

      // Capture selected short-code 
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(SHORT_CODE_PICKER_OPTION_CLASS, node)) {
          // Capture selected option
          var local_idx_str = node.getAttribute(OPTION_LOCAL_IDX_ATTR);
          console.assert(local_idx_str != null);

          var local_idx = parseInt(local_idx_str);
          console.assert(local_idx != null);

          // Deselect previously selected option
          unselectOptionByIndex(selectedOptionIndex);

          // Select clicked option
          selectOptionByIndex(local_idx);

          return;
        }
      }
    };

    // Hide short-code picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        // User clicked on the time-picker, so don't hide it!
        if (Utils.hasClass(shortCodePickerWrapperNode.class, node)) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  }
 
  /**
   * initOptionNodes()
   * - initialize nodes for short code options
   */
  var initOptionNodes = function() {
    // Clear existing nodes
    Utils.removeDomChildren(dropDownNode.node);

    // Generate option nodes and insert into parent
    for (var i = 0; i < shortCodes.length; ++i) {
      initOptionNode(shortCodes[i]);
    }
  };
  
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

    // Initialize starting short code 
    if (shortCodes.length !== 0) {
      selectOptionByIndex(0);
    }
  };

  /**
   * selectOptionByIndex()
   * - select the specified short-code option
   * @param uint option_index: index of the option that is selected
   */
  var selectOptionByIndex = function(option_index) {
    console.assert(option_index < shortCodes.length);

    // Bind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.setAttribute(OPTION_SELECTED_ATTR, '');
    
    inputFieldWrapperNode.node.setAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR, option.code);

    // Update main display
    inputFieldLabelNode.node.innerHTML = option.alias; 

    selectedOptionIndex = option_index;
  };

  /**
   * unselectOptionByIndex()
   * - unselect the specified short-code option
   * @param uint option_index: index of the option that is to be unselected
   */
  var unselectOptionByIndex = function(option_index) {
    console.assert(selectedOptionIndex != null);
    console.assert(option_index < shortCodes.length);

    // Unbind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.removeAttribute(OPTION_SELECTED_ATTR);

    inputFieldWrapperNode.node.removeAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR);

    // Update main display
    inputFieldLabelNode.node.innerHTML = '';

    selectedOptionIndex = null;
  };

  function setInitialStateInternal() {
    // Update ui with new short-codes
    initDisplay();
  };

  // Privileged functions
  /**
   * setShortCodes()
   * - set list of selectable short-codes
   * @param: array<ShortCode> short_codes: {id, code, alias}
   */
  this.setShortCodes = function(short_codes) {
    shortCodes = short_codes; 

    initOptionNodes();
    setInitialStateInternal();
  };

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
    initMainNodes();

    // Initialize ui state
    initOptionNodes();
    setInitialStateInternal();
  };

  this.getSelectedShortCode = function() {
    console.assert(selectedOptionIndex !== null);
    console.assert(selectedOptionIndex < shortCodes.length);
    return shortCodes[selectedOptionIndex];
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };
};
