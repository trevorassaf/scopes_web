var MyExperimentModel = function(
  id,    
  title,
  description,
  scopes_count,
  experiment_duration,
  start_time,
  short_code,
  experiment_status,
  payment_status
) {

  /**
   * Private state
   */
  this.id = id;
  this.title = title;
  this.description = description;
  this.scopesCount = scopes_count;
  this.experimentDuration = experiment_duration;
  this.startTime = start_time;
  this.shortCode = short_code;
  this.experimentStatus = experiment_status;
  this.paymentStatus = payment_status;

  // Callbacks
  this.titleCallbacks = [];
  this.descriptionCallbacks = [];
  this.scopesCountCallbacks = [];
  this.experimentDurationCallbacks = [];
  this.startTimeCallbacks = [];
  this.experimentStatusCallbacks = [];
  this.paymentStatusCallbacks = [];
  this.shortCodeCallbacks = [];
};

// Setters
MyExperimentModel.prototype.setTitle = function(title) {
  this.title = title;
  this.titleCallbacks.forEach(function(callback) {
    callback(this.title); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setDescription = function(description) {
  this.description = description;
  this.descriptionCallbacks.forEach(function(callback) {
    callback(this.description); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setScopesCount = function(scopesCount) {
  this.scopesCount = scopesCount;
  this.scopesCountCallbacks.forEach(function(callback) {
    callback(this.scopesCount); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setExperimentDuration = function(experimentDuration) {
  this.experimentDuration = experimentDuration;
  this.experimentDurationCallbacks.forEach(function(callback) {
    callback(this.experimentDuration); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setStartTime = function(startTime) {
  this.startTime = startTime;
  this.startTimeCallbacks.forEach(function(callback) {
    callback(this.startTime); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setShortCode = function(shortCode) {
  this.shortCode = shortCode;
  this.shortCodeCallbacks.forEach(function(callback) {
    callback(this.shortCode); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setExperimentStatus = function(experimentStatus) {
  this.experimentStatus = experimentStatus;
  this.experimentStatusCallbacks.forEach(function(callback) {
    callback(this.experimentStatus); 
  }, this);
  return this;
};

MyExperimentModel.prototype.setPaymentStatus = function(paymentStatus) {
  this.paymentStatus = paymentStatus;
  this.paymentStatusCallbacks.forEach(function(callback) {
    callback(this.paymentStatus); 
  }, this);
  return this;
};

// Bind callbacks
MyExperimentModel.prototype.bindTitle = function(callback) {
  this.titleCallbacks.push(callback);
  callback(this.title);
  return this;
};

MyExperimentModel.prototype.bindDescription = function(callback) {
  this.descriptionCallbacks.push(callback);
  callback(this.description);
  return this;
};

MyExperimentModel.prototype.bindExperimentDuration = function(callback) {
  this.experimentDurationCallbacks.push(callback);
  callback(this.experimentDuration);
  return this;
};

MyExperimentModel.prototype.bindScopesCount = function(callback) {
  this.scopesCountCallbacks.push(callback);
  callback(this.scopesCount);
  return this;
};

MyExperimentModel.prototype.bindStartTime = function(callback) {
  this.startTimeCallbacks.push(callback);
  callback(this.startTime);
  return this;
};

MyExperimentModel.prototype.bindShortCode = function(callback) {
  this.shortCodeCallbacks.push(callback);
  callback(this.shortCode);
  return this;
};

MyExperimentModel.prototype.bindExperimentStatus = function(callback) {
  this.experimentStatusCallbacks.push(callback);
  callback(this.experimentStatus);
  return this;
};

MyExperimentModel.prototype.bindPaymentStatus = function(callback) {
  this.paymentStatusCallbacks.push(callback);
  callback(this.paymentStatus);
  return this;
};

// Getters
MyExperimentModel.prototype.getId = function() {
  return this.id;
};

MyExperimentModel.prototype.getDescription = function() {
  return this.description;
};

MyExperimentModel.prototype.getScopesCount = function() {
  return this.scopesCount;
};

MyExperimentModel.prototype.getExperimentDuration = function() {
  return this.experimentDuration;
};

MyExperimentModel.prototype.getStartTime = function() {
  return this.startTime;
};

MyExperimentModel.prototype.getShortCode = function() {
  return this.shortCode;
};

MyExperimentModel.prototype.getExperimentStatus = function() {
  return this.experimentStatus;
};

MyExperimentModel.prototype.getPaymentStatus = function() {
  return this.paymentStatus;
};
