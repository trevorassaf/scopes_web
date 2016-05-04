var SidePanelController = function() {

  /**
   * Private state
   */
  var _this = this;

  var sidePanelView = null;
  var centerPageController = null;

  /**
   * Private functions
   */
  var configureCallbacks = function() {
    // Register tab-selection callbacks
    sidePanelView.bindNewExperimentTabClick(_this.selectNewExperimentTab);
    sidePanelView.bindMyExperimentsTabClick(_this.selectMyExperimentsTab);
    sidePanelView.bindFeedbackTabClick(_this.selectFeedbackTab);
    sidePanelView.bindTechnicianTabClick(_this.selectTechnicianTab);
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


  this.selectNewExperimentTab = function() {
    sidePanelView.selectNewExperimentTab();
    centerPageController.showNewExperimentPage();
    return this;
  };
  
  this.selectMyExperimentsTab = function() {
    sidePanelView.selectMyExperimentsTab();
    centerPageController.showMyExperimentsPage();
    return this;
  };

  this.selectFeedbackTab = function() {
    sidePanelView.selectFeedbackTab();
    centerPageController.showFeedbackPage();
    return this;
  };

  this.selectTechnicianTab = function() {
    sidePanelView.selectTechnicianTab();
    centerPageController.showTechnicianPage();
    return this;
  };
};
