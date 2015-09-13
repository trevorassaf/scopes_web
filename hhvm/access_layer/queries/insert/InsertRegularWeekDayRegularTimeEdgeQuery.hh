<?hh // strict

class InsertRegularWeekDayRegularTimeEdgeQuery {

  public function __construct(
    private InsertQuery<RegularWeekDayRegularTimeEdge> $insertQuery,
    private RegularWeekDayRegularTimeEdgesTable $regularWeekDayRegularTimeEdgesTable
  ) {}

  public async function insert(
    UnsignedInt $regular_week_day_id,
    UnsignedInt $regular_time_id
  ): Awaitable<RegularWeekDayRegularTimeEdge> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->regularWeekDayRegularTimeEdgesTable->getRegularWeekDayIdKey() => $regular_week_day_id->getNumber(),
        $this->regularWeekDayRegularTimeEdgesTable->getRegularTimeIdKey() => $regular_time_id->getNumber(),
      }
    );
  }
}
