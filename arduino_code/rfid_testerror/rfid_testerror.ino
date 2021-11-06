#include <SPI.h>
#include <RFID.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define SS_PIN D2
#define RST_PIN D1

RFID rfid(SS_PIN, RST_PIN);

const char* ssid     = "fuckyou";
const char* password = "kaichaiportai";

int buzzPin = D4;

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
String request;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  rfid.init();
  //  Serial.print("ESP Board MAC Address:  ");
  //  Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("WiFi connecting..");

  while ( WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected !");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Disconnected !");
  }
}

void loop()
{
  //  delay(5000);
  WiFiClient client;
  HTTPClient http;
  String node_ip1 = "F4:CF:A2:F5:B1:38";
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /getstt/")+ node_ip1 + " HTTP/1.1\r\n" +
                 "Host: " + "umbrellashareserver.herokuapp.com" + "\r\n" +
                 "Connection: keep-alive\r\n\r\n"
                );
    //    client.print(_str);
    Serial.println("[Response:]");
    int httpCode = http.GET();
    Serial.println(httpCode);
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        if (line == "bb") {
          Serial.println("Borrow");
          request = "bb";
          read_rfid(request);
        }
        else if (line == "bg") {
          Serial.println("Borrow Getting");
          request = "bg";
          read_rfid(request);
        }
        else {
          client.stop();
        }
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }

}

void read_rfid(String request) {
  delay(5000);
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      if (rfid.serNum[0] != serNum0
          && rfid.serNum[1] != serNum1
          && rfid.serNum[2] != serNum2
          && rfid.serNum[3] != serNum3
          && rfid.serNum[4] != serNum4
         ) {
        /* With a new cardnumber, show it. */
        Serial.println(" ");
        Serial.println("Card found");
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];

        String um_id = String(rfid.serNum[0]) + ':' + String(rfid.serNum[1]) + ':' + String(rfid.serNum[2]) + ':' + String(rfid.serNum[3]) + ':' + String(rfid.serNum[4]);
        Serial.println("Cardnumber:" + um_id);

        WiFiClient client;
        HTTPClient http;

        String node_ip = "F4:CF:A2:F5:B1:38";
        String path = node_ip + "/" + um_id + "/" + request;
        Serial.println("path :" + path);
        if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
          Serial.println("can do it");
          Serial.println("connected");
          Serial.println("[Sending a request]");
          client.print(String("GET /umbrella/") + path + " HTTP/1.1\r\n" +
                       "Host: " + "umbrellashareserver.herokuapp.com" + "\r\n" +
                       "Connection: keep-alive\r\n\r\n"
                      );
          //    client.print(_str);
          Serial.println("[Response:]");
          int httpCode = http.GET();
          Serial.println(httpCode);
          while (client.connected() || client.available())
          {
            if (client.available())
            {
              String line = client.readStringUntil('\n');
              Serial.println(line);
            }
          }
          Serial.println("\n[Disconnected]");
        }
        else
        {
          Serial.println("connection failed!");
          client.stop();
        }

        //Serial.println(" ");
        Serial.println("Cardnumber:");
        Serial.print("Dec: ");
        Serial.print(rfid.serNum[0], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], DEC);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], DEC);
        Serial.println(" ");

        Serial.print("Hex: ");
        Serial.print(rfid.serNum[0], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[1], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[2], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[3], HEX);
        Serial.print(", ");
        Serial.print(rfid.serNum[4], HEX);
        Serial.println(" ");
        //buzzer
        analogWrite(3, 20);
        delay(500);
        analogWrite(3, 0);
      } else {
        /* If we have the same ID, just write a dot. */
        Serial.print(".");
      }
    }
  }
  rfid.halt();
  delay(1000);
}
