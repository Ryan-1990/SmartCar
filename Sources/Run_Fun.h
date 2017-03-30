/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Run_Fun.h
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/






#include <hidef.h>      /* common defines and macros */
#include <stdio.h>
#include "derivative.h"
#include "define.h"
#include "Delay.h"
#include "SCI.h"
#include "OLED.h"	


void SetSpeed(int PWM);
void v_PIDInit(void);
void speed_tab_init(void);
void fuzzy_init(void);
void Set_Speed(int v); 
//void QiBu(void);
void steer(void);
void Renew_RoadType(void);
void Laser_Process(void);


