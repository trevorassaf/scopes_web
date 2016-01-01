/**
 * VideoUploadPolicy create table
 */
CREATE TABLE VideoUploadPolicy (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  maxBytes INT UNSIGNED NOT NULL,
  basicVideoStoragePath VARCHAR(100) NOT NULL,
  editedVideoStoragePath VARCHAR(100) NOT NULL,
  timeEnacted TIMESTAMP NOT NULL,
  webFilesParamKey VARCHAR(20) NOT NULL
);
