<?hh

// strict

class UnsignedInt {
  
  private int $number; 

  public static function isValidString(string $number): bool {
    return is_int($number) && self::isUnsigned((int)$number);
  }

  public static function fromString(string $number): UnsignedInt {
    return new UnsignedInt((int)$number);
  }

  public static function isUnsigned(int $number): bool {
    return $number >= 0;
  }

  public function __construct(int $number) {
    if (!static::isUnsigned($number)) {
      throw new Exception("{$number} cannot be negative!");
    }

    $this->number = $number;
  }

  public function getNumber(): int {
    return $this->number;
  }
};
