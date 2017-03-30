/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Test_Fun.c
*  Describe: 各种测试函数的集合
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/




#include "Test_Fun.h"



unsigned int Key; //存储当前按键的键值


unsigned int SelectFunction(void) 
{
   Key=12;
   while(Key!=11)
   {
     DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1: LCD_clear();LCD_Print(0,3,"1:LaserLine");    return 1;break;
        case 2: LCD_clear();LCD_Print(0,3,"2:LaserRec");     return 2;break;
        case 3: LCD_clear();LCD_Print(0,3,"3:UniformSpeed"); return 3;break;
        case 4: LCD_clear();LCD_Print(0,3,"4:StartRun");     return 4;break;
        case 5: LCD_clear();LCD_Print(0,3,"5:PID");          return 5;break;
     }
   }
}


void TestLaserLine(void)
{
  //unsigned char line_flag=0;
  unsigned char Rec[16],i;
  char mystr[20]="";
  
  Key=12;
  DLY_ms(500);
  for(;;) 
  { 
    if(Lie1==0||Lie2==0||Lie3==0) 
    {
      Key=Scan_Key(); 
      if(Key==1) Diantou=Diantou_Near;
      else if(Key==2) Diantou=Diantou_Slope;
    }
    // A1  B1  C4  D4
    IN1=0;IN4=0;IN7=1;IN10=1;
    IN2=0;IN5=1;IN8=1;IN11=0;
    IN3=0;IN6=0;IN9=0;IN12=1;
    DLY_us(150);
    Rec[0] =REC1;
    Rec[4] =REC2;
    Rec[11]=REC3;
    Rec[15]=REC4;
    
    // A2  B2  C3  D3
    IN1=1;IN4=1;IN7=0;IN10=0;
    IN2=0;IN5=1;IN8=1;IN11=0;
    IN3=0;IN6=0;IN9=0;IN12=1;
    DLY_us(150);
    Rec[1] =REC1;
    Rec[5] =REC2;
    Rec[10]=REC3;
    Rec[14]=REC4;
    
    // A3  B3  C2  D2
    IN1=0;IN4=0;IN7=1;IN10=1;
    IN2=1;IN5=0;IN8=0;IN11=1;
    IN3=0;IN6=1;IN9=0;IN12=0;
    DLY_us(150);
    Rec[2] =REC1;
    Rec[6] =REC2;
    Rec[9] =REC3;
    Rec[13]=REC4;
    
    // A4  B4  C1  D1
    IN1=1;IN4=1;IN7=0;IN10=0;
    IN2=1;IN5=0;IN8=0;IN11=1;
    IN3=0;IN6=1;IN9=0;IN12=0;
    DLY_us(150);
    Rec[3] =REC1;
    Rec[7] =REC2;
    Rec[8] =REC3;
    Rec[12]=REC4;
    IN1=1;IN4=1;IN7=1;IN10=1;
    IN2=1;IN5=1;IN8=1;IN11=1;
    IN3=1;IN6=1;IN9=1;IN12=1;
    LCD_clear();
    for(i=0;i<16;i++)
    {
      sprintf(mystr,"%d",Rec[i]);
      LCD_Print(i*6,3,mystr);
    }
  }
}



void TestLaserRec(void) 
{
  unsigned char rec_flag=0;
  DLY_ms(500);
  for(;;)
  {
    if(rec_flag==0)
    {
      switch(Scan_Key())  
      {
        case 1: // A1  B1  C4  D4
                IN1=0;IN4=0;IN7=1;IN10=1;
                IN2=0;IN5=1;IN8=1;IN11=0;
                IN3=0;IN6=0;IN9=0;IN12=1;
                break;
        case 2: // A2  B2  C3  D3
                IN1=1;IN4=1;IN7=0;IN10=0;
                IN2=0;IN5=1;IN8=1;IN11=0;
                IN3=0;IN6=0;IN9=0;IN12=1;
                break;
        case 3: // A3  B3  C2  D2
                IN1=0;IN4=0;IN7=1;IN10=1;
                IN2=1;IN5=0;IN8=0;IN11=1;
                IN3=0;IN6=1;IN9=0;IN12=0;
                break;
        case 4: // A4  B4  C1  D1
                IN1=1;IN4=1;IN7=0;IN10=0;
                IN2=1;IN5=0;IN8=0;IN11=1;
                IN3=0;IN6=1;IN9=0;IN12=0;
                break;
        case 7: // 点头
                Diantou = Diantou_Slope;
                rec_flag=1;
                break; 
      } 
    }
    else if(rec_flag==1)
    {
      switch(Scan_Key())  
      {
        case 1: // A1  B1  C4  D4
                IN1=0;IN4=0;IN7=1;IN10=1;
                IN2=0;IN5=1;IN8=1;IN11=0;
                IN3=0;IN6=0;IN9=0;IN12=1;
                break;
        case 2: // A2  B2  C3  D3
                IN1=1;IN4=1;IN7=0;IN10=0;
                IN2=0;IN5=1;IN8=1;IN11=0;
                IN3=0;IN6=0;IN9=0;IN12=1;
                break;
        case 3: // A3  B3  C2  D2
                IN1=0;IN4=0;IN7=1;IN10=1;
                IN2=1;IN5=0;IN8=0;IN11=1;
                IN3=0;IN6=1;IN9=0;IN12=0;
                break;
        case 4: // A4  B4  C1  D1
                IN1=1;IN4=1;IN7=0;IN10=0;
                IN2=1;IN5=0;IN8=0;IN11=1;
                IN3=0;IN6=1;IN9=0;IN12=0;
                break;
        case 8: // 抬头
                Diantou = Diantou_Near;
                rec_flag=0;
                break;
      } 
    }
  }
}