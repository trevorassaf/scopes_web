<?hh // strict

class CreateCellLabelVectorRequestFieldFactoryBuilder extends ObjectVectorRequestFieldFactoryBuilder<CreateCellLabelRequest> {

  public function __construct() {
    parent::__construct(new CreateCellLabelRequestFactory());
  }
}
