<?hh // strict

class ConfirmedOrdersTable extends Table {

  const string TABLE_NAME = "ConfirmedOrders";
  const string USER_ID_KEY = "userId";
  const string SCOPES_COUNT_KEY = "scopesCount";
  const string START_TIME_KEY = "startTime";
  const string END_TIME_KEY = "endTime";
  const string TITLE_KEY = "title";
  const string DESCRIPTION_KEY = "description";
  const string SHORT_CODE_ID_KEY = "shortCodeId";
  const string PRICE_KEY = "price";
  const string TIME_ORDERED_KEY = "timeOrdered";

  public function getName(): string {
    return self::TABLE_NAME;
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

  public function getEndTimeKey(): string {
    return self::END_TIME_KEY;
  }

  public function getTitleKey(): string {
    return self::TITLE_KEY;
  }
  
  public function getDescriptionKey(): string {
    return self::DESCRIPTION_KEY;
  }

  public function getShortCodeIdKey(): string {
    return self::SHORT_CODE_ID_KEY;
  }

  public function getPriceKey(): string {
    return self::PRICE_KEY;
  }

  public function getTimeOrderedKey(): string {
    return self::TIME_ORDERED_KEY;
  }
}
