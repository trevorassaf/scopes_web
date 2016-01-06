/**
 * BasicVideoOrders
 */
CREATE TABLE BasicVideoOrders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  basicVideoSetOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(basicVideoSetOrderId) REFERENCES BasicVideoSetOrders(id),
  virtualScopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(basicVideoSetOrderId, virtualScopeIndex),
  title VARCHAR(40) NOT NULL
);
