/* 
 * Transacted confirmed orders table
 */
CREATE TABLE FailedConfirmedOrderTransactions (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  timeOfFailedTransaction TIMESTAMP NOT NULL
);
