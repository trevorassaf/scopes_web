<?hh // strict

class ApiRequester {

  const string URL = "www.organicdump.com/scopes_web/hhvm/endpoints/endpoint.hh";
  
  public function executeRequest(
    ApiType $type,
    ImmMap<string, mixed> $request
  ): string {
    $json_payload = json_encode($request->toArray());
    $post_params = ImmMap{
      "api-type" => (int)$type,
      "payload" => $json_payload,
    };

    echo "REQUEST FIELD MAP:\n";
    var_dump($post_params);
    
    $curl = curl_init();
    curl_setopt_array(
      $curl,
      array(
        CURLOPT_RETURNTRANSFER => 1,
        CURLOPT_URL => self::URL,
        CURLOPT_USERAGENT => 'Testing scopes web',
        CURLOPT_POST => 1,
        CURLOPT_POSTFIELDS => $post_params->toArray(),
      )
    ); 

    $resp = curl_exec($curl);

    echo "RESPONSE FIELD MAP:\n";
    var_dump($resp);

    return $resp;
  }
}
