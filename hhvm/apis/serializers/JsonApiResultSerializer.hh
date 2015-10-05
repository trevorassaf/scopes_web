<?hh // strict

class JsonApiResultSerializer extends ApiResultSerializer{

  public function __construct() {
    parent::__construct(new JsonFieldMapSerializer());
  }
}
