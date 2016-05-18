<?php

$to = $_GET['to'];
$subject = $_GET['subject'];
$body = $_GET['body'];

mail($to, $subject, $body);

ob_start();
header("Location: /msgconfirmation.html");
ob_flush();

echo $to;
?>


