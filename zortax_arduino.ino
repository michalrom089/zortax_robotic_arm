#include <Servo.h>

//arm_sweep - C
//shoulder - B
//elbow - A

// For RAMPS 1.4
#define SERVO_PIN          4

#define ARM_SWEEP_STEP_PIN         50
#define ARM_SWEEP_DIR_PIN          51
#define ARM_SWEEP_MIN_PIN           3
#define ARM_SWEEP_MAX_PIN           2

#define SHOULDER_STEP_PIN         48
#define SHOULDER_DIR_PIN          49
#define SHOULDER_MIN_PIN          14
#define SHOULDER_MAX_PIN          15

#define ELBOW_STEP_PIN         46
#define ELBOW_DIR_PIN          47
#define ELBOW_MIN_PIN          18
#define ELBOW_MAX_PIN          19


#define ENABLE 45

#define START_DIR_ELBOW     LOW
#define START_DIR_SHOULDER  LOW

Servo servo;
int pos;
int zmiana;


int elbow_steps=0;
int shoulder_steps=0;


void setup() {
  pinMode( ARM_SWEEP_STEP_PIN ,  OUTPUT);
  pinMode( ARM_SWEEP_DIR_PIN  ,  OUTPUT);
  pinMode( SHOULDER_STEP_PIN  ,  OUTPUT);
  pinMode( SHOULDER_DIR_PIN   ,  OUTPUT);
  pinMode( ELBOW_STEP_PIN     ,  OUTPUT);
  pinMode( ELBOW_DIR_PIN      ,  OUTPUT);
  
  pinMode(ENABLE              ,  OUTPUT);

  digitalWrite(ENABLE,LOW );
  servo.attach(SERVO_PIN);
  pos=180;
}

void loop() {


digitalWrite(ELBOW_DIR_PIN , LOW);
digitalWrite(SHOULDER_DIR_PIN , HIGH);
digitalWrite(ARM_SWEEP_DIR_PIN , HIGH);

if(elbow_steps<100){
digitalWrite(ELBOW_STEP_PIN,HIGH);
delay(10);
digitalWrite(ELBOW_STEP_PIN,LOW);
elbow_steps++;
}
if(shoulder_steps<100){
digitalWrite(SHOULDER_STEP_PIN,HIGH);
delay(10);
digitalWrite(SHOULDER_STEP_PIN,LOW);
shoulder_steps++;
}
if(shoulder_steps<100){
digitalWrite(SHOULDER_STEP_PIN,HIGH);
delay(10);
digitalWrite(SHOULDER_STEP_PIN,LOW);
shoulder_steps++;
}
}
