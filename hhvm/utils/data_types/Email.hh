<?hh

class Email {

  const string EMAIL_USERNAME_TOKEN = "@";
  const string EMAIL_DOMAIN_TOKEN = ".";

  private string $address;

  public function __construct(string $address) {
    $this->validateEmailAddress($address); 
    $this->address = $address;
  }

  private function validateEmailAddress(string $address): void {
    $username_token_idx = strpos($address, self::EMAIL_USERNAME_TOKEN);

    // Throw because no '@' existed in email address string
    if ($username_token_idx === false) {
      throw new Exception(
          "Email address ({$address}) must contain '"
          . self::EMAIL_USERNAME_TOKEN . "' character!"
      ); 
    }
  
    $address_len = strlen($address); 
    $has_domain_token = false;

    // Loop through remaining email string and make sure no other '@'
    // characters appear and make sure that at least one '.' character appears
    for ($i = $username_token_idx + 1; $i < $address_len; ++$i) {
      $curr_char = susbtr($address, $i, 1);
      if ($curr_char == self::EMAIL_USERNAME_TOKEN) {
        throw new Exception(
            "Email address ({$address}) may contain at most one '"
            . self::EMAIL_USERNAME_TOKEN . "' character!"
        ); 
      }

      if ($curr_char == self::EMAIL_DOMAIN_TOKEN) {
        $has_domain_token = true; 
      }
    }

    // Throw because we didn't find a '.' in the email domain
    if (!$has_domain_token) {
      throw new Exception(
          "Email address ({$address}) must contain a '"
          . self::EMAIL_DOMAIN_TOKEN. "' character in its domain clause!"
      );
    }
  }

  public function toString(): string {
    return $this->address; 
  }
}
