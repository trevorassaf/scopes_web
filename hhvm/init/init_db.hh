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

  // TEST: reserve method
  initRsvdOrderPolicy($method_injector);
  initReservedOrders($method_injector);
}

function initReservedOrders(MethodInjector $method_injector): void {
  
  $reserve_order_method = $method_injector->getReserveOrderMethod();

  // Reserve orders for first user
  $date_builder = new DateBuilder();
  $time_builder = new TimeBuilder();

  $start_time = new Timestamp(
    $date_builder
      ->setYear(Year::fromInt(2015))
      ->setMonth(Month::fromInt(8))
      ->setDay(Day::fromInt(1))
      ->build(),
    $time_builder
      ->setHour(Hour::fromInt(9))
      ->build()
  );
  
  $end_time = new Timestamp(
    $date_builder->build(),
    $time_builder
      ->setHour(Hour::fromInt(17))
      ->build()
    );

  $time_segment = new TimestampSegment($start_time, $end_time);

  $rsvd_order_1 = $reserve_order_method->reserve(
    new UnsignedInt(1),
    new UnsignedInt(14),
    $time_segment
  );
  
  $rsvd_order_2 = $reserve_order_method->reserve(
    new UnsignedInt(1),
    new UnsignedInt(2),
    $time_segment
  );

  // Confirm orders
  $cell_label_requests = Vector{};

  $confirm_order_request = new ConfirmOrderRequest(
    $rsvd_order_1->getId(),
    "Title",
    "description blahblahblah",
    "shortcode",
    new UnsignedInt(90),
    $cell_label_requests->toImmVector()
  );

  $confirm_order_method = $method_injector->getConfirmOrderMethod();
  $confirmed_order = $confirm_order_method->confirm($confirm_order_request);
}

function initRegularWeekDaysAndTimes(MethodInjector $method_injector): void {

  // Create regular allowed times
  $create_regular_time_method = $method_injector->getCreateRegularTimeMethod();
  $time_builder = new TimeBuilder();

  $regular_time = $create_regular_time_method->create(
    $time_builder
      ->setHour(Hour::fromInt(9))
      ->build(),
    $time_builder
      ->setHour(Hour::fromInt(17))
      ->build()
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

function initRsvdOrderPolicy(MethodInjector $method_injector): void {

  $create_rsvd_order_policy_method = $method_injector->getCreateReservedOrderPolicyMethod();
  $create_rsvd_order_policy_method->create(new UnsignedInt(16));
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
