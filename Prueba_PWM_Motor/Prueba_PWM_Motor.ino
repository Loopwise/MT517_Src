// Motor A
int ENM = 14; 
int EN1 = 27; 
int EN2 = 26; 

// Setting PWM properties
const int freq = 10000; // Freq_max = 80Mhz/2^resolution
const int pwmChannel = 0;
const int resolution = 12; // Resolutions from 1 to 16 bits.
int dutyCycle = 0;

void setup() {
  // sets the pins as outputs:
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(ENM, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENM, pwmChannel);

  Serial.begin(115200);

}

void loop() {
  if(Serial.available()){
    dutyCycle = Serial.readStringUntil('\n').toInt();

    if(dutyCycle >= 0){
      digitalWrite(EN1, HIGH);
      digitalWrite(EN2, LOW);
    }else{
      digitalWrite(EN1, LOW);
      digitalWrite(EN2, HIGH);
      dutyCycle = -dutyCycle;
    }
    
  }
  ledcWrite(pwmChannel, dutyCycle);
  delay(1750);
}