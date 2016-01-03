<?hh // strict

class FetchDownloadReceiptsForBasicVideoQuery {

  public function __construct(
    private FetchQuery<BasicVideoDownloadReceipt> $fetchDownloadReceiptsQuery,
    private BasicVideoDownloadReceiptsTable $basicVideoDownloadReceiptsTable
  ) {}

  public async function fetch(
    UnsignedInt $basic_video_id
  ): Awaitable<ImmVector<BasicVideoDownloadReceipt>> {
    //// Assemble fetch query ////
    $fetch_params_builder = new FetchParamsBuilder();

    // Assemble where-clause: select all download receipts associated
    // with this basic video  
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder->setFirstClause(
        new EqualsWhereClause(
          $this->basicVideoDownloadReceiptsTable->getBasicVideoIdKey(),
          $basic_video_id->getNumber()
        )
      )
      ->build()
    );

    // Assemble order-by clause: sort by read time in descending order
    // (starting with most recent read)
    $order_by_clause_builder = new OrderByClauseBuilder();
    $fetch_params_builder->setOrderByClause(
      $order_by_clause_builder->desc(
        $this->basicVideoDownloadReceiptsTable->getDownloadTimeKey()
      )
      ->build()
    );

    return await $this->fetchDownloadReceiptsQuery->fetch(
      $fetch_params_builder
        ->setTable($this->basicVideoDownloadReceiptsTable)
        ->build()
    );
  }
}
