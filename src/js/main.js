window.onload = function() {

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

  /**
   * Configure time-picker element
   */
  var start_time = {
    hours: 9,
    minutes: 30
  };

  var end_time = {
    hours: 17,
    minutes: 30 
  };

  var time_picker = new TimePicker(
    template_store,
    'exp-time-picker',
    start_time,
    end_time,
    30
  ); 
  time_picker.init();

  /**
   * Configure calendar element
   */
  var disallowed_week_days = new Set([0, 6]);
  var calendar = new Calendar(
      template_store,
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
  // var get_session_info_api = new GetSessionInfoApi(ScopesNetwork); 
  // get_session_info_api
  //   .setSuccessfulCallback(
  //     function (response) {
  //       console.log("Success for GetSessionInfoApi!"); 
  //       console.log(response.responseText);
  //     }    
  //   )
  //   .setFailedCallback(
  //     function (response) {
  //       console.log("Failure for GetSessionInfoApi!"); 
  //       console.log(response.responseText);
  //     }    
  //   )
  //   .send();
};
