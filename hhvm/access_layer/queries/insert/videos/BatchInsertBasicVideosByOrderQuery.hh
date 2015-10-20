<?hh // strict

class BatchInsertBasicVideosByOrderQuery {

  public function __construct(
    private BatchInsertQuery<BasicVideo> $batchInsertQuery,
    private BasicVideosTable $basicVideosTable,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $confirmed_order_id,
    ImmVector<CreateBasicVideoRequest> $create_basic_video_requests
  ): Awaitable<ImmVector<BasicVideo>> {
    $basic_videos = Vector{}; 
    $scope_index = 0;

    foreach ($create_basic_video_requests as $request) {
      $basic_videos[] = ImmMap{
        $this->basicVideosTable->getConfirmedOrderIdKey() => $confirmed_order_id->getNumber(),
        $this->basicVideosTable->getScopeIndexKey() => $scope_index,
        $this->basicVideosTable->getExpirationTimeKey() => $this->timestampSerializer->serialize($request->getExpirationTime()),
      };

      ++$scope_index;
    }

    return await $this->batchInsertQuery->insert(
      $basic_videos->toImmVector()
    );
  }
}
