<?php
  // Some Web page in PHP
  require_once(__DIR__ . "/cosign.php");
  if (cosign_auth()) {  // Authentication OK
    echo "Authenticated as ".$_SERVER['REMOTE_USER'];
  } else {
    // Authentication failure
    echo "Not authenticated";
    die();
  }
