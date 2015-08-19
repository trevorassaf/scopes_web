/* 
 * CellLabel table creation
 */
CREATE TABLE CellLabels (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  cellNumber INT UNSIGNED NOT NULL,
  label VARCHAR(40) NOT NULL
);
