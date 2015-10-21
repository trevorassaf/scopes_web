/**
 * OrderTransactionPolicy table creation
 */
CREATE TABLE OrderTransactionPolicy (
  daysBeforeCharge INT UNSIGNED NOT NULL,
  timeEnacted TIMESTAMP NOT NULL 
);
