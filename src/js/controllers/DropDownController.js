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
  this.init = function(view, model) {
    dropDownView = view;
    dropDownModel = model;

    // Configure model --> view data pathway
    dropDownModel
      .bindSelectedItem(dropDownView.setSelectedItem)
      .bindDropDownItemModels(dropDownView.setDropDownItemModels);

    // Configure view --> model data pathway
    dropDownView.bindClick(handleClick);
  };

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

  this.getView = function() {
    return dropDownView;
  };

  this.getModel = function() {
    return dropDownModel;
  };
};
