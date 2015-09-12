<?hh // strict

class FetchIrregularTimesQuery {

  public function __construct(
    private FetchQuery<IrregularTime> $fetchIrregularTimesQuery,
    private IrregularTimesTable $irregularTimesTable
  ) {}

  public async function fetch(
    UnsignedInt $irregular_date_id
  ): Awaitable<ImmVector<IrregularTime>> {
    $fetch_params_builder = new FetchParamsBuilder();

    $fetch_irregular_time_query_handle = $this->fetchIrregularTimesQuery
      ->fetch(
        $fetch_params_builder->setWhereClause(
          new EqualsWhereClause(
            $this->irregularTimesTable->getIrregularDateIdKey(),
            (string)$irregular_date_id->getNumber()
          )
        )
        ->build()
      );

    return $fetch_irregular_time_query_handle
      ->getWaitHandle()
      ->join()
      ->toImmVector();
  }
}
