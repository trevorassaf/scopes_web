var UpdateConfirmedOrderRequest = function(
    order_id,
    title,
    is_title_removed,
    description,
   is_description_removed 
) {

  this.orderId = order_id;
  this.title = title;
  this.isTitleRemoved = is_title_removed;
  this.description = description;
  this.isDescriptionRemoved = is_description_removed;

  // Check: can't remove title and supply a new one
  console.assert(!this.isTitleRemoved || this.title == null);

  // Check: can't remove description and supply a new one
  console.assert(!this.isDescriptionRemoved || this.description == null);
};

UpdateConfirmedOrderRequest.prototype.getId = function() {
  return this.orderId;
};

UpdateConfirmedOrderRequest.prototype.isTitleRemoved = function() {
  return this.isTitleRemoved;
};

UpdateConfirmedOrderRequest.prototype.getTitle = function() {
  return this.title;
};

UpdateConfirmedOrderRequest.prototype.isDescriptionRemoved = function() {
  return this.isDescriptionRemoved;
};

UpdateConfirmedOrderRequest.prototype.getDescription = function() {
  return this.description;
};
