/******************************************************************************\
*  Copyright (C) 2011 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Init.c
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/






#include "Init.h"



void SetBusCLK_80M(void)
{   
    CLKSEL=0X00;    //disengage PLL to system
    PLLCTL_PLLON=1;   //turn on PLL
    SYNR =0xc0 | 0x09;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=160MHz;
    _asm(nop);          //BUS CLOCK=80M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));   //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;          //engage PLL to system; 
}


void Port_Init(void)
{   
   DDRA=0X00;
   DDRB=0XFF;
   DDRM=0xFF;
   ECLKCTL=0xC0;
   DDRE=0x6F;
   DDRS_DDRS2=0;
   DDRS_DDRS3=1;
   ATD0DIEN=0xFFFF;
	 DDR1AD0=0xFF; 
	 
	 IO1=0;
	 IO2=0;
	 
	 //激光全灭
	 IN1=1;IN4=1;IN7=1;IN10=1;
   IN2=1;IN5=1;IN8=1;IN11=1;
   IN3=1;IN6=1;IN9=1;IN12=1;
}


void SCI_Init(void) 
{
    SCI0CR2=0x0c; //RX enable,Tx enable
    SCI0BD=521;
} 


void PWM_Init(void)
{   
    //*****转向舵机 0、1级联********
    PWMCTL_CON01=1;
    PWME_PWME1 = 0;
    PWMPRCLK = 0X03;    //clockA 8分频:10Mhz   clockB  1分频:80Mhz 
    PWMSCLA = 5;        //对clock SA 进行2*PWMSCLA=10分频；pwm clock=clockA/10=1MHz;  
    PWMPOL_PPOL1 = 0;   //脉冲有效期间为高电平
    PWMCLK_PCLK1 = 1;   //时钟为SA
    PWMCAE_CAE1 = 0;    //左对齐
    PWMPER01 = 2500;   //PWM频率 = SA/2500 = 400Hz
    PWMDTY01 = Steer_Center;   
    PWME_PWME1 = 1; 
    //******************************
    
    //*****摇头舵机 4、5级联********
    PWMCTL_CON45=1;
    PWME_PWME5 = 0;  
    PWMPOL_PPOL5 = 0;   //脉冲有效期间为高电平
    PWMCLK_PCLK5 = 1;   //时钟为SA
    PWMCAE_CAE5 = 0;    //左对齐
    PWMPER45 = 10000;   //PWM频率 = SA/10000 = 100Hz
    PWMDTY45 = Yaotou_Center;   
    PWME_PWME5 = 1; 
    //******************************
    
    
    //*****点头舵机 6、7级联********
    PWMCTL_CON67=1;
    PWME_PWME7 = 0; 
    PWMSCLB = 40;        //对clock SB 进行2*PWMSCLB=80分频；pwm clock=clockB/80=1MHz;  
    PWMPOL_PPOL7 = 0;   //脉冲有效期间为高电平
    PWMCLK_PCLK7 = 1;   //时钟为SB
    PWMCAE_CAE7 = 0;    //左对齐
    PWMPER67 = 20000;   //PWM频率 = SB/20000 = 50Hz
    PWMDTY67 = Diantou_Near;   
    PWME_PWME7 = 1;   
    
    //****************************** 
    
    //*****电机 2、3级联********
    PWMCTL_CON23=1;
    PWME_PWME3 = 0;   
    PWMPOL_PPOL3 = 0;   //脉冲有效期间为高电平
    PWMCLK_PCLK3 = 0;   //时钟为B
    PWMCAE_CAE3 = 0;    //左对齐
    PWMPER23 = 5000;   //PWM频率 = B/5000 = 16KHz
    PWMDTY23 = 5000;   //占空比 0%
    PWME_PWME3 = 1;   
    //******************************
    
}


//IOC7/PT7用于计算编码器产生的脉冲数
void ECT_Init(void)
{   
    TCNT =0x00;
    PACTL=0xC0;//允许PAC
    TIE  =0x00;//每一位对应相应通道禁止中断
    PACNT=0;
} 



void TimInit(void)
{
	TSCR1=0x00;
	TIE  =0x03;
	TCTL3=0x00; 
	TCTL4=0x05;    //CH0上升沿  坡道   CH1上升沿 编码器Z相
	TIOS =0x00;   //输入捕捉
}



void Timer_Init(void) 
{   
   PITCFLMT_PITE=0;
   PITCE_PCE0=1;             //enable timer channel 0
   PITMUX_PMUX0=0;           //ch0 connected to micro timer 0
   PITMTLD0=250-1;           
   PITLD0=3200-1;            //time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
                             //250 * 3200 * /80000000 = 10ms.
   PITINTE_PINTE0=1;         //enable interupt channel 0
   
   PITCE_PCE1=1;             //enable timer channel 1
   PITMUX_PMUX1=0;           //ch1 connected to micro timer 0
   //PITMTLD1=250-1;           
   PITLD1=128-1;            //time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
                             //250 * 128 /80000000 = 400us.
   PITINTE_PINTE1=1;         //enable interupt channel 1
   
   /*
   PITCE_PCE2=1;             //enable timer channel 1
   PITMUX_PMUX2=1;           //ch1 connected to micro timer 0
   PITMTLD1=25-1;           
   PITLD2=32-1;            //time-out period = (PITMTLD + 1) * (PITLD + 1) / fBUS.
                             //25 * 32 * /80000000 = 10us.
   PITINTE_PINTE2=0;         //disable interupt channel 1
   */
   
   PITCFLMT_PITE=1;    
}


void Init(void)
{
    //COPCTL=0x07;
    SetBusCLK_80M(); 
    Port_Init();
    PWM_Init();
    ECT_Init(); 
    Timer_Init();
    TimInit();
    //SCI_Init(); 
}
