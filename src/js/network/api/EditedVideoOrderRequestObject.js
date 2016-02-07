EditedVideoOrderRequestObject.prototype = new ScopesApiRequestObject();
EditedVideoOrderRequestObject.prototype.constructor = EditedVideoOrderRequestObject;

function EditedVideoOrderRequestObject() {

  // Field keys
  this.recordingDurationMinutesKey = 'duration';
  this.cellLabelsKey = 'cells';
}

function EditedVideoOrderRequestObject.prototype.setRecordingDurationMinutes = function(duration) {
  this.data[this.recordingDurationMinutesKey] = duration;
  return this;
}

function EditedVideoOrderRequestObject.prototype.pushCellLabel = function(cell_label) {
  if (!(this.cellLabelsKey in this.data)) {
    this.data[this.cellLabelsKey] = [];
  }

  this.data[this.cellLabelsKey].push(cell_label.getData());
}
