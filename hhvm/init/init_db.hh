<?hh // decl

require_once(dirname(__FILE__).'/../vendor/autoload.php');

defined("NUM_ARGS") ? null : define("NUM_ARGS", 2);

function initDbMain($argv, $argc): void {
  //// Validate script arguments ////
  // Argument count
  if ($argc !== NUM_ARGS) {
    echo "ERROR: Invalid argument count. Expected number of args: " . NUM_ARGS
      . ", provided number of args: " . $argc;
    return;
  }

  // First argument: absolute system path to project root directory
  $project_root_dir = $argv[1];
  if (!file_exists($project_root_dir)) {
    echo "ERROR: Invalid path to project root: " . $project_root_dir;
    return;
  }

  if (!is_dir($project_root_dir)) {
    echo "ERROR: Project root path must be a directory: " . $project_root_dir;
    return;
  }

  //// Configure system settings ///
  // Set server timezone
  date_default_timezone_set("America/Los_Angeles");

  //// Initialize scopes web server ////
  // Initialize model loader
  $logger_factory = new LocalLoggerFactory();
  $production_method_injector_factory = new ProductionMethodInjectorFactory(
    $logger_factory->make()
  );
  $method_injector = $production_method_injector_factory->get();

  // Init policies
  initRsvdOrderPolicy($method_injector);
  initVideoUploadPolicy($method_injector, $project_root_dir);
  initVideoMimeTypes($method_injector);

  // Insert initial records to database
  initUserPrivileges($method_injector);
  initUsers($method_injector);
  initRegularWeekDaysAndTimes($method_injector);
}

function initVideoMimeTypes($method_injector): void {
  $create_video_mime_method = $method_injector->getCreateVideoMimeTypeMethod();

  $create_video_mime_method->create("mp4", "video/mp4");
  $create_video_mime_method->create("mov", "video/quicktime");
  $create_video_mime_method->create("avi", "video/x-msvideo");
  $create_video_mime_method->create("wmv", "video/x-ms-wmv");
  $create_video_mime_method->create("pdf", "application/pdf");
  $create_video_mime_method->create("docx", "application/word");
  $create_video_mime_method->create("text", "text/plain");
}

function initVideoUploadPolicy(MethodInjector $method_injector, string $project_root_dir): void {
  $make_video_upload_policy_method = $method_injector->getMakeVideoUploadPolicyMethod(); 

  $max_bytes = new UnsignedInt(0x1000000); // 1 Gigabyte (TODO will need to enlarge later)
  $basic_video_storage_path = $project_root_dir . "/files/basic_videos/";
  $edited_video_storage_path = $project_root_dir. "/files/edited_videos/";
  $web_files_param_key = "web-files-param-key";

  $make_video_upload_policy_method->make(
    $max_bytes,
    $basic_video_storage_path,
    $edited_video_storage_path,
    $web_files_param_key  
  );
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

function initUserPrivileges(MethodInjector $method_injector): void {
  // Insert user privileges
  $create_privileges_method = $method_injector->getCreateUserPrivilegesMethod();
  $create_privileges_method->createUserPrivileges();
}

function initUsers(MethodInjector $method_injector): void {
  // Insert Admins 
  $create_user_method = $method_injector->getCreateUserMethod();

  $trevor = $create_user_method->createUser(
    "Trevor",
    "Assaf",
    new Email("astrev@umich.edu")
  );

  // Insert Short Codes
  $trevors_short_code = "0xSHORT";
  $create_short_code_method = $method_injector->getCreateShortCodeMethod();

  $create_short_code_method->createShortCode(
    $trevor->getId(),
    $trevors_short_code
  );

  // Assign default privileges for 'trevor'
  $assign_privileges_method = $method_injector->getAssignUserPrivilegesMethod();
  $assign_privileges_method->assignPrivileges(
    $trevor->getId(),
    ImmSet{
      UserPrivilegeType::ADMIN,
      UserPrivilegeType::DEVELOPER,
      UserPrivilegeType::TECHNICIAN
    }
  );
}

initDbMain($argv, $argc);
