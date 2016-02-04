window.onload = function() {

  var disallowed_week_days = new Set([0, 6]);
  var calendar = new Calendar(
      'exp-date-calendar',
      disallowed_week_days,
      {},
      3,
      0 
  );
  calendar.init();

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
