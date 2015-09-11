<?hh // strict

class RsvdOrdersTable extends Table<RsvdOrder> {

  const string TABLE_NAME = "RsvdOrders";
  const string USER_ID_KEY = "userId";
  const string LEASE_START_KEY = "leaseStart";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getUserIdKey(): string {
    return $this->makeTableQualifiedKey(self::USER_ID_KEY);
  }

  public function getLeaseStartKey(): string {
    return $this->makeTableQualifiedKey(self::LEASE_START_KEY);
  }

  public function getScopesCountKey(): string {
    return $this->makeTableQualifiedKey(self::SCOPES_COUNT_KEY);
  }

  public function getStartTimeKey(): string {
    return $this->makeTableQualifiedKey(self::START_TIME_KEY);
  }

  public function getEndTimeKey(): string {
    return $this->makeTableQualifiedKey(self::END_TIME_KEY);
  }
}
