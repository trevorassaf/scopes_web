/* 
 * Validated short codes table
 */
CREATE TABLE ConfirmedOrdersWithValidatedShortCode (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  validationTime TIMESTAMP NOT NULL
);
