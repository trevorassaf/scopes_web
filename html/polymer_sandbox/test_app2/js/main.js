window.onload = function() {

  /**
   * Configure UI elements
   */
  CenterPanelController.init();
  SidePanelUiController.init();
  NewExperimentUiController.init();

  /**
   * Fetch session information
   */
  var get_session_info_api = new GetSessionInfoApi(ScopesNetwork); 
  get_session_info_api
    .setSuccessfulCallback(
      function (response) {
        console.log("Success for GetSessionInfoApi!"); 
        console.log(response.responseText);
      }    
    )
    .setFailedCallback(
      function (response) {
        console.log("Failure for GetSessionInfoApi!"); 
        console.log(response.responseText);
      }    
    )
    .send();
};
