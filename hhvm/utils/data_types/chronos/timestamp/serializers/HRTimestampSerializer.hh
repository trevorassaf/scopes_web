<?hh // strict

class HRTimestampSerializer implements TimestampSerializer {

  const string DELIMITER = " ";

  public function __construct(
    private HRDateSerializer $hrDateSerializer,
    private HRTimeSerializer $hrTimeSerializer
  ) {}

  public function getFormat(): string {
    return $this->hrDateSerializer->getFormat() . self::DELIMITER 
      . $this->hrTimeSerializer->getFormat();
  }

  public function serialize(Timestamp $timestamp): string {
    return $this->hrDateSerializer->serialize($timestamp->getDate()) .
      self::DELIMITER . $this->hrTimeSerializer->serialize($timestamp->getTime());
  }

  public function deserialize(string $timestamp_str): Timestamp {
    invariant($this->isValidString($timestamp_str), "timestamp is not valid!"); 

    $timestamp_tokens = explode(self::DELIMITER, $timestamp_str);
    return new Timestamp(
      $this->hrDateSerializer->deserialize($timestamp_tokens[0]),
      $this->hrTimeSerializer->deserialize($timestamp_tokens[1])
    );
  }

  public function isValidString(string $timestamp_str): bool {
    $timestamp_tokens = explode(self::DELIMITER, $timestamp_str);
    return $this->hrDateSerializer->isValidString($timestamp_tokens[0])
      && $this->hrTimeSerializer->isValidString($timestamp_tokens[1]);
  }
}
