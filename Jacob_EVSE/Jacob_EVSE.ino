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
  }

   if(VehicleDetected == true && ChargeRequested == true){
    delay(1000);
    CheckStatus();
   if(VehicleDetected == true && ChargeRequested == true){
    digitalWrite(led3, HIGH);
    digitalWrite(PowerRelay, HIGH);
    Serial.println("State C");
   }
   else{
    digitalWrite(led3, LOW);
    digitalWrite(PowerRelay, LOW);
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
