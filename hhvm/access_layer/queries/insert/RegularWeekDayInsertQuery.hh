<?hh // strict

class RegularWeekDayInsertQuery {

  public function __construct(
    private InsertQuery<RegularWeekDay> $insertQuery,
    private RegularWeekDaysTable $regularWeekDaysTable
  ) {}

  public async function insert(
    DayOfTheWeekType $day 
  ): Awaitable<RegularWeekDay> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->regularWeekDaysTable->getIdKey() => (int)$day,
      }
    ); 
  }
}
