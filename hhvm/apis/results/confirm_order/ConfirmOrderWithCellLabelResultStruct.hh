<?hh // strict

class ConfirmOrderWithCellLabelResultStruct {

  public int $id;
  public int $user_id;
  public int $scopes_count;
  public string $start_timestamp;
  public string $end_timestamp;
  public string $title;
  public string $description;
  public string $short_code;
  public int $recording_duration;

  public function __construct(
    UnsignedInt $id,
    UnsignedInt $userId,
    UnsignedInt $scopesCount,
    TimestampSegment $timestampSegment,
    string $title,
    string $description,
    string $shortCode,
    UnsignedInt $recordingDuration,
    HRTimestampSerializer $hrTimestampSerializer 
  ) {
    $this->id = $id->getNumber();
    $this->user_id = $userId->getNumber();
    $this->scopes_count = $scopesCount->getNumber();
    $this->start_timestamp = $hrTimestampSerializer->serialize(
      $timestampSegment->getStart()
    );
    $this->end_timestamp = $hrTimestampSerializer->serialize(
      $timestampSegment->getEnd()
    );
    $this->title = $title;
    $this->description = $description;
    $this->short_code = $shortCode;
    $this->recording_duration = $recordingDuration->getNumber();
  }
}
