window.onload = function() {

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Configure UI elements
   */
  SidePanelUiController.init(template_store);

  /**
   * Fetch startup data and route to proper views 
   */
  GetStartupDataApiController.fetch();

  var my_experiments_view = SidePanelUiController.getMyExperimentsView();
  MyExperimentsLogicController.init(my_experiments_view);

};

function ConfirmedOrder(
  id,
  num_scopes,
  start_timestamp,
  end_timestamp,
  title,
  description,
  time_ordered,
  price,
  short_code
) {
  this.id = id;
  this.scopesCount = num_scopes;
  this.startTimestamp = start_timestamp;
  this.endTimestamp = end_timestamp;
  this.title = title;
  this.description = description;
  this.timeOrdered = time_ordered;
  this.price = price;
  this.shortCode = short_code;
};

ConfirmedOrder.prototype.getId = function() {
  return this.id;
};

ConfirmedOrder.prototype.getScopesCount = function() {
  return this.scopesCount;
};

ConfirmedOrder.prototype.getStartTimestamp = function() {
  return this.startTimestamp;
};

ConfirmedOrder.prototype.getEndTimestamp = function() {
  return this.endTimestamp;
};

ConfirmedOrder.prototype.getTitle = function() {
  return this.title;
};

ConfirmedOrder.prototype.getDescription = function() {
  return this.description;
};

ConfirmedOrder.prototype.getTimeOrdered = function() {
  return this.timeOrdered;
};

ConfirmedOrder.prototype.getPrice = function() {
  return this.price;
};

ConfirmedOrder.prototype.getShortCode = function() {
  return this.shortCode;
};

var DateOperator = (function() {

  // Date constants
  var HOURS_IN_MICROSECONDS = 3.6e6;

  /**
   * Privileged methods
   */

  this.getDifferenceInHours = function(
    date_a,
    date_b
  ) {
    return Math.abs(date_a - date_b) / HOURS_IN_MICROSECONDS; 
  };

  return {
    getDifferenceInHours: getDifferenceInHours
  };

})();

function SerializeableDate(
  year,
  month,
  date
) {

  // Ui constants
  this.DATE_DELIMITER = ',';

  this.SHORT_MONTH_NAMES = [
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

  /**
   * getShortMonthName()
   * @param uint month: 0 < month < 11
   */
  this.getShortMonthName = function(month) {
    return this.SHORT_MONTH_NAMES[month];
  };

  // Private state
  this.year = year;

  console.assert(month >= 0 && month < 12);
  this.month = month;

  console.assert(date >= 0 && date < 31);
  this.date = date;
};

SerializeableDate.prototype.serialize = function() {
  return this.getShortMonthName(this.month) + ' ' + this.date
    + this.DATE_DELIMITER + ' ' + this.year;
};

function SerializeableTime(
  hours,    // military time
  minutes,
  seconds
) {

  this.TIME_DELIMITER = ':';
  this.AM_TOKEN = 'am';
  this.PM_TOKEN = 'pm';

  this.convertHourToNonMilitaryTime = function(military_hours) {
    return (military_hours > 12)
      ? military_hours - 12
      : military_hours;
  };

  this.getMeridianToken = function(military_hours) {
    return (military_hours >= 12 && military_hours !== 24)
      ? this.PM_TOKEN
      : this.AM_TOKEN;
  };

  this.hours = hours;
  this.minutes = minutes;
  this.seconds = seconds;
};

SerializeableTime.prototype.serialize = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.seconds, 2) + " " + meridian_token;
};

SerializeableTime.prototype.serializeWithoutSeconds = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) +
    " " + meridian_token;
};

function ShortCode(
  id,
  code,
  alias
) {
  this.id = id;
  this.code = code;
  this.alias = alias;
};

ShortCode.prototype.getId = function() {
  return this.id;
};

ShortCode.prototype.getCode = function() {
  return this.code;
};

ShortCode.prototype.getAlias = function() {
  return this.alias;
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

  this.makeTimestampIntervalString = function(starting_timestamp, ending_timestamp) {
    // Convert to native js date objects
    var starting_js_date = new Date(starting_timestamp);
    var ending_js_date = new Date(ending_timestamp);

    var serializeable_starting_date = new SerializeableDate(
      starting_js_date.getUTCFullYear(),
      starting_js_date.getUTCMonth(),
      starting_js_date.getUTCDate()
    );

    var serializeable_starting_time = new SerializeableTime(
      starting_js_date.getHours(),
      starting_js_date.getMinutes(),
      starting_js_date.getSeconds()
    );

    var interval_string = serializeable_starting_date.serialize() + ' ' +
        serializeable_starting_time.serializeWithoutSeconds() + ' - ';

    var serializeable_ending_time = new SerializeableTime(
      ending_js_date.getHours(),
      ending_js_date.getMinutes(),
      ending_js_date.getSeconds()
    );

    if (starting_js_date.getUTCFullYear() == ending_js_date.getUTCFullYear() &&
        starting_js_date.getUTCMonth() == ending_js_date.getUTCMonth() &&
        starting_js_date.getUTCDate() == ending_js_date.getUTCDate()
    ) {
      return interval_string + serializeable_ending_time.serializeWithoutSeconds(); 
    }
    
    var serializeable_ending_date = new SerializeableDate(
      ending_js_date.getUTCFullYear(),
      ending_js_date.getUTCMonth(),
      ending_js_date.getUTCDate()
    );

    return interval_string + serializeable_ending_date.serialize() + ' ' + 
        serializeable_ending_time.serializeWithoutSeconds();
  };

  return {
    hasClass: hasClass,
    makePriceString: makePriceString,
    makeTimestampString: makeTimestampString,
    removeDomChildren: removeDomChildren,
    stringifyNumberWithEnforcedDigitCount: stringifyNumberWithEnforcedDigitCount,
    makeTimestampIntervalString: makeTimestampIntervalString
  };

})();

function ApiControllerWrapper(api_object) {

  /**
   * Private state
   */
  var apiObject = api_object;
  var successfulApiCallbackListeners = [];
  var failedLogicalApiCallbackListeners = [];
  var failedNonLogicalApiCallbackListeners = [];

  var successfulApiCallback = function(api_response) {
    for (var i = 0; i < successfulApiCallbackListeners.length; ++i) {
      successfulApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };

  var logicallyFailedApiCallback = function(api_response) {
    for (var i = 0; i < failedLogicalApiCallbackListeners.length; ++i) {
      failedLogicalApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    for (var i = 0; i < failedNonLogicalApiCallbackListeners.length; ++i) {
      failedNonLogicalApiCallbackListeners[i](api_response, apiObject.getApiKeys());
    }
  };
  
  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.registerSuccessfulApiCallback = function(callback) {
    successfulApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.registerLogicalFailedApiCallback = function(callback) {
    failedLogicalApiCallbackListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  this.registerNonLogicalFailedApiCallback = function(callback) {
    failedNonLogicalApiCallbackListeners.push(callback);
    return this;
  };
  
  /**
   * fetch()
   * - fetches startup data
   */
  this.fetch = function() {
    // Bind event listeners
    apiObject.setSuccessfulApiCallback(successfulApiCallback);
    apiObject.setLogicalApiFailureCallback(logicallyFailedApiCallback);
    apiObject.setNonLogicalApiFailureCallback(nonLogicallyFailedApiCallback);

    // Fire api request
    apiObject.send();
  };
};

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

var MyExperimentsLogicController = (function() {

  /**
   * Private state
   */
  var myExperiments = [];
  var getConfirmedOrdersApiWrapper = null;
  var myExperimentsView = null;

  /**
   * Private functions
   */
  var initApi = function() {
    console.assert(getConfirmedOrdersApiWrapper === null); 

    // Initialize get-confirmed-order api
    var get_confirmed_order_api = new GetConfirmedOrdersApi(ScopesNetwork);
    getConfirmedOrdersApiWrapper = new ApiControllerWrapper(get_confirmed_order_api);

    // Bind event listeners to get-confirmed-orders api
    getConfirmedOrdersApiWrapper.registerSuccessfulApiCallback(function(json_response, response_keys) {
      clearConfirmedOrders();
      var orders = json_response[response_keys.orders];
      var order_response_keys = response_keys.confirmed_order;
      var short_code_response_keys = response_keys.short_code;
      
      for (var i = 0; i < orders.length; ++i) {
        var order = orders[i];
        var short_code = order[order_response_keys.short_code];

        var short_code = new ShortCode(
          short_code[short_code_response_keys.id],
          short_code[short_code_response_keys.code],
          short_code[short_code_response_keys.alias]
        );

        var confirmed_order = new ConfirmedOrder(
          order[order_response_keys.id],
          order[order_response_keys.scopes_count],
          order[order_response_keys.start_time],
          order[order_response_keys.end_time],
          order[order_response_keys.title],
          order[order_response_keys.description],
          order[order_response_keys.time_ordered],
          order[order_response_keys.price],
          short_code
        );

        addConfirmedOrder(confirmed_order); 
      }
    });

    getConfirmedOrdersApiWrapper.registerLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders'); 
    });

    getConfirmedOrdersApiWrapper.registerNonLogicalFailedApiCallback(function(response) {
      console.log(response);
      console.log('ERROR: failed to get confirmed orders due to network error'); 
    });
  };

  var addConfirmedOrder = function(confirm_order) {
    // Store in local cache
    myExperiments.push(confirm_order);  

    // Update MyExperiments view
    myExperimentsView.pushPendingOrder(confirm_order);
  };

  var clearConfirmedOrders = function() {
    // Clear local cache
    myExperiments = [];

    // Clear MyExperiments view
    // TODO...   
  };

  var init = function(my_experiments_view) {
    myExperimentsView = my_experiments_view;

    // Initialize api module
    initApi();

    refreshData(); 
  };

  var refreshData = function() {
    getConfirmedOrdersApiWrapper.fetch(); 
  };

  var getMyExperiments = function() {
    return myExperiments;
  };

  return {
    init: init,
    refreshData: refreshData,
    getMyExperiments: getMyExperiments
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
   * Ui attributes
   */
  var HIDDEN_PAGE_ATTR = 'hidden-new-experiment-page';

  /**
   * Dom info
   */
  var rootNode = {
    id: 'add-exp-center-page',
    node: null
  };

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
    // Bind root node
    rootNode.node = document.getElementById(rootNode.id);
    console.assert(rootNode.node !== null);

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
    
    // Initialize ui to 'show' state
    show();
  };

  var hide = function() {
    rootNode.node.setAttribute(HIDDEN_PAGE_ATTR, '');    
  };

  var show = function() {
    rootNode.node.removeAttribute(HIDDEN_PAGE_ATTR);
  };

  return {
    init: init,
    confirmOrder: confirmOrder,
    cancelOrder: cancelOrder,
    hide: hide,
    show: show
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
   * Ui attributes
   */
  var START_HIDDEN_ATTR = "start-hidden";
  
  /**
   * Ui node id's 
   */
  var CENTER_PAGE_TITLE_LABEL_ID = 'center-page-title-label';
  var NAVIGATION_BUTTON_CONTAINER_ID = 'nav-btns-container';
  var CENTER_PANEL_PAGE_CONTAINER = 'center-panel-page-container';

  /**
   * Private state
   */
  var currentlySelectedTabAndPageInfo = null;
  var centerPageTitleLabel = null;
  var centerPanelPageContainer = null;

  var newExperimentInfo = {
    tab_info: {
      button_title: 'Add Experiment',
      icon_type: 'add-circle-outline',
      tab: null
    },
    page_info: {
      page: null
    }
  };

  var myExperimentsInfo = {
    tab_info: {
      button_title: 'My Experiments',
      icon_type: 'group-work',
      tab: null
    },
    page_info: {
      id: 'my-exp-center-page',
      page: null
    }
  };

  var monitorExperimentInfo = {
    tab_info: {
      button_title: 'Monitor Experiment',
      icon_type: 'settings-input-svideo',
      tab: null
    },
    page_info: {
      id: 'monitor-exp-center-page',
      page: null
    }
  };

  var technicianInfo = {
    tab_info: {
      button_title: 'Technician',
      icon_type: 'build',
      tab: null
    },
    page_info: {
      id: 'technician-center-page',
      page: null
    }
  };

  var initTabInfo = function(
    template_store,
    tab_parent_node,
   tab_and_page_info 
  ) {
    var tab_info = tab_and_page_info.tab_info;

    // Initialize tab info
    tab_info.tab = new SidePanelTab(
      template_store,
      tab_parent_node,
      tab_info.button_title,
      tab_info.icon_type
    );

    tab_info.tab.registerOnClickListener(function() {
      selectNewTabAndShowNewPage(tab_and_page_info);
    });

    tab_info.tab.init();
  };

  var deselectCurrentTabAndHideCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.deselect();
    currentlySelectedTabAndPageInfo.page_info.page.hide();
  };

  var selectCurrentTabAndShowCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.select();
    currentlySelectedTabAndPageInfo.page_info.page.show();
    centerPageTitleLabel.innerHTML = currentlySelectedTabAndPageInfo.tab_info.button_title;
  };

  var selectNewTabAndShowNewPage = function(tab_and_page_info) {
    deselectCurrentTabAndHideCurrentPage();
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  var initTabAndPageInfos = function(template_store) {
    // Init side-panel-container node
    var tab_parent_node = document.getElementById(NAVIGATION_BUTTON_CONTAINER_ID);

    // Init new experiment page/tab info
    newExperimentInfo.page_info.page = NewExperimentUiController;
    newExperimentInfo.page_info.page.init(template_store);
   
    // Init my experiments page
    myExperimentsInfo.page_info.page = new MyExperimentsPage(
      template_store,
      myExperimentsInfo.page_info.id,
      false
    );
    myExperimentsInfo.page_info.page.init();

    // Init monitor experiment page
    monitorExperimentInfo.page_info.page = new MonitorExperimentsPage(
      template_store,
      monitorExperimentInfo.page_info.id,
      false
    );
    monitorExperimentInfo.page_info.page.init();

    // Init technician page
    technicianInfo.page_info.page = new TechnicianPage(
      template_store,
      technicianInfo.page_info.id,
      false
    );
    technicianInfo.page_info.page.init();

    // Configure tabs
    initTabInfo(template_store, tab_parent_node, newExperimentInfo); 
    initTabInfo(template_store, tab_parent_node, myExperimentsInfo); 
    initTabInfo(template_store, tab_parent_node, monitorExperimentInfo); 
    initTabInfo(template_store, tab_parent_node, technicianInfo); 
  };

  function initSelectedTabAndPage(tab_and_page_info) {
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  /**
   * init()
   * - initialize ui node bindings, event listeners, and starting
   *   ui state
   */
  var init = function(template_store) {
    // Init center-page title node
    centerPageTitleLabel = document.getElementById(CENTER_PAGE_TITLE_LABEL_ID);
    centerPanelPageContainer = document.getElementById(CENTER_PANEL_PAGE_CONTAINER);

    // Initialize tab and center page controllers and ui elements
    initTabAndPageInfos(template_store);

    initSelectedTabAndPage(newExperimentInfo);

    centerPanelPageContainer.removeAttribute(START_HIDDEN_ATTR);
  };

  var getMyExperimentsView = function() {
    console.assert(myExperimentsInfo.page_info.page !== null);
    return myExperimentsInfo.page_info.page;
  };

  return {
    init: init,
    getMyExperimentsView: getMyExperimentsView
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

GetConfirmedOrdersApi.prototype = new ScopesApi();
GetConfirmedOrdersApi.prototype.constructor = GetConfirmedOrdersApi;

function GetConfirmedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x9;
};

GetConfirmedOrdersApi.prototype.getApiKeys = function() {
  return {
    orders: 'orders',
    confirmed_order: {
      id: 'id',
      scopes_count: 'scopes-count',
      start_time: 'start',
      end_time: 'end',
      title: 'title',
      description: 'description',
      time_ordered: 'time-ordered',
      price: 'price',
      short_code: 'short-code'
    },
    short_code: {
      id: 'id',
      code: 'code',
      alias: 'alias'
    }
  };
};

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
   * handleMalformedApiResponseWrapper()
   * - callback for malformed api response
   */
  this.handleMalformedApiResponseWrapper = function(xhttp_response) {
    console.log("API ERROR: Malformed api response", xhttp_response);
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * handleJsonParseError()
   * - callback for json parse error in api call 
   */
  this.handleJsonParseError = function(xhttp_response) {
    console.log("API ERROR: Json parse error");
    this.nonLogicalApiFailureCallback(xhttp_response);
  };

  /**
   * networkSuccessCallbackWrapper()
   * - callback for ScopesNetwork when network call succeeds
   */
  this.networkSuccessCallbackWrapper = function(xhttp_response) {
    var json_response = null

    try {
      // Deserialize json payload
      json_response = JSON.parse(xhttp_response.responseText);

    } catch (parse_exception) {
      // Failed to parse json api response
      this.handleJsonParseError(xhttp_response);
    }

    console.assert(json_response !== null);
     
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

function MonitorExperimentsPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#monitor-experiments-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-monitor-experiments-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Root node
  var monitorExperimentsPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'monitor-experiments-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = monitorExperimentsPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeMonitorExperimentsPageTemplate()
   * - copy monitor-experiments-page template and insert into main dom tree
   * @pre-condition: 'monitorExperimentsPageRootNode' must be initialized
   */
  function synthesizeMonitorExperimentsPageTemplate() {
    // Bind monitor-experiments-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    monitorExperimentsPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = monitorExperimentsPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize monitor experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level monitor-experiments-page node (we're going to copy the template into this!)
    monitorExperimentsPageRootNode.node = document.getElementById(monitorExperimentsPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeMonitorExperimentsPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the monitor-experiments-page
   */
  this.hide = function() {
    monitorExperimentsPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the monitor-experiments-page
   */
  this.show = function() {
    monitorExperimentsPageRootNode.node.removeAttribute(HIDDEN_ATTR);
  };

};

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
    console.assert(elements.length === 1);
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

function MyExperimentsPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var WRAPPER_TEMPLATE_ID_SELECTOR = '#my-experiments-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-my-experiments-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Pending experiment views
  var pendingExperimentViews = [];

  // Root node
  var myExperimentsPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'my-experiments-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeMyExperimentsPageTemplate()
   * - copy my-experiments-page template and insert into main dom tree
   * @pre-condition: 'myExperimentsPageRootNode' must be initialized
   */
  function synthesizeMyExperimentsPageTemplate() {
    // Bind my-experiments-page dom template
    var page_template = templateStore.import.querySelector(WRAPPER_TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    myExperimentsPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = myExperimentsPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    // Bind internal nodes
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize my experiments page and put it in starting state
   */
  this.init = function() {
    // Bind top-level my-experiments-page node (we're going to copy the template into this!)
    myExperimentsPageRootNode.node = document.getElementById(myExperimentsPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeMyExperimentsPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the my-experiments-page
   */
  this.hide = function() {
    pageWrapperNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the my-experiments-page
   */
  this.show = function() {
    pageWrapperNode.node.removeAttribute(HIDDEN_ATTR);
  };

  this.pushPendingOrder = function(confirmed_order) {
    var pending_experiment_view = new PendingExperimentView(
      templateStore,
      pageWrapperNode.node
    );     

    pendingExperimentViews.push(pending_experiment_view);

    pending_experiment_view.init(confirmed_order);
  };

  this.clearPendingOrders = function() {
    // TODO...
  };
};

function PendingExperimentView(
  template_store,
  parent_node
) {

  /**
   * Key code values
   */
  var ENTER_KEY_CODE = 13;

  /**
   * Default values 
   */
  var DEFAULT_TITLE = 'Add title...';
  var DEFAULT_DESCRIPTION = 'Add description...';

  /**
   * Ui attributes
   */
  var SELECTED_BUTTON_ATTR = "selected-btn";
  var SELECTED_PAGE_ATTR = 'selected-page';
  var EDITING_TITLE_ATTR = 'editing-title';

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#pending-experiment-template';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;
  var selectedButton = null;
  var selectedPageWrapper = null;
  var isEditingTitle = false;
  var cachedTitle = null;
  var changedTitleListeners = [];

  /**
   * Dom nodes
   */
  var rootNode = {
    className: 'pending-experiment-wrapper',
    node: null
  };

  /**
   * Header nodes
   */
  var headerNode = {
    className: 'header-wrapper',
    node: null
  };

  var titleNode = {
    className: 'title-label',
    node: null
  };

  /**
   * Page nodes 
   */
  var descriptionPageNode = {
    className: 'description-page',
    node: null
  };
  
  var hardwarePageNode = {
    className: 'hardware-page',
    node: null
  };
  
  var timePageNode = {
    className: 'time-page',
    node: null
  };
  
  var paymentPageNode = {
    className: 'payment-page',
    node: null
  };
  
  /**
   * Footer button nodes
   */
  var descriptionButtonNode = {
    className: 'description-nav-wrapper',
    node: null
  };

  var hardwareButtonNode = {
    className: 'hardware-nav-wrapper',
    node: null
  };

  var timeButtonNode = {
    className: 'time-nav-wrapper',
    node: null
  };

  var paymentButtonNode = {
    className: 'payment-nav-wrapper',
    node: null
  };

  /**
   * Main stage wrappers
   */

  var scopesCountNode = {
    value: {
      className: 'scopes-count-label',
      node: null
    },
    unit: {
      className: 'scopes-count-unit-label',
      node: null,
      singular: 'scope',
      plural: 'scopes'
    }
  };

  var startDateNode = {
    className: 'start-date-label',
    node: null
  };

  var experimentTimestampIntervalNode = {
    className: 'experiment-timestamp-interval-label',
    node: null
  };

  var startTimeNode = {
    className: 'start-time-label',
    node: null
  };

  var durationNode = {
    value: {
      className: 'duration-label',
      node: null
    },
    unit: {
      className: 'duration-unit-label',
      node: null,
      singular: 'hour',
      plural: 'hours'
    }
  };

  var descriptionNode = {
    className: 'description-label',
    node: null
  };

  var orderedDateNode = {
    className: 'ordered-date-label',
    node: null
  };

  var priceNode = {
    value: { 
      className: 'price-label',
      node: null
    },
    unit: {
      className: 'price-unit-label',
      node: null,
      singular: '$',
      plural: '$'
    }
  };

  var shortCodeNode = {
    className: 'short-code-label',
    node: null
  };

  /**
   * Private functions
   */
  function synthesizeTemplate() {
    // Clone pending-order template
    var pending_order_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var pending_order_clone = document.importNode(pending_order_template.content, true);

    // Activate by inserting into parent 
    parentNode.appendChild(pending_order_clone); 
    var pending_order_list = parentNode.getElementsByClassName(rootNode.className);
    rootNode.node = pending_order_list[pending_order_list.length - 1];
  };

  /**
   * setTitle()
   * @param string title: title string
   */
  function setTitle(title) {
    if (title == null || title == '') {
      titleNode.node.innerHTML = DEFAULT_TITLE; 
    } else {
      titleNode.node.innerHTML = title; 
    }
  };

  /**
   * setDescription()
   * @param string description
   */
  function setDescription(description) {
    if (description == null || description == '') {
      descriptionNode.node.innerHTML = DEFAULT_DESCRIPTION; 
    } else {
      descriptionNode.node.innerHTML = description; 
    }
  };

  function setShortCode(short_code) {
    shortCodeNode.node.innerHTML = short_code.getAlias(); 
  };

  function setScopesCount(scopes_count) {
    updateNodeWithUnit(scopes_count, scopesCountNode);
  };

  function setPrice(price) {
    updateNodeWithUnit(price, priceNode);  
  };

  function setOrderedDate(ordered_date) {
    orderedDateNode.node.innerHTML = ordered_date.serialize();
  };

  function setExperimentTimestampInterval(experiment_timestamp_interval) {
    experimentTimestampIntervalNode.node.innerHTML = experiment_timestamp_interval;
  }

  function updateNodeWithUnit(value, node) {
    // Place value in ui node
    node.value.node.innerHTML = value;
    
    // Adjust unit
    node.unit.node.innerHTML = (value === 1)
      ? node.unit.singular
      : node.unit.plural;
  };

  var bindClassBoundNode = function(node_info) {
    var elements = rootNode.node.getElementsByClassName(node_info.className); 
    console.assert(elements.length === 1);
    node_info.node = elements[0];
  };

  var bindClassBoundNodeWithUnit = function(node_info) {
    bindClassBoundNode(node_info.value);
    bindClassBoundNode(node_info.unit);
  };

  var unselectButton = function() {
    console.assert(selectedButton !== null); 
    selectedButton.node.removeAttribute(SELECTED_BUTTON_ATTR);
    selectedButton = null;
  };

  var selectButton = function(selected_button) {
    console.assert(selectedButton === null);
    selectedButton = selected_button;
    selectedButton.node.setAttribute(SELECTED_BUTTON_ATTR, '');
  };

  var hideSelectedPage = function() {
    console.assert(selectedPageWrapper !== null);
    selectedPageWrapper.node.removeAttribute(SELECTED_PAGE_ATTR);
    selectedPageWrapper = null;
  };

  var selectPage = function(page) {
    console.assert(selectedPageWrapper === null);
    selectedPageWrapper = page;
    selectedPageWrapper.node.setAttribute(SELECTED_PAGE_ATTR, '');
  };

  var changePage = function(button, page) {
    // Deselect currently selected button/page
    unselectButton();
    hideSelectedPage();

    // Select new button/page
    selectButton(button);
    selectPage(page);
  };

  var bindPageNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionPageNode);
    bindClassBoundNode(hardwarePageNode);
    bindClassBoundNode(timePageNode);
    bindClassBoundNode(paymentPageNode);
  };

  var bindFooterNodes = function() {
    // Bind nodes
    bindClassBoundNode(descriptionButtonNode);
    bindClassBoundNode(hardwareButtonNode);
    bindClassBoundNode(timeButtonNode);
    bindClassBoundNode(paymentButtonNode);

    // Configure event listeners
    descriptionButtonNode.node.onclick = function() {
      changePage(descriptionButtonNode, descriptionPageNode); 
    }; 
    hardwareButtonNode.node.onclick = function() {
      changePage(hardwareButtonNode, hardwarePageNode); 
    }; 
    timeButtonNode.node.onclick = function() {
      changePage(timeButtonNode, timePageNode); 
    }; 
    paymentButtonNode.node.onclick = function() {
      changePage(paymentButtonNode, paymentPageNode); 
    }; 
  };

  var setEditingTitle = function() {
    console.assert(!isEditingTitle);
    headerNode.node.setAttribute(EDITING_TITLE_ATTR, '');  
    
    // Select text in title field
    var range = document.createRange();
    range.selectNodeContents(titleNode.node);
    var sel = window.getSelection();
    sel.removeAllRanges();
    sel.addRange(range);

    isEditingTitle = true;
  };

  var setNotEditingTitle = function() {
    console.assert(isEditingTitle);
    headerNode.node.removeAttribute(EDITING_TITLE_ATTR);
    titleNode.node.blur();
    window.getSelection().removeAllRanges();
    isEditingTitle = false;
  };

  var finishedEditingTitle = function() {
    // Notify listeners that the title has changed!
    if (cachedTitle != titleNode.node.innerHTML) {
      // Update cached title value
      cachedTitle = titleNode.node.innerHTML;

      console.log(cachedTitle);

      for (var i = 0; i < changedTitleListeners.length; ++i) {
        changedTitleListeners[i](cachedTitle);
      }
    }
    
    // Return title to unselected state
    setNotEditingTitle();
  };

  var bindHeaderNodes = function() {
    // Bind header nodes
    bindClassBoundNode(headerNode);
    bindClassBoundNode(titleNode); 

    // Bind header event listeners
    headerNode.node.onclick = function() {
      // Short circuit b/c we're already editing the title...
      if (isEditingTitle) {
        return;
      }

      setEditingTitle();
    };

    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      // Short circuit b/c title isn't being edited currently anyway
      if (!isEditingTitle) {
        return;
      }

      for (var node_idx in event.path) {
        var node = event.path[node_idx];
        if (Utils.hasClass(headerNode.className, node)) {
          return;
        }
      }   

      // Signal that we've finished editing the title
      finishedEditingTitle();
    });

    titleNode.node.onkeypress = function(event) {
      // If 'return' pressed, then direct focus away from 'titleNode'
      if (event.charCode == ENTER_KEY_CODE) {
        finishedEditingTitle();
        return false;
      }
    };
  };

  var bindInternalNodes = function() {
    bindHeaderNodes();
    bindPageNodes();
    bindFooterNodes();

    // Bind unitless nodes
    bindClassBoundNode(experimentTimestampIntervalNode);
    bindClassBoundNode(descriptionNode); 
    bindClassBoundNode(orderedDateNode); 
    bindClassBoundNode(shortCodeNode); 
  
    // Bind nodes with unit
    bindClassBoundNodeWithUnit(scopesCountNode); 
    bindClassBoundNodeWithUnit(priceNode); 
  };

  var initUiData = function(confirmed_order) {
    setTitle(confirmed_order.getTitle());
    setDescription(confirmed_order.getDescription());
    setScopesCount(confirmed_order.getScopesCount());
    setPrice(confirmed_order.getPrice());
    setShortCode(confirmed_order.getShortCode());

    // Set date ordered
    var ordered_date = new Date(confirmed_order.getTimeOrdered());
    var serializeable_ordered_date = new SerializeableDate(
      ordered_date.getUTCFullYear(),
      ordered_date.getUTCMonth(),
      ordered_date.getUTCDate()
    );
    setOrderedDate(serializeable_ordered_date);

    var experiment_timestamp_interval = Utils.makeTimestampIntervalString(
      confirmed_order.getStartTimestamp(),
      confirmed_order.getEndTimestamp()
    );

    console.log(experiment_timestamp_interval);

    setExperimentTimestampInterval(experiment_timestamp_interval);
  };

  /**
   * Privileged functions
   */
  this.init = function(confirmed_order) {
    // Clone template and copy into pending-experiments list
    synthesizeTemplate();

    // Init dom pointers to internal nodes
    bindInternalNodes();

    // Place data in proper ui elements
    initUiData(confirmed_order);

    selectButton(descriptionButtonNode);
    selectPage(descriptionPageNode);
  };

  /**
   * registerChangedTitleListener()
   * @param FuncPtr callback: function(title) {...}
   */
  this.registerChangedTitleListener = function(callback) {
    changedTitleListeners.push(callback);
  }
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

function SidePanelTab(
  template_store,
  parent_node,
  button_title,
  iron_icon_type
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = "#side-panel-tab-template";

  /**
   * Ui attributes
   */
  var SELECTED_ATTR = "selected-side-panel-tab";
  var IRON_ICON_TYPE_ATTR = "icon";

  /**
   * Private state
   */
  var _this = this;
  var templateStore = template_store;
  var buttonTitle = button_title;
  var ironIconType = iron_icon_type;
  var onClickListeners = [];

  // Root dom node
  var rootNode = {
    className: 'dash-nav-panel-btn',
    node: null
  };

  var ironIconNode = {
    className: 'nav-btn-icon',
    node: null
  };

  var buttonTitleNode = {
    className: 'nav-btn-label',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = rootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  function synthesizeSidePanelTemplate() {
    var tab_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR); 
    var tab_clone = document.importNode(tab_template.content, true);
    parent_node.appendChild(tab_clone);

    // Initialize root node and configure event listener
    var tabs = parent_node.getElementsByClassName(rootNode.className);
    rootNode.node = tabs[tabs.length - 1];

    rootNode.node.onclick = function() {
      for (var i = 0; i < onClickListeners.length; ++i) {
        onClickListeners[i]();
      }
    };
  };

  /**
   * bindInternalNodes()
   * @pre-condition: 'rootNode' must already be bound
   */
  function bindInternalNodes() {
    bindClassBoundNode(ironIconNode); 
    bindClassBoundNode(buttonTitleNode);
  };

  /**
   * initDisplay()
   * - initializes text/graphics for this tab
   * @pre-condition: all internal nodes bound
   */
  function initDisplay() {
    ironIconNode.node.setAttribute(IRON_ICON_TYPE_ATTR, ironIconType);
    buttonTitleNode.node.innerHTML = buttonTitle; 
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize template and append to parent dom node
    synthesizeSidePanelTemplate();

    // Initialize pointers to internal nodes
    bindInternalNodes();

    // Initialize the ui
    initDisplay();
  }; 

  this.select = function() {
    rootNode.node.setAttribute(SELECTED_ATTR, ''); 
  };

  this.deselect = function() {
    rootNode.node.removeAttribute(SELECTED_ATTR);
  };

  /**
   * registerOnClickListener()
   * @param FuncPtr callback: function(_this) {...}
   */
  this.registerOnClickListener = function(callback) {
    onClickListeners.push(callback); 
  };
};

function TechnicianPage(
  template_store,
  root_id,
  is_displayed_initially
) {

  /**
   * Template id
   */
  var TEMPLATE_ID_SELECTOR = '#technician-page-template';

  /**
   * Ui attributes
   */
  var HIDDEN_ATTR = "hidden-technician-page";

  /**
   * Private state
   */
  // Dom nodes
  var templateStore = template_store;
  var isDisplayedInitially = is_displayed_initially;
  var _this = this;

  // Root node
  var TechnicianPageRootNode = {
    id: root_id,
    node: null
  };

  // Class-bound nodes
  var pageWrapperNode = {
    className: 'technician-page-wrapper',
    node: null 
  };

  /**
   * Private functions
   */
  function fetchClassBoundDomNode(node_info) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * synthesizeTechnicianPageTemplate()
   * - copy technician-page template and insert into main dom tree
   * @pre-condition: 'TechnicianPageRootNode' must be initialized
   */
  function synthesizeTechnicianPageTemplate() {
    // Bind technician-page dom template
    var page_template = templateStore.import.querySelector(TEMPLATE_ID_SELECTOR);
    var page_clone = document.importNode(page_template.content, true);
    TechnicianPageRootNode.node.appendChild(page_clone);
  };

  /**
   * bindClassBoundNode()
   * - initialize pointer to specified dom node
   */
  function bindClassBoundNode(internal_node) {
    elements = TechnicianPageRootNode.node.getElementsByClassName(internal_node.className);
    console.assert(elements.length === 1);
    internal_node.node = elements[0];
  };

  /**
   * bindInternalNodes()
   * - bind class-bound nodes internal to this template
   */
  function bindInternalNodes() {
    bindClassBoundNode(pageWrapperNode);     
  };

  /**
   * initDisplay()
   * - render initially ui
   */
  function initDisplay() {
    if (isDisplayedInitially) {
      _this.show();
    } else {
      _this.hide(); 
    }
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - initialize technician page and put it in starting state
   */
  this.init = function() {
    // Bind top-level technician-page node (we're going to copy the template into this!)
    TechnicianPageRootNode.node = document.getElementById(TechnicianPageRootNode.id);

    // Clone template and copy into wrapper
    synthesizeTechnicianPageTemplate();

    // Bind nodes internal to this template
    bindInternalNodes();

    // Initialize ui
    initDisplay();
  };

  /**
   * hide()
   * - hide the technician-page
   */
  this.hide = function() {
    TechnicianPageRootNode.node.setAttribute(HIDDEN_ATTR, '');
  };

  /**
   * show()
   * - show the technician-page
   */
  this.show = function() {
    TechnicianPageRootNode.node.removeAttribute(HIDDEN_ATTR);
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
