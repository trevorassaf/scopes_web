<?hh // strict

class InsertEditedVideoOrderQuery {

  public function __construct(
    private InsertQuery<EditedVideoOrder> $insertQuery,
    private EditedVideoOrderTable $editedVideoOrdersTable
  ) {}

  public async function insert(
    UnsignedInt $confirmed_order,
    UnsignedInt $recording_duration_minutes
  ): Awaitable<EditedVideoOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->editedVideoOrdersTable->getConfirmedOrderIdKey() => $confirmed_order->getNumber(),
        $this->editedVideoOrdersTable->getRecordingDurationMinutesKey() => $recording_duration_minutes->getNumber(),
      }
    );
  }
}
