#include <Servo.h> // include the Servo library

#define R_MOTOR 4
#define L_MOTOR 3
#define P_MOTOR 5

#define SERVO_FORWARD  false
#define SERVO_BACKWARD true

// create the servo objects
Servo leftMotor;
Servo rightMotor;
Servo penMotor;

typedef struct event {
  uint8_t l;
  uint8_t r;
  int t;
} event;

// update these values if your wheels aren't the same size or motors don't turn
// at the same speed;
int rightCalibration = 0;
int leftCalibration = 0;

void setSpeed(int motor, int motorSpeed, boolean isBackward)
{
  int cal = 0;
  Servo *s;
  if (motor == R_MOTOR) {
    s = &rightMotor;
    cal = rightCalibration;
  }
  else {
    s = &leftMotor;
    cal = leftCalibration;
  }
  motorSpeed += cal;
  
  if ((motor == R_MOTOR) ^ (isBackward))
  {
    motorSpeed = -motorSpeed;
  }
  
  s->write(90+ motorSpeed);
}

void stopMotor(int motor)
{
  Servo *s = (motor == R_MOTOR) ? &rightMotor : &leftMotor;
  s->write(90);
}


#define PEN_UP_POSITION 70
#define PEN_DOWN_POSITION 90
#define DOWN true
#define UP false
boolean pen_state;

#define PU pu();
void pu() {
    Serial.println("Pen Up");
  pen_state = UP;
    penMotor.write(PEN_UP_POSITION);
  delay(20);
}

#define PD pd();
void pd() {
  pen_state = DOWN;
      Serial.println("Pen Down");
    penMotor.write(PEN_DOWN_POSITION);
  delay(20);
}

#define TURN_SPEED 15
void t(int d) {
  boolean restore;
  if (restore = (pen_state == DOWN)) PU;
  _t(d);
  if (d>=90) { m(-.1);}
//  else if (d >=30) { m(-.05);}
  if (restore) PD;
}

void _t(int d) {
    setSpeed(R_MOTOR,TURN_SPEED,d>0);
    setSpeed(L_MOTOR,TURN_SPEED,d<0);
    delay(abs(d)*(3100.0/360.0));
    stopMotor(R_MOTOR);
    stopMotor(L_MOTOR);
}

#define MOVE_FACTOR 50
#define MOVE_SPEED 15
int scale;
void m(float _mm) {
  int mm = _mm*scale;
  Serial.print("Moving:");
  Serial.println(mm);
    setSpeed(R_MOTOR,MOVE_SPEED,mm<0);
    setSpeed(L_MOTOR,MOVE_SPEED,mm<0);
    delay(abs(mm)*MOVE_FACTOR);
    stopMotor(R_MOTOR);
    stopMotor(L_MOTOR);
    Serial.println("Stopping");
}

#define SPC m(.75);
#define NXT PU t(scale * 2); m(.4);
#define H _H();
void _H() {
  t(-90); PD m(1); PU m(-.5); t(90); PD m(.5); PU t(90); m(-.5); PD m(1); t(-90);  NXT;
}
#define I _I();
void _I() {
  t(-90); PD m(.8); PU m(-.8);t(90); NXT
}

#define MM 1.4
#define NN (1.4/2)

#define WA 30
#define WH 1.1
#define W _W();
void _W() {
 m(.4); t(-90-WA);m(WH);t(180);PD m(WH);t(-180+WA*2);m(.4);t(180-WA*2);m(.4);t(-180+WA*2);m(WH);PU t(180-WA/2); m(1); t(-90); NXT
//t(-90); PD m(1); t(135); m(NN); t(-135); m(MM); t(135); m(MM); t(-135); m(NN); PU t(45); m(1); t(-90); NXT
}

#define L _L();
void _L() {
  t(-90); PD m(1); PU m(-1); t(90); PD m(.5); NXT
}

#define BANG _BANG();
void _BANG() {
  t(-90);PD m(.2);PU m(.1); PD m(.7);PU m(-1); t(90); NXT
}

#define AA 22.5
#define AH 1.05
#define A _A();
void _A() {
  t(-90+AA);PD m(AH);t(180-AA*2);m(AH);PU m(-AH/2); t(90+AA); PD m(.2); PU m(-.2); t(-90-AA); m(AH/2); t(-90+AA); NXT
//PD t(-45);m(NN);PU m(-MM); t(135); PD m(MM); PU t(180); m(MM); t(45); m(MM); t(-45); NXT
}

#define C225 _t(23); m(.08);

//#define QC C225 C225 C225 C225
#define QC _t(48); m(.15); _t(48); m(.15);
#define HC QC m(.05); QC

#define P _P();
void _P() {
  t(-90); PD m(1); t(90); m(.3); HC  m(.15); PU t(-180 +50); m(.8); t(-45); NXT
}

#define Y _Y();
void _Y() {
  m(.25);t(-90);PD m(.5);t(-WA); m(.6);PU m(-.6);t(WA*2);PD m(.6); PU t(-WA); m(-1); t(90); NXT
}

#define B _B();
void _B() {
  t(-90); PD m(1); t(90); m(.3); HC  m(.15); PU t(-165); m(.3); PD HC m(.2); PU t(180); m(.5); NXT
}

#define D _D();
void _D() {
  t(-90); PD m(1); t(90); m(.3); QC m(.6); QC m(.25); PU t(180); m(.5); NXT
}
#define TICK m(.1); m(-.1);
#define PLUS _PLUS();
void _PLUS() {
  t(-90); PD m(1); PU  m(-.5);t(-90); m(.5); PD m(-1); PU t(90); m(-.5); t(90); NXT
}

#define DASH _DASH();
void _DASH() {
  t(-90); m(.5); t(90); PD m(.4); PU t(90); m(.5); t(-90); NXT
}

void setup()
{
  Serial.begin(115200);
  Serial.println("STARTING");
  leftMotor.attach(L_MOTOR); 
  rightMotor.attach(R_MOTOR);
  penMotor.attach(P_MOTOR);
  scale = 15;
//  PU 
//  H I SPC W I L L BANG
//  t(-10); m(-8); t(10);
//  H A P P Y SPC B D A Y BANG
  
PU
delay(1000);
PD
delay(3000);
  PU

//PD m(1000);

// Calibrate
//PD _t(22.5); TICK _t(-22.5); SPC _t(45); TICK _t(-45); SPC _t(90); TICK _t(-90); SPC _t(180); TICK _t(-180); SPC _t(360);  TICK _t(-360);
  
//H I SPC W I L L SPC BANG t(180-10); m(10); t(-180+10);

H A P P Y SPC B DASH D A Y 

t(180); m(5); t(22.5); m(5); t(-45); m(3);

scale = 30;

t(-45);

W I L L BANG
//DASH W DASH W DASH

//P B B D SPC SPC
 PU
 
}

void loop() {
 
}
