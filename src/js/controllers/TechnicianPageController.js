var TechnicianPageController = function() {

  /**
   * Private vars
   */
  var technicianPageView = null;
  var feedbackPageView = null;
  var questionIndex = 0;

  /**
   * Private functions
   */
  var handleNewQuestion = function() {
    var question = technicianPageView.getNewQuestionText();
    addNewQuestion(question);
  };

  var handleCancel = function(question_view) {
    var index = question_view.getIndex();
    question_view.remove();
    feedbackPageView.removeQuestion(index);
  };

  var addNewQuestion = function(question_text) {
    // Update technician ui
    var new_question = technicianPageView.spawnNewQuestion();
    new_question.setText(question_text);
    new_question.setIndex(questionIndex++);
    new_question.bindCancel(handleCancel);

    technicianPageView.clearNewQuestionText();
    
    // Update feedback page ui
    feedbackPageView.addQuestion(question_text);
  };

  var configureCallbacks = function() {
    technicianPageView.bindNewQuestion(handleNewQuestion);
  };

  var initUi = function() {
    addNewQuestion("What was one thing MVS did especially well? Why?");  
    addNewQuestion("What is one thing that you would like MVS to change going forward? Why?");  
    addNewQuestion("Any other comments/suggestions?");  
  };

  /**
   * Privileged functions
   */
  this.init = function(
    technician_page_view,
    feedback_page_view     
  ) {
    technicianPageView = technician_page_view;
    feedbackPageView = feedback_page_view;

    configureCallbacks();
    
    initUi();
  };
};
