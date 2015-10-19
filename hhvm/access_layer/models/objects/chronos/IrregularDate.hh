<?hh // strict

class IrregularDate implements Model {

  public function __construct(
    private UnsignedInt $id,
    private Date $date,
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getDate(): Date {
    return $this->date;
  }
}
