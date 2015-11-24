<?hh // strict

class CreateBasicVideoRequest {

  public function __construct(
    private string $title,
    private Time $videoDuration,
    private string $fileName,
    private string $description
  ) {}

  public function getTitle(): string {
    return $this->title;
  }

  public function getVideoDuration(): Time {
    return $this->videoDuration;
  }

  public function getFileName(): string {
    return $this->fileName;
  }

  public function getDescription(): string {
    return $this->description;
  }
}
