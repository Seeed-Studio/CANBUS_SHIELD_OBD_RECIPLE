/****************************************Copyright (c)****************************************************
**                            Shenzhen SeeedStudio Co.,LTD.
**
**                                 http://www.seeedstudio.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  cbs_reciple_data.h
** Latest modified Date:       2012-7-23
** Latest Version:             v0.1
** Descriptions:               CAN BUS SHIELD RECIPLE  GET DATA
**                             
**--------------------------------------------------------------------------------------------------------
** Created by:                 loovee
** Created date:               2012-7-23
** Version:                    v0.1
** Descriptions:               
*********************************************************************************************************/
#ifndef _OBD_II_H_
#define _OBD_II_H_

#include "cbs_reciple_dfs.h"
#define AVERAGENUM 10
class cbd_reciple_data
{
  private:
  INT8U m_cMode;
  INT8U m_cPid;
  INT8U m_cData[8];
  INT32U m_nMileage_init;
  INT8U  m_nSpeed;
  INT8U  m_cSpeedBuf[AVERAGENUM];
  
  private:
  INT32U AvSpeedCount();
  void sendOrder();
  void AvSpeedBufSave();
  void setModePid(INT8U cMode, INT8U cPid);
  
  public:
  void init(void);
  INT32U getData(INT8U type);

};

extern cbd_reciple_data OBDDATA;
#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

