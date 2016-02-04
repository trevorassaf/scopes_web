$(document).ready(function() {

  var PageController = function(
    title,
    $page_root,
    activater,
    reducer 
  ) {
    var _title = title; 
    var _$pageRoot = $page_root;
    var _activater = activater;
    var _reducer = reducer;
    
    return {
      getTitle: function() {
        return _title; 
      },

      activate: function() {
        _activater(_$pageRoot);
      },

      reduce: function() {
        _reducer(_$pageRoot);
      }
    };
  };

  var NewExpPageController = function() {
    
  };

  // Content panel module
  var MainPanel = (function() { 
    // Cache main panel super header panel
    var mainPanelSuperPanel = $("#main-panel-super-header");

    // Cache main panel handle
    var mainPanel = $("#main-panel-inner");

    // Map of button-id to corresponding
    // main-page controller
    var mainPageCache = [];

    // Public handle
    return {
      loadPage: function(id) {
        var name = null;
        switch (id) {
          case "new-exp-btn":
            name = "New Experiment";
            if (!(id in mainPageCache)) {
                        
            }
            break;
          case "my-exp-btn":
            name = "My Experiments";
            if (!(id in mainPageCache)) {
              
            }
            break;
          case "recordings-btn":
            name = "Recordings";
            if (!(id in mainPageCache)) {
              
            }
            break;
          case "settings-btn":
            name = "Settings";
            if (!(id in mainPageCache)) {
              
            }
            break;
          case "contact-us-btn":
            name = "Contact Us";
            if (!(id in mainPageCache)) {
              
            }
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
    
    // Load initial page
    $('#new-exp-btn').click();
    
    return {};
  })(MainPanel);

});
