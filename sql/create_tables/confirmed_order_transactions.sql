/* 
 * Transacted confirmed orders table
 */
CREATE TABLE ConfirmedOrderTransactions (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  UNIQUE KEY(confirmedOrderId),
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  timeOfTransaction TIMESTAMP NOT NULL
);
