#ifndef xmiomod_h 
#define xmiomod_h	

#define RM_DIR 13
#define RM_PWM 11
#define LM_DIR 12
#define LM_PWM 10


void x_forward(int speed);
void x_backward(int speed);
void x_right0(int speed);
void x_left0(int speed);
void x_stopMotors();
void x_arcTurn(int LeftSpeed, int RightSpeed);
void x_motorControl(int LeftSpeed, int RightSpeed);


#endif