<?hh // strict

class SessionKeys {

  const string USER_AGENT_ID_KEY = "user-agent-id";
  const string EXPIRATION_TIME_KEY = "expiration-time";
  const string INITIATION_TIME_KEY = "initiation-time";

  public function getUserAgentIdKey(): string {
    return self::USER_AGENT_ID_KEY;
  }

  public function getExpirationTimeKey(): string {
    return self::EXPIRATION_TIME_KEY;
  }

  public function getInitiationTimeKey(): string {
    return self::INITIATION_TIME_KEY;
  }
}
