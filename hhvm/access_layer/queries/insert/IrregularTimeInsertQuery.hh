<?hh // strict

class IrregularTimeInsertQuery {
  
  public function __construct(
    private InsertQuery<IrregularTime> $insertQuery,
    private IrregularTimesTable $irregularTimesTable
  ) {}

  public async function insert(
    UnsignedInt $irregular_date_id,
    Time $start_time, 
    Time $end_time
  ): Awaitable<IrregularTimesTable> {
    return await $this->insertQuery->query(
      ImmMap{
        $this->irregularTimesTable->getIrregularDateIdKey() => $irregular_date_id->getNumber(),
        $this->irregularTimesTable->getStartTimeKey() => $start_time->toString(),
        $this->irregularTimesTable->getEndTimeKey() => $irregular_date_id->getNumber(),
      }
    ); 
  }
}
