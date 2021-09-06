#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// defines pins numbers
const int stepPin = D5;
const int dirPin = D2;
const int enPin = D8;

void setup() {
  Serial.begin(115200);
  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

}
void loop() {
  Serial.println("input degree:");
  while(Serial.available()) {
    String degree = Serial.readString();
    int a = degree.toInt();
    rotation(a);
    Serial.println("rotate");
  }
  delay(1000);

}

void rotation(int deg) {

  if (deg == 180) {
    Serial.println("rotate 180 deg");
    delay(2000);
    digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for (int x = 1; x <= 100; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
    delay(10000); // One second delay

    digitalWrite(dirPin, LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for (int x = 1; x <= 100; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
  }
  else if (deg == 90) {
    Serial.println("rotate 90 deg");
    delay(2000);
    digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for (int x = 1; x <= 50; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
    delay(10000); // One second delay

    digitalWrite(dirPin, LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for (int x = 1; x <= 50; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
  }
  else if (deg == 45) {
    Serial.println("rotate 45 deg");
    delay(2000);
    digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for (int x = 1; x <= 25; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
    delay(10000); // One second delay

    digitalWrite(dirPin, LOW); //Changes the rotations direction
    // Makes 400 pulses for making two full cycle rotation
    for (int x = 1; x <= 25; x++) {
      digitalWrite(stepPin, HIGH);
      delay(1);
      digitalWrite(stepPin, LOW);
      delay(1);
    }
  }
  else {
    Serial.println("no degree");
    delay(2000);
  }

}
