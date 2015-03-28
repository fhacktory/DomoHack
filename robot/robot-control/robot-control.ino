#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <WiFi.h>

#define BAUDRATE 115200
#define RFIDEnablePin 3
#define RFIDSerialRate 2400
#define RxPin 5
#define TxPin 4

Servo monServo;
SoftwareSerial RFIDReader(RxPin,TxPin);

String RFIDTAG = "";
String DisplayTAG = "";

int ledPin13 = 13;
int mode = 0;
int status = WL_IDLE_STATUS;  

byte incomingByte;

char ssid[] = "cbrun_dev_network";
char pass[] = "monfilsquentin";

 
void setup() {
  RFIDReader.begin(RFIDSerialRate);
  pinMode(RFIDEnablePin,OUTPUT);
  digitalWrite(RFIDEnablePin, LOW);  
  Serial.begin( BAUDRATE );
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } else {
    Serial.println("Connected to network");
  }
  monServo.attach(2, 1000, 2000);
  pinMode(ledPin13, OUTPUT);
}

void loop() {  
  if (RFIDReader.available() > 0) {
    ReadSerial(RFIDTAG);
    if ( DisplayTAG != RFIDTAG) {
      DisplayTAG=RFIDTAG;
      Serial.println("RFID:" + DisplayTAG);
    }
  }
  if (Serial.available() > 0) {
    incomingByte = Serial.parseInt();
    switcher(incomingByte);
  }
  if (mode == 1 && DisplayTAG != "") {
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    int j = map(sensorValue, 0, 1023, 0, 179);
    Serial.println(j);
    monServo.write(j);
    delay(150);
  } else if (mode == 2) {
    delay(10000);
    printMacAddress();
    Serial.println("Scanning available networks...");
    listNetworks();
    mode = 0;
  }
}

void switcher(byte switchByte) {
  if (incomingByte == 2) {
    digitalWrite(ledPin13, LOW);
    mode = 2;
  } else if (incomingByte == 1) {
    digitalWrite(ledPin13, HIGH);
    mode = 1;
  } else if (incomingByte == 0) {
    digitalWrite(ledPin13, LOW);
    mode = 0;
  } 
}

void ReadSerial(String &ReadTagString)
{
  int bytesread = 0;
  int  val = 0;
  char code[10];
  String TagCode="";

  if(RFIDReader.available() > 0) {
    if((val = RFIDReader.read()) == 10) {
      bytesread = 0;
      while(bytesread<10) {
        if( RFIDReader.available() > 0) {
          val = RFIDReader.read();
          if((val == 10)||(val == 13)) {
            break;
          }
          code[bytesread] = val;
          bytesread++;
        }
      }
      if(bytesread == 10) {

        for(int x=0;x<10;x++)
        {
          TagCode += code[x];
        }
        ReadTagString = TagCode;
        while(RFIDReader.available() > 0)
        {
          RFIDReader.read();
        }

      }
      bytesread = 0;
      TagCode="";
    }
  }
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];                    

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}


