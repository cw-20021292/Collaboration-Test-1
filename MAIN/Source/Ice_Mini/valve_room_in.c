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
#include    "valve_room_in.h"

void output_valve_room_in_feed1(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8RoomInValveONB;
#define            u8RoomInValveON                      U8RoomInValveONB.byte
#define            Bit0_Room_In_Water_Out_On_State      U8RoomInValveONB.Bit.b0
#define            Bit1_Flushing_Heater_In_Valve_on     U8RoomInValveONB.Bit.b1
#define            Bit2_Ice_Make_Input_State       		U8RoomInValveONB.Bit.b2
#define            Bit3_Tray_retry_state                U8RoomInValveONB.Bit.b3
#define            Bit4_Tray_In_Water_State             U8RoomInValveONB.Bit.b4
#define			   Bit5_Cody_Water_Line_Clean_State		U8RoomInValveONB.Bit.b5  /* Cody Water Line Clean Service */
#define            Bit6_RIV_Release_Pressure_State      U8RoomInValveONB.Bit.b6

TYPE_BYTE          U8RoomInValveOFFB;
#define            u8RoomInValveOFF                     U8RoomInValveOFFB.byte
#define            Bit0_Room_In_Off_State               U8RoomInValveOFFB.Bit.b0

U8 gu8_release_pressure_timer;
U8 gu8_ice_melt_wait_timer;

extern bit bit_filter_all;
extern FLUSHING_STEP gu8_flushing_mode;
extern U8 gu8_Hot_Filling_Step;
extern bit F_First_Hot_Effluent;
extern U8 tray_error_flag_E63;
extern U8 tray_abnormal_E63_step;
// extern U8 gu8_tray_hotster_cold_drain;
extern U8 gu8_hot_wait_step;
/***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_room_in_feed1(void)
{
    /* �����ϱ� ���� Ʈ���� �Լ� �� �����Լ���� open */
    if(gu8IceStep == STATE_20_WATER_IN_ICE_TRAY)
    {
        Bit2_Ice_Make_Input_State = SET;
    }
    else
    {
        Bit2_Ice_Make_Input_State = CLEAR;
    }

/***********************************************************************************************/
    /* ���� ���� �� �����Լ���� open */
    if( F_WaterOut == SET )
    {
        if(( u8WaterOutState == PURE_WATER_SELECT )
        && (u8IceOutState != ICE_SELECT__ICE_WATER)
        )
    {
            if( gu8_Water_Out_Step >= STATE_10_WATER_IN_FEED_ON_STATE
            && gu8_Water_Out_Step <= STATE_40_EXTRACT_VALVE_OFF_STATE )
            {
                Bit0_Room_In_Water_Out_On_State = SET;
            }
            else
            {
                Bit0_Room_In_Water_Out_On_State = CLEAR;
            }
        }
        else
        {
            Bit0_Room_In_Water_Out_On_State = CLEAR;
        }
    }
    else
    {
        Bit0_Room_In_Water_Out_On_State = CLEAR;
    }

    if(F_Safety_Routine == SET)
    {
        if(F_Ice_Tray_Down_Move_Reset == SET)
        {
            if( gu8_over_ice_melt_proc == 1 || gu8_over_ice_melt_proc == 4)
            {
                if(bit_tray_valve_output == SET)
                {
                    /*..hui [20-4-29���� 11:13:35] Ʈ���� ��� ������ 300ms�Ŀ� ���� ��������..*/
                    if(gu8_ice_melt_wait_timer >= 5)
                    {
                        gu8_ice_melt_wait_timer = 5;
                        Bit3_Tray_retry_state = SET;
                    }
                    else
                    {
                        gu8_ice_melt_wait_timer++;
                    }
                }
                else
                {
                gu8_ice_melt_wait_timer = 0;
                Bit3_Tray_retry_state = CLEAR;
                }
            }
            else
            {
            gu8_ice_melt_wait_timer = 0;
            Bit3_Tray_retry_state = CLEAR;
            }
        }
        else
        {
            gu8_ice_melt_wait_timer = 0;
            Bit3_Tray_retry_state = CLEAR;
        }
    }
    else
    {
        gu8_ice_melt_wait_timer = 0;
        Bit3_Tray_retry_state = CLEAR;
    }

#if 0
    if(tray_error_flag_E63 == SET)
	{
		if( tray_abnormal_E63_step == 2 || tray_abnormal_E63_step == 4 )
		{ 
			Bit3_Tray_retry_state  = SET;
		}
		else
		{
			Bit3_Tray_retry_state = CLEAR;
		}
	}
	else
	{
		Bit3_Tray_retry_state = CLEAR;
	}
#endif

#if 0
		if(gu8_flushing_mode == FLUSHING_FILTER)
		{
			if(gu8_filter_flushing_step == 1)
			{
				Bit1_Flushing_Heater_In_Valve_on = SET;
			}
			
		}
		else
#endif

#if 0
    /* �÷��� - ���� ä��� �� �� �����Լ���� open */
    if(gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE)
    {
        if( gu8_Hot_Filling_Step >= 1 && gu8_Hot_Filling_Step <= 6 )
        {
            Bit1_Flushing_Heater_In_Valve_on = F_First_Hot_Effluent;
        }
        else
        {
            Bit1_Flushing_Heater_In_Valve_on= CLEAR;
        }
    }
    else
    {
        Bit1_Flushing_Heater_In_Valve_on = CLEAR;
    }
#endif

    /* �ڵ����λ�� Cody Water Line Clean Service */
    if(cody_water_line.gu8_start == SET)
    {
        if((cody_water_line.gu8_step == 0)
        || (cody_water_line.gu8_step == 4)
        )
        {
            Bit5_Cody_Water_Line_Clean_State = SET;
        }
        else
        {
            Bit5_Cody_Water_Line_Clean_State = CLEAR;
        }
    }
    else
    {
        Bit5_Cody_Water_Line_Clean_State = CLEAR;
    }

    /* ���ͱ�ü �� �з»��� */
    if( bit_filter_all == CLEAR )
    {
        gu8_release_pressure_timer++;

        if( gu8_release_pressure_timer >= 70 )
        {
            gu8_release_pressure_timer = 70;
            Bit6_RIV_Release_Pressure_State = CLEAR;
        }
        else
        {
            Bit6_RIV_Release_Pressure_State = SET;
        }
    }
    else
    {
        gu8_release_pressure_timer = 0;
        Bit6_RIV_Release_Pressure_State = CLEAR;
    }

/***********************************************************************************************/
    if (u8RoomInValveOFF > 0)
    {
        pVALVE_ROOM_IN = CLEAR;      /*off*/
    }
    else
    {
        if (u8RoomInValveON > 0)
        {
            pVALVE_ROOM_IN = SET;    /*on*/
        }
        else
        {
            pVALVE_ROOM_IN = CLEAR;  /*off*/
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




