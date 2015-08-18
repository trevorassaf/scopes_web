$(document).ready(function() {
  // Bind back button
  var back_button = $("#mvs-back-btn-container");
  back_button.on('click', function() {
    alert("back"); 
  }); 

  var mvs_button_panel = $("#mvs-panel-btns");
  var mvs_side_panel_buttons = mvs_button_panel.find("paper-button");
  var selected_side_panel_button = null;
  console.log(mvs_side_panel_buttons);
  mvs_button_panel.on(
    'click',
    'paper-button',
    function() {
      if (selected_side_panel_button != null) {
        $(selected_side_panel_button).removeAttr('active');
      }
      selected_side_panel_button = $(this)[0];;
    }  
  );
});
