<?hh // strict

enum QueryErrorType : int {
  
  DUPLICATE_KEY = 0x0;
  UNKNOWN = 0x1;
  TOO_MANY_RECORDS = 0x2;
  NONEXTANT_RECORD = 0x3;
}
