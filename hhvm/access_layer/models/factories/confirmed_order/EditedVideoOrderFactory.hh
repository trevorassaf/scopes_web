<?hh // strict

class EditedVideoOrderFactory extends ConcreteModelFactory<EditedVideoOrder> {

  public function __construct(
    private EditedVideoOrderTable $table
  ) {}

  public function extrudeWithId(
    UnsignedInt $id,
    ImmMap<string, mixed> $params
  ): EditedVideoOrder {
    return new EditedVideoOrder(
      $id,
      new UnsignedInt((int)$params[$this->table->getConfirmedOrderIdKey()]),
      new UnsignedInt((int)$params[$this->table->getRecordingDurationMinutesKey()])
    );
  }
}
