var NewExperimentUiController = (function() {

  /**
   * Private state
   */
  var shortCodePicker = null;
  var calendarPicker = null;
  var timePicker = null;

  /**
   * Private functions
   */
  var isValidInput = function() {
    return ScopesCountUiController.getScopesCount() !== 0 &&
      ExperimentCountUiController.getDuration() !== 0;
  };

  var registerOnClickListeners = function() {
    ConfirmOrderUiController.registerConfirmOrderOnClickListener(confirmOrder);

    ConfirmOrderUiController.registerCancelOrderOnClickListener(cancelOrder);  
  };

  var registerEventListeners = function() {
    registerOnClickListeners();
  };

  /**
   * Public methods
   */
  /**
   * confirmOrder()
   * - Ensure valid input states.
   *   - invalid input: prompt user to to fix invalid input
   *   - valid input: hit server confirm-order api 
   */
  var confirmOrder = function() {
    // Check for invalid input -- notify user of all invalid input
    var is_valid_input = true;

    if (!ScopesCountUiController.isValidInput()) {
      ScopesCountUiController.signalInvalidInput(); 
      is_valid_input = false; 
    } 

    if (!ExperimentDurationUiController.isValidInput()) {
      ExperimentDurationUiController.signalInvalidInput(); 
      is_valid_input = false; 
    }

    // Short-circuit due to invalid input
    if (!is_valid_input) {
      return;
    }

    // Send confirm-order request to server
    var confirm_order_api = new ConfirmOrderApi(ScopesNetwork);   
    confirm_order_api.setScopesCount(ScopesCountUiController.getScopesCount());
    confirm_order_api.setExperimentDuration(ExperimentDurationUiController.getDuration());
    confirm_order_api.setPrice(ConfirmOrderUiController.getTotalPrice());

    var timestamp = Utils.makeTimestampString(
      calendarPicker.getSelectedDate(),
      timePicker.getSelectedTime()
    );
    confirm_order_api.setStartTimestamp(timestamp);
    
    confirm_order_api.setShortCodeId(shortCodePicker.getSelectedShortCode().id);

    confirm_order_api.setSuccessfulApiCallback(function(api_response) {
      console.log(api_response);
    });

    confirm_order_api.setLogicalApiFailureCallback(function(api_response) {
      console.log(api_response);
    });

    confirm_order_api.setNonLogicalApiFailureCallback(function(api_response) {
      console.log(api_response);
    });

    confirm_order_api.send();
  };

  /**
   * cancelOrder()
   * - revert all ui elements to original state
   */
  var cancelOrder = function() {
    ScopesCountUiController.setInitialState();  
    ExperimentDurationUiController.setInitialState();  
  };

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
    shortCodePicker = new ShortCodePicker(
      template_store,
      'existing-short-code-picker'
    );
    shortCodePicker.init();
    
    /**
     * Configure time-picker element
     */
    var start_time = {
      hours: 10,
      minutes: 00 
    };

    var end_time = {
      hours: 17,
      minutes: 30 
    };

    timePicker = new TimePicker(
      template_store,
      'exp-time-picker',
      start_time,
      end_time,
      30
    ); 
    timePicker.init();

    /**
     * Configure calendar element
     */
    var disallowed_week_days = new Set([0, 6]);
    calendarPicker = new Calendar(
        template_store,
        'exp-date-calendar',
        disallowed_week_days,
        {},
        3,
        0 
    );
    calendarPicker.init();

    // Register listeners on startup-data api call
    GetStartupDataApiController.registerSuccessfulApiCallback(function(json_response, api_keys) {
      shortCodePicker.setShortCodes(json_response[api_keys.short_codes]);
      ConfirmOrderUiController.setHourlyCost(json_response[api_keys.hourly_price]);
    }); 

    // Register event listeners
    registerEventListeners();

  };

  return {
    init: init,
    confirmOrder: confirmOrder,
    cancelOrder: cancelOrder
  };
})();
