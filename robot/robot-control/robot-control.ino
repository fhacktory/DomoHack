#include <Servo.h>

#define BAUDRATE 115200

Servo monServo;

int ledPin13 = 13;
int mode = 0;

byte incomingByte;
 
void setup() {
  Serial.begin( BAUDRATE );
  monServo.attach(2, 1000, 2000);
  pinMode(ledPin13, OUTPUT);
  Serial.println("Init Complete !");
}

void loop() {
  
  if (Serial.available() > 0){
    incomingByte = Serial.parseInt();
    switcher(incomingByte);
  }
  
  if (mode == 1) {
    monServo.write(360);
  }
}

void switcher(byte switchByte) {
  if (incomingByte == 1){
    if (mode == 0){
      digitalWrite(ledPin13, HIGH);
      mode = 1;
    }
  } else {
    if (mode == 1){
      digitalWrite(ledPin13, LOW);
      mode = 0;
    }
  }
}

