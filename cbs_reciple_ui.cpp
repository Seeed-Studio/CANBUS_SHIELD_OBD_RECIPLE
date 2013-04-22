/****************************************Copyright (c)****************************************************
**                            Shenzhen SeeedStudio Co.,LTD.
**
**                                 http://www.seeedstudio.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  cbs_reciple_ui_cpp
** Latest modified Date:       2012-7-23
** Latest Version:             v0.1
** Descriptions:               CAN BUS SHIELD RECIPLE UI
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 loovee
** Created date:               2012-7-23
** Version:                    v0.1
** Descriptions:
*********************************************************************************************************/
#include "cbs_reciple_ui.h"
//#include "cbs_reciple_data.h"
#include <stdint.h>
#include <TouchScreen.h>
#include <TFTv2.h>
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);                      /* init TouchScreen port pins   */

/*********************************************************************************************************
 ** Function name:           init
 ** Descriptions:            init ui, such as some vari, tft. 
*********************************************************************************************************/
void cbs_reciple_ui::init()
{
  m_nPage = 0;
  memset(m_nData, 0, 8*sizeof(INT32U));
  memset(m_nData_buf, 0, 8*sizeof(INT32U));
  memset( m_nSpeedBuf, 0, 8);
  memset(m_nSbHigh, 0, 8);
  Tft.TFTinit(); 
  TFT_BL_ON;
}

/*********************************************************************************************************
 ** Function name:           changPage
 ** Descriptions:            change Page, there is 2 page
*********************************************************************************************************/
void cbs_reciple_ui::changPage()
{
  m_nPage = 1 - m_nPage;
}

/*********************************************************************************************************
 ** Function name:           get_anytouch
 ** Descriptions:            if touch ,return 1, else return 0
*********************************************************************************************************/
INT8U cbs_reciple_ui::get_anytouch()
{
    Point p = ts.getPoint();
    if (p.z > ts.pressureThreshhold)return 1;
    return 0;
}

/*********************************************************************************************************
 ** Function name:           get_touch()
 ** Descriptions:            if get touch, with eliminate jitter
*********************************************************************************************************/
INT8U cbs_reciple_ui::get_touch()
{
  if(get_anytouch())
  {
    int tout = TIMEOUT;
    while(tout)
    {
      if(!get_anytouch())tout--;
      else tout = TIMEOUT;
    }
    return 1;
  }
  return 0;
}

/*********************************************************************************************************
 ** Function name:           disp_title_bg()
 ** Descriptions:            display title background
*********************************************************************************************************/
void cbs_reciple_ui::disp_title_bg(INT16U color)
{
  //Tft.fillScreen(WHITE);
  Tft.fillScreen(0, 239, 0, 319, WHITE);
  int y[4] = {Y_PARA_1, Y_PARA_2, Y_PARA_3, Y_PARA_4};
  for(int i = 0; i<4; i++)
  {
    Tft.fillRectangle(0, y[i], 240, PARA_HIGH, color);
  }
  Tft.fillRectangle(0, Y_PARA_5, 240, DOWN_HIGH, color);
}

/*********************************************************************************************************
 ** Function name:           disp_title(
 ** Descriptions:            display title such as "Engine Speed"
*********************************************************************************************************/
void cbs_reciple_ui::disp_title(INT8U line, char *str)
{
  int y[4] = {Y_PARA_1, Y_PARA_2, Y_PARA_3, Y_PARA_4};
  Tft.drawString(str,0+10, y[line-1]+7,2,BLACK);
}

/*********************************************************************************************************
 ** Function name:           disp_unit
 ** Descriptions:            display unit such as "km/h"
*********************************************************************************************************/
#define X_BEGIN_NUM 10
 
void cbs_reciple_ui::disp_unit(INT8U line, char *str, INT16U color)
{
  int y[4] = {Y_NUM_1, Y_NUM_2, Y_NUM_3, Y_NUM_4};
  Tft.drawString(str, X_BEGIN_NUM + 4*18 + 20, y[line-1]+DEPTH_UNIT2TOP,3,color);
}

/*********************************************************************************************************
 ** Function name:           disp_unit_oC
 ** Descriptions:            display unit temperature oC
*********************************************************************************************************/
void cbs_reciple_ui::disp_unit_oC(INT8U line, INT16U color)
{
  int y[4] = {Y_NUM_1, Y_NUM_2, Y_NUM_3, Y_NUM_4};
  Tft.drawChar('o', X_BEGIN_NUM + 4*18 + 20, y[line-1]+8, 2, color);
  Tft.drawChar('C', X_BEGIN_NUM + 4*18 + 30, y[line-1]+DEPTH_UNIT2TOP, 3, color);
}

/*********************************************************************************************************
 ** Function name:           disp_unit_page
 ** Descriptions:            show all unit
*********************************************************************************************************/
void cbs_reciple_ui::disp_unit_page()
{
  if(m_nPage == 0)
  {
    disp_unit(1, "L/100KM", WHITE);
    disp_unit(2, "RPM", WHITE);
    disp_unit_oC(3, WHITE);
    disp_unit_oC(4, WHITE);
    disp_unit(2, "KM/H", BLACK);
    disp_unit(3, "KM/H", BLACK);
    disp_unit(4, "KM", BLACK);
  }
  else
  { 
    disp_unit(2, "KM/H", WHITE);
    disp_unit(3, "KM/H", WHITE);
    disp_unit(4, "KM", WHITE);
    Tft.fillRectangle(0, Y_NUM_1, 240, NUM_HIGH, WHITE);

    disp_unit(1, "g/s", BLACK);
    disp_unit(2, "RPM", BLACK);
    disp_unit_oC(3, BLACK);
    disp_unit_oC(4, BLACK);
  }
}

/*********************************************************************************************************
 ** Function name:           disp_page
 ** Descriptions:            show page, but data
*********************************************************************************************************/
#define COLOR1 0x639
#define COLOR2 0xb6ac

void cbs_reciple_ui::disp_page()
{
  INT16U icolor[2] = {COLOR1, COLOR2};
  char cTitle[8][20] = {STR_P11, STR_P12, STR_P13, STR_P14, 
                        STR_P21, STR_P22, STR_P23, STR_P24};
  disp_title_bg(icolor[m_nPage]);
  for(int i = 0 ;i<4; i++)
  {
    disp_title(i+1, cTitle[4*m_nPage + i]);
  }  
  
  memset(m_nSbHigh, 0, 8);
  INT16U y_t[4] = {Y_NUM_1, Y_NUM_2, Y_NUM_3, Y_NUM_4};
  for(int i = 0; i<4; i++)
    Tft.fillRectangle(0, y_t[i], 240, 40, WHITE);
  disp_unit_page();
  if(m_nPage == 0)disp_time();
  
  int y_tt[4] = {Y_NUM_1, Y_NUM_2, Y_NUM_3, Y_NUM_4};
  for(int i = 0; i<4; i++)
  {
    if((m_nPage == 0) && (i == 0))continue;
    if(m_nData[m_nPage*4 + i]<10)show_thing(m_nData[i+m_nPage*4], m_nData[i+m_nPage*4] + 1, DEPTH_NUM2LEFT, y_tt[i] + DEPTH_UNIT2TOP, 4);
    else if(m_nData[m_nPage*4 + i]<100)show_thing(m_nData[i+m_nPage*4], m_nData[i+m_nPage*4] + 11, DEPTH_NUM2LEFT, y_tt[i] + DEPTH_UNIT2TOP, 4);
    else if(m_nData[m_nPage*4 + i]<1000)show_thing(m_nData[i+m_nPage*4], m_nData[i+m_nPage*4] + 111, DEPTH_NUM2LEFT, y_tt[i] + DEPTH_UNIT2TOP, 4);
    else if(m_nData[m_nPage*4 + i]<10000)show_thing(m_nData[i+m_nPage*4], m_nData[i+m_nPage*4] + 1111, DEPTH_NUM2LEFT, y_tt[i] + DEPTH_UNIT2TOP, 4);
    else show_thing(m_nData[i+m_nPage*4], m_nData[i+m_nPage*4] + 11111, DEPTH_NUM2LEFT, y_tt[i] + DEPTH_UNIT2TOP, 4);
  }
}

/*********************************************************************************************************
 ** Function name:           saveDataBuf
 ** Descriptions:            m_nData_Buf = m_nData
*********************************************************************************************************/
void cbs_reciple_ui::saveDataBuf()
{
  memcpy(m_nData_buf, m_nData, 8*sizeof(INT32U));
}

/*********************************************************************************************************
 ** Function name:           deal_t
 ** Descriptions:            for show_thing
*********************************************************************************************************/
void cbs_reciple_ui::deal_t(INT16U nData, INT16U nData_buf, INT8U *misk, INT8U num[4])
{
  int i;
  INT8U my_mist = 0;
  for(i=0;i<4;i++)
  {
    INT8U tmpD = nData%10;
    INT8U tmpDbuf = nData_buf%10;
    if(tmpD!=tmpDbuf)
    {
      my_mist|=(1<<i);
      num[4-i-1] = tmpD;
    }
    else
    {
      num[4-i-1]=0;
    }
    nData/=10;
    nData_buf/=10;
  }
  *misk = my_mist;
}

/*********************************************************************************************************
 ** Function name:           show_thing
 ** Descriptions:            for refresh
*********************************************************************************************************/
void cbs_reciple_ui::show_thing(INT16U d, INT16U d_buf, INT16U poX, INT16U poY, INT8U iWay)
{
  INT8U misk;
  INT8U bf[4];
  deal_t((INT16U)d, (INT16U)d_buf , &misk, bf);
  INT8U flag_t = 1;
  for(int i = iWay-1; i>=0; i--)
  {
    if(misk & (0x01<<i))
    {
      Tft.fillRectangle(poX+(iWay-1-i)*24, poY, 24, 24, WHITE);
      if(!((m_nPage == 0) && (poY == (Y_NUM_1 + DEPTH_UNIT2TOP))))
      {
        if((bf[3-i] == 0) && flag_t) {if(i>0)continue;}
        else flag_t = 0;
      }
      Tft.drawNumber(bf[3-i], poX+(iWay-1-i)*24, poY , 3, BLACK);     
    }
  }
}

/*********************************************************************************************************
 ** Function name:           timeRefresh
 ** Descriptions:            refresh data
*********************************************************************************************************/
void cbs_reciple_ui::cspRefresh()
{
  Tft.fillRectangle(0, Y_NUM_1, 100, 40, WHITE);
  float t = m_nData[TYPE_FUELCON]*1.0 /100/ 14.7;
  if(t>=10.0)Tft.drawFloat(t, 2,DEPTH_NUM2LEFT, Y_NUM_1+DEPTH_UNIT2TOP, 3, BLACK);
  else Tft.drawFloat(t, 2,DEPTH_NUM2LEFT+18, Y_NUM_1+DEPTH_UNIT2TOP, 3, BLACK);
}

  
/*********************************************************************************************************
 ** Function name:           dataRefresh
 ** Descriptions:            refresh data
*********************************************************************************************************/
void cbs_reciple_ui::dataRefresh()
{
  int y_t[] = {Y_NUM_1 + DEPTH_UNIT2TOP,Y_NUM_2 + DEPTH_UNIT2TOP,Y_NUM_3 + DEPTH_UNIT2TOP,Y_NUM_4 + DEPTH_UNIT2TOP};
  for(int i = 0; i<4; i++)
  {
    if(i==0 && m_nPage==0)timeRefresh();
    else if(i==0 && m_nPage==1)cspRefresh();
    else show_thing(m_nData[m_nPage*4 + i], m_nData_buf[m_nPage*4 + i], DEPTH_NUM2LEFT, y_t[i], 4);  // vehicle speed
  }
  saveSpeedBuf();
  disp_diaSpeed();
}

/*********************************************************************************************************
 ** Function name:           drawxx
 ** Descriptions:            u know
*********************************************************************************************************/
void cbs_reciple_ui::drawxx(INT8U iway, INT16U poy, INT8U high, INT16U color)
{
  int pox = (DDS_DEPTH - DDS_DEPTH_P)/2 + iway*DDS_DEPTH;
  poy -= high;
  
  Tft.fillRectangle(pox, poy, DDS_DEPTH_P, high, color);
}

/*********************************************************************************************************
 ** Function name:           saveSpeedBuf
 ** Descriptions:            u know
*********************************************************************************************************/
void cbs_reciple_ui::saveSpeedBuf()
{
  for(int i =0; i<=6; i++)
  {
    m_nSpeedBuf[i] = m_nSpeedBuf[i+1];
  }
  m_nSpeedBuf[7] = m_nData[TYPE_VSPEED];
  
}

/*********************************************************************************************************
 ** Function name:           disp_diaSpeed
 ** Descriptions:            
*********************************************************************************************************/
void cbs_reciple_ui::disp_diaSpeed()
{
  INT16U icolor[2] = {COLOR1, COLOR2};
  for(int i = 0; i<=7; i++)
  {
    int speedt = (int)m_nSpeedBuf[i]*HIGHMAX/SPEEDMAX - (int)m_nSbHigh[i];
    
    if(speedt == 0)continue;
    else if(speedt>0)
    {
      drawxx(i, 320 - m_nSbHigh[i], speedt, BLACK);
      m_nSbHigh[i] += speedt;
    }
    else
    {
      speedt = (int)m_nSbHigh[i] - (int)m_nSpeedBuf[i]*HIGHMAX/SPEEDMAX ;
      drawxx(i, 320-(m_nSpeedBuf[i]*HIGHMAX/SPEEDMAX), speedt, icolor[m_nPage]);
      m_nSbHigh[i] = m_nSpeedBuf[i]*HIGHMAX/SPEEDMAX ;
    }
  }
}

/*********************************************************************************************************
 ** Function name:           disp_diaSpeed
 ** Descriptions:            
*********************************************************************************************************/
void cbs_reciple_ui::disp_time()
{
  INT8U h =  m_nData[TYPE_RUNTIME] / 3600;
  INT8U m = (m_nData[TYPE_RUNTIME] / 60)%60;
  INT8U s =  m_nData[TYPE_RUNTIME] % 60;
  INT8U h_buf =  m_nData_buf[TYPE_RUNTIME] / 3600;
  INT8U m_buf = (m_nData_buf[TYPE_RUNTIME] / 60)%60;
  INT8U s_buf =  m_nData_buf[TYPE_RUNTIME] % 60;
  
  show_thing(h, h+11, DEPTH_NUM2LEFT, Y_NUM_1+DEPTH_UNIT2TOP, 2);
  Tft.drawChar(':', DEPTH_NUM2LEFT+20*2+3,Y_NUM_1+DEPTH_UNIT2TOP, 3, BLACK);
  show_thing(m, m+11, DEPTH_NUM2LEFT+20*3,Y_NUM_1+DEPTH_UNIT2TOP, 2);
  Tft.drawChar(':', DEPTH_NUM2LEFT+20*5+3,Y_NUM_1+DEPTH_UNIT2TOP, 3, BLACK);
  show_thing(s, s+11, DEPTH_NUM2LEFT+20*6,Y_NUM_1+DEPTH_UNIT2TOP, 2);
}

/*********************************************************************************************************
 ** Function name:           disp_diaSpeed
 ** Descriptions:            
*********************************************************************************************************/
void cbs_reciple_ui::timeRefresh()
{
  INT8U h =  m_nData[TYPE_RUNTIME] / 3600;
  INT8U m = (m_nData[TYPE_RUNTIME] / 60)%60;
  INT8U s =  m_nData[TYPE_RUNTIME] % 60;
  INT8U h_buf =  m_nData_buf[TYPE_RUNTIME] / 3600;
  INT8U m_buf = (m_nData_buf[TYPE_RUNTIME] / 60)%60;
  INT8U s_buf =  m_nData_buf[TYPE_RUNTIME] % 60;

  show_thing(h, h_buf, DEPTH_NUM2LEFT, Y_NUM_1+DEPTH_UNIT2TOP, 2);
  show_thing(m, m_buf, DEPTH_NUM2LEFT+20*3,Y_NUM_1+DEPTH_UNIT2TOP, 2);
  show_thing(s, s_buf, DEPTH_NUM2LEFT+20*6,Y_NUM_1+DEPTH_UNIT2TOP, 2);
}

cbs_reciple_ui UI;
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
