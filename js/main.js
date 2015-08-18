$(document).ready(function() {

  // Content panel module
  var MainPanel = (function() { 
    // Cache main panel super header panel
    var mainPanelSuperPanel = $("#main-panel-super-header");

    // Cache main panel handle
    var mainPanel = $("#main-panel-inner");

    // Public handle
    return {
      loadPage: function(id) {
        var name = null;
        switch (id) {
          case "new-exp-btn":
            name = "New Experiment";
            break;
          case "my-exp-btn":
            name = "My Experiments";
            break;
          case "recordings-btn":
            name = "Recordings";
            break;
          case "settings-btn":
            name = "Settings";
            break;
          case "contact-us-btn":
            name = "Contact Us";
            break;
          default:
            alert("Invalid page name: " + name);
            break;
        }
        mainPanelSuperPanel.html(name); 
      }  
    };
  })();

  // Side panel module
  var SidePanel = (function(main_panel) {
  
    // Cache main panel handle
    var mainPanel = main_panel;

    var activeButton = null;

    // Set mvs button panel click listener
    $('#mvs-panel-btns').on(
      'click',
      'paper-button',
      function() {
        if (activeButton != null) {
          $(activeButton).removeAttr('active');
        }
        activeButton = $(this)[0];
        mainPanel.loadPage(activeButton.id);

      }
    );
    return {};
  })(MainPanel);

  // Load initial page
  $('#my-exp-btn').click();
});
