<?hh // strict

class DeactivateUserMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private UpdateByIdQuery $updateByIdQuery,
    private UsersTable $usersTable,
    private DeleteUsersRsvdOrdersMethod $deleteUsersRsvdOrdersMethod,
    private DeleteUsersFutureConfirmedOrdersMethod $deleteUsersConfirmedOrdersMethod
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

      // Delete assets: basic-videos, edited-videos, etc

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    } 
  }
}
