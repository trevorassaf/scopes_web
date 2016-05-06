var Timestamp = function(
  _date,
  _time
) {

  /**
   * Private state
   */
  var date = _date;
  var time = _time;

  /**
   * Privileged functions
   */
  this.getDate = function() {
    return date;
  };

  this.getTime = function() {
    return time;
  };
};

/**
 * fromDate()
 * @param Date date
 */
Timestamp.prototype.fromDate = function(date) {
  return new Timestamp(
    DateObject.fromDate(date),
    Time.fromDate(date)
  );
};
