/**
 * ScopesApi
 * - base class for all api calls.
 * @req: all child classes assign 'this.apiType' to corresponding api-type value
 *       in constructor.
 * @req: all child classes assign 'network_module' to 'this.networkModule'
 *       in constructor
 */

function ScopesApi(network_module) {
  this.networkModule = network_module;
  this.data = {};
  this.isAsync = true;
  this.successfulCallback = function() {};
  this.failedCallback = function() {};
}

ScopesApi.prototype.setIsAsync = function(is_async) {
  this.isAsync = is_async;
  return this;
}

ScopesApi.prototype.setSuccessfulCallback = function(callback) {
  this.successfulCallback = callback;
  return this;
}

ScopesApi.prototype.setFailedCallback = function(callback) {
  this.failedCallback = callback;
  return this;
}

ScopesApi.prototype.send = function() {
  return this.networkModule.request(
    this.apiType,
    this.data,
    this.isAsync,
    this.successfulCallback,
    this.failedCallback
  );    
}
