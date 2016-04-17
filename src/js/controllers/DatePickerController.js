var DatePickerController = function() {

  /**
   * Private state
   */
  var currentDate = new Date();
  var datePickerView = null;
  var datePickerModel = null;

  /**
   * Private functions
   */
  var handleDateSelection = function(view, date) {
    // Exit early if we're no longer using this view
    if (view != datePickerView) {
      return;
    }

    // Handle date selection
    datePickerModel
      .setSelectedDate(date)
      .setSelectedMonth(datePickerModel.getViewedMonth())
      .setSelectedYear(datePickerModel.getViewedYear());
  };

  var handleMonthNavigation = function(view, is_decrement) {
    if (view != datePickerView) {
      return; 
    }

    var month_displacement = is_decrement
      ? -1
      : 1;

    // Check current date, fix date if necessary
    var current_date = new Date();
    if (current_date.getUTCFullYear() != currentDate.getUTCFullYear() ||
        current_date.getMonth() != currentDate.getMonth() ||
        current_date.getDate() != currentDate.getDate()) {
      currentDate = current_date;    
    }

    // Adjust year and reset month if we extend beyond calendar bounds
    var current_month = datePickerModel.getViewedMonth();
    var current_year = datePickerModel.getViewedYear();

    var next_month = current_month + month_displacement;
    var next_year = current_year;

    switch (next_month) {
      case -1:
        next_month = 11;
        --next_year;
        break;
      case 12:
        next_month = 0;
        ++next_year;
        break;
    }

    // Exit early if invalid month displacement
    if (!isValidMonth(next_month, next_year)) {
      return;
    }

    // Update viewed month/date in model
    datePickerModel.setViewedMonthAndYear(next_month, next_year);
    
    // Check if previous month is illegal. If so, disable decrement month
    // navigation arrow
    var previous_month = new Date(next_year, next_month - 1);
    datePickerView.toggleMonthDecrementNavButtonActiveState(
      isValidMonth(previous_month.getMonth(), previous_month.getFullYear())    
    );

    // Check if next month is illegal. If so, disable increment month
    // navigation arrow
    var next_month = new Date(next_year, next_month + 1);
    datePickerView.toggleMonthIncrementNavButtonActiveState(
      isValidMonth(next_month.getMonth(), next_month.getFullYear())   
    );

    return this;
  };

  var isValidMonth = function(month, year) {
    var start_date = new Date(); 
    start_date.setDate(
      start_date.getDate() + datePickerModel.getMinAdvanceDayCount()
    );

    // Calculate month-displacement between new-date and start-date
    var month_displacement = 12 * (year - start_date.getFullYear()) + month - start_date.getMonth();

    return month_displacement > 0 &&
      month_displacement <= datePickerModel.getMaxAdvanceMonthCount();
  };

  // TODO these...
  var handleMinAdvanceDayCountChange = function(min_advance_day_count) {
  };

  var handleMaxAdvanceMonthCountChange = function(max_advance_month_count) {
  };

  var handleInvalidWeekDaysChange = function(invalid_week_days) {};

  var handleInvalidDatesChange = function(invalid_dates) {};

  var handleCalendarRefresh = function() {
    datePickerView.refreshCalendar(
      datePickerModel.getViewedMonth(),
      datePickerModel.getViewedYear(),
      datePickerModel.getMinAdvanceDayCount(),
      datePickerModel.getInvalidDaysOfTheWeek(),
      datePickerModel.getInvalidDates()
    ); 
  };

  /**
   * Privileged functions
   */
  this.init = function(view, model) {
    datePickerView = view;
    datePickerModel = model;

    // Configure view --> model data pathway
    datePickerView
      .bindDateSelection(handleDateSelection)
      .bindMonthNavigation(handleMonthNavigation);

    // Configure model --> view data pathway
    datePickerModel
      .bindSelectedDate(datePickerView.setSelectedDate)
      .bindSelectedMonth(datePickerView.setSelectedMonth)
      .bindSelectedYear(datePickerView.setSelectedYear)
      .bindViewedMonth(handleCalendarRefresh)
      .bindMinAdvanceDayCount(handleCalendarRefresh)
      .bindMaxAdvanceMonthCount(handleCalendarRefresh)
      .bindInvalidDaysOfTheWeek(handleCalendarRefresh)
      .bindInvalidDates(handleCalendarRefresh);
  };
};
