/* 
 * RegularActiveWeekDays table creation
 */
CREATE TABLE RegularWeekDays (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  name ENUM(
    'Sunday',
    'Monday',
    'Tuesday',
    'Wednesday',
    'Thursday',
    'Friday',
    'Saturday') NOT NULL,
  UNIQUE KEY(name)
);
