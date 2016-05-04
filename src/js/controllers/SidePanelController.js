var SidePanelController = function() {

  /**
   * Private state
   */
  var _this = this;

  // Views
  var sidePanelView = null;

  // Controllers
  var centerPageController = null;
  var apiController = null;

  // Models
  var userModel = null;

  /**
   * Private functions
   */
  var configureGetStartupDataApi = function() {
    // Bind custom handler logic
    var get_startup_data_api_controller = apiController.getGetStartupDataApiController();

    // Update user model startup data response
    get_startup_data_api_controller.bindSuccess(function(json_response, api_keys) {

// Debug
console.log(json_response);
console.log(api_keys);

      // Update first and last name
      userModel.setName(
        json_response[api_keys.first_name],
        json_response[api_keys.last_name]
      );

      // Update email
      userModel.setEmail(json_response[api_keys.email]);
    });
  };

  var configureCallbacks = function() {
    // Register model callbacks
    userModel.bindSetName(sidePanelView.setUserName);

    // Register network callbacks
    configureGetStartupDataApi();

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
    center_page_controller,
    user_model,
    api_controller
  ) {
    sidePanelView = side_panel_view;
    centerPageController = center_page_controller;
    userModel = user_model;
    apiController = api_controller;

    // Bind event listeners
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
