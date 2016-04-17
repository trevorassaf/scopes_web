var ConfirmOrderController = function() {

  /**
   * Private state
   */
  var confirmOrderView = null;
  var experimentDurationModel = null;
  var pricePerHour = 20;

  var cancelOrderCallbacks = [];
  var confirmOrderCallbacks = [];

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathway
    experimentDurationModel.bindCurrentValue(handleNewExperimentDuration);

    // Register button click callbacks
    confirmOrderView.bindCancelOrder(handleCancelOrderClick);
    confirmOrderView.bindConfirmOrder(handleConfirmOrderClick);
  };

  var handleConfirmOrderClick = function() {
    for (var i = 0; i < confirmOrderCallbacks.length; ++i) {
      confirmOrderCallbacks[i]();
    }
  };

  var handleCancelOrderClick = function() {
    for (var i = 0; i < cancelOrderCallbacks.length; ++i) {
      cancelOrderCallbacks[i]();
    }
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

    return this;
  };

  this.bindConfirmOrder = function(callback) {
    confirmOrderCallbacks.push(callback);
    return this;
  };

  this.bindCancelOrder = function(callback) {
    cancelOrderCallbacks.push(callback);
    return this;
  };
};
