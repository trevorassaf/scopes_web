var ApplicationController = function(template_store) {

  /**
   * Private state
   */
  var templateStore = template_store;

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
      centerPageController,
      applicationModel.getUserModel(),
      apiController
    );
  };

  var initApiController = function() {
    apiController = new ApiController();
    apiController.init();
  };

  var initControllers = function() {
    initApiController();
    initCenterPageController();
    initSidePanelController();
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
  };
};
