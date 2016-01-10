UploadEditedVideoApi.prototype = new ScopesApi();
UploadEditedVideoApi.prototype.constructor = UploadEditedVideoApi;

function UploadEditedVideoApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xB;

  // Api request param keys
  this.editedVideoOrderIdKey = 'eid';
  this.durationKey = 'duration';
  this.titleKey = "title";
  this.descriptionKey = 'description';
  this.expirationTimeKey = 'expiration-time';
}

UploadEditedVideoApi.prototype.setEditedVideoOrderId = function(edited_video_order_id) {
  this.data[this.editedVideoOrderIdKey] = edited_video_order_id;
  return this;
}

UploadEditedVideoApi.prototype.setDuration = function(duration) {
  this.data[this.durationKey] = duration;
  return this;
}

UploadEditedVideoApi.prototype.setTitle = function(title) {
  this.data[this.titleKey] = title;
  return this;
}

UploadEditedVideoApi.prototype.setDescription = function(description) {
  this.data[this.descriptionKey] = description;
  return this;
}

UploadEditedVideoApi.prototype.setExpirationTime = function(expiration_time) {
  this.data[this.expirationTimeKey] = expiration_time;
  return this;
}
