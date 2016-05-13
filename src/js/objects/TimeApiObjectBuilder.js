var TimeApiObjectBuilder = function() {

  /**
   * Api object field keys
   */
  var HOUR_KEY = 'hour';
  var MINUTE_KEY = 'minute';
  var SECOND_KEY = 'second';

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
    INITIAL_HOUR,
    INITIAL_MINUTE,
    INITIAL_SECOND
  );

  /**
   * Privileged functions
   */
  this.build = function() {
    return {
      HOUR_KEY : time.getHours(),
      MINUTE_KEY : time.getMinutes(),
      SECOND_KEY : time.getSeconds() 
    };
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
