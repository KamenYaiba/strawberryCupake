#include "Arduino.h"
#include "xmiomod.h"

pinMode(RM_DIR, OUTPUT);
pinMode(RM_PWM, OUTPUT);
pinMode(LM_DIR, OUTPUT);
pinMode(LM_PWM, OUTPUT);


static int rSpeed = 0;
static int lSpeed = 0;


void x_forward(int speed) {
    if(rSpeed == speed && lSpeed == speed) return;
    digitalWrite(RM_DIR,HIGH);
    digitalWrite(LM_DIR,HIGH);
    analogWrite(RM_PWM, speed);
    analogWrite(LM_PWM, speed);

    rSpeed = lSpeed = speed;
}


void x_backward(int speed) {
    if(rSpeed == -speed && lSpeed == -speed) return;

    digitalWrite(RM_DIR,LOW);
    digitalWrite(LM_DIR,LOW);
    analogWrite(LM_PWM, speed);
    analogWrite(RM_PWM, speed);

    rSpeed = lSpeed = -speed;
}


void x_right0(int speed) {
    if(rSpeed == -speed && lSpeed == speed) retrun;

    digitalWrite(RM_DIR,LOW);
    digitalWrite(LM_DIR,HIGH);
    analogWrite(RM_PWM, speed);
    analogWrite(LM_PWM, speed);

    rSpeed = -speed;
    lSpeed = speed;
}


void x_left0(int speed){
    if(rSpeed == speed && lSpeed == -speed) retrun;
    
    digitalWrite(RM_DIR,HIGH);
    digitalWrite(LM_DIR,LOW);
    analogWrite(RM_PWM, speed);
    analogWrite(LM_PWM, speed);

    rSpeed = speed;
    lSpeed = -speed;
}


void x_arcTurn(int LeftSpeed, int RightSpeed){
    if(rSpeed == RightSpeed && lSpeed == LeftSpeed) return;

	digitalWrite(RM_DIR,HIGH);
    digitalWrite(LM_DIR,HIGH);
    analogWrite(RM_PWM, RightSpeed);
    analogWrite(LM_PWM, LeftSpeed);

    lSpeed = LeftSpeed;
    rSpeed = RightSpeed;
}


void x_motorControl(int RightMotorPwm, int LeftMotorPwm) {
    if (RightMotorPwm <= 0) {
      RightMotorPwm = abs(RightMotorPwm);
      digitalWrite(RM_DIR, LOW);
      analogWrite(RM_PWM, RightMotorPwm);
    }
    else {
      digitalWrite(RM_DIR, HIGH);
      analogWrite(RM_PWM, RightMotorPwm);
    }
    if (LeftMotorPwm <= 0) {
      LeftMotorPwm = abs(LeftMotorPwm);
      digitalWrite(LM_DIR, LOW);
      analogWrite(LM_PWM, LeftMotorPwm);
    }
    else {
      digitalWrite(LM_DIR, HIGH);
      analogWrite(LM_PWM, LeftMotorPwm);
    }
}


void x_stopMotors(){
    analogWrite(RM_PWM, 0);
    analogWrite(LM_PWM, 0);
    
    rSpeed = lSpeed = 0;
}



