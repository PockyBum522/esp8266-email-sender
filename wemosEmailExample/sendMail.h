#include <ESP8266HTTPClient.h>

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

void sendMail(String addressTo, String subject, String body, bool serialEcho) {
  HTTPClient http;

  if (serialEcho) {
    Serial.print("[HTTP] begin...\n");
  }

  subject = urlencode(subject);
  body = urlencode(body);

  String request = "http://yourwebsite.com/mailer.php?to=" + addressTo + "&subject=" + subject + "&body=" + body;

  if (serialEcho) {
    Serial.print("Connecting to: ");
    Serial.println(request);
  }

  http.begin(request); //HTTP

  if (serialEcho) {
    Serial.print("[HTTP] GET...\n");
  }
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    if (serialEcho) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      if (serialEcho) {
        Serial.println(payload);
      }
    }
  } else {
    if (serialEcho) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  }

  http.end();

}

void sendMMS(String phoneNumber, String subject, String body, String carrier, bool serialEcho) {
  HTTPClient http;

  if (serialEcho) {
    Serial.print("[HTTP] begin...\n");
  }

  // Add your carrier and the postfix after the @
  if (carrier == "T-Mobile") {
    carrier = "@tmomail.net";
  } else if (carrier == "AT&T") {
    carrier = "@txt.att.net";
  } else {
    Serial.println("Unknown carrier");
  }

  subject = urlencode(subject);
  body = urlencode(body);

  String request = "http://yourwebsite.com/mailer.php?to=" + phoneNumber + carrier + "&subject=" + subject + "&body=" + body;

  if (serialEcho) {
    Serial.print("Connecting to: ");
    Serial.println(request);
  }

  http.begin(request); //HTTP

  if (serialEcho) {
    Serial.print("[HTTP] GET...\n");
  }
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    if (serialEcho) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      if (serialEcho) {
        Serial.println(payload);
      }
    }
  } else {
    if (serialEcho) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  }

  http.end();
}
