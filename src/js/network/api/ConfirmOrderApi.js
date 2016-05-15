ConfirmOrderApi.prototype = new ScopesApi();
ConfirmOrderApi.prototype.constructor = ConfirmOrderApi;

function ConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x3;

  // Api request field keys
  this.apiKeys = {
    scopes_count: "scopes-count",
    experiment_duration: "duration",
    start_timestamp: "start-time",
    short_code_id: "short-code-id",
    price: "price"
  };
}

ConfirmOrderApi.prototype.getApiKeys = function() {
  return this.apiKeys; 
};

ConfirmOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.apiKeys.scopes_count] = scopes_count;
  return this;
};

ConfirmOrderApi.prototype.setExperimentDuration = function(duration) {
  this.data[this.apiKeys.experiment_duration] = duration;
  return this;
};

ConfirmOrderApi.prototype.setStartTimestamp = function(start_timestamp) {
  this.data[this.apiKeys.start_timestamp] = start_timestamp;
  return this;
};

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.apiKeys.short_code_id] = short_code_id;
  return this;
};

ConfirmOrderApi.prototype.setPrice = function(price) {
  this.data[this.apiKeys.price] = price;
  return this;
};
