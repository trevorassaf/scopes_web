/* 
 * Orders table creation
 *  - m/m: users
 */
CREATE TABLE Orders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  scopesCount INT UNSIGNED NOT NULL,
  startTime TIMESTAMP NOT NULL,
  reservedMinutesCount INT UNSIGNED NOT NULL,
  statusId INT UNSIGNED NOT NULL,
  FOREIGN KEY(statusId) REFERENCES OrderStatuses(id),
  PRIMARY KEY(id)
);
