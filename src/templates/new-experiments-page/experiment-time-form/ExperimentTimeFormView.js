var ExperimentTimeFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'experiment-time-form-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'experiment-time-form-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var experimentTimePickerView = null;
  var experimentDatePickerView = null;

  /**
   * Dom nodes
   */
  var experimentTimePickerNode = {
    className: 'exp-time-picker',
    node: null
  };
  
  var experimentDatePickerNode = {
    className: 'exp-date-picker',
    node: null
  };

  /**
   * Private functions
   */
  var initExperimentTimePickerView = function() {
    // Bind nodes
    experimentTimePickerNode.node = Utils.bindNode(
      rootNode,
      experimentTimePickerNode.className
    );

    // Initialize view
    experimentTimePickerView = new TimePicker(
      templateStore,
      experimentTimePickerNode.node,
      {minutes: 0, hours: 10},
      {minutes: 0, hours: 19},
      30
    ); 

    experimentTimePickerView.init();
  };

  var initExperimentDatePickerView = function() {
  
  };

  var initFormElements = function() {
    initExperimentTimePickerView();
    initExperimentDatePickerView();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Synthesize template into document
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    ); 

    // Initialize form elements 
    initFormElements();
  };
};
