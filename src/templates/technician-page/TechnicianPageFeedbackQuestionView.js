var TechnicianPageFeedbackQuestionView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'technician-feedback-question-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'technician-feedback-question-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;
  var questionIndex = null;

  var cancelCallbacks = [];

  var _this = this;

  /**
   * Dom nodes
   */
  var cancelButtonNode = {
    className: 'delete-question-button',
    node: null
  };

  var textNode = {
    className: 'question-text',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, cancelButtonNode);
    Utils.bindNodeInfo(rootNode, textNode);

    cancelButtonNode.node.onclick = function(event) {
      cancelCallbacks.forEach(function(callback) {
        callback(this);
      }, _this);
    };
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui dom nodes
    bindNodes();
  };

  this.setText = function(text) {
    textNode.node.innerHTML = text;
  };

  this.bindCancel = function(callback) {
    cancelCallbacks.push(callback);
  };

  this.remove = function() {
    rootNode.parentNode.removeChild(rootNode);
  };

  this.setIndex = function(index) {
    questionIndex = index;
  };

  this.getIndex = function() {
    return questionIndex;
  };
};
