/** 
 * ConfirmedOrders table creation
 *  - Relationships:
 *    - o/m: users  
 *    - o/o: ConfirmedOrder
 *  - Application layer responsibilities:
 *    - 'shortCodeId' should belong to user indicated by 'userId'
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
  price DECIMAL(6,2) UNSIGNED NOT NULL,
  basicVideosExpirationTime TIMESTAMP NOT NULL
);
