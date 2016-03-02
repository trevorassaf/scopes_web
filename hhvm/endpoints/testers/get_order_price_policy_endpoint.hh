<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testGetOrderPricePolicyEndpoint(): void {

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::GET_ORDER_PRICE_POLICY,
    ImmMap{}
  );
}

testGetOrderPricePolicyEndpoint();
