/****************************************Copyright (c)****************************************************
 **                            Shenzhen SeeedStudio Co.,LTD.
 **
 **                                 http://www.seeedstudio.com
 **
 **--------------File Info---------------------------------------------------------------------------------
 ** File name:                  reciple.cpp
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
#include "cbs_reciple_ui.h"
#include "cbs_reciple_dfs.h"
#include <mcp_can.h>
#include <SPI.h>
#include <TouchScreen.h>
#include <stdint.h>
#include <TFTv2.h>

#define  TIMER2  1

#include <MsTimer2.h>

//********************** TIMER **************************
#define TIMERUNIT  250 // ms

boolean Flag_Timer   = 0;
boolean Flag_Timer_s = 0;
INT32U timerCount    = 0;
INT32U timerCount_s  = 0;
//INT32U timerCount_refresh = 0

void timer_interrupt()
{
    Flag_Timer   = 1;
    Flag_Timer_s = 1;
    timerCount++;
}
//********************** TIMER OVER********************

//can bus get data
unsigned char getInterrupt()
{
    if(!digitalRead(2)) return 1;
    else return 0;
}

//********************** BUTTON AND SeeeD*****************
#define button A5
void disp_seeed()
{
    while(!digitalRead(button));
}

// setup
void setup()
{
    pinMode(button, INPUT);
    pinMode(0, INPUT);
    digitalWrite(button, HIGH);
    digitalWrite(2, HIGH);
#if DEBUGMODE
    Serial.begin(115200);
#endif

    MsTimer2::set(TIMERUNIT, timer_interrupt); // init timer

    // UI init
    UI.init();

    delay(5);
    OBDDATA.init();

    // sd card init

    disp_seeed();
    UI.disp_page();

#if DEBUGMODE
    Serial.println("init over!!");
#endif

    MsTimer2::start();

}// setup over
int temp = 950;

void loop()
{
    if(UI.get_touch())
    {
        UI.changPage();
        UI.disp_page();
    }
    if(Flag_Timer)
    {
        MsTimer2::stop();
        UI.saveDataBuf();
        for(int i = 0; i<8; i++)
        {
            UI.m_nData[i] = OBDDATA.getData(i);
        }
#if DEBUGMODE
        Serial.println("datarefresh\r\n");
#endif
        UI.dataRefresh();
        Flag_Timer = 0;
        MsTimer2::start();
    }
}
/*********************************************************************************************************
 * END FILE
 *********************************************************************************************************/
