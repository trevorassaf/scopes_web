<?hh // strict

class HRTimestampInterval implements TimestampInterval {

  const string DELIMITER = " ";

  public function __construct(
    private HRDateSerializer $hrDateSerializer,
    private HRTimeSerializer $hrTimeSerializer
  ) {}

  public function serializer(Timestamp $timestamp): string {
    return $this->hrDateInterval;
  }

  public function deserialize(string $timestamp_str): Timestamp {
    invariant($this->isValidString($timestamp_str), "timestamp is not valid!"); 
    $timestamp_tokens = explode(self::DELIMITER, $timestamp_str);
    return new Timestamp(
      Date::fromString($timestamp_tokens[0]),
      Time::fromString($timestamp_tokens[1])
    );
  }

  public function isValidString(string $timestamp_str): bool {
    $timestamp_tokens = explode(self::DELIMITER, $timestamp_str);
    return $this->hrDateSerializer->isValidString($timestamp_tokens[0])
      && $this->hrTimeSerializer->isValidString($timestamp_tokens[1]);
  }
}
