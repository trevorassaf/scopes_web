<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testDeleteReservedOrderEndpoint(): void {

  $delete_reserved_order_payload = ImmMap{
    "rid" => 2,
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::DELETE_RESERVED_ORDER,
    $delete_reserved_order_payload
  );
}

testDeleteReservedOrderEndpoint();
