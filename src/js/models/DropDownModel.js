var DropDownModel = function() {
  // Private state
  this.selectedItemIdx = 0;
  this.dropDownItemModels = [];

  // Callback listeners
  this.selectedItemChangeCallbacks = [];
  this.dropDownItemModelsChangeCallbacks = [];
};

// Callback functions
DropDownModel.prototype.bindSelectedItem = function(callback) {
  this.selectedItemChangeCallbacks.push(callback);
  callback(this.dropDownItemModels[this.selectedItemIdx]);

  // Handle click
  return this;
};

DropDownModel.prototype.bindDropDownItemModels = function(callback) {
  this.dropDownItemModelsChangeCallbacks.push(callback);
  callback(this.dropDownItemModels);
  return this;
};

// Setters
DropDownModel.prototype.setSelectedItemIdx = function(index) {
  // Check: 'index' isn't out of bounds
  console.assert(index < this.dropDownItemModels.length);

  this.selectedItemIdx = index;
  this.selectedItemChangeCallbacks.forEach(function(callback) {
    callback(this.dropDownItemModels[this.selectedItemIdx]);
  }, this);
  return this;
};

DropDownModel.prototype.setDropDownItems = function(drop_down_item_models) {
  this.dropDownItemModels = drop_down_item_models;
  this.dropDownItemModelsChangeCallbacks.forEach(function(callback) {
    callback(this.dropDownItemModels);
  }, this);

  this.setSelectedItemIdx(0);
  return this;
};

// Getters
DropDownModel.prototype.getSelectedItem = function() {
  return this.dropDownItemModels[this.selectedItemIdx];
};

DropDownModel.prototype.getDropDownItemModels = function() {
  return this.dropDownItemModels;
};
