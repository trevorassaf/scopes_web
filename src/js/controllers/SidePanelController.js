var SidePanelController = function() {

  /**
   * Private state
   */
  var _this = this;

  // Views
  var sidePanelView = null;

  // Controllers
  var apiController = null;

  // Models
  var userModel = null;

  // Tab selection callbacks
  var selectNewExperimentTabCallbacks = [];
  var selectMyExperimentsTabCallbacks = [];
  var selectTechnicianTabCallbacks = [];
  var selectFeedbackTabCallbacks = [];

  /**
   * Private functions
   */
  var configureGetStartupDataApi = function() {
    // Bind custom handler logic
    var get_startup_data_api_controller = apiController.getGetStartupDataApiController();

    // Update user model startup data response
    get_startup_data_api_controller.bindSuccess(function(json_response, api_keys) {
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
    sidePanelView.bindNewExperimentTabClick(handleNewExperimentTabClick);
    sidePanelView.bindMyExperimentsTabClick(handleMyExperimentsTabClick);
    sidePanelView.bindFeedbackTabClick(handleTechnicianTabClick);
    sidePanelView.bindTechnicianTabClick(handleFeedbackTabClick);
  };

  var handleNewExperimentTabClick = function() {
    selectNewExperimentTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleMyExperimentsTabClick = function() {
    selectMyExperimentsTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleTechnicianTabClick = function() {
    selectTechnicianTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  var handleFeedbackTabClick = function() {
    selectFeedbackTabCallbacks.forEach(function(callback) {
      callback();
    });
  };

  /**
   * Privileged functions
   */
  this.init = function(
    side_panel_view,
    user_model,
    api_controller
  ) {
    sidePanelView = side_panel_view;
    userModel = user_model;
    apiController = api_controller;

    // Bind event listeners
    configureCallbacks();
  };


  this.selectNewExperimentTab = function() {
    sidePanelView.selectNewExperimentTab();
  };
  
  this.selectMyExperimentsTab = function() {
    sidePanelView.selectMyExperimentsTab();
  };

  this.selectFeedbackTab = function() {
    sidePanelView.selectFeedbackTab();
  };

  this.selectTechnicianTab = function() {
    sidePanelView.selectTechnicianTab();
  };

  /**
   * Register tab selection callbacks
   */
  this.bindNewExperimentTabSelection = function(callback) {
    selectNewExperimentTabCallbacks.push(callback);
    return this;
  };
  
  this.bindMyExperimentsTabSelection = function(callback) {
    selectMyExperimentsTabCallbacks.push(callback);
    return this;
  };

  this.bindTechnicianTabSelection = function(callback) {
    selectTechnicianTabCallbacks.push(callback);
    return this;
  };

  this.bindFeedbackTabSelection = function(callback) {
    selectFeedbackTabCallbacks.push(callback);
    return this;
  };
};
