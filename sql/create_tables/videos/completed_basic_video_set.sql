/**
 * CompletedBasicVideo table creation
 */
CREATE TABLE CompletedBasicVideoSets (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  completedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(completedOrderId) REFERENCES CompletedOrders(id),
  UNIQUE KEY(confirmedOrderId),
  timeCompleted TIMESTAMP NOT NULL
);
