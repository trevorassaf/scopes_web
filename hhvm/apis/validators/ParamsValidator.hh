<?hh // strict

class ParamsValidator {

  public function verifyNonEmpty(string $value): bool {
    return $value != '';
  }

  public function verifyInt(
    string $value
  ): bool {
    return is_numeric($value);
  }

  public function verifyUnsignedInt(
    int $value
  ): bool {
    return $value >= 0;
  }

  public function verifyTimestamp(
    string $value
  ): bool {
    return DateTime::createFromFormat(
      Timestamp::DATE_TIME_FORMAT,
      $value
    ); 
  }
}
