<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testCreateUserEndpoint(): void {

  $create_user_payload = ImmMap{
    "first-name" => "Trevor",
    "last-name" => "Assaf",
    "email" => "astrev@umich.edu",
    "password-hash" => "brownpoopsbrownpoopsbrownpoopsbrownpoops",
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::CREATE_USER,
    $create_user_payload
  );
}

testCreateUserEndpoint();
