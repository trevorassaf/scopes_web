<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testGetUserEndpoint(): void {

  $get_user_payload = ImmMap{
      "email" => "astrev@umich.EDU",
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::GET_USER,
    $get_user_payload
  );
}

testGetUserEndpoint();
