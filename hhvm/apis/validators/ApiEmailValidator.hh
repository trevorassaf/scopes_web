<?hh // strict

class ApiEmailValidator {
  
  const string EMAIL_USERNAME_TOKEN = "@";
  const string EMAIL_DOMAIN_TOKEN = ".";

  public function validateAddress(
    string $email_address,
  ): void {
    // We might need to throw something...
    $api_exception_builder = new ApiExceptionBuilder();

    // Check for non-empty string
    if ($email_address == '') {
      throw $api_exception_builder
        ->addApiError(ApiErrorType::EMPTY_USER_EMAIL)
        ->build();
    }

    // Check for '@' username token
    $username_token_idx = strpos($email_address, self::EMAIL_USERNAME_TOKEN);

    // Throw because no '@' existed in email address string
    if ($username_token_idx === false) {
      throw $api_exception_builder
        ->addApiError(ApiErrorType::EMAIL_MISSING_USERNAME_TOKEN)
        ->build();
    }
  
    $address_len = strlen($email_address); 
    $has_domain_token = false;

    // Loop through remaining email string and make sure no other '@'
    // characters appear and make sure that at least one '.' character appears
    for ($i = $username_token_idx + 1; $i < $address_len; ++$i) {
      $curr_char = substr($email_address, $i, 1);
      if ($curr_char == self::EMAIL_USERNAME_TOKEN) {
        throw $api_exception_builder
          ->addApiError(ApiErrorType::EMAIL_EXTRANEOUS_USERNAME_TOKEN)
          ->build();
      }

      if ($curr_char == self::EMAIL_DOMAIN_TOKEN) {
        $has_domain_token = true; 
      }
    }

    // Throw because we didn't find a '.' in the email domain
    if (!$has_domain_token) {
      throw $api_exception_builder
        ->addApiError(ApiErrorType::EMAIL_MISSING_DOMAIN_TOKEN)
        ->build();
    }
  }
}
