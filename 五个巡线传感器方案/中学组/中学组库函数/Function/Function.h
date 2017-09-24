#ifndef Function_h
#define Function_h
#include <Arduino.h>
#include "Servo.h"
#include "Track.h"
#include "Car.h"
//小车左轮的速度
int SPEED1 = 150;
//小车右轮的速度
int SPEED2 = 150;
//小车转弯时的速度
int TURN = 200;
//定义小车电机电平的延时
int TIME = 0;
//小车转弯时的延时
int DELAY = 300;
//小车停止时的延时
int STOP = 250;
//小车后退时的延时
int BACK = 400;
Car mycar(10,11,12,13);
Track mytrack(A0,A1,A2, true);
/*舵机设置：1表示控制夹子的舵机，2表示控制机械
臂腕转的舵机，3表示控制机械臂摆动的舵机，4表示
控制机械臂底座旋转的舵机*/
Servo myservo1, myservo2, myservo3,myservo4;
/********************小车转弯函数********************/
//小车直角左转
void TurnL(){
	mycar.Move(0, 0, 5, STOP);
        mycar.Move(SPEED1, SPEED2, 2, BACK);
	mycar.Move(TURN, TURN, 4, DELAY);
	do{
		mycar.Move(TURN, TURN, 4, TIME);
	} while (mytrack.Digital_in(1));
	mycar.Move(0, 0, 5, 1);
}
//小车直角右转
void TurnR(){
	mycar.Move(0, 0, 5, STOP);
	mycar.Move(SPEED1, SPEED2, 2, BACK);
	mycar.Move(TURN, TURN, 6, DELAY);
	do{
		mycar.Move(TURN, TURN, 6, TIME);
	} while (mytrack.Digital_in(1));
	mycar.Move(0, 0, 5, 1);
}
//小车原地转180度
void TurnC(){
	mycar.Move(0, 0, 5, STOP);
	mycar.Move(TURN, TURN, 4, DELAY*3);
	do{
		mycar.Move(TURN, TURN, 4, TIME);
	} while (mytrack.Digital_in(1));
	mycar.Move(0, 0, 5, 1);
}
void Tracking(int a, int b, int temp = 101){
	int t = 1;
	while (t){
		t = mytrack.Digital_in();
		Serial.println(t);
		if (t == 10 || t == 111)t = temp;
		switch (t){

		case 110:
                        if(digitalRead(A4) || digitalRead(A5)){t = 0;break;}
			mycar.Move(a, b, 6, TIME); temp = t; break;

		case 11:
                        if(digitalRead(A4) || digitalRead(A5)){t = 0;break;}
			mycar.Move(a, b, 4, TIME); temp = t; break;

		case 101: 
                        if(digitalRead(A4) || digitalRead(A5)){t = 0;break;}
			mycar.Move(a, b, 2, TIME); temp = t; break;

		case 0: case 100: case 1:
                        if(digitalRead(A4) || digitalRead(A5)){t = 0;break;}
			t = 0; break;

		default:
                        if(digitalRead(A4) || digitalRead(A5)){t = 0;break;}
                        break;
		}
	}
	mycar.Move(0, 0, 5, 1);
void In(){
	TurnL();
	Tracking(SPEED1, SPEED2, 1);
	mycar.Move(SPEED1, SPEED2, 8, BACK);
	mycar.Move(0, 0, 5, 1);

}
void Out(){
	TurnC();
	Tracking(SPEED1, SPEED2, 1);
	mycar.Move(SPEED1, SPEED2, 8, BACK / 3);
	mycar.Move(0, 0, 5, 1);
	TurnL();
}
/********************舵机转动函数********************/
//控制舵机的转动
void ServoMove(int a, int b, int c){
	Servo p; int t;
	switch (c){
	case 1:p = myservo1; t = 1; break;
	case 2:p = myservo2; t = 1; break;
	case 3:p = myservo3; t = 1; break;
        case 4:p = myservo4; t = 1; break;
	default:break;
	}
	//考虑到舵机的精确度，此函数用脉冲值来进行控制
	a = map(a, 0, 180, 544, 2400);
	b = map(b, 0, 180, 544, 2400);
	if (a>b)
	for (int i = a; i>b; i-=2){
		p.writeMicroseconds(i); delay(t);
	}
	else
	for (int i = a; i<b; i+=2){
		p.writeMicroseconds(i); delay(t);
	}
}
/********************校正函数********************/
//自动调整阈值
void Modify(){
	int test1[3] = { 0, 0, 0 };
	int test2[3] = { 0, 0, 0 };
	int t[5] = { 0, 0, 0 };
	pinMode(4, OUTPUT);
	//在指示灯停止闪烁前，应将红外全部对准黑线部分放置
	for (int i = 0; i<3000 / 200; i++){
		digitalWrite(4, HIGH); delay(100);
		digitalWrite(4, LOW); delay(100);
	}
	for (int i = 0; i<20; i++){
		mytrack.Test();
		for (int i = 0; i<3; i++){
			test1[i] += mytrack.value[i];
		}
		delay(10);
	}
	//在指示灯停止闪烁前，应将红外全部对准白色部分放置
	for (int i = 0; i<3000 / 1000; i++){
		digitalWrite(4, HIGH); delay(500);
		digitalWrite(4, LOW); delay(500);
	}
	for (int i = 0; i<20; i++){
		mytrack.Test();
		for (int i = 0; i<3; i++){
			test2[i] += mytrack.value[i];
		}
		delay(10);
	}
	for (int i = 0; i<3; i++){
		test1[i] = test1[i] / 20;
		test2[i] = test2[i] / 20;
		t[i] = (test1[i] + test2[i]) / 2;
	}
	mytrack.Set(t[0], t[1], t[2]);
	for (int i = 0; i<3000 / 200; i++){
		digitalWrite(4, HIGH); delay(100);
		digitalWrite(4, LOW); delay(100);
	}
}
#endif