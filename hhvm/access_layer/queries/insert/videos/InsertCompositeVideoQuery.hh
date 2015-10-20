<?hh // strict

class InsertCompositeVideoQuery {

  public function __construct(
    private InsertQuery<CompositeVideo> $insertQuery,
    private CompositeVideoTable $compositeVideoTable,
    private HRTimestampSerializer $timestampSerializer
  ) {}

  public async function insert(
    UnsignedInt $edited_video_order_id,
    Timestamp $expiration_time
  ): Awaitable<CompositeVideo> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->compositeVideoTable->getEditedVideoOrderIdKey() => $edited_video_order_id->getNumber(),
        $this->compositeVideoTable->getExpirationTimeKey() => $this->timestampSerializer->serialize($expiration_time),
      }
    ); 
  }

}
