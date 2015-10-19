/* 
 * IrregularTimes table creation
 */
CREATE TABLE IrregularTimes (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  startTime TIME NOT NULL,
  endTime TIME NOT NULL
);
