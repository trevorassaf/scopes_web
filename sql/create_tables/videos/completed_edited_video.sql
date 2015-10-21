/**
 * CompletedEditedVideo table creation
 */
CREATE TABLE CompletedEditedVideo (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  editedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(editedOrderId) REFERENCES EditedVideoOrders(id),
  UNIQUE KEY(editedOrderId),
  timeCompleted TIMESTAMP NOT NULL
);
