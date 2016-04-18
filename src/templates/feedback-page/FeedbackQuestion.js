function FeedbackQuestion(
  template_store,
  parent_node,
  question_title
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#feedback-question-template';

  /**
   * Default ui string
   */
  var DEFAULT_FEEDBACK_PROMPT = 'Add feedback...';

  /**
   * Ui attributes
   */
  var EDITING_RESPONSE_ATTR = 'editing-response';
  var CHANGED_RESPONSE_ATTR = 'changed-response';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var questionTitle = question_title;
  var isEditingResponse = false;
  var isChangedResponse = false;

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'feedback-question-wrapper',
    node: null
  };

  var questionLabelNode = {
    className: 'question-label',
    node: null
  };

  var responseAreaNode = {
    className: 'response-area',
    node: null
  };

  var synthesizeTemplate = function() {
    // Clone pending-order template
    var feedback_question_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var feedback_question_clone = document.importNode(feedback_question_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(feedback_question_clone); 
    var feedback_question_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = feedback_question_list[feedback_question_list.length - 1];
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var bindInternalNodes = function() {
    bindClassBoundNode(questionLabelNode);
    bindClassBoundNode(responseAreaNode);

    responseAreaNode.node.onclick = function() {
      // Short circuit b/c we're already editing this
      if (isEditingResponse) {
        return;
      }

      isEditingResponse = true;
      responseAreaNode.node.setAttribute(EDITING_RESPONSE_ATTR, '');

      if (!isChangedResponse) {
        var range = document.createRange();
        range.selectNodeContents(responseAreaNode.node);
        var sel = window.getSelection();
        sel.removeAllRanges();
        sel.addRange(range);
      }
    };
    
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c question isn't being edited currently anyway
      if (!isEditingResponse) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(responseAreaNode.className, node)) {
          return;
        }
      }   

      if (responseAreaNode.node.innerHTML == '' || responseAreaNode.node.innerHTML == null ||
        responseAreaNode.node.innerHTML == DEFAULT_FEEDBACK_PROMPT
      ) {
        responseAreaNode.node.removeAttribute(CHANGED_RESPONSE_ATTR);
        responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
        isChangedResponse = false;
      } else {
        responseAreaNode.node.setAttribute(CHANGED_RESPONSE_ATTR, '');
        isChangedResponse = true;
      }

      isEditingResponse = false;
      responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);
    });
  }

  var initUi = function() {
    questionLabelNode.node.innerHTML = questionTitle; 
    responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
    isEditingResponse = false;
    responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);
  };

  this.clearResponse = function() {
    isEditingResponse = false;
    responseAreaNode.node.removeAttribute(EDITING_RESPONSE_ATTR);

    isChangedResponse = false;
    responseAreaNode.node.removeAttribute(CHANGED_RESPONSE_ATTR);
    responseAreaNode.node.innerHTML = DEFAULT_FEEDBACK_PROMPT;
  };

  this.getResponse = function() {
    return (isChangedResponse)
      ? responseAreaNode.node.innerHTML
      : null;
  };

  this.init = function() {
    synthesizeTemplate();
    bindInternalNodes();
    initUi();
  };

  this.remove = function() {
    rootNode.node.parentNode.removeChild(rootNode.node);    
  };

};
