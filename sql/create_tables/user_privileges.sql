/* 
 * User privileges table creation
 *  - m/m: users 
 */
CREATE TABLE UserPrivileges (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  userTypeName VARCHAR(20) NOT NULL,
  UNIQUE KEY(userTypeName),
  PRIMARY KEY(id)
);
