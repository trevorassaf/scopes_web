<?hh // strict

class DescOrderByTerm extends OrderByTerm {

  const string ORDER_TOKEN = "DESC";

  public function getOrderToken(): string {
    return self::ORDER_TOKEN;
  }
}
