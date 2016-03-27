var ConfirmedOrderModel = function() {

  // Order state
  this.id = null;
  this.title = null;
  this.description = null;
  this.price = null;
  this.scopesCount = null;
  this.experimentDuration = null;
  this.startTime = null;
  this.startDate = null;
  this.paymentStatus = null;
  this.shortCode = null;

  // State change event listeners
  this.titleChangeListeners = [];
  this.descriptionChangeListeners = [];
  this.priceChangeListeners = [];
  this.scopesCountChangeListeners = [];
  this.experimentDurationChangeListeners = [];
  this.startTimeChangeListeners = [];
  this.startDateChangeListeners = [];
  this.shortCodeChangeListeners = [];
};

/**
 * ConfirmedOrder state getters
 */
ConfirmedOrderModel.prototype.getId = function() {
  return this.id;
};

ConfirmedOrderModel.prototype.getTitle = function() {
  return this.title;
};

ConfirmedOrderModel.prototype.getDescription = function() {
  return this.description;
};

/**
 * Setters w/callbacks
 */
ConfirmedOrderModel.prototype.setId = function(id) {
  this.id = id;
  return this;
}

ConfirmedOrderModel.prototype.setTitle = function(title) {
  this.title = title;

  for (var i = 0; i < this.titleChangeListeners.length; ++i) {
    this.titleChangeListeners[i](title);
  }

  return this;
};

ConfirmedOrderModel.prototype.setDescription = function(description) {
  this.description = description;

  for (var i = 0; i < this.descriptionChangeListeners.length; ++i) {
    this.descriptionChangeListeners[i](description);
  }

  return this;
};

ConfirmedOrderModel.prototype.setPrice = function(price) {
  this.price = price;

  for (var i = 0; i < this.priceChangeListeners.length; ++i) {
    this.priceChangeListeners[i](price);
  }

  return this;
};

ConfirmedOrderModel.prototype.setScopesCount = function(scopesCount) {
  this.scopesCount = scopesCount;

  for (var i = 0; i < this.scopesCountChangeListeners.length; ++i) {
    this.scopesCountChangeListeners[i](scopesCount);
  }

  return this;
};

ConfirmedOrderModel.prototype.setExperimentDuration = function(experimentDuration) {
  this.experimentDuration = experimentDuration;

  for (var i = 0; i < this.experimentDurationChangeListeners.length; ++i) {
    this.experimentDurationChangeListeners[i](experimentDuration);
  }

  return this;
};

ConfirmedOrderModel.prototype.setStartTime = function(startTime) {
  this.startTime = startTime;

  for (var i = 0; i < this.startTimeChangeListeners.length; ++i) {
    this.startTimeChangeListeners[i](startTime);
  }

  return this;
};

ConfirmedOrderModel.prototype.setStartDate = function(startDate) {
  this.startDate = startDate;

  for (var i = 0; i < this.startDateChangeListeners.length; ++i) {
    this.startDateChangeListeners[i](startDate);
  }

  return this;
};

ConfirmedOrderModel.prototype.setShortCode = function(shortCode) {
  this.shortCode = shortCode;

  for (var i = 0; i < this.shortCodeChangeListeners.length; ++i) {
    this.shortCodeChangeListeners[i](shortCode);
  }

  return this;
};

/**
 * Register state change listeners
 */
ConfirmedOrderModel.prototype.bindTitle = function(callback) {
  callback(this.title);
  this.titleChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindDescription = function(callback) {
  callback(this.description);
  this.descriptionChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindPrice = function(callback) {
  callback(this.price);
  this.priceChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindScopesCount = function(callback) {
  callback(this.scopesCount);
  this.scopesCountChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindExperimentDuration = function(callback) {
  callback(this.experimentDuration);
  this.experimentDurationChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindStartTime = function(callback) {
  callback(this.startTime);
  this.startTimeChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindStartDate = function(callback) {
  callback(this.startDate);
  this.startDateChangeListeners.push(callback);
  return this;
};

ConfirmedOrderModel.prototype.bindShortCode = function(callback) {
  callback(this.shortCode);
  this.shortCodeChangeListeners.push(callback);
  return this;
};
