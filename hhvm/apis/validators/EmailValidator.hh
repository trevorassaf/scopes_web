<?hh // strict

class EmailValidator {
  
  const string EMAIL_USERNAME_TOKEN = "@";
  const string EMAIL_DOMAIN_TOKEN = ".";

  public function validateAddress(
    string $email_address,
    MethodResultBuilder $method_result_builder
  ): void {
    // Check for '@' username token
    $username_token_idx = strpos($address, self::EMAIL_USERNAME_TOKEN);

    // Throw because no '@' existed in email address string
    if ($username_token_idx === false) {
      $method_result_builder->addMethodError(
        MethodErrorType::EMAIL_MISSING_USERNAME_TOKEN
      );
      return;
    }
  
    $address_len = strlen($address); 
    $has_domain_token = false;

    // Loop through remaining email string and make sure no other '@'
    // characters appear and make sure that at least one '.' character appears
    for ($i = $username_token_idx + 1; $i < $address_len; ++$i) {
      $curr_char = substr($address, $i, 1);
      if ($curr_char == self::EMAIL_USERNAME_TOKEN) {
        $method_result_builder->addMethodError(
          MethodErrorType::EMAIL_EXTRANEOUS_TOKEN
        );
        return;
      }

      if ($curr_char == self::EMAIL_DOMAIN_TOKEN) {
        $has_domain_token = true; 
      }
    }

    // Throw because we didn't find a '.' in the email domain
    if (!$has_domain_token) {
      $method_result_builder->addMethodError(
        MethodErrorType::EMAIL_MISSING_DOMAIN_TOKEN
      );
      return;
    }
  }
}
