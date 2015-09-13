<?hh // strict

class InsertRegularTimeQuery {

  public function __construct(
    private InsertQuery<RegularTime> $insertQuery,
    private RegularTimesTable $regularTimesTable
  ) {}

  public async function insert(
    Time $start_time, 
    Time $end_time
  ): Awaitable<RegularTime> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->regularTimesTable->getStartTimeKey() => $start_time,
        $this->regularTimesTable->getEndTimeKey() => $end_time,
      }
    ); 
  }
}
