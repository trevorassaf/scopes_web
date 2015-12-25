<?hh // strict

class GetUsersShortCodesMethod {

  public function __construct(
    private FetchByIdQuery<User> $fetchUserByIdQuery,
    private FetchUserShortCodesQuery $fetchUserShortCodesQuery
  ) {}

  public function getShortCodes(UnsignedInt $user_id): ImmVector<ShortCode> {
    try {
      // Check that user exists
      $fetch_user_handle = $this->fetchUserByIdQuery->fetch($user_id);

      $user = $fetch_user_handle
        ->getWaitHandle()
        ->join();

      if ($user === null) {
        throw new NonextantObjectException();
      }

      // Fetch all short codes associated with this user
      $fetch_user_handle = $this->fetchUserShortCodesQuery->fetch($user_id);

      return $fetch_user_handle
        ->getWaitHandle()
        ->join();

    } catch (QueryException $ex) {
      throw new FailedQueryMethodException($ex);
    }
  }
}
