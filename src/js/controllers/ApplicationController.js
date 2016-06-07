var ApplicationController = function(template_store) {

  /**
   * Private state
   */
  var templateStore = template_store;

  var _this = this;

  // Controllers
  var centerPageController = null;
  var sidePanelController = null;
  var apiController = null;

  // Models
  var applicationModel = null;

  /**
   * Private functions
   */
  var initCenterPageController = function() {
    // Init center page view
    var center_page_node = document.getElementById('center-panel');

    var center_page_view = new CenterPageView(
      templateStore,
      center_page_node
    );
    center_page_view.init();

    // Init center page controller
    centerPageController = new CenterPageController();
    centerPageController.init(
      center_page_view,
      applicationModel.getCenterPageModel(),
      apiController
    );
  };

  var initSidePanelController = function() {
    // Init side panel view
    var side_panel_parent_root = document.getElementById('side-panel');

    var side_panel_view = new SidePanelView(
      templateStore,
      side_panel_parent_root
    );
    side_panel_view.init();

    // Init side panel controller
    sidePanelController = new SidePanelController();
    sidePanelController.init(
      side_panel_view,
      applicationModel.getUserModel(),
      apiController
    );
  };

  var initApiController = function() {
    apiController = new ApiController();
    apiController.init();
  };

  var configureControllers = function() {
    // Navigate to proper page when side panel tab is clicked
    sidePanelController.bindNewExperimentTabSelection(_this.showNewExperimentPage);
    sidePanelController.bindMyExperimentsTabSelection(_this.showMyExperimentsPage);
    sidePanelController.bindTechnicianTabSelection(_this.showTechnicianPage);
    sidePanelController.bindFeedbackTabSelection(_this.showFeedbackPage);
    
    // Navigate to 'MyExperiments' page on new experiment
    centerPageController.bindNewExperiment(_this.showMyExperimentsPage);
  };

  var initControllers = function() {
    // Init individual controllers
    initApiController();
    initCenterPageController();
    initSidePanelController();

    // Configure controllers with mutual responsibilities
    configureControllers(); 
  };

  var initUi = function() {
    sidePanelController.selectNewExperimentTab();
  };

  var initModels = function() {
    applicationModel = new ApplicationModel();
    applicationModel.init();
  };

  /**
   * Public functions
   */
  this.init = function(template_store) {
    initModels();
    initControllers();     
    initUi();

    // Fetch startup data
    apiController.getGetStartupDataApiController().fetch();

    // Configure initial ui
    _this.showNewExperimentPage();
  };

  this.showNewExperimentPage = function() {
    sidePanelController.selectNewExperimentTab();
    centerPageController.showNewExperimentPage();
  };

  this.showMyExperimentsPage = function() {
    sidePanelController.selectMyExperimentsTab();
    centerPageController.showMyExperimentsPage();
  };

  this.showTechnicianPage = function() {
    sidePanelController.selectTechnicianTab();
    centerPageController.showTechnicianPage();
  };

  this.showFeedbackPage = function() {
    sidePanelController.selectFeedbackTab();
    centerPageController.showFeedbackPage();
  };
};
