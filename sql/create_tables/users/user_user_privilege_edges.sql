/**
 * User privileges/users join table
 */
CREATE TABLE UserUserPrivilegeEdges (
  userId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userId) REFERENCES Users(id),
  userPrivilegeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(userPrivilegeId) REFERENCES UserPrivileges(id),
  PRIMARY KEY(userId, userPrivilegeId)
);

