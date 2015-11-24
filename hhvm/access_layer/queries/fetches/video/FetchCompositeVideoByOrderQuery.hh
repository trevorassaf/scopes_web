<?hh // strict

class FetchCompositeVideoByOrderQuery {

  public function __construct(
    private FetchQuery<CompositeVideo> $fetchCompositeVideosQuery,
    private CompositeVideoTable $compositeVideoTable
  ) {}

  public async function fetch(
    UnsignedInt $order_id
  ): Awaitable<CompositeVideo> {
    //// Assemble fetch query
    // Assemble where-clause: select composite video associated with this order
    $fetch_params_builder = new FetchParamsBuilder();

    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $fetch_params_builder->setWhereClause(
      $where_clause_vector_builder
        ->setFirstClause(
          new EqualsWhereClause(
            $this->compositeVideoTable->getCompletedCompositeVideoIdKey(),
            $order_id->getNumber()
          ) 
        )
        ->build()
      );

    $composite_videos = await $this->fetchCompositeVideosQuery->fetch(
      $fetch_params_builder
        ->setTable($this->compositeVideoTable)
        ->build()
      );

    switch ($composite_videos->count()) {
      // Fail b/c we couldn't find the video associated with this order
      case 0:
        throw new QueryException(
          QueryErrorType::NONEXTANT_RECORD,
          "Couldn't find CompositeVideo for EditedVideoOrder (id=" . $order_id->getNumber() . ")"
        );
        break;
      case 1:
        return $composite_videos[0];
        break;
      default:
        throw new QueryException(
          QueryErrorType::TOO_MANY_RECORDS,
          "Too many CompositeVideos (" . $composite_videos->count()
            . ") associated with this EditedVideoOrder (id="
            . $order_id->getNumber() . ")"
        );
        break;  
    }
  }
}
