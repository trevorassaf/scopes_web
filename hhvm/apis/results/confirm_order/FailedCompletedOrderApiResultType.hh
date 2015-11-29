<?hh // strict

enum FailedCompletedOrderApiResultType : int {

  NONEXTANT_CONFIRMED_ORDER = 0x0;
  INVALID_PERMISSION = 0x1;
  ORDER_ALREADY_CONFIRMED = 0x2;

}
