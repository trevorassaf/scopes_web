<?hh // strict

class GetUsersConfirmedOrdersApiResult extends SuccessfulApiResult {

  const string CONFIRMED_ORDER_ID_KEY = "id";
  const string CONFIRMED_ORDER_SCOPES_COUNT_KEY = "scopes-count";
  const string CONFIRMED_ORDER_START_TIME_KEY = "start";
  const string CONFIRMED_ORDER_END_TIME_KEY = "end";
  const string CONFIRMED_ORDER_TITLE_KEY = "title";
  const string CONFIRMED_ORDER_DESCRIPTION_KEY = "description";
  const string CONFIRMED_ORDER_RECORDING_DURATION_KEY = "recording-duration";
  const string CONFIRMED_ORDER_CELL_LABELS_KEY = "cell-labels";

  const string CELL_LABEL_ID_KEY = "id";
  const string CELL_LABEL_CELL_NUMBER_KEY = "cell-number";
  const string CELL_LABEL_LABEL_KEY = "label";

  public ImmVector<ImmMap<string, mixed>> $orders;

  public function __construct(
    ImmVector<ConfirmedOrderWithCellLabels> $orders,
    TimestampSerializer $timestamp_serializer
  ) {
    parent::__construct(ApiType::GET_USERS_CONFIRMED_ORDERS);
    $order_vector = Vector{};
    foreach ($orders as $order_with_cell_labels) {
      // Cell labels
      $cell_label_vector = Vector{};
      foreach ($order_with_cell_labels->getCellLabels() as $cell_label) {
        $cell_label_vector[] = ImmMap{
          self::CELL_LABEL_ID_KEY => $cell_label->getId()->getNumber(),
          self::CELL_LABEL_CELL_NUMBER_KEY => $cell_label->getCellNumber()->getNumber(),
          self::CELL_LABEL_LABEL_KEY => $cell_label->getLabel(), 
        }; 
      }

      // Order
      $order = $order_with_cell_labels->getConfirmedOrder();
      $map = Map{
        self::CONFIRMED_ORDER_ID_KEY => $order->getId()->getNumber(),
        self::CONFIRMED_ORDER_SCOPES_COUNT_KEY => $order->getScopesCount()->getNumber(),
        self::CONFIRMED_ORDER_START_TIME_KEY => $timestamp_serializer->serialize(
          $order->getTimestampSegment()->getStart()
        ),
        self::CONFIRMED_ORDER_END_TIME_KEY => $timestamp_serializer->serialize(
          $order->getTimestampSegment()->getEnd()
        ),
        self::CONFIRMED_ORDER_TITLE_KEY => $order->getTitle(),
        self::CONFIRMED_ORDER_DESCRIPTION_KEY => $order->getDescription(),
        self::CONFIRMED_ORDER_RECORDING_DURATION_KEY => $order->getRecordingDuration()->getNumber(),
        self::CONFIRMED_ORDER_CELL_LABELS_KEY => $cell_label_vector->toImmVector()
      };
        
      $order_vector[] = $map->toImmMap(); 
    }
    $this->orders = $order_vector->toImmVector();
  }
}
