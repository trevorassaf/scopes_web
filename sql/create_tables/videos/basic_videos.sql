/**
 * BasicVideo table creation
 *  - Relationships:
 *    - (optional)o/m: ConfirmedOrder
 *  - Application layer responsibilities:
 *    - number of basic-videos associated with a
 *        given confirmed-order equals scope-count
 *        of that order
 *  - File-system asset:
 *    - parent-dir: assets/basic_videos/
 *    - file-name: system-file-hash('id').mp4
 */
CREATE TABLE BasicVideos (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  confirmedOrderId INT UNSIGNED NOT NULL,
  FOREIGN KEY(confirmedOrderId) REFERENCES ConfirmedOrders(id),
  scopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(confirmedOrderId, scopeIndex),
  title VARCHAR(30) NOT NULL,
  duration INT UNSIGNED NOT NULL
);
