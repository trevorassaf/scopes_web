function ConfirmedOrder(
  id,
  num_scopes,
  start_timestamp,
  end_timestamp,
  title,
  description,
  time_ordered,
  price,
  short_code
) {
  this.id = id;
  this.scopesCount = num_scopes;
  this.startTimestamp = start_timestamp;
  this.endTimestamp = end_timestamp;
  this.title = title;
  this.description = description;
  this.timeOrdered = time_ordered;
  this.price = price;
  this.shortCode = short_code;
};

ConfirmedOrder.prototype.getId = function() {
  return this.id;
};

ConfirmedOrder.prototype.getStartTimestamp = function() {
  return this.startTimestamp;
};

ConfirmedOrder.prototype.getEndTimestamp = function() {
  return this.endTimestamp;
};

ConfirmedOrder.prototype.getTitle = function() {
  return this.title;
};

ConfirmedOrder.prototype.getDescription = function() {
  return this.description;
};

ConfirmedOrder.prototype.getTimeOrdered = function() {
  return this.timeOrdered;
};

ConfirmedOrder.prototype.getPrice = function() {
  return this.price;
};

ConfirmedOrder.prototype.getShortCode = function() {
  return this.shortCode;
};
