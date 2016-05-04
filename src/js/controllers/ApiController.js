var ApiController = function(network_module) {

  /**
   * Private state
   */
  // Api dependencies
  var networkModule = network_module;

  // Apis
  var confirmOrderApi = null;
  var getAllUsersApi = null;
  var getConfirmedOrdersApi = null;
  var getOrderPricePolicyApi = null;
  var getStartupDataApi = null;
  var updateConfirmedOrderApi = null;

  // Event listeners
  var lostConnectionListeners = [];
  var badRequestListeners = [];

  /**
   * Private functions
   */
  // Bind generic event listeners
  var initApi = function(api) {};

  /**
   * Public functions
   */
  // Lazy loader api getters
  this.getConfirmOrderApi = function() {
    if (confirmOrderApi == null) {
      confirmOrderApi = new ConfirmOrderApi(networkModule);
      initApi(confirmOrderApi);
    }
    return confirmOrderApi;
  };

  this.getStartupDataApi = function() {
    if (getStartupDataApi == null) {
      getStartupDataApi = new GetStartupDataApi(networkModule);
      initApi(getStartupDataApi);
    }
    return getStartupDataApi;
  };

  this.getAllUsersApi = function() {
    if (getAllUsersApi == null) {
      getAllUsersApi = new GetAllUsersApi(networkModule);
      initApi(getAllUsersApi);
    }
    return getAllUsersApi;
  };
  
  this.getOrderPricePolicyApi = function() {
    if (getOrderPricePolicyApi == null) {
      getOrderPricePolicyApi = new GetOrderPricePolicyApi(networkModule);
      initApi(getOrderPricePolicyApi);
    }
    return getOrderPricePolicyApi;
  };

  this.updateConfirmedOrderApi = function() {
    if (updateConfirmedOrderApi == null) {
      updateConfirmedOrderApi = new UpdateConfirmedOrderApi(networkModule);
      initApi(updateConfirmedOrderApi);
    }
    return updateConfirmedOrderApi;
  };

  // Register event listeners
  this.bindLostConnection = function(callback) {
    lostConnectionListeners.push(callback);
    return this;
  };

  this.bindBadRequest = function(callback) {
    badRequestListeners.push(callback);
    return this;
  };
};
