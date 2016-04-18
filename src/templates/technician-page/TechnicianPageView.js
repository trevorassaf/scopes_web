var TechnicianPageView = function(
  template_store,
  parent_node
) {

  /**
   * Page title
   */
  var PAGE_TITLE = 'Technician';

  /**
   * Template id
   */
  var TEMPLATE_ID = 'technician-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'technician-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var rootNode = null;

  var addQuestionCallbacks = [];

  /**
   * Dom nodes
   */
  var existingQuestionsNode = {
    className: 'existing-questions',
    node: null
  };

  var addQuestionTextNode = {
    className: 'add-question-text-field',
    node: null
  };

  var addQuestionWrapperNode = {
    className: 'add-new-question-wrapper',
    node: null
  };

  var addQuestionButtonNode = {
    className: 'add-question-button',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    Utils.bindNodeInfo(rootNode, existingQuestionsNode);
    Utils.bindNodeInfo(rootNode, addQuestionTextNode);
    Utils.bindNodeInfo(rootNode, addQuestionWrapperNode);
    Utils.bindNodeInfo(rootNode, addQuestionButtonNode);

    addQuestionButtonNode.node.onclick = function() {
      addQuestionCallbacks.forEach(function(callback) {
        callback();
      });      
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

  this.hide = function() {
    Utils.hideNode(rootNode);
  };

  this.show = function() {
    Utils.showNode(rootNode);
  };

  this.getTitle = function() {
    return PAGE_TITLE;
  };

  this.clearNewQuestionText = function() {
    addQuestionTextNode.node.innerHTML = ''; 
  };

  this.getNewQuestionText = function() {
    return addQuestionTextNode.node.innerHTML;
  };

  this.bindNewQuestion = function(callback) {
    addQuestionCallbacks.push(callback);
  };

  this.addQuestion = function(question) {
    feedback_question.setText(question);
  };

  this.spawnNewQuestion = function() {
    var feedback_question = new TechnicianPageFeedbackQuestionView(
      templateStore,
      existingQuestionsNode.node
    );

    feedback_question.init();
    return feedback_question;
  };
};
