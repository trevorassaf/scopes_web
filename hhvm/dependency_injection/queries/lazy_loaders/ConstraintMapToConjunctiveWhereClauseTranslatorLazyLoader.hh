<?hh // strict

class ConstraintMapToConjunctiveWhereClauseLazyLoader extends LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> {
  
  protected function make(): ConstraintMapToConjunctiveWhereClauseTranslator {
    return new ConstraintMapToConjunctiveWhereClauseTranslator();
  }
}
