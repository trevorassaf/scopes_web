/**
 * OrderPricePolicy table creation
 *   - price: price per group of 4 scopes per hour
 */
CREATE TABLE OrderPricePolicy (
  price FLOAT UNSIGNED NOT NULL,
  timeEnacted TIMESTAMP NOT NULL
);
