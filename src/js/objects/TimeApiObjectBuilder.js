var TimeApiObjectBuilder = function() {

  /**
   * Api object field keys
   */
  var HOUR_KEY = 'hours';
  var MINUTE_KEY = 'minutes';
  var SECOND_KEY = 'seconds';

  /**
   * Initial values
   */
  var INITIAL_HOUR = 0;
  var INITIAL_MINUTE = 0;
  var INITIAL_SECOND = 0;

  /**
   * Private vars
   */
  var time = new Time(
    this.INITIAL_HOUR,
    this.INITIAL_MINUTE,
    this.INITIAL_SECOND
  );

  /**
   * Privileged functions
   */
  this.build = function() {
    var time_obj = {};
    time_obj[HOUR_KEY] = time.getHours();
    time_obj[MINUTE_KEY] = time.getMinutes();
    time_obj[SECOND_KEY] = time.getSeconds();

    return time_obj;
  };

  this.setTime = function(_time) {
    time = _time;
    return this;
  };

  /**
   * setTimeWithDate()
   * @param Date date
   */
  this.setTimeWithDate = function(date) {
    time = new Time(
      date.getHours(),
      date.getMinutes(),
      date.getSeconds()
    );
    return this;
  };
};
