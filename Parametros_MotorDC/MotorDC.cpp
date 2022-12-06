#include <Arduino.h>
#include "MotorDC.h"

MotorDC::MotorDC(){}

MotorDC::MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB){
  this -> ENM = ENM;
  this -> EN1 = EN1;
  this -> EN2 = EN2;
  this -> ENCA = ENCA;
}

void MotorDC::begin(float PPR){
  pinMode(this -> ENM, OUTPUT);
  pinMode(this -> EN1, OUTPUT);
  pinMode(this -> EN2, OUTPUT);

  pinMode(this -> ENCA, INPUT);
  pinMode(this -> ENCB, INPUT);


  this -> PPR = PPR;
}

void MotorDC::setup(byte ENM_channel, void (*ISR_A)(void), void (*ISR_B)(void)){
  this -> ENM_channel = ENM_channel;
  ledcSetup(this -> ENM_channel, freq, resolution);
  ledcAttachPin(this -> ENM, this -> ENM_channel);

  attachInterrupt(digitalPinToInterrupt(this -> ENCA), ISR_A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(this -> ENCB), ISR_B, CHANGE);

  interrupts();
}

void MotorDC::start(bool state){
  digitalWrite(this -> EN1, state);
  digitalWrite(this -> EN2, !state);
  digitalWrite(this -> ENM, LOW);

  if(state)
    this -> signo = 1;
  else
    this -> signo = -1;
}

void MotorDC::set_DutyCycle(int value){
  ledcWrite(this->ENM_channel, value);
}

float MotorDC::get_RPMA(){
  float tMax = 5;
  int dt = millis() - (this -> t);
  if(dt > tMax){
    noInterrupts();
    this -> RPMA = 1.0*(this -> contA)/(this -> PPR); // Revoluciones en tms
    this -> RPMA *= 60.0*1000.0/dt; // Revoluciones por Minuto
    this -> velocityA = 2.0*PI/60.0*(this -> RPMA); // Rad/s
    this -> pos += 360.0*(this -> signo)*(this -> contA);
    this -> t = millis();
    this -> contA = 0;
    interrupts();
  }
  return this -> RPMA;
}
float MotorDC::get_VelocityA(){
  get_RPMA();
  return this -> velocityA;
}

float MotorDC::get_Position(){
  return (this -> pos)/(this -> PPR);
}