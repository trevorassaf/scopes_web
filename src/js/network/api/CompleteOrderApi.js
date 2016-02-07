CompleteOrderApi.prototype = new ScopesApi();
CompleteOrderApi.prototype.constructor = CompleteOrderApi;

function CompleteOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xC;

  // Api request field keys
  this.confirmedOrderIdKey = "cid";
}

CompleteOrderApi.prototype.setConfirmedOrderId = function(confirmed_order_id) {
  this.data[this.confirmedOrderIdKey] = confirmed_order_id;
  return this;
}
