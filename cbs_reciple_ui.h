/****************************************Copyright (c)****************************************************
**                            Shenzhen SeeedStudio Co.,LTD.
**
**                                 http://www.seeedstudio.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  cbs_reciple_ui.h
** Latest modified Date:       2012-7-23
** Latest Version:             v0.1
** Descriptions:               CAN_BUS Shield reciple UI
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 loovee
** Created date:               2012-7-23
** Version:                    v0.1
** Descriptions:

*********************************************************************************************************/
#ifndef _CBS_RECIPLE_UI_H_
#define _CBS_RECIPLE_UI_H_

#include "cbs_reciple_dfs.h"

// tft touch shield
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3

#define PARA_HIGH 25
#define NUM_HIGH  40
#define DOWN_HIGH 320-4*(PARA_HIGH+NUM_HIGH)
#define DEPTH_UNIT2TOP  10
#define DEPTH_NUM2LEFT  5
#define Y_PARA_1  0
#define Y_PARA_2  Y_PARA_1+PARA_HIGH+NUM_HIGH //65
#define Y_PARA_3  Y_PARA_2+PARA_HIGH+NUM_HIGH //130
#define Y_PARA_4  Y_PARA_3+PARA_HIGH+NUM_HIGH //195
#define Y_PARA_5  Y_PARA_4+PARA_HIGH+NUM_HIGH //260
#define Y_NUM_1   Y_PARA_1+PARA_HIGH
#define Y_NUM_2   Y_PARA_2+PARA_HIGH
#define Y_NUM_3   Y_PARA_3+PARA_HIGH
#define Y_NUM_4   Y_PARA_4+PARA_HIGH

//Dynamic display of speed
#define SPEEDMAX 100
#define HIGHMAX  60
#define DDS_DEPTH_P 10
#define DDS_DEPTH 30

class cbs_reciple_ui
{
  public:
  INT8U m_nPage;
  
  INT32U m_nData[8];
  INT32U m_nData_buf[8];
  
  INT8U  m_nSpeedBuf[8];
  INT8U  m_nSbHigh[8];
  private:
  INT8U get_anytouch();  
  void disp_title_bg(INT16U color);
  void disp_title(INT8U line, char *str);
  void disp_unit(INT8U line, char *str, INT16U color);
  void disp_unit_oC(INT8U line, INT16U color);
  void disp_unit_page();
  void deal_t(INT16U nData, INT16U nData_buf, INT8U *misk, INT8U num[4]);
  void show_thing(INT16U d, INT16U d_buf, INT16U poX, INT16U poY, INT8U iWay);
  void drawxx(INT8U iway, INT16U poy, INT8U high, INT16U color);
  void disp_time();
  void timeRefresh(); 
  void cspRefresh();
  void saveSpeedBuf();
  void disp_diaSpeed();

  
  public:
  void init();             // init
  INT8U get_touch();       // if any touch?
  void changPage();        // get touch, then change page
  void disp_page();        // display page
  
  void dataRefresh();       // before get new data
  void saveDataBuf();       // after get new data, to refresh the display
};

extern cbs_reciple_ui UI;
#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

