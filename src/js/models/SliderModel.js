var SliderModel = function() {
  // State
  this.minValue = 0;
  this.maxValue = 0;
  this.step = 0;
  this.currentValue = 0;

  // Callback listeners
  this.minValueCallbacks = [];
  this.maxValueCallbacks = [];
  this.stepCallbacks = [];
  this.currentValueCallbacks = [];
};

// Callback registration
SliderModel.prototype.bindMinValue = function(callback) {
  this.minValueCallbacks.push(callback);
  callback(this.minValue);
  return this;
};

SliderModel.prototype.bindMaxValue = function(callback) {
  this.maxValueCallbacks.push(callback);
  callback(this.maxValue);
  return this;
};

SliderModel.prototype.bindStep = function(callback) {
  this.stepCallbacks.push(callback);
  callback(this.step);
  return this;
};

SliderModel.prototype.bindCurrentValue = function(callback) {
  this.currentValueCallbacks.push(callback);
  callback(this.currentValue);
  return this;
};

// Setters
SliderModel.prototype.setMinValue = function(value) {
  this.minValue = value;
  this.minValueCallbacks.forEach(function(callback) {
    callback(this.minValue);
  }, this);
  return this;
};

SliderModel.prototype.setMaxValue = function(value) {
  this.maxValue = value;
  this.maxValueCallbacks.forEach(function(callback) {
    callback(this.maxValue);
  }, this);
  return this;
};

SliderModel.prototype.setStep = function(value) {
  this.step = value;
  this.stepCallbacks.forEach(function(callback) {
    callback(this.step);
  }, this);
  return this;
};

SliderModel.prototype.setCurrentValue = function(value) {
  this.currentValue = value;
  this.currentValueCallbacks.forEach(function(callback) {
    callback(this.currentValue);
  }, this);
  return this;
};

// Getters
SliderModel.prototype.getMinValue = function() {
  return this.minValue;
};

SliderModel.prototype.getMaxValue = function() {
  return this.maxValue;
};

SliderModel.prototype.getStep = function() {
  return this.step;
};

SliderModel.prototype.getCurrentValue = function() {
  return this.currentValue;
};
