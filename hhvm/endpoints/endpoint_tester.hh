<?hh // decl

function endpointTesterMain(): void {
  $url = "www.organicdump.com/scopes_web/hhvm/endpoints/endpoint.hh";

  $get_user_payload = ImmMap{
      "email" => "astrev@umich.edu",
  };

  $create_user_payload = ImmMap{
    "first-name" => "Trevor",
    "last-name" => "Assaf",
    "email" => "ASTREV@umich.edu",
    "password-hash" => "brownpoopsbrownpoopsbrownpoopsbrownpoops",
  };

  $json_payload = json_encode($create_user_payload->toArray());

  $post_params = ImmMap{
    "api-type" => 0,
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
