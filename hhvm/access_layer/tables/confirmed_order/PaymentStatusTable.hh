<?hh // strict

class PaymentStatusTable extends Table {
  
  const string TABLE_NAME = 'PaymentStatuses';
  const string NAME_KEY = 'name';

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getNameKey(): string {
    return self::NAME_KEY;
  }
}
