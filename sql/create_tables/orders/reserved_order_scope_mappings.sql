/**
 * ReservedOrderScopeMappings table creation
 */
CREATE TABLE ReservedOrderScopeMappings (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  rsvdOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(rsvdOrderId) REFERENCES RsvdOrders(id),
  virtualScopeIndex INT UNSIGNED NOT NULL,
  physicalScopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(confirmedOrderId, virtualScopeIndex), 
  UNIQUE KEY(confirmedOrderId, physicalScopeIndex)
);
