<?hh // strict

class RsvdOrdersTable extends Table<RsvdOrder> {

  const string TABLE_NAME = "RsvdOrders";
  const string USER_ID_KEY = "userId";
  const string LEASE_START_KEY = "leaseStart";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string START_TIME_KEY = "startTime";
  const string RESERVED_MINUTES_COUNT_KEY = "reservedMinutesCount";

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): RsvdOrder {
    return new RsvdOrder(
      $id,
      new UnsignedInt((int)$params[$this->getUserIdKey()]), 
      new Timestamp((string)$params[$this->getLeaseStartKey()]),
      new UnsignedInt((int)$params[$this->getScopesCountKey()]),
      new Timestamp((string)$params[$this->getStartTimeKey()]),
      new UnsignedInt((int)$params[$this->getReservedMinutesCountKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getUserIdKey(): string {
    return self::USER_ID_KEY;
  }

  public function getLeaseStartKey(): string {
    return self::LEASE_START_KEY;
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
}
