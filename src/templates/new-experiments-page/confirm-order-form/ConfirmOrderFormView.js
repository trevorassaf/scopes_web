var ConfirmOrderFormView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'confirm-order-form-template';

  /**
   * Root wrapper class
   */
  var ROOT_CLASS = 'confirm-order-form-wrapper';

  /**
   * UI text
   */
  var HOUR_UNIT = {
    singular: 'hour',
    plural: 'hours'
  };

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  // Callbacks
  var cancelOrderCallbacks = [];
  var confirmOrderCallbacks = [];

  // Cached 'this' pointer
  var _this = this;

  /**
   * Dom nodes
   */
  var cancelPaymentButtonNode = {
    className: 'cancel-payment-button',
    node: null
  };

  var confirmPaymentButtonNode = {
    className: 'confirm-payment-button',
    node: null
  };

  var hoursValueNode = {
    className: 'hours-value-field-label',
    node: null
  };

  var hoursUnitNode = {
    className: 'hours-unit-field-label',
    node: null
  };

  var hourlyRateValueNode = {
    className: 'hourly-rate-field-label',
    node: null
  }; 

  var totalPriceValueNode = {
    className: 'total-price-field-label',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Bind nodes
    Utils.bindNodeInfo(rootNode, cancelPaymentButtonNode); 
    Utils.bindNodeInfo(rootNode, confirmPaymentButtonNode); 
    Utils.bindNodeInfo(rootNode, hoursValueNode); 
    Utils.bindNodeInfo(rootNode, hoursUnitNode); 
    Utils.bindNodeInfo(rootNode, hourlyRateValueNode); 
    Utils.bindNodeInfo(rootNode, totalPriceValueNode); 

    // Attach event listeners
    confirmPaymentButtonNode.node.onclick = function() {
      for (var i = 0; i < confirmOrderCallbacks.length; ++i) {
        var callback = confirmOrderCallbacks[i];
        callback(_this);
      } 
    };

    cancelPaymentButtonNode.node.onclick = function() {
      for (var i = 0; i < cancelOrderCallbacks.length; ++i) {
        var callback = cancelOrderCallbacks[i];
        callback(_this);
      } 
    };
  };

  /**
   * Privileged functions
   */
  this.init = function() {
    // Initialize new-experiment ui
    rootNode = Utils.synthesizeTemplateIntoList(
      templateStore,
      TEMPLATE_ID,
      parentNode,
      ROOT_CLASS 
    );

    // Bind all ui dom nodes
    bindNodes();
  };

  this.bindCancelOrder = function(callback) {
    cancelOrderCallbacks.push(callback);
    return this;
  };

  this.bindConfirmOrder = function(callback) {
    confirmOrderCallbacks.push(callback);
    return this;
  };

  this.setPricingInformation = function(
    hours_count,
    hourly_rate,
    total_price
  ) {
    hoursValueNode.node.innerHTML = hours_count;
    hoursUnitNode.node.innerHTML = (hours_count == 1)
      ? HOUR_UNIT.singular
      : HOUR_UNIT.plural;
    hourlyRateValueNode.node.innerHTML = hourly_rate;
    totalPriceValueNode.node.innerHTML = total_price;
  };
};
