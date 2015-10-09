/**
 * EditedVideoOrders table creation
 *   - Relationships:
 *      - (optional)o/o: ConfirmedOrder
 */
CREATE TABLE EditedVideoOrders (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  UNIQUE KEY(confirmedOrderId),
  recordingDurationMinutes INT UNSIGNED NOT NULL
);
