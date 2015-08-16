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


  public function __construct(
    private AsyncMysqlConnection $asyncMysqlConnection,
    private WebParamsFetcher $webParamsFetcher,
    private ParamsValidator $paramsValidator,
    private ApiEmailValidator $apiEmailValidator,
    private SerializerFactory $serializerFactory,
    private QueryToApiExceptionConverter $queryToApiExceptionConverter,
    private ApiExceptionToApiResultErrorConverter $apiExceptionToApiResultErrorConverter
  ) {}

  public function loadApi(ApiType $type): Api {
    switch ($type) {
    case ApiType::ADD_USER:
      return new AddUserApi(
        $this->webParamsFetcher,
        $this->paramsValidator,
        $this->apiEmailValidator,
        $this->serializerFactory,
        $this->apiExceptionToApiResultErrorConverter,
        new AddUserMethod(
          $this->queryToApiExceptionConverter,
          new UserInsertQuery(
            $this->asyncMysqlConnection,
            new UsersTable() 
          )
        )
      );
      break;
      default:
        throw new Exception("Unsupported api: " . (int)$type);
    }  
  }

}
