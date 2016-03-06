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
    registerCancelOrderOnClickListener: registerCancelOrderOnClickListener
  };
})();
