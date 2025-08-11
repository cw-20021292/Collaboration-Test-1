/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "valve_nos.h"

void output_valve_nos(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8NOSValveONB;
#define            u8NOSValveON                           U8NOSValveONB.byte
#define            Bit0_Water_Error_NOS_On_State          U8NOSValveONB.Bit.b0
#define            Bit1_Filter_Open_NOS_On_State          U8NOSValveONB.Bit.b1
#define            Bit2_Filter_Cover_Open_NOS_On_State    U8NOSValveONB.Bit.b2

TYPE_BYTE          U8NOSValveOFFB;
#define            u8NOSValveOFF                         U8NOSValveOFFB.byte
#define            Bit0_Not_Use_State                    U8NOSValveOFFB.Bit.b0



/***********************************************************************************************************************/

bit bit_nos_output;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_nos(void)
{
    /***********************************************************************************************/

    if( Bit3_Leakage_Sensor_Error__E01 == SET )
    {
        if(gu8_uart_test_mode == NON_UART_TEST)
        {
            Bit0_Water_Error_NOS_On_State = SET;            // �����Ǹ� ��� (nos)        
        }
        else
        {
            Bit0_Water_Error_NOS_On_State = CLEAR;          /* �����˻���� �����ϸ� �뽺 ���� ���� 250321 CH.PARK */
        }
    }
    else
    {
        Bit0_Water_Error_NOS_On_State = CLEAR;
    }

    /* �����˻� ���� �� NOS ������ ������ */
    if(gu8_uart_test_mode == NON_UART_TEST)
    {
        /* ����, ����Ŀ�� �ϳ��� ������ �Լ� ���� 250219 CH.PARK */
        Bit1_Filter_Open_NOS_On_State = ~bit_filter_all;
    }
    else
    {
        Bit1_Filter_Open_NOS_On_State = CLEAR;   
    }

/***********************************************************************************************/
    if (u8NOSValveOFF > 0)
    {
        pVALVE_NOS = CLEAR;      /*off*/
        bit_nos_output = CLEAR;
    }
    else
    {
        if (u8NOSValveON > 0)
        {
            pVALVE_NOS = SET;    /*on*/
            bit_nos_output = SET;
        }
        else
        {
            pVALVE_NOS = CLEAR;  /*off*/
            bit_nos_output = CLEAR;
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




