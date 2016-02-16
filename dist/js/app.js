window.onload = function() {

  /**
   * Capture import node for html templates
   */
  var template_store = document.querySelector('#template-import');
  console.assert(template_store != null);

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

var CenterPanelController = (function() {

  /**
   * Dom ui id's
   */
  var TITLE_LABEL_ID = 'center-page-title-label';

  /**
   * Attribute names
   */
  var HIDDEN_PAGE_ATTRIBUTE = 'hidden-page';

  /**
   * Dom nodes
   */
  var currentPage = null;
  var titleLabel = null;

  /**
   * Center panel data structures
   */
  var addExperimentPageInfo = {
    title: 'Add Experiment',
    container_id : 'add-exp-center-page',
    container : null
  };
  
  var myExperimentsPageInfo = {
    title: 'My Experiments',
    container_id : 'my-exp-center-page',
    container : null
  };
  
  var recordedExperimentsPageInfo = {
    title: 'Recorded Experiments',
    container_id : 'recorded-exp-center-page',
    container : null
  };

  var monitorExperimentPageInfo = {
    title: 'Monitor Experiment',
    container_id : 'monitor-exp-center-page',
    container : null
  };

  /**
   * changePage()
   * - change page to page indicated in 'next_page_info'
   */
  this.changePage = function(next_page_info) {
    // Check to see if 'currentPage' is set. If not, then this ui module is
    // just being initialized.
    if (currentPage != null) {
      // Skip change b/c we're switching to the same page
      if (next_page_info.container_id == currentPage.id) {
        return;
      }

      // Hide 'currentPage'
      console.assert(
        !currentPage.hasAttribute(HIDDEN_PAGE_ATTRIBUTE),
        'Illegal state: current page (id=' + currentPage.id + ') should not have the HIDDEN_LABEL_ATTRIBUTE'
      );

      currentPage.removeAttribute(HIDDEN_PAGE_ATTRIBUTE);
    }

    // Display page indicated by 'next_page_info'
    if (next_page_info.container == null) {
      next_page_info.container = document.getElementById(next_page_info.container_id);
      console.assert(
        next_page_info.container != null,
        'Illegal state: next page (id=' + next_page_info.container_id + ') has invalid id'
      );
    }

    titleLabel.innerHTML = next_page_info.title;
    currentPage = next_page_info.container;
    currentPage.removeAttribute(HIDDEN_PAGE_ATTRIBUTE);
  };

  /**
   * init()
   * - bind dom ui nodes and event listeners, configure ui for startup
   */
  this.init = function() {
    // Load dom ui nodes
    titleLabel = document.getElementById(TITLE_LABEL_ID);

    // Configure Ui
    displayAddExperimentPage(); 
  };
  
  /**
   * dispalyAddExperimentPage()
   * - hide previous page and display add experiment page 
   */
  this.displayAddExperimentPage = function() {
    changePage(addExperimentPageInfo);
  };

  /**
   * dispalyMyExperimentsPage()
   * - hide previous page and display my experiments page 
   */
  this.displayMyExperimentsPage = function() {
    changePage(myExperimentsPageInfo);
  };

  /**
   * dispalyRecordedExperimentsPage()
   * - hide previous page and display recorded experiments page 
   */
  this.displayRecordedExperimentsPage = function() {
    changePage(recordedExperimentsPageInfo);
  };
  
  /**
   * dispalyMonitorExperimentPage()
   * - hide previous page and display monitor experiment page 
   */
  this.displayMonitorExperimentPage = function() {
    changePage(monitorExperimentPageInfo);
  };

  return {
    init: init,
    displayAddExperimentPage: displayAddExperimentPage,
    displayMyExperimentsPage: displayMyExperimentsPage,
    displayRecordedExperimentsPage: displayRecordedExperimentsPage,
    displayMonitorExperimentPage: displayMonitorExperimentPage
  };

})();

var NewExperimentUiController = (function() {

  /**
   * Ui attributes
   */
  var HIDDEN_VALIDATION_ICON_ATTRIBUTE = 'hidden-validation-icon';

  /**
   * Ui node id's
   */
  // Scope count
  var scopesCountUiFormInfo = {
    id_set: {
      display: 'scopes-count-display',
      display_unit: 'scopes-count-display-unit',
      input: 'scopes-count-input',
      valid_icon: 'scopes-count-valid-icon',
      invalid_icon: 'scopes-count-invalid-icon'
    },
    
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null,
      valid_icon: null,
      invalid_icon: null
    },

    display_labels: {
      singular: 'scope',
      plural: 'scopes'
    },

    value_change_count: 0
  };
  
  // Experiment duration
  var durationUiFormInfo = {
    id_set: {
      display: 'duration-display',
      display_unit: 'duration-display-unit',
      input: 'duration-input',
      valid_icon: 'duration-valid-icon',
      invalid_icon: 'duration-invalid-icon'
    },
  
    ui_nodes: {
      input_field: null,
      display_unit: null,
      display: null,
      valid_icon: null,
      invalid_icon: null
    },

    display_labels: {
      singular: 'hour',
      plural: 'hours'
    },

    value_change_count: 0
  };

  /**
   * Ui util functions
   */
  /**
   * Update the display for an input form.
   *
   * @param: int count: number of microscopes
   * @param: Obj ui_form_info: data for form ui element (see 
   *    'this.scopesCountUiFormInfo')
   */
  this.updateDisplay = function(count, ui_form_info) {
    ui_form_info.ui_nodes.display.innerHTML = count;
    ui_form_info.ui_nodes.display_unit.innerHTML = (count == 1)
      ? ui_form_info.display_labels.singular
      : ui_form_info.display_labels.plural;
  };

  /**
   * Updates input node and display labels for the form.
   *
   * @param: Obj ui_form_info: data for form ui element (see 
   *    'this.scopesCountUiFormInfo')
   * @param: int count: number of microscopes
   */
  this.setInputValue = function(ui_form_info, count) {
    // Skip if same value
    if (ui_form_info.ui_nodes.input_field.value == count) {
      return;
    }

    // Update with new 'count' 
    ui_form_info.ui_nodes.input_field.value = count;
    updateDisplay(count, ui_form_info);
  };

  this.bindFormDomNodes = function(ui_form_info) {
    ui_form_info.ui_nodes.input_field = document.getElementById(ui_form_info.id_set.input); 
    ui_form_info.ui_nodes.display_unit = document.getElementById(ui_form_info.id_set.display_unit); 
    ui_form_info.ui_nodes.display = document.getElementById(ui_form_info.id_set.display); 
    ui_form_info.ui_nodes.valid_icon = document.getElementById(ui_form_info.id_set.valid_icon);
    ui_form_info.ui_nodes.invalid_icon = document.getElementById(ui_form_info.id_set.invalid_icon);
  };

  /**
   * hideInputValidationIcon()
   * - hide the validation icon
   */
  this.hideInputValidationIcon = function(validation_input_icon_dom) {
    validation_input_icon_dom.setAttribute(HIDDEN_VALIDATION_ICON_ATTRIBUTE, '');  
  };

  /**
   * showInputValidationIcon()
   * - show the validation icon
   */
  this.showInputValidationIcon = function(validation_input_icon_dom) {
    validation_input_icon_dom.removeAttribute(HIDDEN_VALIDATION_ICON_ATTRIBUTE); 
  };

  /**
   * updateUiInputCardWithValidInput()
   * - update the ui of the specified input card to reflect valid input
   */
  this.updateUiInputCardWithValidInput = function(ui_form_info) {
    hideInputValidationIcon(ui_form_info.ui_nodes.invalid_icon);   
    showInputValidationIcon(ui_form_info.ui_nodes.valid_icon);   
  };
 
  /**
   * updateUiInputCardWithInvalidInput()
   * - update the ui of the specified input card to reflect invalid input
   */
  this.updateUiInputCardWithInvalidInput = function(ui_form_info) {
    hideInputValidationIcon(ui_form_info.ui_nodes.valid_icon);   
    showInputValidationIcon(ui_form_info.ui_nodes.invalid_icon);   
  };

  /**
   * Initialize all input forms in the 'New Experiment' page.
   * Bind DOM nodes and attach event listeners.
   */
  this.init = function() {
    /**
     * Configure 'Scopes Count' input field
     */
    // Bind DOM nodes
    bindFormDomNodes(scopesCountUiFormInfo);

    // Bind event listeners
    scopesCountUiFormInfo.ui_nodes.input_field.onchange = function() {
      updateDisplay(this.immediateValue, scopesCountUiFormInfo);
    };

    // Initialize scopes count input card ui
    updateUiInputCardWithValidInput(scopesCountUiFormInfo); 
    setInputValue(scopesCountUiFormInfo, 9);

    /**
     * Configure 'Duration' input field
     */
    // Bind DOM nodes
    bindFormDomNodes(durationUiFormInfo);

    // Bind event listeners
    durationUiFormInfo.ui_nodes.input_field.onchange = function() {
      updateDisplay(this.immediateValue, durationUiFormInfo);
    };

    // Initialize duration input card ui
    updateUiInputCardWithInvalidInput(durationUiFormInfo); 
    setInputValue(durationUiFormInfo, 9);
  };

  return {
    init: init
  };
})();

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

var Utils = (function() {
 
  this.hasClass = function(expected_class, node_class) {
    var class_idx = node_class.indexOf(expected_class);
    
    if (class_idx == -1) {
      return;
    }

    return (class_idx == 0 || node_class.charAt(class_idx - 1) == ' ')
      && (expected_class.length + class_idx == node_class.length
        || node_class.charAt(expected_class.length + class_idx) == ' ');
  };

  return {
    hasClass: hasClass
  };
})();

function Calendar(
  template_store,
  calendar_id,
  disallowed_week_days,
  irregular_disallowed_days,
  forward_month_limit,
  min_num_days_in_advance
) {

  /**
   * Date style tokens
   */
  var SHORT_DOW_ABBREVIATION_TOKEN = '.';
  var DOM_DELIMITER = ',';

  /**
   * Template name constants
   */
  var TEMPLATE_ID = '#calendar-template';

  /**
   * Html class names
   */
  var DATE_CLASS = 'date';
  var UNSELECTABLE_DATE_CLASS = 'unselectable-date';
  var SELECTABLE_DATE_CLASS = 'selectable-date';
  var DATE_LABEL_CLASS = 'date-label';
  var WEEK_CLASS = 'week';

  /**
   * Html attribute names
   */
  var SELECTED_DATE_ATTR = 'selected-date';
  var DISABLED_MONTH_NAV_ATTR = 'disabled';
  var HIDDEN_ATTR = 'hidden';
  var CLOSED_ATTR = 'closed';

  /**
   * Class constants
   */
  var JS_YEAR_OFFSET = 1900;
  var JS_DATE_LOCALE = 'en-us';

  var SHORT_DAY_OF_THE_WEEK_NAMES = [
    'Sun',
    'Mon',
    'Tue',
    'Wed',
    'Thu',
    'Fri',
    'Sat'
  ];

  var LONG_DAY_OF_THE_WEEK_NAMES = [
    'Sunday',
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday'
  ];
  
  var LONG_MONTH_NAMES = [
    'January',
    'February',
    'March',
    'April',
    'May',
    'June',
    'July',
    'August',
    'September',
    'October',
    'November',
    'December'
  ];

  var SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  // Js utility pointers
  var that = this;
  var jsDate = null;

  // Calendar State
  var templateStore = template_store;
  var minNumDaysInAdvance = min_num_days_in_advance;
  var disallowedWeekDays = disallowed_week_days;
  var irregularDisallowedDays = irregular_disallowed_days;
  var isEnabled = true;
  var isVisible = false;
  
  var monthDisplacement = 0;
  var maxMonthDisplacement = forward_month_limit;

  /**
   * Stores information for the current date
   */
  var currentDateObj = {
    date: null,
    month: null,
    year: null
  };

  /**
   * Stores information for the current *selected* date
   */
  var selectedDateObj = {
    date: null,
    month: null,
    year: null,
    selectedDateNode: null
  };

  /**
   * Stores information for the month that is currently displayed
   */
  var calendarMonthObj = {
    month: null,
    year: null,
    startingDayOfTheWeek: null
  };

  /**
   * Dom node info
   */
  // Calendar root
  var calendarRootNodeInfo = {
    id: calendar_id,
    node: null
  };

  // Selected display date
  // var selectedDowLabelNodeInfo = {
  //   className: 'selected-dow-label',
  //   node: null
  // };

  var selectedMonthLabelNodeInfo = {
    className: 'selected-month-label',
    node: null
  };
  
  var selectedDomLabelNodeInfo = {
    className: 'selected-dom-label',
    node: null
  };

  var selectedYearLabelNodeInfo = {
    className: 'selected-year-label',
    node: null
  };

  // Month nav node info
  var monthNavDisplayNodeInfo = {
    className: 'month-label',
    node: null
  };

  var decrementMonthNavNodeInfo = {
    className: 'decrement-month-container',
    node: null
  };
  
  var incrementMonthNavNodeInfo = {
    className: 'increment-month-container',
    node: null
  };
  
  // Selectable dates node info
  var selectableDaysContainerNodeInfo = {
    className: 'selectable-dates-container',
    node: null
  };

  var selectedDateDisplayContainer = {
    className: 'selected-date-display-container',
    node: null
  };

  var calendarMainContainerNodeInfo = {
    className: 'calendar-main-container',
    node: null
  };

  /**
   * Private functions
   */
  /**
   * fetchClassBoundDomNode()
   * - fetch the dom node indicated by the provided class-name
   * @param Object node_info: datastructure for the node (see above for example)
   */
  function fetchClassBoundDomNode(node_info) {
    elements = calendarRootNodeInfo.node.getElementsByClassName(node_info.className);
    console.assert(elements.length == 1);
    node_info.node = elements[0];
  };

  /**
   * initInternalCalendarNodes()
   * - initialize dom node pointers
   * - binds event listeners
   */
  function initInternalCalendarNodes() {
    // Bind all nodes and init their event listeners
    // Selected display date nodes
    fetchClassBoundDomNode(selectedYearLabelNodeInfo);
    // fetchClassBoundDomNode(selectedDowLabelNodeInfo);
    fetchClassBoundDomNode(selectedDomLabelNodeInfo);
    fetchClassBoundDomNode(selectedMonthLabelNodeInfo);

    fetchClassBoundDomNode(calendarMainContainerNodeInfo);
    fetchClassBoundDomNode(selectedDateDisplayContainer);

    selectedDateDisplayContainer.node.onclick = function(event) {
      if (isVisible) {
        hideCalendar();
      } else {
        showCalendar();
      }
    };

    // Month nav nodes
    fetchClassBoundDomNode(monthNavDisplayNodeInfo);
    fetchClassBoundDomNode(decrementMonthNavNodeInfo);
    fetchClassBoundDomNode(incrementMonthNavNodeInfo);
    
    // Month navigation button event listeners
    decrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(false); 
    };
    
    incrementMonthNavNodeInfo.node.onclick = function() {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }
      shiftMonth(true); 
    };

    // Selectable dates node info
    fetchClassBoundDomNode(selectableDaysContainerNodeInfo);

    // Selectable dates event listener
    selectableDaysContainerNodeInfo.node.onclick = function(event) {
      // Kill event if client asks for it
      if (!isEnabled) {
        return;
      }

      // Search event propagation list to find selectable-date node
      var date = null;
      for (var i = 0; i < event.path.length; ++i) {
        if (event.path[i].className != undefined && Utils.hasClass(SELECTABLE_DATE_CLASS, event.path[i].className)) {
          date = event.path[i];
          break;
        } 
      }

      // Kill event if a selectable-date wasn't clicked
      if (date == null) {
        return;
      }

      // Kill event here b/c this date is already selected!
      if (date.hasAttribute(SELECTED_DATE_ATTR)) {
        return;
      }

      // Extract the numerical date
      console.assert(date.childNodes.length == 1);
      var label = date.childNodes[0];
      console.assert(Utils.hasClass(DATE_LABEL_CLASS, label.className));

      var date_idx = parseInt(label.innerHTML);

      // Clear current selected date
      if (selectedDateObj.selectedDateNode != null) {
        selectedDateObj.selectedDateNode.removeAttribute(SELECTED_DATE_ATTR);
      } 

      // Render current selected date
      date.setAttribute(SELECTED_DATE_ATTR, '');
      selectedDateObj.selectedDateNode = date;
      selectedDateObj.date = date_idx;

      // Update selected date top-banner display
      updateSelectedDowDisplay(date_idx);
      updateSelectedMonthDisplay(calendarMonthObj.month);

      // Hide calendar body
      hideCalendar();
    };

    // Hide calendar if user clicks off the screen
    document.getElementsByTagName('html')[0].addEventListener('click', function(event) {
      for (var node_id in event.path) {
        var node = event.path[node_id];
        // User clicked on the screen, so don't hide!
        if (node.id == calendarRootNodeInfo.node.id) {
          return;
        }
      }

      // User clicked off the calendar, so hide it!
      hideCalendar();
    });
  };

  function hideCalendar() {
    isVisible = false;  
    calendarMainContainerNodeInfo.node.setAttribute(HIDDEN_ATTR, ''); 
    selectedDateDisplayContainer.node.setAttribute(CLOSED_ATTR, '');
  };

  function showCalendar() {
    isVisible = true; 
    calendarMainContainerNodeInfo.node.removeAttribute(HIDDEN_ATTR); 
    selectedDateDisplayContainer.node.removeAttribute(CLOSED_ATTR);
  };

  /**
   * shiftMonth()
   * - increment/decrement month and update ui
   * @param: bool is_increment: true iff incrementing month
   */
  function shiftMonth(is_increment) {
    // Kill event if increments month past forward limit
    if (is_increment && monthDisplacement == maxMonthDisplacement) {
      return;
    }

    // Kill event if decrements month past current one
    if (!is_increment && monthDisplacement == 0) {
      return;
    }

    if (is_increment) {
      ++monthDisplacement; 
      if (monthDisplacement == maxMonthDisplacement) {
        // Update forward month-nav-arrow to signal that it can't go forward anymore 
        incrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');  
        decrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    } else {
      --monthDisplacement;
      if (monthDisplacement == 0) {
        // Update backward month-nav-arrow to signal that it can't go backward anymore 
        decrementMonthNavNodeInfo.node.setAttribute(DISABLED_MONTH_NAV_ATTR, '');
        incrementMonthNavNodeInfo.node.removeAttribute(DISABLED_MONTH_NAV_ATTR);
      }
    }

    // Render new grid for month
    var month_offset = monthDisplacement + selectedDateObj.month;
    var year_offset = Math.floor(month_offset / 12);
    var next_year = year_offset + selectedDateObj.year;
    var next_month = month_offset % 12;

    // Update internal calendar state
    calendarMonthObj.month = next_month;
    calendarMonthObj.year = next_year;
    var starting_day_of_week_obj = new Date(next_year, next_month, 1);
    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();

    updateMonthDisplayGrid(next_month, next_year);
    updateCurrentMonthDisplay(next_month);
  };

  function initDate() {
    // Capture today's date and initialize calendar state
    var current_date_js_obj = new Date(); 
    
    // Adjust first available day with min-num-days-in-advance offset
    current_date_js_obj = new Date(
      current_date_js_obj.getUTCFullYear(),
      current_date_js_obj.getMonth(),
      current_date_js_obj.getDate() + minNumDaysInAdvance
    );

    // Set current date
    currentDateObj.date = current_date_js_obj.getUTCDate();
    currentDateObj.month = current_date_js_obj.getUTCMonth();
    currentDateObj.year = current_date_js_obj.getUTCFullYear();
   
    // Initialize selected date to current date
    selectedDateObj.date = current_date_js_obj.getUTCDate();
    selectedDateObj.month = current_date_js_obj.getUTCMonth();
    selectedDateObj.year = current_date_js_obj.getUTCFullYear();

    // Initialize calendar grid state to current month
    calendarMonthObj.month = selectedDateObj.month;
    calendarMonthObj.year = selectedDateObj.year;

    // Determine starting day of the week for the selected date
    var starting_day_of_week_obj = new Date(
      calendarMonthObj.year,    
      calendarMonthObj.month,    
      1
    );

    calendarMonthObj.startingDayOfTheWeek = starting_day_of_week_obj.getDay();
  };

  /**
   * updateSelectedDowDisplay()
   * - update the selected-date banner
   * @param Obj selected_date: {int date, int month, int year}
   */
  function updateSelectedDowDisplay(date) {
    // var date_label = computeSelectedDowLabel(date);
    // selectedDowLabelNodeInfo.node.innerHTML = date_label;
    selectedDomLabelNodeInfo.node.innerHTML = date + DOM_DELIMITER;
  };

  function updateSelectedMonthDisplay(month) {
    var month_label = computeSelectedMonthLabel(month);
    selectedMonthLabelNodeInfo.node.innerHTML = month_label;
  };

  function updateCurrentMonthDisplay(month) {
    var month_label = computeCurrentSelectedMonthLabel(month);
    monthNavDisplayNodeInfo.node.innerHTML = month_label; 
  };

  function updateSelectedYearDisplayLabel(year) {
    var year_label = computeSelectedYearLabel(year); 
    selectedYearLabelNodeInfo.node.innerHTML = year_label;
  };

  function generateDateNode() {
    var date_node = document.createElement('div');
    date_node.className = DATE_CLASS;
    return date_node;
  };

  function generateBlankDateNode() {
    return generateDateNode();
  };

  /**
   * generateDateLabelNode()
   * - dynamically generate html node for displaying an individual
   *   date in the calendar
   * @param int date: day of the month 
   */
  function generateDateLabelNode(date) {
    var date_label_node = document.createElement('div');
    var label = document.createElement('span');
    label.className = DATE_LABEL_CLASS;
    label.innerHTML = date;
    date_label_node.appendChild(label);
    return date_label_node;
  };

  /**
   * generateSelectableDateNode()
   * - dynamically generates html node representing date
   *   within this month that can be selected.
   */
  function generateSelectableDateNode(date) {
    var selectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = SELECTABLE_DATE_CLASS;
    selectable_date_node.appendChild(date_label_node);
    return selectable_date_node; 
  };

  /**
   * generateUnselectableDateNode()
   * - dynamically generates html node representing
   *   date wthin this month that can't be selected, 
   *   e.g. date has already passed or date is already
   *   booked
   */
  function generateUnselectableDateNode(date) {
    var unselectable_date_node = generateDateNode();
    var date_label_node = generateDateLabelNode(date);
    date_label_node.className = UNSELECTABLE_DATE_CLASS;
    unselectable_date_node.appendChild(date_label_node);
    return unselectable_date_node; 
  };

  /**
   * generateWeekNode()
   * - dynamically generate the node for 1 row in the calendar
   */
  function generateWeekNode() {
    var week_node = document.createElement('div');
    week_node.className = WEEK_CLASS;
    return week_node;
  };

  /**
   * updateMonthDisplayGrid()
   * - dynamically generate date cells for this month
   * @param int month: [0, 11] indicating month index
   * @param int year: any year
   */
  function updateMonthDisplayGrid(month, year) {
    // Clear existing week-nodes within the calendar grid
    while (selectableDaysContainerNodeInfo.node.hasChildNodes()) {
      selectableDaysContainerNodeInfo.node.removeChild(selectableDaysContainerNodeInfo.node.lastChild);
    }

    // Get starting day-of-week idx
    var new_date = new Date(year, month);
    var starting_day_idx = new_date.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0); // hacky :/
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate dynamic html nodes for days in last week of previous month that appear
    // in first week of this month, e.g. last few days
    var current_week = generateWeekNode();
    selectableDaysContainerNodeInfo.node.appendChild(current_week);

    for (var i = 0; i < starting_day_idx; ++i) {
      var blank_node = generateBlankDateNode();
      current_week.appendChild(blank_node);
    }
    
    // Generate dynamic html nodes for displaying selectable days in month
    for (var i = 1; i <= num_days_in_month; ++i) { // fewer ops with these loop conditions
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = generateWeekNode();
        selectableDaysContainerNodeInfo.node.appendChild(current_week);
      }

      // Create date node: date node is 'unselectable' iff it is on either
      // of the 'disallowed' lists or if it occurs before the specified
      // min-number-days-in-advance threshold
      var date_node = (disallowedWeekDays.has(current_week.childNodes.length)) || 
          (month == currentDateObj.month && i < currentDateObj.date)
        ? generateUnselectableDateNode(i)
        : generateSelectableDateNode(i);

      current_week.appendChild(date_node);
    }
  }

  /**
   * initDisplay()
   * - initialize calendar display
   * - generate and bind dynamic nodes
   * @pre-condition: 'selectedDateObj' must be initialized to current date
   */
  function initDisplay() {
    // Render grid of dates
    updateMonthDisplayGrid(selectedDateObj.month, selectedDateObj.year);

    // Render banner date label for current date
    updateSelectedDowDisplay(selectedDateObj.date);

    // Render banner month label for current date
    updateSelectedMonthDisplay(selectedDateObj.month);

    // Render banner year label for current date 
    updateSelectedYearDisplayLabel(selectedDateObj.year);

    // Render calendar month label for grid
    updateCurrentMonthDisplay(selectedDateObj.month);

    // Render or hide main calendar content on startup
    if (isVisible) {
      showCalendar();
    } else {
      hideCalendar();
    }
  };

  /**
   * computeCurrentSelectedMonthLabel()
   * - return the month label for the calendar title itself (not the banner)
   * @param int month: [0-11] month index
   */
  function computeCurrentSelectedMonthLabel(month) {
    return LONG_MONTH_NAMES[month]; 
  };

  /**
   * computeSelectedDowLabel()
   * - return date label: '<day of the week>, <numerical day of the month>'
   * @param int date: numerical day of the month
   */
  function computeSelectedDowLabel(date) {
    var day_of_week_idx = (date + calendarMonthObj.startingDayOfTheWeek - 1) % 7;
    return SHORT_DAY_OF_THE_WEEK_NAMES[day_of_week_idx] + SHORT_DOW_ABBREVIATION_TOKEN;
  };

  /**
   * computeSelectedMonthLabel()
   * - return short month label for top-banner displaying selected date
   * @param int month_idx: [0-11] month index of selected month
   */
  function computeSelectedMonthLabel(month_idx) {
    return SHORT_MONTH_NAMES[parseInt(month_idx)]; 
  };

  /**
   * computeSelectedYearLabel()
   * - return year label for top-banner displaying selected date
   * @param int year: year index (UTC)
   */
  function computeSelectedYearLabel(year) {
    // Must have valid date
    return year;
  };

  /**
   * setDate()
   * - set date state and update ui
   * @pre-condition: params must correspond to valid date
   * @param int day: day of the month index
   * @param int month: month index
   * @param int year: year index
   */
  function setDate(day, month, year) {
    // TODO: write api for setting date externally 
  };

  /**
   * synthesizeCalendarTemplate()
   * - copy calendar template and insert into main dom tree
   * @pre-condition: 'calendarRootNodeInfo' must be initialized
   */
  function synthesizeCalendarTemplate() {
    // Bind calendar dom template 
    var calendar_template = templateStore.import.querySelector(TEMPLATE_ID);
    var calendar_clone = document.importNode(calendar_template.content, true);
    calendarRootNodeInfo.node.appendChild(calendar_clone);
  };

  /**
   * Privileged functions
   */
  /**
   * init()
   * - bind all nodes, initialize state and ui
   * - bind event listeners
   */
  this.init = function() {
    // Initialize top-level calendar node (we're going to copy the template into this!)
    calendarRootNodeInfo.node = document.getElementById(calendarRootNodeInfo.id);

    // Copy the template and insert into root node
    synthesizeCalendarTemplate();

    // Initialize dom nodes internal to the calendar object
    initInternalCalendarNodes();

    // Cache today's date
    initDate();

    // Load ui
    initDisplay();
  };

  /**
   * disable()
   * - disable event listeners and render 'disabled' ui
   */
  this.disable = function() {
    isEnabled = false;
  };

  /**
   * enable()
   * - enable event listeners and render 'enabled' ui
   */
  this.enable = function() {
    isEnabled = true;
  };

  this.getSelectedDate = function() {
    return {
      year: selectedDateObj.year,
      month: selectedDateObj.month,
      date: selectedDateObj.date
    };
  };
};
