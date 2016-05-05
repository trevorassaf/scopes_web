var ConfirmOrderController = function() {

  /**
   * Private state
   */
  // Model
  var confirmOrderView = null;
  var experimentDurationModel = null;
  var pricingModel = null;

  // Event listeners
  var cancelOrderCallbacks = [];
  var confirmOrderCallbacks = [];

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathway
    experimentDurationModel.bindCurrentValue(refreshPriceDisplay);
    pricingModel.bindPricePerHour(refreshPriceDisplay);

    // Register button click callbacks
    confirmOrderView.bindCancelOrder(handleCancelOrderClick);
    confirmOrderView.bindConfirmOrder(handleConfirmOrderClick);
  };

  var refreshPriceDisplay = function() {
    var hours = experimentDurationModel.getCurrentValue();
    var hourly_price = pricingModel.getPricePerHour();
    var total_cost = hours * hourly_price

    confirmOrderView.setPricingInformation(
      hours,
      hourly_price,
      total_cost
    );
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

  /**
   * Privileged functions
   */
  this.init = function(
    confirm_order_view,
    experiment_duration_model,
    pricing_model
  ) {
    confirmOrderView = confirm_order_view;
    experimentDurationModel = experiment_duration_model;
    pricingModel = pricing_model;

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

  this.getPricingModel = function() {
    return pricingModel;
  };
};
