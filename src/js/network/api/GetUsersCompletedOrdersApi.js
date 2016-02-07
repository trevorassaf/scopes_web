GetUsersCompletedOrdersApi.prototype = new ScopesApi();
GetUsersCompletedOrdersApi.prototype.constructor = GetUsersCompletedOrdersApi;

function GetUsersCompletedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x10;

  // Api request field keys
  this.userIdKey = 'uid';
}

GetUsersCompletedOrdersApi.prototype.setUserId = function(user_id) {
  this.data[this.userIdKey] = user_id;
  return this;
}
