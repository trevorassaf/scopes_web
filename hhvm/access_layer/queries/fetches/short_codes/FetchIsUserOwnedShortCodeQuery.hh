<?hh // strict

class FetchIsUserOwnedShortCodeQuery {

  public function __construct(
    private FetchUserShortCodesQuery $fetchUsersShortCodesQuery
  ) {}

  public async function fetch(
    UnsignedInt $user_id,
    UnsignedInt $short_code_id
  ): Awaitable<bool> {
    // Fetch short-codes belonging to users
    $user_short_codes = await $this->fetchUsersShortCodesQuery->fetch(
      $user_id
    );

    // Check to see if short-code belongs to this user
    foreach ($user_short_codes as $code) {
      if ($code->getId()->equals($short_code_id)) {
        return true;
      }
    }

    return false;
  }
}
