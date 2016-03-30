var DatePickerModel = function() {

  // Privat state
  this.selectedDate = null;
  this.selectedMonth = null;
  this.selectedYear = null;
  this.viewedMonth = null;
  this.viewedYear = null;

  this.minAdvanceDayCount = null;
  this.maxAdvanceMonthCount = null;
  this.invalidDaysOfTheWeek = [];
  this.invalidDates = [];

  // Callbacks
  this.selectedDateCallbacks = []; 
  this.selectedMonthCallbacks = []; 
  this.selectedYearCallbacks = []; 
  this.viewedMonthCallbacks = []; 

  this.minAdvanceDayCountCallbacks = [];
  this.maxAdvanceMonthCountCallbacks = [];
  this.invalidDaysOfTheWeekCallbacks = [];
  this.invalidDatesCallbacks = [];
};

// Setters
DatePickerModel.prototype.setSelectedDate = function(selected_date) {
  this.selectedDate = selected_date;
  this.selectedDateCallbacks.forEach(function(callback) {
    callback(selectedDate);
  });
  return this;
};

DatePickerModel.prototype.setSelectedMonth = function(selected_month) {
  this.selectedMonth = selected_month;
  this.selectedMonthCallbacks.forEach(function(callback) {
    callback(selectedMonth);
  });
  return this;
};

DatePickerModel.prototype.setSelectedYear = function(selected_year) {
  this.selectedYear = selected_year;
  this.selectedYearCallbacks.forEach(function(callback) {
    callback(selectedYear);
  });
  return this;
};

DatePickerModel.prototype.setViewedMonthAndYear = function(viewed_month, viewed_year) {
  this.viewedMonth = viewed_month;
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(viewedMonth, viewedYear);
  });
  return this;
};

DatePickerModel.prototype.setViewedMonth = function(viewed_month) {
  this.viewedMonth = viewed_month;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(viewedMonth, viewedYear);
  });
  return this;
};

DatePickerModel.prototype.setViewedYear = function(viewed_year) {
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(viewedMonth, viewedYear);
  });
  return this;
};

DatePickerModel.prototype.setMinAdvanceDayCount = function(count) {
  this.minAdvanceDayCount = count;
  this.minAdvanceDayCountCallbacks.forEach(function(callback) {
    callback(minAdvanceDayCount);
  });
  return this;
};

DatePickerModel.prototype.setMaxAdvanceDayCount = function(count) {
  this.maxAdvanceDayCount = count;
  this.maxAdvanceDayCountCallbacks.forEach(function(callback) {
    callback(maxAdvanceDayCount);
  });
  return this;
};

DatePickerModel.prototype.setInvalidDaysOfTheWeek = function(invalid_days) {
  this.invalidDaysOfTheWeek = invalid_days;
  this.invalidDaysOfTheWeekCallbacks.forEach(function(callback) {
    callback(invalidDaysOfTheWeek);
  });
  return this;
};

DatePickerModel.prototype.setInvalidDates = function(invalid_dates) {
  this.invalidDates = invalid_dates;
  this.invalidDatesCallbacks.forEach(function(callback) {
    callback(invalidDates);
  });
  return this;
};

// Callback listeners
DatePickerModel.prototype.bindSelectedDate = function(callback) {
  this.selectedDateCallbacks.push(callback);
  callback(this.selectedDate);
  return this;
};

DatePickerModel.prototype.bindSelectedMonth = function(callback) {
  this.selectedMonthCallbacks.push(callback);
  callback(this.selectedMonth);
  return this;
};

DatePickerModel.prototype.bindSelectedYear = function(callback) {
  this.selectedYearCallbacks.push(callback);
  callback(this.selectedYear);
  return this;
};

DatePickerModel.prototype.bindViewedMonth = function(callback) {
  this.viewedMonthCallbacks.push(callback);
  callback(this.viewedMonth);
  return this;
};

DatePickerModel.prototype.bindViewedYear = function(callback) {
  this.viewedYearCallbacks.push(callback);
  callback(this.viewedYear);
  return this;
};

DatePickerModel.prototype.bindMinAdvanceDayCount = function(callback) {
  this.minAdvanceDayCountCallbacks.push(callback);
  callback(this.minAdvanceDayCount);
  return this;
};

DatePickerModel.prototype.bindMaxAdvanceDayCount = function(callback) {
  this.maxAdvanceDayCountCallbacks.push(callback);
  callback(this.maxAdvanceDayCount);
  return this;
};

DatePickerModel.prototype.bindInvalidDaysOfTheWeek = function(callback) {
  this.invalidDaysOfTheWeekCallbacks.push(callback);
  callback(this.invalidDaysOfTheWeek);
  return this;
};

DatePickerModel.prototype.bindInvalidDates = function(callback) {
  this.invalidDatesCallbacks.push(callback);
  callback(this.invalidDates);
  return this;
};

// Getters
DatePickerModel.prototype.getSelectedDate = function() {
  return this.selectedDate;
};

DatePickerModel.prototype.getMinAdvanceDayCount = function() {
  return this.minAdvanceDayCount;
};

DatePickerModel.prototype.getMaxAdvanceMonthCount = function() {
  return this.maxAdvanceMonthCount;
};

DatePickerModel.prototype.getInvalidDaysOfTheWeek = function() {
  return this.invalidDaysOfTheWeek;
};

DatePickerModel.prototype.getInvalidDates = function() {
  return this.invalidDates;
};
