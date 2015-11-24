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
