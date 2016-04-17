var SliderController = function() {

  /**
   * Private state
   */
  var sliderView = null;
  var sliderModel = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Configure model --> view data pathway
    sliderModel
      .bindMinValue(sliderView.setMinValue)
      .bindMaxValue(sliderView.setMaxValue)
      .bindStep(sliderView.setStep)
      .bindCurrentValue(sliderView.setValue);

    // Configure view --> model data pathway
    sliderView.bindValueChange(updateValue);
  };

  var updateValue = function(value) {
    sliderModel.setCurrentValue(value);
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    sliderView = view;
    sliderModel = model;

    // Attach view to model
    configureCallbacks();
  };

  this.renderDefaultUi = function() {
    updateValue(sliderModel.getMinValue()); 
  };

  this.getModel = function() {
    return sliderModel;
  };

  this.getView = function() {
    return sliderView;
  };
};
