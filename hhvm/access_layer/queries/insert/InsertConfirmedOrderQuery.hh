<?hh // strict

class InsertConfirmedOrderQuery {

  public function __construct(
    private InsertQuery<ConfirmedOrder> $insertQuery,
    private ConfirmedOrdersTable $confirmedOrdersTable
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    UnsignedInt $scopes_count,
    Timestamp $start_time,
    Timestamp $end_time,
    string $title,
    string $description,
    string $short_code,
    UnsignedInt $recording_duration
  ): Awaitable<ConfirmedOrder> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->confirmedOrdersTable->getUserIdKey() => $user_id->getNumber(),
        $this->confirmedOrdersTable->getScopesCountKey() => $scopes_count->getNumber(),
        $this->confirmedOrdersTable->getStartTimeKey() => $start_time->toString(),
        $this->confirmedOrdersTable->getEndTimeKey() => $end_time->toString(),
        $this->confirmedOrdersTable->getTitleKey() => $title,
        $this->confirmedOrdersTable->getDescriptionKey() => $description,
        $this->confirmedOrdersTable->getShortCodeKey() => $short_code,
        $this->confirmedOrdersTable->getRecordingDurationKey() => $recording_duration->getNumber(),
      }
    );  
  }

}
