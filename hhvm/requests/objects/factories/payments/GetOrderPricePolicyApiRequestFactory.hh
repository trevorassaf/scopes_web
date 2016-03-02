<?hh // strict

class GetOrderPricePolicyApiRequestFactory implements RequestFactory<GetOrderPricePolicyApiRequest> {

  public function make(
    ImmMap<string, mixed> $raw_field_map
  ): GetOrderPricePolicyApiRequest {
    if (!$raw_field_map->isEmpty()) {
      $key = $raw_field_map->firstKey();
      invariant($key !== null, "key can't be null!");

      throw new UnexpectedRequestFieldKeyException(
        __CLASS__,
        $key
      );
    }

    return new GetOrderPricePolicyApiRequest();
  }
}
