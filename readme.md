Wemos/ESP8266 E-Mailer/MMS Sender

v1.0        Author: pockybum522

To use:
    
    Place mailer.php onto a PHP-enabled webserver.

    Change the two URLs in sendMail.h to point to where you put that PHP file.
    
    To send an E-Mail, use sendMail("email@whoever.com", "Subject", "Body", 1);
    (The 1 signals verbose serial output.)
    
    To send an MMS, use sendMMS("5555555555", "MMS Subject", "Body", "AT&T", 1);
    
    Supported carriers are so far AT&T and T-Mobile. More can be added in sendMail.h