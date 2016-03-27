UpdateConfirmOrderApi.prototype = new ScopesApi();
UpdateConfirmOrderApi.prototype.constructor = UpdateConfirmOrderApi;

function UpdateConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x4;

  // Api request field keys
  this.apiKeys = {
    id: 'cid',
    title: 'title',
    description: 'desc',
    short_code_id: 'code'
  };
}

UpdateConfirmOrderApi.prototype.getApiKeys = function() {
  return this.apiKeys;
};

UpdateConfirmOrderApi.prototype.setConfirmedOrderId = function(id) {
  this.data[this.apiKeys.id] = id;
  return this;
};

UpdateConfirmOrderApi.prototype.setTitle = function(title) {
  this.data[this.apiKeys.title] = title;
  return this;
};

UpdateConfirmOrderApi.prototype.setDescription = function(description) {
  this.data[this.apiKeys.description] = description;
  return this;
};

UpdateConfirmOrderApi.prototype.setShortCodeId = function(id) {
  this.data[this.apiKeys.short_code_id] = id;
  return this;
};
