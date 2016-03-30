var DatePickerView = function(
  template_store,
  parent_node
) {

  /**
   * Template ids
   */
  var MAIN_TEMPLATE_ID = 'calendar-template';
  var WEEK_TEMPLATE_ID = 'date-picker-week-template';
  var DATE_TEMPLATE_ID = 'date-template';

  /**
   * Class names
   */
  var ROOT_WRAPPER_CLASS = 'calendar-wrapper';
  var WEEK_WRAPPER_CLASS = 'week-wrapper';
  var DATE_WRAPPER_CLASS = 'date-wrapper';
  var DATE_LABEL_CLASS = 'date-label';

  /**
   * Attribute names
   */
  var UNSELECTABLE_DATE_ATTR = 'unselectable-date';

  /**
   * Private state
   */
  var datePickerModel = null;

  var templateStore = template_store;
  var parentNode = parent_node;
  var datePickerRootNode = null;

  /**
   * Dom nodes
   */
  // Top banner elements
  var selectedDateDisplayContainerNodeInfo = {
    className: 'selected-date-display-container',
    node: null
  };

  var selectedMonthLabelNodeInfo = {
    className: 'selected-month-label',
    node: null
  };
  
  var selectedDateLabelNodeInfo = {
    className: 'selected-dom-label',
    node: null
  };

  var selectedYearLabelNodeInfo = {
    className: 'selected-year-label',
    node: null
  };

  // Month nav node info (current month & left/right month controls)
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
  var weeksContainerNodeInfo = {
    className: 'weeks-container',
    node: null
  };

  var calendarMainContainerNodeInfo = {
    className: 'calendar-main-container',
    node: null
  };

  /**
   * Private functions
   */
  var bindNodes = function() {
    // Top banner nodes
    Utils.bindNodeInfo(parentNode, selectedDateDisplayContainer);
    Utils.bindNodeInfo(parentNode, selectedMonthLabelNodeInfo);
    Utils.bindNodeInfo(parentNode, selectedDomLabelNodeInfo);
    Utils.bindNodeInfo(parentNode, selectedYearLabelNodeInfo);

    // Month nav/display
    Utils.bindNodeInfo(parentNode, monthNavDisplayNodeInfo);
    Utils.bindNodeInfo(parentNode, decrementMonthNavNodeInfo);
    Utils.bindNodeInfo(parentNode, incrementMonthNavNodeInfo);

    // Selectable dates
    Utils.bindNodeInfo(parentNode, weeksContainerNodeInfo);
    Utils.bindNodeInfo(parentNode, calendarMainContainerNodeInfo);
  };

  var setSelectedDate = function(selected_date) {
    selectedDateLabelNodeInfo.node.innerHTML = selected_date; 
  };

  var setSelectedMonth = function(selected_month) {
    selectedMonthLabelNodeInfo.node.innerHTML = selected_month;
  };

  var setSelectedYear = function(selected_year) {
    selectedYearLabelNodeInfo.node.innerHTML = selected_year;
  };

  var setViewedMonth = function(month, year) {
    refreshCalendar(month, year);
  }

  var refreshCalendar = function(month, year) {
    // Remove previous date nodes
    Utils.removeChildren(weeksContainerNodeInfo.node); 

    // Render calendar for specified month/year
    // Get starting day-of-week idx
    var starting_day_obj = new Date(year, month);  
    var starting_day_idx = starting_day_obj.getUTCDay();

    // Get number of days in month
    var num_days_in_month_obj = new Date(year, month + 1, 0);
    var num_days_in_month = num_days_in_month_obj.getDate();

    // Generate blank date nodes for days in final week of previous
    // month that appear in the first week of this calendar month
    var current_week = genWeekNode();

    for (var i = 0; i < starting_day_idx; ++i) {
      var date = makeDateNode(current_week);
      date.setAttribute(UNSELECTABLE_DATE_ATTR, '');
    }

    // Determine which date is the first selectable one
    var first_selectable_date = new Date();
    first_selectable_date.setDate(
      first_selectable_date.getDate() + datePickerModel.getMinAdvanceDayCount()
    );

    // Generate nodes for displaying selectable days
    for (var i = 1; i <= num_days_in_month; ++i) {
      // Insert rows for calendar weeks
      if (current_week.childNodes.length == 7) {
        current_week = makeWeekNode();
      }

      // Initialize date and insert into week
      var date = makeDateNode(current_week);

      // Create date node. Node is 'unselectable' iff it is...
      // 1. On either of the 'disallowed' lists *OR*
      // 2. It falls too close to the current date 
      if (Utils.compareDates(first_selectable_date, date) < 0 || isInvalidDate(date)) {
        date.setAttribute(UNSELECTABLE_DATE_ATTR, '');     
      }
    }

  };

  var isInvalidDate = function(date) {
    // Check if this date's 'day of the week' is marked invalid
    if (datePickerModel.getInvalidDaysOfTheWeek().includes(date.getDay())) {
      return true;
    }

    // Check if this date is one of the irregular dates marked invalid
    var invalid_dates = datePickerModel.getInvalidDates();
    for (var i = 0; i < invalid_dates.length; ++i) {
      var invalid_date = invalid_dates[i];
      if (Utils.compareDates(date, invalid_date) == 0) {
        return true;
      }
    }

    return false;
  };

  var genWeekNode = function() {
    return Utils.synthesizeTemplateIntoList(
      templateStore,
      WEEK_TEMPLATE_ID,
      weeksContainerNodeInfo.node,
      WEEK_WRAPPER_CLASS
    );
  };

  var setMinAdvanceDayCount = function(count) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setMaxAdvanceMonthCount = function(count) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setInvalidDaysOfTheWeek = function(invalid_days) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var setInvalidDates = function(dates) {
    refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear()
    ); 
  };

  var bindModel = function(date_picker_model) {
    datePickerModel = date_picker_model;
    datePickerModel 
      .bindSelectedDate(setSelectedDate)
      .bindSelectedMonth(setSelectedMonth)
      .bindSelectedYear(setSelectedYear)
      .bindViewedMonth(setViewedMonth)
      .bindMinAdvanceDayCount(setMinAdvanceDayCount)
      .bindMaxAdvanceMonthCount(setMaxAdvanceMonthCount)
      .bindInvalidDaysOfTheWeek(setInvalidDaysOfTheWeek)
      .bindInvalidDates(setInvalidDates);
  };

  /**
   * Privileged functions
   */
  this.init = function(date_picker_model) {
    // Synthesize template into document
    datePickerRootNode = Utils.synthesizeTemplate(
      templateStore,
      MAIN_TEMPLATE_ID,
      parentNode,
      ROOT_WRAPPER_CLASS
    ); 

    // Bind nodes
    bindNodes();

    // Bind model and init ui
    bindModel(date_picker_model);
  };
};
