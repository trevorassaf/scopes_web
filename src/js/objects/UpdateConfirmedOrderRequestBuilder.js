var UpdateConfirmedOrderRequestBuilder = function() {

  this.orderId = null;
  this.title = null;
  this.removeTitle = false;
  this.description = null;
  this.removeDescription = false;
};

UpdateConfirmedOrderRequestBuilder.prototype.setId = function(id) {
  this.orderId = id;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.setTitle = function(title) {
  this.title = title;
  this.removeTitle = false;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.removeTitle = function() {
  this.title = null;
  this.removeTitle = true;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.setDescription = function(description) {
  this.description = description;
  this.removeDescription = false;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.removeDescription = function() {
  this.description = null;
  this.removeDescription = true;
  return;
};

UpdateConfirmedOrderRequestBuilder.prototype.build = function() {
  // Check: id must be set!
  console.assert(this.orderId != null);

  // Check: at least one other field must be set 
  console.assert(
      this.title != null ||
      this.isTitleRemoved != null ||
      this.description != null ||
      this.isDescriptionRemoved != null
  );

  return new UpdateConfirmedOrderRequest(
    this.orderId,
    this.title,
    this.isTitleRemoved,
    this.description,
    this.isDescriptionRemoved
  );
};
