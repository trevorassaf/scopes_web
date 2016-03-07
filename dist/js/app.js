window.onload = function() {

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Configure UI elements
   */
  CenterPanelController.init();
  SidePanelUiController.init();
  NewExperimentUiController.init(template_store);
  
  /**
   * Fetch startup data and route to proper views 
   */
  GetStartupDataApiController.fetch();
};

var Utils = (function() {

  var CLASS_NAME_PROPERTY = "className";

  // Timestamp delimiters
  var DATE_DELIMITER = "-";
  var TIME_DELIMITER = ":";
  var DATE_TIME_SEPERATOR = " ";

  this.hasClass = function(expected_class, node) {
    if (!(CLASS_NAME_PROPERTY in node)) {
      return false;
    }

    var node_class = node[CLASS_NAME_PROPERTY];
    var class_idx = node_class.indexOf(expected_class);
    
    if (class_idx == -1) {
      return false;
    }

    return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
      && (expected_class.length + class_idx == node_class.length
        || node_class.charAt(expected_class.length + class_idx) == ' ');
  };
  
  this.makePriceString = function(price) {

    // Group thousands with commas 
    var price_str = "";
    var price_in_dollars = Math.floor(price);
    
    var i = 1;
    var j = 1000;

    while (j < price_in_dollars) {
      var codon = Math.floor((price_in_dollars % j) / i);
      price_str = "," + codon.toString().concat(price_str);
      i = j;
      j *= 1000;
    }

    var leading_digits = Math.floor(price_in_dollars / i);
    price_str = leading_digits.toString().concat(price_str);

    // Stringify decimal digits
    var cents = Math.floor(price * 100) % 100;
    var cents_str = cents.toString();
    if (cents_str.length === 1) {
      cents_str = "0".concat(cents_str);
    }
    console.assert(cents_str.length === 2);

    cents_str = ".".concat(cents_str);
    return price_str.concat(cents_str);
  };

  this.stringifyNumberWithEnforcedDigitCount = function(number, digit_count) {
    var number_string = number.toString();
    console.assert(number_string.length <= digit_count);

    if (number_string.length < digit_count) {
      var zero_prefix = "0".repeat(digit_count - number_string.length);
      number_string = zero_prefix.concat(number_string);
    }

    return number_string;
  };

  /**
   * makeTimestampString()
   * @param DateObj date: {year, month, date}
   * @param TimeObj time: {hours, minutes, seconds}
   *   - 'hours' is in military time
   */
  this.makeTimestampString = function(date, time) {
    return date.year.toString() + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.month, 2) + DATE_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(date.date, 2) + DATE_TIME_SEPERATOR +
      stringifyNumberWithEnforcedDigitCount(time.hours, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.minutes, 2) + TIME_DELIMITER +
      stringifyNumberWithEnforcedDigitCount(time.seconds, 2);
  };

  /**
   * removeDomChildren()
   *   - remove all children from dom node
   * @param DOMElemet dom_node: some dom node
   */
  this.removeDomChildren = function(dom_node) {
    while (dom_node.firstChild) {
      dom_node.removeChild(dom_node.firstChild);
    }
  };

  return {
    hasClass: hasClass,
    makePriceString: makePriceString,
    makeTimestampString: makeTimestampString,
    removeDomChildren: removeDomChildren
  };

})();

var GetStartupDataApiController = (function() {

  /**
   * Private state
   */
  var getStartupDataApi = null;
  var successfulApiCallbackListeners = [];
  var failedLogicalApiCallbackListeners = [];
  var failedNonLogicalApiCallbackListeners = [];

  /**
   * fetch()
   * - fetches startup data
   */
  var fetch = function() {
    // Initialize api and bind event listeners
    if (getStartupDataApi === null) {
      getStartupDataApi = new GetStartupDataApi(ScopesNetwork);

      // Bind api listeners
      getStartupDataApi.setSuccessfulApiCallback(successfulApiCallback);
      getStartupDataApi.setLogicalApiFailureCallback(logicallyFailedApiCallback);
      getStartupDataApi.setNonLogicalApiFailureCallback(nonLogicallyFailedApiCallback);
    }

    // Fetch startup data from server
    getStartupDataApi.send();
  };

  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successfulApiCallbackListeners.length; ++i) {
      successfulApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };
  
  var logicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < logicallyFailedApiCallbackListeners.length; ++i) {
      logicallyFailedApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    console.nonLog("WARNING: Logically failed api response!");
    console.nonLog(api_response); 
    
    for (var i = 0; i < nonLogicallyFailedApiCallbackListeners.length; ++i) {
      nonLogicallyFailedApiCallbackListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  var registerSuccessfulApiCallback = function(callback) {
    successfulApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  var registerLogicalFailedApiCallback = function(callback) {
    logicallyFailedApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  var registerNonLogicalFailedApiCallback = function(callback) {
    logicallyFailedApiCallbackListeners.push(callback);
    return this;
  };

  return {
    fetch: fetch,
    registerSuccessfulApiCallback: registerSuccessfulApiCallback,
    registerLogicalFailedApiCallback: registerLogicalFailedApiCallback,
    registerNonLogicalFailedApiCallback: registerNonLogicalFailedApiCallback
  };
})();

var CenterPanelController = (function() {

  /**
   * Dom ui id's
   */
  var TITLE_LABEL_ID = 'center-page-title-label';

  /**
   * Attribute names
   */
  var HIDDEN_PAGE_ATTRIBUTE = 'hidden-page';

  /**
   * Dom nodes
   */
  var currentPage = null;
  var titleLabel = null;

  /**
   * Center panel data structures
   */
  var addExperimentPageInfo = {
    title: 'Add Experiment',
    container_id : 'add-exp-center-page',
    container : null
  };
  
  var myExperimentsPageInfo = {
    title: 'My Experiments',
    container_id : 'my-exp-center-page',
    container : null
  };
  
  var recordedExperimentsPageInfo = {
    title: 'Recorded Experiments',
    container_id : 'recorded-exp-center-page',
    container : null
  };

  var monitorExperimentPageInfo = {
    title: 'Monitor Experiment',
    container_id : 'monitor-exp-center-page',
    container : null
  };

  /**
   * changePage()
   * - change page to page indicated in 'next_page_info'
   */
  this.changePage = function(next_page_info) {
    // Check to see if 'currentPage' is set. If not, then this ui module is
    // just being initialized.
    if (currentPage != null) {
      // Skip change b/c we're switching to the same page
      if (next_page_info.container_id == currentPage.id) {
        return;
      }

      // Hide 'currentPage'
      console.assert(
        !currentPage.hasAttribute(HIDDEN_PAGE_ATTRIBUTE),
        'Illegal state: current page (id=' + currentPage.id + ') should not have the HIDDEN_LABEL_ATTRIBUTE'
      );

      currentPage.setAttribute(HIDDEN_PAGE_ATTRIBUTE, '');
    }

    // Display page indicated by 'next_page_info'
    if (next_page_info.container == null) {
      next_page_info.container = document.getElementById(next_page_info.container_id);
      console.assert(
        next_page_info.container != null,
        'Illegal state: next page (id=' + next_page_info.container_id + ') has invalid id'
      );
    }

    titleLabel.innerHTML = next_page_info.title;
    currentPage = next_page_info.container;
    currentPage.removeAttribute(HIDDEN_PAGE_ATTRIBUTE);
  };

  /**
   * init()
   * - bind dom ui nodes and event listeners, configure ui for startup
   */
  this.init = function() {
    // Load dom ui nodes
    titleLabel = document.getElementById(TITLE_LABEL_ID);

    // Configure Ui
    displayAddExperimentPage(); 
  };
  
  /**
   * dispalyAddExperimentPage()
   * - hide previous page and display add experiment page 
   */
  this.displayAddExperimentPage = function() {
    changePage(addExperimentPageInfo);
  };

  /**
   * dispalyMyExperimentsPage()
   * - hide previous page and display my experiments page 
   */
  this.displayMyExperimentsPage = function() {
    changePage(myExperimentsPageInfo);
  };

  /**
   * dispalyRecordedExperimentsPage()
   * - hide previous page and display recorded experiments page 
   */
  this.displayRecordedExperimentsPage = function() {
    changePage(recordedExperimentsPageInfo);
  };
  
  /**
   * dispalyMonitorExperimentPage()
   * - hide previous page and display monitor experiment page 
   */
  this.displayMonitorExperimentPage = function() {
    changePage(monitorExperimentPageInfo);
  };

  return {
    init: init,
    displayAddExperimentPage: displayAddExperimentPage,
    displayMyExperimentsPage: displayMyExperimentsPage,
    displayRecordedExperimentsPage: displayRecordedExperimentsPage,
    displayMonitorExperimentPage: displayMonitorExperimentPage
  };

})();

var ConfirmOrderUiController = (function() {
  
  /**
   * Class-bound ui symbols
   */
  var MULTIPLIER_LABEL_SYMBOL_INFO = {
    className: 'payment-multiplier-label',
    symbol: 'x'
  };

  var ASSIGNMENT_LABEL_SYMBOL_INFO = {
    className: 'payment-assignment-label',
    symbol: '='
  };

  var CURRENCY_UNIT_SYMBOL_INFO = {
    className: 'payment-currency-unit-label',
    symbol: '$'
  };

  /**
   * Private state
   */
  var isInitialized = false;
  var hourlyCost = 0;
  var scopesCount = 0;
  var experimentDuration = 0;
  var totalPrice = 0;
  var confirmOrderButtonOnClickListeners = [];
  var cancelOrderButtonOnClickListeners = [];

  /**
   * Dom Nodes
   */
  var rootNode = {
    id: 'pricing-confirmation-form-container',
    node: null
  };

  var confirmOrderButtonNode = {
    id: 'confirm-payment-button',
    node: null
  };
  
  var cancelOrderButtonNode = {
    id: 'cancel-payment-button',
    node: null
  };

  var scopesCountNode = {
    number: {
      id: 'payment-scopes-count-amount-label',
      node: null
    },
    unit: {
      id: 'payment-scopes-count-unit-label',
      node: null,
      singular: 'scope',
      plural: 'scopes'
    }
  };

  var experimentDurationNode = {
    number: {
      id: 'payment-experiment-duration-amount-label',
      node: null
    },
    unit: {
      id: 'payment-experiment-duration-unit-label',
      node: null,
      singular: 'hour',
      plural: 'hours'
    }
  };

  var hourlyPriceNode = {
    number: {
      id: 'payment-hourly-price-amount-label',
      node: null
    }
  };

  var paymentAmountNode = {
    id: 'payment-total-price-label',
    node: null
  };

  /**
   * Private methods
   */
  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindPriceComponentNode = function(price_component_node) {
    bindInternalNode(price_component_node.number); 
    if (price_component_node.hasOwnProperty("unit")) {
      bindInternalNode(price_component_node.unit); 
    }
  };

  var bindNodes = function() {
    bindInternalNode(rootNode); 
    bindInternalNode(paymentAmountNode);

    bindInternalNode(confirmOrderButtonNode);
    confirmOrderButtonNode.node.onclick = function() {
      for (var i = 0; i < confirmOrderButtonOnClickListeners.length; ++i) {
        confirmOrderButtonOnClickListeners[i](); 
      }
    };

    bindInternalNode(cancelOrderButtonNode);
    cancelOrderButtonNode.node.onclick = function() {
      for (var i = 0; i < cancelOrderButtonOnClickListeners.length; ++i) {
        cancelOrderButtonOnClickListeners[i](); 
      }
    };

    bindPriceComponentNode(scopesCountNode);
    bindPriceComponentNode(experimentDurationNode);
    bindPriceComponentNode(hourlyPriceNode);
  };

  var populateClassBoundUiSymbol = function(class_bound_ui_symbol) {
    var dom_nodes = rootNode.node.getElementsByClassName(class_bound_ui_symbol.className);
    for (var i = 0; i < dom_nodes.length; ++i) {
      dom_nodes[i].innerHTML = class_bound_ui_symbol.symbol;
    }
  };
  
  var initDisplay = function() {
    // Populate dom nodes with ui symbols 
    populateClassBoundUiSymbol(MULTIPLIER_LABEL_SYMBOL_INFO);
    populateClassBoundUiSymbol(ASSIGNMENT_LABEL_SYMBOL_INFO);
    populateClassBoundUiSymbol(CURRENCY_UNIT_SYMBOL_INFO);

    // Initialize price label
    setHourlyCost(0);
    setScopesCount(0);
    setExperimentDuration(0);
    updatePrice();
  };
  
  var updatePrice = function() {
    // Recompute price
    totalPrice = scopesCount * experimentDuration * hourlyCost;

    // Update price display
    paymentAmountNode.node.innerHTML = Utils.makePriceString(totalPrice); 
  };

  var updatePriceContributingNodeIfInitialized = function(price_contributing_node, value) {
    if (isInitialized) {
      // Update value
      price_contributing_node.number.node.innerHTML = value;

      // Update unit
      if (price_contributing_node.hasOwnProperty("unit")) {
        price_contributing_node.unit.node.innerHTML = (value === 1)
          ? price_contributing_node.unit.singular
          : price_contributing_node.unit.plural;
      }

      // Recompute price and update ui
      updatePrice();
    } 
  };

  /**
   * Public methods
   */
  var setHourlyCost = function(hourly_cost) {
    hourlyCost = hourly_cost;
    updatePriceContributingNodeIfInitialized(hourlyPriceNode, Utils.makePriceString(hourly_cost));
    return this;
  };

  var setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;
    updatePriceContributingNodeIfInitialized(scopesCountNode, scopes_count);
    return this;
  };

  var setExperimentDuration = function(experiment_duration) {
    experimentDuration = experiment_duration; 
    updatePriceContributingNodeIfInitialized(experimentDurationNode, experiment_duration);
    return this;
  };

  var registerConfirmOrderOnClickListener = function(callback) {
    confirmOrderButtonOnClickListeners.push(callback);
  };

  var registerCancelOrderOnClickListener = function(callback) {
    cancelOrderButtonOnClickListeners.push(callback);
  };

  var getTotalPrice = function() {
    return totalPrice; 
  };

  var init = function() {
    console.assert(isInitialized === false, "ERROR: don't initialize ConfirmOrderUiController more than once!");
    isInitialized = true;

    // Bind all nodes and attach event listeners
    bindNodes(); 
    
    // Render dynamic ui elements
    initDisplay();
  };

  return {
    init: init,
    setHourlyCost: setHourlyCost,
    setScopesCount: setScopesCount,
    setExperimentDuration: setExperimentDuration,
    registerConfirmOrderOnClickListener: registerConfirmOrderOnClickListener,
    registerCancelOrderOnClickListener: registerCancelOrderOnClickListener,
    getTotalPrice: getTotalPrice
  };
})();

var ExperimentDurationUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var EXPERIMENT_DURATION_UNIT_SINGULAR = "hour";
  var EXPERIMENT_DURATION_UNIT_PLURAL = "hours";

  /**
   * Private state
   */
  var experimentDuration = 0;
  var onChangeCallback = function(duration) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'duration-form-container',
    node: null
  };

  var validIconNode = {
    id: 'duration-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'duration-invalid-icon',
    node: null
  };
  
  var experimentDurationValueNode = {
    id: 'duration-display',
    node: null
  };

  var experimentDurationUnitNode = {
    id: 'duration-display-unit',
    node: null
  };

  var experimentDurationSliderNode = {
    id: 'duration-input',
    node: null
  };

  /**
   * Private functions
   */
  var showProperValidationIcon = function() {
    if (isValidInput()) {
      showValidIcon();
    } else {
      showInvalidIcon();
    }
  };

  var showValidIcon = function() {
    hideValidationIcon(invalidIconNode);
    showValidationIcon(validIconNode);
  };

  var showInvalidIcon = function() {
    hideValidationIcon(validIconNode);
    showValidationIcon(invalidIconNode);
  };

  var hideBothValidationIcons = function() {
    hideValidationIcon(invalidIconNode);
    hideValidationIcon(validIconNode);
  };

  var hideValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.setAttribute(HIDDEN_VALIDATION_ICON_ATTR, '');
  };

  var showValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.removeAttribute(HIDDEN_VALIDATION_ICON_ATTR);
  }

  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindNodes = function() {
    // Bind internal nodes
    bindInternalNode(rootNode);
    bindInternalNode(experimentDurationValueNode);
    bindInternalNode(experimentDurationUnitNode);
    bindInternalNode(experimentDurationSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    experimentDurationSliderNode.node.onchange = function() {
      experimentDuration = this.immediateValue;
      updateDurationDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateDurationDisplay = function() {
    // Render scope count value
    experimentDurationValueNode.node.innerHTML = experimentDuration;

    // Update scope count unit
    experimentDurationUnitNode.node.innerHTML = (experimentDuration === 1)
      ? EXPERIMENT_DURATION_UNIT_SINGULAR
      : EXPERIMENT_DURATION_UNIT_PLURAL;

    // Notify listeners
    onChangeCallback(experimentDuration);
  };

  /**
   * Public functions
   */
  var setDuration = function(experiment_duration) {
    experimentDuration = experiment_duration;

    // Update ui
    experimentDurationSliderNode.node.value = experiment_duration;
    updateDurationDisplay();

    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getDuration = function() {
    return experimentDuration;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scopes count
    setInitialState();
  };
  
  var setInitialState = function() {
    setDuration(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return experimentDuration !== 0; 
  };

  var signalInvalidInput = function() {
    // Short circuit if valid input...
    if (isValidInput()) {
      return;
    }

    showInvalidIcon();
  };

  return {
    init: init,
    setDuration: setDuration,
    getDuration: getDuration,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput,
    setInitialState: setInitialState
  };
})();

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
    calendarPicker.setInitialState();
    shortCodePicker.setInitialState();
    timePicker.setInitialState();
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

var ScopesCountUiController = (function() {
  
  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTR = "hidden";

  /**
   * Unit plural/singular
   */
  var SCOPES_UNIT_SINGULAR = "scope";
  var SCOPES_UNIT_PLURAL = "scopes";

  /**
   * Private state
   */
  var scopesCount = 0;
  var onChangeCallback = function(num_scopes) {};

  /**
   * Dom nodes
   */
  var rootNode = {
    id: 'scopes-count-input-container',
    node: null
  };
  
  var validIconNode = {
    id: 'scopes-count-valid-icon',
    node: null
  };
  
  var invalidIconNode = {
    id: 'scopes-count-invalid-icon',
    node: null
  };

  var scopesCountValueNode = {
    id: 'scopes-count-display',
    node: null
  };

  var scopesCountUnitNode = {
    id: 'scopes-count-display-unit',
    node: null
  };

  var scopesCountSliderNode = {
    id: 'scopes-count-input',
    node: null
  };

  /**
   * Private functions
   */
  var showProperValidationIcon = function() {
    if (isValidInput()) {
      showValidIcon();
    } else {
      showInvalidIcon();
    }
  };

  var showValidIcon = function() {
    hideValidationIcon(invalidIconNode);
    showValidationIcon(validIconNode);
  };

  var showInvalidIcon = function() {
    hideValidationIcon(validIconNode);
    showValidationIcon(invalidIconNode);
  };

  var hideBothValidationIcons = function() {
    hideValidationIcon(invalidIconNode);
    hideValidationIcon(validIconNode);
  };

  var hideValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.setAttribute(HIDDEN_VALIDATION_ICON_ATTR, '');
  };

  var showValidationIcon = function(validation_icon_node) {
    validation_icon_node.node.removeAttribute(HIDDEN_VALIDATION_ICON_ATTR);
  }

  var bindInternalNode = function(internal_node) {
    internal_node.node = document.getElementById(internal_node.id);
    console.assert(internal_node !== null, "ERROR: failed to bind internal node with id: " + internal_node.id);
  };

  var bindNodes = function() {
    // Bind internal nodes
    bindInternalNode(rootNode);
    bindInternalNode(scopesCountValueNode);
    bindInternalNode(scopesCountUnitNode);
    bindInternalNode(scopesCountSliderNode);
    bindInternalNode(validIconNode);
    bindInternalNode(invalidIconNode);

    // Attach event listeners
    scopesCountSliderNode.node.onchange = function() {
      scopesCount = this.immediateValue;
      updateScopesCountDisplay();
      
      // Show appropriate validation icon
      showProperValidationIcon();
    };
  };

  var updateScopesCountDisplay = function() {
    // Render scope count value
    scopesCountValueNode.node.innerHTML = scopesCount;

    // Update scope count unit
    scopesCountUnitNode.node.innerHTML = (scopesCount === 1)
      ? SCOPES_UNIT_SINGULAR
      : SCOPES_UNIT_PLURAL;
      
    // Notify listeners
    onChangeCallback(scopesCount);
  };

  /**
   * Public functions
   */
  var setScopesCount = function(scopes_count) {
    scopesCount = scopes_count;

    // Update ui
    scopesCountSliderNode.node.value = scopes_count;
    updateScopesCountDisplay();
    
    // Show appropriate validation icon
    showProperValidationIcon();
  };

  var getScopesCount = function() {
    return scopesCount;
  };

  var init = function() {
    // Bind dom nodes and attach event listeners
    bindNodes();

    // Initialize scope count and ui
    setInitialState();
  };

  var setInitialState = function() {
    setScopesCount(0);
    hideBothValidationIcons();
  };

  var setOnChangeCallback = function(callback) {
    onChangeCallback = callback;
  };

  var isValidInput = function() {
    return scopesCount !== 0; 
  };

  var signalInvalidInput = function() {
    // Short circuit if valid input...
    if (isValidInput()) {
      return;
    }

    showInvalidIcon();
  };

  return {
    init: init,
    setScopesCount: setScopesCount,
    getScopesCount: getScopesCount,
    setOnChangeCallback: setOnChangeCallback,
    isValidInput: isValidInput,
    signalInvalidInput: signalInvalidInput,
    setInitialState: setInitialState
  };
})();

var SidePanelUiController = (function() {
  
  /**
   * Ui node id's 
   */
  var CENTER_PAGE_TITLE_LABEL_ID = 'center-page-title-label';

  var NAVIGATION_BUTTON_CONTAINER_ID = 'nav-btns-container';

  /**
   * Navigation button info
   */
  var addExperimentPageInfo = {
    id: 'add-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayAddExperimentPage
  };

  var myExperimentsPageInfo = {
    id: 'my-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayMyExperimentsPage
  };
  
  var recordedExperimentsPageInfo = {
    id: 'recorded-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayRecordedExperimentsPage
  };
  
  var monitorExperimentPageInfo = {
    id: 'monitor-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayMonitorExperimentPage
  };

  var ADD_EXP_BTN_ID = 'add-exp-btn';
  var MY_EXP_BTN_ID = 'my-exp-btn';
  var RECORDED_EXP_BTN_ID = 'recorded-exp-btn';
  var MONITOR_EXP_BTN_ID = 'monitor-exp-btn';

  /**
   * Ui classes
   */
  var DASH_NAV_PANEL_BTN_CLASS = 'dash-nav-panel-btn';

  /**
   * Ui attributes
   */
  var SELECTED_ATTR = 'selected';
  
  /**
   * Ui nodes
   */
  var centerPageTitleLabel = null;

  /**
   * Id to node info map
   */
  var idToNodeInfoMap = {};

  var currentSelectedPageNode = null;

  /**
   * changeCenterPage()
   * - switch center page
   */
  var changeCenterPage = function(next_page_id) {
    // Check that page id is valid
    console.assert(
        idToNodeInfoMap.hasOwnProperty(next_page_id),
        'illegal key in idToNodeInfoMap: ' + next_page_id
      );

    // At startup, we don't have a 'current_page,' so we jump
    // immediately to the 'next_page' rendering
    if (currentSelectedPageNode != null) {
      // Skip page change because same page would be rendered
      if (currentSelectedPageNode.id == next_page_id) {
        return;
      }

      // Deselect current page
      console.assert(currentSelectedPageNode.hasAttribute(SELECTED_ATTR));
      currentSelectedPageNode.removeAttribute(SELECTED_ATTR); 
    }

    // Fetch 'next_page'
    var next_page_info = idToNodeInfoMap[next_page_id];

    // Lazy load ui dom node
    if (next_page_info.node == null) {
      next_page_info.node = document.getElementById(next_page_info.id);
      console.assert(
        next_page_info.node != null,
        'Illegal state: failed to lazy load side panel nav button (id=' + next_page_id + ')'
      );
    }
    
    console.assert(
        !next_page_info.node.hasAttribute(SELECTED_ATTR),
        'Illegal state: next-page (id=' + next_page_id + ') already has SELECTED_ATTR'
    );

    // Select new page and render center page
    next_page_info.node.setAttribute(SELECTED_ATTR, "");
    next_page_info.displayCenterPagePtr();

    // Update 'currentSelectedPageNode'
    currentSelectedPageNode = next_page_info.node;
  };

  /**
   * init()
   * - initialize ui node bindings, event listeners, and starting
   *   ui state
   */
  var init = function() {
    // Init DOM nodes
    centerPageTitleLabel = document.getElementById(CENTER_PAGE_TITLE_LABEL_ID);

    // Init id to ui node map
    idToNodeInfoMap[ADD_EXP_BTN_ID] = addExperimentPageInfo;
    idToNodeInfoMap[MY_EXP_BTN_ID] = myExperimentsPageInfo;
    idToNodeInfoMap[RECORDED_EXP_BTN_ID] = recordedExperimentsPageInfo;
    idToNodeInfoMap[MONITOR_EXP_BTN_ID] = monitorExperimentPageInfo;

    // Bind event listeners
    document.getElementById(NAVIGATION_BUTTON_CONTAINER_ID).onclick = function(event) {
      // Search event propagation path for selected navigation button
      for (var i=0; i < event.path.length; ++i) {
        var node = event.path[i];
        if (node.classList.contains(DASH_NAV_PANEL_BTN_CLASS)) {
          changeCenterPage(node.id);
          break;
        }
      }
    };

    // Set initial page: new experiment
    changeCenterPage(ADD_EXP_BTN_ID);
  };

  return {
    init: init
  };
})();

ConfirmOrderApi.prototype = new ScopesApi();
ConfirmOrderApi.prototype.constructor = ConfirmOrderApi;

function ConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x3;

  // Api request field keys
  this.apiKeys = {
    scopes_count: "scopes-count",
    experiment_duration: "duration",
    start_timestamp: "start-timestamp",
    short_code_id: "short-code-id",
    price: "price"
  };
}

ConfirmOrderApi.prototype.getApiKeys = function() {
  return this.apiKeys; 
};

ConfirmOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.apiKeys.scopes_count] = scopes_count;
  return this;
};

ConfirmOrderApi.prototype.setExperimentDuration = function(duration) {
  this.data[this.apiKeys.experiment_duration] = duration;
  return this;
};

ConfirmOrderApi.prototype.setStartTimestamp = function(start_timestamp) {
  this.data[this.apiKeys.start_timestamp] = start_timestamp;
  return this;
};

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.apiKeys.short_code_id] = short_code_id;
  return this;
};

ConfirmOrderApi.prototype.setPrice = function(price) {
  this.data[this.apiKeys.price] = price;
  return this;
};

GetAllUsersApi.prototype = new ScopesApi();
GetAllUsersApi.prototype.constructor = GetAllUsersApi;

function GetAllUsersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xD;
}

GetOrderPricePolicyApi.prototype = new ScopesApi();
GetOrderPricePolicyApi.prototype.constructor = GetOrderPricePolicyApi;

function GetOrderPricePolicyApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x14;
}

GetStartupDataApi.prototype = new ScopesApi();
GetStartupDataApi.prototype.constructor = GetStartupDataApi;

function GetStartupDataApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x15;
}

GetStartupDataApi.prototype.getApiKeys = function() {
  return {
    first_name: 'first_name',
    last_name: 'last_name',
    email: 'email',
    hourly_price: 'hourly_price',
    short_codes: 'short_codes'
  };
};

/**
 * ScopesApi
 * - base class for all api calls.
 * @req: all child classes assign 'this.apiType' to corresponding api-type value
 *       in constructor.
 * @req: all child classes assign 'network_module' to 'this.networkModule'
 *       in constructor
 * @override: 
 *        - nonLogicalApiFailureCallback()
 *        - logicalApiFailureCallback()
 *        - successfulApiCallback()
 */
function ScopesApi(network_module) {

  /**
   * Api parameters 
   */
  this.IS_SUCCESSFUL_KEY = "is_successful";
  this.API_TYPE_KEY = "api_type";

  this.networkModule = network_module;
  this.data = {};
  this.isAsync = true;
  this.uploadedFile = null;

  /**
   * isWellFormedApiResponseWrapper()
   * - checks that 'json_response' contains the fields characteristic of all
   *   responses (both successful and failed)
   * @param JSON json_response: response payload
   */
  this.isWellFormedApiResponseWrapper = function(json_response) {
    return this.IS_SUCCESSFUL_KEY in json_response &&
      this.API_TYPE_KEY in json_response;
  };

  /**
   * nonLogicalApiFailureCallback()
   * - callback register for handling non-logical api failures (e.g. bad request)
   * - user overrides this function to register callback
   */
  this.nonLogicalApiFailureCallback = function(xhttp_response) {}

  /**
   * logicalApiFailureCallback()
   * - callback for handling logical api failures (e.g. user not found)
   * - user overrides this function to register callback
   */
  this.logicalApiFailureCallback = function(json_response) {}

  /**
   * successfulApiCallback()
   * - callback for handling successful api call
   * - user overrides this function to register callback
   */
  this.successfulApiCallback = function(json_response) {};

  /**
   * handleMalformedApiResponseWrapper()
   * - callback for malformed api response
   */
  this.handleMalformedApiResponseWrapper = function(xhttp_response) {
    console.log("API ERROR: Malformed api response", xhttp_response);
    this.prototype.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * handleJsonParseError()
   * - callback for json parse error in api call 
   */
  this.handleJsonParseError = function(xhttp_response) {
    console.log("API ERROR: Json parse error");
    this.prototype.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * networkSuccessCallbackWrapper()
   * - callback for ScopesNetwork when network call succeeds
   */
  this.networkSuccessCallbackWrapper = function(xhttp_response) {
    try {
      // Deserialize json payload
      var json_response = JSON.parse(xhttp_response.responseText);
     
      // Check that wrapper api keys are present (should be here whether api
      // call succeeded or not...)
      if (!this.isWellFormedApiResponseWrapper(json_response)) {
        this.handleMalformedApiResponseWrapper(xhttp_response);
      }

      // Check if api call succeeded
      if (!json_response[this.IS_SUCCESSFUL_KEY]) {
        // Api logical failure. Should have meaningful api failure code...
        this.logicalApiFailureCallback(json_response);
      }

      // Api call succeeded. Pass off to next handler
      this.successfulApiCallback(json_response);
    } catch (parse_exception) {
      // Failed to parse json api response
      this.handleJsonParseError(xhttp_response);
    }
  };

  /**
   * networkFailureCallbackWrapper()
   * - callback for network failure when making api call
   */
  this.networkFailureCallbackWrapper = function(xhttp_response) {
    console.log("API ERROR: Network failure durng api call");
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

}

ScopesApi.prototype.setIsAsync = function(is_async) {
  this.isAsync = is_async;
  return this;
}

ScopesApi.prototype.setSuccessfulApiCallback = function(callback) {
  this.successfulApiCallback = callback;
  return this;
}

ScopesApi.prototype.setLogicalApiFailureCallback = function(callback) {
  this.logicalApiFailureCallback = callback;
  return this;
}

ScopesApi.prototype.setNonLogicalApiFailureCallback = function(callback) {
  this.nonLogicalApiFailureCallback = callback;
  return this;
}

ScopesApi.prototype.setFile = function(file) {
  this.uploadedFile = file;
  return this;
}

ScopesApi.prototype.send = function() {
  return this.networkModule.request(
    this.apiType,
    this.data,
    this.isAsync,
    this.networkSuccessCallbackWrapper,
    this.networkFailureCallbackWrapper,
    this.uploadedFile,
    this
  );    
}

var ScopesNetwork = (function() {
  
  var ENDPOINT_PATH = "hhvm/endpoints/endpoint.hh";

  var API_TYPE_KEY = "api_type";

  var PAYLOAD_KEY = "payload";

  var VIDEO_UPLOAD_KEY = "video";

  var HTTP_REQUEST_TYPE = "POST";

  var CONTENT_TYPE_KEY = "Content-Type";

  var WWW_FORM_URLENCODED_CONTENT_TYPE = "application/x-www-form-urlencoded";

  var PARAMETER_ASSIGNMENT_TOKEN = "=";

  var PARAMETER_SEPARATOR_TOKEN = "&";

  return {
    /**
     * request()
     * @param int api_type: index of specified api 
     * @param array<string, mixed> payload_fields: payload parameters
     * @param bool is_async: is request synchronous
     * @param function(XMLHttpRequest xhttp) network_success_callback: callback function for when request finishes successfully
     * @param function(XMLHttpRequest xhttp) network_failure_callback: callback function for when request finishes with failure
     * @param File upload_file: optional file upload parameter
     */
    request: function(
     api_type,
     payload_fields,
     is_async,
     network_success_callback,
     network_failure_callback,
     upload_file,
     scopes_api_context
   ) {
      var xhttp = new XMLHttpRequest(); 
      
      // Bind callbacks
      if (is_async) {
        xhttp.onreadystatechange = function() {
          if (xhttp.readyState == 4) {
            if (xhttp.status == 200) {
              scopes_api_context.networkSuccessCallbackWrapper(xhttp); 
            } else {
              scopes_api_context.networkFailureCallbackWrapper(xhttp);
            }
          }
        };
      }

      // Bind http destination and request type
      xhttp.open(
        HTTP_REQUEST_TYPE,
        ENDPOINT_PATH,
        is_async
      );

      console.log(ENDPOINT_PATH);

      // Assemble payload
      var serialized_payload = JSON.stringify(payload_fields);

      var form_data = new FormData();
      
      if (upload_file != null) {
        form_data.append(VIDEO_UPLOAD_KEY, upload_file);
        console.log(VIDEO_UPLOAD_KEY);
        console.log(upload_file);
      }

      form_data.append(API_TYPE_KEY, api_type);
      form_data.append(PAYLOAD_KEY, serialized_payload);

      // Execute request 
      xhttp.send(form_data);

      if (!is_async) {
        return xhttp.responseText;
      }
    }  
  }
}());

function Calendar(
  template_store,
  calendar_id,
  disallowed_week_days,
  irregular_disallowed_days,
  forward_month_limit,
  min_num_days_in_advance
) {

  /**
   * Date style tokens
   */
  var SHORT_DOW_ABBREVIATION_TOKEN = '.';
  var DOM_DELIMITER = ',';

  /**
   * Template name constants
   */
  var TEMPLATE_ID = '#calendar-template';

  /**
   * Html class names
   */
  var DATE_CLASS = 'date';
  var UNSELECTABLE_DATE_CLASS = 'unselectable-date';
  var SELECTABLE_DATE_CLASS = 'selectable-date';
  var DATE_LABEL_CLASS = 'date-label';
  var WEEK_CLASS = 'week';

  /**
   * Html attribute names
   */
  var SELECTED_DATE_ATTR = 'selected-date';
  var DISABLED_MONTH_NAV_ATTR = 'disabled';
  var HIDDEN_ATTR = 'hidden';
  var CLOSED_ATTR = 'closed';

  /**
   * Class constants
   */
  var JS_YEAR_OFFSET = 1900;
  var JS_DATE_LOCALE = 'en-us';

  var SHORT_DAY_OF_THE_WEEK_NAMES = [
    'Sun',
    'Mon',
    'Tue',
    'Wed',
    'Thu',
    'Fri',
    'Sat'
  ];

  var LONG_DAY_OF_THE_WEEK_NAMES = [
    'Sunday',
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday'
  ];
  
  var LONG_MONTH_NAMES = [
    'January',
    'February',
    'March',
    'April',
    'May',
    'June',
    'July',
    'August',
    'September',
    'October',
    'November',
    'December'
  ];

  var SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  // Js utility pointers
  var that = this;
  var jsDate = null;

  // Calendar State
  var templateStore = template_store;
  var minNumDaysInAdvance = min_num_days_in_advance;
  var disallowedWeekDays = disallowed_week_days;
  var irregularDisallowedDays = irregular_disallowed_days;
  var isEnabled = true;
  var isVisible = false;
  
  var monthDisplacement = 0;
  var maxMonthDisplacement = forward_month_limit;

  /**
   * Stores information for the current date
   */
  var currentDateObj = {
    date: null,
    month: null,
    year: null
  };

  /**
   * Stores information for the current *selected* date
   */
  var selectedDateObj = {
    date: null,
    month: null,
    year: null,
    selectedDateNode: null
  };

  /**
   * Stores information for the month that is currently displayed
   */
  var calendarMonthObj = {
    month: null,
    year: null,
    startingDayOfTheWeek: null
  };

  /**
   * Dom node info
   */
  // Calendar root
  var calendarRootNodeInfo = {
    id: calendar_id,
    node: null
  };

  var calendarWrapperNodeInfo = {
    className: 'calendar-wrapper',
    node: null
  };

  var selectedMonthLabelNodeInfo = {
    className: 'selected-month-label',
    node: null
  };
  
  var selectedDomLabelNodeInfo = {
    className: 'selected-dom-label',
    node: null
  };

  var selectedYearLabelNodeInfo = {
    className: 'selected-year-label',
    node: null
  };

  // Month nav node info
  var monthNavDisplayNodeInfo = {
    className: 'month-label',
    node: null
  };

  var decrementMonthNavNodeInfo = {
    className: 'decrement-month-container',
    node: null
  };
  
  var incrementMonthNavNodeInfo = {
    className: 'increment-month-container',
    node: null
  };
  
  // Selectable dates node info
  var selectableDaysContainerNodeInfo = {
    className: 'selectable-dates-container',
    node: null
  };

  var selectedDateDisplayContainer = {
    className: 'selected-date-display-container',
    node: null
  };

  var calendarMainContainerNodeInfo = {
    className: 'calendar-main-container',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * fetchClassBoundDomNode()
   * - fetch the dom node indicated by the provided class-name
   * @param Object node_info: datastructure for the node (see above for example)
   */
  function fetchClassBoundDomNode(node_info) {
    elements = calendarRootNodeInfo.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * initInternalCalendarNodes()
   * - initialize dom node pointers
   * - binds event listeners
   */
  function initInternalCalendarNodes() {
    // Bind all nodes and init their event listeners
    fetchClassBoundDomNode(calendarWrapperNodeInfo);

    // Selected display date nodes
    fetchClassBoundDomNode(selectedYearLabelNodeInfo);
    fetchClassBoundDomNode(selectedDomLabelNodeInfo);
    fetchClassBoundDomNode(selectedMonthLabelNodeInfo);

    fetchClassBoundDomNode(calendarMainContainerNodeInfo);
    fetchClassBoundDomNode(selectedDateDisplayContainer);

    selectedDateDisplayContainer.node.onclick = function(event) {
      if (isVisible) {
        hideCalendar();
      } else {
        showCalendar();
      }
    };

    // Month nav nodes
    fetchClassBoundDomNode(monthNavDisplayNodeInfo);
    fetchClassBoundDomNode(decrementMonthNavNodeInfo);
    fetchClassBoundDomNode(incrementMonthNavNodeInfo);
    
    // Month navigation button event listeners
    decrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(false); 
    };
    
    incrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(true); 
    };

    // Selectable dates node info
    fetchClassBoundDomNode(selectableDaysContainerNodeInfo);

    // Selectable dates event listener
    selectableDaysContainerNodeInfo.node.onclick = function(event) {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }

      // Search event propagation list to find selectable-date node
      var date = null;
      for (var i = 0; i < event.path.length; ++i) {
        if (Utils.hasClass(SELECTABLE_DATE_CLASS, event.path[i])) {
          date = event.path[i];
          break;
        } 
      }

      // Kill event if a selectable-date wasn't clicked
      if (date == null) {
        return;
      }

      // Kill event here b/c this date is already selected!
      if (date.hasAttribute(SELECTED_DATE_ATTR)) {
        return;
      }

      // Extract the numerical date
      console.assert(date.childNodes.length == 1);
      var label = date.childNodes[0];
      console.assert(Utils.hasClass(DATE_LABEL_CLASS, label));

      var date_idx = parseInt(label.innerHTML);

      // Clear current selected date
      if (selectedDateObj.selectedDateNode != null) {
        selectedDateObj.selectedDateNode.removeAttribute(SELECTED_DATE_ATTR);
      } 

      // Render current selected date
      date.setAttribute(SELECTED_DATE_ATTR, '');
      selectedDateObj.selectedDateNode = date;
      selectedDateObj.date = date_idx;

      // Update selected date top-banner display
      updateSelectedDowDisplay(date_idx);
      updateSelectedMonthDisplay(calendarMonthObj.month);

      // Hide calendar body
      hideCalendar();
    };

    // Hide calendar if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the screen, so don't hide!
        if (node.id == calendarRootNodeInfo.node.id) {
          return;
        }
      }

      // User clicked off the calendar, so hide it!
      hideCalendar();
    });
  };

  function hideCalendar() {
    isVisible = false;  
    calendarMainContainerNodeInfo.node.setAttribute(HIDDEN_ATTR, ''); 
    calendarWrapperNodeInfo.node.setAttribute(CLOSED_ATTR, '');
  };

  function showCalendar() {
    isVisible = true; 
    calendarMainContainerNodeInfo.node.removeAttribute(HIDDEN_ATTR); 
    calendarWrapperNodeInfo.node.removeAttribute(CLOSED_ATTR);
  };

  /**
   * shiftMonth()
   * - increment/decrement month and update ui
   * @param: bool is_increment: true iff incrementing month
   */
  function shiftMonth(is_increment) {
    // Kill event if increments month past forward limit
    if (is_increment && monthDisplacement == maxMonthDisplacement) {
      return;
    }

    // Kill event if decrements month past current one
    if (!is_increment && monthDisplacement == 0) {
      return;
    }

    if (is_increment) {
      ++monthDisplacement; 
      if (monthDisplacement == maxMonthDisplacement) {
        // Update forward month-nav-arrow to signal that it can't go forward anymore 
        incrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');  
        decrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    } else {
      --monthDisplacement;
      if (monthDisplacement == 0) {
        // Update backward month-nav-arrow to signal that it can't go backward anymore 
        decrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');
        incrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    }

    // Render new grid for month
    var month_offset = monthDisplacement + selectedDateObj.month;
    var year_offset = Math.floor(month_offset / 12);
    var next_year = year_offset + selectedDateObj.year;
    var next_month = month_offset % 12;

    // Update internal calendar state
    calendarMonthObj.month = next_month;
    calendarMonthObj.year = next_year;
    var starting_day_of_week_obj = new Date(next_year, next_month, 1);
    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();

    updateMonthDisplayGrid(next_month, next_year);
    updateCurrentMonthDisplay(next_month);
  };

  function initDate() {
    // Capture today's date and initialize calendar state
    var current_date_js_obj = new Date(); 
    
    // Adjust first available day with min-num-days-in-advance offset
    current_date_js_obj = new Date(
      current_date_js_obj.getUTCFullYear(),
      current_date_js_obj.getMonth(),
      current_date_js_obj.getDate() + minNumDaysInAdvance
    );

    // Set current date
    currentDateObj.date = current_date_js_obj.getUTCDate();
    currentDateObj.month = current_date_js_obj.getUTCMonth();
    currentDateObj.year = current_date_js_obj.getUTCFullYear();
   
    // Initialize selected date to current date
    selectedDateObj.date = current_date_js_obj.getUTCDate();
    selectedDateObj.month = current_date_js_obj.getUTCMonth();
    selectedDateObj.year = current_date_js_obj.getUTCFullYear();

    // Initialize calendar grid state to current month
    calendarMonthObj.month = selectedDateObj.month;
    calendarMonthObj.year = selectedDateObj.year;

    // Determine starting day of the week for the selected date
    var starting_day_of_week_obj = new Date(
      calendarMonthObj.year,    
      calendarMonthObj.month,    
      1
    );

    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();
  };

  /**
   * updateSelectedDowDisplay()
   * - update the selected-date banner
   * @param Obj selected_date: {int date, int month, int year}
   */
  function updateSelectedDowDisplay(date) {
    // var date_label = computeSelectedDowLabel(date);
    // selectedDowLabelNodeInfo.node.innerHTML = date_label;
    selectedDomLabelNodeInfo.node.innerHTML = date + DOM_DELIMITER;
  };

  function updateSelectedMonthDisplay(month) {
    var month_label = computeSelectedMonthLabel(month);
    selectedMonthLabelNodeInfo.node.innerHTML = month_label;
  };

  function updateCurrentMonthDisplay(month) {
    var month_label = computeCurrentSelectedMonthLabel(month);
    monthNavDisplayNodeInfo.node.innerHTML = month_label; 
  };

  function updateSelectedYearDisplayLabel(year) {
    var year_label = computeSelectedYearLabel(year); 
    selectedYearLabelNodeInfo.node.innerHTML = year_label;
  };

  function generateDateNode() {
    var date_node = document.createElement('div');
    date_node.className = DATE_CLASS;
    return date_node;
  };

  function generateBlankDateNode() {
    return generateDateNode();
  };

  /**
   * generateDateLabelNode()
   * - dynamically generate html node for displaying an individual
   *   date in the calendar
   * @param int date: day of the month 
   */
  function generateDateLabelNode(date) {
    var date_label_node = document.createElement('div');
    var label = document.createElement('span');
    label.className = DATE_LABEL_CLASS;
    label.innerHTML = date;
    date_label_node.appendChild(label);
    return date_label_node;
  };

  /**
   * generateSelectableDateNode()
   * - dynamically generates html node representing date
   *   within this month that can be selected.
   */
  function generateSelectableDateNode(date) {
    var selectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = SELECTABLE_DATE_CLASS;
    selectable_date_node.appendChild(date_label_node);
    return selectable_date_node; 
  };

  /**
   * generateUnselectableDateNode()
   * - dynamically generates html node representing
   *   date wthin this month that can't be selected, 
   *   e.g. date has already passed or date is already
   *   booked
   */
  function generateUnselectableDateNode(date) {
    var unselectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = UNSELECTABLE_DATE_CLASS;
    unselectable_date_node.appendChild(date_label_node);
    return unselectable_date_node; 
  };

  /**
   * generateWeekNode()
   * - dynamically generate the node for 1 row in the calendar
   */
  function generateWeekNode() {
    var week_node = document.createElement('div');
    week_node.className = WEEK_CLASS;
    return week_node;
  };

  /**
   * updateMonthDisplayGrid()
   * - dynamically generate date cells for this month
   * @param int month: [0, 11] indicating month index
   * @param int year: any year
   */
  function updateMonthDisplayGrid(month, year) {
    // Clear existing week-nodes within the calendar grid
    while (selectableDaysContainerNodeInfo.node.hasChildNodes()) {
      selectableDaysContainerNodeInfo.node.removeChild(selectableDaysContainerNodeInfo.node.lastChild);
    }

    // Get starting day-of-week idx
    var new_date = new Date(year, month);
    var starting_day_idx = new_date.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0); // hacky :/
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate dynamic html nodes for days in last week of previous month that appear
    // in first week of this month, e.g. last few days
    var current_week = generateWeekNode();
    selectableDaysContainerNodeInfo.node.appendChild(current_week);

    for (var i = 0; i < starting_day_idx; ++i) {
      var blank_node = generateBlankDateNode();
      current_week.appendChild(blank_node);
    }
    
    // Generate dynamic html nodes for displaying selectable days in month
    for (var i = 1; i <= num_days_in_month; ++i) { // fewer ops with these loop conditions
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = generateWeekNode();
        selectableDaysContainerNodeInfo.node.appendChild(current_week);
      }

      // Create date node: date node is 'unselectable' iff it is on either
      // of the 'disallowed' lists or if it occurs before the specified
      // min-number-days-in-advance threshold
      var date_node = (disallowedWeekDays.has(current_week.childNodes.length)) || 
          (month == currentDateObj.month && i < currentDateObj.date)
        ? generateUnselectableDateNode(i)
        : generateSelectableDateNode(i);

      current_week.appendChild(date_node);
    }
  }

  /**
   * initDisplay()
   * - initialize calendar display
   * - generate and bind dynamic nodes
   * @pre-condition: 'selectedDateObj' must be initialized to current date
   */
  function initDisplay() {
    // Render grid of dates
    updateMonthDisplayGrid(selectedDateObj.month, selectedDateObj.year);

    // Render banner date label for current date
    updateSelectedDowDisplay(selectedDateObj.date);

    // Render banner month label for current date
    updateSelectedMonthDisplay(selectedDateObj.month);

    // Render banner year label for current date 
    updateSelectedYearDisplayLabel(selectedDateObj.year);

    // Render calendar month label for grid
    updateCurrentMonthDisplay(selectedDateObj.month);

    // Render or hide main calendar content on startup
    if (isVisible) {
      showCalendar();
    } else {
      hideCalendar();
    }
  };

  /**
   * computeCurrentSelectedMonthLabel()
   * - return the month label for the calendar title itself (not the banner)
   * @param int month: [0-11] month index
   */
  function computeCurrentSelectedMonthLabel(month) {
    return LONG_MONTH_NAMES[month]; 
  };

  /**
   * computeSelectedDowLabel()
   * - return date label: '<day of the week>, <numerical day of the month>'
   * @param int date: numerical day of the month
   */
  function computeSelectedDowLabel(date) {
    var day_of_week_idx = (date + calendarMonthObj.startingDayOfTheWeek - 1) % 7;
    return SHORT_DAY_OF_THE_WEEK_NAMES[day_of_week_idx] + SHORT_DOW_ABBREVIATION_TOKEN;
  };

  /**
   * computeSelectedMonthLabel()
   * - return short month label for top-banner displaying selected date
   * @param int month_idx: [0-11] month index of selected month
   */
  function computeSelectedMonthLabel(month_idx) {
    return SHORT_MONTH_NAMES[parseInt(month_idx)]; 
  };

  /**
   * computeSelectedYearLabel()
   * - return year label for top-banner displaying selected date
   * @param int year: year index (UTC)
   */
  function computeSelectedYearLabel(year) {
    // Must have valid date
    return year;
  };

  /**
   * setDate()
   * - set date state and update ui
   * @pre-condition: params must correspond to valid date
   * @param int day: day of the month index
   * @param int month: month index
   * @param int year: year index
   */
  function setDate(day, month, year) {
    // TODO: write api for setting date externally 
  };

  /**
   * synthesizeCalendarTemplate()
   * - copy calendar template and insert into main dom tree
   * @pre-condition: 'calendarRootNodeInfo' must be initialized
   */
  function synthesizeCalendarTemplate() {
    // Bind calendar dom template 
    var calendar_template = templateStore.import.querySelector(TEMPLATE_ID);
    var calendar_clone = document.importNode(calendar_template.content, true);
    calendarRootNodeInfo.node.appendChild(calendar_clone);
  };

  function setInitialStateInternal() {
    // Cache today's date
    initDate();

    // Load ui
    initDisplay();
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - bind all nodes, initialize state and ui
   * - bind event listeners
   */
  this.init = function() {
    // Initialize top-level calendar node (we're going to copy the template into this!)
    calendarRootNodeInfo.node = document.getElementById(calendarRootNodeInfo.id);

    // Copy the template and insert into root node
    synthesizeCalendarTemplate();

    // Initialize dom nodes internal to the calendar object
    initInternalCalendarNodes();

    // Initialize and configure calendar date
    setInitialStateInternal();
  };

  /**
   * disable()
   * - disable event listeners and render 'disabled' ui
   */
  this.disable = function() {
    isEnabled = false;
  };

  /**
   * enable()
   * - enable event listeners and render 'enabled' ui
   */
  this.enable = function() {
    isEnabled = true;
  };

  /**
   * getSelectedDate()
   * - return selected date
   */
  this.getSelectedDate = function() {
    return {
      year: selectedDateObj.year,
      month: selectedDateObj.month + 1, // b/c month is 0 indexed internally
      date: selectedDateObj.date
    };
  };

  /**
   * setInitialState()
   * - select initial date
   */
  this.setInitialState = function() {
    setInitialStateInternal();
  };
};

function ShortCodePicker(
  template_store,
  id,
  short_codes // {id, code, alias}, optional
) {

  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var INPUT_FIELD_WRAPPER_TOOLTIP_ATTR = 'tooltip';
  var OPTION_LOCAL_IDX_ATTR = 'local-idx';
  var OPTION_TOOLTIP_ATTR = 'tooltip';
  var OPTION_SELECTED_ATTR = 'selected-option';

  /**
   * Html class names
   */
  var SHORT_CODE_LABEL_CLASS = 'short-code-label';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-option';
  var SHORT_CODE_PICKER_OPTION_CLASS = 'short-code-picker-option';

  /**
   * Html template id names
   */
  var MAIN_TEMPLATE_ID = '#short-code-picker-template';
  var OPTION_TEMPLATE_ID = '#short-code-picker-option-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var shortCodes = typeof short_codes == 'undefined' ? [] : short_codes;
  var isDropDownOpen = false;
  var selectedOptionIndex = null;

  /**
   * Dom nodes
   */
  var rootNode = {
    nodeId: id,
    node: null
  };

  var shortCodePickerWrapperNode = {
    class: 'short-code-picker-wrapper',
    node: null
  };
  
  var inputFieldLabelNode = {
    class: 'input-field-label',
    node: null
  };

  var inputFieldNode = {
    class: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    class: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    class: 'short-code-dropdown',
    node: null
  };

  // Private functions
  /**
   * synthesizeShortCodePickerTemplate()
   * - copy template and insert into root node
   * @pre-condition: root node is initialized 
   */
  var synthesizeShortCodePickerTemplate = function() {
    var short_code_picker_template = templateStore.import.querySelector(MAIN_TEMPLATE_ID);
    var short_code_picker_clone = document.importNode(short_code_picker_template.content, true);
    rootNode.node.appendChild(short_code_picker_clone);
  };

  /**
   * openDropDown()
   * - opens drop-down menu
   */
  var openDropDown = function() {
    isDropDownOpen = true;
    shortCodePickerWrapperNode.node.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };
 
  /**
   * closeDropDown()
   * - closes drop-down menu
   */
  var closeDropDown = function() {
    isDropDownOpen = false;    
    shortCodePickerWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * initOptionNode()
   * - clone new option node
   * - bind data and event listeners
   * - insert into drop-down
   * @param Object option: option struct provided in constructor
   */
  var initOptionNode = function(option) {
    // Clone new option node from template
    var short_code_picker_option_template = templateStore.import.querySelector(OPTION_TEMPLATE_ID);  
    var short_code_picker_option_clone = document.importNode(short_code_picker_option_template.content, true);

    // Add to drop-down (activates node so that we can now bind data/event listeners)
    dropDownNode.node.appendChild(short_code_picker_option_clone); 

    // Bind data
    var short_code_picker_option_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(short_code_picker_option_list.length > 0);
    var option_local_idx = short_code_picker_option_list.length - 1; 
    var short_code_picker_option = short_code_picker_option_list[option_local_idx];

    // Local index (index of short-code in local array of short-code objects)
    short_code_picker_option.setAttribute(OPTION_LOCAL_IDX_ATTR, option_local_idx);
   
    // Tooltip (actual short code number, not just name)
    short_code_picker_option.setAttribute(OPTION_TOOLTIP_ATTR, option.code);
   
    // Short code name (name given by user, not just number)
    var short_code_label_node_list = short_code_picker_option.getElementsByClassName(SHORT_CODE_LABEL_CLASS);
    console.assert(short_code_label_node_list.length == 1);
    short_code_label_node_list[0].innerHTML = option.alias;
  };

  /**
   * bindInternalNode()
   * - bind the specified dom node (must be internal to this short-code-picker)
   * @param: Obj internal_node: internal dom node (see 'inputFieldNode' for structure)
   * @pre-condition: root node bound 
   */
  var bindInternalNode = function(internal_node) {
    // We bind internal nodes once only!
    console.assert(internal_node.node == null); 

    // Fetch internal node by class
    var node_set = rootNode.node.getElementsByClassName(internal_node.class);

    // We should only find one *internal* node with this class
    console.assert(node_set.length == 1);

    internal_node.node = node_set[0];
  };

  /**
   * initMainNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initMainNodes = function() {
    // Bind top-level node in short-code-picker template
    bindInternalNode(shortCodePickerWrapperNode);
    
    // Bind input field and configure event listener
    bindInternalNode(inputFieldLabelNode);
    bindInternalNode(inputFieldNode);
    bindInternalNode(inputFieldWrapperNode);

    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    // Bind time dropdown field and configure event listener
    bindInternalNode(dropDownNode);

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected short-code 
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(SHORT_CODE_PICKER_OPTION_CLASS, node)) {
          // Capture selected option
          var local_idx_str = node.getAttribute(OPTION_LOCAL_IDX_ATTR);
          console.assert(local_idx_str != null);

          var local_idx = parseInt(local_idx_str);
          console.assert(local_idx != null);

          // Deselect previously selected option
          unselectOptionByIndex(selectedOptionIndex);

          // Select clicked option
          selectOptionByIndex(local_idx);

          return;
        }
      }
    };

    // Hide short-code picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        // User clicked on the time-picker, so don't hide it!
        if (Utils.hasClass(shortCodePickerWrapperNode.class, node)) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  }
 
  /**
   * initOptionNodes()
   * - initialize nodes for short code options
   */
  var initOptionNodes = function() {
    // Clear existing nodes
    Utils.removeDomChildren(dropDownNode.node);

    // Generate option nodes and insert into parent
    for (var i = 0; i < shortCodes.length; ++i) {
      initOptionNode(shortCodes[i]);
    }
  };
  
  /**
   * initDisplay()
   * - initialize the picker display
   */
  var initDisplay = function() {
    // Start with dropdown closed or open depending on initial value
    if (isDropDownOpen) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize starting short code 
    if (shortCodes.length !== 0) {
      selectOptionByIndex(0);
    }
  };

  /**
   * selectOptionByIndex()
   * - select the specified short-code option
   * @param uint option_index: index of the option that is selected
   */
  var selectOptionByIndex = function(option_index) {
    console.assert(option_index < shortCodes.length);

    // Bind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.setAttribute(OPTION_SELECTED_ATTR, '');
    
    inputFieldWrapperNode.node.setAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR, option.code);

    // Update main display
    inputFieldLabelNode.node.innerHTML = option.alias; 

    selectedOptionIndex = option_index;
  };

  /**
   * unselectOptionByIndex()
   * - unselect the specified short-code option
   * @param uint option_index: index of the option that is to be unselected
   */
  var unselectOptionByIndex = function(option_index) {
    console.assert(selectedOptionIndex != null);
    console.assert(option_index < shortCodes.length);

    // Unbind attributes
    var option = shortCodes[option_index];

    var option_dom_node_list = dropDownNode.node.getElementsByClassName(SHORT_CODE_PICKER_OPTION_CLASS);
    console.assert(option_dom_node_list.length == shortCodes.length);

    var option_node = option_dom_node_list[option_index];
    option_node.removeAttribute(OPTION_SELECTED_ATTR);

    inputFieldWrapperNode.node.removeAttribute(INPUT_FIELD_WRAPPER_TOOLTIP_ATTR);

    // Update main display
    inputFieldLabelNode.node.innerHTML = '';

    selectedOptionIndex = null;
  };

  function setInitialStateInternal() {
    // Update ui with new short-codes
    initDisplay();
  };

  // Privileged functions
  /**
   * setShortCodes()
   * - set list of selectable short-codes
   * @param: array<ShortCode> short_codes: {id, code, alias}
   */
  this.setShortCodes = function(short_codes) {
    shortCodes = short_codes; 

    initOptionNodes();
    setInitialStateInternal();
  };

  /**
   * init()
   * - initialize short-code picker
   */
  this.init = function() {
    // We only init once!
    console.assert(rootNode.node == null);

    // Bind root node
    rootNode.node = document.getElementById(rootNode.nodeId);

    // Synthesize the template and copy into the root node
    synthesizeShortCodePickerTemplate();

    // Initialize nodes: dom elements and event listeners
    initMainNodes();

    // Initialize ui state
    initOptionNodes();
    setInitialStateInternal();
  };

  this.getSelectedShortCode = function() {
    console.assert(selectedOptionIndex !== null);
    console.assert(selectedOptionIndex < shortCodes.length);
    return shortCodes[selectedOptionIndex];
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };
};

function TimePicker(
  template_store,
  id,
  start_time, // {minute, hour}
  end_time,   // {minute, hour}
  time_interval // min
) {
  /**
   * Html dom attributes
   */
  var HIDDEN_ATTR = 'hidden-dropdown';
  var SHADOW_BORDER_ATTR = 'shadow-border';
  var TIME_ATTR = 'time';

  /**
   * Html class names
   */
  var TIME_LABEL_CLASS = 'time-label';
  var TIME_PICKER_OPTION_CLASS = 'time-picker-option';

  /**
   * Html template id name
   */
  var MAIN_TEMPLATE_ID = '#time-picker-template';
  var OPTION_TEMPLATE_ID = '#time-picker-option-template';

  /**
   * Meridian designations 
   */
  var HOUR_MIN_SEPARATOR = ':';
  var AM_DESIGNATION = 'am';
  var PM_DESIGNATION = 'pm';

  /**
   * Initial state
   */
  var INITIAL_IS_DROP_DOWN_OPEN = false;

  // Private state
  var templateStore = template_store;
  var startTime = start_time;
  var endTime = end_time;
  var timeInterval = time_interval; 
  var isDropDownOpen = false;
  var currentTime = null; // hours * 60 + minutes

  // Dom Nodes
  var rootNode = {
    nodeId: id,
    node: null
  };
  
  /**
   * Internal dom nodes
   */
  var timePickerWrapperNode = {
    class: 'time-picker-wrapper',
    node: null
  };

  var inputFieldNode = {
    class: 'input-field',
    node: null
  };

  var inputFieldWrapperNode = {
    class: 'input-field-wrapper',
    node: null
  };

  var dropDownNode = {
    class: 'time-dropdown',
    node: null
  };

  // Private functions
  /**
   * synthesizeTimePickerTemplate()
   * - copy template and insert into root node
   * @pre-condition: root node is initialized 
   */
  var synthesizeTimePickerTemplate = function() {
    var time_picker_template = templateStore.import.querySelector(MAIN_TEMPLATE_ID);
    var time_picker_clone = document.importNode(time_picker_template.content, true);
    rootNode.node.appendChild(time_picker_clone);
  };

  var openDropDown = function() {
    isDropDownOpen = true;    
    timePickerWrapperNode.node.removeAttribute(HIDDEN_ATTR);
    inputFieldNode.node.setAttribute(SHADOW_BORDER_ATTR, '');
  };

  var closeDropDown = function() {
    isDropDownOpen = false;    
    timePickerWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
    inputFieldNode.node.removeAttribute(SHADOW_BORDER_ATTR);
  };

  /**
   * configureAvailableTimes()
   * - compute available times and initialize ui elements
   * @pre-condition: root initialized and dom synthesized
   */
  var configureAvailableTimes = function() {
    // Bind template node for time-picker-option
    var time_picker_option_template = templateStore.import.querySelector(OPTION_TEMPLATE_ID);

    var current_time = startTime.hours * 60 + startTime.minutes;
    var next_time = current_time + time_interval;
    var end_time = endTime.hours * 60 + endTime.minutes;

    while (next_time <= end_time) {
      // Create new time-picker-option html element
      var current_time_string = stringifyTime(current_time); 
      var time_picker_option_clone = document.importNode(time_picker_option_template.content, true);

      // Incorporate into time-option list
      dropDownNode.node.appendChild(time_picker_option_clone);

      var new_time_picker_option_list = document.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
      var new_time_picker_option = new_time_picker_option_list[new_time_picker_option_list.length - 1];
      new_time_picker_option.setAttribute(TIME_ATTR, current_time);
      var time_label = new_time_picker_option.querySelector('.' + TIME_LABEL_CLASS);
      time_label.innerHTML = current_time_string;

      current_time = next_time;
      next_time += time_interval;
    }
  };

  var applyDoubleDigitTimeFormat = function(numeric_time_element) {
    return (numeric_time_element < 10)
      ? '0' + numeric_time_element 
      : numeric_time_element;
  };

  var stringifyTimeForInputField = function(time) {
    var string_time = stringifyTime(time);
    return string_time.replace(/&nbsp/gi, '');
  };

  /**
   * stringifyTime()
   * - convert numeric time to string format 
   * @param: uint time: hours * 60 + minutes
   * @return 'hh:mm' 
   */
  var stringifyTime = function(time) {
    // Stringify minutes
    var minutes = time % 60;
    var minutes_string = applyDoubleDigitTimeFormat(minutes);

    // Stringify hours
    var hours = (time - minutes) / 60;

    var meridian_designation = AM_DESIGNATION;
    if (hours > 12) {
      meridian_designation = PM_DESIGNATION;   
      hours = hours % 12;
    } 

    var hours_string = (hours < 10)
      ? '&nbsp&nbsp' + hours
      : hours;

    return hours_string + HOUR_MIN_SEPARATOR + minutes_string + ' ' + meridian_designation;
  };

  /**
   * bindInternalNode()
   * - bind the specified dom node (must be internal to this time-picker)
   * @param: Obj internal_node: internal dom node (see 'inputFieldNode' for structure)
   * @pre-condition: root node bound 
   */
  var bindInternalNode = function(internal_node) {
    // We bind internal nodes once only!
    console.assert(internal_node.node == null); 

    // Fetch internal node by class
    var node_set = rootNode.node.getElementsByClassName(internal_node.class);

    // We should only find one *internal* node with this class
    console.assert(node_set.length == 1);

    internal_node.node = node_set[0];
  };

  /**
   * initNodes()
   * - bind all internal nodes and configure event listeners
   */
  var initNodes = function() {
    // Bind top-level node in time-picker template 
    bindInternalNode(timePickerWrapperNode);

    // Bind input field and configure event listener
    bindInternalNode(inputFieldNode);
    bindInternalNode(inputFieldWrapperNode);

    inputFieldWrapperNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown(); 
      } else {
        openDropDown();
      }
    };

    // Bind time dropdown field and configure event listener
    bindInternalNode(dropDownNode);

    dropDownNode.node.onclick = function(event) {
      if (isDropDownOpen) {
        closeDropDown();
      } 

      // Capture selected time
      for (var i in event.path) {
        var node = event.path[i];
        if (hasClass(TIME_PICKER_OPTION_CLASS, node)) {
          var numeric_time = node.getAttribute(TIME_ATTR); 
          inputFieldNode.node.innerHTML = stringifyTimeForInputField(numeric_time);
          currentTime = numeric_time;
          return;
        }
      }
    };

    // Hide time picker if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the time-picker, so don't hide it!
        if (node.id == rootNode.node.id) {
          return;
        }
      }    

      // User clicked off the time-picker, so hide it!
      closeDropDown();
    });
  };

  // Start with closed or open drop-down (as specified by default param)
  var initDisplay = function() {
    if (INITIAL_IS_DROP_DOWN_OPEN) {
      openDropDown();
    } else {
      closeDropDown();
    }

    // Initialize start time
    var time_picker_options = rootNode.node.getElementsByClassName(TIME_PICKER_OPTION_CLASS);
    var starting_time_option = time_picker_options[0].getAttribute(TIME_ATTR);
    inputFieldNode.node.innerHTML = stringifyTimeForInputField(starting_time_option);
    currentTime = starting_time_option;
  };

  function setInitialStateInternal() {
    // Initialize the ui
    initDisplay();
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // We only init once!
    console.assert(rootNode.node == null);

    // Bind root node
    rootNode.node = document.getElementById(rootNode.nodeId);
    
    // Synthesize the template and copy into root node
    synthesizeTimePickerTemplate();

    // Initialize nodes: dom elements and event listeners
    initNodes(); 
  
    // Compute available times and initialize ui state
    configureAvailableTimes();
    setInitialStateInternal();
  };

  this.getSelectedTime = function() {
    var num_minutes = currentTime % 60;
    var num_hours = (currentTime - num_minutes) / 60;
    return {
      hours: num_hours,
      minutes: num_minutes,
      seconds: 0
    };
  };

  this.setInitialState = function() {
    setInitialStateInternal();
  };
};
