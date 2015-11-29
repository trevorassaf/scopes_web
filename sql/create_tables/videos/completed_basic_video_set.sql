/**
 * CompletedBasicVideo table creation
 */
CREATE TABLE CompletedBasicVideoSets (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  UNIQUE KEY(confirmedOrderId),
  timeCompleted TIMESTAMP NOT NULL
);
