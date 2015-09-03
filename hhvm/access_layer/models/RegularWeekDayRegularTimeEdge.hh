<?hh // strict

class RegularWeekDayRegularTimeEdge implements Model {

  public function __construct(
    private UnsignedInt $id,
    private UnsignedInt $regularWeekDayId,
    private UnsignedInt $regularTimeId
  ) {}
  
  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getRegularWeekDayId(): UnsignedInt {
    return $this->regularWeekDayId;
  }

  public function getRegularTimeId(): UnsignedInt {
    return $this->regularTimeId;
  }
}
