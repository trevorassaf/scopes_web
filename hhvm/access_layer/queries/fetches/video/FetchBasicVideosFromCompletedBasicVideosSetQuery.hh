<?hh // strict

class FetchBasicVideosFromCompletedBasicVideosSetQuery {

  public function __construct(
    private FetchQuery<BasicVideo> $fetchBasicVideosQuery,
    private BasicVideosTable $basicVideosTable
  ) {}

  /**
   * @pre CompletedBasicVideoSet exists
   */
  public async function fetch(UnsignedInt $video_set_id): Awaitable<ImmVector<BasicVideo>> {
    // Select BasicVideos associated with this CompletedBasicVideoSet
    $where_clause_vector_builder = new WhereClauseVectorBuilder(); 
    $where_clause_vector_builder->setFirstClause(
      new EqualsWhereClause(
        $this->basicVideosTable->getCompletedBasicVideoSetIdKey(),
        $video_set_id->getNumber()
      )
    );

    // Order by increasing scope number
    $order_by_clause_builder = new OrderByClauseBuilder();
    $order_by_clause_builder->asc($this->basicVideosTable->getScopeIndexKey());

    // Execute fetch query
    return await $this->fetchBasicVideosQuery->fetch(
      new FetchParams(
        $this->basicVideosTable,
        $where_clause_vector_builder->build(),
        $order_by_clause_builder->build()  
      )
    );
  }
}
