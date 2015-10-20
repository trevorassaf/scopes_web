<?hh // strict

class CreateBasicVideoRequest {

  public function __construct(
    private string $title
  ) {}

  public function getTitle(): string {
    return $this->title;
  }
}
