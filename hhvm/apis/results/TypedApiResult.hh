<?hh // strict

abstract class TypedApiResult implements ApiResult {

  const RESULT_TYPE_KEY = "result-type";

  public function __construct(
    private SerializerFactory $serializerFactory
  ) {}

  abstract protected function getResultType(): ApiResultType;
  
  abstract protected function bindParametersToSerializer(
    Serializer $serializer
  ): void;

  public function serialize(): string {
    $serializer = $this->serializerFactory->get();
    $this->bindParametersToSerializer($serializer);
    $serializer->addParameter(
      self::RESULT_TYPE_KEY,
      $this->getResultType()
    );
    return $serializer->serialize();
  }
}
