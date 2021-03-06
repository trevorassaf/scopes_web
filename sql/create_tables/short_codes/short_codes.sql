/* 
 * Short codes table
 */
CREATE TABLE ShortCodes (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id) ON DELETE CASCADE,
  code VARCHAR(10) NOT NULL,
  alias VARCHAR(20) NOT NULL
);
