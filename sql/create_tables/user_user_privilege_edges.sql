/**
 * User privileges/users join table
 */
CREATE TABLE UserUserPrivilegeEdges (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id),
  userPrivilegeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userPrivilegeId) REFERENCES UserPrivileges(id)
);

