<?hh // strict

class CellLabelVectorApiRequestFieldFactoryBuilder extends ObjectVectorApiRequestFieldFactoryBuilder<CreateCellLabelApiRequest> {

  public function __construct() {
    parent::__construct(new CreateCellLabelApiRequestFactory());
  }
}
