GetUsersReservedOrdersApi.prototype = new ScopesApi();
GetUsersReservedOrdersApi.prototype.constructor = GetUsersReservedOrdersApi;

function GetUsersReservedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xF;

  // Api request field keys
  this.userIdKey = 'uid';
}

GetUsersReservedOrdersApi.prototype.setUserId = function(user_id) {
  this.data[this.userIdKey] = user_id;
  return this;
}
