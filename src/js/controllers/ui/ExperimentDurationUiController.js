var ExperimentDurationUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var EXPERIMENT_DURATION_UNIT_SINGULAR = "hour";
  var EXPERIMENT_DURATION_UNIT_PLURAL = "hours";

  /**
   * Private state
   */
  var experimentDuration = 0;
  var onChangeCallback = function(duration) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'duration-form-container',
    node: null
  };

  var validIconNode = {
    id: 'duration-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'duration-invalid-icon',
    node: null
  };
  
  var experimentDurationValueNode = {
    id: 'duration-display',
    node: null
  };

  var experimentDurationUnitNode = {
    id: 'duration-display-unit',
    node: null
  };

  var experimentDurationSliderNode = {
    id: 'duration-input',
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
    bindInternalNode(experimentDurationValueNode);
    bindInternalNode(experimentDurationUnitNode);
    bindInternalNode(experimentDurationSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    experimentDurationSliderNode.node.onchange = function() {
      experimentDuration = this.immediateValue;
      updateDurationDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateDurationDisplay = function() {
    // Render scope count value
    experimentDurationValueNode.node.innerHTML = experimentDuration;

    // Update scope count unit
    experimentDurationUnitNode.node.innerHTML = (experimentDuration === 1)
      ? EXPERIMENT_DURATION_UNIT_SINGULAR
      : EXPERIMENT_DURATION_UNIT_PLURAL;

    // Notify listeners
    onChangeCallback(experimentDuration);
  };

  /**
   * Public functions
   */
  var setDuration = function(experiment_duration) {
    experimentDuration = experiment_duration;

    // Update ui
    experimentDurationSliderNode.node.value = experiment_duration;
    updateDurationDisplay();

    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getDuration = function() {
    return experimentDuration;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scopes count
    setDuration(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return experimentDuration !== 0; 
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
    setDuration: setDuration,
    getDuration: getDuration,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput
  };
})();
