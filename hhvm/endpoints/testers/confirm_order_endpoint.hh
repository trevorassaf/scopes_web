<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testConfirmOrderEndpoint(): void {

  $confirm_order_payload = ImmMap{
    "rid" => 2,
    "title" => "Title",
    "desc" => "descriptiondescription",
    "code" => "0xC5ghY",
    "duration" => 4,
    "labels" => array(
      array(
        "label" => "dmfo1",
      ),
      array(
        "label" => "dmfo2",
      )
    ),
  };

  $api_requester = new ApiRequester();
  $api_requester->executeRequest(
    ApiType::CONFIRM_ORDER,
    $confirm_order_payload
  );
}

testConfirmOrderEndpoint();
