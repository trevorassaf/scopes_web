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
