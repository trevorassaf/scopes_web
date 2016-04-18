var MyExperimentFrontPageView = function(
  template_store,
  parent_node
) {

  /**
   * Template id
   */
  var TEMPLATE_ID = 'my-experiment-front-page-template';

  /**
   * Root class
   */
  var ROOT_CLASS = 'my-experiment-front-page-wrapper';

  /**
   * Private state
   */
  var templateStore = template_store;
  var parentNode = parent_node;

  /**
   * Dom node info
   */
  var experimentStatusValueNode = {
    className: 'experiment-status-value',
    node: null
  };

  var startTimeValueNode = {
    className: 'start-time-value',
    node: null
  };

  var experimentDurationValueNode = {
    className: 'experiment-duration-value',
    node: null
  };

  var scopesCountValueNode = {
    className: 'scopes-count-value',
    node: null
  };

  var paymentStatusValueNode = {
    className: 'payment-status-value',
    node: null
  };

  var experimentPriceValueNode = {
    className: 'experiment-price-value',
    node: null
  };

  var shortCodeValueNode = {
    className: 'short-code-value',
    node: null
  };

  /**
   * Private functions
   */
  var createExperimentStartTimeString = function(start_time) {
    var start_time_str = Utils.getShortMonthName(start_time.getMonth());
    start_time_str += " " + start_time.getDate();
    start_time_str += ", " + start_time.getFullYear();
    start_time_str += " @ " + Utils.toHoursAndMinutesString(start_time);
    return start_time_str;
  };

  var bindNodes = function() {
    // Bind dom node info    
    Utils.bindNodeInfo(rootNode, experimentStatusValueNode); 
    Utils.bindNodeInfo(rootNode, startTimeValueNode); 
    Utils.bindNodeInfo(rootNode, experimentDurationValueNode); 
    Utils.bindNodeInfo(rootNode, scopesCountValueNode); 
    Utils.bindNodeInfo(rootNode, paymentStatusValueNode); 
    Utils.bindNodeInfo(rootNode, experimentPriceValueNode); 
    Utils.bindNodeInfo(rootNode, shortCodeValueNode); 
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

    // Bind all ui nodes and attach event listeners
    bindNodes(); 
  };

  this.hide = function() {
    Utils.hideNode(parentNode);
  };

  this.show = function() {
    Utils.showNode(parentNode);
  };

  // Setters
  this.setExperimentStatus = function(experiment_status) {
    experimentStatusValueNode.node.innerHTML = experiment_status;
  };

  this.setStartTime = function(start_time) {
    startTimeValueNode.node.innerHTML = createExperimentStartTimeString(start_time);
  };

  this.setExperimentDuration = function(duration) {
    experimentDurationValueNode.node.innerHTML = duration.toString() + " hr";
  };

  this.setScopesCount = function(count) {
    scopesCountValueNode.node.innerHTML = count;
  };

  this.setPaymentStatus = function(payment_status) {
    paymentStatusValueNode.node.innerHTML = payment_status;
  };

  this.setExperimentPrice = function(price) {
    experimentPriceValueNode.node.innerHTML = price;
  };

  this.setShortCode = function(short_code) {
    shortCodeValueNode.node.innerHTML = short_code;
  };
};
