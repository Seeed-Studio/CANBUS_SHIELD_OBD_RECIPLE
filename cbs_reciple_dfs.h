/****************************************Copyright (c)****************************************************
**                            Shenzhen SeeedStudio Co.,LTD.
**
**                                 http://www.seeedstudio.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  obd_ii_dfs.h
** Latest modified Date:       2012-6-10
** Latest Version:             v0.1
** Descriptions:               obd_ii.h
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 loovee
** Created date:               2012-6-10
** Version:                    v0.1
** Descriptions:
*********************************************************************************************************/
#ifndef _CBS_RECIPLE_DFS_H_
#define _CBS_RECIPLE_DFS_H_

#ifndef INT8U
#define INT8U unsigned char
#endif
#ifndef INT16U
#define INT16U unsigned short
#endif
#ifndef INT32U
#define INT32U unsigned long
#endif

//MODE
#define MODE1    0x01
#define MODE2    0x02
#define MODE3    0x03
#define MODE4    0x04
#define MODE5    0x05
#define MODE6    0x06
#define MODE7    0x07
#define MODE8    0x08
#define MODE9    0x09

//PID
#define PID_RUNTIME             0x1f
#define PID_VSPEED              0x0d
#define PID_MILEAGE             0x31

#define PID_MAF                 0x10                            
#define PID_ENGINE_SPEED        0x0c
#define PID_COOLTEMP            0x05
#define PID_OILTEMP             0x00

//TYPE
#define TYPE_RUNTIME            0x00
#define TYPE_VSPEED             0x01
#define TYPE_AVSPEED            0x02
#define TYPE_MILEAGE            0x03

#define TYPE_FUELCON            0x04                              
#define TYPE_ENGINE_SPEED       0x05
#define TYPE_OILTEMP            0x06
#define TYPE_COOLTEMP           0x07

#define TIMEOUT 100

#define STR_P11 "Running Time"
#define STR_P12 "Vehicle Speed"
#define STR_P13 "Average Speed"
#define STR_P14 "Mileage"
#define STR_P21 "Consumption"
#define STR_P22 "Engine Speed"
#define STR_P23 "Lubricant Temp"
#define STR_P24 "Coolant Temp"

#define DEBUGMODE 0

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

