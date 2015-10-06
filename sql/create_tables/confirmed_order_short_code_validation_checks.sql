/* 
 * Validated short codes table
 */
CREATE TABLE ConfirmedOrderShortCodeValidationChecks (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  timeChecked TIMESTAMP NOT NULL,
  isValid BOOLEAN NOT NULL
);
