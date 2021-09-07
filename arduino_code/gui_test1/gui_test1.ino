#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

Servo myservo; //ประกาศตัวแปรแทน Servo
TFT_eSPI tft = TFT_eSPI();

int myArray[8] = {0, 45, 90, 135, 180};
int bStatus[8] = {0, 0, 0, 1, 1};
String ans1 = "p1";
String stt = "";
String id = "";
String num = "";
String block = ""; //สร้างobject
String req, user_id, _str, check_id;


#define WIFI_SSID "fuckyou"
#define WIFI_PASSWORD "kaichaiportai"

void setup() {
  connectWifi();
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  uint16_t calData[5] = { 268, 3640, 249, 3520, 7 };
  tft.setTouch(calData);
  //  tft.fillScreen(tft.color24to16(0xFFFFFF));
  //  tft.fillRoundRect(50, 60, 180, 200, 10, tft.color24to16(0x0000FF)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
  //  tft.setTextColor(tft.color24to16(0xFFFFFF));
  //  tft.setTextSize(3);
  //  tft.drawString("Borrow", 70, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)
  //  tft.fillRoundRect(270, 60, 180, 200, 10, tft.color24to16(0xF3DA03)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
  //  tft.setTextColor(tft.color24to16(0xFFFFFF));
  //  tft.setTextSize(3);
  //  tft.drawString("Deposite", 290, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)
}

void loop() {
  //ans1 = "p1";
  //Serial.println(ans1);
  if (ans1 == "p1") {
    uint16_t x, y;
    if (tft.getTouch(&x, &y)) {
      Serial.printf("Touched at (%d, %d)\n", x, y);
      tft.fillScreen(tft.color24to16(0xFFFFFF));
      tft.fillRoundRect(50, 60, 180, 200, 10, tft.color24to16(0x0000FF)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
      tft.setTextColor(tft.color24to16(0xFFFFFF));
      tft.setTextSize(3);
      tft.drawString("Borrow", 70, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)
      tft.fillRoundRect(270, 60, 180, 200, 10, tft.color24to16(0xF3DA03)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
      tft.setTextColor(tft.color24to16(0xFFFFFF));
      tft.setTextSize(3);
      tft.drawString("Deposite", 290, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)

      if ((x > 50 && x < 230) && (y > 60 && y < 250)) {
        ans1 = "b";
        Serial.println(ans1);
      }
      if ((x > 260 && x < 460) && (y > 60 && y < 250)) {
        ans1 = "d";
        Serial.println(ans1);
      }
    }
  }

  else if (ans1 == "b") {
    String ans2 = "bb_unsubmit";
    id = "";
    tft.fillScreen(tft.color24to16(0xFFFFFF));
    tft.fillRoundRect(50, 60, 180, 200, 10, tft.color24to16(0x0000FF)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(3);
    tft.drawString("Borrow", 70, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)
    tft.fillRoundRect(270, 60, 180, 200, 10, tft.color24to16(0xF3DA03)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(3);
    tft.drawString("Getting", 290, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)

    tft.fillRoundRect(40, 285, 60, 30, 10, tft.color24to16(0x248D3E));
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(2);
    tft.drawString("back", 45, 287);
    uint16_t x, y;
    if (tft.getTouch(&x, &y)) {
      if ((x > 50 && x < 230) && (y > 60 && y < 250)) {
        Serial.printf("Touched at (%d, %d)\n", x, y);
        ans1 = "bb";
        Serial.println(ans1);
        tft.fillScreen(tft.color24to16(0xFFFFFF));
        tft.setTextColor(tft.color24to16(0x0000FF));
        tft.setTextSize(3);
        tft.drawString("you borrow", 100, 20);
        tft.drawString("please input ID", 100, 45);

        //10 pin to input ID
        while (ans2 == "bb_unsubmit") {
          input_id_page();
          uint16_t w, v;
          if (tft.getTouch(&w, &v)) {
            if ((w > 20 && w < 80) && (v > 150 && v < 210)) {
              num = "1";
            }
            if ((w > 85 && w < 145) && (v > 150 && v < 210)) {
              num = "2";
            }
            if ((w > 150 && w < 210) && (v > 150 && v < 210)) {
              num = "3";
            }
            if ((w > 215 && w < 275) && (v > 150 && v < 210)) {
              num = "4";
            }
            if ((w > 280 && w < 340) && (v > 150 && v < 210)) {
              num = "5";
            }
            if ((w > 20 && w < 80) && (v > 215 && v < 275)) {
              num = "6";
            }
            if ((w > 85 && w < 145) && (v > 215 && v < 275)) {
              num = "7";
            }
            if ((w > 150 && w < 210) && (v > 215 && v < 275)) {
              num = "8";
            }
            if ((w > 215 && w < 275) && (v > 215 && v < 275)) {
              num = "9";
            }
            if ((w > 280 && w < 340) && (v > 215 && v < 275)) {
              num = "0";
            }
            if ((w > 345 && w < 450) && (v > 150 && v < 210) && (ans2 == "bb_unsubmit")) {
              ans2 = "bb_submit";
              Serial.println("submit");
              //break;
              //              tft.fillScreen(tft.color24to16(0xFFFFFF));
              //              tft.setTextColor(tft.color24to16(0x0000FF));
              //              tft.setTextSize(3);
              //              tft.drawString("wait umbrella", 100, 140);
              String req = "bb";
              send_id(req, id);
              if (check_id == "correct") {
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("Correct ID", 100, 140);
                delay(3000);
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("wait umbrella", 100, 140);
                //                borrow(id);
                break;
              } else {
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("Incorrect ID", 100, 140);
              }
              //              if ((w > 0 && w < 500) && (v > 0 && v < 500) && (ans2 == "bb_unsubmit")) {
              //                //ans1 = "p1";
              //                exit(0);
              //              }
              break;
            }
            id = id + num;
            Serial.println("id1 = " + id);
            if ((w > 345 && w < 450) && (v > 215 && v < 275)) {
              id = "";
              //tft.drawString(id, 100, 100);
              tft.fillRoundRect(10, 95, 500, 60, 10, tft.color24to16(0xFFFFFF));
              Serial.println("cancel" + id);
            }
            //            Serial.println("req = " + req);
            //            if (req == "bb") {
            //              send_id(req, id);
            //            }
            tft.setTextColor(tft.color24to16(0x0000FF));
            tft.setTextSize(3);
            tft.drawString(id, 100, 100);
          }
          ans1 = "p1";
        }
        delay(10);
        ans1 = "p1";
      }
      if ((x > 260 && x < 460) && (y > 60 && y < 250)) {
        Serial.printf("Touched at (%d, %d)\n", x, y);
        ans1 = "bg";
        Serial.println(ans1);
        tft.fillScreen(tft.color24to16(0xFFFFFF));
        tft.setTextColor(tft.color24to16(0x0000FF));
        tft.setTextSize(3);
        tft.drawString("you getting", 100, 20);
        tft.drawString("please input ID", 100, 45);

        //10 pin to input ID
        while (ans2 == "bb_unsubmit") {
          input_id_page();
          uint16_t w, v;
          if (tft.getTouch(&w, &v)) {
            if ((w > 20 && w < 80) && (v > 150 && v < 210)) {
              num = "1";
            }
            if ((w > 85 && w < 145) && (v > 150 && v < 210)) {
              num = "2";
            }
            if ((w > 150 && w < 210) && (v > 150 && v < 210)) {
              num = "3";
            }
            if ((w > 215 && w < 275) && (v > 150 && v < 210)) {
              num = "4";
            }
            if ((w > 280 && w < 340) && (v > 150 && v < 210)) {
              num = "5";
            }
            if ((w > 20 && w < 80) && (v > 215 && v < 275)) {
              num = "6";
            }
            if ((w > 85 && w < 145) && (v > 215 && v < 275)) {
              num = "7";
            }
            if ((w > 150 && w < 210) && (v > 215 && v < 275)) {
              num = "8";
            }
            if ((w > 215 && w < 275) && (v > 215 && v < 275)) {
              num = "9";
            }
            if ((w > 280 && w < 340) && (v > 215 && v < 275)) {
              num = "0";
            }
            if ((w > 345 && w < 450) && (v > 150 && v < 210) && (ans2 == "bb_unsubmit")) {
              ans2 = "bb_submit";
              Serial.println("submit");
              //break;
              //              tft.fillScreen(tft.color24to16(0xFFFFFF));
              //              tft.setTextColor(tft.color24to16(0x0000FF));
              //              tft.setTextSize(3);
              //              tft.drawString("wait umbrella", 100, 140);
              String req = "bg";
              send_id(req, id);
              if (check_id == "correct") {
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("Correct ID", 100, 140);
                delay(3000);
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("getting umbrella", 100, 140);
                //                borrow(id);
                break;
              } else {
                tft.fillScreen(tft.color24to16(0xFFFFFF));
                tft.setTextColor(tft.color24to16(0x0000FF));
                tft.setTextSize(3);
                tft.drawString("Incorrect ID", 100, 140);
              }
              //              if ((w > 0 && w < 500) && (v > 0 && v < 500) && (ans2 == "bb_unsubmit")) {
              //                //ans1 = "p1";
              //                exit(0);
              //              }
              break;
            }
            id = id + num;
            Serial.println("id1 = " + id);
            if ((w > 345 && w < 450) && (v > 215 && v < 275)) {
              id = "";
              //tft.drawString(id, 100, 100);
              tft.fillRoundRect(10, 95, 500, 60, 10, tft.color24to16(0xFFFFFF));
              Serial.println("cancel" + id);
            }
            //            Serial.println("req = " + req);
            //            if (req == "bb") {
            //              send_id(req, id);
            //            }
            tft.setTextColor(tft.color24to16(0x0000FF));
            tft.setTextSize(3);
            tft.drawString(id, 100, 100);
          }
          ans1 = "p1";
        }
        delay(10);
        ans1 = "p1";
      }
      if ((x > 40 && x < 100) && (y > 285 && y < 310)) {
        ans1 = "p1";
        //Serial.println(ans1);
      }
    }
  }

  else if (ans1 == "d") {
    tft.fillScreen(tft.color24to16(0xFFFFFF));
    tft.fillRoundRect(50, 60, 180, 200, 10, tft.color24to16(0x0000FF)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(3);
    tft.drawString("Deposite", 70, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)
    tft.fillRoundRect(270, 60, 180, 200, 10, tft.color24to16(0xF3DA03)); //วาดกล่องสี่เหลี่ยมทึบแสงขอบโค้งที่จุดเริ่มต้น (20, 60) ขนาด 100 x 100 พิกเซล ขอบโค้ง 10 พิกเซล สีขาว
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(3);
    tft.drawString("Getting", 290, 150); //แสดงข้อความ Hello ที่ตำแหน่ง (20, 20)

    tft.fillRoundRect(40, 285, 60, 30, 10, tft.color24to16(0x248D3E));
    tft.setTextColor(tft.color24to16(0xFFFFFF));
    tft.setTextSize(2);
    tft.drawString("back", 45, 287);
    uint16_t x, y;
    if (tft.getTouch(&x, &y)) {
      if ((x > 50 && x < 230) && (y > 60 && y < 250)) {
        ans1 = "dd";
        Serial.println(ans1);
        tft.fillScreen(tft.color24to16(0xFFFFFF));
        tft.setTextColor(tft.color24to16(0x0000FF));
        tft.setTextSize(3);
        tft.drawString("you deposite", 100, 100);
        tft.drawString("please scan ID", 100, 140);

        delay(10);
        ans1 = "p1";
      }
      if ((x > 260 && x < 460) && (y > 60 && y < 250)) {
        ans1 = "dg";
        Serial.println(ans1);
        tft.fillScreen(tft.color24to16(0xFFFFFF));
        tft.setTextColor(tft.color24to16(0x0000FF));
        tft.setTextSize(3);
        tft.drawString("you getting deposite", 100, 100);
        tft.drawString("please scan ID", 100, 140);
        delay(10);
        ans1 = "p1";
      }
      if ((x > 40 && x < 100) && (y > 285 && y < 310)) {
        ans1 = "p1";
        Serial.println(ans1);
      }
    }
  }
}

//}


void connectWifi() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void input_id_page() {
  uint16_t x, y;
  tft.fillRoundRect(20, 150, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("1", 42, 165);
  tft.fillRoundRect(85, 150, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("2", 110, 165);
  tft.fillRoundRect(150, 150, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("3", 175, 165);
  tft.fillRoundRect(215, 150, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("4", 239, 165);
  tft.fillRoundRect(280, 150, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("5", 304, 165);

  tft.fillRoundRect(20, 215, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("6", 42, 240);
  tft.fillRoundRect(85, 215, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("7", 110, 240);
  tft.fillRoundRect(150, 215, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("8", 175, 240);
  tft.fillRoundRect(215, 215, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("9", 239, 240);
  tft.fillRoundRect(280, 215, 60, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(3);
  tft.drawString("0", 304, 240);

  tft.fillRoundRect(345, 150, 105, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(2);
  tft.drawString("Submit", 352, 167);
  tft.fillRoundRect(345, 215, 105, 60, 10, tft.color24to16(0xF3DA03));
  tft.setTextColor(tft.color24to16(0x0000FF));
  tft.setTextSize(2);
  tft.drawString("Cancel", 352, 230);

  //id = "";
  //  uint16_t w, v;
  //  if (tft.getTouch(&w, &v)) {
  //    if ((w > 20 && w < 80) && (v > 150 && v < 210)) {
  //      num = "1";
  //    }
  //    if ((w > 85 && w < 145) && (v > 150 && v < 210)) {
  //      num = "2";
  //    }
  //    if ((w > 150 && w < 210) && (v > 150 && v < 210)) {
  //      num = "3";
  //    }
  //    if ((w > 215 && w < 275) && (v > 150 && v < 210)) {
  //      num = "4";
  //    }
  //    if ((w > 280 && w < 340) && (v > 150 && v < 210)) {
  //      num = "5";
  //    }
  //    if ((w > 20 && w < 80) && (v > 215 && v < 275)) {
  //      num = "6";
  //    }
  //    if ((w > 85 && w < 145) && (v > 215 && v < 275)) {
  //      num = "7";
  //    }
  //    if ((w > 150 && w < 210) && (v > 215 && v < 275)) {
  //      num = "8";
  //    }
  //    if ((w > 215 && w < 275) && (v > 215 && v < 275)) {
  //      num = "9";
  //    }
  //    if ((w > 280 && w < 340) && (v > 215 && v < 275)) {
  //      num = "0";
  //    }
  //    if ((w > 345 && w < 450) && (v > 150 && v < 210) && (ans2 == "bb_unsubmit")) {
  //      ans2 = "bb_submit";
  //      Serial.println("submit");
  //      //break;
  //      //              tft.fillScreen(tft.color24to16(0xFFFFFF));
  //      //              tft.setTextColor(tft.color24to16(0x0000FF));
  //      //              tft.setTextSize(3);
  //      //              tft.drawString("wait umbrella", 100, 140);
  //      String req = "bb";
  //      send_id(req, id);
  //      if (check_id == "correct") {
  //        tft.fillScreen(tft.color24to16(0xFFFFFF));
  //        tft.setTextColor(tft.color24to16(0x0000FF));
  //        tft.setTextSize(3);
  //        tft.drawString("Correct ID", 100, 140);
  //        delay(3000);
  //        tft.fillScreen(tft.color24to16(0xFFFFFF));
  //        tft.setTextColor(tft.color24to16(0x0000FF));
  //        tft.setTextSize(3);
  //        tft.drawString("wait umbrella", 100, 140);
  //        //        borrow(id);
  //        //        break;
  //      } else {
  //        tft.fillScreen(tft.color24to16(0xFFFFFF));
  //        tft.setTextColor(tft.color24to16(0x0000FF));
  //        tft.setTextSize(3);
  //        tft.drawString("Incorrect ID", 100, 140);
  //      }
  //      //              if ((w > 0 && w < 500) && (v > 0 && v < 500) && (ans2 == "bb_unsubmit")) {
  //      //                //ans1 = "p1";
  //      //                exit(0);
  //      //              }
  //      //      break;
  //    }
  //    id = id + num;
  //    Serial.println("id1 = " + id);
  //    if ((w > 345 && w < 450) && (v > 215 && v < 275)) {
  //      id = "";
  //      //tft.drawString(id, 100, 100);
  //      tft.fillRoundRect(10, 95, 500, 60, 10, tft.color24to16(0xFFFFFF));
  //      Serial.println("cancel" + id);
  //    }
  //    //            Serial.println("req = " + req);
  //    //            if (req == "bb") {
  //    //              send_id(req, id);
  //    //            }
  //    tft.setTextColor(tft.color24to16(0x0000FF));
  //    tft.setTextSize(3);
  //    tft.drawString(id, 100, 100);
  //  }
  //  //  ans1 = "p1";
}

void send_id(String req, String user_id) {
  WiFiClient client;
  HTTPClient http;
  Serial.println("req = " + req);
  Serial.println("user id = " + user_id);
  String path = user_id + "/" + req + "/kku";
  Serial.print(path);
  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
    _str = "GET /writestt/";
    _str += path;
    _str += " HTTP/1.1\r\n";
    _str += "Host: ";
    _str += "umbrellashareserver.herokuapp.com";
    _str += "\r\n";
    _str += "Connection: keep-alive\r\n\r\n";
    Serial.println(_str);
    Serial.println("can do it");
    Serial.println("connected");
    Serial.println("[Sending a request]");
    client.print(String("GET /writestt/") + path + " HTTP/1.1\r\n" +
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
        if (line == "correct ID") {
          Serial.println("Correct ID");
          check_id = "correct";
          break;
        } else {
          Serial.println("Incorrect ID");
          check_id = "";
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

//void borrow(String user_id) {
//  String umbrella_id = "1223";
//  String borrow_time = "12000";
//  String borrow_place = "KKU";
//  String getting_time = "0";
//  String getting_place = "null";
//  String stt = "borrowing";
//  WiFiClient client;
//  HTTPClient http;
//  String path = user_id + "/" + umbrella_id;
//  path += "/" + borrow_time + "/" + borrow_place;
//  path += "/" + getting_time + "/" + getting_place + "/" + stt;
//  Serial.print(path);
//  if (client.connect("umbrellashareserver.herokuapp.com", 80)) {
//    Serial.println("can do it");
//    Serial.println("connected");
//    Serial.println("[Sending a request]");
//    client.print(String("GET /borrow/") + path + " HTTP/1.1\r\n" +
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
//        ans1 = "p1";
//        break;
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
//}
