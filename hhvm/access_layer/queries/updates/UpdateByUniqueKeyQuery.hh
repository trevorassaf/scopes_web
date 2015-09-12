<?hh // strict

class UpdateByUniqueKeyQuery {

  public function __construct(
    private UpdateQuery $updateQuery,
    private Table $table,
    private ConstraintMapToConjunctiveWhereClauseTranslator $constraintMapToConjunctiveWhereClauseTranslator
  ) {}

  public async function update(
    ImmMap<string, mixed> $new_values,
    ImmMap<string, mixed> $conditions
  ): Awaitable<void> {
    // Perform fetch
    await $this->updateQuery->update(
      $new_values,
      $this->constraintMapToConjunctiveWhereClauseTranslator
        ->translate($conditions)
    );
  }
}
