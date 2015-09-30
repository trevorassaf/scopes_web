<?hh // strict

class ApiInjector {

  private ?CreateUserApi $createUserApi;

  private ?GetUserByEmailApi $getUserApi;

  private ?ReserveOrderApi $reserveOrderApi;

  private ?ConfirmOrderApi $confirmOrderApi;

  private ?UpdateConfirmedOrderApi $updateConfirmedOrderApi;

  private ?UpdateCellLabelApi $updateCellLabelApi;

  private ?DeleteCellLabelApi $deleteCellLabelApi;

  private ?DeleteConfirmedOrderApi $deleteConfirmedOrderApi;

  private ?DeleteReservedOrderApi $deleteReservedOrderApi;

  private ?GetUsersConfirmedOrdersApi $getUsersConfirmedOrdersApi;

  public function __construct(
    private MethodInjector $methodInjector,
    private Logger $logger,
    private LazyLoader<RequestFactory<CreateUserRequest>> $createUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<GetUserByEmailRequest>> $getUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<ReserveOrderRequest>> $reserveOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<ConfirmOrderRequest>> $confirmOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<UpdateConfirmedOrderRequest>> $updateConfirmedOrderRequestLoader,
    private LazyLoader<RequestFactory<UpdateCellLabelRequest>> $updateCellLabelRequestLoader,
    private LazyLoader<RequestFactory<DeleteCellLabelRequest>> $deleteCellLabelRequestLoader,
    private LazyLoader<RequestFactory<DeleteReservedOrderRequest>> $deleteReservedOrderRequestLoader,
    private LazyLoader<RequestFactory<DeleteConfirmedOrderRequest>> $deleteConfirmedOrderRequestLoader,
    private LazyLoader<RequestFactory<GetUsersConfirmedOrdersRequest>> $getUsersConfirmedOrdersRequestLoader
  ) {}

  public function getCreateUserApi(): CreateUserApi {
    if ($this->createUserApi == null) {
      $this->createUserApi = new CreateUserApi(
        $this->createUserRequestFactoryLoader->load(),
        $this->methodInjector->getCreateUserMethod(),
        $this->logger
      ); 
    }
    return $this->createUserApi;
  }

  public function getGetUserByEmailApi(): GetUserByEmailApi {
    if ($this->getUserApi == null) {
      $this->getUserApi = new GetUserByEmailApi(
        $this->getUserRequestFactoryLoader->load(),
        $this->methodInjector->getGetUserByEmailMethod(),
        $this->logger
      );
    } 
    return $this->getUserApi;
  }

  public function getReserveOrderApi(): ReserveOrderApi {
    if ($this->reserveOrderApi === null) {
      $this->reserveOrderApi = new ReserveOrderApi(
        $this->reserveOrderRequestFactoryLoader->load(),
        $this->methodInjector->getReserveOrderMethod(),
        $this->logger
      ); 
    }
    return $this->reserveOrderApi;
  }

  public function getConfirmOrderApi(): ConfirmOrderApi {
    if ($this->confirmOrderApi === null) {
      $this->confirmOrderApi = new ConfirmOrderApi(
        $this->confirmOrderRequestFactoryLoader->load(),
        $this->methodInjector->getConfirmOrderMethod(),
        $this->logger
      );        
    }
    return $this->confirmOrderApi;
  }

  public function getUpdateConfirmedOrderApi(): UpdateConfirmedOrderApi {
    if ($this->updateConfirmedOrderApi === null) {
      $this->updateConfirmedOrderApi = new UpdateConfirmedOrderApi(
        $this->updateConfirmedOrderRequestLoader->load(),
        $this->methodInjector->getUpdateConfirmedOrderMethod(),
        $this->logger
      ); 
    }
    return $this->updateConfirmedOrderApi;
  }

  public function getUpdateCellLabelApi(): UpdateCellLabelApi {
    if ($this->updateCellLabelApi === null) {
      $this->updateCellLabelApi = new UpdateCellLabelApi(
        $this->updateCellLabelRequestLoader->load(),
        $this->methodInjector->getUpdateCellLabelMethod(),
        $this->logger
      ); 
    }
    return $this->updateCellLabelApi;
  }
  
  public function getDeleteReservedOrderApi(): DeleteReservedOrderApi {
    if ($this->deleteReservedOrderApi === null) {
      $this->deleteReservedOrderApi = new DeleteReservedOrderApi(
        $this->deleteReservedOrderRequestLoader->load(),
        $this->methodInjector->getDeleteReservedOrderMethod(),
        $this->logger
      ); 
    }
    return $this->deleteReservedOrderApi;
  }
  
  public function getDeleteConfirmedOrderApi(): DeleteConfirmedOrderApi {
    if ($this->deleteConfirmedOrderApi === null) {
      $this->deleteConfirmedOrderApi = new DeleteConfirmedOrderApi(
        $this->deleteConfirmedOrderRequestLoader->load(),
        $this->methodInjector->getDeleteConfirmedOrderMethod(),
        $this->logger
      ); 
    }
    return $this->deleteConfirmedOrderApi;
  }

  public function getDeleteCellLabelApi(): DeleteCellLabelApi {
    if ($this->deleteCellLabelApi === null) {
      $this->deleteCellLabelApi = new DeleteCellLabelApi(
        $this->deleteCellLabelRequestLoader->load(),
        $this->methodInjector->getDeleteCellLabelMethod(),
        $this->logger
      ); 
    }
    return $this->deleteCellLabelApi;
  }

  public function getGetUsersConfirmedOrdersApi(): GetUsersConfirmedOrdersApi {
    if ($this->getUsersConfirmedOrdersApi === null) {
      $this->getUsersConfirmedOrdersApi = new GetUsersConfirmedOrdersApi(
        $this->getUsersConfirmedOrdersRequestLoader->load(),
        $this->methodInjector->getGetUsersConfirmedOrdersAndCellLabelMethod(),
        $this->logger
      ); 
    }
    return $this->getUsersConfirmedOrdersApi;
  }

}
