GetUsersConfirmedOrdersApi.prototype = new ScopesApi();
GetUsersConfirmedOrdersApi.prototype.constructor = GetUsersConfirmedOrdersApi;

function GetUsersConfirmedOrdersApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x9;

  // Api request field keys
  this.userIdKey = 'uid';
}

GetUsersConfirmedOrdersApi.prototype.setUserId = function(user_id) {
  this.data[this.userIdKey] = user_id;
  return this;
}
