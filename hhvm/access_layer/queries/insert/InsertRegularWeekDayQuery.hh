<?hh // strict

class InsertRegularWeekDayQuery {

  public function __construct(
    private InsertQuery<RegularWeekDay> $insertQuery,
    private RegularWeekDaysTable $regularWeekDaysTable
  ) {}

  public async function insert(
    UnsignedInt $day_id
  ): Awaitable<RegularWeekDay> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->regularWeekDaysTable->getIdKey() => $day_id->getNumber(),
      }
    ); 
  }
}
