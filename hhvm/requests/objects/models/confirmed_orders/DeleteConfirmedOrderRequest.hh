<?hh // strict

class DeleteConfirmedOrderRequest {

  const string REQUEST_OBJECT_NAME = "DeleteConfirmedOrderRequest";
  
  const string CONFIRMED_ORDER_ID_KEY = 'cid';

  public function __construct(
    private RequestField<UnsignedInt> $confirmedOrderId
  ) {}

  public function getConfirmedOrderId(): RequestField<UnsignedInt> {
    return $this->confirmedOrderId;
  }
}

class DeleteConfirmedOrderRequestBuilder {

  private ?RequestField<UnsignedInt> $confirmedOrderId;

  public function setConfirmedOrderId(?RequestField<UnsignedInt> $confirmed_order_id): this {
    $this->confirmedOrderId = $confirmed_order_id;
    return $this; 
  }

  public function build(): DeleteConfirmedOrderRequest {
    // Confirmed order id must be provided!
    if ($this->confirmedOrderId === null) {
      throw new UnsetRequestFieldException(
        DeleteConfirmedOrderRequest::REQUEST_OBJECT_NAME,
        DeleteConfirmedOrderRequest::CONFIRMED_ORDER_ID_KEY
      );
    }

    // Extrude request object
    return new DeleteConfirmedOrderRequest($this->confirmedOrderId);
  }
}
