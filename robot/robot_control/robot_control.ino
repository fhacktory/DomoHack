#include <Servo.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>

#define BAUDRATE 9600
#define RFIDEnablePin 3
#define RFIDSerialRate 2400
#define RxPin 5
#define TxPin 4
#define STRING_BUFFER_SIZE 128

Servo serv1;
SoftwareSerial RFIDReader(RxPin,TxPin);

String RFIDTAG = "";
String DisplayTAG = "";

char cmd[15];
char param1[15];
char domoserver[] = "192.168.3.218";

int calibrationTime = 30;
int pirPin = 3;
const int pingPin = 7;

long inches;
long cm;
long duration;

boolean lockLow = true;
boolean takeLowTime; 

char buffer[STRING_BUFFER_SIZE]; 

byte mac[] = {  
  0x90, 0xA2, 0xDA, 0x0F, 0x3B, 0x4C };

EthernetServer server = EthernetServer(80);
EthernetClient ethclient;

void setup() {
  // Init RFID
  RFIDReader.begin(RFIDSerialRate);
  pinMode(RFIDEnablePin,OUTPUT);
  digitalWrite(RFIDEnablePin, LOW);
  // Init Serial USB
  Serial.begin(BAUDRATE);
  // Init Ethernet
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  // Init Servo
  serv1.attach(9);  
  server.begin();
}

void loop() {
  // RFID ID
  getRfid();
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  if (cm <= 10) {
    serv1.write(50);
  } else {
    serv1.write(170);
  }  
  // Service REST
  apiRobot(server);
  
}

// Get RFID ID from sensor
void getRfid() {
  if (RFIDReader.available() > 0) {
    ReadSerial(RFIDTAG);
    if ( DisplayTAG != RFIDTAG) {
      DisplayTAG=RFIDTAG;
      if (ethclient.connect(domoserver, 5000)) {
        ethclient.print("PUT /rest/rfid/");
        ethclient.print(DisplayTAG);
        ethclient.println(" HTTP/1.1");
        ethclient.println("Connection: close");
        ethclient.println();      
      }
      ethclient.stop();
      Serial.println("RFID:" + DisplayTAG);
    }
  }  
}

// Fonction to read 
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

void apiRobot(EthernetServer server) {
  EthernetClient client = server.available();
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
    client.stop();
    while(client.status() != 0){
      delay(5);
    }    
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

void handleCommand(EthernetClient client, char* cmd, char* param) {
  if (strcmp(cmd, "rfid") == 0) {
    sendRfid(client);
  } else if (strcmp(cmd, "servo") == 0) {
    commandServo(client, param);
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

void sendRfid(EthernetClient client) {
  if (DisplayTAG == "") {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connnection: close");
    client.println();
    client.println("{");
    client.print("\"rfid");
    client.print("\": ");
    client.print("\"none");
    client.println("\n}");
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

void send404(EthernetClient client) {
  client.println("HTTP/1.1 404 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body>404</body></html>");
}

void commandServo(EthernetClient client, char* param) {
  int movement = map(atoi(param), 0, 179, 50  , 180);
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.print("<html><body>");
  client.print(movement);
  client.println("</body></html>");
  
  serv1.write(movement);
  delay(1000); 
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
