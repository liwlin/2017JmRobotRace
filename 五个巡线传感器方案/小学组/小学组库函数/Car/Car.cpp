#include <Arduino.h> 
#include "Car.h"
Car::Car(int a, int b, int c, int d){
	IN1 = c; IN2 = d; MotorA = a; MotorB = b;
        L_IN1 = 1, R_IN2 = 1;
}
//����������Ϊ���
void Car::Mode(){
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(MotorA, OUTPUT);
	pinMode(MotorB, OUTPUT);
}
//�����������ŵ�ƽ������������������ת����
void Car::Digital_out(int a, int b){
	digitalWrite(IN1, a);
	digitalWrite(IN2, b);
}
//����PWM���ţ����������������ٶ�
void Car::Analog_out(int a, int b){
	analogWrite(MotorA, a);
	analogWrite(MotorB, b);
}
//������С��ǰ��ʱIN1��IN2�ĵ�ƽ���Դ˶�Move������������
void Car::Infer(int a, int b){
	L_IN1 = a; R_IN2 = b;
}
/*��һ�������βηֱ��ʾMotorA��MotorB��PWM���������β�ΪС
���˶��ķ�ʽ��ȡֵΪ24568���ֱ��ʾǰ��,��ת��ֹͣ����ת����
�ˣ����ĸ��βα�ʾ�ӳ�ʱ�䣬Ĭ��Ϊ����ʱ�������ô˺������
Infer������С��ǰ��ʱIN1��IN2�ĵ�ƽ����ȷ�ϣ��Ӷ������˺���*/
void Car::Move(int a, int b, int c, unsigned long d){
	switch (c){
	case 2:Digital_out(L_IN1, R_IN2); break; 
	case 4:Digital_out(!L_IN1,R_IN2); break;
        case 5:Digital_out(0,0); break;    
	case 6:Digital_out(L_IN1,!R_IN2); break;
	case 8:Digital_out(!L_IN1,!R_IN2); break;
        default:Digital_out(L_IN1,R_IN2); break;
	}
	Analog_out(a, b);
        if(d) 
          delay(d);
}