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
#include    "Key_Handling.h"
#include "WIFI_SetFunctionData.h"
#include "WIFI_A101x_FunctionList.h"
/**********************************************************************************************/
/* �Ϲݻ��� Ű�Է� ó�� */
void key_ice_select_job(void);
void key_ice_water_select_job(void);
void key_hot_water_select_job(void);
void hot_setting_change(void);
void key_ambient_water_select_job(void);
void key_cold_water_select_job(void);
void key_amount_select_job(void);
void key_my_select_job(void);
/**********************************************************************************************/
/* ������� Ű�Է� ó�� */
void key_setting_select_job(void);
void key_setting_ice_size(void);
void key_setting_ice_off(void);
void key_setting_ice_lock(void);
void key_setting_hot_lock(void);
void key_setting_fast_icemake(void);
void key_setting_cold_power(void);
void key_setting_cold_off(U8 mu8_setting);
void key_setting_sleepmode(void);
void key_setting_all_lock_on(void);
/**********************************************************************************************/
/**********************************************************************************************/

//================================== Key Flag
bit F_KeySet;
bit F_ExtractKeySet;
bit F_TestKeySet;
bit F_LongKeySet;
bit F_IceKeySet;
bit F_Cold_Enable;
bit F_ColdOut;
bit F_ColdOn;
bit F_ColdOff;
bit F_Hot_Enable;
bit F_HotOut;
bit F_HotOn;
bit F_HotOff;
bit F_Room;
bit F_RoomOut;
bit F_Save;
bit F_Conty;
bit F_ContyGo;
bit F_Hot_Lock;
bit F_All_Lock;
bit F_BeIce;
bit F_IceOn;
bit F_IceBreak;     /* ����Ÿ�� ���� ���� �÷��� �߰� 250217 CH.PARK */
bit F_IceWaterOn;
bit F_Ice_Lock;
///bit F_IceOut;
bit F_IceOutStop;
bit F_LEDOff;
bit F_ColdSet;
bit F_HotSet;
bit F_IcemakeSet;
bit F_SaveSet;
bit F_KeySetBuz;
bit F_SterAuto;
bit F_SterLED;
bit F_Altitude;
bit Be_COMP;
bit Be_EW_POW;
bit Be_F_EWDrainPump;
//================================== S/W ����
bit F_Out;
bit F_BeOut;
bit F_OutSet;

bit F_WaterOut;         /* �ÿ��� ������ */
bit F_IceOut;           /* ���������� */
bit F_Ice_Water_Out;    /* ������ ������ */

U8 gu8LockFlick;
bit F_Mute_Enable;
bit F_Mute_Enable_Old;



bit F_Hot_Temp_Setting;
bit F_Circul_Drain;
U8 gu8_water_out_state_old;

bit F_Extraction_LED_Display_Mode;
bit F_Extraction_LED_Display_Mode_Old;

bit bit_fast_ice_make;
bit bit_ice_size;
bit F_Ice_Make_Priority_Setting_Mode;

U8 gu8_direction_continue_timer;
U8 gu8_direction_continue_max;

U8 gu8_ice_make_priority_settiong_time;

extern bit bit_setting_mode_time_init;
extern U16 gu16_setting_finish_timer;
extern U8 gu8_fnd_right_on_display_flag;
extern U8 gu8_fnd_right_off_display_flag;
extern U16 gu16_fnd_right_onoff_display_timer;
extern U8 gu8_Icewater_level;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ice_select_job(void)
{    
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    if( F_IceOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    if( F_Ice_Lock == SET )
    {
        start_ice_lock_flick();
        play_voice_ice_lock_ice_out_98();
        return;
    }
    else{}

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    /* ������ �������̸� ������ �ȴ��� 250704 CH.PARK */
    if((u8IceOutState == ICE_SELECT__ICE_WATER)
    )
    {
        if((F_WaterOut == SET) 
        || (F_IceOut == SET)
        )
        {
            play_melody_warning_197();
            return;
        }
    }
    else {  }

    if(bit_myWater_setting_start == SET)
    {
        if( F_WaterOut == SET )
        {
            play_melody_warning_197();
            return;
        }
        else {  }
    }
    else {  }

    stop_hot_off_flick();

    /* ����OFF ���¸� ���� ���������� ������ �� */
    if(F_IceOn == CLEAR)
    {
        start_ice_off_flick();
        play_voice_ice_off_ice_out_99();
    }
    else
    {
        /*.. sean [25-06-30] �����ɸ���, ��ư ������ ���� ���� ǥ�õǵ��� ���� ..*/
		if( Bit3_Leakage_Sensor_Error__E01 == SET )
		{
			play_voice_leakage_error_12();
		}
		else if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
		|| Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
		|| Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
		|| Bit16_Drain_Pump_Error__E60 == SET
		|| Bit15_Amb_Temp_Open_Short_Error__E43 == SET
		|| Bit7_BLDC_Communication_Error__E27 == SET
		|| bit_bldc_operation_error_total == SET
		||Bit2_Room_Temp_Open_Short_Error__E42 == SET)
		{
			/*..hui [24-1-10���� 3:42:03] ����������.. Ʈ���̿���, �巹����������, �ܱ⼾������, ��������..*/
			/*..hui [24-2-1���� 4:30:53] ���� �µ����� ������ �߰�..*/
			play_voice_ice_error_10();
		}
		else
		{
        	play_melody_select_196();
		}

        gu16_ice_off_flick_timer = 0;
        gu16_icewater_off_flick_timer = 0;
        gu8_indicator_flick_timer = 0;
    }

    bit_myWater_setting_start = CLEAR;
		
    if( u8IceOutState != ICE_SELECT__ICE )
    {
        u8IceOutState = ICE_SELECT__ICE;

        /* �¼������� ����, ������ ���� �� ��� �¼����� ���� 250626 CH.PARK  */
        if((u8WaterOutState == HOT_WATER_SELECT)
        && (F_WaterOut == CLEAR)
        )
        {
            u8WaterOutState = gu8_recovery_water_out_state;
        }
        else {  }

        /* ���� �뷮�� ������ ������ 1�ܰ���� �����ϵ��� ���� 250717 CH.PARK */
        gu8_ice_amount_step = ICE_LEVEL_1_STEP;
        
        if( F_WaterOut == SET )
        {
            Extract_Stack.U8_iceSelect = SET;
        }
        else
        {
            Extract_Stack.U8_waterSelect = CLEAR;
        }
    }
    else
    {
        if( F_IceBreak == CLEAR )
        {
            F_IceBreak = SET;
            play_voice_ice_type_break_select_157();
        }
        else
        {
            F_IceBreak = CLEAR;
            play_melody_select_196();
        }
    }

    gu16_ice_select_return_time = 0;
    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;
    cup_select_init();
}

/**
 * @brief ������ ���� �� ȣ��Ǵ� �Լ� (������ ���õ� ���� �ʱ�ȭ)
 * 
 */
void key_ice_water_select_job(void)
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    /* ��ü ���, ��� ��� ���� �� ����ó�� (�ٸ� Ű ���� ���) */
    if( F_Child_Lock == SET )
    {
        return;
    }
    else{}
    
    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

   /* �ÿ��� ��� ���̸� ������ ���� (�ٸ� Ű ���� ���) */
    if( F_WaterOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /* ���� �������̸� ������ ���� (�ٸ� Ű ���� ���) */
    if( F_IceOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    gu8_cup_level_time_init = SET; //LSH zzang Ȯ���ʿ�

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    /* ������� �����̸� ����� + ����ó��  */
    if( F_Ice_Lock == SET )
    {
        start_ice_lock_flick();
        play_voice_ice_lock_ice_out_98();
        return;
    }
    else{}

    stop_hot_off_flick();

    /* ����OFF ���¸� ���� ���������� ������ �� */
    if((F_IceOn == CLEAR)
    || (F_Cold_Enable == CLEAR)
    )
    {
        if(F_IceOn == CLEAR)
        {
            start_icewater_off_flick();
            play_voice_ice_off_ice_out_99();
        }
        else if(F_Cold_Enable == CLEAR)
        {
            start_cold_off_flick();
            play_voice_cold_off_cold_select_96();
        }
    }
    else
    {
        /*.. sean [25-06-30] �����ɸ���, ��ư ������ ���� ���� ǥ�õǵ��� ���� ..*/
		if( Bit3_Leakage_Sensor_Error__E01 == SET )
		{
			play_voice_leakage_error_12();
		}
		else if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
		|| Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
		|| Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
		|| Bit16_Drain_Pump_Error__E60 == SET
		|| Bit15_Amb_Temp_Open_Short_Error__E43 == SET
		|| Bit7_BLDC_Communication_Error__E27 == SET
		|| bit_bldc_operation_error_total == SET
		||Bit2_Room_Temp_Open_Short_Error__E42 == SET)
		{
			/*..hui [24-1-10���� 3:42:03] ����������.. Ʈ���̿���, �巹����������, �ܱ⼾������, ��������..*/
			/*..hui [24-2-1���� 4:30:53] ���� �µ����� ������ �߰�..*/
			play_voice_ice_error_10();
		}
		else
		{
        	play_melody_select_196();
		}
        
        gu16_ice_off_flick_timer = 0;
        gu16_icewater_off_flick_timer = 0;
        gu8_indicator_flick_timer = 0;
    }

    // /* �ü� OFF ���·� ������ ���� �� OFF ǥ���ؾߵ� 250722 CH.PARK */
    // if( F_Cold_Enable == CLEAR )
    // {
    //     start_cold_off_flick();
    //     play_voice_cold_off_cold_select_96();
    // }
    // else
    // {
    //    play_melody_select_196();    
    // }

    bit_myWater_setting_start = CLEAR;

    if( u8IceOutState != ICE_SELECT__ICE_WATER )
    {
        u8IceOutState = ICE_SELECT__ICE_WATER;

        /* �¼������� ����, ������ ���� �� ��� �¼����� ���� 250626 CH.PARK  */
        if(u8WaterOutState == HOT_WATER_SELECT)
        {
            u8WaterOutState = gu8_recovery_water_out_state;
        }
        else {  }
        
        if(gu8Cup_level >= CUP_LEVEL_CONTINUE)
        {
            gu8_ice_amount_step = ICE_LEVEL_4_STEP;
            gu8_Icewater_level = ICEWATER_CUP_LEVEL_4_500ML;
            gu8Cup_level = CUP_LEVEL_4_1000ML;
        }
        else
        {
            gu8_Icewater_level = gu8Cup_level;
            gu8_ice_amount_step = gu8Cup_level;
        }
    }
    else {  }

    gu16_ice_select_return_time = 0;
    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;
    cup_select_init();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_hot_water_select_job(void)
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    gu8_cup_level_time_init = SET;

    if( F_WaterOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    /*..hui [19-10-7���� 3:24:23] �˾� ���� ���� �ڷ�..*/
    if(F_Hot_Lock == SET)
    {
        start_hot_off_flick();
    	play_voice_hot_lcok_hot_select_93();
        return;
    }
    else {  }

    /* ������ �������̸� �ÿ��� �ȴ��� 250704 CH.PARK */
    if((u8IceOutState == ICE_SELECT__ICE_WATER)
    )
    {
        if((F_WaterOut == SET) 
        || (F_IceOut == SET)
        )
        {
            play_melody_warning_197();
            return;
        }
    }
    else {  }

    gu16_water_select_return_time = 0;

    /* �¼� �ܼ� �߻� ��, �¼� ���� �� E08 ǥ�� �� ���� �Ұ� 250730 CH.PARK */
    if(Bit0_Hot_Water_Flow_Block_Error__E08 == SET)
    {
        play_melody_warning_197();
        gu8_error_popup_enable = SET;
        return;

    }
    else
    {
        play_melody_select_196();

    }
    
    if(F_IceOut == SET)
    {
        Extract_Stack.U8_waterSelect = SET;
    }
    else
    {
        Extract_Stack.U8_iceSelect = CLEAR;
    }
    
    if((u8WaterOutState != HOT_WATER_SELECT)
    || (u8IceOutState != ICE_SELECT__NONE)
    || (bit_myWater_setting_start == SET)
    )
    {
        u8WaterOutState = HOT_WATER_SELECT;

        /*..hui [18-8-14���� 1:31:34] �¼��µ� ����Ʈ�� ������ Ŀ��..*/
        /*..hui [23-5-11���� 4:29:49] ����Ʈ �¼��µ� 85���� ����.. 85�� ��� �󵵰� �� ����?..*/
        gu8_hot_water_select_index = 0;
        gu8_hot_setting_temperature = selected_hot_temp[gu8_hot_water_select_index];

        if( Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            play_voice_leakage_error_12();
        }
        else if( Bit4_Hot_In_Temp_Open_Short_Error__E46 == SET
        || Bit5_Hot_Heater_OverHeat_Error__E40 == SET
        || Bit20_Hot_Out_Temp_Open_Short_Error__E47 == SET )
        {
            /*..sean [25-05-31] �¼����� ������ �¼����� ������..*/
            play_voice_hot_error_9();
        }
		else
		{
			play_melody_select_196();
		}

        /*..hui [23-9-25���� 3:37:28] Ű �������� ���� ����ÿ��� A1014�� ����..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else
    {
        hot_setting_change();
    }

    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;

    /* �ÿ��� ���� �� �������� ���� �̼������� ���� 250625 CH.PARK */
    u8IceOutState = ICE_SELECT__NONE;

    /* MY���� ���� �� �¼� ���� ��� �̼������� ���� 250630 CH.PARK */
    bit_myWater_setting_start = CLEAR;

    bit_ice_water_extract = CLEAR;
    gu8_ice_water_ext_start_timer_100ms = CLEAR;
    cup_select_init();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_setting_change(void)
{
    gu8_hot_water_select_index++;
    if(gu8_hot_water_select_index > 3)
    {
        gu8_hot_water_select_index = 0;
    }
    else {  }

    gu8_hot_setting_temperature = selected_hot_temp[gu8_hot_water_select_index];
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_ambient_water_select_job(void)
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    gu8_cup_level_time_init = SET;

    if(F_WaterOut == SET)
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    /* ������ �������̸� �ÿ��� �ȴ��� 250704 CH.PARK */
    if((u8IceOutState == ICE_SELECT__ICE_WATER)
    )
    {
        if((F_WaterOut == SET) 
        || (F_IceOut == SET)
        )
        {
            play_melody_warning_197();
            return;
        }
    }
    else {  }

    bit_myWater_setting_start = CLEAR;
    
    if(F_IceOut == SET)
    {
        Extract_Stack.U8_waterSelect = SET;
    }
    else
    {
        Extract_Stack.U8_iceSelect = CLEAR;
    }

	/*sean [25-05-31] error�� ���� ���� �߰�*/
    if( Bit3_Leakage_Sensor_Error__E01 == SET )
    {
        play_voice_leakage_error_12();
    }
	else
	{
		play_melody_select_196();
	}

    if( u8WaterOutState != PURE_WATER_SELECT )
    {
        u8WaterOutState = PURE_WATER_SELECT;
        /*..hui [23-9-25���� 3:37:28] Ű �������� ���� ����ÿ��� A1014�� ����..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else {  }

    gu16_water_select_return_time = 0;
    
    play_melody_select_196();

    stop_ice_off_flick();
    stop_ice_lock_flick();
    stop_icewater_off_flick();
    stop_cold_off_flick();
    stop_hot_off_flick();

    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;
    
    /* �ÿ��� ���� �� �������� ���� �̼������� ���� 250625 CH.PARK */
    u8IceOutState = ICE_SELECT__NONE;

    bit_ice_water_extract = CLEAR;
    gu8_ice_water_ext_start_timer_100ms = CLEAR;
    cup_select_init();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cold_water_select_job(void)
{
    /* ��ü�÷��� ��� ->  [�ü�] ��Ű �Է� */
    if(gu8_Led_Display_Step == LED_Display__FLUSHING)
    {
        if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
        {
            cold_long_flushing_cancel_job();

            play_voice_filter_flushing_cancle_25();

            return;
        }
        else {  }
    } else {  }

    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }
    
    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    gu8_cup_level_time_init = SET;

    if( F_WaterOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    if( F_Cold_Enable == CLEAR )
    {
        start_cold_off_flick();
        //play_melody_warning_197();
        play_voice_cold_off_cold_select_96();
    }
    else
    {
        play_melody_select_196();
    }

    /* ������ �������̸� �ÿ��� �ȴ��� 250704 CH.PARK */
    if((u8IceOutState == ICE_SELECT__ICE_WATER)
    )
    {
        if((F_WaterOut == SET) 
        || (F_IceOut == SET)
        )
        {
            play_melody_warning_197();
            return;
        }
    }
    else {  }

    bit_myWater_setting_start = CLEAR;
    if(F_IceOut == SET)
    {
        Extract_Stack.U8_waterSelect = SET;
    }
    else
    {
        Extract_Stack.U8_iceSelect = CLEAR;
    }

    if( u8WaterOutState != COLD_WATER_SELECT )
    {
        u8WaterOutState = COLD_WATER_SELECT;

        if( Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            play_voice_leakage_error_12();
        }
        else if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET
        || Bit7_BLDC_Communication_Error__E27 == SET
        || bit_bldc_operation_error_total == SET )
        {
            /*..hui [23-12-15���� 4:14:02] �ü����� ���� �߰�..*/
            /*..hui [24-1-10���� 3:38:37] �ü� ���� ������.. �ü����� ����, ���� �����϶��� ����ϱ��.. ������..*/
            play_voice_cold_error_7();
        }
        else {  }
        
        /*..hui [23-9-25���� 3:37:28] Ű �������� ���� ����ÿ��� A1014�� ����..*/
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else{}

    gu16_water_select_return_time = 0;

    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;

    /* �ÿ��� ���� �� �������� ���� �̼������� ���� 250625 CH.PARK */
    u8IceOutState = ICE_SELECT__NONE;

    bit_ice_water_extract = CLEAR;
    gu8_ice_water_ext_start_timer_100ms = CLEAR;
    cup_select_init();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_amount_select_job(void)
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    if(bit_memento_start == SET)
    {
        return;
    }

    if(bit_volume_setting_start == SET)
    {
        return;
    }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    if( bit_setting_mode_start == SET )
    {
        /* ������� ���� (��Ű�Է�) */
        bit_setting_mode_start = CLEAR;

        gu16_fnd_right_onoff_display_timer = 0;
		gu8_fnd_right_on_display_flag = CLEAR;
		gu8_fnd_right_off_display_flag = CLEAR;
        
        /* ������� ���� */
        play_voice_setting_mode_out_77();
        return;
    }
    else{}

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}

    /* ������ �������̸� �ÿ��� �ȴ��� 250704 CH.PARK */
    if((u8IceOutState == ICE_SELECT__ICE_WATER)
    )
    {
        if((F_WaterOut == SET) 
        || (F_IceOut == SET)
        )
        {
            play_melody_warning_197();
            return;
        }
    }
    else {  }

    if(bit_myWater_setting_start == SET)
    {
        play_melody_warning_197();
        return;
    }
    else {  }

    stop_ice_off_flick();
    stop_ice_lock_flick();
    stop_icewater_off_flick();
    stop_cold_off_flick();
    stop_hot_off_flick();

    gu8_cup_level_time_init = SET;
    /*..hui [19-8-22���� 2:45:46] �¼� ���� �� �����/���� ��ư ���� ��� ���� �ð� �ʱ�ȭ..ĳ�� ���..*/
    gu8_hot_select_time_init = SET;
    bit_myWater_setting_start = CLEAR;

    /* �Ұ���� �� �Ϲݻ��¿����� �뷮���� ���� 250725 CH.PARK */
    /* ������� ���¿��� �뷮 ��ư�� �Ҹ��� �ȳ��� ���� ���� 250807 CH.PARK */
    if((gu8_Led_Display_Step == LED_Display__MAIN)
    || (gu8_Led_Display_Step == LED_Display__INSTRUCTION)
    || (gu8_Led_Display_Step == LED_Display__SLEEP)
    )
    {
        if( u8IceOutState == ICE_SELECT__ICE )
        {
            if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)
            {
                gu8_ice_amount_step = ICE_LEVEL_2_STEP;
                // gu8Cup_level = CUP_LEVEL_2_250ML;
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
            {
                gu8_ice_amount_step = ICE_LEVEL_3_STEP;
                // gu8Cup_level = CUP_LEVEL_3_500ML;
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
            {
                gu8_ice_amount_step = ICE_LEVEL_4_STEP;
                // gu8Cup_level = CUP_LEVEL_4_1000ML;
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
            {
                gu8_ice_amount_step = ICE_LEVEL_1_STEP;
                // gu8Cup_level = CUP_LEVEL_1_120ML;
            }
        }
        else if(u8IceOutState == ICE_SELECT__ICE_WATER)
        {
            if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_1_150ML)
            {
                gu8_ice_amount_step = ICE_LEVEL_2_STEP;
                gu8_Icewater_level = ICEWATER_CUP_LEVEL_2_250ML;
                gu8Cup_level = CUP_LEVEL_2_250ML;
            }
            else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_2_250ML)
            {
                gu8_ice_amount_step = ICE_LEVEL_3_STEP;
                gu8_Icewater_level = ICEWATER_CUP_LEVEL_3_350ML;
                gu8Cup_level = CUP_LEVEL_3_500ML;
            }
            else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_3_350ML)
            {
                gu8_ice_amount_step = ICE_LEVEL_4_STEP;
                gu8_Icewater_level = ICEWATER_CUP_LEVEL_4_500ML;
                gu8Cup_level = CUP_LEVEL_4_1000ML;
            }
            else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_4_500ML)
            {
                gu8_ice_amount_step = ICE_LEVEL_1_STEP;
                gu8_Icewater_level = ICEWATER_CUP_LEVEL_1_150ML;
                gu8Cup_level = CUP_LEVEL_1_120ML;
            }
        }
        else
        {
            if(gu8Cup_level == CUP_LEVEL_1_120ML)
            {
                gu8Cup_level = CUP_LEVEL_2_250ML;
            }
            else if(gu8Cup_level == CUP_LEVEL_2_250ML)
            {
                gu8Cup_level = CUP_LEVEL_3_500ML;
            }
            else if(gu8Cup_level == CUP_LEVEL_3_500ML)
            {
                gu8Cup_level = CUP_LEVEL_4_1000ML;
            }
            else if(gu8Cup_level == CUP_LEVEL_4_1000ML)
            {
                gu8Cup_level = CUP_LEVEL_CONTINUE;
            }
            else
            {
                gu8Cup_level = CUP_LEVEL_1_120ML;
            }
        }
        play_melody_select_196();
    }
    else {  }


    /*..hui [20-1-7���� 9:56:14] ���� ���� LED ǥ�ÿ�..*/
    gu8_cup_led_select = SET;

    gu16_ice_select_return_time = 0;
    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;
    cup_select_init();
}

/**
 * @brief MY ��ư ������ �� ó���Լ�
 * 
 */
void    key_my_select_job(void)
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* ����Ŀ�� ���� �� ���úҰ� ������ �Ҹ��� �ȳ� (�����ư�� �Ҹ���) */
    if(bit_filter_all == CLEAR)
    {
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_sleep_mode_start == SET)
    {
        power_saving_init();
    }

    if( F_WaterOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( F_IceOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    gu8_cup_level_time_init = SET;

    if(( F_WaterOut == SET )
    || (F_IceOut == SET)
    )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    /* ���λ������ �� */
    if(cody_water_line.gu8_start == SET)
    {
        play_melody_warning_197();
        return;
    }

    if( bit_ice_tank_ster_start == SET )
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else{}
    
    if( F_WaterOut != SET )                /* ������ �������� �ƴ� �� ��� �� ���� */
    {
        //LSH zzang
        if(bit_myWater_setting_start == CLEAR)
        {
            /* MY���� ���� �ÿ��� flick ǥ�� ��� ���� 250624 CH.PARK */
            stop_ice_lock_flick();
            stop_icewater_off_flick();
            stop_cold_off_flick();
            stop_hot_off_flick();

            gu8_cup_led_select = CLEAR;
            bit_myWater_setting_start = SET;
            gu16_my_recipe_menu_on_timer = 0;
            my_recipe_select = my_receipe_default;

            play_melody_select_196();
#if 0
            if(my_recipe_select == RECIPE_RAMEN)
            {
                play_voice_ramyeon_recipe_select_147();
            }
            else if(my_recipe_select == RECIPE_DRIPCOFFEE)
            {
                play_voice_drip_coffee_recipe_select_148();
            }
            else if(my_recipe_select == RECIPE_TEA)
            {
                play_voice_tea_recipe_select_149();
            }
            else if(my_recipe_select == RECIPE_MY1)
            {
                play_voice_my1_recipe_select_150();
            }
            else if(my_recipe_select == RECIPE_MY2)
            {
                play_voice_my2_recipe_select_151();
            }
            else if(my_recipe_select == RECIPE_MY3)
            {
                play_voice_my3_recipe_select_152();
            }
#endif
            gu8_water_out_state_old = u8WaterOutState;
        }
        else
        {
            play_melody_select_196();
            if(my_recipe_select == RECIPE_RAMEN)
            {
                my_recipe_select = RECIPE_DRIPCOFFEE;
                // play_voice_drip_coffee_recipe_select_148();
            }
            else if(my_recipe_select == RECIPE_DRIPCOFFEE)
            {
                my_recipe_select = RECIPE_TEA;
                // play_voice_tea_recipe_select_149();
            }
            else if(my_recipe_select == RECIPE_TEA)
            {
                if(my_setting[MY_INDEX_MY1].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY1;
                    // play_voice_my1_recipe_select_150();
                }
                else if(my_setting[MY_INDEX_MY2].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY2;
                    // play_voice_my2_recipe_select_151();
                }
                else if(my_setting[MY_INDEX_MY3].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY3;
                    // play_voice_my3_recipe_select_152();
                }
                else
                {
                    my_recipe_select = MY_INDEX_RAMEN;
                    // play_voice_ramyeon_recipe_select_147();
                }
            }
            else if(my_recipe_select == MY_INDEX_MY1)
            {
                if(my_setting[MY_INDEX_MY2].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY2;
                    // play_voice_my2_recipe_select_151();
                }
                else if(my_setting[MY_INDEX_MY3].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY3;
                    // play_voice_my3_recipe_select_152();
                }
                else
                {
                    my_recipe_select = MY_INDEX_RAMEN;
                    // play_voice_ramyeon_recipe_select_147();
                }
            }
            else if(my_recipe_select == MY_INDEX_MY2)
            {
                if(my_setting[MY_INDEX_MY3].use == SET)
                {
                    my_recipe_select = MY_INDEX_MY3;
                    // play_voice_my3_recipe_select_152();
                }
                else
                {
                    my_recipe_select = MY_INDEX_RAMEN;
                    // play_voice_ramyeon_recipe_select_147();
                }
            }
            else if(my_recipe_select == MY_INDEX_MY3)
            {
                my_recipe_select = MY_INDEX_RAMEN;
                // play_voice_ramyeon_recipe_select_147();
            }
            else
            {
                my_recipe_select = MY_INDEX_RAMEN;
                // play_voice_ramyeon_recipe_select_147();
            }

            if(my_recipe_select != MY_INDEX_DRIPCOFFEE )
            {
                drip_timer = 0;
                gu8_dripcoffee_percent = 0;
            }

            gu16_my_recipe_menu_on_timer = 0;
        }

        if(my_setting[my_recipe_select].temp == 6)
        {
            u8WaterOutState = COLD_WATER_SELECT;
        }
        else if(my_setting[my_recipe_select].temp == 27)
        {
            u8WaterOutState = PURE_WATER_SELECT;
        }
        else
        {
            u8WaterOutState = HOT_WATER_SELECT;
            
            gu8_hot_setting_temperature = ((my_setting[my_recipe_select].temp)-45)/5;
        }

        gu16_cup_level_default_return_time = 0;
        
        gu16_water_select_return_time = 0;
        
        gu8_clock_hide_state = SET;
        gu8_clock_hide_timer = 0;
        u8Extract_Continue = CLEAR;
        
        gu16_cold_off_flick_timer = CLEAR;
        gu8_indicator_flick_timer = CLEAR;

        /* �ÿ��� ���� �� �������� ���� �̼������� ���� 250625 CH.PARK */
        u8IceOutState = ICE_SELECT__NONE;

        bit_ice_water_extract = CLEAR;
        gu8_ice_water_ext_start_timer_100ms = CLEAR;
    }
}

void key_setting_select_job()
{
    // if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    // {
    //     return;
    // }
    // else{}

    /* �Ҹ����� ������ ���� */
    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }
    
    /* �ð����� ������ ���� */
    if(bit_time_setting_start == SET)
    {
        return;
    }
    else {  }

    /* �޸������� �� ���� */
    if( bit_memento_start == SET )
    {
        return;
    }
    else {  }

    if( F_WaterOut == SET || F_IceOut == SET )
    {
        return;
    }
    else{}

    if(cody_water_line.gu8_start == SET)
	{
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    if(bit_manual_drain_start == SET)
    {
        return;
    }

	if(bit_setting_mode_start == SET)
	{

	}
	else
	{
		bit_setting_mode_start = SET;

		if( F_WaterOut == SET || F_Out == SET )
		{
			play_melody_warning_197();
		}
		else
		{
            /* ������� ���� */
            play_voice_setting_mode_in_43();
        }
	}
}

void key_setting_ice_size(void)
{
    if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

	bit_setting_mode_time_init = SET;

	if(bit_ice_size == ICE_SIZE_LARGE)
	{
		bit_ice_size = ICE_SIZE_SMALL;
		play_voice_ice_size_small_143();
	}
	else
	{
		bit_ice_size = ICE_SIZE_LARGE;
		play_voice_ice_size_large_144();
	}
}
void key_setting_cold_off(U8 mu8_setting)
{
	bit_setting_mode_time_init = SET;

    if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}
    	
    if(mu8_setting == SET)
	{
        gu16_fnd_right_onoff_display_timer = 0;
		gu8_fnd_right_on_display_flag = SET;
		gu8_fnd_right_off_display_flag = CLEAR;

		water_select_return_timer_control(1);

		/*..hui [20-1-6���� 8:06:19] �ü� ��ư���� �ü� ���� �ü� ������ OFF�� ����..*/
		/*..hui [20-2-24���� 7:44:02] �ü� ONOFF�� �ü��µ� ���� �޴� �и�..*/
		/*gu8_cold_setting_level = COLD_TEMP_OFF;*/

		play_voice_setting_cold_on_124();
	}
	else
	{
        gu16_fnd_right_onoff_display_timer = 0;
		gu8_fnd_right_on_display_flag = CLEAR;
		gu8_fnd_right_off_display_flag = SET;

        Bit2_Cold_Off_Indicator = CLEAR;
        gu16_cold_off_flick_timer = 0;          /* flick Ÿ�̸� ���� �ʱ�ȭ�ؾ��� ǥ�� ����� ����� 250318 CH.PARK */
		water_select_return_timer_control(0);

		play_voice_setting_cold_off_125();
	}
    
    F_Cold_Enable = mu8_setting;
}
void key_setting_ice_lock(void)
{
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}
	
	F_Ice_Lock = ~F_Ice_Lock;
	
	if( F_Ice_Lock == SET )
	{
		play_voice_setting_ice_lock_on_147();
	}
	else
	{
		play_voice_setting_ice_lock_off_148();
	}
	
	send_wifi_each_data_control( WIFI_FUNC_0032_ICELOCK_SEL );
}

void key_setting_hot_lock(void)
{
    if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

	bit_setting_mode_time_init = SET;

	// if( bit_setting_mode_start == CLEAR )
	// {
	// 	return;
	// }
	// else{}

	F_Hot_Lock = ~F_Hot_Lock;

	if( F_Hot_Lock == SET )
	{
		play_voice_setting_hot_lock_on_112();

		/*..hui [24-1-19���� 2:23:12] �¼� ���� ���� -> �¼���� �� �¼� ���û��� �����ǵ���..*/
		if( u8WaterOutState == HOT_WATER_SELECT )
		{
			water_select_return_timer_control(1);
		}
		else{}
	}
	else
	{
        play_voice_setting_hot_lock_off_113();
	}
}
void key_setting_fast_icemake(void)
{
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

	if( bit_fast_ice_make == COLD_FIRST_ICE_MAKE )
    {
        bit_fast_ice_make = ICE_FIRST_ICE_MAKE;
        play_melody_setting_on_198();
    }
    else
    {
        bit_fast_ice_make = COLD_FIRST_ICE_MAKE;
        play_melody_setting_off_199();
    }

  send_wifi_each_data_control( WIFI_FUNC_0008_ICE_SEL );
}

void key_setting_cold_power(void)
{
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

	if(gu8_cold_setting_level == COLD_POWER_HIGH)
	{
		gu8_cold_setting_level = COLD_POWER_LOW;
        play_voice_cold_temp_weak_139();
	}
	else
	{
		gu8_cold_setting_level = COLD_POWER_HIGH;
        play_voice_cold_temp_strong_140();
	}

}
void key_setting_ice_off(void)
{
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

	if(F_IceOn == SET)
	{
		F_IceOn = CLEAR;
        
        /* �������� ���� [����] �������� Default ���� 250625 CH.PARK */
        u8IceOutState = ICE_SELECT__NONE;

        gu16_fnd_right_onoff_display_timer = 0;
		gu8_fnd_right_on_display_flag = CLEAR;
		gu8_fnd_right_off_display_flag = SET;

        F_IceDoorClose = SET;
        F_IceSelectDoorClose = SET;
		play_voice_setting_ice_off_150();
	}
	else
	{
		F_IceOn = SET;

        Bit0_Ice_Lock_Indicator = CLEAR;
        gu16_ice_off_flick_timer = 0;
        gu16_icewater_off_flick_timer = 0;
        gu8_indicator_flick_timer = 0;
        
        gu16_fnd_right_onoff_display_timer = 0;
		gu8_fnd_right_on_display_flag = SET;
		gu8_fnd_right_off_display_flag = CLEAR;

		play_voice_setting_ice_on_149();
	}
}
void key_setting_sleepmode(void)
{
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}
    
    if(bit_first_time_setting == CLEAR)
	{
		play_voice_eco_mode_not_available_51();
		return;
	}

    if(bit_sleep_mode_enable == CLEAR)
    {
        bit_sleep_mode_enable = SET;
        play_voice_sleep_mode_enable_145();
    }
    else
    {
        bit_sleep_mode_enable = CLEAR;
        play_voice_sleep_mode_disable_146();
    }
}

void key_setting_all_lock_on(void)
{  
	bit_setting_mode_time_init = SET;

	if( bit_setting_mode_start == CLEAR )
	{
		return;
	}
	else{}

    if(F_All_Lock == CLEAR)
	{
		F_All_Lock = SET;
		play_voice_all_lock_start_127();
        
        /* ��� ������� ���� */
        bit_setting_mode_start = CLEAR;
		send_wifi_each_data_control( WIFI_FUNC_0005_LOCK_SEL );
	}
	else
	{
        
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Memento Here! 
***********************************************************************************************************************/
void memento_mode_cancel(void)
{
    if( bit_memento_start == CLEAR )
    {
        return;
    }
    else{}

    play_melody_setting_off_199();      // �޸����� �����ϱ� ������
    bit_memento_start = CLEAR;
    memento_display_step_conv(MEMENTO_DISPLAY_START);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Memento Here! 
***********************************************************************************************************************/
void memento_mode_error_clear(void)
{
    if( bit_memento_start == CLEAR )
    {
        return;
    }
    else{}

    play_melody_setting_on_198();       // �����缭�� �����ϰ�

    // 1�� ���� �ʱ�ȭ �ȵż� ���� 250717 CH.PARK
    u8Memento_Buff[0] = CLEAR;
    u8Memento_Buff[1] = CLEAR;
    u8Memento_Buff[2] = CLEAR;
    u8Memento_Buff[3] = CLEAR;
    u8Memento_Buff[4] = CLEAR;
    u8Memento_Buff[5] = CLEAR;
    F_ErrorSave = SET;      /* ���� */
}



