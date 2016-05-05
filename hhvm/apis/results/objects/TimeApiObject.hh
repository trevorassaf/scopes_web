<?hh // strict

class TimeApiObject {
  
  const string HOURS_KEY = 'hours';
  const string MINUTES_KEY = 'minutes';
  const string SECONDS_KEY = 'seconds';

  public function __construct(private Time $time) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::HOURS_KEY => $this->time->getHour()->getNumber()->getNumber(),
      self::MINUTES_KEY => $this->time->getMinute()->getNumber()->getNumber(),
      self::SECONDS_KEY => $this->time->getSecond()->getNumber()->getNumber(),
    };
  }
}
