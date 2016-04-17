var DatePickerModel = function() {

  // Private state
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
    callback(this.selectedDate);
  }, this);
  return this;
};

DatePickerModel.prototype.setSelectedMonth = function(selected_month) {
  this.selectedMonth = selected_month;
  this.selectedMonthCallbacks.forEach(function(callback) {
    callback(this.selectedMonth);
  }, this);
  return this;
};

DatePickerModel.prototype.setSelectedYear = function(selected_year) {
  this.selectedYear = selected_year;
  this.selectedYearCallbacks.forEach(function(callback) {
    callback(this.selectedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedMonthAndYear = function(viewed_month, viewed_year) {
  this.viewedMonth = viewed_month;
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedMonth = function(viewed_month) {
  this.viewedMonth = viewed_month;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setViewedYear = function(viewed_year) {
  this.viewedYear = viewed_year;
  this.viewedMonthCallbacks.forEach(function(callback) {
    callback(this.viewedMonth, this.viewedYear);
  }, this);
  return this;
};

DatePickerModel.prototype.setMinAdvanceDayCount = function(count) {
  this.minAdvanceDayCount = count;
  this.minAdvanceDayCountCallbacks.forEach(function(callback) {
    callback(this.minAdvanceDayCount);
  }, this);
  return this;
};

DatePickerModel.prototype.setMaxAdvanceMonthCount = function(count) {
  this.maxAdvanceMonthCount = count;
  this.maxAdvanceMonthCountCallbacks.forEach(function(callback) {
    callback(this.maxAdvanceMonthCount);
  }, this);
  return this;
};

DatePickerModel.prototype.setInvalidDaysOfTheWeek = function(invalid_days) {
  this.invalidDaysOfTheWeek = invalid_days;
  this.invalidDaysOfTheWeekCallbacks.forEach(function(callback) {
    callback(this.invalidDaysOfTheWeek);
  }, this);
  return this;
};

DatePickerModel.prototype.setInvalidDates = function(invalid_dates) {
  this.invalidDates = invalid_dates;
  this.invalidDatesCallbacks.forEach(function(callback) {
    callback(this.invalidDates);
  }, this);
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
  callback(this.viewedMonth, this.viewedYear);
  return this;
};

DatePickerModel.prototype.bindMinAdvanceDayCount = function(callback) {
  this.minAdvanceDayCountCallbacks.push(callback);
  callback(this.minAdvanceDayCount);
  return this;
};

DatePickerModel.prototype.bindMaxAdvanceMonthCount = function(callback) {
  this.maxAdvanceMonthCountCallbacks.push(callback);
  callback(this.maxAdvanceMonthCount);
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

DatePickerModel.prototype.getSelectedMonth = function() {
  return this.selectedMonth;
};

DatePickerModel.prototype.getSelectedYear = function() {
  return this.selectedYear;
};

DatePickerModel.prototype.getViewedMonth = function() {
  return this.viewedMonth;
};

DatePickerModel.prototype.getViewedYear = function() {
  return this.viewedYear;
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
