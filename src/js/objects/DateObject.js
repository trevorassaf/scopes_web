var DateObject = function(
  _year,
  _month,
  _day
) {
  
  /**
   * Private vars
   */
  var year = _year;
  var month = _month;
  var day = _day;

  // Validate input
  console.assert(month > 0 && month <= 12);
  console.assert(day > 0 && day <= 31);

  /**
   * Privileged functions
   */
  this.getYear = function() {
    return year;
  };

  this.getMonth = function() {
    return month;
  };

  this.getDay = function() {
    return day;
  };
};

DateObject.prototype.fromDate = function(date) {
  return new DateObject(
    date.getFullYear(),
    date.getMonth() + 1,
    date.getDate()
  );
};
