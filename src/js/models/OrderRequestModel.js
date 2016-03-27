var OrderRequestModel = function() {

  // Order request state
  this.scopesCount = null;
  this.experimentDuration = null; // num hours
  this.startTime = null; // seconds from start of day
  this.startDate = null; // DateObj
  this.shortCodeId = null;

  // State change listeners
  this.scopesCountChangeListeners = [];
  this.experimentDurationChangeListeners = [];
  this.startTimeChangeListeners = [];
  this.startDateChangeListeners = [];
  this.shortCodeIdChangeListeners = [];
};

/**
 * Getters
 */
OrderRequestModel.prototype.getScopesCount = function() {
  return this.scopesCount;
};

OrderRequestModel.prototype.getExperimentDuration = function() {
  return this.experimentDuration;
};

OrderRequestModel.prototype.getStartTime = function() {
  return this.startTime;
};

OrderRequestModel.prototype.getStartDate = function() {
  return this.startDate;
};

OrderRequestModel.prototype.getShortCodeId = function() {
  return this.shortCodeId;
};

/**
 * Setters
 */

/**
 * Register event listeners
 */
OrderRequestModel.prototype.bindScopesCount = function(callback) {
  this.scopesCountChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindExperimentDuration = function(callback) {
  this.experimentDurationChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindStartTime = function(callback) {
  this.startTimeChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindStartDate = function(callback) {
  this.startDateChangeListeners.push(callback);
  return this;
};

OrderRequestModel.prototype.bindShortCode = function(callback) {
  this.shortCodeChangeListeners.push(callback);
  return this;
};
