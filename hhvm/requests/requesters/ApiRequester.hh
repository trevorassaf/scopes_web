<?hh // strict

class ApiRequester {

  const string URL = "www.organicdump.com/scopes_web/hhvm/endpoints/endpoint.hh";
  
  public function executeRequest(
    ApiType $type,
    ImmMap<string, mixed> $request
  ): string {
    $request_map = $request->toMap();
    $request_map[RequestWrapper::API_TYPE_KEY] = (int)$type;

    echo "REQUEST FIELD MAP:\n";
    var_dump($request_map->toArray());
    
    $curl = curl_init();
    curl_setopt_array(
      $curl,
      array(
        CURLOPT_RETURNTRANSFER => 1,
//        CURLOPT_HTTPHEADER => array('Content-Type: multipart/form-data'),
        CURLOPT_URL => self::URL,
        CURLOPT_USERAGENT => 'Testing scopes web',
        CURLOPT_POST => 1,
        CURLOPT_POSTFIELDS => http_build_query($request_map->toArray()),
      )
    ); 

    $resp = curl_exec($curl);

    echo "RESPONSE FIELD MAP:\n";
    var_dump($resp);

    return $resp;
  }
}
