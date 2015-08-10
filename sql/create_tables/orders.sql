/* 
 * Orders table creation
 *  - m/m: users
 */
CREATE TABLE Orders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  scopesCount INT UNSIGNED NOT NULL,
  startTime TIMESTAMP NOT NULL,
  reservedMinutesCount INT UNSIGNED NOT NULL,
  PRIMARY KEY(id)
);
