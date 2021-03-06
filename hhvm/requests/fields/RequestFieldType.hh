<?hh // strict

enum RequestFieldType : int {
  INT = 0x0;
  UNSIGNED_INT = 0x1;
  BOOL = 0x2;
  FLOAT = 0x3;
  STRING = 0x4;
  EMAIL = 0x5;
  TIMESTAMP = 0x6;
  API_TYPE = 0x7;
  VECTOR = 0x8;
  OBJECT_VECTOR = 0x9;
  MAP = 0xA;
  TIME = 0xB;
  UNSIGNED_FLOAT = 0xC;
}
