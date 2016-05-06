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
    dateBuilder.setDate(timestamp.getDate());
    timeBuilder.setTime(timestamp.getTime());
    return this;
  };

  this.build = function() {
    console.assert(timestamp != null);

    return {
      DATE_KEY : dateBuilder.build(),
      TIME_KEY : timeBuilder.build()
    }; 
  };
};
