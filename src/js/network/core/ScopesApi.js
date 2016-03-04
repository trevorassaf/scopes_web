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
