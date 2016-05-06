<?hh // strict

class DateApiObject implements ApiObject {

  const string YEAR_KEY = 'year';
  const string MONTH_KEY = 'month';
  const string DAY_KEY = 'day';

  public function __construct(private Date $date) {}

  public function getResultFields(): ImmMap<string, mixed> {
    return ImmMap{
      self::YEAR_KEY => $this->date->getYear()->getNumber()->getNumber(),
      self::MONTH_KEY => $this->date->getMonth()->getNumber()->getNumber(),
      self::DAY_KEY => $this->date->getDay()->getNumber()->getNumber(),
    };
  }
}
