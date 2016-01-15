var NewExperimentUiController = (function() {
 
  /**
   * Ui node id's
   */
  // Scope count
  var scopesCountUiFormInfo = {
    id_set: {
      display: 'scopes-count-display',
      display_unit: 'scopes-count-display-unit',
      input: 'scopes-count-input'
    },
    
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null
    },

    display_labels: {
      singular: 'microscope',
      plural: 'microscopes'
    }
  };
  
  // Experiment duration
  var durationUiFormInfo = {
    id_set: {
      display: 'duration-display',
      display_unit: 'duration-display-unit',
      input: 'duration-input'
    },
  
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null
    },

    display_labels: {
      singular: 'hour',
      plural: 'hours'
    }
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
  var updateDisplay = function(
    count,
    ui_form_info
  ) {
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
  var setInputValue = function(ui_form_info, count) {
    // Skip if same value
    if (ui_form_info.ui_nodes.input_field.value == count) {
      return;
    }

    // Update with new 'count' 
    ui_form_info.ui_nodes.input_field.value = count;
    updateDisplay(count, ui_form_info);
  };

  var bindFormDomNodes = function(ui_form_info) {
    ui_form_info.ui_nodes.input_field = document.getElementById(ui_form_info.id_set.input); 
    ui_form_info.ui_nodes.display_unit = document.getElementById(ui_form_info.id_set.display_unit); 
    ui_form_info.ui_nodes.display = document.getElementById(ui_form_info.id_set.display); 
  };

  /**
   * Initialize all input forms in the 'New Experiment' page.
   * Bind DOM nodes and attach event listeners.
   */
  var init = function() {
    /**
     * Configure 'Scopes Count' input field
     */
    // Bind DOM nodes
    bindFormDomNodes(scopesCountUiFormInfo);

    // Bind event listeners
    scopesCountUiFormInfo.ui_nodes.input_field.onchange = function() {
      updateDisplay(this.immediateValue, scopesCountUiFormInfo);
    };

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

    setInputValue(durationUiFormInfo, 9);
  };

  return {
    init: init
  };
}());
