template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }

#include "MotorDC.h"

// MotorDC(ENM, EN1, EN2, ENCA, ENCB)
MotorDC Motor1(14, 27, 26, 25, 33);
MotorDC Motor75(5, 19, 18, 22, 23);
int dutyCycle = 0;
int dC75 = 0;

const int PPR = 80*22;
const int PPR75 = 3591.84;

// Prototipos
void IRAM_ATTR ISR1_A();
void IRAM_ATTR ISR1_B();

void IRAM_ATTR ISR75_A();
void IRAM_ATTR ISR75_B();

void setup(){ 
  Motor1.begin(PPR);
  Motor1.setup(0, ISR1_A, ISR1_B);
  Motor1.start(true);

  Motor75.begin(PPR75);
  Motor75.setup(1, ISR75_A, ISR75_B);
  Motor75.start(true);

  Serial.begin(115200);
}


void loop(){
  if(Serial.available()){
    Serial << "Posicion angular: " << Motor1.get_Position() << '\n';
    dutyCycle = Serial.readStringUntil(' ').toInt();
    dC75 = Serial.readStringUntil('\n').toInt();

    if(dutyCycle >= 0)
      Motor1.start(true);
    else
      Motor1.start(false);
    
    if(dC75 >= 0)
      Motor75.start(true);
    else
      Motor75.start(false);
      
    dutyCycle = abs(dutyCycle);
    dC75 = abs(dC75);

    Motor1.set_DutyCycle(dutyCycle);
    Motor75.set_DutyCycle(dC75);
    for(int i = 0; i < 10; i++){
      Serial << "Velocidad Motor 1 en rad/s: " << Motor1.get_VelocityA() << '\n';
      Serial << "Velocidad Motor 75 en rad/s: " << Motor75.get_VelocityA() << '\n';
      Serial << "Posicion Motor 75 en Sexagesimales:" << Motor75.get_Position() << '\n';
      delay(50);
    }
  }
  dutyCycle = 0;
  Motor1.set_DutyCycle(dutyCycle);
  Motor75.set_DutyCycle(dutyCycle);

}

void IRAM_ATTR ISR1_A(){
  Motor1.contA++;
}

void IRAM_ATTR ISR1_B(){
  Motor1.contB++;
}

void IRAM_ATTR ISR75_A(){
  Motor75.contA++;
}

void IRAM_ATTR ISR75_B(){
  Motor75.contB++;
}