<?hh // strict

class InsertShortCodeQuery {

  public function __construct(
    private InsertQuery<ShortCode> $insertQuery,
    private ShortCodeTable $shortCodesTable
  ) {}

  public async function insert(
    UnsignedInt $user_id,
    string $code,
    string $alias
  ): Awaitable<ShortCode> {
    return await $this->insertQuery->insert(
      ImmMap{
        $this->shortCodesTable->getUserIdKey() => $user_id->getNumber(),
        $this->shortCodesTable->getCodeKey() => $code,
        $this->shortCodesTable->getAliasKey() => $alias,
      }
    );
  }
}
