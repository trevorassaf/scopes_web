var ConfirmOrderFormController = function() {

  /**
   * Private state
   */
  var confirmOrderView = null;
  var experimentDurationModel = null;
  var pricePerHour = 20;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Bind to experiment-duration change 
    experimentDurationModel.bindCurrentValue(handleNewExperimentDuration);
  };

  var handleNewExperimentDuration = function(experiment_duration) {
    // Calculate price
    var total_price = pricePerHour * experiment_duration;
    confirmOrderView.setPricingInformation(
      experiment_duration,
      pricePerHour,
      total_price
    );
  };


  /**
   * Privileged functions
   */
  this.init = function(
    confirm_order_view,
    experiment_duration_model
  ) {
    confirmOrderView = confirm_order_view;
    experimentDurationModel = experiment_duration_model;

    // Attach models to views
    configureCallbacks(); 
  };
};
