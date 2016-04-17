var MyExperimentsPageModel = function() {

  /**
   * Private vars
   */
  this.myExperiments = [];

  /**
   * Callbacks
   */
  this.newExperimentCallbacks = []; 
  this.removeExperimentCallbacks = [];
  this.setExperimentsCallbacks = [];
};

MyExperimentsPageModel.prototype.addExperiment = function(experiment) {
  this.myExperiments.push(experiment);
  this.newExperimentCallbacks.forEach(function(callback) {
    callback(experiment);
  });
  return this;
};

MyExperimentsPageModel.prototype.removeExperiment = function(experiment) {
  // TODO: Need to rethink this
  Utils.removeElementFromArray(experiment, this.myExperiments);  
  this.removeExperimentsCallbacks.forEach(function(callback) {
    callback(experiment);
  });
  return this;
};

MyExperimentsPageModel.prototype.setExperiments = function(my_experiments) {
  this.myExperiments = my_experiments;
  this.setExperimentsCallbacks.forEach(function(callback) {
    callback(my_experiments);
  });
  return this;
};

// Bind Callbacks
MyExperimentsPageModel.prototype.bindAddExperiment = function(callback) {
  this.newExperimentCallbacks.push(callback);
  return this;
};

MyExperimentsPageModel.prototype.bindRemoveExperiment = function(callback) {
  this.removeExperimentCallbacks.push(callback);
  return this;
};

MyExperimentsPageModel.prototype.bindSetExperiments = function(callback) {
  this.setExperimentsCallbacks.push(callback);
  return this;
};

// Getters
MyExperimentsPageModel.prototype.getExperiments = function() {
  return this.myExperiments;
};
