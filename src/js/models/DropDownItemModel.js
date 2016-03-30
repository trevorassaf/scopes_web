var DropDownItemModel = function(
  label,
  tooltip,
  data
) {
  // Private state
  this.label = label
  this.tooltip = tooltip;
  this.data = data;

  // Event listeners
  this.labelChangeCallbacks = [];
  this.tooltipChangeCallbacks = [];
};

// Setters
DropDownItemModel.prototype.setLabel = function(label) {
  this.label = label;
  this.labelChangeCallbacks.forEach(function(callback) {
    callback(label);
  });
  return this;
};

DropDownItemModel.prototype.setTooltip = function(tooltip) {
  this.tooltip = tooltip;
  this.tooltipChangeCallbacks.forEach(function(callback) {
    callback(tooltip);
  });
  return this;
};

// Bind event listeners
DropDownItemModel.prototype.bindLabel = function(callback) {
  this.labelChangeCallbacks.push(callback);
  callback(this.label);
  return this;
};

DropDownItemModel.prototype.bindTooltip = function(callback) {
  this.tooltipChangeCallbacks.push(callback);
  callback(this.tooltip);
  return this;
};

// Getters
DropDownItemModel.prototype.getLabel = function() {
  return this.label;
};

DropDownItemModel.prototype.getTooltip = function() {
  return this.tooltip;
};

DropDownItemModel.prototype.getData = function() {
  return this.data;
};
