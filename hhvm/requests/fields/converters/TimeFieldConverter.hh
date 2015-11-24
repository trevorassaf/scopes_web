<?hh // strict

class TimeFieldConverter implements RequestFieldTypeConverter<Time> {

  public function __construct(
    private TimeSerializer $timeSerializer
  ) {}

  public function convert(string $key, mixed $value): Time {
    if (!is_string($value) || !$this->timeSerializer->isValidString((string)$value)) {
      throw new RequestFieldTypeConversionException(
        RequestFieldType::TIME,
        $key,
        $value
      );
    }

    // Convert to time
    return $this->timeSerializer->deserialize((string)$value);
  }
}
