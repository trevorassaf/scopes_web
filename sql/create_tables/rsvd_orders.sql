/* 
 * RsvdOrders table creation
 *  - m/m: users
 */
CREATE TABLE RsvdOrders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id),
  scopesCount INT UNSIGNED NOT NULL,
  startTime TIMESTAMP NOT NULL,
  endTime Timestamp NOT NULL
);
