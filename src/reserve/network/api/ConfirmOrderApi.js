ConfirmOrderApi.prototype = new ScopesApi();
ConfirmOrderApi.prototype.constructor = ConfirmOrderApi;

function ConfirmOrderApi(network_module) {
  this.networkModule = network_module;
  this.apiType = 0x3;

  // Api request field keys
  this.reservedOrderIdKey = "rid";  
  this.titleKey = "title";
  this.descriptionKey = "desc";
  this.shortCodeIdKey = "code-id";
  this.editedVideoOrderKey = "edited-video-order";
}

ConfirmOrderApi.prototype.setReservedOrderId = function(reserved_order_id) {
  this.data[this.reservedOrderIdKey] = reserved_order_id;
  return this;
}

ConfirmOrderApi.prototype.setTitle = function(title) {
  this.data[this.titleKey] = title;
  return this;
}

ConfirmOrderApi.prototype.setDescription = function(description) {
  this.data[this.descriptionKey] = description;
  return this;
}

ConfirmOrderApi.prototype.setShortCodeId = function(short_code_id) {
  this.data[this.shortCodeIdKey] = short_code_id;
  return this;
}

ConfirmedOrdereApi.prototype.setEditedVideoOrderRequestObject = function(edited_video_order_request_object) {
  this.data[this.editedVideoOrderKey] = edited_video_order_request_object.getData();
  return this;
}
