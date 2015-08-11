<?hh // strict

require_once('Model.hh');

require_once(dirname(__FILE__)."/../../utils/data_types/UnsignedInt.hh");

class Order implements Model {
  
  public function __construct(
      private UnsignedInt $id,
      private UnsignedInt $scopesCount,
      private DateTime $startTime,
      private UnsignedInt $reservedMinutesCount 
  ) {}

  public function getId(): UnsignedInt {
    return $this->id;
  }

  public function getScopesCount(): UnsignedInt {
    return $this->scopesCount;
  }

  public function getStartTime(): DateTime {
    return $this->startTime;
  }
  
  public function getReservedMinutesCount(): UnsignedInt {
    return $this->reservedMinutesCount;
  }

}
