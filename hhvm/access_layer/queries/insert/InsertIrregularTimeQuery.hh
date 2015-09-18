<?hh // strict

class InsertIrregularTimeQuery {
  
  public function __construct(
    private InsertQuery<IrregularTime> $insertQuery,
    private IrregularTimesTable $irregularTimesTable,
    private TimeSerializer $timeSerializer
  ) {}

  public async function insert(
    UnsignedInt $irregular_date_id,
    Time $start_time, 
    Time $end_time
  ): Awaitable<IrregularTime> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->irregularTimesTable->getIrregularDateIdKey() => $irregular_date_id->getNumber(),
        $this->irregularTimesTable->getStartTimeKey() => $this->timeSerializer->serialize($start_time),
        $this->irregularTimesTable->getEndTimeKey() => $this->timeSerializer->serialize($end_time),
      }
    ); 
  }
}
