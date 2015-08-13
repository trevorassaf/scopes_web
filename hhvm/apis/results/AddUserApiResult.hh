<?hh // strict

class AddUserApiResult extends SuccessfulApiResult {

  const string USER_ID_KEY = "user-id";

  public function __construct(
    SerializerFactory $serializer_factory,
    private User $user 
  ) {
    parent::__construct($serializer_factory); 
  }

  protected function bindParametersToSerializer(
    Serializer $serializer
  ): void {
    $serializer->addParameter(
      self::USER_ID_KEY,
      $this->user->getId()->getNumber()
    );    
  }
}
