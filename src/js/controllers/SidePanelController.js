var SidePanelController = function() {

  /**
   * Private state
   */
  var sidePanelView = null;
  var centerPageController = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Model --> view data pathways
  
    // Register tab-selection callbacks
    sidePanelView.bindNewExperimentTabClick(handleNewExperimentTabClick);
    sidePanelView.bindMyExperimentsTabClick(handleMyExperimentsTabClick);
    sidePanelView.bindFeedbackTabClick(handleFeedbackTabClick);
    sidePanelView.bindTechnicianTabClick(handleTechnicianTabClick);
  };

  var handleNewExperimentTabClick = function() {
    centerPageController.showNewExperimentPage();
  };

  var handleMyExperimentsTabClick = function() {
    centerPageController.showMyExperimentsPage();
  };

  var handleFeedbackTabClick = function() {
    centerPageController.showFeedbackPage();
  };

  var handleTechnicianTabClick = function() {
    centerPageController.showTechnicianPage();
  };

  /**
   * Privileged functions
   */
  this.init = function(
    side_panel_view,
    center_page_controller
  ) {
    sidePanelView = side_panel_view;
    centerPageController = center_page_controller;

    configureCallbacks();
  };
};
