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
