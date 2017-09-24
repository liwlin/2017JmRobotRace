#ifndef Car_h
#define Car_h
class Car{
private:
	//�������ţ�L_IN1��R_IN3�ֱ�ΪС��ǰ��ʱIN1��IN2�ĵ�ƽ
	int IN1, IN2,L_IN1, R_IN2, MotorA, MotorB;

public:
	//���캯��
	Car(int a, int b, int c, int d);
	//����������Ϊ���
	void Mode();
	//�����������ŵ�ƽ������������������ת����
	void Digital_out(int a, int b);
	//����PWM���ţ����������������ٶ�
	void Analog_out(int a, int b);
	//������С��ǰ��ʱIN1��IN2�ĵ�ƽ���Դ˶�Move������������
	void Infer(int a, int b);
	/*��һ�������βηֱ��ʾMotorA��MotorB��PWM���������β�ΪС
	���˶��ķ�ʽ��ȡֵΪ1��9���ֱ��ʾ������ǰת��ǰ����������ǰ
	ת��˫����ת��ֹͣ��˫����ת���������ת�����ˣ������Һ�ת��
	���ĸ��βα�ʾ�ӳ�ʱ�䣬Ĭ��Ϊ����ʱ�������ô˺������Infer
	������С��ǰ��ʱIN1��IN2�ĵ�ƽ����ȷ�ϣ��Ӷ������˺���*/
	void Move(int a, int b, int c, unsigned long d = 0);
};
#endif