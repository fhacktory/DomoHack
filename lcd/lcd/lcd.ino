#include <LiquidCrystal.h>
#include <SPI.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define BAUDRATE 9600

int temp = 20;
int current_temp = 0;

void setup() {
 lcd.begin(16, 2);              
 lcd.setCursor(0,0);
 lcd.print(String("Domohack    ") + temp + String(" C")); 
  // Init Ethernet
 Serial.begin(BAUDRATE);
}
 
void loop() { 

 lcd.setCursor(0,1);            
 lcd_key = read_LCD_buttons();  
 
 switch (lcd_key) {
   case btnRIGHT:
     {
     lcd.print("IP 192.168.3.201");
     break;
     }
   case btnLEFT:
     {
     lcd.print("STATUS ONLINE   ");
     break;
     }
   case btnUP:
     {
     int new_temp = current_temp + 1;
     lcd.setCursor(0,0);
     lcd.print(String("Domohack    ") + new_temp + String(" C")); //
     current_temp = new_temp;
     break;
     }
   case btnDOWN:
     {
     int new_temp = current_temp - 1;
     lcd.setCursor(0,0);
     lcd.print(String("Domohack    ") + new_temp + String(" C")); 
     current_temp = new_temp;
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT          ");
     break;
     }
   case btnNONE:
     {
     lcd.print("WAITING...      ");
     break;
     }
 }
 delay(1000);

}

// read the buttons
int read_LCD_buttons() {
 adc_key_in = analogRead(0); 
 if (adc_key_in > 1000) return btnNONE; 
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}
