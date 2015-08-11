/**
 * Users/Orders join table
 */
CREATE TABLE UserOrderEdges (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id),
  orderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(orderId) REFERENCES Orders(id)
);

