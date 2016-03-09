function SerializeableTime(
  hours,    // military time
  minutes,
  seconds
) {

  this.TIME_DELIMITER = ':';
  this.AM_TOKEN = 'am';
  this.PM_TOKEN = 'pm';

  this.convertHourToNonMilitaryTime = function(military_hours) {
    return (military_hours > 12)
      ? military_hours - 12
      : military_hours;
  };

  this.getMeridianToken = function(military_hours) {
    return (military_hours >= 12 && military_hours !== 24)
      ? this.PM_TOKEN
      : this.AM_TOKEN;
  };

  this.hours = hours;
  this.minutes = minutes;
  this.seconds = seconds;
};

SerializeableTime.prototype.serialize = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.seconds, 2) + " " + meridian_token;
};

SerializeableTime.prototype.serializeWithoutSeconds = function() {
  var non_military_hours = this.convertHourToNonMilitaryTime(this.hours);
  var meridian_token = this.getMeridianToken(this.hours);
  
  return non_military_hours.toString() + this.TIME_DELIMITER +
    Utils.stringifyNumberWithEnforcedDigitCount(this.minutes, 2) +
    " " + meridian_token;
};
