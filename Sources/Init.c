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
	 
	 //����ȫ��
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
    //*****ת���� 0��1����********
    PWMCTL_CON01=1;
    PWME_PWME1 = 0;
    PWMPRCLK = 0X03;    //clockA 8��Ƶ:10Mhz   clockB  1��Ƶ:80Mhz 
    PWMSCLA = 5;        //��clock SA ����2*PWMSCLA=10��Ƶ��pwm clock=clockA/10=1MHz;  
    PWMPOL_PPOL1 = 0;   //������Ч�ڼ�Ϊ�ߵ�ƽ
    PWMCLK_PCLK1 = 1;   //ʱ��ΪSA
    PWMCAE_CAE1 = 0;    //�����
    PWMPER01 = 2500;   //PWMƵ�� = SA/2500 = 400Hz
    PWMDTY01 = Steer_Center;   
    PWME_PWME1 = 1; 
    //******************************
    
    //*****ҡͷ��� 4��5����********
    PWMCTL_CON45=1;
    PWME_PWME5 = 0;  
    PWMPOL_PPOL5 = 0;   //������Ч�ڼ�Ϊ�ߵ�ƽ
    PWMCLK_PCLK5 = 1;   //ʱ��ΪSA
    PWMCAE_CAE5 = 0;    //�����
    PWMPER45 = 10000;   //PWMƵ�� = SA/10000 = 100Hz
    PWMDTY45 = Yaotou_Center;   
    PWME_PWME5 = 1; 
    //******************************
    
    
    //*****��ͷ��� 6��7����********
    PWMCTL_CON67=1;
    PWME_PWME7 = 0; 
    PWMSCLB = 40;        //��clock SB ����2*PWMSCLB=80��Ƶ��pwm clock=clockB/80=1MHz;  
    PWMPOL_PPOL7 = 0;   //������Ч�ڼ�Ϊ�ߵ�ƽ
    PWMCLK_PCLK7 = 1;   //ʱ��ΪSB
    PWMCAE_CAE7 = 0;    //�����
    PWMPER67 = 20000;   //PWMƵ�� = SB/20000 = 50Hz
    PWMDTY67 = Diantou_Near;   
    PWME_PWME7 = 1;   
    
    //****************************** 
    
    //*****��� 2��3����********
    PWMCTL_CON23=1;
    PWME_PWME3 = 0;   
    PWMPOL_PPOL3 = 0;   //������Ч�ڼ�Ϊ�ߵ�ƽ
    PWMCLK_PCLK3 = 0;   //ʱ��ΪB
    PWMCAE_CAE3 = 0;    //�����
    PWMPER23 = 5000;   //PWMƵ�� = B/5000 = 16KHz
    PWMDTY23 = 5000;   //ռ�ձ� 0%
    PWME_PWME3 = 1;   
    //******************************
    
}


//IOC7/PT7���ڼ��������������������
void ECT_Init(void)
{   
    TCNT =0x00;
    PACTL=0xC0;//����PAC
    TIE  =0x00;//ÿһλ��Ӧ��Ӧͨ����ֹ�ж�
    PACNT=0;
} 



void TimInit(void)
{
	TSCR1=0x00;
	TIE  =0x03;
	TCTL3=0x00; 
	TCTL4=0x05;    //CH0������  �µ�   CH1������ ������Z��
	TIOS =0x00;   //���벶׽
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
