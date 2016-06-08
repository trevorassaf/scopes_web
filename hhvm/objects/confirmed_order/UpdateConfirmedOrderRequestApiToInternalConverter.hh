<?hh // strict

class UpdateConfirmedOrderRequestApiToInternalConverter {

  public function convert(
    UpdateConfirmedOrderApiRequest $api_request
  ): UpdateConfirmedOrderRequest {

    $title_request_field = $api_request->getTitle();
    $title = ($title_request_field === null)
      ? null
      : $title_request_field->get();
    
    $description_request_field = $api_request->getDescription();
    $description = ($description_request_field === null)
      ? null
      : $description_request_field->get();

    $short_code_id_request_field = $api_request->getShortCodeId();
    $short_code_id = ($short_code_id_request_field === null)
      ? null
      : $short_code_id_request_field->get();

    return new UpdateConfirmedOrderRequest(
      $api_request->getConfirmedOrderId()->get(),
      $title,
      $description,
      $short_code_id
    );  
  }
}
