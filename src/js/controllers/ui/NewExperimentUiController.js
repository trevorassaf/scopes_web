var NewExperimentUiController = (function() {

  /**
   * Private state
   */
  var shortCodePicker = null;

  /**
   * Private functions
   */

  /**
   * Public methods
   */
  var init = function(template_store) {
    // Configure confirm-order controller
    ConfirmOrderUiController.init();

    // Configure scopes count ui contrller
    ScopesCountUiController.setOnChangeCallback(function(scopes_count) {
      ConfirmOrderUiController.setScopesCount(scopes_count);
    });
    ScopesCountUiController.init();
   
    // Configure experiment duration ui contrller
    ExperimentDurationUiController.setOnChangeCallback(function(experiment_duration) {
      ConfirmOrderUiController.setExperimentDuration(experiment_duration);
    });
    ExperimentDurationUiController.init();
  
    // Configure short code picker
    var shortCodePicker = new ShortCodePicker(
      template_store,
      'existing-short-code-picker'
    );
    shortCodePicker.init();

    // Register listeners on startup-data api call
    GetStartupDataApiController.registerSuccessfulApiCallback(function(json_response, api_keys) {
      shortCodePicker.setShortCodes(json_response[api_keys.short_codes]);
      ConfirmOrderUiController.setHourlyCost(json_response[api_keys.hourly_price]);
    }); 

  };

  return {
    init: init
  };
})();
