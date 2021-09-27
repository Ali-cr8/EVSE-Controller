//Code libraries

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


//Screen Size Definition
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#define OLED_RESET     6 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

const int PilotPin = 3;
const int ChargeRequestPin = 4;
const int VehicleDetectPin = 5;
const int PowerRelay = 12;
bool VehicleDetected = false;
bool ChargeRequested = false;

int k,l;



const int led1 = 7;
const int led2 = 8;
const int led3 = 9;

void setup() {

    Serial.begin(9600);
   
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // put your setup code here, to run once:
  pinMode(PilotPin, OUTPUT);
  pinMode(11, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 180;
  OCR2B = 50;
  pinMode(ChargeRequestPin, INPUT_PULLUP);
  pinMode(VehicleDetectPin, INPUT_PULLUP);
  pinMode(PowerRelay, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(PowerRelay, LOW);
  analogWrite(PilotPin, 255);
  digitalWrite(led1, HIGH);
   Serial.begin(9600);
  Serial.println("Started"); 

}

void loop() {
  // put your main code here, to run repeatedly:
  
  CheckStatus();

  Serial.println(k);
  Serial.println(l);

  if(VehicleDetected == true){
    digitalWrite(led2, HIGH);
    analogWrite(PilotPin, 64);
    Serial.println("State B");
    l++;
    
  }

  else{
    digitalWrite(led2, LOW);
    analogWrite(PilotPin, 255);
    Serial.println("State A");
    k++;  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(20,0);
  display.println("CONNECT");
  display.println(" YOUR CAR");
  display.display();  
  }

   if(VehicleDetected == true && ChargeRequested == true){
    delay(1000);
    CheckStatus();
   if(VehicleDetected == true && ChargeRequested == true){
    digitalWrite(led3, HIGH);
    digitalWrite(PowerRelay, HIGH);
    Serial.println("State C");

    //display
    display.clearDisplay();
     display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  // Display static text
  display.println("CHARGING!");
  display.display(); 
   }
   else{
    digitalWrite(led3, LOW);
    digitalWrite(PowerRelay, LOW);
    
   display.clearDisplay();
   display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40,0);
  // Display static text
  display.println("NOT");
  display.println(" CHARGING");
  display.display(); 
   }
    
   }
   else{
    digitalWrite(led3, LOW);
    digitalWrite(PowerRelay, LOW);


   }
   }
void CheckStatus(){
  Serial.println("checking status");
   VehicleDetected = !(digitalRead(VehicleDetectPin));

    if(pulseIn(ChargeRequestPin, HIGH, 5000) > 0){
    ChargeRequested = false;
  }else{
      ChargeRequested = true; 
  }


}
