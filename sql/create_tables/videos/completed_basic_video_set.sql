/**
 * CompletedBasicVideo table creation
 */
CREATE TABLE CompletedBasicVideoSets (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  UNIQUE KEY(confirmedOrderId),
  timeCompleted TIMESTAMP NOT NULL
);
