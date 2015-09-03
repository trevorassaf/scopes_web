<?hh // strict

class ApiTypeRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<ApiType> {

  public function __construct() {
    parent::__construct(new ApiTypeFieldConverter());
  }
}
