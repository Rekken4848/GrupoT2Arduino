#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial
#include <math.h>

#define pinVgas 5
#define pinVref 28
#define pinVtemp 29

void setup() {
  // put your setup code here, to run once:
  pinMode(pinVgas, INPUT);
  pinMode(pinVref, INPUT);
  pinMode(pinVtemp, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(temp(general_code_to_voltage(analogRead(pinVtemp))));
  delay(1500);
}

double general_code_to_voltage(int pinValue) {
  return ( pinValue / pow(2, 12) ) * 3.3;
}

double temp(double Vtemp) {
  return ( Vtemp *87 ) -18;
}