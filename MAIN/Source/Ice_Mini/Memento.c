/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Memento.h"

void ErrorSaveStart( U8 mu8_err_code );
void ErrorSave(void);

/*..�޸���..*/
U8 u8Memento_Buff[] = {0,0,0,0,0,0};
bit F_ErrorSave;
U8  u8ErrorSaveCount;

U8  u8LEDOnTime;            //LED ON Time Memento
U8  u8LEDMementoBlinkCnt;
U8  u8MementoBufferCnt;
bit F_Memento;

U8  u8LEDMementoStep; /**********test*******************/

U8 gu8_memento_e29_detail_code;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ErrorSaveStart( U8 mu8_err_code )
{
    U8 mu8_final_error = 0;
/**********..Error Code..*****************************************/
/**********..1: �޼�����(F_WaterSupplyError))..********************/
/**********..2: ��������(F_WaterLeakError))..**********************/
/**********..3: ���¿µ�����(F_SeatTempOverError))..**************/
/**********..4: ����µ�����(F_OutTempOverError))..***************/
/**********..5: ���Short/Open����(F_WaterTempShortOpenError))..*/
/**********..6: ����Short/Open����(F_SeatTempShortOpenError)..***/

    U8 mu8ErrorState = 0;

    if( mu8_err_code == 0 )
    {
        return;
    }
    else{}

    #if 0
    // 2�� - 101
    // 1�� - 102
    // 3�� - 103
    // 5�� - 104
    // 6�� - 105
    // 4�� - 106
    // 12�� - 107
    // �׿� - 108
    #endif

    /*..hui [23-9-26���� 5:43:04] �Ｚ COMP E29 ���� �����ڵ�� ����..*/
    if( mu8_err_code == 29 )
    {
        if( gu8_memento_e29_detail_code == 2 )
        {
            mu8_final_error = 101;
        }
        else if( gu8_memento_e29_detail_code == 1 )
        {
            mu8_final_error = 102;
        }
        else if( gu8_memento_e29_detail_code == 3 )
        {
            mu8_final_error = 103;
        }
        else if( gu8_memento_e29_detail_code == 5 )
        {
            mu8_final_error = 104;
        }
        else if( gu8_memento_e29_detail_code == 6 )
        {
            mu8_final_error = 105;
        }
        else if( gu8_memento_e29_detail_code == 4 )
        {
            mu8_final_error = 106;
        }
        else if( gu8_memento_e29_detail_code == 12 )
        {
            mu8_final_error = 107;
        }
        else
        {
            mu8_final_error = 108;
        }
    }
    else
    {
        mu8_final_error = mu8_err_code;
    }

    /*if(u8Memento_Buff[0] == mu8_err_code || mu8_err_code == 0)*/ /*..������ ������ ������..*/
    if(u8Memento_Buff[0] == mu8_final_error || mu8_final_error == 0) /*..������ ������ ������..*/
    {
        return;
    }
    else{}

    u8Memento_Buff[4] = u8Memento_Buff[3];
    u8Memento_Buff[3] = u8Memento_Buff[2];
    u8Memento_Buff[2] = u8Memento_Buff[1];
    u8Memento_Buff[1] = u8Memento_Buff[0];


    u8Memento_Buff[0] = mu8_final_error;


    F_ErrorSave = SET;  /*..���� ����..*/
    u8ErrorSaveCount = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ErrorSave(void)
{
    if(F_ErrorSave != SET)
    {
        return;
    }
    else{}

    gu8_eeprom_wbuf[0] = u8Memento_Buff[0];
    gu8_eeprom_wbuf[1] = u8Memento_Buff[1];
    gu8_eeprom_wbuf[2] = u8Memento_Buff[2];
    gu8_eeprom_wbuf[3] = u8Memento_Buff[3];
    gu8_eeprom_wbuf[4] = u8Memento_Buff[4];

    EepromPageWrite(MEMENTO_START_ADDR, gu8_eeprom_wbuf, MEMENTO_LENGTH);

    F_ErrorSave = CLEAR;
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

