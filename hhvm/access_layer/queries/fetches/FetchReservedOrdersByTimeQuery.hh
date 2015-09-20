<?hh // strict

class FetchReservedOrdersByTimeQuery {

  public function __construct(
    private FetchQuery<RsvdOrder> $fetchQuery,
    private RsvdOrdersTable $rsvdOrdersTable,
    private TimestampSerializer $timestampSerializer
  ) {}

  public async function fetch(
    TimestampSegment $interval
  ): Awaitable<ImmVector<RsvdOrder>> {
    // Build where clause
    $where_clause_vector_builder = new WhereClauseVectorBuilder();
    $where_clause = $where_clause_vector_builder
      ->setFirstClause(
        new GreaterThanOrEqualToWhereClause(
          $this->rsvdOrdersTable->getStartTimeKey(),
          $this->timestampSerializer->serialize($interval->getStart())
        )
      )
      ->logicalAnd(
        new LessThanOrEqualToWhereClause(
          $this->rsvdOrdersTable->getEndTimeKey(),
          $this->timestampSerializer->serialize($interval->getEnd())
        )
      )
      ->build();

    // Build order by clause
    $order_clause_builder = new OrderByClauseBuilder();
    $order_clause = $order_clause_builder
      ->asc($this->rsvdOrdersTable->getStartTimeKey())
      ->build();

    return await $this->fetchQuery->fetch(
      new FetchParams(
        $this->rsvdOrdersTable,
        $where_clause,
        $order_clause
      )
    );  
  }
}
