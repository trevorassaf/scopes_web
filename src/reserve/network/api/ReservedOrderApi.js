ReserveOrderApi.prototype = new ScopesApi();
ReserveOrderApi.prototype.constructor = ReserveOrderApi;

function ReserveOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x2;

  // Api request field keys
  this.userIdKey = 'user-id';
  this.scopesCountKey = 'scopes-count';
  this.startTimeKey = 'start-time';
  this.endTimeKey = 'end-time';
}

ReserveOrderApi.prototype.setUserId = function(user_id) {
  this.data[this.userIdKey] = user_id;
  return this;
}

ReserveOrderApi.prototype.setScopesCount = function(scopes_count) {
  this.data[this.scopesCountKey] = scopes_count;
  return this;
}

ReserveOrderApi.prototype.setStartTime = function(start_time) {
  this.data[this.startTimeKey] = start_time;
  return this;
}

ReserveOrderApi.prototype.setEndTime = function(end_time) {
  this.data[this.endTimeKey] = end_time;
  return this;
}
