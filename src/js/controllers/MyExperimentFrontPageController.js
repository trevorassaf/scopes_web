var MyExperimentFrontPageController = function() {

  /**
   * Private state
   */
  var frontPageView = null;
  var myExperimentModel = null;

  /**
   * Private functions
   */
  var handleStartTimeChange = function(start_time) {
    frontPageView.setStartTime(start_time) 
  };

  var configureCallbacks = function() {
    // Model --> view data pathway
    myExperimentModel
      .bindScopesCount(frontPageView.setScopesCount)
      .bindExperimentDuration(frontPageView.setExperimentDuration)
      .bindStartTime(handleStartTimeChange)
      .bindShortCode(frontPageView.setShortCode)
      .bindExperimentStatus(frontPageView.setExperimentStatus)
      .bindPaymentStatus(frontPageView.setPaymentStatus);
  };

  /**
   * Privileged functions
   */
  this.init = function(
    front_page_view,
    my_experiment_model
  ) {
    frontPageView = front_page_view;
    myExperimentModel = my_experiment_model;

    configureCallbacks();
  };
};
