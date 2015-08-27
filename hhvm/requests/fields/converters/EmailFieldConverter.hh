<?hh // strict

class EmailFieldConverter implements RequestFieldTypeConverter<Email> {

  public function convert(string $key, mixed $value): Email {
    // Validate int type
    if (!is_string($value) || Email::isValid((string)$value)) {
      throw RequestFieldTypeConversionException(
        RequestFieldType::EMAIL,
        $key,
        $value
      );
    }

    // Convert to email 
    return new Email((string)$value);
  }
}
