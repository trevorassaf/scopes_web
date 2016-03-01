/**
 * Gen0OrderPricePolicies table creation
 * - Pricing generation: 0 
 */
CREATE TABLE Gen0OrderPricePolicies (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  timeEnacted TIMESTAMP NOT NULL,
  price FLOAR UNSIGNED NOT NULL
);
