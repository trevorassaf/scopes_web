CellLabelRequestObject.prototype = new ScopesApiRequestObject();
CellLabelRequestObject.prototype.constructor = new CellLabelRequestObject;

function CellLabelRequestObject() {
  
  // Field keys
  this.labelKey = 'label';
}

function CellLabelRequestObject.prototype.setLabel = function(label) {
  this.data[this.labelKey] = label;
  return this;
}
