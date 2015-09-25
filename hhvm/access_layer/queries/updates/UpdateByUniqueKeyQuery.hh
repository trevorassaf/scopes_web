<?hh // strict

class UpdateByUniqueKeyQuery {

  public function __construct(
    private UpdateQuery $updateQuery,
    private ConstraintMapToConjunctiveWhereClauseTranslator $constraintMapToConjunctiveWhereClauseTranslator
  ) {}

  public async function update(
    Table $table,
    ImmMap<string, mixed> $new_values,
    ImmMap<string, mixed> $conditions
  ): Awaitable<void> {
    // Perform fetch
    await $this->updateQuery->update(
      $table,
      $new_values,
      $this->constraintMapToConjunctiveWhereClauseTranslator
        ->translate($conditions)
    );
  }
}
