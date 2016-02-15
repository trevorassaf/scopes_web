GetSessionInfoApi.prototype = new ScopesApi();
GetSessionInfoApi.prototype.constructor = GetSessionInfoApi;

function GetSessionInfoApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x13;
}
