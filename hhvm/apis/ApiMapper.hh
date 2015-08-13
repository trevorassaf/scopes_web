<?hh // strict

enum ApiType : int {
  // User apis
  ADD_USER = 0x0;
  UPDATE_USER = 0x1;
  DELETE_USER = 0x2;
  GET_USER = 0x3;
  
  // Order apis 
  ADD_ORDER = 0x4;
  UPDATE_ORDER = 0x5;
  DELETE_ORDER = 0x6;
  GET_ORDER = 0x7;
}

class ApiMapper {

  public function loadApi(ApiType $type): Api {
    switch ($type) {
      default:
        throw new Exception("Unsupported api: " . (int)$type);
    }  
  }

}
