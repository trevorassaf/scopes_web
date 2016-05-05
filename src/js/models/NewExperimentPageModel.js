var NewExperimentPageModel = function() {

  /**
   * Default starting state
   */
  var DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS = {
    min_value: 0,
    max_value: 15,
    step: 1,
    value: 0
  };

  var DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS = {
    min_value: 0,
    max_value: 15,
    step: 1,
    value: 0
  };

  /**
   * Private state
   */
  var scopesCountModel = null;
  var experimentDurationModel = null;
  var experimentTimePickerModel = null;
  var experimentDatePickerModel = null;
  var shortCodePickerModel = null;
  var pricingModel = null;

  /**
   * Private functions
   */
  var initializeScopesCountModel = function() {
    var slider_model = new SliderModel();
    return slider_model
      .setMinValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.min_value)
      .setMaxValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.max_value)
      .setStep(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.step)
      .setCurrentValue(DEFAULT_SCOPES_COUNT_MODEL_PARAMETERS.value);
  };

  var initializeExperimentDurationModel = function() {
    var slider_model = new SliderModel();
    return slider_model
      .setMinValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.min_value)
      .setMaxValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.max_value)
      .setStep(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.step)
      .setCurrentValue(DEFAULT_EXPERIMENT_DURATION_MODEL_PARAMETERS.value);
  };

  var initializeExperimentDatePickerModel = function() {
    // Create data model
    var min_advance_day_count = 14;
    var max_advance_month_count = 4;
    var invalid_days_of_the_week = [0, 6];
    var invalid_dates = [
      new Date(2016, 4, 3),
      new Date(2016, 4, 4),
      new Date(2016, 4, 5)
    ];
    
    // Create model
    var date_picker_model = new DatePickerModel();
    return date_picker_model
      .setMinAdvanceDayCount(min_advance_day_count)
      .setMaxAdvanceMonthCount(max_advance_month_count)
      .setInvalidDaysOfTheWeek(invalid_days_of_the_week)
      .setInvalidDates(invalid_dates);
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize models
    scopesCountModel = initializeScopesCountModel();
    experimentDurationModel = initializeExperimentDurationModel();
    experimentDatePickerModel = initializeExperimentDatePickerModel();
    experimentTimePickerModel = new DropDownModel();
    shortCodePickerModel = new DropDownModel();
    pricingModel = new PricingModel();
  };

  // Getters
  this.getScopesCountModel = function() {
    return scopesCountModel;
  };

  this.getExperimentDurationModel = function() {
    return experimentDurationModel;
  };

  this.getExperimentTimePickerModel = function() {
    return experimentTimePickerModel;
  };

  this.getExperimentDatePickerModel = function() {
    return experimentDatePickerModel;
  };

  this.getShortCodePickerModel = function() {
    return shortCodePickerModel;
  };

  this.getPricingModel = function() {
    return pricingModel;
  };
};
