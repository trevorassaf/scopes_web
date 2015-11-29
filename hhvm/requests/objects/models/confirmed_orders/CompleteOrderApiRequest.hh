<?hh // strict

class CompleteOrderApiRequest {

  const string REQUEST_OBJECT_NAME = "CompleteOrderApiRequest";

  const string CONFIRMED_ORDER_ID_KEY = "cid";

  public function __construct(
    private RequestField<UnsignedInt> $confirmedOrderId
  ) {}

  public function getConfirmedOrderId(): RequestField<UnsignedInt> {
    return $this->confirmedOrderId; 
  }
}

class CompleteOrderApiRequestBuilder {
  
  private ?RequestField<UnsignedInt> $confirmedOrderId;

  public function setConfirmedOrderId(RequestField<UnsignedInt> $confirmed_order_id): this {
    $this->confirmedOrderId = $confirmed_order_id;
    return $this;
  }

  private function checkNotNull<T>(?T $field, string $key): T {
    if ($field === null) {
      throw new UnsetRequestFieldException(
        CompleteOrderApiRequest::REQUEST_OBJECT_NAME,
        $key
      );
    }
    return $field;
  }

  public function build(): CompleteOrderApiRequest {
    return new CompleteOrderApiRequest(
      $this->checkNotNull($this->confirmedOrderId, CompleteOrderApiRequest::CONFIRMED_ORDER_ID_KEY)
    );
  }
}
