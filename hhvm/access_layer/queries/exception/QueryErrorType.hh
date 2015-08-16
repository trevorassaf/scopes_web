<?hh // strict

enum QueryErrorType : int {
  DUPLICATE_UNIQUE_KEY = 0x0;
  NONEXISTANT_UNIQUE_KEY = 0x1;
}
