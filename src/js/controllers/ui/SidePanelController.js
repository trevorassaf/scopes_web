var SidePanelUiController = (function() {

  /**
   * Ui attributes
   */
  var START_HIDDEN_ATTR = "start-hidden";
  
  /**
   * Ui node id's 
   */
  var CENTER_PAGE_TITLE_LABEL_ID = 'center-page-title-label';
  var NAVIGATION_BUTTON_CONTAINER_ID = 'nav-btns-container';
  var CENTER_PANEL_PAGE_CONTAINER = 'center-panel-page-container';

  /**
   * Private state
   */
  var currentlySelectedTabAndPageInfo = null;
  var centerPageTitleLabel = null;
  var centerPanelPageContainer = null;

  var newExperimentInfo = {
    tab_info: {
      button_title: 'Add Experiment',
      icon_type: 'add-circle-outline',
      tab: null
    },
    page_info: {
      page: null
    }
  };

  var myExperimentsInfo = {
    tab_info: {
      button_title: 'My Experiments',
      icon_type: 'group-work',
      tab: null
    },
    page_info: {
      id: 'my-exp-center-page',
      page: null
    }
  };

  var feedbackInfo = {
    tab_info: {
      button_title: 'Feedback',
      icon_type: 'question-answer',
      tab: null
    },
    page_info: {
      id: 'feedback-center-page',
      page: null
    }
  };

  var technicianInfo = {
    tab_info: {
      button_title: 'Technician',
      icon_type: 'build',
      tab: null
    },
    page_info: {
      id: 'technician-center-page',
      page: null
    }
  };

  var initTabInfo = function(
    template_store,
    tab_parent_node,
   tab_and_page_info 
  ) {
    var tab_info = tab_and_page_info.tab_info;

    // Initialize tab info
    tab_info.tab = new SidePanelTab(
      template_store,
      tab_parent_node,
      tab_info.button_title,
      tab_info.icon_type
    );

    tab_info.tab.registerOnClickListener(function() {
      selectNewTabAndShowNewPage(tab_and_page_info);
    });

    tab_info.tab.init();
  };

  var deselectCurrentTabAndHideCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.deselect();
    currentlySelectedTabAndPageInfo.page_info.page.hide();
  };

  var selectCurrentTabAndShowCurrentPage = function() {
    console.assert(currentlySelectedTabAndPageInfo !== null);
    currentlySelectedTabAndPageInfo.tab_info.tab.select();
    currentlySelectedTabAndPageInfo.page_info.page.show();
    centerPageTitleLabel.innerHTML = currentlySelectedTabAndPageInfo.tab_info.button_title;
  };

  var selectNewTabAndShowNewPage = function(tab_and_page_info) {
    deselectCurrentTabAndHideCurrentPage();
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  var initTabAndPageInfos = function(template_store) {
    // Init side-panel-container node
    var tab_parent_node = document.getElementById(NAVIGATION_BUTTON_CONTAINER_ID);

    // Init new experiment page/tab info
    newExperimentInfo.page_info.page = NewExperimentUiController;
    newExperimentInfo.page_info.page.init(template_store);
   
    // Init my experiments page
    myExperimentsInfo.page_info.page = new MyExperimentsPage(
      template_store,
      myExperimentsInfo.page_info.id,
      false
    );
    myExperimentsInfo.page_info.page.init();

    // Init feedback experiment page
    feedbackInfo.page_info.page = new FeedbackPage(
      template_store,
      feedbackInfo.page_info.id,
      false
    );
    feedbackInfo.page_info.page.init();

    // Init technician page
    // technicianInfo.page_info.page = new TechnicianPage(
    //   template_store,
    //   technicianInfo.page_info.id,
    //   false
    // );
    // technicianInfo.page_info.page.init();

    // Configure tabs
    initTabInfo(template_store, tab_parent_node, newExperimentInfo); 
    initTabInfo(template_store, tab_parent_node, myExperimentsInfo); 
    initTabInfo(template_store, tab_parent_node, feedbackInfo); 
    // initTabInfo(template_store, tab_parent_node, technicianInfo); 
  };

  function initSelectedTabAndPage(tab_and_page_info) {
    currentlySelectedTabAndPageInfo = tab_and_page_info;
    selectCurrentTabAndShowCurrentPage();
  };

  /**
   * init()
   * - initialize ui node bindings, event listeners, and starting
   *   ui state
   */
  var init = function(template_store) {
    // Init center-page title node
    centerPageTitleLabel = document.getElementById(CENTER_PAGE_TITLE_LABEL_ID);
    centerPanelPageContainer = document.getElementById(CENTER_PANEL_PAGE_CONTAINER);

    // Initialize tab and center page controllers and ui elements
    initTabAndPageInfos(template_store);

    initSelectedTabAndPage(newExperimentInfo);

    centerPanelPageContainer.removeAttribute(START_HIDDEN_ATTR);
  };

  var getMyExperimentsView = function() {
    console.assert(myExperimentsInfo.page_info.page !== null);
    return myExperimentsInfo.page_info.page;
  };

  return {
    init: init,
    getMyExperimentsView: getMyExperimentsView
  };
})();
