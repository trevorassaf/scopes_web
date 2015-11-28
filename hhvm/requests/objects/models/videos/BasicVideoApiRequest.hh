<?hh // strict

class BasicVideoApiRequest {

  const string REQUEST_OBJECT_NAME = "BasicVideo";
  const string TITLE_KEY = "title";
  const string VIDEO_DURATION_KEY = "duration";
  const string FILE_NAME_KEY = "filename";
  const string DESCRIPTION_KEY = "description";

  public function __construct(
    private RequestField<string> $title,
    private RequestField<Time> $videoDuration,
    private RequestField<string> $fileName,
    private RequestField<string> $description
  ) {}

  public function getTitle(): RequestField<string> {
    return $this->title;
  }

  public function getVideoDuration(): RequestField<Time> {
    return $this->videoDuration;
  }

  public function getFileName(): RequestField<string> {
    return $this->fileName;
  }

  public function getDescription(): RequestField<string> {
    return $this->description;
  }
}

class BasicVideoApiRequestBuilder {

  private ?RequestField<string> $title;
  private ?RequestField<Time> $videoDuration;
  private ?RequestField<string> $fileName;
  private ?RequestField<string> $description;

  public function setTitle(RequestField<string> $title): this {
    $this->title = $title;
    return $this;
  }

  public function setVideoDuration(RequestField<Time> $video_duration): this {
    $this->videoDuration = $video_duration;
    return $this;
  }

  public function setFileName(RequestField<string> $file_name): this {
    $this->fileName = $file_name;
    return $this;
  }

  public function setDescription(RequestField<string> $description): this {
    $this->description = $description;
    return $this;
  }
  
  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        CreateUploadBasicVideosApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): BasicVideoApiRequest {
    return new BasicVideoApiRequest(
      $this->checkNotNull($this->title, BasicVideoApiRequest::TITLE_KEY),
      $this->checkNotNull($this->videoDuration, BasicVideoApiRequest::VIDEO_DURATION_KEY),
      $this->checkNotNull($this->fileName, BasicVideoApiRequest::FILE_NAME_KEY),
      $this->checkNotNull($this->description, BasicVideoApiRequest::DESCRIPTION_KEY)
    );   
  }

}
