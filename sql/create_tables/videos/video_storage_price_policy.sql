/**
 * VideoStoragePricePolicy table creation
 *  - price: price per Gb per day
 */
CREATE TABLE VideoStoragePricePolicy (
  price FLOAT UNSIGNED NOT NULL,
  numberFreeDays INT UNSIGNED NOT NULL,
  timeEnacted TIMESTAMP NOT NULL
);
