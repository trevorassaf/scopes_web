window.onload = function() {

  /**
   * Configure UI elements
   */
  console.log(NewExperimentUiController);
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

  var NAV_PANEL_ID = "dash-nav-panel";
  var ADD_EXP_BTN_ID = 'add-exp-btn';
  var SELECTED_ATTR = "selected";
  /**
   * Page Navigation Panel Setup
   */
  // Bind buttons
  var add_exp_btn = document.getElementById(ADD_EXP_BTN_ID);
  var view_proj_btn = document.getElementById("view-proj-btn");
  var video_lib_btn = document.getElementById("video-lib-btn");
  var live_monitor_btn = document.getElementById("live-monitor-btn");

  var nav_panel_btn_id_map = {};
  nav_panel_btn_id_map[add_exp_btn.id] = add_exp_btn;
  nav_panel_btn_id_map[view_proj_btn.id] = view_proj_btn;
  nav_panel_btn_id_map[video_lib_btn.id] = video_lib_btn;
  nav_panel_btn_id_map[live_monitor_btn.id] = live_monitor_btn;

  var current_page = null;

  var changePage = function(next_page) {
    // At startup, we don't have a 'current_page,' so we jump
    // immediately to the 'next_page' rendering
    if (current_page != null) {
      // Skip page change because same page would be rendered
      if (current_page.id == next_page.id) {
        return;
      }

      //// Change to page indicated by'next_page_id'
      // Deselect current page
      console.assert(current_page.hasAttribute(SELECTED_ATTR));
      current_page.removeAttribute(SELECTED_ATTR); 
    }

    // Select next page
    console.assert(!next_page.hasAttribute(SELECTED_ATTR));
    next_page.setAttribute(SELECTED_ATTR, "");

    // Update 'current_page'
    current_page = next_page;
  };

  // Set initial page
  changePage(add_exp_btn);

  // Bind event listener
  var nav_panel = document.getElementById("dash-nav-panel");
  nav_panel.onclick = function(event) {
    // Search event propagation path for selected navigation button
    for (var i=0; i < event.path.length; ++i) {
      var node = event.path[i];
      if (node.classList.contains('dash-nav-panel-btn')) {
        var next_page = nav_panel_btn_id_map[node.id];
        changePage(next_page);
        break;
      }
    }
  };
};
