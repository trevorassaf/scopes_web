<?hh // strict

class ApiResultSerializer {

  public function __construct(
    private FieldMapSerializer $fieldMapSerializer
  ) {}

  public function serialize(ApiResult $result): string {
    return $this->fieldMapSerializer->serialize($result->getResultFields());  
  }
}
