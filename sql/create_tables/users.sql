/* 
 * Users table creation
 *  - m/m: orders, user-privileges 
 */
CREATE TABLE Users (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  firstName VARCHAR(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  lastName VARCHAR(20) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  email VARCHAR(40) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL UNIQUE,
  passwordHash VARCHAR(100) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  timeJoined TIMESTAMP NOT NULL,
  PRIMARY KEY(id)
);
