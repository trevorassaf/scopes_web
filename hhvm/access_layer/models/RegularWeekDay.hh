<?hh // strict

class RegularWeekDay implements Model {

  public static function fromType(
    DayOfTheWeekType $type
  ): RegularWeekDay {
    return new RegularWeekDay(new UnsignedInt((int)$type));
  }

  public function __construct(
    private UnsignedInt $id
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getType(): DayOfTheWeekType {
    return DayOfTheWeekType::assert($this->id->getNumber());
  }
}
