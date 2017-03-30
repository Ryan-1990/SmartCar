/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Scan_Key.c
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/






#include "Scan_Key.h"




//==============================================================
//函数名： unsigned int Scan_Key(void)
//功能描述：扫描按键
//返回：按键值 0~9代表相应的数字，10代表Cancle，11代表OK
//==============================================================
unsigned int Scan_Key(void)
{
   unsigned int j=0;
   Hang1=0;Hang2=0;Hang3=0;Hang4=0;
   while(Lie1!=0&&Lie2!=0&&Lie3!=0);
   
   if(Lie1==0) 
   {
      j=0;
      do
      {
        j++;
        if(j==5) j=1;
        switch(j)
        {
          case 1: Hang1=0;Hang2=1;Hang3=1;Hang4=1;break;
          case 2: Hang1=1;Hang2=0;Hang3=1;Hang4=1;break;
          case 3: Hang1=1;Hang2=1;Hang3=0;Hang4=1;break;
          case 4: Hang1=1;Hang2=1;Hang3=1;Hang4=0;break;
        }
      } while(Lie1!=0);
      DLY_ms(10);
      if(Lie1==0)
      {
        switch(j)
        {
          case 1: return 1;break;
          case 2: return 4;break;
          case 3: return 7;break;
          case 4: return 10;break;
        }
      }
   } 
   
   if(Lie2==0) 
   {
      j=0;
      do
      {
        j++;
        if(j==5) j=1;
        switch(j)
        {
          case 1: Hang1=0;Hang2=1;Hang3=1;Hang4=1;break;
          case 2: Hang1=1;Hang2=0;Hang3=1;Hang4=1;break;
          case 3: Hang1=1;Hang2=1;Hang3=0;Hang4=1;break;
          case 4: Hang1=1;Hang2=1;Hang3=1;Hang4=0;break;
        }
      } while(Lie2!=0);
      DLY_ms(10);
      if(Lie2==0)
      {
        switch(j)
        {
          case 1: return 2;break;
          case 2: return 5;break;
          case 3: return 8;break;
          case 4: return 0;break;
        }
      }
   }
   
   if(Lie3==0) 
   {
      j=0;
      do
      {
        j++;
        if(j==5) j=1;
        switch(j)
        {
          case 1: Hang1=0;Hang2=1;Hang3=1;Hang4=1;break;
          case 2: Hang1=1;Hang2=0;Hang3=1;Hang4=1;break;
          case 3: Hang1=1;Hang2=1;Hang3=0;Hang4=1;break;
          case 4: Hang1=1;Hang2=1;Hang3=1;Hang4=0;break;
        }
      } while(Lie3!=0);
      DLY_ms(10);
      if(Lie3==0)
      {
        switch(j)
        {
          case 1: return 3;break;
          case 2: return 6;break;
          case 3: return 9;break;
          case 4: return 11;break;
        }
      }
   }
   
}