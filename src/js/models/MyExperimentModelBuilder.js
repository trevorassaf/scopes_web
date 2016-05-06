var MyExperimentModelBuilder = function() {

  /**
   * Private state
   */
  var id = null;
  var title = null;
  var description = null;
  var scopesCount = null;
  var experimentDuration = null;
  var startTime = null;
  var shortCode = null;
  var experimentStatus = null;
  var paymentStatus = null;
  var isPersisted = null;

  /**
   * Privileged functions
   */
  this.build = function() {
    return new MyExperimentModel(
      id,
      title,
      description,
      scopesCount,
      experimentDuration,
      startTime,
      shortCode,
      experimentStatus,
      paymentStatus,
      isPersisted
    );
  };

  this.setId = function(_id) {
    id = _id;
    return this;
  };

  this.setTitle = function(_title) {
    title = _title;
    return this;
  };

  this.setDescription = function(_description) {
    description = _description;
    return this;
  };

  this.setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;
    return this;
  };

  this.setExperimentDuration = function(experiment_duration) {
    experimentDuration = experiment_duration;
    return this;
  };
  
  this.setStartTime = function(start_time) {
    startTime = start_time;
    return this;
  };

  this.setShortCode = function(short_code) {
    shortCode = short_code;
    return this;
  };

  this.setExperimentStatus = function(experiment_status) {
    experimentStatus = experiment_status;
    return this;
  };

  this.paymentStatus = function(payment_status) {
    paymentStatus = payment_status;
    return this;
  };

  this.isPersisted = function(is_persisted) {
    isPersisted = is_persisted;
    return this;
  };
};
