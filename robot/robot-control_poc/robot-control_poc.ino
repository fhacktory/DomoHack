#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <WiFi.h>

#define BAUDRATE 115200
#define RFIDEnablePin 3
#define RFIDSerialRate 2400
#define RxPin 5
#define TxPin 4
#define STRING_BUFFER_SIZE 128

Servo monServo;
SoftwareSerial RFIDReader(RxPin,TxPin);

String RFIDTAG = "";
String DisplayTAG = "";

int ledPin9 = 9;
int mode = 0;
int status = WL_IDLE_STATUS;  

byte incomingByte;

char ssid[] = "fHacktory";
char pass[] = "fHacktory";

WiFiServer server(80);


char cmd[15];
char param1[15];
boolean systemArmed = true;
char buffer[STRING_BUFFER_SIZE]; 
 
void setup() {
  RFIDReader.begin(RFIDSerialRate);
  pinMode(RFIDEnablePin,OUTPUT);
  digitalWrite(RFIDEnablePin, LOW);  
  Serial.begin(BAUDRATE);
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } else {
    Serial.println("Connected to network");
    printWifiStatus();
    server.begin();
  }
  monServo.attach(2, 1000, 2000);
  pinMode(ledPin9, OUTPUT);
  Serial.print(F("Firmware Version:"));
  Serial.println(WiFi.firmwareVersion());
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
  if (mode == 1) {
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    int j = map(sensorValue, 0, 1023, 0, 179);
    Serial.println(j);
    monServo.write(j);
    delay(150);
  } else if (mode == 2) {
    listNetworks();
    Serial.println("Scanning available networks...");
    mode = 0;
  }
  apiRobot(server);
}

void switcher(byte switchByte) {
  if (incomingByte == 2) {
    digitalWrite(ledPin9, LOW);
    mode = 2;
  } else if (incomingByte == 1) {
    digitalWrite(ledPin9, HIGH);
    mode = 1;
  } else if (incomingByte == 0) {
    digitalWrite(ledPin9, LOW);
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

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void apiRobot(WiFiServer server) {
  WiFiClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true; 
    while (client.connected()) {
      if (client.available()) {
        char c;
        int bufindex = 0; // reset buffer
        buffer[0] = client.read();
        buffer[1] = client.read();
        bufindex = 2;
        // Read the first line to determin the request page
        while (buffer[bufindex-2] != '\r' && buffer[bufindex-1] != '\n') {
          // read full row and save it in buffer
          c = client.read();
          if (bufindex<STRING_BUFFER_SIZE) {
            buffer[bufindex] = c;
          }
          bufindex++;
        } 
        bufindex = 0;
        
        int nSegments = countSegments(buffer);
        char **pathsegments = parse(buffer); 

        int i = 0;
        for(i=0; i<nSegments; i++) {
          Serial.println(pathsegments[i]);
        }  
        if (c == '\n' && currentLineIsBlank) {
          handleCommand(client, pathsegments[0], pathsegments[1]);
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }         

      }
    }
    delay(1);
    client.stop();
  }  
}


int countSegments(char* str) {
  int p = 0;
  int count = 0;
  while (str[p] != '\0') {
    if (str[p] == '/') {
      count++;
    }
    p++;
  }
  // We don't want to count the / in 'HTTP/1.1'
  count--;
  return count;
} 

void send404(WiFiClient client) {
  client.println("HTTP/1.1 404 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body>404</body></html>");
}

void sendStatus(WiFiClient client) {
  // Send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connnection: close");
  client.println();
  client.println("{");
  // Output the value of each analog input pin
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    int sensorReading = analogRead(analogChannel);
    client.print("\"analog_in_");
    client.print(analogChannel);
    client.print("\": ");
    client.print(sensorReading);
    // if (analogChannel != 5) {
    client.println(",");
    // }
  }
  client.print("\"system_armed\": ");
  client.print( systemArmed );
  client.println("\n}");
} 

void sendRfid(WiFiClient client) {
  if (DisplayTAG == "") {
    send404(client);
  } else {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connnection: close");
    client.println();
    client.println("{");
    client.print("\"rfid");
    client.print("\": ");
    client.print(DisplayTAG);
    client.println("\n}");
  }   
}

void armSystem() {
  systemArmed = true;
}

void disarmSystem() {
  systemArmed = false;
} 

void handleCommand(WiFiClient client, char* cmd, char* param) {
  if (strcmp(cmd, "status") == 0) {
    Serial.println("status");
    sendStatus(client);
  } else if (strcmp(cmd, "arm") == 0) {
    armSystem();
    sendStatus(client);
    Serial.println("arm");
  } else if (strcmp(cmd, "disarm") == 0) {
    disarmSystem();
    sendStatus(client);
    Serial.println("disarm");
  } else if (strcmp(cmd, "rfid") == 0) {
    sendRfid(client);
  } else {
    send404(client);
  }
} 

char** parse(char* str) {
  char ** messages;
  messages = (char**)malloc(sizeof(char *));
  char *p;
  p = strtok(str, " ");
  unsigned int i = 0;
  while (p != NULL) {
    p = strtok(NULL, "/");
    char *sp;
    boolean last = false;
    sp = strchr(p, ' ');
    if (sp != NULL) {
      *sp++ = '\0';
      last = true;
    }
    messages[i] = p;
    i++;
    if (last) {
      break;
    }
    messages = (char**)realloc(messages, sizeof(char *) * i + 1);
  }
  messages[i] = '\0';
  return messages;
} 


