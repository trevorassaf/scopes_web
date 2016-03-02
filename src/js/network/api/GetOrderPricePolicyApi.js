GetOrderPricePolicyApi.prototype = new ScopesApi();
GetOrderPricePolicyApi.prototype.constructor = GetOrderPricePolicyApi;

function GetOrderPricePolicyApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x14;
}
