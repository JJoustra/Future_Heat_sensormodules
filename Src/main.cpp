#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
bool a = true;

void loop() {
  //als ik hier meer dan 10 regels zie dan doe ik jullie wat aan
  a = !a;
  Serial.println(a);
}