window.onload = function() {

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Configure UI elements
   */
  CenterPanelController.init();
  SidePanelUiController.init();
  NewExperimentUiController.init(template_store);
  
  /**
   * Fetch startup data and route to proper views 
   */
  GetStartupDataApiController.fetch();
};
