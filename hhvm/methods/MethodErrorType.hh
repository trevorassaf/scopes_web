<?hh // strict

enum MethodErrorType : int {

  EMPTY_FIRST_NAME = 1;
  EMPTY_LAST_NAME = 2;
  EMPTY_EMAIL = 3;
  MALFORMED_EMAIL = 4;
  EMPTY_PASSWORD_HASH = 5;
}
