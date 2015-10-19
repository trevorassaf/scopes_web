/**
 * CellLabels table creation
 *  - Relationships:
 *    - o/m: EditedVideoOrders
 */
CREATE TABLE CellLabels (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  editedVideoOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(editedVideoOrderId) REFERENCES EditedVideoOrders(id),
  cellNumber INT UNSIGNED NOT NULL,
  label VARCHAR(20) NOT NULL
);
