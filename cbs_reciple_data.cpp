/****************************************Copyright (c)****************************************************
**                            Shenzhen SeeedStudio Co.,LTD.
**
**                                 http://www.seeedstudio.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  cbs_reciple_data_cpp
** Latest modified Date:       2012-7-23
** Latest Version:             v0.1
** Descriptions:               main file
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 loovee
** Created date:               2012-7-23
** Version:                    v0.1
** Descriptions:
*********************************************************************************************************/
#include "cbs_reciple_data.h"
#include <mcp_can.h>
//#include <debug_lvc.h>

extern unsigned char getInterrupt();

INT32U char_meger(INT8U iHigh, INT8U iLow)
{
  INT32U t = 0;
  t = iHigh;
  t<<=8;
  return (t+iLow);
}

void cbd_reciple_data::init(void)
{
  m_cMode      = 0;
  m_cPid       = 0;
  m_nSpeed     = 0;
  memcpy(m_cSpeedBuf, 0, AVERAGENUM);

// CAN bus INIT 500k
  if(CAN.begin(CAN_500KBPS) == CAN_OK)
  {
#if DEBUGMODE
    Serial.println("CAN init ok!!");
#else
    ;
#endif
   }
  else 
  {
#if DEBUGMODE
    Serial.println("CAN INIT FAIL!!");
#else
    ;
#endif
  }
  
  CAN.init_Mask(0, 0, 0x7f0);
  CAN.init_Mask(1, 0, 0x7f0);
  CAN.init_Filt(0, 0, 0x7e0); 
  CAN.init_Filt(1, 0, 0x7e0);
  CAN.init_Filt(2, 0, 0x7e0);
  CAN.init_Filt(3, 0, 0x7e0);
  CAN.init_Filt(4, 0, 0x7e0);
  CAN.init_Filt(5, 0, 0x7e0);
  
  delay(10);

}

#define TOUT 3000

void cbd_reciple_data::sendOrder()
{

  INT8U len = 0;
  INT8U orBuf[8]= {0x02, m_cMode, m_cPid, 0x00, 0x00, 0x00, 0x00, 0x00};
  CAN.sendMsgBuf(0x7df, 0, 8, orBuf);
  
  while(CAN.checkReceive() == CAN_NOMSG);
  while(CAN.checkReceive() == CAN_NOMSG);
  while(CAN.checkReceive() == CAN_NOMSG);

  len = 0;
  memcpy(m_cData, 0, 8);
  CAN.readMsgBuf(&len, m_cData);  
  
  INT32U timeout = TOUT;
  INT8U t[8];
  
  while(timeout--)
  {
    if(getInterrupt())
    {
      CAN.readMsgBuf(&len, t);
      break;
    }
  }
}

void cbd_reciple_data::setModePid(INT8U cMode, INT8U cPid)
{
  m_cMode = cMode;
  m_cPid  = cPid;
}

void cbd_reciple_data::AvSpeedBufSave()
{
  memcpy(&m_cSpeedBuf[0], &m_cSpeedBuf[1], AVERAGENUM*sizeof(INT8U));
  m_cSpeedBuf[AVERAGENUM-1] = m_nSpeed;
}

INT32U cbd_reciple_data::AvSpeedCount()
{
  INT32U sum = 0;
  for(int i = 0; i<AVERAGENUM; i++)
  {
    sum += m_cSpeedBuf[i];
  }
  return sum/AVERAGENUM;
}
INT32U cbd_reciple_data::getData(INT8U type)
{
  switch(type)
  {
    ///***********************************running time******************************************
    case TYPE_RUNTIME:
    setModePid(0x01, 0x1f);
    sendOrder();
    return char_meger(m_cData[3], m_cData[4]);
    break;
    
    ///***********************************vehicle speed*****************************************
    case TYPE_VSPEED:
    setModePid(0x01, 0x0d);
    sendOrder();
    
    m_nSpeed = m_cData[3];
    AvSpeedBufSave();
    
    if(m_nSpeed<150)
    return (INT32U)m_nSpeed;
    else return m_cSpeedBuf[AVERAGENUM-1];
    break;
    
    ///***********************************average vehicle speed  *******************************
    case TYPE_AVSPEED:
    return AvSpeedCount();
    break;
    
    ///***********************************mileage***********************************************
    case TYPE_MILEAGE:
    setModePid(0x01, 0x31);
    sendOrder();
    return (char_meger(m_cData[3], m_cData[4]) - m_nMileage_init);
    break;
    
    ///***********************************InstantaneousFuelConsumption**************************
    case TYPE_FUELCON:
    setModePid(0x01, 0x10);
    sendOrder();
    return char_meger(m_cData[3], m_cData[4]);
    break;
    
    ///***********************************engine speed******************************************
    case TYPE_ENGINE_SPEED:
    setModePid(0x01, 0x0c);
    sendOrder();
    return (char_meger(m_cData[3], m_cData[4])/4);
    break;
    
    ///***********************************oil temperature***************************************
    case TYPE_OILTEMP:
    setModePid(0x01, 0x05);
    sendOrder();
    return (m_cData[3] - 40);
    break;
    ///***********************************cooltant temperature**********************************
    case TYPE_COOLTEMP:
    setModePid(0x01, 0x05);
    sendOrder();
    return (m_cData[3] - 40);
    break;
    
    ///***********************************something else ? *************************************
    default:
    
    ;
   }
}

cbd_reciple_data OBDDATA;

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
