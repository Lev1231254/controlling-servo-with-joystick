#include <ServoSmooth.h> //используем библиотеку для работы с сервоприводом

// пин подключения контакта VRX
#define PIN_VRX A0
// пин подключения контакта VRY
#define PIN_VRY A1
// пин подключения кнопки
#define PIN_BUTTON 3

int SPEED_CAP = 90;
double CONST1 = SPEED_CAP / 1024; //how much speed you should have for 1 (VRX)
double CONST2 = 1024/180; //at what angle you should turn servo for 1 (VRX)

ServoSmooth servo;

 
void setup() {
  // put your setup code here, to run once:
  
  
  servo.attach(10); //привязываем привод к порту 10
  
  servo.setAccel(0.5); //accelaration
  servo.setAutoDetach(false); //auto detaching
  servo.setSpeed(60); //speed(will be changed)
  Serial.begin (9600);
}

void loop() {
  servo.tick();

  servo.setSpeed(toSpeed(analogRead(PIN_VRX))); //set speed depending on position on the axis X

  int angle = toAngle(analogRead(PIN_VRX)); //set angle of motor turning depending on position on the axis X
  servo.setTargetDeg(angle); //set angle for servo
  
  
}

//convert analog value to angle
double toAngle(int analog) {
  return floor(analog/CONST2);
}

//convert analog value to speed of motor
double toSpeed(int analog) { 
  
  double speed = 2 * abs(analog - 512) * CONST1;
  
  //made to not have speed greater than speed cap
  if (speed > SPEED_CAP) {
    return 90;
  }
  
  return floor(speed);
}
