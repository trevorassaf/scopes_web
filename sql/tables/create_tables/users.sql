/* 
 * Users table creation
 *  - m/m: orders, user-privileges 
 */
CREATE TABLE Users (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  firstName VARCHAR(20) NOT NULL,
  lastName VARCHAR(20) NOT NULL,
  email VARCHAR(40) NOT NULL,
  passwordHash VARCHAR(100) NOT NULL,
  timeJoined TIMESTAMP NOT NULL,
  PRIMARY KEY(id)
);
