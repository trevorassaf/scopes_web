UploadBasicVideoApi.prototype = new ScopesApi();
UploadBasicVideoApi.prototype.constructor = UploadBasicVideoApi;

function UploadBasicVideoApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0xA;

  // Api request param keys
  this.completedOrderIdKey = 'cid';
  this.titleKey = 'title';
  this.durationKey = 'duration';
  this.fileNameKey = 'file-name';
  this.descriptionKey = 'description';
  this.videoKey = 'video';
}

UploadBasicVideoApi.prototype.setCompletedOrderId = function(completed_order_id) {
  this.data[this.completedOrderIdKey] = completed_order_id;
  return this;
}

UploadBasicVideoApi.prototype.setTitle = function(title) {
  this.data[this.titleKey] = title;
  return this;
}

UploadBasicVideoApi.prototype.setDuration = function(duration) {
  this.data[this.durationKey] = duration;
  return this;
}

UploadBasicVideoApi.prototype.setFileName = function(file_name) {
  this.data[this.fileNameKey] = file_name;
  return this;
}

UploadBasicVideoApi.prototype.setDescription = function(description) {
  this.data[this.descriptionKey] = description;
  return this;
}
