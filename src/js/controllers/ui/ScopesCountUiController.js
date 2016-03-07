var ScopesCountUiController = (function() {
  
  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var SCOPES_UNIT_SINGULAR = "scope";
  var SCOPES_UNIT_PLURAL = "scopes";

  /**
   * Private state
   */
  var scopesCount = 0;
  var onChangeCallback = function(num_scopes) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'scopes-count-input-container',
    node: null
  };
  
  var validIconNode = {
    id: 'scopes-count-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'scopes-count-invalid-icon',
    node: null
  };

  var scopesCountValueNode = {
    id: 'scopes-count-display',
    node: null
  };

  var scopesCountUnitNode = {
    id: 'scopes-count-display-unit',
    node: null
  };

  var scopesCountSliderNode = {
    id: 'scopes-count-input',
    node: null
  };

  /**
   * Private functions
   */
  var showProperValidationIcon = function() {
    if (isValidInput()) {
      showValidIcon();
    } else {
      showInvalidIcon();
    }
  };

  var showValidIcon = function() {
    hideValidationIcon(invalidIconNode);
    showValidationIcon(validIconNode);
  };

  var showInvalidIcon = function() {
    hideValidationIcon(validIconNode);
    showValidationIcon(invalidIconNode);
  };

  var hideBothValidationIcons = function() {
    hideValidationIcon(invalidIconNode);
    hideValidationIcon(validIconNode);
  };

  var hideValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.setAttribute(HIDDEN_VALIDATION_ICON_ATTR, '');
  };

  var showValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.removeAttribute(HIDDEN_VALIDATION_ICON_ATTR);
  }

  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindNodes = function() {
    // Bind internal nodes
    bindInternalNode(rootNode);
    bindInternalNode(scopesCountValueNode);
    bindInternalNode(scopesCountUnitNode);
    bindInternalNode(scopesCountSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    scopesCountSliderNode.node.onchange = function() {
      scopesCount = this.immediateValue;
      updateScopesCountDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateScopesCountDisplay = function() {
    // Render scope count value
    scopesCountValueNode.node.innerHTML = scopesCount;

    // Update scope count unit
    scopesCountUnitNode.node.innerHTML = (scopesCount === 1)
      ? SCOPES_UNIT_SINGULAR
      : SCOPES_UNIT_PLURAL;
      
    // Notify listeners
    onChangeCallback(scopesCount);
  };

  /**
   * Public functions
   */
  var setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;

    // Update ui
    scopesCountSliderNode.node.value = scopes_count;
    updateScopesCountDisplay();
    
    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getScopesCount = function() {
    return scopesCount;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scope count and ui
    setInitialState();
  };

  var setInitialState = function() {
    setScopesCount(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return scopesCount !== 0; 
  };

  var signalInvalidInput = function() {
    // Short circuit if valid input...
    if (isValidInput()) {
      return;
    }

    showInvalidIcon();
  };

  return {
    init: init,
    setScopesCount: setScopesCount,
    getScopesCount: getScopesCount,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput,
    setInitialState: setInitialState
  };
})();
