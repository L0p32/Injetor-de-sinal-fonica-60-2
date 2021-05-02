/*
  60-2 tooth CAS signal generator for bench testing Bosch Motronic ECUs.
  Connect a linear 10k potentiometer's pin 1 to VCC, pin 2 to A0, pin 3 to GND.
  TTL CAS signal output is on pin 12.
*/

int PotPin = A0;                       // the input pin for the potentiometer
int PotValue = 0;                      // variable to store the value coming from the sensor
int CASpin = 12;                       // CAS out pin
int LEDpin = 13;                       // on-board LED

void setup() {
  Serial.begin(9600);
    pinMode(CASpin, OUTPUT);
    pinMode(LEDpin, OUTPUT);
}

void loop() {
   PotValue = analogRead(PotPin);       // read the value from the potentiometer   
   digitalWrite(LEDpin,LOW);
   int PulseDelay = 50000 / PotValue;   // 50000 gives >7000 rpm which is enough
   if (PotValue > 5)                           // Stop signal output at minimum pot value
   {
     digitalWrite(LEDpin,HIGH);            // LED indicates CAS signal status
     for (int j = 0; j < 5; j++)              // Update the RPM only every few revolutions
     {
        for (int i = 0; i < 58; i++)          // 58 of the 60 teeth high/pause/low/pause cycle
         {
          digitalWrite(CASpin, HIGH);
          delayMicroseconds(PulseDelay);
          digitalWrite(CASpin, LOW);
          delayMicroseconds(PulseDelay);
         }
       for (int i = 0; i < 4; i++)            // 2 missing teeth are low for both halves of cycle
        {                             
         delayMicroseconds(PulseDelay);
        }
     }
   } 
   Serial.println(CASpin);  
}      
