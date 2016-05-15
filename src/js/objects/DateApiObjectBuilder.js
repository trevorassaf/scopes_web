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

    var date_obj = {};
    date_obj[YEAR_KEY] = date.getYear();
    date_obj[MONTH_KEY] = date.getMonth();
    date_obj[DAY_KEY] = date.getDay();

    return date_obj;
  };

  /**
   * setDateObject()
   * @param DateObject _date 
   */
  this.setDateObject = function(_date) {
    date = _date; 
    return this;
  };

  /**
   * setDate()
   * @param Date _date 
   */
  this.setDate = function(_date) {
    date = new DateObject(
      _date.getFullYear(),
      _date.getMonth() + 1, // Date.month is 0 indexed
      _date.getDate()
    );
    return this;
  };
};
