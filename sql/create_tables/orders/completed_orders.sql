/**
 * CompletedOrders table creation
 */
CREATE TABLE CompletedOrders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  timeCompleted TIMESTAMP NOT NULL,
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  UNIQUE KEY(confirmedOrderId)
);
