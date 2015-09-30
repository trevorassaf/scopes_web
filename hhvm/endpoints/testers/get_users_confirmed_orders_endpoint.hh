<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testGetUsersConfirmedOrdersEndpoint(): void {

  $get_user_payload = ImmMap{
      "uid" => "1",
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::GET_USERS_CONFIRMED_ORDERS,
    $get_user_payload
  );
}

testGetUsersConfirmedOrdersEndpoint();
