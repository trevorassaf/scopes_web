<?hh // strict

class FetchConfirmedOrderCellLabelsQuery {

  public function __construct(
    private FetchQuery<CellLabel> $fetchCellLabelQuery,
    private CellLabelsTable $cellLabelsTable
  ) {}

  public async function fetch(
    UnsignedInt $edited_video_order_id
  ): Awaitable<ImmVector<CellLabel>> {
    // Assemble cell label fetch query
    $fetch_params_builder = new FetchParamsBuilder();
    
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->cellLabelsTable->getEditedVideoOrderIdKey(),
            $edited_video_order_id->getNumber()
          ) 
        )
        ->build()
      );

    // Execute query: fetch all cell labels associated with this confirmed order
    return await $this->fetchCellLabelQuery->fetch(
      $fetch_params_builder
        ->setTable($this->cellLabelsTable)
        ->build()
    );
  }
}
