<?hh // strict

class GetUsersConfirmedOrdersAndCellLabelsMethod {

  public function __construct(
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery,
    private FetchConfirmedOrderCellLabelsQuery $fetchConfirmedOrdersCellLabelsQuery,
    private FetchByIdQuery<User> $fetchUserById
  ) {}

  public function get(
    UnsignedInt $user_id
  ): ImmVector<ConfirmedOrderWithCellLabels> {
    // Execute fetch confirmed orders query
    $fetch_orders_query_handle = $this
      ->fetchUsersConfirmedOrdersQuery
      ->fetch($user_id);     

    // Block until we fetch confirmed orders
    $confirmed_orders = $fetch_orders_query_handle
      ->getWaitHandle()
      ->join();

    // Check to make sure user exists (only check if no confirmed orders)
    if ($confirmed_orders->isEmpty()) {
      $fetch_user_handle = $this->fetchUserById->fetch($user_id);
      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();
      if ($user === null) {
        throw new NonextantObjectException();
      }
    }

    // Loop through confirmed orders and fetch corresponding cell labels
    $confirmed_order_with_cell_labels_list = Vector{};

    foreach ($confirmed_orders as $order) {
      // Execute fetch cell-labels query
      $fetch_cell_labels_wait_handle = $this->fetchConfirmedOrdersCellLabelsQuery
        ->fetch(
          $order->getId()
        );       

      // Block until cell-labels fetch finishes
      $cell_labels = $fetch_cell_labels_wait_handle
        ->getWaitHandle()
        ->join();

      // Push confirmed order w/cell-labels
      $confirmed_order_with_cell_labels_list[] = new ConfirmedOrderWithCellLabels(
        $order,
        $cell_labels
      );
    }

    return $confirmed_order_with_cell_labels_list->toImmVector();
  }
}
