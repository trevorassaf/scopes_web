<?hh // strict

class EmailRequestFieldFactoryBuilder extends RequestFieldFactoryBuilder<Email> {

  public function __construct() {
    parent::__construct(new EmailRequestFieldTypeConverter());
  }
}
