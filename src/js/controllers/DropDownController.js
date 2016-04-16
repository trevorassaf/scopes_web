var DropDownController = function() {

  /**
   * Private state
   */
  var dropDownView = null;
  var dropDownModel = null;

  /**
   * Private functions
   */
  var handleClick = function(view, idx) {
    // Exit early if we're no longer monitoring this view
    if (view != dropDownView) {
      return;
    }

    // Handle click
    dropDownModel.setSelectedItemIdx(idx);
  }

  /**
   * Privileged functions
   */
  this.setView = function(view) {
    dropDownView = view;

    // Bind event listeners
    dropDownView.bindClick(handleClick); 
    return this;
  };

  this.setModel = function(model) {
    dropDownModel = model;
    return this;
  };
};
