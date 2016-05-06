var NewMyExperimentModelBuilder = function() {

  /**
   * Default constants
   */
  var INITIAL_TITLE = '';
  var INITIAL_DESCRIPTION = '';
  var INITIAL_EXPERIMENT_STATUS = ExperimentStatus.PENDING;
  var INITIAL_PAYMENT_STATUS = PaymentStatus.PENDING;
  var INITIAL_IS_PERSISTED = false;

  /**
   * Private state
   */
  var builder = new MyExperimentModelBuilder();

  // Initialize builder with default data
  builder
    .setTitle(INITIAL_TITLE)
    .setDescription(INITIAL_DESCRIPTION)
    .setExperimentStatus(INITIAL_EXPERIMENT_STATUS)
    .setPaymentStatus(INITIAL_PAYMENT_STATUS)
    .setIsPersisted(INITIAL_IS_PERSISTED);

  /**
   * Privileged functions
   */
  this.init = function() {
    return builder.build(); 
  };

  this.setScopesCount = function(scopes_count) {
    builder.setScopesCount(scopes_count);
    return this;
  };

  this.setExperimentDuration = function(experiment_duration) {
    builder.setExperimentDuration(experiment_duration);
    return this;
  };
  
  this.setStartTime = function(start_time) {
    builder.setStartTime(start_time);
    return this;
  };

  this.setShortCode = function(short_code) {
    builder.setShortCode(short_code);
    return this;
  };
};
