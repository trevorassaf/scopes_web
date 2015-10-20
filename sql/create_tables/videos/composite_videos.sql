/**
 * CompositeVideos table creation
 *  - Fields:
 *    - duraiton: length of video in minutes
 *  - Relationships:
 *    - (optional)o/o: EditedVideoOrders
 *  - File-system asset:
 *    - parent-dir: assets/composite_videos/
 *    - file-name: 'id'.mp4
 */
CREATE TABLE CompositeVideos (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  UNIQUE KEY(confirmedOrderId),
  expirationTime TIMESTAMP NOT NULL,
  duration INT UNSIGNED NOT NULL
);
