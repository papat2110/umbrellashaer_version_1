#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <RFID.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define SS_PIN D2
#define RST_PIN D1

Servo myservo; //ประกาศตัวแปรแทน Servo
const char* ssid     = "fuckyou";
const char* password = "kaichaiportai";

String req, user_id, _str, check_stt, umbrella_id;
int myArray[8] = {0, 45, 90, 135, 180, 225, 270, 315};
int bStatus[8] = {0, 0, 1, 1, 1, 0, 0, 0};
//int myArray[8] = {};
//char bStatus[8] = {};
String ans1 = "";
String ans2 = "";
String stt = "";
String block = ""; //สร้างobject
String stt_id;
String um_id;
String um_stt;
String user;
String a;
int ro_deg;

RFID rfid(SS_PIN, RST_PIN);
int buzzPin = D1;

const int stepPin = 14; //clk+
const int dirPin = 4;  //cw+
const int enPin = 15;   //en+



// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;
int num = 0;
String myTime;


const long offsetTime = 25200;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int hourNow, minuteNow, secondNow;


void setup()
{
  SPI.begin();
  rfid.init();
  timeClient.begin();
  //  myservo.attach(2); // D4 (กำหนดขาควบคุม Servo)
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(115200);

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
  for (int j = 0; j < 8; j++) {
    Serial.println(bStatus[j]);
  }
  myservo.write(0);
  send_id();
  delay(2000);
}

//void check_locker() {
//  //  int myArray[8] = {};
//  //  int bStatus[8] = {};
//  WiFiClient client;
//  HTTPClient http;
//  int lc = 1;
//  String path = WiFi.macAddress();
//  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
//    Serial.println("can do it");
//    Serial.println("connected");
//    Serial.println("[Sending a request]");
//    client.print(String("GET /getlocker/") + path + " HTTP/1.1\r\n" +
//                 "Host: " + "umbrellashareserver.herokuapp.com" + "\r\n" +
//                 "Connection: keep-alive\r\n\r\n"
//                );
//    //    client.print(_str);
//    Serial.println("[Response:]");
//    int httpCode = http.GET();
//    Serial.println(httpCode);
//    while (client.connected() || client.available())
//    {
//      if (client.available())
//      {
//        String line = client.readStringUntil('\n');
//        Serial.println(line);
//        if (line.indexOf("$") != -1) {
//          //          user = line.indexOf("user id:");
//          //          char locker[30] = line;
//
//          String locker = line;
//          locker.remove(0, 3);
//          char locker_b = locker.toInt();
//          bStatus[lc] = locker_b;
//          lc = lc + 1;
//        }
//      }
//    }
//    client.stop();
//    Serial.println("\n[Disconnected]");
//  }
//  else
//  {
//    Serial.println("connection failed!");
//    client.stop();
//  }
//  //  servo_control(check_stt);
//}

void send_id() {
  WiFiClient client;
  HTTPClient http;
  //  Serial.println("req = " + req);
  //  Serial.println("user id = " + user_id);
  //  String path = user_id + "/" + req + "/kku";
  //  Serial.print(path);
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /getstt/kku") + " HTTP/1.1\r\n" +
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
        //        user = line.startsWith("user id:");
        //        user.indexOf(':')
        if (line.indexOf("$") != -1) {
          //          user = line.indexOf("user id:");
          user = line;
          Serial.println("use : " + user);
          user.remove(0, 2);
          Serial.println("use : " + user);
        }
        if (line == "bb") {
          Serial.println("Borrow");
          check_stt = "bb";
          delete_status();
          //          servo_control(check_stt);
        }
        if (line == "bg") {
          Serial.println("Borrow Getting");
          check_stt = "bg";
          delete_status();
          //          servo_control(check_stt);
        }
        if (line == "dd") {
          Serial.println("Deposite");
          check_stt = "dd";
          delete_status();
          //          servo_control(check_stt);
        }
        if (line == "dg") {
          Serial.println("Deposite Getting");
          check_stt = "dg";
          delete_status();
          //          servo_control(check_stt);
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
  //  servo_control(check_stt);

}

void delete_status() {
  servo_control(check_stt);
  WiFiClient client;
  HTTPClient http;
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /delete_stt/kku") + " HTTP/1.1\r\n" +
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
        client.stop();
      }
      client.stop();
      Serial.println("\n[Disconnected]");
    }
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }

}


void servo_control(String c_stt) {
  //  int rotate;
  //  int num;
  if (c_stt == "bg") {
    Serial.println("rotate = bg");
    for (int i = 0; i < 8; i++) {
      Serial.println(bStatus[i]);
      if (bStatus[i] == 0) {
        //        rotate = myArray[i];
        //        Serial.println("rotate = " + rotate);
        //        myservo.write(myArray[i]);

        Serial.println(myArray[i]);
        delay(5000);
        digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
        // Makes 200 pulses for making one full cycle rotation
        int ro_deg = myArray[i] / 1.8;
        for (int x = 1; x <= ro_deg; x++) {
          digitalWrite(stepPin, HIGH);
          delay(1);
          digitalWrite(stepPin, LOW);
          delay(1);
        }
        umbrella_read(i);
        break;
        delay(10000); // One second delay
        //
        //        digitalWrite(dirPin, LOW); //Changes the rotations direction
        //        // Makes 400 pulses for making two full cycle rotation
        //        for (int x = 1; x <= ro_deg; x++) {
        //          digitalWrite(stepPin, HIGH);
        //          delay(1);
        //          digitalWrite(stepPin, LOW);
        //          delay(1);
        //        }
        //        delay(20);
        //        bStatus[i] = 1;
        //        //        myservo.write(180);
        //        break;
      }
    }
  }
  else if (c_stt == "bb") {
    Serial.println("rotate = bb");
    for (int j = 0; j < 8; j++) {
      Serial.println(bStatus[j]);
      if (bStatus[j] == 1) {
        //        Serial.println("aaa = " + bStatus[i]);
        //        Serial.println("bbb = " + myArray[i]);
        //        rotate = myArray[i];
        //        Serial.println("rotate = " + rotate);
        //        myservo.write(myArray[j]);
        //        Serial.println("rotate = " + myArray[j]);
        Serial.println(myArray[j]);
        delay(5000);
        digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
        // Makes 200 pulses for making one full cycle rotation
        int ro_deg = myArray[j] / 1.8;
        for (int x = 1; x <= ro_deg; x++) {
          digitalWrite(stepPin, HIGH);
          delay(1);
          digitalWrite(stepPin, LOW);
          delay(1);
        }
        umbrella_read(j);
        break;
        delay(10000); // One second delay

        //        digitalWrite(dirPin, LOW); //Changes the rotations direction
        //        // Makes 400 pulses for making two full cycle rotation
        //        for (int x = 1; x <= ro_deg; x++) {
        //          digitalWrite(stepPin, HIGH);
        //          delay(1);
        //          digitalWrite(stepPin, LOW);
        //          delay(1);
        //        }
        //        //        umbrella_read();
        //        delay(2000);
        //        bStatus[j] = 0;
        //        //        myservo.write(180);
        //        break;
      }
    }
  }
  else if (c_stt == "dd") {
  }
  else if (c_stt == "dg") {
  }
  else {
    Serial.println(".");
  }
  //  for (int j = 0; j < 5; j++) {
  //    Serial.println(bStatus[j]);
  //  }
}

void umbrella_read(int j) {
  WiFiClient client;
  HTTPClient http;
  //  Serial.println("req = " + req);
  //  Serial.println("user id = " + user_id);
  Serial.println(WiFi.macAddress());
  String path = WiFi.macAddress();
  String umbrella_id;
  Serial.println("read rfid from other board");
  delay(3000);
  Serial.print(path);
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /get_umbrella/") + path + " HTTP/1.1\r\n" +
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
        if (line.indexOf("#") != -1) {
          //          user = line.indexOf("user id:");
          umbrella_id = line;
          Serial.println("use : " + umbrella_id);
          umbrella_id.remove(0, 1);
          Serial.println("use : " + umbrella_id);
          //          borrow_umbrella(umbrella_id);
        }
        if (line.indexOf("%%") != -1) {
          //          user = line.indexOf("user id:");
          um_stt = line;
          Serial.println("status : " + um_stt);
          um_stt.remove(0, 2);
          Serial.println("status : " + um_stt);
          if (um_stt == "bb") {
            borrow_umbrella(umbrella_id);
            bStatus[j] = 0;
            digitalWrite(dirPin, LOW); //Changes the rotations direction
            // Makes 400 pulses for making two full cycle rotation
            for (int x = 1; x <= ro_deg; x++) {
              digitalWrite(stepPin, HIGH);
              delay(1);
              digitalWrite(stepPin, LOW);
              delay(1);
            }
            //        umbrella_read();
            delay(2000);
          }
          if (um_stt == "bg") {
            getting_umbrella(umbrella_id);
            bStatus[j] = 1;
            digitalWrite(dirPin, LOW); //Changes the rotations direction
            // Makes 400 pulses for making two full cycle rotation
            for (int x = 1; x <= ro_deg; x++) {
              digitalWrite(stepPin, HIGH);
              delay(1);
              digitalWrite(stepPin, LOW);
              delay(1);
            }
          }
        }
        if (line == "error get umbrella id") {
          delete_realtime();
          digitalWrite(dirPin, LOW); //Changes the rotations direction
          // Makes 400 pulses for making two full cycle rotation
          for (int x = 1; x <= ro_deg; x++) {
            digitalWrite(stepPin, HIGH);
            delay(1);
            digitalWrite(stepPin, LOW);
            delay(1);
          }
          //        umbrella_read();
          delay(2000);
          break;
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
  //  servo_control(check_stt);

}

void borrow_umbrella(String um_id) {
  //  time_stamp
  timeClient.update();
  secondNow = timeClient.getSeconds();
  minuteNow = timeClient.getMinutes();
  hourNow = timeClient.getHours();
  String day = daysOfTheWeek[timeClient.getDay()];
  String currentTimestamp = "date:" + day + " time:" + String(hourNow) + "." + String(minuteNow);
  myTime = String(hourNow) + "." + String(minuteNow);
  Serial.println(myTime);
  delay(2000);

  String umbrella_id = um_id;
  String user_id = user;
  String borrow_place = "kku";
  String borrow_time = myTime;
  String getting_place = "none";
  String getting_time = "0";
  String b_status = "borrowing";
  String path = user_id + "/" + umbrella_id + "/" + borrow_time + "/" + borrow_place + "/" + getting_time + "/" + getting_place + "/" + b_status;
  Serial.println(path);

  WiFiClient client;
  HTTPClient http;
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /borrow/") + path + " HTTP/1.1\r\n" +
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
        client.stop();
      }
      client.stop();
      Serial.println("\n[Disconnected]");
    }
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }
  um_stt = "";
  delete_realtime();
}

void getting_umbrella(String um_id) {
  //  time_stamp
  timeClient.update();
  secondNow = timeClient.getSeconds();
  minuteNow = timeClient.getMinutes();
  hourNow = timeClient.getHours();
  String day = daysOfTheWeek[timeClient.getDay()];
  String currentTimestamp = "date:" + day + " time:" + String(hourNow) + "." + String(minuteNow);
  myTime = String(hourNow) + "." + String(minuteNow);
  Serial.println(myTime);
  delay(2000);

  String umbrella_id = um_id;
  String user_id = user;
  String getting_place = "KKU";
  String getting_time = myTime;
  String b_status = "got";
  String path = user_id + "/" + umbrella_id + "/" + getting_time + "/" + getting_place + "/" + b_status;
  Serial.println(path);

  WiFiClient client;
  HTTPClient http;
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /getborrow/") + path + " HTTP/1.1\r\n" +
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
        client.stop();
      }
      client.stop();
      Serial.println("\n[Disconnected]");
    }
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }
  um_stt = "";
  delete_realtime();

}

void delete_realtime() {
  WiFiClient client;
  HTTPClient http;
  String path = WiFi.macAddress();
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /delete_realtime/") + path + " HTTP/1.1\r\n" +
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
        client.stop();
      }
      client.stop();
      Serial.println("\n[Disconnected]");
    }
  }
  else
  {
    Serial.println("connection failed!");
    client.stop();
  }

}
