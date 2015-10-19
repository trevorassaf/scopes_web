<?hh // strict

class EditedVideoOrderTable extends Table {

  const string TABLE_NAME = "EditedVideoOrders";
  const string CONFIRMED_ORDER_ID_KEY = "confirmedOrderId";
  const string RECORDING_DURATION_MINUTES_KEY = "recordingDurationMinutes";

  public function getName(): string {
    return self::TABLE_NAME;
  }

  public function getConfirmedOrderIdKey(): string {
    return self::CONFIRMED_ORDER_ID_KEY;
  }

  public function getRecordingDurationMinutesKey(): string {
    return self::RECORDING_DURATION_MINUTES_KEY;
  }
}
