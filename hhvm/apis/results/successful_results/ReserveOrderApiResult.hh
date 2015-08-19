<?hh // strict

class ReserveOrderApiResult extends SuccessfulApiResult {

  const string ORDER_ID_KEY = "order-id";

  public function __construct(
    SerializerFactory $serializer_factory,
    private Order $order 
  ) {
    parent::__construct($serializer_factory); 
  }

  protected function bindParametersToSerializer(
    Serializer $serializer
  ): void {
    $serializer->addParameter(
      self::ORDER_ID_KEY,
      $this->order->getId()->getNumber()
    );    
  }
}
