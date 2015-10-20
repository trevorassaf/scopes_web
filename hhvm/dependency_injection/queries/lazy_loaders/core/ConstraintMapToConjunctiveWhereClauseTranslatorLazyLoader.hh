<?hh // strict

class ConstraintMapToConjunctiveWhereClauseTranslatorLazyLoader extends LazyLoader<ConstraintMapToConjunctiveWhereClauseTranslator> {
  
  protected function make(): ConstraintMapToConjunctiveWhereClauseTranslator {
    return new ConstraintMapToConjunctiveWhereClauseTranslator();
  }
}
