var ApplicationController = function(template_store) {

  /**
   * Private state
   */
  var templateStore = template_store;

  var centerPageController = null;
  var sidePanelController = null;
  var apiController = null;

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

    // Init center page model
    var center_page_model = new CenterPageModel();
    center_page_model.init();

    // Init center page controller
    centerPageController = new CenterPageController();
    centerPageController.init(
      center_page_view,
      center_page_model
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
     centerPageController 
    );
  };

  var initApiController = function() {
    apiController = new ApiController(ScopesNetwork);
  };

  var initControllers = function() {
    initCenterPageController();
    initSidePanelController();
    initApiController();
  };

  var initUi = function() {
    sidePanelController.selectNewExperimentTab();
  };

  /**
   * Public functions
   */
  this.init = function(template_store) {
    initControllers();     
    initUi();
  };
};
