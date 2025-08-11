/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "valve_overflow.h"

void output_valve_overflow_nos4(void);

TYPE_WORD          U16OverFlowValveOnW;
#define            u16OverFlowValveON                                 U16OverFlowValveOnW.word
#define            u8OverFlowValveOn_L                                U16OverFlowValveOnW.byte[0]
#define            u8OverFlowValveOn_H                                U16OverFlowValveOnW.byte[1]
#define            Bit0_OverFlow_Valve_Extract_On_State               U16OverFlowValveOnW.Bit.b0
#define            Bit1_flushing_Cold_Overflow_ON                     U16OverFlowValveOnW.Bit.b1
#define            Bit2_Air_Vent_State               		      	  U16OverFlowValveOnW.Bit.b2
#define            Bit3_Ice_Make_Input_State               	      	  U16OverFlowValveOnW.Bit.b3
#define            Bit4_OverFlow_Valve_IcewaterExtract_On_State       U16OverFlowValveOnW.Bit.b4
#define            Bit5_HDN4_Buffer_Remain_Water_State     			  U16OverFlowValveOnW.Bit.b5
#define            Bit6_flushing_hot_fill                         	  U16OverFlowValveOnW.Bit.b6
#define            Bit7_OFV_Ice_Tray_Ster_State                       U16OverFlowValveOnW.Bit.b7
#define            Bit8_CD_Circul_Drain_Off_State_State           	  U16OverFlowValveOnW.Bit.b8    
#define			   Bit9_Cody_Water_Line_Clear_State					  U16OverFlowValveOnW.Bit.b9

TYPE_BYTE          U8OverFlowValveOFFB;
#define            u8OverFlowValveOFF                                 U8OverFlowValveOFFB.byte
#define            Bit0_OverFlow_Valve_Off_State                      U8OverFlowValveOFFB.Bit.b0

extern bit F_IceOut;
extern FLUSHING_STEP gu8_Ice_Out_Step;
extern bit F_Circul_Drain;
extern bit F_DrainStatus;
extern bit F_auto_drain_mode_cold_water_valve_out;
extern special_func cody_water_line;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_overflow_nos4(void)
{
	if( F_WaterOut == SET )
    {
		/* �ü�, ������ ���� �� overflow ��� ���� */
		if(( u8WaterOutState == COLD_WATER_SELECT )
		|| (u8IceOutState == ICE_SELECT__ICE_WATER )	/* �ü� OR ������ ���� �� OVERFLOW VALVE ���� */
		)
        {
            // if( gu8_Water_Out_Step >= STATE_10_WATER_IN_FEED_ON_STATE
			// && gu8_Water_Out_Step <= STATE_11_COLD_WATER_PRESSURE_PREVENT_STATE )
            // {
			// 	// ���� �ʱ� 0.3 ~ 0.4SEC�� OVERFLOW OPEN
            //     Bit0_OverFlow_Valve_Extract_On_State = CLEAR;
            // }
            // else
            // {
            //     Bit0_OverFlow_Valve_Extract_On_State = SET;
            // }

			/* �ü� ���� �� OVERFLOW, �ü��Լ� ��� �ݰ� ���� �� 0.3�� ���Ŀ� ������ 
			��� �з��̶� ���� ������ ���� (�÷Ằ �������� ���� ���) - Water������ ��û 250731 CH.PARK */
			if( gu8_Water_Out_Step >= STATE_10_WATER_IN_FEED_ON_STATE
			&& gu8_Water_Out_Step <= STATE_40_EXTRACT_VALVE_OFF_STATE )
            {
                Bit0_OverFlow_Valve_Extract_On_State = SET;
            }
            else
            {
                Bit0_OverFlow_Valve_Extract_On_State = CLEAR;
            }

        }
		else if( u8WaterOutState == HOT_WATER_SELECT )				/* �¼������� �� overflow��� ���� */
		{
			if( gu8_Water_Out_Step == STATE_32_WATER_AIR_VENT_STATE )
			{
				Bit2_Air_Vent_State = CLEAR;
			}
			// �� 2025-06-11 Phil
			else if( gu8_Water_Out_Step == STATE_21_HOT_PRE_HEATING_BUFFER_DRAIN_STATE )
			{
				Bit2_Air_Vent_State = SET;
			}
			// �� 2025-06-11 Phils
			else
			{
				Bit2_Air_Vent_State = SET;
			}
		}
		else
        {
            Bit0_OverFlow_Valve_Extract_On_State = SET;
        }
    }
    else
    {
		Bit2_Air_Vent_State = CLEAR;
		Bit0_OverFlow_Valve_Extract_On_State = CLEAR;
	}

	if(F_IceOut == SET)
	{
		if((gu8_Ice_Out_Step >= STATE_20_ICEWATER_COLD_FFED_ON_STATE)
		&& (gu8_Ice_Out_Step <= STATE_41_ICEWATER_COLD_FEED_OFF_STATE)
		)
		{
			Bit4_OverFlow_Valve_IcewaterExtract_On_State = SET;
		}
		else
		{
			Bit4_OverFlow_Valve_IcewaterExtract_On_State = CLEAR;
		}
	}
	else
	{
		Bit4_OverFlow_Valve_IcewaterExtract_On_State = CLEAR;
	}

	if(gu8_flushing_mode == FLUSHING_FILTER)
	{
		if(gu8_filter_flushing_step >= 1 && gu8_filter_flushing_step <= 3)
		{
			Bit1_flushing_Cold_Overflow_ON = SET;
		}
		else
		{
			Bit1_flushing_Cold_Overflow_ON = CLEAR;
		}
	}
	else if(gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE)
	{
		if((gu8_cold_tank_fill_step >= COLD_TANK_FILL_OVERFLOW_OPEN)
		&& (gu8_cold_tank_fill_step <= COLD_TANK_FILL_COLD_CLOSE)
		)
		{
			// OVERFLOW ��� OPEN
			Bit1_flushing_Cold_Overflow_ON = CLEAR;
		}
		else
		{
			// OVERFLOW ��� CLOSE
			Bit1_flushing_Cold_Overflow_ON = SET;
		}
	}
	else if(gu8_flushing_mode == FLUSHING_COLD_TANK)
	{
		if(gu8_cold_tank_flushing_step == COLDTANK_FLUSHING_INIT)
		{
			// OVERFLOW ��� OPEN
			Bit1_flushing_Cold_Overflow_ON = CLEAR;
		}
		else if(gu8_cold_tank_flushing_step == COLDTANK_FLUSHING_5MINUTE)
		{
			// OVERFLOW ��� OPEN
			Bit1_flushing_Cold_Overflow_ON = CLEAR;
		}
		else
		{
			// OVERFLOW ��� CLOSE
			Bit1_flushing_Cold_Overflow_ON = SET;
		}
	}
	else
	{
		// OVERFLOW ��� CLOSE !!
		Bit1_flushing_Cold_Overflow_ON = CLEAR;
	}

	if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE)
	{
		/* �¼���ũ ä��� �ϴ� ���ȿ��� ��� �ݾƳ��� �Ϸ�Ǹ� ���� */
		if(gu8_Hot_Filling_Step == 6)
		{
			Bit6_flushing_hot_fill = CLEAR;
		}
		else
		{
			Bit6_flushing_hot_fill = SET;
		}
	}
	else
	{
		Bit6_flushing_hot_fill = CLEAR;
	}

	if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
	{
		Bit3_Ice_Make_Input_State = SET;
	}
	else
	{
		Bit3_Ice_Make_Input_State = CLEAR;
	}

	if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_PREHEAT )
        {
            /*..hui [25-4-8���� 9:54:35] ������..*/
            if( gu8_preheat_ster_step >= 1 )
            {
                Bit7_OFV_Ice_Tray_Ster_State = SET;
            }
            else
            {
                Bit7_OFV_Ice_Tray_Ster_State = CLEAR;
            }
        }
        else if( gu8_ice_ster_mode == STER_MODE_HOT_INPUT_STATE )
        {
            /*..hui [25-4-8���� 9:54:41] ���� Ʈ���� �Լ���..*/
            if( gu8_hot_input_ster_step >= 0 && gu8_hot_input_ster_step <= 4 )
            {
                Bit7_OFV_Ice_Tray_Ster_State = SET;
            }
            else
            {
                Bit7_OFV_Ice_Tray_Ster_State = CLEAR;
            }
        }
        else
        {
            Bit7_OFV_Ice_Tray_Ster_State = CLEAR;
        }
    }
    else
    {
        Bit7_OFV_Ice_Tray_Ster_State = CLEAR;
    }

	/* ��ȯ��� ������ : �����÷ο� NOS ��� ��� */
	if( F_Circul_Drain == SET )
    {
        if( F_DrainStatus == SET )
        {
            /*..hui [23-8-25???? 1:19:18] ?????? ???? ??..*/
            if(F_auto_drain_mode_cold_water_valve_out == SET)
            {
                Bit8_CD_Circul_Drain_Off_State_State = SET;
            }
            else
            {
                Bit8_CD_Circul_Drain_Off_State_State = CLEAR;
            }
        }
        else
        {
            Bit8_CD_Circul_Drain_Off_State_State = CLEAR;
        }
    }
    else
    {
        Bit8_CD_Circul_Drain_Off_State_State = CLEAR;
    }

	/* [�ӽ�] ���λ�ո�� �ü����� �ÿ��� OVERFLOW ��� CLOSE 250708 */
	if(cody_water_line.gu8_start == SET)
	{
		if(cody_water_line.gu8_step == 2)
		{
			// OVERLFOW ��� CLOSE
			Bit9_Cody_Water_Line_Clear_State = SET;
		}
		else
		{
			// OVERLFOW ��� OPEN
			Bit9_Cody_Water_Line_Clear_State = CLEAR;
		}
	}
	else
	{
		// OVERLFOW ��� OPEN
		Bit9_Cody_Water_Line_Clear_State = CLEAR;
	}

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
    if (u8OverFlowValveOFF > 0)
    {
        pVALVE_HOT_COLD_OVERFLOW = CLEAR;      /*off*/
    }
    else
    {
        if (u16OverFlowValveON > 0)
        {
            pVALVE_HOT_COLD_OVERFLOW = SET;    /*on*/
        }
        else
        {
            pVALVE_HOT_COLD_OVERFLOW = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




