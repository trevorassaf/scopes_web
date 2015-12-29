<?hh // strict

class FailedSerializationException extends Exception {

  public function __construct(ImmMap<string, mixed> $field_map) {
    parent::__construct($field_map->__toString());
  }
}
