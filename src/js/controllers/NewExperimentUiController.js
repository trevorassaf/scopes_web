var NewExperimentUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTRIBUTE = 'hidden-validation-icon';

  /**
   * Ui node id's
   */
  // Scope count
  var scopesCountUiFormInfo = {
    id_set: {
      display: 'scopes-count-display',
      display_unit: 'scopes-count-display-unit',
      input: 'scopes-count-input',
      valid_icon: 'scopes-count-valid-icon',
      invalid_icon: 'scopes-count-invalid-icon'
    },
    
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null,
      valid_icon: null,
      invalid_icon: null
    },

    display_labels: {
      singular: 'scope',
      plural: 'scopes'
    },

    value_change_count: 0
  };
  
  // Experiment duration
  var durationUiFormInfo = {
    id_set: {
      display: 'duration-display',
      display_unit: 'duration-display-unit',
      input: 'duration-input',
      valid_icon: 'duration-valid-icon',
      invalid_icon: 'duration-invalid-icon'
    },
  
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null,
      valid_icon: null,
      invalid_icon: null
    },

    display_labels: {
      singular: 'hour',
      plural: 'hours'
    },

    value_change_count: 0
  };

  /**
   * Ui util functions
   */
  /**
   * Update the display for an input form.
   *
   * @param: int count: number of microscopes
   * @param: Obj ui_form_info: data for form ui element (see 
   *    'this.scopesCountUiFormInfo')
   */
  this.updateDisplay = function(count, ui_form_info) {
    ui_form_info.ui_nodes.display.innerHTML = count;
    ui_form_info.ui_nodes.display_unit.innerHTML = (count == 1)
      ? ui_form_info.display_labels.singular
      : ui_form_info.display_labels.plural;
  };

  /**
   * Updates input node and display labels for the form.
   *
   * @param: Obj ui_form_info: data for form ui element (see 
   *    'this.scopesCountUiFormInfo')
   * @param: int count: number of microscopes
   */
  this.setInputValue = function(ui_form_info, count) {
    // Skip if same value
    if (ui_form_info.ui_nodes.input_field.value == count) {
      return;
    }

    // Update with new 'count' 
    ui_form_info.ui_nodes.input_field.value = count;
    updateDisplay(count, ui_form_info);
  };

  this.bindFormDomNodes = function(ui_form_info) {
    ui_form_info.ui_nodes.input_field = document.getElementById(ui_form_info.id_set.input); 
    ui_form_info.ui_nodes.display_unit = document.getElementById(ui_form_info.id_set.display_unit); 
    ui_form_info.ui_nodes.display = document.getElementById(ui_form_info.id_set.display); 
    ui_form_info.ui_nodes.valid_icon = document.getElementById(ui_form_info.id_set.valid_icon);
    ui_form_info.ui_nodes.invalid_icon = document.getElementById(ui_form_info.id_set.invalid_icon);
  };

  /**
   * hideInputValidationIcon()
   * - hide the validation icon
   */
  this.hideInputValidationIcon = function(validation_input_icon_dom) {
    validation_input_icon_dom.setAttribute(HIDDEN_VALIDATION_ICON_ATTRIBUTE, '');  
  };

  /**
   * showInputValidationIcon()
   * - show the validation icon
   */
  this.showInputValidationIcon = function(validation_input_icon_dom) {
    validation_input_icon_dom.removeAttribute(HIDDEN_VALIDATION_ICON_ATTRIBUTE); 
  };

  /**
   * updateUiInputCardWithValidInput()
   * - update the ui of the specified input card to reflect valid input
   */
  this.updateUiInputCardWithValidInput = function(ui_form_info) {
    hideInputValidationIcon(ui_form_info.ui_nodes.invalid_icon);   
    showInputValidationIcon(ui_form_info.ui_nodes.valid_icon);   
  };
 
  /**
   * updateUiInputCardWithInvalidInput()
   * - update the ui of the specified input card to reflect invalid input
   */
  this.updateUiInputCardWithInvalidInput = function(ui_form_info) {
    hideInputValidationIcon(ui_form_info.ui_nodes.valid_icon);   
    showInputValidationIcon(ui_form_info.ui_nodes.invalid_icon);   
  };

  /**
   * Initialize all input forms in the 'New Experiment' page.
   * Bind DOM nodes and attach event listeners.
   */
  this.init = function() {
    /**
     * Configure 'Scopes Count' input field
     */
    // Bind DOM nodes
    bindFormDomNodes(scopesCountUiFormInfo);

    // Bind event listeners
    scopesCountUiFormInfo.ui_nodes.input_field.onchange = function() {
      updateDisplay(this.immediateValue, scopesCountUiFormInfo);
    };

    // Initialize scopes count input card ui
    // updateUiInputCardWithValidInput(scopesCountUiFormInfo); 
    setInputValue(scopesCountUiFormInfo, 9);

    /**
     * Configure 'Duration' input field
     */
    // Bind DOM nodes
    bindFormDomNodes(durationUiFormInfo);

    // Bind event listeners
    durationUiFormInfo.ui_nodes.input_field.onchange = function() {
      updateDisplay(this.immediateValue, durationUiFormInfo);
    };

    // Initialize duration input card ui
    // updateUiInputCardWithInvalidInput(durationUiFormInfo); 
    setInputValue(durationUiFormInfo, 9);
  };

  return {
    init: init
  };
})();
