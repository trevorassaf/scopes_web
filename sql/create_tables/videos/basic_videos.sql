/**
 * BasicVideo table creation
 *  - Relationships:
 *    - (optional)o/m: CompletedBasicVideoSets 
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
  completedBasicVideoSetId INT UNSIGNED NOT NULL,
  FOREIGN KEY(completedBasicVideoSetId) REFERENCES CompletedBasicVideoSets(id),
  scopeIndex INT UNSIGNED NOT NULL,
  UNIQUE KEY(completedBasicVideoSetId, scopeIndex),
  title VARCHAR(30) NOT NULL,
  duration INT UNSIGNED NOT NULL,
  mimeId INT UNSIGNED NOT NULL,
  FOREIGN KEY(mimeId) REFERENCES VideoMimeTypes(id)
);
