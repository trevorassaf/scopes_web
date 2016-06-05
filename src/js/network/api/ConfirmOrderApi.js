ConfirmOrderApi.prototype = new ScopesApi();
ConfirmOrderApi.prototype.constructor = ConfirmOrderApi;

function ConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x3;

  // Api request field keys
  this.apiRequestKeys = {
    scopes_count: "scopes-count",
    experiment_duration: "duration",
    start_timestamp: "start-time",
    short_code_id: "short-code-id",
    price: "price"
  };

  // Api response field keys
  this.apiResponseKeys = {
    id : 'id'
  };
}

ConfirmOrderApi.prototype.getApiRequestKeys = function() {
  return this.apiRequestKeys; 
};

ConfirmOrderApi.prototype.getApiResponseKeys = function() {
  return this.apiResponseKeys;
};

ConfirmOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.apiRequestKeys.scopes_count] = scopes_count;
  return this;
};

ConfirmOrderApi.prototype.setExperimentDuration = function(duration) {
  this.data[this.apiRequestKeys.experiment_duration] = duration;
  return this;
};

ConfirmOrderApi.prototype.setStartTimestamp = function(start_timestamp) {
  this.data[this.apiRequestKeys.start_timestamp] = start_timestamp;
  return this;
};

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.apiRequestKeys.short_code_id] = short_code_id;
  return this;
};

ConfirmOrderApi.prototype.setPrice = function(price) {
  this.data[this.apiRequestKeys.price] = price;
  return this;
};
