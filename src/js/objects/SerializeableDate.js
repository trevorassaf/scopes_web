function SerializeableDate(
  year,
  month,
  date
) {

  // Ui constants
  this.DATE_DELIMITER = ',';

  this.SHORT_MONTH_NAMES = [
    'Jan',
    'Feb',
    'Mar',
    'Apr',
    'May',
    'Jun',
    'Jul',
    'Aug',
    'Sep',
    'Oct',
    'Nov',
    'Dec'
  ];

  /**
   * getShortMonthName()
   * @param uint month: 0 < month < 11
   */
  this.getShortMonthName = function(month) {
    return this.SHORT_MONTH_NAMES[month];
  };

  // Private state
  this.year = year;

  console.assert(month >= 0 && month < 12);
  this.month = month;

  console.assert(date >= 0 && date < 31);
  this.date = date;
};

SerializeableDate.prototype.serialize = function() {
  return this.getShortMonthName(this.month) + ' ' + this.date
    + this.DATE_DELIMITER + ' ' + this.year;
};
