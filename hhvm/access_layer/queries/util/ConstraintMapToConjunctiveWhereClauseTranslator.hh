<?hh // strict

class ConstraintMapToConjunctiveWhereClauseTranslator {

  public function translate(
    ImmMap<string, mixed> $constraint_map
  ): WhereClause {
    $where_clause_vector_builder = new WhereClauseVectorBuilder(); 
    foreach ($constraint_map as $key => $value) {
      $equals_clause = new EqualsWhereClause($key, (string)$value);
      if (!$where_clause_vector_builder->hasFirstClause()) {
        $where_clause_vector_builder->setFirstClause($equals_clause); 
      } else {
        $where_clause_vector_builder->logicalAnd($equals_clause);
      }
    }
    return $where_clause_vector_builder->build();
  } 
}
