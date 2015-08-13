<?hh // strict

enum ApiErrorType : int {
  EMPTY_USER_FIRST_NAME = 0x1;
  EMPTY_USER_LAST_NAME = 0x2;
  EMPTY_USER_EMAIL = 0x3;
  EMAIL_MISSING_USERNAME_TOKEN = 0x4;
  EMAIL_MISSING_DOMAIN_TOKEN = 0x5;
  EMAIL_EXTRANEOUS_USERNAME_TOKEN = 0x6;
  EMPTY_USER_PASSWORD = 0x7;
  DUPLICATE_USER_EMAIL = 0x8;
}
