#include <Arduino.h> 
#include "Car.h"
Car::Car(int a, int b, int c, int d){
	IN1 = c; IN2 = d; MotorA = a; MotorB = b;
        L_IN1 = 1, R_IN2 = 1;
}
//将引脚配置为输出
void Car::Mode(){
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(MotorA, OUTPUT);
	pinMode(MotorB, OUTPUT);
}
//控制数字引脚电平，进而控制左右轮旋转方向
void Car::Digital_out(int a, int b){
	digitalWrite(IN1, a);
	digitalWrite(IN2, b);
}
//控制PWM引脚，进而控制左右轮速度
void Car::Analog_out(int a, int b){
	analogWrite(MotorA, a);
	analogWrite(MotorB, b);
}
//可设置小车前进时IN1和IN2的电平，以此对Move函数进行修正
void Car::Infer(int a, int b){
	L_IN1 = a; R_IN2 = b;
}
/*第一，二个形参分别表示MotorA和MotorB的PWM，第三个形参为小
车运动的方式，取值为1至9，分别表示单边左前转，前进，单边右前
转，双边左转，停止，双边右转，单边左后转，后退，单边右后转，
第四个形参表示延迟时间，默认为不延时，可以用此函数配合Infer
函数对小车前进时IN1和IN2的电平进行确认，从而修正此函数*/
void Car::Move(int a, int b, int c, unsigned long d){
	switch (c){
        case 1:Digital_out(L_IN1, R_IN2); break;
	case 2:Digital_out(L_IN1, R_IN2); break;
        case 3:Digital_out(L_IN1, R_IN2); break;   
	case 4:Digital_out(!L_IN1,R_IN2); break;
        case 5:Digital_out(0,0); break;    
	case 6:Digital_out(L_IN1,!R_IN2); break;
        case 7:Digital_out(!L_IN1,!R_IN2); break;
	case 8:Digital_out(!L_IN1,!R_IN2); break;
        case 9:Digital_out(!L_IN1,!R_IN2); break;
        default:Digital_out(L_IN1,R_IN2); break;
	}
	Analog_out(a, b);
        if(d) 
          delay(d);
}