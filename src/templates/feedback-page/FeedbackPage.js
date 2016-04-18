function FeedbackPage(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'feedback-page-template';

  var ROOT_CLASS = 'feedback-page-wrapper';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-feedback-page";

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  var _this = this;
  var feedbackQuestionList = [];

  /**
   * Dom nodes
   */
  // Root node
  var feedbackPageRootNode = {
    node: null
  };

  // Class-bound nodes
  var questionListNode = {
    className: 'questions-wrapper',
    node: null
  };

  var submitBtnNode = {
    className: 'submit-btn',
    node: null
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = feedbackPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeFeedbackPageTemplate()
   * - copy feedback-page template and insert into main dom tree
   * @pre-condition: 'feedbackPageRootNode' must be initialized
   */
  // function synthesizeFeedbackPageTemplate() {
  //   // Bind feedback-page dom template
  //   var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
  //   var page_clone = document.importNode(page_template.content, true);
  //   feedbackPageRootNode.node.appendChild(page_clone);
  // };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = feedbackPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    bindClassBoundNode(questionListNode);     
    bindClassBoundNode(submitBtnNode);     

    submitBtnNode.node.onclick = function() {
      for (var i = 0; i < feedbackQuestionList.length; ++i) {
        feedbackQuestionList[i].clearResponse();
      }
    };
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    // Initialize feedback questions
    feedbackQuestionList = [];
    Utils.removeDomChildren(questionListNode.node);

    // Question 1
    var question_1 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'What is one thing that MVS did especially well? Why?'
    );
    question_1.init();

    feedbackQuestionList.push(question_1);

    // Question 2
    var question_2 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'What is one thing that you would like to see MVS change going forward? Why?'
    );
    question_2.init();
    feedbackQuestionList.push(question_2);
    
    // Question 3
    var question_3 = new FeedbackQuestion(
      templateStore,
      questionListNode.node,
      'Any other comments/suggestions?'
    );
    question_3.init();

    feedbackQuestionList.push(question_3);
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize monitor experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level feedback-page node (we're going to copy the template into this!)
    feedbackPageRootNode.node = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS
    );

    // // Clone template and copy into wrapper
    // synthesizeFeedbackPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the feedback-page
   */
  this.hide = function() {
    Utils.hideNode(feedbackPageRootNode.node);
    // feedbackPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the feedback-page
   */
  this.show = function() {
    Utils.showNode(feedbackPageRootNode.node);
    // feedbackPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

  this.getTitle = function() {
    return "Feedback";
  };
};
