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
#include    "Fan_Control.h"




void output_fan(void);
U8 get_hotgas_fan_operation(void);



TYPE_BYTE          U8CoolingFanONB;
#define            u8CoolingFanON                              U8CoolingFanONB.byte
#define            Bit0_CF_Cold_Make_State                     U8CoolingFanONB.Bit.b0
#define            Bit1_CF_Ice_Make_State                      U8CoolingFanONB.Bit.b1
#define            Bit2_CF_Hot_Gase_State                      U8CoolingFanONB.Bit.b2
#define            Bit3_CF_Fan_Delay_Operation_State           U8CoolingFanONB.Bit.b3
#define            Bit4_CF_Fan_First_Operation_State           U8CoolingFanONB.Bit.b4





TYPE_BYTE          U8CoolingFanOFFB;
#define            u8CoolingFanOFF                             U8CoolingFanOFFB.byte
//#define            Bit0_Filling_Valve_Error_State            U8CoolingFanOFFB.Bit.b0

bit bit_comp_off_check;
U16 gu16_fan_delay_timer;

bit bit_fan_first;
U16 gu16_fan_first_timer;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_fan(void)
{
    U8 mu8_hot_gas_fan = 0;

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( F_FW_Version_Display_Mode == CLEAR )
    {
        #if 0
        /*..hui [24-3-25���� 2:20:03] �ܱ� 33�� ���Ͽ����� FAN 5�� ���� ����..*/
        /*..hui [24-3-25���� 3:31:18] ���� �������� Ȯ��..*/
        if( gu8_Amb_Temperature_One_Degree < 34 )
        {
            bit_fan_first = SET;
        }
        else{}
        #endif

        return;
    }
    else{}

    //Bit0_CF_Cold_Make_State = F_Comp_Output;

    if( Bit0_Cold_Mode_On_State == SET )
    {
        Bit0_CF_Cold_Make_State = SET;
    }
    else
    {
        Bit0_CF_Cold_Make_State = CLEAR;
    }

    /*..hui [23-4-13���� 10:11:47] ���� ���� - Ʈ���� �ø��� COMP ���� �� �ٷ� ����..*/
    /*..hui [23-4-13���� 10:12:09] ù ���� - Ʈ���� �ø��� �� �ְ� COMP ���� �� ����..*/
    if( gu8IceStep >= STATE_14_CHECK_ICE_TRAY_HZ && gu8IceStep <= STATE_41_GAS_SWITCH_HOT_GAS )
    {
        /*Bit1_CF_Ice_Make_State = F_Comp_Output;*/
        Bit1_CF_Ice_Make_State = SET;
    }
    else
    {
        Bit1_CF_Ice_Make_State = CLEAR;
    }


    if( gu8IceStep >= STATE_42_CALC_HOT_GAS_TIME && gu8IceStep <= STATE_43_ICE_TAKE_OFF )
    {
        mu8_hot_gas_fan = get_hotgas_fan_operation();

        if( mu8_hot_gas_fan == SET )
        {
            /*Bit2_CF_Hot_Gase_State = F_Comp_Output;*/
            Bit2_CF_Hot_Gase_State = SET;
        }
        else
        {
            Bit2_CF_Hot_Gase_State = CLEAR;
        }
    }
    else
    {
        Bit2_CF_Hot_Gase_State = CLEAR;
    }


    /*..hui [24-3-25���� 2:13:27] ���� OFF �� 15�а� ���� �� OFF..*/
    if( F_Comp_Output == SET )
    {
        /*..hui [24-3-25���� 4:39:49] �ܱ�µ� 34�� �̻󿡼���..*/
        /*if( gu8_Amb_Temperature_One_Degree >= 34 )*/
        /*..hui [25-3-19���� 5:44:26] 14�� �̻󿡼��� 5�� ���� ������ OFF �̰�δ�..*/
        if( gu8_Amb_Temperature_One_Degree > HOT_GAS_AMB_TEMP_13_DIGREE )
        {
            bit_comp_off_check = SET;
        }
        else{}

        gu16_fan_delay_timer = 0;
        Bit3_CF_Fan_Delay_Operation_State = CLEAR;
    }
    else
    {
        /*..hui [24-3-25���� 4:39:41] ���� �����Ŀ��� ����..*/
        if( gu8IceStep > STATE_0_STANDBY )
        {
            bit_comp_off_check = CLEAR;
        }
        else{}

        if( bit_comp_off_check == SET )
        {
            gu16_fan_delay_timer++;

            if( gu16_fan_delay_timer >= FAN_DELAY_5_MIN )
            {
                bit_comp_off_check = CLEAR;
                gu16_fan_delay_timer = 0;
                Bit3_CF_Fan_Delay_Operation_State = CLEAR;
            }
            else
            {
                Bit3_CF_Fan_Delay_Operation_State = SET;
            }
        }
        else
        {
            gu16_fan_delay_timer = 0;
            Bit3_CF_Fan_Delay_Operation_State = CLEAR;
        }
    }

    #if 0
    /*..hui [24-3-25���� 2:20:03] �ܱ� 33�� ���Ͽ����� FAN 5�� ���� ����..*/
    if( gu8_Amb_Temperature_One_Degree < 34 )
    {
        bit_fan_first = SET;
    }
    else{}
    #endif

    #if 0
    /*..hui [24-3-25���� 2:13:07] ���� �ΰ� �� 5�е��� ������ ����..*/
    if( bit_fan_first == CLEAR )
    {
        gu16_fan_first_timer++;

        /*..hui [23-7-12���� 11:21:08] ó�� �����Ѱ� ����Ż�� �� 5�е��� FAN ���� - ��������..*/
        if( gu16_fan_first_timer >= 3000 )
        {
            bit_fan_first = SET;

            gu16_fan_first_timer = 0;
            Bit4_CF_Fan_First_Operation_State = CLEAR;
        }
        else
        {
            Bit4_CF_Fan_First_Operation_State = SET;
        }
    }
    else
    {
        gu16_fan_first_timer = 0;
        Bit4_CF_Fan_First_Operation_State = CLEAR;
    }
    #endif


    #if 0
    /*..hui [23-9-4���� 2:51:07] Ʈ���� �������� ��õ��� �غ��۾� �ְ��� �����Ҷ� ����..*/
    if( F_Safety_Routine == SET && F_Ice_Tray_Down_Move_Reset == SET )
    {
        if( gu8_over_ice_melt_proc == 5 )
        {
            mu8_hot_gas_fan = get_hotgas_fan_operation();

            if( mu8_hot_gas_fan == SET )
            {
                Bit3_CF_Tray_Melt_Operation_State = SET;
            }
            else
            {
                Bit3_CF_Tray_Melt_Operation_State = CLEAR;
            }
        }
        else
        {
            Bit3_CF_Tray_Melt_Operation_State = CLEAR;
        }
    }
    else
    {
        Bit3_CF_Tray_Melt_Operation_State = CLEAR;
    }
    #endif

    /*..hui [23-9-22���� 9:54:36] �غ� ���۶� �ְ��� ����..*/
    /*Bit3_CF_Tray_Melt_Operation_State = CLEAR;*/

/***********************************************************************************************/
    if (u8CoolingFanOFF > 0)
    {
        pDC_FAN = CLEAR;  /*off*/
    }
    else
    {
        if (u8CoolingFanON > 0)
        {
            pDC_FAN = SET; /*on*/
        }
        else
        {
            pDC_FAN = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_hotgas_fan_operation(void)
{
    U8 mu8_return = 0;

    if( gu8_Amb_Temperature_One_Degree < HOT_GAS_AMB_TEMP_9_DIGREE )
    {
        mu8_return = CLEAR;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_13_DIGREE )
    {
        /*..hui [23-4-7���� 1:23:42] 9�� ~ 13��..*/
        mu8_return = CLEAR;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_19_DIGREE )
    {
        /*..hui [23-4-7���� 1:23:55] 14�� ~ 19��..*/
        mu8_return = CLEAR;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_24_DIGREE )
    {
        /*..hui [23-4-7���� 1:24:08] 20�� ~ 24��..*/
        mu8_return = SET;
    }
    else if( gu8_Amb_Temperature_One_Degree <= HOT_GAS_AMB_TEMP_29_DIGREE )
    {
        /*..hui [23-4-7���� 1:24:18] 25�� ~ 29��..*/
        mu8_return = SET;
    }
    else
    {
        /*..hui [23-4-7���� 1:24:23] 30�� �̻�..*/
        mu8_return = SET;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/






