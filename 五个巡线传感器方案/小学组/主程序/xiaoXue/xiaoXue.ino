#include "Function.h"  //包含变量的定义和函数的实现
#include "Track.h"  //巡线传感器类
#include "Car.h"  //小车类
int crossingNum = 0; //路口编号
int startSignal = 0;
void setup(){
   /*将下面两句前面的//删除，修改数字的值可以改变机器人的速度*/

pinMode(A4,INPUT);
pinMode(A5,INPUT);
  SPEED1 = 170;
  SPEED2 = 170; 
  TURN = 150;//转弯的速度
	mycar.Mode();   //将引脚配置为输出
	mycar.Infer(1, 1);
	mytrack.Mode();  //将引脚配置为输入
	Modify();  //自动调整阈值
}
/*****************以上部分不需要更改。****************************/
void loop(){
  /*前五句固定不需要改。
改动的位置是case之后的数字。
情况1：路口右转进站点出来后右转；
情况2：路口右转进站点出来后直行；
情况3：路口直行进站点出来后右转；
情况4：左转；
情况5：右转；
情况6：直行；
break;跳出这一个子程序，继续监测下一个路口。*/
    //int x = 0;
    //x = mytrack.Digital_in();
    //if(x == 1001 || x ==1011 || x ==1101) startSignal = 1;

    if(!digitalRead(9)) startSignal = 1;
	while (startSignal){
          Tracking(SPEED1, SPEED2); 
          crossingNum++; 
	  switch(crossingNum){
            case 1: case 3:  case 6:  
              qingkuang1();
              break;
             case 5: case 9:
              qingkuang2();
              break;
           //case 2: case 7:
            //  qingkuang3();
             // break;
            case 2: case 7: case 10:
              qingkuang4();
              break;
             case 11: 
              qingkuang5();
	      break;
              case 4: case 8:
              qingkuang6();
        break;
            case 12: 
              zhongdian();
	      break;
           default:break;
}
        mycar.Move(0,0,5,1);//停止电机
}
}
/*****************以下部分为子程序，不需要更改。************************/
//情况1具体运行步骤::右转→巡线→鸣笛→后退→停止→后转→巡线→右转
void qingkuang1(){
  TurnR();
  Tracking(SPEED1, SPEED2);
  bee();
  mycar.Move(SPEED1, SPEED2, 8, BACK);
  mycar.Move(0, 0, 5, 1);
  TurnC();
  Tracking(SPEED1,SPEED2);
  TurnR();
}
//情况2具体运行步骤::右转→巡线→鸣笛→后退→停止→后转→巡线→直行
void qingkuang2(){
  TurnR();
  Tracking(SPEED1, SPEED2);
  bee();
  mycar.Move(SPEED1, SPEED2, 8, BACK);
  mycar.Move(0, 0, 5, 1);
  TurnC();
  Tracking(SPEED1,SPEED2);
  mycar.Move(SPEED1,SPEED2,2,200);
}
//情况3具体运行步骤::直行→巡线→鸣笛→后退→停止→后转→巡线→右转
void qingkuang3(){
  mycar.Move(SPEED1,SPEED2,2,200);
  Tracking(SPEED1,SPEED2);
  bee();
  mycar.Move(SPEED1, SPEED2, 8, BACK);
  mycar.Move(0, 0, 5, 1);
  TurnC();
  Tracking(SPEED1,SPEED2);
  TurnR();
}
//情况4具体运行步骤::左转
void qingkuang4(){
  TurnL();
}
//情况5具体运行步骤::右转
void qingkuang5(){
  TurnR();
}
//情况6具体运行步骤::直行
void qingkuang6(){
  mycar.Move(SPEED1*0.6,SPEED2*0.6,2,150);
}
//终点路口具体运行步骤::右转→巡线→直行→停止
void zhongdian(){
  mycar.Move(SPEED1,SPEED2,2,200);
  startSignal = 0;
}


