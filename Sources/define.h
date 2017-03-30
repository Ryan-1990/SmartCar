/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:define.h
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/




#define Yaotou   PWMDTY45
#define Diantou  PWMDTY67
#define Steer    PWMDTY01



#define SpeedDang 30
#define Speed_Max 5000    //PWM���ռ�ձ�ֵ
#define PID_Dead  3       //PID����
#define PID_BangBang 500  //PIDת�����ٽ�ֵ
#define Speed_ShaChe 40   //ɲ��ʱ��PIDɲ�����ٶ�


#define Yaotou_abs 500    //ҡͷ���ķ�Χ
#define Steer_abs 300    //������ķ�Χ


#define Yaotou_abs_Slope 200    //ҡͷ���ķ�Χ
//#define Steer_abs_Slope 1300    //������ķ�Χ


#define Steer_Center 1242
#define Steer_Max Steer_Center+Steer_abs     //�����
#define Steer_Min Steer_Center-Steer_abs     //�Ҵ���
//#define Steer_Max_Slope Steer_Center+Steer_abs_Slope     //�����
//#define Steer_Min_Slope Steer_Center-Steer_abs_Slope     //�Ҵ���

#define Yaotou_Center 8314
#define Yaotou_Max Yaotou_Center+Yaotou_abs   //�Ҵ���
#define Yaotou_Min Yaotou_Center-Yaotou_abs   //�����
#define Yaotou_Max_Slope Yaotou_Center+Yaotou_abs_Slope   //�Ҵ���
#define Yaotou_Min_Slope Yaotou_Center-Yaotou_abs_Slope   //�����


//#define Diantou_Far    18725   //Զ��
//#define Diantou_Near   18673   //����
#define Diantou_Near   18106   //����
#define Diantou_Slope  17920   //�µ�

////////////////////////////////////////////////////////////////////


#define REC1  PORTA_PA1
#define REC2  PORTA_PA2
#define REC3  PORTA_PA3
#define REC4  PORTA_PA4


#define IN1   PORTB_PB0
#define IN2   PORTB_PB1
#define IN3   PORTB_PB2
#define IN4   PORTB_PB3
#define IN5   PORTB_PB4
#define IN6   PORTB_PB5
#define IN7   PORTB_PB6
#define IN8   PORTB_PB7
#define IN9   PTM_PTM0
#define IN10  PTM_PTM1
#define IN11  PTM_PTM2
#define IN12  PTM_PTM3

#define IO1   PTM_PTM4
#define IO2   PTM_PTM5
