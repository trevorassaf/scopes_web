/**
 * BasicVideoDownloadReciept table creation
 */
CREATE TABLE BasicVideoDownloadReceipts (
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  PRIMARY KEY(id),
  basicVideoId INT UNSIGNED NOT NULL,
  FOREIGN KEY(basicVideoId) REFERENCES BasicVideos(id),
  downloadTime TIMESTAMP NOT NULL
);
