/* 
 * Validated short codes table
 */
CREATE TABLE ShortCodeValidationChecks (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  shortCodeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(shortCodeId) REFERENCES ShortCodes(id),
  timeChecked TIMESTAMP NOT NULL,
  isValid BOOLEAN NOT NULL
);
