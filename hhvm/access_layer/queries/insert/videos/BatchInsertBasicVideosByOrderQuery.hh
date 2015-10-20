<?hh // strict

class BatchInsertBasicVideosByOrderQuery {

  public function __construct(
    private BatchInsertQuery<BasicVideo> $batchInsertQuery,
    private BasicVideosTable $basicVideosTable
  ) {}

  public async function insert(
    UnsignedInt $confirmed_order_id
  ): Awaitable<ImmVector<BasicVideo>> {
    
  }
}
