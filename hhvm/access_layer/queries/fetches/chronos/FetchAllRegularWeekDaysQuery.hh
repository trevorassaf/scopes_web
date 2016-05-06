<?hh // strict

class FetchAllRegularWeekDaysQuery {

  public function __construct(
    private FetchQuery<RegularWeekDay> $fetchQuery,
    private RegularWeekDaysTable $table
  ) {}

  public async function fetch(): Awaitable<ImmVector<RegularWeekDay>> {
    $fetch_params_builder = new FetchParamsBuilder();
    return await $this->fetchQuery->fetch(
      $fetch_params_builder
        ->setTable($this->table)
        ->build()
      );
  }
}
