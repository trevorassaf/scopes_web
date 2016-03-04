var GetStartupDataApiController = (function() {

  var shortCodePicker = null;
  var getStartupDataApi = null;

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
      getStartupDataApi.setLogicalApiFailureCallback(failedApiCallback);
      getStartupDataApi.setNonLogicalApiFailureCallback(failedApiCallback);
    }

    // Fetch startup data from server
    getStartupDataApi.send();
  };

  var setShortCodePicker = function(short_code_picker) {
    shortCodePicker = short_code_picker;
    return this;
  };
  
  var successfulApiCallback = function(api_response) {
    console.assert(shortCodePicker !== null, "Must set short-code-picker");
    shortCodePicker.setShortCodes(api_response[getStartupDataApi.getShortCodesKey()]);
  };

  var failedApiCallback = function(api_response) {
    console.log(api_response); 
  };

  return {
    fetch: fetch,
    setShortCodePicker: setShortCodePicker,
    successfulApiCallback: successfulApiCallback,
    failedApiCallback: failedApiCallback
  };
})();
