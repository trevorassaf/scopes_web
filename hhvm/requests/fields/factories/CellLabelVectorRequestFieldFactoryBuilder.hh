<?hh // strict

class CellLabelVectorRequestFieldFactoryBuilder extends ObjectVectorRequestFieldFactoryBuilder<CellLabelRequest> {

  public function __construct() {
    parent::__construct(new CellLabelRequestFactory());
  }
}
