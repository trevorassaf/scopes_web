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

  // Create regular allowed times
  $create_regular_time_method = $method_injector->getCreateRegularTimeMethod();

  $regular_time = $create_regular_time_method->create(
    new Time("9:00:00"),
    new Time("17:00:00")
  );

  // Create M-F week days
  $active_days_of_the_week = ImmVector{
    DayOfTheWeekType::MONDAY,
    DayOfTheWeekType::TUESDAY,
    DayOfTheWeekType::WEDNESDAY,
    DayOfTheWeekType::THURSDAY,
    DayOfTheWeekType::FRIDAY,
  };

  $create_regular_week_days_method = $method_injector->getCreateRegularWeekDayMethod();
  $create_regular_edge_method = $method_injector->getCreateRegularEdgeMethod();

  foreach ($active_days_of_the_week as $day) {
    // Insert regular day
    $regular_day = $create_regular_week_days_method->create($day);

    // Bind regular week day to regular time
    $create_regular_edge_method->create(
      $regular_day->getId(),
      $regular_time->getId()
    ); 
  }
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
