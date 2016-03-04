var ScopesCountUiController = (function() {

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

    // Attach event listeners
    scopesCountSliderNode.node.onchange = function() {
      scopesCount = this.immediateValue;
      updateScopesCountDisplay();
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
  };

  var getScopesCount = function() {
    return scopesCount;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scopes count
    setScopesCount(0);
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  return {
    init: init,
    setScopesCount: setScopesCount,
    getScopesCount: getScopesCount,
    setOnChangeCallback: setOnChangeCallback
  };

})();
