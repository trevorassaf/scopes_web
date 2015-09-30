<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testReserveOrderEndpoint(): void {
  
  $reserve_order_payload = ImmMap{
    "user-id" => 1,
    "scopes-count" => 5,
    "start-time"=> "2016-1-1 10:00:00",
    "end-time"=> "2016-1-1 10:30:00",
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::RESERVE_ORDER,
    $reserve_order_payload
  );
}

testReserveOrderEndpoint();
