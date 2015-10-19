/* 
 * Reserved order plicy table creation
 */
CREATE TABLE ReservedOrderPolicy (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  scopesCount INT UNSIGNED NOT NULL
);
