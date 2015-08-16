<?hh // strict

class OrdersTable {

  const string TABLE_NAME = "Orders";
  const string ID_KEY = "id";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string START_TIME_KEY = "startTime";
  const string RESERVED_MINUTES_COUNT_KEY = "reservedMinutesCount";

  public function extrude(Map<string, mixed> $params): Order {
    return new Order(
        new UnsignedInt((int)$params[$this->getIdKey()]),
        new UnsignedInt((int)$params[$this->getScopesCountKey()]),
        new Timestamp((string)$params[$this->getStartTimeKey()]),
        new UnsignedInt((int)$params[$this->getReservedMinutesCountKey()])
    );
  }

  public function getTableName(): string {
    return self::TABLE_NAME;
  }

  public function getIdKey(): string {
    return self::ID_KEY;
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
