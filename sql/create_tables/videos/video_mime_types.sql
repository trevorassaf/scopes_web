/**
 * VideoMimeTypes create table
 */
CREATE TABLE VideoMimeTypes (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  mimeType VARCHAR(10) NOT NULL,
  UNIQUE KEY(mimeType)
);
