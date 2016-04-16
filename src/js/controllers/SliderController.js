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

  this.getModel = function() {
    return sliderModel;
  };

  this.getView = function() {
    return sliderView;
  };
};
