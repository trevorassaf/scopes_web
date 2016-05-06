var DateApiObjectBuilder = function() {

  /**
   * Api object field keys
   */
  var YEAR_KEY = 'year';
  var MONTH_KEY = 'month';
  var DAY_KEY = 'day';

  /**
   * Private vars
   */
  var date = null;

  /**
   * Privileged functions
   */
  this.build = function() {
    console.assert(date != null);

    return {
      YEAR_KEY : date.getYear(),
      MONTH_KEY : date.getMonth(),
      DAY_KEY : date.getDay() 
    };
  };

  /**
   * setDateObject()
   * @param DateObject date 
   */
  this.setDateObject = function(_date) {
    date = _date; 
    return this;
  };
};
