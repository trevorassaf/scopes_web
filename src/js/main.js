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
    hours: 10,
    minutes: 00 
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
  NewExperimentUiController.init(template_store);
  
  /**
   * Fetch startup data and route to proper views 
   */
  GetStartupDataApiController.fetch();
};
