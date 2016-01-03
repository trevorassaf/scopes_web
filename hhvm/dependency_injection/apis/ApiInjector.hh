<?hh // strict

class ApiInjector {

  // User apis
  private ?CreateUserApi $createUserApi;
  private ?GetUserByEmailApi $getUserApi;
  private ?GetAllUsersApi $getAllUsersApi;

  // Reserved order apis
  private ?ReserveOrderApi $reserveOrderApi;
  private ?DeleteReservedOrderApi $deleteReservedOrderApi;
  private ?GetUsersReservedOrdersApi $getUsersReservedOrdersApi;

  // Confirmed order apis
  private ?ConfirmOrderApi $confirmOrderApi;
  private ?UpdateConfirmedOrderApi $updateConfirmedOrderApi;
  private ?DeleteConfirmedOrderApi $deleteConfirmedOrderApi;
  private ?GetUsersConfirmedOrdersApi $getUsersConfirmedOrdersApi;

  // Completed order apis
  private ?CompleteOrderApi $completeOrderApi;
  private ?GetUsersCompletedOrdersApi $getUsersCompletedOrdersApi;

  // Cell label apis
  private ?UpdateCellLabelApi $updateCellLabelApi;
  private ?DeleteCellLabelApi $deleteCellLabelApi;

  // Video apis
  private ?UploadBasicVideoApi $uploadBasicVideoApi;
  private ?UploadEditedVideoApi $uploadEditedVideoApi;

  // Video downlaod receipts
  private ?MarkBasicVideoDownloadedApi $markBasicVideoDownloadedApi;
  private ?DeleteBasicVideoApi $deleteBasicVideoApi;

  public function __construct(
    private MethodInjector $methodInjector,
    private Logger $logger,
    private HttpUploadedFilesFetcher $httpUploadedFileFetcher,
    private LazyLoader<RequestFactory<CreateUserRequest>> $createUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<GetUserByEmailRequest>> $getUserRequestFactoryLoader,
    private LazyLoader<RequestFactory<ReserveOrderRequest>> $reserveOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<ConfirmOrderApiRequest>> $confirmOrderRequestFactoryLoader,
    private LazyLoader<RequestFactory<UpdateConfirmedOrderRequest>> $updateConfirmedOrderRequestLoader,
    private LazyLoader<RequestFactory<UpdateCellLabelRequest>> $updateCellLabelRequestLoader,
    private LazyLoader<RequestFactory<DeleteCellLabelRequest>> $deleteCellLabelRequestLoader,
    private LazyLoader<RequestFactory<DeleteReservedOrderRequest>> $deleteReservedOrderRequestLoader,
    private LazyLoader<RequestFactory<DeleteConfirmedOrderRequest>> $deleteConfirmedOrderRequestLoader,
    private LazyLoader<RequestFactory<GetUsersConfirmedOrdersRequest>> $getUsersConfirmedOrdersRequestLoader,
    private LazyLoader<RequestFactory<CreateUploadEditedVideoApiRequest>> $createUploadEditedVideoApiRequestLoader,
    private LazyLoader<RequestFactory<CompleteOrderApiRequest>> $completeOrderApiRequestLoader,
    private LazyLoader<HRTimestampSerializer> $timestampSerializerLoader,
    private LazyLoader<TimestampBuilder> $timestampBuilderLoader,
    private LazyLoader<TimestampSegmentFactory> $timestampSegmentFactoryLoader,
    private LazyLoader<RequestFactory<GetAllUsersApiRequest>> $getAllUsersApiRequestFactoryLoader,
    private LazyLoader<RequestFactory<GetUsersReservedOrdersApiRequest>> $getUsersReservedOrdersApiRequestFactoryLoader,
    private LazyLoader<RequestFactory<GetUsersCompletedOrdersApiRequest>> $getUsersCompletedOrdersApiRequestFactoryLoader,
    private LazyLoader<RequestFactory<UploadBasicVideoApiRequest>> $uploadBasicVideoApiRequestFactoryLoader,
    private LazyLoader<RequestFactory<MarkBasicVideoDownloadedApiRequest>> $markBasicVideoDownloadedApiRequestLoader,
    private LazyLoader<RequestFactory<DeleteBasicVideoApiRequest>> $deleteBasicVideoApiRequestLoader
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
        $this->logger,
        $this->timestampSegmentFactoryLoader->load()
      ); 
    }
    return $this->reserveOrderApi;
  }

  public function getConfirmOrderApi(): ConfirmOrderApi {
    if ($this->confirmOrderApi === null) {
      $this->confirmOrderApi = new ConfirmOrderApi(
        $this->confirmOrderRequestFactoryLoader->load(),
        $this->timestampBuilderLoader->load(),
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
        $this->methodInjector->getGetUsersConfirmedOrdersMethod(),
        $this->logger,
        $this->timestampSerializerLoader->load()
      ); 
    }
    return $this->getUsersConfirmedOrdersApi;
  }

  public function getUploadBasicVideoApi(): UploadBasicVideoApi {
    if ($this->uploadBasicVideoApi === null) {
      $this->uploadBasicVideoApi = new UploadBasicVideoApi(
        $this->uploadBasicVideoApiRequestFactoryLoader->load(),
        $this->methodInjector->getUploadBasicVideoMethod(),
        $this->logger,
        $this->httpUploadedFileFetcher
      ); 
    }
    return $this->uploadBasicVideoApi;
  }

  public function getUploadEditedVideoApi() : UploadEditedVideoApi {
    if ($this->uploadEditedVideoApi === null) {
      $this->uploadEditedVideoApi = new UploadEditedVideoApi(
        $this->createUploadEditedVideoApiRequestLoader->load(),
        $this->methodInjector->getUploadEditedVideoMethod(),
        $this->logger  
      );
    }  
    return $this->uploadEditedVideoApi;   
  }

  public function getCompleteOrderApi(): CompleteOrderApi {
    if ($this->completeOrderApi === null) {
      $this->completeOrderApi = new CompleteOrderApi(
        $this->completeOrderApiRequestLoader->load(),
        $this->timestampBuilderLoader->load(),
        $this->methodInjector->getCompleteOrderMethod(),
        $this->logger
      ); 
    }
    return $this->completeOrderApi;
  }

  public function getGetUsersCompletedOrdersApi(): GetUsersCompletedOrdersApi {
    if ($this->getUsersCompletedOrdersApi === null) {
      $this->getUsersCompletedOrdersApi = new GetUsersCompletedOrdersApi(
        $this->getUsersCompletedOrdersApiRequestFactoryLoader->load(),
        $this->methodInjector->getGetUsersCompletedOrdersMethod(),
        $this->logger,
        $this->timestampSerializerLoader->load()  
      );
    }
    return $this->getUsersCompletedOrdersApi;
  }

  public function getGetAllUsersApi(): GetAllUsersApi {
    if ($this->getAllUsersApi === null) {
      $this->getAllUsersApi = new GetAllUsersApi(
        $this->getAllUsersApiRequestFactoryLoader->load(),
        $this->methodInjector->getGetAllUsersMethod(),
        $this->logger
      ); 
    }
    return $this->getAllUsersApi;
  }

  public function getGetUsersReservedOrdersApi(): GetUsersReservedOrdersApi {
    if ($this->getUsersReservedOrdersApi === null) {
      $this->getUsersReservedOrdersApi = new GetUsersReservedOrdersApi(
        $this->getUsersReservedOrdersApiRequestFactoryLoader->load(),
        $this->methodInjector->getGetUsersReservedOrdersMethod(),
        $this->logger,
        $this->timestampSerializerLoader->load()
      ); 
    }
    return $this->getUsersReservedOrdersApi;
  }

  public function getMarkBasicVideoDownloadedApi(): MarkBasicVideoDownloadedApi {
    if ($this->markBasicVideoDownloadedApi === null) {
      $this->markBasicVideoDownloadedApi = new MarkBasicVideoDownloadedApi(
        $this->markBasicVideoDownloadedApiRequestLoader->load(),
        $this->logger,
        $this->methodInjector->getMarkBasicVideoDownloadedMethod() 
      ); 
    }
    return $this->markBasicVideoDownloadedApi;
  }

  public function getDeleteBasicVideoApi(): DeleteBasicVideoApi {
    if ($this->deleteBasicVideoApi === null) {
      $this->deleteBasicVideoApi = new DeleteBasicVideoApi(
        $this->deleteBasicVideoApiRequestLoader->load(),
        $this->logger,
        $this->methodInjector->getDeleteBasicVideoMethod(),
        $this->methodInjector->getIsBasicVideoDownloadedMethod() 
      ); 
    }
    return $this->deleteBasicVideoApi;
  }

  public function getMethodInjector(): MethodInjector {
    return $this->methodInjector;
  }
}
