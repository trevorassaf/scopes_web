<?php

include_once("cosign.php");

if (!cosign_auth()) {
    header("403 Not Authorized");
      exit();
}

?>
<html>
<head>Simple Cosign protected page</head>
</html>
<body>
<h1>Successfull Authentication</h1>

Your login is <b><?php echo $_SERVER['REMOTE_USER']; ?></b>

</body>
</html>
