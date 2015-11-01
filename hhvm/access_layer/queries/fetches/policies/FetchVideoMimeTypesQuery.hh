<?hh // strict

class FetchVideoMimeTypesQuery {

  public function __construct(
    private FetchQuery<VideoMimeType> $fetchQuery,
    private VideoMimeTypesTable $videoMimeTypesTable
  ) {}

  public async function fetch(): Awaitable<ImmVector<VideoMimeType>> {
    $fetch_params_builder = new FetchParamsBuilder();
    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->videoMimeTypesTable)
        ->build()
    );
  }
}
