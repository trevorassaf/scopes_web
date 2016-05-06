<?hh // strict

class GetConfirmedOrderDatesMethod {

  public function __construct(
    private GetAllConfirmedOrdersMethod $getAllConfirmedOrdersMethod
  ) {}

  public function get(TimestampSegment $interval): ImmVector<Date> {
    $confirmed_orders = $this->getAllConfirmedOrdersMethod->getWithTimeInterval($interval);
    $date_list = Vector{};

    // TODO handle multi-day experiments, which we don't really allow rn
    foreach ($confirmed_orders as $order) {
      $start_timestamp = $order->getTimestampSegment()->getStart();
      $date_list[] = $start_timestamp->getDate();
    }

    return $date_list->toImmVector();
  }
}
