#ifndef Track_h
#define Track_h
class Track{
private:
	//�������ţ��±�0��2��Ӧ������3������
	int Light[3];
	//���巧ֵ���������ֺںͰ�
	int NUM[3];
	//��Ϊtrue���������ֵʱ�ǰ�ɫ����Ϊfalse���������ֵʱ�Ǻ�ɫ��Ĭ��Ϊtrue
	bool flag;

public:
	//���ڴ洢��ȡ��ģ����
	int value[3];
	Track(int a, int b, int c, bool f = true);
	void Mode();
	void Set(int a, int b, int c);
	void Test();
	int Digital_in(int a = 3);
};
#endif