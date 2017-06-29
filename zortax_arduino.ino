#include <Servo.h>

//arm_sweep - C
//shoulder - B
//elbow - A

// For RAMPS 1.4
#define SERVO_PIN          9

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

#define ELBOW_UP     LOW
#define SHOULDER_UP  HIGH
#define ARM_LEFT     HIGH

#define ELBOW_DOWN   HIGH
#define SHOULDER_DOWN LOW
#define ARM_RIGHT    LOW

#define ELBOW_STEPS         150
#define SHOULDER_STEPS      350
#define ARM_STEPS           200
7
#define SERVO_MAX           180

#define DELAY_TIME          6

Servo servo;
int pos;
int zmiana;


int elbow_steps=0;
int shoulder_steps=0;
int arm_steps=0;

//when the state==3 the first part of the movements is done
//when the state==6 the second part of the movements is done
//every joint adds 1 to the state, when the move is ended
int state=0;

int elbow_flag=0,shoulder_flag=0,arm_flag=0;
 
void setup() {
  pinMode( ARM_SWEEP_STEP_PIN ,  OUTPUT);
  pinMode( ARM_SWEEP_DIR_PIN  ,  OUTPUT);
  pinMode( SHOULDER_STEP_PIN  ,  OUTPUT);
  pinMode( SHOULDER_DIR_PIN   ,  OUTPUT);
  pinMode( ELBOW_STEP_PIN     ,  OUTPUT);
  pinMode( ELBOW_DIR_PIN      ,  OUTPUT);
  
  pinMode(ENABLE              ,  OUTPUT);
  
  digitalWrite(ENABLE,LOW ); //enabling motors
  servo.attach(SERVO_PIN);
}

void loop() {
//    -----------------STATE 0--------------- 
//    -- Opening servo-----------------------
//   ----------------------------------------
    if(state==0){
      openServo();
      state++;
    }
//    -----------------STATE 1--------------- 
//    -- Robot is moving toward the object---
//   ----------------------------------------
    if(state==1){
      digitalWrite(ELBOW_DIR_PIN , ELBOW_UP);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_UP);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_LEFT);
      move_joints(1,1,1);

      //conditional  - next state
      if(elbow_flag==1 && shoulder_flag==1 && arm_flag==1){
        state++;
      }
      
//    -----------------STATE 2--------------------
//    -- Robot is resetting variables and flags---
//    -- preparation to move in the opposed direction---
//   ---------------------------------------------
    }else if(state==2){
      reset();
      state++; 
      closeServo();
      delay(500);

//    -----------------STATE 3--------------------
//    -- Robot is moving arm_sweep and shoulder---
//   ---------------------------------------------
    }else if(state==3){
      digitalWrite(ELBOW_DIR_PIN , ELBOW_DOWN);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_DOWN);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_RIGHT);
      move_joints(1,1,0); 

      //conditional  - next state
      if( shoulder_flag==1 && arm_flag==1){
        state++;
      }

//    -----------------STATE 4--------------------
//    -- Robot is moving elbow--------------------
//   ---------------------------------------------
    }else if(state==4){
       digitalWrite(ELBOW_DIR_PIN , ELBOW_DOWN);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_DOWN);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_RIGHT);
      move_joints(0,0,1);

      //conditional  - next state
      if(elbow_flag==1){
        state++; 
    
      }

//    -----------------STATE 5--------------------
//    -------resetting -----------------------------
//   ---------------------------------------------
    }else if(state==5){
      reset();
      state++;
  }else if(state==6){
      digitalWrite(ELBOW_DIR_PIN , ELBOW_UP);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_UP);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_RIGHT);
      move_joints(1,1,1);

      //conditional  - next state
      if(elbow_flag==1 && shoulder_flag==1 && arm_flag==1){
        state++;
      }
    }else if(state==7){
      reset();
      state++; 
      openServo();
      delay(500);
    }else if(state==8){
      digitalWrite(ELBOW_DIR_PIN , ELBOW_DOWN);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_DOWN);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_LEFT);
      move_joints(1,1,0); 

      //conditional  - next state
      if( shoulder_flag==1 && arm_flag==1){
        state++;
      }
    }else if(state==9){
       digitalWrite(ELBOW_DIR_PIN , ELBOW_DOWN);
      digitalWrite(SHOULDER_DIR_PIN , SHOULDER_DOWN);
      digitalWrite(ARM_SWEEP_DIR_PIN , ARM_LEFT);
      move_joints(0,0,1);

      //conditional  - next state
      if(elbow_flag==1){
        state++; 
    
      }
}}

void move_joints(bool arm_turn,bool shoulder_turn,bool elbow_turn){
    if(shoulder_steps <  SHOULDER_STEPS && shoulder_turn){
      digitalWrite(SHOULDER_STEP_PIN,HIGH);
    }else if(shoulder_turn){
      shoulder_flag=1;
    }
    if(elbow_steps  < ELBOW_STEPS && elbow_turn){
      digitalWrite(ELBOW_STEP_PIN,HIGH);
    }else if(elbow_turn){
      elbow_flag=1;
    }
    if(arm_steps  < ARM_STEPS && arm_turn){
      digitalWrite(ARM_SWEEP_STEP_PIN,HIGH);
    }else if(arm_turn){
      arm_flag=1;
    }
    
    delay(DELAY_TIME);
    
    if(shoulder_steps < SHOULDER_STEPS && shoulder_turn){
      digitalWrite(SHOULDER_STEP_PIN,LOW);
      shoulder_steps++;
    }
    if(elbow_steps  < ELBOW_STEPS && elbow_turn){
      digitalWrite(ELBOW_STEP_PIN,LOW);
      elbow_steps++;
    }
    if(arm_steps  < ARM_STEPS && arm_turn){
      digitalWrite(ARM_SWEEP_STEP_PIN,LOW);
      arm_steps++;
    }
    delay(DELAY_TIME);

}

void openServo(){
  for (pos = 0; pos <= SERVO_MAX; pos += 1) { 
    // in steps of 1 degree
    servo.write(pos);             
    delay(15);                      
  }
}

void closeServo(){
  for (pos = SERVO_MAX; pos >= 0; pos -= 1) { 
      servo.write(pos);              
      delay(15);                       
  }
}

void reset(){
    elbow_flag=0;
    arm_flag=0;
    shoulder_flag=0;
    
    elbow_steps=0;
    arm_steps=0;
    shoulder_steps=0;
}
