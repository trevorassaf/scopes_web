<?hh // strict

class DeleteReservedOrderRequest {

  const string REQUEST_OBJECT_NAME = "ReserveOrderRequest";
  
  const string RSVD_ORDER_ID_KEY = "rid";

  public function __construct(
    private RequestField<UnsignedInt> $rsvdOrderId
  ) {}

  public function getReservedOrderId(): RequestField<UnsignedInt> {
    return $this->rsvdOrderId;
  }
}

class DeleteReservedOrderRequestBuilder {

  private ?RequestField<UnsignedInt> $rsvdOrderId;

  public function setReservedOrderId(RequestField<UnsignedInt> $id): this {
    $this->rsvdOrderId = $id;
    return $this;
  }

  public function build(): DeleteReservedOrderRequest {
    if ($this->rsvdOrderId === null) {
      throw new UnsetRequestFieldException(
        DeleteReservedOrderRequest::REQUEST_OBJECT_NAME,
        DeleteReservedOrderRequest::RSVD_ORDER_ID_KEY
      );
    }    

    return new DeleteReservedOrderRequest($this->rsvdOrderId);
  }
}
