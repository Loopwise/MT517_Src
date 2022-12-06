#ifndef freq
#define freq 10000
#endif

#ifndef resolution
#define resolution 12
#endif

class MotorDC{
private:
  byte EN1, EN2, ENM;
  byte ENCA, ENCB;
  byte ENM_channel;
  unsigned int t = 0;
  float PPR, velocityA = 0, velocityB = 0;
  float RPMA = 0;
  int signo = 1;

public:
  volatile int contA = 0;
  volatile int contB = 0;
  volatile float pos = 0;

  MotorDC();
  MotorDC(byte ENM, byte EN1, byte EN2, byte ENCA, byte ENCB);

  void begin(float PPR);
  void setup(byte ENM_channel, void (*ISR_A)(void), void (*ISR_B)(void));
  void start(bool state);

  void set_DutyCycle(int value);
  float get_VelocityA();
  float get_VelocityB();

  float get_RPMA();
  float get_Position();
};