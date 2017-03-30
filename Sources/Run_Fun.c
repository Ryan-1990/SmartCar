/******************************************************************************\
*  Copyright (C) 2012 Nick Lee, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Run_Fun.c
*  Describe: 小车跑动过程中需要用到的函数
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/





#include "Run_Fun.h"


extern int OutData[4];

char mystr[20]="";

unsigned int Crazy_Speed=0;
unsigned int Max_Speed=0;
unsigned int Min_Speed=0;
unsigned int Slope_Speed=0;

char v_Kp=20;      
char v_Ki=2;     
char v_Kd=2;


float dy_ki_max=3.4;
float dy_ki_min=2.7;


float s_kp;
float ds_kp_max=0.6;
float ds_kp_min=0.55;
int s_kd;
float ds_kp[10];


float y_ki;
int y_kp;

//int dy_kp[13];
float dy_ki[11];
//int dy_kd[13];


int dy_kp[5][5]=
{
  {8,6,4,6,8},
  {6,4,2,4,6},
  {4,2,1,2,4},
  {6,4,2,4,6},
  {8,6,4,6,8}
};
int Motor_PWM;
int v_PID_Result;         //电机控制 PWM 输出增量
unsigned int SpeedBack;   //速度反馈值
unsigned int SpeedWant=50;
int SpeedPreError;  
int SpeedError;  
int d_SpeedError;
int d_PreSpeedError;
int dd_SpeedError;   

int YaoPreError=0;  
int YaoError=0;  
int d_YaoError=0;

unsigned char Slo_Cnt=0;

//int SteerPreError=0;  
int SteerError=0;  

extern unsigned int ShaCheTime;
  
unsigned int Qibu_Speed_Tab[4]={50,150,250,350};
unsigned int speed_tab[SpeedDang+1];

unsigned int QipaoJudgeTime=0;
//unsigned int slopeDelayTime=0;
                           
int Record[100]={0};
//unsigned int TypeJudgeCount=0;
//unsigned int RoadLength=0;
//unsigned int LastRoadLength=0;
long int Time=0;
//unsigned int TypeChangeLength=0;
//unsigned int TypeChangeLength1=0;
/*
unsigned int NewTypeLength0=0;  
unsigned int NewTypeLength1=0;  
unsigned int NewTypeLength2=0;   
unsigned int NewTypeLength3=0;   
unsigned int NewTypeLength4=0;   
unsigned int NewTypeLength5=0;   
unsigned int NewTypeLength6=0;
unsigned int NewTypeLength7=0;      
*/
unsigned int REC[16];
unsigned int rec[16];
unsigned int REC_Slope[8];
unsigned int rec_Slope[8];
unsigned int L_BlackCount=0;
unsigned int R_BlackCount=0;

//unsigned char L_BlackLength=0;
int L_BlackStart=0;

//unsigned char R_BlackLength=0;
int R_BlackStart=0;
//unsigned int CrossCnt=0;

//以下为标志定义区
unsigned char CrossFlag=0;
unsigned char LeftLostFlag=0;
unsigned char RightLostFlag=0; 
unsigned int ShaChe_Flag=0;
unsigned char Laser_OK=0;
//unsigned char MotorProtect_Flag=0;
unsigned char OpenQipaoFlag=0;
unsigned char QiPao_Flag=0;
unsigned char QiPaoTempFlag=0;
unsigned char slope_Flag=0;
unsigned char slopeTemp_Flag=0;
unsigned char RoadType=0;  //道路类型  
unsigned char LastRoadType=0; //上次道路类型
//unsigned char TypeChange=0; //道路类型发生改变的情况 0:速度无需变化  1:(需要减速) 2:(需要加速)
//以上为标志定义区

unsigned int abs(int b)
{
   if(b<0) return -b;
   else return b;
}

void speed_tab_init(void)
{
   byte i;
   for(i=0;i<SpeedDang+1;i++) 
   {
      speed_tab[i]=Max_Speed-(Max_Speed-Min_Speed)*i/SpeedDang;
   }
}

void fuzzy_init(void)
{
  char i;
  for(i=0;i<11;i++) dy_ki[i]=dy_ki_min+(dy_ki_max-dy_ki_min)*i/10;
  for(i=0;i<10;i++) ds_kp[i]=ds_kp_min+(ds_kp_max-ds_kp_min)*i*i/9/9;
}

void SetSpeed(int PWM) 
{
   if(PWM==0)
   { 
     IO1=0;
     IO2=0; 
   } 
   if(PWM>0)
   { 
     IO1=0;
     IO2=1; 
   } 
   if(PWM<0)
   { 
     IO1=1;
     IO2=0;  
   } 
   PWMDTY23 = Speed_Max-abs(PWM);
}

void v_PIDInit(void)
{ 
   SpeedBack=0;
   SpeedPreError=0;
   d_PreSpeedError=0; 
   d_SpeedError=0;
   dd_SpeedError=0;
}     

int PID(unsigned int SpeedSet)
{
   SpeedError=SpeedSet-SpeedBack;
   d_SpeedError=SpeedError-SpeedPreError;
   dd_SpeedError=d_SpeedError-d_PreSpeedError;
   SpeedPreError=SpeedError;     
   d_PreSpeedError=d_SpeedError;
   //////////////////////////////////////////////////////////////////
   
   if(SpeedError<-40&&slope_Flag==0) return SpeedError;
   //else if(SpeedError<-30&&slope_Flag==0) return SpeedError*1;
   /*if(abs(SpeedError)>PID_BangBang) 
   {
     if(SpeedError>0) return Speed_Max;
     else return -Speed_Max;
   } */
   //else 
   if(abs(SpeedError)<PID_Dead) return 0;
   else return (v_Kp*d_SpeedError+v_Ki*SpeedError+v_Kd*dd_SpeedError);
}



void Set_Speed(int v) 
{
   v_PID_Result=PID(v);
   if(v_PID_Result>300)  v_PID_Result=300;
   else if(v_PID_Result<-1000)  v_PID_Result=-1000;
   Motor_PWM=Motor_PWM+v_PID_Result;
   if(Motor_PWM>Speed_Max)  Motor_PWM=Speed_Max;
   else if(Motor_PWM<-Speed_Max)  Motor_PWM=-Speed_Max;  
   SetSpeed(Motor_PWM); 
}


void Get_Position(void)
{
  int i;
  static int QiPao_Cnt=0;
  static int SlopeTemp_Cnt=0;
  static int slope_Cnt=0;
  //static int Slope_Cnt=0;
  //static int Slope_cnt=0;
  L_BlackCount=0;
  R_BlackCount=0;
  
  for(i=0;i<16;i++) REC[i]=rec[i];
  
  if(slope_Flag==1&&Diantou==Diantou_Slope) REC[12]=0;
  
  PITINTE_PINTE1=1;         //打开激光中断
  for(i=0;i<8;i++)
  {
    if(REC[i]==1) L_BlackCount++;
  }
  for(i=8;i<16;i++)
  {
    if(REC[i]==1) R_BlackCount++;
  }
  /*
  if(QiPaoTempFlag==1)
  {
    
    //LCD_Fill(0xff);
    
    QiPao_Cnt++;
    if(QiPao_Cnt>10)  
    {
      QiPao_Cnt=0;
      if(RoadType==0&&(L_BlackCount<3||R_BlackCount<3)&&REC[7]==0&&REC[8]==0) 
      {
        QiPao_Flag=1;
        if(SpeedBack>370) ShaCheTime=10;
        else ShaCheTime=30;
      }
      else QiPaoTempFlag=0;
    }
  }
  */
  /*
  if(Diantou==Diantou_Slope) 
  {
    Slope_cnt++;
    if(Slope_cnt>250) 
    {
      Slope_cnt=0;
      slope_Flag=0;
      Diantou=Diantou_Near; 
    }
  }
  if(slope_Flag==1&&Diantou==Diantou_Near)
  {
    
    //LCD_Fill(0xff);
    
    Slope_Cnt++;
    if(Slope_Cnt>200) 
    {
      Slope_Cnt=0;
      Diantou=Diantou_Slope;
    }
    CrossFlag=0;
    LeftLostFlag=0;
    RightLostFlag=0;
    YaoError=0; 
    Yaotou=Yaotou_Center;  
  } 
  */
  
  if(slope_Flag==1&&Diantou==Diantou_Near)
  {
    
    //LCD_Fill(0xff);
    
    Slo_Cnt++;
    if(Slo_Cnt>100) 
    {
      Diantou=Diantou_Slope;
    }
    CrossFlag=0;
    LeftLostFlag=0;
    RightLostFlag=0;
    YaoError=0; 
    Yaotou=Yaotou_Center;  
  } 
  
  else 
  {
    if(slopeTemp_Flag==1)
    {
      SlopeTemp_Cnt++;
      if(SlopeTemp_Cnt>40) 
      {
        SlopeTemp_Cnt=0;
        slope_Cnt=0;
        slope_Flag=0;
      }
      else if(L_BlackCount==8&&R_BlackCount==8&&RoadType<3&&ShaChe_Flag==0) 
      {
        slope_Cnt++;
        if(slope_Cnt>1) 
        {
          slope_Cnt=0;
          slope_Flag=1;
          QiPaoTempFlag=0;
          slopeTemp_Flag=0;
          QiPao_Cnt=0;
          SlopeTemp_Cnt=0;  
        }
      }
      else 
      {
        slope_Cnt=0;
        slope_Flag=0;
      }
    }
    //if(RoadType<3&&REC[7]==1&&REC[8]==1) 
    if((REC[7]==1||REC[6]==1)&&(REC[8]==1||REC[9]==1)&&L_BlackCount<8&&R_BlackCount<8) 
    {
      if(Time>(100*QipaoJudgeTime)&&slope_Flag==0)  
      {
        QiPao_Flag=1; 
        if(SpeedBack>430) ShaCheTime=10;
        else ShaCheTime=16; 
      }
      else
      {
        CrossFlag=0;
        LeftLostFlag=0;
        RightLostFlag=0; 
      }
      YaoError=0;  
    }
    
    else if(L_BlackCount==0&&R_BlackCount==0) 
    {
      LeftLostFlag=0;
      RightLostFlag=0; 
      CrossFlag=1; 
      YaoError=YaoPreError;
      //if(RoadType==0&&Time>100) 
      //{
        //slopeTemp_Flag=1;
      //}
    }
    else if(R_BlackCount==0) 
    {
      //QiPao_Cnt=0;
      //CrossCnt=0;
      CrossFlag=0;
      LeftLostFlag=0;
      RightLostFlag=1; 
      for(i=7;i>-1;i--)        
      {
        if(REC[i]==1) 
        {
          L_BlackStart=i;
          break; 
        }
      }
      YaoError=L_BlackStart;
    } 
    else if(L_BlackCount==0) 
    {
      //QiPao_Cnt=0;
      //CrossCnt=0;
      CrossFlag=0;
      LeftLostFlag=1;
      RightLostFlag=0;
      
      for(i=8;i<16;i++)        
      {
        if(REC[i]==1) 
        {
          R_BlackStart=i;
          break; 
        }
      }
      YaoError=R_BlackStart-15;
    }
    else 
    {
      YaoError=YaoPreError;
      //CrossCnt=0;
      CrossFlag=0;
      LeftLostFlag=0;
      RightLostFlag=0;
      /*
      for(i=7;i>-1;i--)        
      {
        if(REC[i]==1) 
        {
          L_BlackStart=i;
          break; 
        }
      }
      
      for(i=8;i<16;i++)        
      {
        if(REC[i]==1) 
        {
          R_BlackStart=i;
          break; 
        }
      }
      if(L_BlackStart>4||R_BlackStart<11) YaoError=YaoPreError;
      else YaoError=L_BlackStart+R_BlackStart-15;  */
    }
  }
  SteerError=Yaotou_Center-Yaotou;
}


void Renew_Record(void)
{
  int index=0;
  //TypeJudgeCount++;
  //if(TypeJudgeCount>100) TypeJudgeCount=100;
  for(index=98;index>=0;index--) Record[index+1]=Record[index];
  Record[0]=SteerError; 
}

void Renew_RoadType(void)
{
  int index=0,TypeChangeTemp=0;
  int max_record=-Yaotou_abs,min_record=Yaotou_abs;
  
  LastRoadType=RoadType;
  for(index=0;index<50;index++)
  {
    if(Record[index]>max_record) max_record=Record[index];
    if(Record[index]<min_record) min_record=Record[index];
  }
  
  if(max_record<70&&min_record>-70)  RoadType=0;      //直道
  else if(max_record<100&&min_record>-140) RoadType=2;  //右大弯
  else if(max_record<140&&min_record>-100) RoadType=1;  //左大弯
  else RoadType=5; 
}

int Cal_D(unsigned int length)
{
   int DCal_D,error1,error2,q_1_1,q_1_2,q_1_3;
   static int Z[102],queue_index=0;
   Z[queue_index]=SteerError;
   queue_index=(queue_index+1)%102;
   q_1_1=queue_index-1;
   if(q_1_1<0) q_1_1=102+q_1_1;
   q_1_2=queue_index-2;
   if(q_1_2<0) q_1_2=102+q_1_2;
   q_1_3=queue_index-3;
   if(q_1_3<0) q_1_3=102+q_1_3;
   error1=(Z[q_1_1]+Z[q_1_2]+Z[q_1_3])/3;
   q_1_1=queue_index-1-length;
   if(q_1_1<0) q_1_1=102+q_1_1;
   q_1_2=queue_index-2-length;
   if(q_1_2<0) q_1_2=102+q_1_2;
   q_1_3=queue_index-3-length;
   if(q_1_3<0) q_1_3=102+q_1_3;
   error2=(Z[q_1_1]+Z[q_1_2]+Z[q_1_3])/3;
   DCal_D=error1-error2;
   return DCal_D;
}

void steer(void)
{
  int Steer_Temp;
  char e;
  if(Time>40) 
  {
    e=abs(SteerError)/40;
    if(e>9) e=9;
    if(RoadType<3) s_kp=ds_kp_min;
    else s_kp=ds_kp[e]; 
    Steer_Temp=s_kp*((float)SteerError);//-YaoError*20;//+2*Cal_D(5);
    if(abs(YaoError)>2) Steer_Temp=Steer_Temp-YaoError*20;
    /*
    LCD_clear();
    sprintf(mystr,"YaoError:%d",YaoError);
    LCD_Print(0,3,mystr);
    */
    //if(YaoError>2) Steer_Temp=Steer_Temp-YaoError*20;
    //if(YaoError<-2) Steer_Temp=Steer_Temp-YaoError*20;
    //Steer_Temp=s_kp*((float)SteerError);
    //Steer_Temp=s_kp*SteerError+s_kd*Cal_D(10);
    if(Steer_Temp<Steer_Min-Steer_Center) Steer=Steer_Min;
    else if(Steer_Temp>Steer_Max-Steer_Center) Steer=Steer_Max;
    else Steer=Steer_Center+Steer_Temp; 
  }
}

void Speed_Adjust(void)
{ 
  unsigned int speed_dang;
  
  if(Time<40) SpeedWant=Qibu_Speed_Tab[Time/10];
  else
  {
    //if(abs(SteerError)==Yaotou_abs&&abs(YaoError)>6) SpeedWant=Min_Speed;
    //else if(RoadType<3&&(L_BlackCount==0&&R_BlackCount>0)||(L_BlackCount>0&&R_BlackCount==0)) SpeedWant=Min_Speed;
    //else 
    //{
      
      if(slope_Flag==1) SpeedWant=Slope_Speed;
      else
      {
        speed_dang=(abs(Steer-Steer_Center))/10;
        if(speed_dang>SpeedDang) speed_dang=SpeedDang;
        
        if(RoadType<3)  
        {
          SpeedWant=Crazy_Speed;  
        }
        else 
        {
          SpeedWant=speed_tab[speed_dang];
          if(abs(Cal_D(30))<30) SpeedWant+=15;
          //if(SpeedWant>Max_Speed) SpeedWant=Max_Speed;
        } 
      }
  }
  /*
  OutData[0]=SpeedWant;
  OutData[1]=Steer-Steer_Center;
  OutData[2]=SteerError;
  OutData[3]=RoadType;
  OutPut_Data(); 
  */
}


void Yaotou_Judgement(void)
{  
  static int yao_cnt=0,cross_cnt=0;
  float laser_temp;
  char e,e1,ec;
  
  if(Time>20)
  {
    if(slope_Flag==0)
    {
      yao_cnt++;
      cross_cnt++;
      if(CrossFlag==1)
      { 
        CrossFlag=0;
        if(cross_cnt>1)
        {
          cross_cnt=0;
          if(SteerError>70) 
          {
            laser_temp=Yaotou+6;
            if(laser_temp>Yaotou_Center) laser_temp=Yaotou_Center;
            Yaotou=laser_temp;
          }
          else if(SteerError<-70) 
          {
            laser_temp=Yaotou-4;
            if(laser_temp<Yaotou_Center) laser_temp=Yaotou_Center;
            Yaotou=laser_temp;
          }
        }
      }
      else
      {
        cross_cnt=0;
        if(yao_cnt>2)
        {
          yao_cnt=0;
          d_YaoError=YaoError-YaoPreError; 
          //if(slope_Flag==1&&abs(d_YaoError)>2) YaoError=YaoPreError;
          YaoPreError=YaoError;  
          e=abs(YaoError); 
          e1=YaoError/3+2;
          ec=d_YaoError*3/4+2;
          if(e1<0) e1=0;else if(e1>4) e1=4;
          if(ec<0) ec=0;else if(ec>4) ec=4;
          /*
          if(RoadType==0)
          {
            y_ki=dy_ki_min;
            y_kp=1; 
          }
          else 
          { */
            y_kp=dy_kp[e1][ec];
            y_ki=dy_ki[e];
          //}
          //////////////////////////////////////////////////////////////////
          //laser_temp=(y_kp*d_YaoError+y_ki*YaoError+y_kd*dd_YaoError);
          laser_temp=(y_kp*d_YaoError+y_ki*(float)YaoError);
          //laser_temp=y_ki*(float)YaoError;
          /*
          if(RoadType<3) 
          {
            if(laser_temp>50) laser_temp=50;
            else if(laser_temp<-50) laser_temp=-50; 
          }
          else
          {
            if(laser_temp>155) laser_temp=155;
            else if(laser_temp<-155) laser_temp=-155;
          }
          */
          laser_temp+=Yaotou;
          if(laser_temp>Yaotou_Max)  laser_temp=Yaotou_Max;
          else if(laser_temp<Yaotou_Min)  laser_temp=Yaotou_Min;
          
          Yaotou=laser_temp;  
        }
      } 
    }
    
    else 
    {
      yao_cnt++;
      if(CrossFlag==1)
      { 
        Yaotou=Yaotou_Center;
        Steer=Steer_Center;
      }
      if(yao_cnt>3)
      {
        yao_cnt=0;
        d_YaoError=YaoError-YaoPreError;
        //if(abs(d_YaoError)>2) YaoError=YaoPreError;
        if(abs(YaoError)>2) YaoError=0;
        //dd_YaoError=d_YaoError-d_PreYaoError;  
        YaoPreError=YaoError;  
        //d_PreYaoError=d_YaoError; 
        e=abs(YaoError); 
        e1=YaoError/3+2;
        ec=d_YaoError*2/3+2;
        if(e1<0) e1=0;else if(e1>4) e1=4;
        if(ec<0) ec=0;else if(ec>4) ec=4;
        y_kp=dy_kp[e1][ec];
        y_ki=dy_ki[e];
        
        //////////////////////////////////////////////////////////////////
        //laser_temp=(y_kp*d_YaoError+y_ki*YaoError+y_kd*dd_YaoError);
        laser_temp=(y_kp*d_YaoError+y_ki*(float)YaoError);
        //laser_temp=y_ki*(float)YaoError;
        if(laser_temp>50) laser_temp=50;
        else if(laser_temp<-50) laser_temp=-50; 
        laser_temp+=Yaotou;
        if(laser_temp>Yaotou_Max_Slope)  laser_temp=Yaotou_Max_Slope;
        else if(laser_temp<Yaotou_Min_Slope)  laser_temp=Yaotou_Min_Slope;
        Yaotou=laser_temp; 
      }
    }
  }
} 
/*
void DianTou(void)
{
  if(RoadType<3&&(L_BlackCount==0&&R_BlackCount>0)||(L_BlackCount>0&&R_BlackCount==0))
  {
    Diantou=Diantou_Near;
  }
  else if(TypeChange==0&&RoadType<3) 
  {
    if(NewTypeLength3<10) Diantou=Diantou_Near;
    else 
    {
      Diantou=Diantou+(NewTypeLength3-10); 
      if(Diantou>Diantou_Far) Diantou=Diantou_Far;  
    }
  }
  LastRoadLength=RoadLength;
  
  LCD_clear();
  sprintf(mystr,"RoadType:%d",RoadType);
  LCD_Print(0,5,mystr);
  sprintf(mystr,"TypeChange:%d",TypeChange);
  LCD_Print(0,6,mystr);
  sprintf(mystr,"NewTypeTime:%d",NewTypeTime);
  LCD_Print(0,7,mystr);
  
}
*/

void Laser_Process(void)
{
   while(Laser_OK==0);
   Laser_OK=0;
   Get_Position();
   if(OpenQipaoFlag==1)
   {
     if(QiPao_Flag>0)  ShaChe_Flag=1;  
   }
   Renew_Record();
   Speed_Adjust();
   steer(); 
   Yaotou_Judgement();
   //Renew_RoadType();
}
