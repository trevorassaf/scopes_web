<?hh // strict

class InvalidPayloadException extends RequestException {

  public function __construct(string $payload_str) {
    parent::__construct("Invalid payload string format: " . $payload_str);
  }
}
