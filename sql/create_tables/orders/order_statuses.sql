/**
 * OrderStatuses
 */
CREATE TABLE OrderStatuses (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  name VARCHAR(20) NOT NULL,
  UNIQUE KEY(name)
);
