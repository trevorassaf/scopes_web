<?hh // strict

class CreateVideoMimeTypeMethod {

  public function __construct(
    private InsertQuery<VideoMimeType> $insertQuery,
    private VideoMimeTypesTable $table
  ) {}

  public function create(
    string $file_extension,
    string $http_application_mime_type
  ): VideoMimeType {
    $insert_handle = $this->insertQuery->insert(
      ImmMap{
        $this->table->getFileExtensionKey() => $file_extension,
        $this->table->getHttpApplicationMimeTypeKey() => $http_application_mime_type,
      }
    ); 

    return $insert_handle
      ->getWaitHandle()
      ->join();
  }
}
