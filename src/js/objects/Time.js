var Time = function(
  _hours,
  _minutes,
  _seconds
) {
 
  /**
   * Private vars
   */
  var hours = (_hours == null) ? 0 : _hours;
  var minutes = (_minutes == null) ? 0 : _minutes;
  var seconds = (_seconds == null) ? 0 : _seconds;

  // Validate input
  console.assert(hours >= 0 && hours < 24);
  console.assert(minutes >= 0 && minutes < 60);
  console.assert(seconds >= 0 && seconds < 60);

  /**
   * Public functions
   */
  this.getHours = function() {
    return hours;
  };

  this.getMinutes = function() {
    return minutes;
  };

  this.getSeconds = function() {
    return seconds;
  };

  this.toDate = function() {
    var current_time = new Date(0, 0, 0);
    current_time.setHours(hours);
    current_time.setMinutes(minutes);
    current_time.setSeconds(seconds);
    return current_time;
  };
};

Time.prototype.fromDate = function(date) {
  return new Time(
    date.getHours(),
    date.getMinutes(),
    date.getSeconds()
  );
};
