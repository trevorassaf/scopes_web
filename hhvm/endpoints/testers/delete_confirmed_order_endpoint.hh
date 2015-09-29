<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testDeleteConfirmedOrderEndpoint(): void {

  $delete_confirmed_order_payload = ImmMap{
    "cid" => 2,
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::DELETE_CONFIRMED_ORDER,
    $delete_confirmed_order_payload
  );
}

testDeleteConfirmedOrderEndpoint();
