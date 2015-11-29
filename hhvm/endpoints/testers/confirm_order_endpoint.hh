<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testConfirmOrderEndpoint(): void {

  $confirm_order_payload = ImmMap{
    "rid" => 1,
    "title" => "Title",
    "desc" => "descriptiondescription",
    "code-id" => 1,
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::CONFIRM_ORDER,
    $confirm_order_payload
  );
}

testConfirmOrderEndpoint();
