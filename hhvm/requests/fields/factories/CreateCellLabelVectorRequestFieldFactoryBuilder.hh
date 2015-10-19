<?hh // strict

class CreateCellLabelVectorApiRequestFieldFactoryBuilder extends ObjectVectorApiRequestFieldFactoryBuilder<CreateCellLabelApiRequest> {

  public function __construct() {
    parent::__construct(new CreateCellLabelApiRequestFactory());
  }
}
