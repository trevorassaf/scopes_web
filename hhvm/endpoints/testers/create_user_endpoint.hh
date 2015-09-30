<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testCreateUserEndpoint(): void {

  $create_user_payload = ImmMap{
    "first-name" => "Alexis",
    "last-name" => "Donneys",
    "email" => "email@umich.edu",
    "password-hash" => "somepassword",
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::CREATE_USER,
    $create_user_payload
  );
}

testCreateUserEndpoint();
