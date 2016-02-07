GetAllUsersApi.prototype = new ScopesApi();
GetAllUsersApi.prototype.constructor = GetAllUsersApi;

function GetAllUsersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xD;
}
