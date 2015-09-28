<?hh // decl

function endpointTesterMain(): void {
  $url = "www.organicdump.com/scopes_web/hhvm/endpoints/endpoint.hh";

  $get_user_payload = ImmMap{
      "email" => "astrev@umich.edu",
  };

  $create_user_payload = ImmMap{
    "first-name" => "Trevor",
    "last-name" => "Assaf",
    "email" => "astrev@umich.edu",
    "password-hash" => "brownpoopsbrownpoopsbrownpoopsbrownpoops",
  };

  $reserve_order_payload = ImmMap{
    "user-id" => 1,
    "scopes-count" => 1,
    "start-time"=> "2016-1-1 09:00:00",
    "end-time"=> "2016-1-1 14:00:00",
  };

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

  $delete_reserved_order = ImmMap{
    "rid" => 2,
  };

  $json_payload = json_encode($delete_reserved_order->toArray());

  $post_params = ImmMap{
    "api-type" => 0x7,
    "payload" => $json_payload,
  };

  var_dump($post_params);

  $curl = curl_init();
  curl_setopt_array(
    $curl,
    array(
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_URL => $url,
      CURLOPT_USERAGENT => 'Testing scopes web',
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $post_params->toArray(),
    )
  ); 

  $resp = curl_exec($curl);
  var_dump($resp);
}

endpointTesterMain();
