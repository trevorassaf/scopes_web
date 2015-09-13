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
  initRegularWeekDaysAndTimes($method_injector);

}

function initRegularWeekDaysAndTimes(MethodInjector $method_injector): void {
  $create_regular_week_days_method = $method_injector->getCreateRegularWeekDayMethod();

  // Create M-F 
  $create_regular_week_days_method->create(DayOfTheWeekType::MONDAY);
  $create_regular_week_days_method->create(DayOfTheWeekType::TUESDAY);
  $create_regular_week_days_method->create(DayOfTheWeekType::WEDNESDAY);
  $create_regular_week_days_method->create(DayOfTheWeekType::THURSDAY);
  $create_regular_week_days_method->create(DayOfTheWeekType::FRIDAY);
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
