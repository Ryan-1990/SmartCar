/******************************************************************************\
*  Copyright (C) 2011 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:SCI.c
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/






#include "SCI.h"



int OutData[4] = { 0 };


void uart_putchar(unsigned char ch)
{ 
  if (ch == '\n')  
  {
    while(!(SCI0SR1&0x80)) ;     
    SCI0DRL= 0x0d;      
	  return;
  }
  while(!(SCI0SR1&0x80)) { _FEED_COP(); /* feeds the dog */; }
  SCI0DRL=ch;
}                 


void PutStr(char ch[])
{
  unsigned char ptr=0;
  while(ch[ptr])
  {
    uart_putchar((unsigned char)ch[ptr++]);
  }
}


char RecChar() 
{
  byte  rec_char;
  if (SCI0SR1_RDRF)  rec_char = SCI0DRL;  
  SCI0CR2_RE = 1;    		   
  while(!SCI0SR1_RDRF){  _FEED_COP(); }; 
  rec_char = SCI0DRL; 	
  return SCI0DRL;
} 




unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
    uart_putchar(databuf[i]);
}