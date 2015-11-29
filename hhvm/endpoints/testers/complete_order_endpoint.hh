<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testCompleteOrderEndpoint(): void {

  $complete_order_payload = ImmMap{
    "cid" => 1,
  };
  
  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::COMPLETE_ORDER,
    $complete_order_payload
  );
}

testCompleteOrderEndpoint();
