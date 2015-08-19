/* 
 * ConfirmedOrders table creation
 *  - m/m: users, o/m: CellLabel 
 */
CREATE TABLE ConfirmedOrders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userid) REFERENCES Users(id),
  scopesCount INT UNSIGNED NOT NULL,
  startTime TIMESTAMP NOT NULL,
  reservedMinutesCount INT UNSIGNED NOT NULL,
  title VARCHAR(40) NOT NULL,
  description VARCHAR(400) NOT NULL,
  shortCode VARCHAR(40) NOT NULL,
  recordingDurationMinutes INT UNSIGNED NOT NULL
);
