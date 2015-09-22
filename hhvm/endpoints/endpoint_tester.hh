<?hh // decl

function endpointTesterMain(): void {

  var_dump(ini_get('error_log'));

  $url = "www.organicdump.com/scopes_web/hhvm/endpoints/endpoint.hh";

  $post_params = ImmMap{
    "user_id" => 1
  };

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
