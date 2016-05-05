/**
 * Order configuration table creation
 */
CREATE TABLE OrderConfiguration (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  scopesCount INT UNSIGNED NOT NULL,
  maxExperimentDuration INT UNSIGNED NOT NULL,
  timeEnacted TIMESTAMP NOT NULL,
  UNIQUE KEY(timeEnacted)
);
