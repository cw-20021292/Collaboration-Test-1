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
#include    "valve_ice_tray.h"

void output_valve_ice_tray_feed3(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8IceTrayValveONB;
#define            u8IceTrayValveON                         U8IceTrayValveONB.byte
#define            Bit0_Ice_Make_Input_State                U8IceTrayValveONB.Bit.b0
#define            Bit1_Over_Ice_Melt_Input_State           U8IceTrayValveONB.Bit.b1
#define            Bit2_ITV_Ice_Tray_Ster_State             U8IceTrayValveONB.Bit.b2
#define            Bit3_Tray_Clean_State                    U8IceTrayValveONB.Bit.b3
#define            Bit4_Tray_retry_state                    U8IceTrayValveONB.Bit.b4


TYPE_BYTE          U8IceTrayValveOFFB;
#define            u8IceTrayValveOFF                         U8IceTrayValveOFFB.byte
#define            Bit0_Tray_Drain_Error_Off_State           U8IceTrayValveOFFB.Bit.b0
#define            Bit1_Tray_Leakage_Error_Off_State         U8IceTrayValveOFFB.Bit.b1



/***********************************************************************************************************************/


bit bit_tray_valve_output;

extern U8 tray_error_flag_E63;
extern U8 tray_abnormal_E63_step;
extern HOT_STER_STEP gu8_hot_ster_step;
extern bit F_Hot_Ster_ON;
extern WATER_OUT_STEP gu8_Water_Out_Step;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_ice_tray_feed3(void)
{
    /***********************************************************************************************/
    /***********************************************************************************************/
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        /* Ʈ���� �Լ��� ������� �ӽ��ߴ� */
        Bit0_Ice_Make_Input_State = ~F_WaterOut;
    }
    else
    {
        Bit0_Ice_Make_Input_State = CLEAR;
    }

    /***********************************************************************************************/
    /*if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)*/
    /*if(gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 6)*/
    if(gu8_over_ice_melt_proc == 1  || gu8_over_ice_melt_proc == 4 )
    {
        Bit1_Over_Ice_Melt_Input_State = (F_Safety_Routine & F_Ice_Tray_Down_Move_Reset & F_IceVV);
    }
    else
    {
        Bit1_Over_Ice_Melt_Input_State = CLEAR;
    }
    
    if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_INPUT_STATE )
        {
            /*..hui [25-4-8???? 9:54:41] ???? ????? ?????..*/
            if( gu8_hot_input_ster_step >= 0 && gu8_hot_input_ster_step <= 5 )
            {
                Bit2_ITV_Ice_Tray_Ster_State = SET;
            }
            else
            {
                Bit2_ITV_Ice_Tray_Ster_State = CLEAR;
            }
        }
        else
        {
            Bit2_ITV_Ice_Tray_Ster_State = CLEAR;
        }
    }
    else
    {
        Bit2_ITV_Ice_Tray_Ster_State = CLEAR;
    }

    /***********************************************************************************************/
    /***********************************************************************************************/
    /***********************************************************************************************/


    Bit0_Tray_Drain_Error_Off_State = Bit16_Drain_Pump_Error__E60;
    Bit1_Tray_Leakage_Error_Off_State = Bit3_Leakage_Sensor_Error__E01;

    /***********************************************************************************************/


    /*..hui [19-8-27���� 3:44:11] Ʈ���� �Լ� �� �¼� ���� �� Ʈ���� ��� OFF..*/
    /*..hui [19-8-27���� 3:44:17] �¼� ����� ��ȯ..*/

    /*..hui [19-8-27���� 7:24:57] �¼� ���� �Ӹ��ƴ϶� ����/�ü� �����߿��� Ʈ���� �Լ��� ��� ���..*/
    /*..hui [19-8-28���� 2:44:21] Ʈ���� �Լ� �ȵɰ�� ��õ� ��� �ð����� OFF �߰�..*/
		#if 0
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        Bit3_Tray_Hot_Out_Off_State = F_WaterOut;  /* | F_Tray_In_Error_Temporary;*/
    }
    else
    {
        Bit3_Tray_Hot_Out_Off_State = CLEAR;
    }
#endif
    /***********************************************************************************************/
    /*..hui [19-12-13���� 3:09:53] �� �� ������ ��� ������ �̸��϶��� ����..*/
/*
if( gu8_Room_Water_Level == ROOM_LEVEL_LOW)
    {
        Bit4_Tray_Low_Level_Off_State = SET;
    }
    else
    {
        Bit4_Tray_Low_Level_Off_State = CLEAR;
    }
*/
    // /* �غ�����(Ż������) �� Ʈ���̿� ���Ѹ��� */
    // if(tray_error_flag_E63 == SET)
    // {
    //     if( tray_abnormal_E63_step == 2 || tray_abnormal_E63_step == 4 )
    //     { 
    //         Bit4_Tray_retry_state  = ~F_WaterOut;
    //     }
    //     else
    //     {
    //         Bit4_Tray_retry_state = CLEAR;
    //     }
    // }
    // else
    // {
    //     Bit4_Tray_retry_state = CLEAR;
    // }

    /***********************************************************************************************/
    /***********************************************************************************************/

    if (u8IceTrayValveOFF > 0)
    {
        pVALVE_ICE_TRAY_IN = CLEAR;      /*off*/
        bit_tray_valve_output = CLEAR;
    }
    else
    {
        if (u8IceTrayValveON > 0)
        {
            pVALVE_ICE_TRAY_IN = SET;    /*on*/
            bit_tray_valve_output = SET;
        }
        else
        {
            pVALVE_ICE_TRAY_IN = CLEAR;  /*off*/
            bit_tray_valve_output = CLEAR;
        }
    }
    /***********************************************************************************************/
    /***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


