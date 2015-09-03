<?hh // strict

class RegularWeekDay implements Model {

  public function __construct(
    private UnsignedInt $id
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }
}
