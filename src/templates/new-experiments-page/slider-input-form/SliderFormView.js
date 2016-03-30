var SliderFormView = function(
  template_store,
  parent_node,
  title_label,
  unit_labels // {singular, plural}
) {

  /**
   * Template Id
   */
  var TEMPLATE_ID = 'slider-input-form-template';

  /**
   * Wrapper root node
   */
  var WRAPPER_ROOT_NODE_CLASS = 'slider-input-form-wrapper';

  /**
   * Paper slider ui attributes
   */
  var PAPER_SLIDER_MIN_ATTR = 'min';
  var PAPER_SLIDER_MAX_ATTR = 'max';
  var PAPER_SLIDER_STEP_ATTR = 'step';
  var PAPER_SLIDER_VALUE_ATTR = 'value';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var unitLabels = unit_labels;
  var titleLabel = title_label;
  
  var _this = this;

  var rootNode = null;

  var changedValueListeners = [];

  /**
   * Dom node info
   */
  var formTitleNode = {
    class_name: 'form-title-label',
    node: null
  };

  var valueDisplayNode = {
    class_name: 'value-display',
    node: null
  };

  var unitDisplayNode = {
    class_name: 'unit-display',
    node: null
  };

  var sliderNode = {
    class_name: 'slider-input',
    node: null
  };

  var bindNodes = function() {
    // Bind nodes
    formTitleNode.node = Utils.bindNode(rootNode, formTitleNode.class_name); 
    valueDisplayNode.node = Utils.bindNode(rootNode, valueDisplayNode.class_name); 
    unitDisplayNode.node = Utils.bindNode(rootNode, unitDisplayNode.class_name); 
    sliderNode.node = Utils.bindNode(rootNode, sliderNode.class_name); 

    // Bind onchange event listeners
    sliderNode.node.onchange = function() {
     
      // Update display
      _this.setValue(this.immediateValue);  
     
      // Notify listeners
      for (var i = 0; i < changedValueListeners.length; ++i) {
        changedValueListeners[i](this.immediateValue);
      }
    };
  };

  var setMinValue = function(min_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MIN_ATTR, min_value); 
  };

  var setMaxValue = function(max_value) {
    sliderNode.node.setAttribute(PAPER_SLIDER_MAX_ATTR, max_value); 
  };

  var setStep = function(step) {
    sliderNode.node.setAttribute(PAPER_SLIDER_STEP_ATTR, step); 
  };

  var initUi = function() {
    // Initialize slider
    formTitleNode.node.innerHTML = titleLabel;
  };

  var bindModel = function(slider_model) {
    slider_model
      .bindMinValue(setMinValue)
      .bindMaxValue(setMaxValue)
      .bindStep(setStep)
      .bindCurrentValue(_this.setValue);
  };

  /**
   * Privileged functions
   */
  this.init = function(slider_model) {
    // Initialize root node
    rootNode = Utils.synthesizeTemplate(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      WRAPPER_ROOT_NODE_CLASS
    );

    // Initialize nodes and bind event listeners
    bindNodes();

    // Bind model and init ui
    bindModel(slider_model);

    // Init ui elements (e.g. form title)
    initUi();
  };

  this.setValue = function(value) {
    // Update slider
    sliderNode.node.value = value;  

    // Update value display
    valueDisplayNode.node.innerHTML = value; 

    // Update unit display
    unitDisplayNode.node.innerHTML = (value == 1)
      ? unitLabels.singular
      : unitLabels.plural;
  };

  this.bindValueChange = function(callback) {
    changedValueListeners.push(callback);  
  };
};
