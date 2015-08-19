<?hh // strict

class ConfirmedOrdersTable {

  const string TABLE_NAME = "ConfirmedOrders";
  const string ID_KEY = "id";
  const string USER_ID_KEY = "userId";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string START_TIME_KEY = "startTime";
  const string RESERVED_MINUTES_COUNT_KEY = "reservedMinutesCount";
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "description";
  const string SHORT_CODE_KEY = "shortCode";
  const string RECORDING_DURATION_KEY = "recordingDurationMinutes";

  public function extrude(Map<string, mixed> $params): ConfirmedOrder {
    return new ConfirmedOrder(
      new UnsignedInt((int)$params[$this->getIdKey()]),
      new UnsignedInt((int)$params[$this->getUserIdKey()]), 
      new UnsignedInt((int)$params[$this->getScopesCountKey()]),
      new Timestamp((string)$params[$this->getStartTimeKey()]),
      new UnsignedInt((int)$params[$this->getReservedMinutesCountKey()]),
      (string)$params[$this->getTitleKey()],
      (string)$params[$this->getDescriptionKey()],
      (string)$params[$this->getShortCodeKey()],
      new UnsignedInt((int)$params[$this->getRecordingDurationKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getIdKey(): string {
    return self::ID_KEY;
  }

  public function getUserIdKey(): string {
    return self::USER_ID_KEY;
  }

  public function getScopesCountKey(): string {
    return self::SCOPES_COUNT_KEY;
  }

  public function getStartTimeKey(): string {
    return self::START_TIME_KEY;
  }

  public function getReservedMinutesCountKey(): string {
    return self::RESERVED_MINUTES_COUNT_KEY;
  }

  public function getTitleKey(): string {
    return self::TITLE_KEY;
  }
  
  public function getDescriptionKey(): string {
    return self::DESCRIPTION_KEY;
  }

  public function getShortCodeKey(): string {
    return self::SHORT_CODE_KEY;
  }

  public function getRecordingDurationKey(): string {
    return self::RECORDING_DURATION_KEY;
  }
}
