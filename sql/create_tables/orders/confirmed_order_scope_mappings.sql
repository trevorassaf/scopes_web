/**
 * ConfirmedOrderScopeMappings table creation
 */ 
CREATE TABLE ConfirmedOrderScopeMappings (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  virtualScopeIndex INT UNSIGNED NOT NULL,
  physicalScopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(confirmedOrderId, virtualScopeIndex), 
  UNIQUE KEY(confirmedOrderId, physicalScopeIndex)
);
