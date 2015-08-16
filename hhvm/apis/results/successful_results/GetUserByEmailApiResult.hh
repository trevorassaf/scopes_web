<?hh // strict

class GetUserByEmailApiResult extends SuccessfulApiResult {

  const string USER_ID_KEY = "user-id";
  const string FIRST_NAME_KEY = "first-name";
  const string LAST_NAME_KEY = "last-name";
  const string DATE_JOINED_KEY = "date-joined";

  public function __construct(
    SerializerFactory $serializer_factory,
    private User $user
  ) {
    parent::__construct($serializer_factory);
  }

  protected function bindParametersToSerializer(
    Serializer $serializer
  ): void {
    // Add user-id
    $serializer->addParameter(
      self::USER_ID_KEY,
      $this->user->getId()->getNumber()
    );

    // Add first-name
    $serializer->addParameter(
      self::FIRST_NAME_KEY,
      $this->user->getFirstName()
    );

    // Add last-name
    $serializer->addParameter(
      self::LAST_NAME_KEY,
      $this->user->getLastName()
    );
    
    // Add date-joined 
    $serializer->addParameter(
      self::DATE_JOINED_KEY,
      $this->user->getTimeJoined()->toString()
    );
  }
}
