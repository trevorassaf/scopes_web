<?hh // strict

class CreateUserRequestFactory implements RequestFactory<CreateUserRequest> {

  private RequestFieldFactory<string> $nameFieldFactory;
  private RequestFieldFactory<Email> $emailFieldFactory;
  private RequestFieldFactory<string> $passwordHashFactory;

  public function __construct() {
    // Create name field factory
    $name_field_factory_builder = new StringRequestFieldFactoryBuilder();
    $this->nameFieldFactory = $name_field_factory_builder
        ->addConstraint()
        
  }

  public function get(ImmMap<string, mixed> $raw_field_map): CreateUserRequest {}
}
