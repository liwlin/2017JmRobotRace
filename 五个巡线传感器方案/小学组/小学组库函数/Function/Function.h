#ifndef Function_h
#define Function_h
#include <Arduino.h>
#include "Track.h"
#include "Car.h"
//С�����ֵ��ٶ�
int SPEED1 = 100;
//С�����ֵ��ٶ�
int SPEED2 = 100;
//С��ת��ʱ���ٶ�
int TURN = 150;
//����С�������ƽ����ʱ
int TIME = 1;
//С��ת��ʱ����ʱ
int DELAY = 300;
//С��ֹͣʱ����ʱ
int STOP = 250;
//С������ʱ����ʱ
int BACK = 250;
Car mycar(10,11,12,13);
Track mytrack(A0,A1,A2, true);
/********************С��ת�亯��********************/
//С��ֱ����ת
void TurnL(){
	mycar.Move(0, 0, 5, STOP);
        mycar.Move(SPEED1, SPEED2, 2, BACK);
	mycar.Move(TURN, TURN, 6, DELAY);
	do{
		mycar.Move(TURN, TURN, 6, TIME);
	} while (mytrack.Digital_in(1));
	mycar.Move(0, 0, 5, 1);
}
//С��ֱ����ת
void TurnR(){
	mycar.Move(0, 0, 5, STOP);
	mycar.Move(SPEED1, SPEED2, 2, BACK);
	mycar.Move(TURN, TURN, 4, DELAY);
	do{
		mycar.Move(TURN, TURN, 4, TIME);
	} while (mytrack.Digital_in(1));
	mycar.Move(0, 0, 5, 1);
}
//С��ԭ��ת180��
void TurnC(){
	mycar.Move(0, 0, 5, STOP);
	mycar.Move(TURN, TURN, 4, DELAY);
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
}
/********************У������********************/
//�Զ�������ֵ
void Modify(){
	int test1[3] = { 0, 0, 0 };
	int test2[3] = { 0, 0, 0 };
	int t[5] = { 0, 0, 0 };
	pinMode(4, OUTPUT);
	//��ָʾ��ֹͣ��˸ǰ��Ӧ������ȫ����׼���߲��ַ���
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
	//��ָʾ��ֹͣ��˸ǰ��Ӧ������ȫ����׼��ɫ���ַ���
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
void bee(){
        for(int i = 0; i < 3; i++){
                digitalWrite(4,HIGH);
                delay(500);
                digitalWrite(4,LOW);
                delay(100);
        }
}
#endif