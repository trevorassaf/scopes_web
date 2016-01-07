/**
 * ReservedOrderScopeMappings table creation
 */
CREATE TABLE ReservedOrderScopeMappings (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  rsvdOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(rsvdOrderId) REFERENCES RsvdOrders(id) ON DELETE CASCADE,
  virtualScopeIndex INT UNSIGNED NOT NULL,
  physicalScopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(rsvdOrderId, virtualScopeIndex), 
  UNIQUE KEY(rsvdOrderId, physicalScopeIndex)
);
