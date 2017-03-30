/******************************************************************************\
*  Copyright (C) 2012 Nan Li, Tianjin University 
*  ALL RIGHTS RESERVED
*  Filename:Scan_Key.h
*  Version: 1.0
*  Author: Nan Li
\******************************************************************************/





#include <hidef.h>      
#include "derivative.h" 
#include "Delay.h"



#define Hang1 PORTE_PE2
#define Hang2 PORTE_PE3
#define Hang3 PORTE_PE5
#define Hang4 PTS_PTS3

#define Lie1  PORTE_PE4
#define Lie2  PORTE_PE7
#define Lie3  PTS_PTS2


unsigned int Scan_Key(void);