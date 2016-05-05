var PricingModel = function() {
  
  // Private state
  this.pricePerHour = 0;

  // Field listeners
  this.pricePerHourListeners = [];
};

/**
 * PricingModel state getters
 */
PricingModel.prototype.getPricePerHour = function() {
  return this.pricePerHour;
};

/**
 * Setters w/callbacks
 */
PricingModel.prototype.setPricePerHour = function(price) {
  this.pricePerHour = price;

  this.pricePerHourListeners.forEach(function(callback) {
    callback(this.pricePerHour);
  }, this); 
  return this;
};

/**
 * Register listeners
 */
PricingModel.prototype.bindPricePerHour = function(callback) {
  this.pricePerHourListeners.push(callback);
  callback(this.pricePerHour);
  return this;
};
