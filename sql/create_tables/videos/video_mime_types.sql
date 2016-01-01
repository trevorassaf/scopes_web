/**
 * VideoMimeTypes create table
 */
CREATE TABLE VideoMimeTypes (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  fileExtension VARCHAR(10) NOT NULL,
  UNIQUE KEY(fileExtension),
  httpApplicationMimeType VARCHAR(20) NOT NULL,
  UNIQUE KEY(httpApplicationMimeType)
);
