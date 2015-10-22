/**
 * VideoUploadPolicy create table
 */
CREATE TABLE VideoUploadPolicy (
  maxBytes INT UNSIGNED NOT NULL,
  basicVideoStoragePath VARCHAR(100) NOT NULL,
  editedVideoStoragePath VARCHAR(100) NOT NULL,
  timeEnacted TIMESTAMP NOT NULL
);
