<?hh // strict

class GetUsersCompletedOrdersMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery,
    private FetchCompletedOrderByConfirmedOrderQuery $fetchCompletedOrderByConfirmedOrderQuery
  ) {}
    
  public function get(UnsignedInt $user_id): ImmVector<CompletedOrder> {
    try {
      // Check that user exists
      $fetch_user_handle = $this->fetchUserByIdQuery->fetch($user_id);

      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException();
      }

      // Fetch confirmed orders owned by this user
      $fetch_confirmed_orders_handle = $this->fetchUsersConfirmedOrdersQuery->fetch(
        $user_id
      );

      $confirmed_order_list = $fetch_confirmed_orders_handle
        ->getWaitHandle()
        ->join();

      // Fetch corresponding completed orders
      $completed_order_list = Vector{};

      foreach ($confirmed_order_list as $confirmed_order) {
        $fetch_completed_order_handle = $this->fetchCompletedOrderByConfirmedOrderQuery->fetch(
          $confirmed_order->getId()
        );

        $completed_order = $fetch_completed_order_handle
          ->getWaitHandle()
          ->join();

        if ($completed_order !== null) {
          $completed_order_list[] = $completed_order;
        }
      }

      return $completed_order_list->toImmVector();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
