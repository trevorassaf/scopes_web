var DateOperator = (function() {

  // Date constants
  var HOURS_IN_MICROSECONDS = 3.6e6;

  /**
   * Privileged methods
   */

  this.getDifferenceInHours = function(
    date_a,
    date_b
  ) {
    return Math.abs(date_a - date_b) / HOURS_IN_MICROSECONDS; 
  };

  return {
    getDifferenceInHours: getDifferenceInHours
  };

})();
