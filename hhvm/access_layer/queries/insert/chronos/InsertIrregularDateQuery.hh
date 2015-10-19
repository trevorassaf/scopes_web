<?hh // strict

class InsertIrregularDateQuery {

  public function __construct(
    private InsertQuery<IrregularDate> $insertQuery,
    private IrregularDatesTable $irregularDatesTable,
    private DateSerializer $dateSerializer
  ) {}

  public async function insert(
    Date $date
  ): Awaitable<IrregularDate> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->irregularDatesTable->getDateKey() => $this->dateSerializer->serialize($date),
      }
    );
  }
}
