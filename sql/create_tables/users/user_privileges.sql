/* 
 * User privileges table creation
 *  - m/m: users 
 */
CREATE TABLE UserPrivileges (
  id INT UNSIGNED NOT NULL,
  PRIMARY KEY(id),
  name VARCHAR(20) NOT NULL,
  UNIQUE KEY(name)
);
