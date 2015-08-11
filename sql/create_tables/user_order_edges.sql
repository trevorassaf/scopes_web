/**
 * Users/Orders join table
 */
CREATE TABLE UserOrderEdges (
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id),
  orderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(orderId) REFERENCES Orders(id),
  PRIMARY KEY(userId, orderId)
);

