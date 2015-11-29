<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testUploadBasicVideosEndpoint(): void {

  $create_user_payload = ImmMap{
    "user-id" => 1,
    "completed-order-id" => 1,
    "videos" => array(
      array(
        "title" => "Video1", 
        "duration" => "1:00:00",
        "filename" => "video1.mp4",
        "description" => "video1",
      ),
      array( 
        "title" => "Video1", 
        "duration" => "1:00:00",
        "filename" => "video1.mp4",
        "description" => "video1",
      ),
      array( 
        "title" => "Video1", 
        "duration" => "1:00:00",
        "filename" => "video1.mp4",
        "description" => "video1",
      ),
      array( 
        "title" => "Video1", 
        "duration" => "1:00:00",
        "filename" => "video1.mp4",
        "description" => "video1",
      ),
      array( 
        "title" => "Video1", 
        "duration" => "1:00:00",
        "filename" => "video1.mp4",
        "description" => "video1",
      ),
    ), 
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::UPLOAD_BASIC_VIDEOS,
    $create_user_payload
  );
}

testUploadBasicVideosEndpoint();

