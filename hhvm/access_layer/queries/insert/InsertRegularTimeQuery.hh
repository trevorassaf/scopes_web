<?hh // strict

class InsertRegularTimeQuery {

  public function __construct(
    private InsertQuery<RegularTime> $insertQuery,
    private RegularTimesTable $regularTimesTable,
    private TimeSerializer $timeSerializer
  ) {}

  public async function insert(
    Time $start_time, 
    Time $end_time
  ): Awaitable<RegularTime> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->regularTimesTable->getStartTimeKey() => $this->timeSerializer->serialize($start_time),
        $this->regularTimesTable->getEndTimeKey() => $this->timeSerializer->serialize($end_time),
      }
    ); 
  }
}
