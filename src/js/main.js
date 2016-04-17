window.onload = function() {

  document.execCommand('defaultParagraphSeparator', false, 'p');

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Initialize center page
   */
  // Center page view
  var center_page_node = document.getElementById('center-panel');

  var center_page_view = new CenterPageView(
    template_store,
    center_page_node
  );
  center_page_view.init();
  center_page_view.showNewExperimentPage();

  // Center page model
  var center_page_model = new CenterPageModel();
  center_page_model.init();

  // Center page controller
  var center_page_controller = new CenterPageController();
  center_page_controller.init(
    center_page_view,
    center_page_model
  );
  
  /**
   * Initialize side panel
   */
  // Side panel view
  var side_panel_parent_root = document.getElementById('side-panel');

  var side_panel_view = new SidePanelView(
    template_store,
    side_panel_parent_root
  );
  side_panel_view.init();
  side_panel_view.selectNewExperimentTab();

  // Side panel controller
  var side_panel_controller = new SidePanelController();
  side_panel_controller.init(
    side_panel_view,
    center_page_controller
  );

  // Initialize page controller
  // var page_controller = new PageController(
  //   side_panel_view,
  //   new_experiment_page_view
  // );
  // page_controller.init();

  // Initialize pages

  // #<{(|*
  //  * Configure UI elements
  //  |)}>#
  // SidePanelUiController.init(template_store);
  //
  // #<{(|*
  //  * Fetch startup data and route to proper views 
  //  |)}>#
  // GetStartupDataApiController.fetch();
  //
  // var my_experiments_view = SidePanelUiController.getMyExperimentsView();
  // MyExperimentsLogicController.init(my_experiments_view);
  //
  // NewExperimentUiController.registerOrderConfirmedListener(function() {
  //   MyExperimentsLogicController.refreshData();
  // });
};
