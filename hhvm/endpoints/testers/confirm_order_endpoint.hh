<?hh // decl

require_once(dirname(__FILE__).'/../../vendor/autoload.php');

function testConfirmOrderEndpoint(): void {

  $confirm_order_payload = ImmMap{
    "rid" => 1,
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
      ),
      array(
        "label" => "dmfo3",
      ),
      array(
        "label" => "dmfo4",
      ),
      array(
        "label" => "dmfo5",
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
