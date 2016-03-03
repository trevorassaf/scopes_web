var SidePanelUiController = (function() {
  
  /**
   * Ui node id's 
   */
  var CENTER_PAGE_TITLE_LABEL_ID = 'center-page-title-label';

  var NAVIGATION_BUTTON_CONTAINER_ID = 'nav-btns-container';

  /**
   * Navigation button info
   */
  var addExperimentPageInfo = {
    id: 'add-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayAddExperimentPage
  };

  var myExperimentsPageInfo = {
    id: 'my-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayMyExperimentsPage
  };
  
  var recordedExperimentsPageInfo = {
    id: 'recorded-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayRecordedExperimentsPage
  };
  
  var monitorExperimentPageInfo = {
    id: 'monitor-exp-btn',
    node: null,
    displayCenterPagePtr: CenterPanelController.displayMonitorExperimentPage
  };

  var ADD_EXP_BTN_ID = 'add-exp-btn';
  var MY_EXP_BTN_ID = 'my-exp-btn';
  var RECORDED_EXP_BTN_ID = 'recorded-exp-btn';
  var MONITOR_EXP_BTN_ID = 'monitor-exp-btn';

  /**
   * Ui classes
   */
  var DASH_NAV_PANEL_BTN_CLASS = 'dash-nav-panel-btn';

  /**
   * Ui attributes
   */
  var SELECTED_ATTR = 'selected';
  
  /**
   * Ui nodes
   */
  var centerPageTitleLabel = null;

  /**
   * Id to node info map
   */
  var idToNodeInfoMap = {};

  var currentSelectedPageNode = null;

  /**
   * changeCenterPage()
   * - switch center page
   */
  var changeCenterPage = function(next_page_id) {
    // Check that page id is valid
    console.assert(
        idToNodeInfoMap.hasOwnProperty(next_page_id),
        'illegal key in idToNodeInfoMap: ' + next_page_id
      );

    // At startup, we don't have a 'current_page,' so we jump
    // immediately to the 'next_page' rendering
    if (currentSelectedPageNode != null) {
      // Skip page change because same page would be rendered
      if (currentSelectedPageNode.id == next_page_id) {
        return;
      }

      // Deselect current page
      console.assert(currentSelectedPageNode.hasAttribute(SELECTED_ATTR));
      currentSelectedPageNode.removeAttribute(SELECTED_ATTR); 
    }

    // Fetch 'next_page'
    var next_page_info = idToNodeInfoMap[next_page_id];

    // Lazy load ui dom node
    if (next_page_info.node == null) {
      next_page_info.node = document.getElementById(next_page_info.id);
      console.assert(
        next_page_info.node != null,
        'Illegal state: failed to lazy load side panel nav button (id=' + next_page_id + ')'
      );
    }
    
    console.assert(
        !next_page_info.node.hasAttribute(SELECTED_ATTR),
        'Illegal state: next-page (id=' + next_page_id + ') already has SELECTED_ATTR'
    );

    // Select new page and render center page
    next_page_info.node.setAttribute(SELECTED_ATTR, "");
    next_page_info.displayCenterPagePtr();

    // Update 'currentSelectedPageNode'
    currentSelectedPageNode = next_page_info.node;
  };

  /**
   * init()
   * - initialize ui node bindings, event listeners, and starting
   *   ui state
   */
  var init = function() {
    // Init DOM nodes
    centerPageTitleLabel = document.getElementById(CENTER_PAGE_TITLE_LABEL_ID);

    // Init id to ui node map
    idToNodeInfoMap[ADD_EXP_BTN_ID] = addExperimentPageInfo;
    idToNodeInfoMap[MY_EXP_BTN_ID] = myExperimentsPageInfo;
    idToNodeInfoMap[RECORDED_EXP_BTN_ID] = recordedExperimentsPageInfo;
    idToNodeInfoMap[MONITOR_EXP_BTN_ID] = monitorExperimentPageInfo;

    // Bind event listeners
    document.getElementById(NAVIGATION_BUTTON_CONTAINER_ID).onclick = function(event) {
      // Search event propagation path for selected navigation button
      for (var i=0; i < event.path.length; ++i) {
        var node = event.path[i];
        if (node.classList.contains(DASH_NAV_PANEL_BTN_CLASS)) {
          changeCenterPage(node.id);
          break;
        }
      }
    };

    // Set initial page: new experiment
    changeCenterPage(ADD_EXP_BTN_ID);
  };

  return {
    init: init
  };
})();
