/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _CDS_H_
#define _CDS_H_

//

extern U16 gu16ADCds;
/////extern bit F_Save;
extern U8 gu8_Amb_Temperature_One_Degree;
extern bit F_IceFull;


/*#define ICESTOP_TIME_SIX_HOURS               60*60*6*/                 // ��ħ�� �������� 6�ð�(21600��)

#define ICESTOP_TIME_SIX_HOURS                 21600                 // ��ħ�� �������� 6�ð�(21600��)
#define ICESTOP_TIME_FIVE_HOURS                18000                 // ��ħ�� �������� 5�ð�(21600��)

#define POWER_SAVING_WAKEUP_DELAY_TIME         3000



#endif
