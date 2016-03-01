<?hh // strict

enum ApiType : int as int {

  CREATE_USER = 0x0;
  GET_USER = 0x1; 
  RESERVE_ORDER = 0x2;
  CONFIRM_ORDER = 0x3;
  UPDATE_CONFIRMED_ORDER = 0x4;
  UPDATE_CELL_LABEL = 0x5;
  DELETE_CELL_LABEL = 0x6;
  DELETE_RESERVED_ORDER = 0x7;
  DELETE_CONFIRMED_ORDER = 0x8;
  GET_USERS_CONFIRMED_ORDERS = 0x9;
  UPLOAD_BASIC_VIDEO = 0xA;
  UPLOAD_EDITED_VIDEO = 0xB;
  COMPLETE_ORDER = 0xC;
  GET_ALL_USERS = 0xD;
  DEACTIVATE_USER = 0xE;
  GET_USERS_RSVD_ORDERS = 0xF;
  GET_USERS_COMPLETED_ORDERS = 0x10;
  DELETE_BASIC_VIDEO = 0x11;
  MARK_BASIC_VIDEO_DOWNLOADED = 0x12;
  GET_SESSION_INFO = 0x13;
  GET_ORDER_PRICE_POLICY = 0x14;

  GENERAL = 0xFFFF;
}
