<?hh // strict

enum ApiType : int as int {

  CREATE_USER = 0x0;
  GET_USER = 0x1; 
  RESERVE_ORDER = 0x2;
  CONFIRM_ORDER = 0x3;

  GENERAL = 0xffff;
}
