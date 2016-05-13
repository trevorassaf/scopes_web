var TimestampApiObjectBuilder = function() {

  /**
   * Api keys
   */
  var DATE_KEY = 'date';
  var TIME_KEY = 'time';

  /**
   * Private state
   */
  var dateBuilder = new DateApiObjectBuilder();
  var timeBuilder = new TimeApiObjectBuilder();

  /**
   * Privileged functions
   */
  this.setTimestamp = function(timestamp) {
    dateBuilder.setDateObject(timestamp.getDate());
    timeBuilder.setTime(timestamp.getTime());
    return this;
  };

  this.setTimestampWithDate = function(date) {
    dateBuilder.setDate(date);
    timeBuilder.setTimeWithDate(date);
    return this;
  };

  this.build = function() {
    return {
      DATE_KEY : dateBuilder.build(),
      TIME_KEY : timeBuilder.build()
    }; 
  };
};
