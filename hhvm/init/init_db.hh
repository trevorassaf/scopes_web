<?hh // decl 

require_once(dirname(__FILE__).'/../vendor/autoload.php');

function initDbMain(): void {
  // Set server timezone
  date_default_timezone_set("America/Detroit");

  // Initialize model loader
  $production_method_injector_factory = new ProductionMethodInjectorFactory();
  $method_injector = $production_method_injector_factory->get();

  // Insert initial records to database
  initUsers($method_injector);

}

function initUsers(MethodInjector $method_injector): void {
  $create_user_method = $method_injector->getCreateUserMethod();

  // Insert Admins 
  $create_user_method->createUser(
    "Trevor",
    "Assaf",
    new Email("astrev@umich.edu"),
    "password"
  );
}

initDbMain();
