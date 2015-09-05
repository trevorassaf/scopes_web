<?hh // strict

class AscOrderByTerm extends OrderByTerm {

  const string ORDER_TOKEN = "ASC";

  public function getOrderToken(): string {
    return self::ORDER_TOKEN;
  }
}
