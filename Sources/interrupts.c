/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:interrupts.c
*  Describe: 中断函数
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/







#include "interrupts.h"

extern char mystr[20];

extern unsigned int SpeedBack; 
extern unsigned int SpeedWant; 
extern unsigned int ShaChe_Flag;
extern unsigned char slopeTemp_Flag;
extern unsigned char Slo_Cnt;
extern unsigned char slope_Flag;
unsigned int ShaCheTime=0;    //看到起跑线到做出刹车动作的时间 单位（10ms）
unsigned int StopCnt=0;
unsigned char StopFlag=0;
int PIT_CNT=0;
unsigned int TIM_CNT=0;   //上升沿计数器
unsigned int RTI_CNT=0;   //RTI计数器
int aa=0;    //加速度
extern unsigned int rec[16];
extern unsigned int rec_Slope[8];
extern unsigned char Laser_OK;
//extern unsigned char MotorProtect_Flag;

extern long int Time;
extern unsigned char QiPao_Flag;

//extern unsigned int TypeJudgeCount;
extern unsigned int Crazy_Speed;
extern unsigned char RoadType;  //道路类型  

unsigned char Crack_Flag=0;  //撞车标志



#pragma CODE_SEG __NEAR_SEG NON_BANKED 


void interrupt 9 TimCH1_ISR(void)     //编码器Z相中断  车每前进7.8cm进入一次
{ 
  //static int TypeJudgeCnt=0;
  DisableInterrupts;
  if(Time>20)
  {
    //RoadLength++;
    //TypeJudgeCnt++;
    Renew_RoadType();
    /*
    if(TypeJudgeCnt>1) 
    {
      TypeJudgeCnt=0;
      TypeJudgeCount=0; 
    }
    */
  }
  TFLG1_C1F=1;
  EnableInterrupts;
}


void interrupt 66 PIT0_ISR(void)
{ 
  DisableInterrupts;
  Time++;
  aa=PACNT-SpeedBack;
  SpeedBack=PACNT;
  PACNT=0;
  if(StopFlag==0&&ShaChe_Flag>0) 
  {
    StopCnt++;
    if(StopCnt>ShaCheTime) StopFlag=1;
  } 
  if(SpeedBack>700) 
  {
    SetSpeed(0);
    DisableInterrupts;
    IN1=1;IN4=1;IN7=1;IN10=1;
    IN2=1;IN5=1;IN8=1;IN11=1;
    IN3=1;IN6=1;IN9=1;IN12=1;
    for(;;);
  }
  if((aa<-50||SpeedBack<30)&&SpeedBack<100&&Time>200&&ShaChe_Flag==0)  Crack_Flag=1;     //撞了  电机掉电
  if(Crack_Flag==0)
  {
    if(StopFlag>0) 
    {
      if(SpeedBack>Speed_ShaChe+20) Set_Speed(Speed_ShaChe);
      else 
      {
        SetSpeed(0); 
        /*
        LCD_Print(7,0,"天津大学光电一队");
        sprintf(mystr,"Time:%dms",Time*10);
        LCD_Print(0,3,mystr);
        */
        //PITINTE_PINTE0=0;
      }
    }
    else Set_Speed(SpeedWant);  
  }
  else
  {
    SetSpeed(0); 
    if(aa>30)  Crack_Flag=0;   //向前推一下继续走
  }
  PITTF_PTF0=1;
  EnableInterrupts;
}

 
void interrupt 67 PIT1_ISR(void)
{ 
  DisableInterrupts;
  PIT_CNT++;
  switch(PIT_CNT)
  {
    case 1: 
            rec[0] =REC1;
            rec[4] =REC2;
            rec[11]=REC3;
            rec[15]=REC4;
            // A2  B2  C3  D3
            IN1=1;IN4=1;IN7=0;IN10=0;
            IN2=0;IN5=1;IN8=1;IN11=0;
            IN3=0;IN6=0;IN9=0;IN12=1;
            break;
    case 2: 
            rec[1] =REC1;
            rec[5] =REC2;
            rec[10]=REC3;
            rec[14]=REC4;
            // A3  B3  C2  D2
            IN1=0;IN4=0;IN7=1;IN10=1;
            IN2=1;IN5=0;IN8=0;IN11=1;
            IN3=0;IN6=1;IN9=0;IN12=0;
            break;
    case 3: 
            rec[2] =REC1;
            rec[6] =REC2;
            rec[9] =REC3;
            rec[13]=REC4;
            // A4  B4  C1  D1
            IN1=1;IN4=1;IN7=0;IN10=0;
            IN2=1;IN5=0;IN8=0;IN11=1;
            IN3=0;IN6=1;IN9=0;IN12=0;
            break;
    case 4: 
            rec[3] =REC1;
            rec[7] =REC2;
            rec[8] =REC3;
            rec[12]=REC4;
            // A1  B1  C4  D4
            IN1=0;IN4=0;IN7=1;IN10=1;
            IN2=0;IN5=1;IN8=1;IN11=0;
            IN3=0;IN6=0;IN9=0;IN12=1;
            PIT_CNT=0;
            Laser_OK=1;
            PITINTE_PINTE1=0;
            break;   
  }
  PITTF_PTF1=1;
  EnableInterrupts;
}


void interrupt 8 TimCH0_ISR(void)
{ 
   DisableInterrupts;
   if(Time>100)
   {
     RTICTL=0xFF;
     CRGINT_RTIE=1;   //开RTI
     TCTL4=0x04;      //关坡道检测上升沿
     //TIM_CNT++;
     if(slope_Flag==1)
     {
       //TIM_CNT=0;
       Diantou=Diantou_Near;
       //Laser_OK=0;
       slope_Flag=0;
       Slo_Cnt=0;
       slopeTemp_Flag=0;
       //LCD_Fill(0x00);
     }
     else 
     {
       //Diantou=Diantou_Slope;
       //Yaotou=Yaotou_Center;
       //Steer=Steer_Center;
       //Laser_OK=0;
       //slope_Flag=1;
       slopeTemp_Flag=1; 
       //LCD_Fill(0xFF);
     }
   }
   TFLG1_C0F=1;
   EnableInterrupts;
}


void interrupt 7 RTI_ISR(void)
{ 
  DisableInterrupts;
  RTI_CNT++;
  if(RTI_CNT==5)
  {
    RTI_CNT=0;
    TCTL4=0x05;      //开坡道检测上升沿
    CRGINT_RTIE=0;   //关RTI
  }
  CRGFLG_RTIF=1;
  EnableInterrupts;
}










