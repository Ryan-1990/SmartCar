/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename: main.c
*  Version: 1.0
*  Author: Nick Lee
\******************************************************************************/




#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>

#include "Init.h"
#include "Delay.h"
#include "OLED.h"	
#include "Test_Fun.h"
#include "Set_Fun.h"
#include "Run_Fun.h"


//extern unsigned char MotorProtect_Flag;
//extern unsigned int Max_Speed;
//extern unsigned int Min_Speed;
extern unsigned int Crazy_Speed;
extern unsigned int SpeedBack; 
extern unsigned int SpeedWant; 
//extern unsigned int RoadLength;


extern char mystr[20];

void main(void) 
{
  DisableInterrupts;
  Init();
  LCD_Init();  
 	v_PIDInit(); 
 	fuzzy_init();
 	DLY_ms(10);
 	
 	LCD_Print(7,0,"天津大学光电一队");
 	LCD_Print(0,3,"1..LaserLine");    //激光直线
  LCD_Print(0,4,"2..LaserRec");     //激光接收
  LCD_Print(0,5,"3..SetSpeed");     //设速度跑
  LCD_Print(0,6,"4..StartRun");     //选档跑
  LCD_Print(0,7,"5..PID");    

  
  switch(SelectFunction()) 
  {
     case 1: //调试激光直线
             TestLaserLine();
             break;
     case 2: //调试激光接收 
             TestLaserRec();
             break;
     case 3: //设速走
             Init_Run();
             speed_tab_init();
             DLY_ms(2000);
             LCD_clear_all();
             //MotorProtect_Flag=1;
             TSCR1=0x80;
             // A1  B1  C4  D4
             IN1=0;IN4=0;IN7=1;IN10=1;
             IN2=0;IN5=1;IN8=1;IN11=0;
             IN3=0;IN6=0;IN9=0;IN12=1;
             DLY_us(400);
             SpeedWant=50;
             //TFLG1_C1F=1;PITTF_PTF0=1;PITTF_PTF1=1;TFLG1_C0F=1;CRGFLG_RTIF=1;
             PACNT=0;
             EnableInterrupts;
             
             for(;;)
             {
               Laser_Process();
             }
             break;
     case 4: //选档走
             DLY_ms(500);
             SwitchQipao();
             Switch_Dang();
             speed_tab_init();
             DLY_ms(2000);
             LCD_clear_all();
             //MotorProtect_Flag=1;
             TSCR1=0x80;
             // A1  B1  C4  D4
             IN1=0;IN4=0;IN7=1;IN10=1;
             IN2=0;IN5=1;IN8=1;IN11=0;
             IN3=0;IN6=0;IN9=0;IN12=1;
             DLY_us(400);
             SpeedWant=50;
             //TFLG1_C1F=1;PITTF_PTF0=1;PITTF_PTF1=1;TFLG1_C0F=1;CRGFLG_RTIF=1;
             PACNT=0;
             EnableInterrupts;
             
             for(;;)
             {
               Laser_Process();
             }
             break;
             
     case 5: PITINTE_PINTE1=0;
             Set_CrazySpeed();
             SpeedWant=Crazy_Speed;
             EnableInterrupts;
             for(;;);
  } 
  
} // please make sure that you never leave main 
