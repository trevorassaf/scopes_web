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

  var timePickerView = null;

  var datePickerView = null;

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
    Utils.bindNodeInfo(rootNode, experimentTimePickerNode);

    // Create view
    timePickerView = new DropDownView(
      templateStore,
      experimentTimePickerNode.node
    );

    timePickerView.init('device:access-time');
  };

  var initExperimentDatePickerView = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, experimentDatePickerNode);

    // Create view
    datePickerView = new DatePickerView(
      templateStore,
      experimentDatePickerNode.node
    );

    datePickerView.init();
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

  this.getTimePickerView = function() {
    return timePickerView;
  };

  this.getDatePickerView = function() {
    return datePickerView;
  };
};
