/* 
 * RegularTimes table creation
 */
CREATE TABLE RegularTimes (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  startTime TIME NOT NULL,
  endTime TIME NOT NULL
);
