<?hh // strict

enum FailedConfirmOrderApiResultType : int {

  CONFLICTING_ORDER = 0x0;
  INVALID_SHORT_CODE = 0x1;
  INVALID_PRICE = 0x2;

}
