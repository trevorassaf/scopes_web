var GetStartupDataApiController = function() {

  /**
   * Private state
   */
  var getStartupDataApi = null;
  var successListeners = [];
  var logicalFailureListeners = [];
  var nonLogicalFailureListeners = [];

  /**
   * fetch()
   * - fetches startup data
   */
  this.fetch = function() {
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
    for (var i = 0; i < successListeners.length; ++i) {
      successListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };
  
  var logicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < logicalFailureListeners.length; ++i) {
      logicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  var nonLogicallyFailedApiCallback = function(api_response) {
    console.log("WARNING: Logically failed api response!");
    console.log(api_response); 
    
    for (var i = 0; i < nonLogicalFailureListeners.length; ++i) {
      nonLogicalFailureListeners[i](api_response, getStartupDataApi.getApiKeys());
    }
  };

  /**
   * registerSuccessfulApiCallback()
   * - add callback for successful api call
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindSuccess = function(callback) {
    successListeners.push(callback);
    return this;
  };

  /**
   * registerLogicalFailedApiCallback()
   * - add callback for logical failed api call (i.e. api error error rather than network error)
   * @param FuncPtr callback: function(json_response, api_keys) {...}
   */
  this.bindLogicalFailure = function(callback) {
    logicalFailureListeners.push(callback);
    return this;
  };

  /**
   * registerNonLogicalFailedApiCallback()
   * - add callback for non-logical failed api call (i.e. network error rather than api error)
   * @param FuncPtr callback: function(xhttp_response) {...}
   */
  this.bindNonLogicalFailure = function(callback) {
    nonLogicalFailureListeners.push(callback);
    return this;
  };
};
