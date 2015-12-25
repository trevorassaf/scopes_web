<?hh // strict

class DeleteFileMethod {

  public function delete(string $path): void {
    if (file_exists($path)) {
      if (!unlink($path)) {
        throw new FailedDeleteFileException("Failed to delete file! Path: " . $path);
      }
    } else {
      throw new FailedDeleteFileException("File does not exist! Path: " . $path);
    }
  }
}
