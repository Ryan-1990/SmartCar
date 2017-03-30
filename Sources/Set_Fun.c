/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Set_Fun.c
*  Describe: 设置参数的所有函数
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/







#include "Set_Fun.h"



extern unsigned int Crazy_Speed;
extern unsigned int Max_Speed;
extern unsigned int Min_Speed;
extern unsigned int Slope_Speed;

extern unsigned int SpeedWant; 
extern unsigned char OpenQipaoFlag;

extern unsigned int QipaoJudgeTime;
extern unsigned int slopeDelayTime;
extern unsigned int Key;

extern char mystr[20];


unsigned int power(unsigned int z)
{
   byte i;
   unsigned int result=1;
   for(i=0;i<z;i++) 
   {
      result=result*10; 
   }
   return result;
}

void SetQipaoTime(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MaxSpeedTemp[4];
   Key=12;
   LCD_Print(0,5,"QipaoTime:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,5,"1");MaxSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,5,"2");MaxSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,5,"3");MaxSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,5,"4");MaxSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,5,"5");MaxSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,5,"6");MaxSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,5,"7");MaxSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,5,"8");MaxSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,5,"9");MaxSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,5,"0");MaxSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,5," ");a-=2; } 
                 else { LCD_Print(80,5,"0");a--;MaxSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   QipaoJudgeTime=0;
   for(j=0;j<a;j++)
   {
      QipaoJudgeTime=QipaoJudgeTime+(power(a-1-j)*MaxSpeedTemp[j]);
   }
   LCD_clear_line(5);
   sprintf(mystr,"QipaoTime:%d",QipaoJudgeTime);
   LCD_Print(0,5,mystr);
}

void SetSlopeTime(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MaxSpeedTemp[4];
   Key=12;
   LCD_Print(0,6,"SlopeTime:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,6,"1");MaxSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,6,"2");MaxSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,6,"3");MaxSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,6,"4");MaxSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,6,"5");MaxSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,6,"6");MaxSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,6,"7");MaxSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,6,"8");MaxSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,6,"9");MaxSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,6,"0");MaxSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,6," ");a-=2; } 
                 else { LCD_Print(80,6,"0");a--;MaxSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   slopeDelayTime=0;
   for(j=0;j<a;j++)
   {
      slopeDelayTime=slopeDelayTime+(power(a-1-j)*MaxSpeedTemp[j]);
   }
   LCD_clear_line(6);
   sprintf(mystr,"SlopeTime:%d",slopeDelayTime);
   LCD_Print(0,6,mystr);
}

void SwitchQipao(void)
{
   Key=12;
   LCD_clear();
   LCD_Print(0,3,"OpenQipao?"); 
   Key=Scan_Key();
   if(Key==1) 
   {
     OpenQipaoFlag=1;
     LCD_Print(0,4,"Yes");
     DLY_ms(500);
     SetQipaoTime();  
   }
   else if(Key==2) 
   {
     OpenQipaoFlag=0;
     LCD_Print(0,4,"No");
   }
   //DLY_ms(500);
   //SetSlopeTime();
}

/*
void Set_UniformSpeed(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int UniformSpeedTemp[4];
   Key=12;
   LCD_clear();
   LCD_Print(0,3,"Uni_Speed:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,3,"1");UniformSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,3,"2");UniformSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,3,"3");UniformSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,3,"4");UniformSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,3,"5");UniformSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,3,"6");UniformSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,3,"7");UniformSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,3,"8");UniformSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,3,"9");UniformSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,3,"0");UniformSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,3," ");a-=2; } 
                 else { LCD_Print(80,3,"0");a--;UniformSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   Uniform_Speed=0;
   for(j=0;j<a;j++)
   {
      Uniform_Speed=Uniform_Speed+(power(a-1-j)*UniformSpeedTemp[j]);
   }
   LCD_clear_line(3);
   sprintf(mystr,"Uni_Speed:%d",Uniform_Speed);
   LCD_Print(0,3,mystr);
   DLY_ms(500);
}
*/
void Set_CrazySpeed(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MaxSpeedTemp[4];
   Key=12;
   LCD_clear();
   LCD_Print(0,3,"Cra_Speed:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,3,"1");MaxSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,3,"2");MaxSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,3,"3");MaxSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,3,"4");MaxSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,3,"5");MaxSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,3,"6");MaxSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,3,"7");MaxSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,3,"8");MaxSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,3,"9");MaxSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,3,"0");MaxSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,3," ");a-=2; } 
                 else { LCD_Print(80,3,"0");a--;MaxSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   Crazy_Speed=0;
   for(j=0;j<a;j++)
   {
      Crazy_Speed=Crazy_Speed+(power(a-1-j)*MaxSpeedTemp[j]);
   }
   LCD_clear_line(3);
   sprintf(mystr,"Cra_Speed:%d",Crazy_Speed);
   LCD_Print(0,3,mystr);
   DLY_ms(500);
}

void Set_MaxSpeed(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MaxSpeedTemp[4];
   Key=12;
   LCD_Print(0,4,"Max_Speed:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,4,"1");MaxSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,4,"2");MaxSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,4,"3");MaxSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,4,"4");MaxSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,4,"5");MaxSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,4,"6");MaxSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,4,"7");MaxSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,4,"8");MaxSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,4,"9");MaxSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,4,"0");MaxSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,4," ");a-=2; } 
                 else { LCD_Print(80,4,"0");a--;MaxSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   Max_Speed=0;
   for(j=0;j<a;j++)
   {
      Max_Speed=Max_Speed+(power(a-1-j)*MaxSpeedTemp[j]);
   }
   LCD_clear_line(4);
   sprintf(mystr,"Max_Speed:%d",Max_Speed);
   LCD_Print(0,4,mystr);
   DLY_ms(500);
}

void Set_MinSpeed(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MinSpeedTemp[4];
   Key=12;
   LCD_Print(0,5,"Min_Speed:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,5,"1");MinSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,5,"2");MinSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,5,"3");MinSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,5,"4");MinSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,5,"5");MinSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,5,"6");MinSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,5,"7");MinSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,5,"8");MinSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,5,"9");MinSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,5,"0");MinSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,5," ");a-=2; } 
                 else { LCD_Print(80,5,"0");a--;MinSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   Min_Speed=0;
   for(j=0;j<a;j++)
   {
      Min_Speed=Min_Speed+(power(a-1-j)*MinSpeedTemp[j]);
   }
   LCD_clear_line(5);
   sprintf(mystr,"Min_Speed:%d",Min_Speed);
   LCD_Print(0,5,mystr);
   DLY_ms(500);
}

void Set_SlopeSpeed(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int MinSpeedTemp[4];
   Key=12;
   LCD_Print(0,6,"Slo_Speed:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(80+6*a,6,"1");MinSpeedTemp[a]=1;break;
        case 2:  LCD_Print(80+6*a,6,"2");MinSpeedTemp[a]=2;break;
        case 3:  LCD_Print(80+6*a,6,"3");MinSpeedTemp[a]=3;break;
        case 4:  LCD_Print(80+6*a,6,"4");MinSpeedTemp[a]=4;break;
        case 5:  LCD_Print(80+6*a,6,"5");MinSpeedTemp[a]=5;break;
        case 6:  LCD_Print(80+6*a,6,"6");MinSpeedTemp[a]=6;break;
        case 7:  LCD_Print(80+6*a,6,"7");MinSpeedTemp[a]=7;break;
        case 8:  LCD_Print(80+6*a,6,"8");MinSpeedTemp[a]=8;break;
        case 9:  LCD_Print(80+6*a,6,"9");MinSpeedTemp[a]=9;break;
        case 0:  LCD_Print(80+6*a,6,"0");MinSpeedTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(74+6*a,6," ");a-=2; } 
                 else { LCD_Print(80,6,"0");a--;MinSpeedTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   Slope_Speed=0;
   for(j=0;j<a;j++)
   {
      Slope_Speed=Slope_Speed+(power(a-1-j)*MinSpeedTemp[j]);
   }
   LCD_clear_line(6);
   sprintf(mystr,"Slo_Speed:%d",Slope_Speed);
   LCD_Print(0,6,mystr);
   DLY_ms(500);
}

void Switch_Dang(void)
{
   unsigned int dangcnt=0;
   Key=12;
   while(Key!=11)
   {
     dangcnt++;
     DLY_ms(500);
     if(dangcnt<2) LCD_clear();
     Key=Scan_Key();
     switch(Key) 
     {
        case 1://
               Crazy_Speed=500;
               Max_Speed  =370;
               Min_Speed  =350;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"1");
               sprintf(mystr,"%d Dang",1);
               break;
        case 2://
               Crazy_Speed=470;
               Max_Speed  =400;
               Min_Speed  =400;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"2");
               sprintf(mystr,"%d Dang",2);
               break;
        case 3://
               Crazy_Speed=470;
               Max_Speed  =430;
               Min_Speed  =380;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"3");
               sprintf(mystr,"%d Dang",3);
               break;
        case 4://
               Crazy_Speed=450;
               Max_Speed  =380;
               Min_Speed  =360;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"4");
               sprintf(mystr,"%d Dang",4);
               break;
        case 5://
               Crazy_Speed=430;
               Max_Speed  =390;
               Min_Speed  =390;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"5");
               sprintf(mystr,"%d Dang",5);
               break;
        case 6://
               Crazy_Speed=420;
               Max_Speed  =370;
               Min_Speed  =370;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"6");
               sprintf(mystr,"%d Dang",6);
               break;
        case 7://
               Crazy_Speed=420;
               Max_Speed  =360;
               Min_Speed  =350;
               Slope_Speed=280;
               LCD_clear();
               LCD_Print(0,3,"7");
               sprintf(mystr,"%d Dang",7);
               break;
        case 8://
               Crazy_Speed=250;
               Max_Speed  =250;
               Min_Speed  =250;
               Slope_Speed=250;
               LCD_clear();
               LCD_Print(0,3,"8");
               sprintf(mystr,"%d Dang",8);
               break;
     }
   }
   LCD_clear();
   LCD_Print(0,3,mystr);
}
  
/*
void Set_ds_kp_max(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KpTemp[4];
   Key=12;
   LCD_Print(0,6,"sp_B:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,6,"1");v_KpTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,6,"2");v_KpTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,6,"3");v_KpTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,6,"4");v_KpTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,6,"5");v_KpTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,6,"6");v_KpTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,6,"7");v_KpTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,6,"8");v_KpTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,6,"9");v_KpTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,6,"0");v_KpTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,6," ");a-=2; } 
                 else { LCD_Print(40,6,"0");a--;v_KpTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   ds_kp_max=0;
   for(j=0;j<a;j++)
   {
      ds_kp_max=ds_kp_max+(power(a-1-j)*v_KpTemp[j]);
   }
   LCD_clear_line(6);
   sprintf(mystr,"sp_B:%d",ds_kp_max);
   LCD_Print(0,6,mystr);
   DLY_ms(500);
}

void Set_ds_kp_min(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KiTemp[4];
   Key=12;
   LCD_Print(0,7,"sp_S:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,7,"1");v_KiTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,7,"2");v_KiTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,7,"3");v_KiTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,7,"4");v_KiTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,7,"5");v_KiTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,7,"6");v_KiTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,7,"7");v_KiTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,7,"8");v_KiTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,7,"9");v_KiTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,7,"0");v_KiTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,7," ");a-=2; } 
                 else { LCD_Print(40,7,"0");a--;v_KiTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   ds_kp_min=0;
   for(j=0;j<a;j++)
   {
      ds_kp_min=ds_kp_min+(power(a-1-j)*v_KiTemp[j]);
   }
   LCD_clear_line(7);
   sprintf(mystr,"sp_S:%d",ds_kp_min);
   LCD_Print(0,7,mystr);
   DLY_ms(500);
}

void Set_dy_kp_max(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KpTemp[4];
   Key=12;
   LCD_clear();
   LCD_Print(0,2,"yp_B:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,2,"1");v_KpTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,2,"2");v_KpTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,2,"3");v_KpTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,2,"4");v_KpTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,2,"5");v_KpTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,2,"6");v_KpTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,2,"7");v_KpTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,2,"8");v_KpTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,2,"9");v_KpTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,2,"0");v_KpTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,2," ");a-=2; } 
                 else { LCD_Print(40,2,"0");a--;v_KpTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_kp_max=0;
   for(j=0;j<a;j++)
   {
      dy_kp_max=dy_kp_max+(power(a-1-j)*v_KpTemp[j]);
   }
   LCD_clear_line(2);
   sprintf(mystr,"yp_B:%d",dy_kp_max);
   LCD_Print(0,2,mystr);
   DLY_ms(500);
}


void Set_dy_kp_min(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KpTemp[4];
   Key=12;
   LCD_Print(0,3,"yp_S:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,3,"1");v_KpTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,3,"2");v_KpTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,3,"3");v_KpTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,3,"4");v_KpTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,3,"5");v_KpTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,3,"6");v_KpTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,3,"7");v_KpTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,3,"8");v_KpTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,3,"9");v_KpTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,3,"0");v_KpTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,3," ");a-=2; } 
                 else { LCD_Print(40,3,"0");a--;v_KpTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_kp_min=0;
   for(j=0;j<a;j++)
   {
      dy_kp_min=dy_kp_min+(power(a-1-j)*v_KpTemp[j]);
   }
   LCD_clear_line(3);
   sprintf(mystr,"yp_S:%d",dy_kp_min);
   LCD_Print(0,3,mystr);
   DLY_ms(500);
}

void Set_dy_ki_max(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KpTemp[4];
   LCD_clear();
   Key=12;
   LCD_Print(0,4,"yi_B:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,4,"1");v_KpTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,4,"2");v_KpTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,4,"3");v_KpTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,4,"4");v_KpTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,4,"5");v_KpTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,4,"6");v_KpTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,4,"7");v_KpTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,4,"8");v_KpTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,4,"9");v_KpTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,4,"0");v_KpTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,4," ");a-=2; } 
                 else { LCD_Print(40,4,"0");a--;v_KpTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_ki_max=0;
   for(j=0;j<a;j++)
   {
      dy_ki_max=dy_ki_max+(power(a-1-j)*v_KpTemp[j]);
   }
   LCD_clear_line(4);
   sprintf(mystr,"yi_B:%d",dy_ki_max);
   LCD_Print(0,4,mystr);
   DLY_ms(500);
}

void Set_dy_ki_min(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KiTemp[4];
   Key=12;
   LCD_Print(0,5,"yi_S:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,5,"1");v_KiTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,5,"2");v_KiTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,5,"3");v_KiTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,5,"4");v_KiTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,5,"5");v_KiTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,5,"6");v_KiTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,5,"7");v_KiTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,5,"8");v_KiTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,5,"9");v_KiTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,5,"0");v_KiTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,5," ");a-=2; } 
                 else { LCD_Print(40,5,"0");a--;v_KiTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_ki_min=0;
   for(j=0;j<a;j++)
   {
      dy_ki_min=dy_ki_min+(power(a-1-j)*v_KiTemp[j]);
   }
   LCD_clear_line(5);
   sprintf(mystr,"yi_S:%d",dy_ki_min);
   LCD_Print(0,5,mystr);
   DLY_ms(500);
}
void Set_dy_kd_max(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KpTemp[4];
   Key=12;
   LCD_Print(0,6,"yd_B:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,6,"1");v_KpTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,6,"2");v_KpTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,6,"3");v_KpTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,6,"4");v_KpTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,6,"5");v_KpTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,6,"6");v_KpTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,6,"7");v_KpTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,6,"8");v_KpTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,6,"9");v_KpTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,6,"0");v_KpTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,6," ");a-=2; } 
                 else { LCD_Print(40,6,"0");a--;v_KpTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_kd_max=0;
   for(j=0;j<a;j++)
   {
      dy_kd_max=dy_kd_max+(power(a-1-j)*v_KpTemp[j]);
   }
   LCD_clear_line(6);
   sprintf(mystr,"yd_B:%d",dy_kd_max);
   LCD_Print(0,6,mystr);
   DLY_ms(500);
}

void Set_dy_kd_min(void)
{
   unsigned int j=0;
   int a=0;
   unsigned int v_KiTemp[4];
   Key=12;
   LCD_Print(0,7,"yd_S:");
   while(Key!=11)
   {
     if(a>0) DLY_ms(500);
     Key=Scan_Key();
     switch(Key) 
     {
        case 1:  LCD_Print(40+6*a,7,"1");v_KiTemp[a]=1;break;
        case 2:  LCD_Print(40+6*a,7,"2");v_KiTemp[a]=2;break;
        case 3:  LCD_Print(40+6*a,7,"3");v_KiTemp[a]=3;break;
        case 4:  LCD_Print(40+6*a,7,"4");v_KiTemp[a]=4;break;
        case 5:  LCD_Print(40+6*a,7,"5");v_KiTemp[a]=5;break;
        case 6:  LCD_Print(40+6*a,7,"6");v_KiTemp[a]=6;break;
        case 7:  LCD_Print(40+6*a,7,"7");v_KiTemp[a]=7;break;
        case 8:  LCD_Print(40+6*a,7,"8");v_KiTemp[a]=8;break;
        case 9:  LCD_Print(40+6*a,7,"9");v_KiTemp[a]=9;break;
        case 0:  LCD_Print(40+6*a,7,"0");v_KiTemp[a]=0;break;
        case 10: if(a>0){ LCD_Print(34+6*a,7," ");a-=2; } 
                 else { LCD_Print(40,7,"0");a--;v_KiTemp[0]=0; }
                 break; 
        default:a--;break;
     }
     a++; 
   }
   dy_kd_min=0;
   for(j=0;j<a;j++)
   {
      dy_kd_min=dy_kd_min+(power(a-1-j)*v_KiTemp[j]);
   }
   LCD_clear_line(7);
   sprintf(mystr,"yd_S:%d",dy_kd_min);
   LCD_Print(0,7,mystr);
   DLY_ms(500);
}

void Init_UniformRun(void)
{
   DLY_ms(500);
   Set_UniformSpeed();
   SpeedWant=50;
   //Set_ds_kp_max();
   //Set_ds_kp_min();
   //Set_dy_kp_max();
   //Set_dy_kp_min();
   //Set_dy_ki_max();
   //Set_dy_ki_min();
   //Set_dy_kd_max();
   //Set_dy_kd_min();
}
*/
void Init_Run(void)
{
   DLY_ms(500); 
   SwitchQipao();
   DLY_ms(500);
   Set_CrazySpeed();
   Set_MaxSpeed();
   Set_MinSpeed();
   Set_SlopeSpeed();
   //Set_ds_kp_max();
   //Set_ds_kp_min();
   //Set_dy_kp_max();
   //Set_dy_kp_min();
   //Set_dy_ki_max();
   //Set_dy_ki_min();
   //Set_dy_kd_max();
   //Set_dy_kd_min();
} 
