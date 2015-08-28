<?hh // strict

class DebugApiRunnerFactory extends ProductionApiRunnerFactory {

  public function __construct() {
    parent::__construct();
    $this->displayRequestFieldErrors = new ServerState<bool>(true);
  }
}
