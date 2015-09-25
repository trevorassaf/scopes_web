<?hh // strict

enum ApiType : int as int {

  CREATE_USER = 0x0;
  GET_USER = 0x1; 
  RESERVE_ORDER = 0x2;
  CONFIRM_ORDER = 0x3;
  UPDATE_CONFIRMED_ORDER = 0x4;
  UPDATE_CELL_LABEL = 0x5;

  GENERAL = 0xffff;
}
