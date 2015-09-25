<?hh // strict

class ApiInjector {

  private ?CreateUserApi $createUserApi;

  private ?GetUserByEmailApi $getUserApi;

  private ?ReserveOrderApi $reserveOrderApi;

  private ?ConfirmOrderApi $confirmOrderApi;

  private ?UpdateConfirmedOrderApi $updateConfirmedOrderApi;

  public function __construct(
    private MethodInjector $methodInjector,
    private LazyLoader<RequestFactory<CreateUserRequest>> $createUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<GetUserByEmailRequest>> $getUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<ReserveOrderRequest>> $reserveOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<ConfirmOrderRequest>> $confirmOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<UpdateConfirmedOrderRequest>> $updateConfirmedOrderRequestLoader
  ) {}

  public function getCreateUserApi(): CreateUserApi {
    if ($this->createUserApi == null) {
      $this->createUserApi = new CreateUserApi(
        $this->createUserRequestFactoryLoader->load(),
        $this->methodInjector->getCreateUserMethod() 
      ); 
    }
    return $this->createUserApi;
  }

  public function getGetUserByEmailApi(): GetUserByEmailApi {
    if ($this->getUserApi == null) {
      $this->getUserApi = new GetUserByEmailApi(
        $this->getUserRequestFactoryLoader->load(),
        $this->methodInjector->getGetUserByEmailMethod() 
      );
    } 
    return $this->getUserApi;
  }

  public function getReserveOrderApi(): ReserveOrderApi {
    if ($this->reserveOrderApi === null) {
      $this->reserveOrderApi = new ReserveOrderApi(
        $this->reserveOrderRequestFactoryLoader->load(),
        $this->methodInjector->getReserveOrderMethod()        
      ); 
    }
    return $this->reserveOrderApi;
  }

  public function getConfirmOrderApi(): ConfirmOrderApi {
    if ($this->confirmOrderApi === null) {
      $this->confirmOrderApi = new ConfirmOrderApi(
        $this->confirmOrderRequestFactoryLoader->load(),
        $this->methodInjector->getConfirmOrderMethod()
      );        
    }
    return $this->confirmOrderApi;
  }

  public function getUpdateConfirmedOrderApi(): UpdateConfirmedOrderApi {
    if ($this->updateConfirmedOrderApi === null) {
      $this->updateConfirmedOrderApi = new UpdateConfirmedOrderApi(
        $this->updateConfirmedOrderRequestLoader->load(),
        $this->methodInjector->getUpdateConfirmedOrderMethod()
      ); 
    }
    return $this->updateConfirmedOrderApi;
  }

}
