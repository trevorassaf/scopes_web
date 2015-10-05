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
  endTime TIMESTAMP NOT NULL,
  title VARCHAR(40) NOT NULL,
  description VARCHAR(400) NOT NULL,
  shortCodeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(shortCodeId) REFERENCES ShortCodes(id),
  recordingDurationMinutes INT UNSIGNED NOT NULL
);
