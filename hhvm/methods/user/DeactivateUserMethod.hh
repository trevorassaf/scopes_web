<?hh // strict

class DeactivateUserMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private UpdateByIdQuery $updateByIdQuery,
    private UsersTable $usersTable,
    private DeleteUsersRsvdOrdersMethod $deleteUsersRsvdOrdersMethod,
    private DeleteUsersFutureConfirmedOrdersMethod $deleteUsersConfirmedOrdersMethod,
    private FetchUsersConfirmedOrdersQuery $fetchUsersConfirmedOrdersQuery,
    private DeleteBasicVideoGroupMethod $deleteBasicVideoGroupMethod
  ) {}

  public function deactivate(UnsignedInt $user_id): void {
    try {
      // Check that user exists 
      $fetch_handle = $this->fetchUserByIdQuery->fetch($user_id);

      $user = $fetch_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException();
      }

      // Unset the 'isActive' bit
      $update_handle = $this->updateByIdQuery->update(
        $this->usersTable,
        ImmMap{
          $this->usersTable->getIsActiveKey() => false, 
        }, 
        $user_id
      );

      $update_handle->getWaitHandle()->join();

      // Delete scheduled reserved orders and confirmed orders
      $this->deleteUsersRsvdOrdersMethod->delete($user_id);
      $this->deleteUsersConfirmedOrdersMethod->delete($user_id);

      // Fetch remaining confirmed orders (those that have already transpired)
      $fetch_remaining_confirmed_orders_handle = $this->fetchUsersConfirmedOrdersQuery->fetch(
        $user_id
      );

      $remaining_confirmed_orders = $fetch_remaining_confirmed_orders_handle
        ->getWaitHandle()
        ->join();

      // Delete basic-videos and edited-videos
      foreach ($remaining_confirmed_orders as $order) {
        $this->deleteBasicVideoGroupMethod->delete($order->getId());
      }
      

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
