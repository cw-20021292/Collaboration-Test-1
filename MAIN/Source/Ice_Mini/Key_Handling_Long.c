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
#include    "Key_Handling_Long.h"
#include "WIFI_SetFunctionData.h"
#include "WIFI_A101x_FunctionList.h"

void calcel_comp_delay(void);
void ice_on_off_setting_job( U8 mu8_mode );
void cold_water_enable_setting_job( U8 mu8_mode );

void setting_mode_start(void);
void key_time_setting_job(void);
void key_time_setting_ice_water_long_select_job(void);
void key_time_setting_ice_long_select_job(void);
void key_setting_all_lock_off(void);
void key_manual_ice_tank_ster(void);

/* Cody Water Line Clean Service */
void key_cody_water_line_clean_job(void);
void stop_flushing_test_mode_start(void);

bit bit_setting_mode_start;

U16 gu16_Time_Setting_Mode_Timer_100ms;

bit bit_altitude_setting_start;
bit bit_memento_start;
U8 gu8_memento_display_num;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calcel_comp_delay(void)
{
    /*..hui [19-10-25���� 9:21:25] ���⼭ �ѹ� �� ���͸�..*/
    if(F_Comp_Output == CLEAR && gu16CompOffDelay > 0)
    {
        /*..hui [19-10-25���� 9:22:56] �ø���ȯ��� �ʱ�ȭ�ð� ���..*/
        gu16CompOffDelay = DEVELOPE_COMP_DELAY_CANCEL_TIME;
        F_IceInit = CLEAR;
        play_melody_setting_on_198();
    }
    else
    {
        play_melody_warning_197();
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_on_off_setting_job( U8 mu8_mode )
{
    if( F_All_Lock == SET )
    {
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    /*..hui [17-12-28���� 1:03:15] ���� �����߿��� ������ϵ��� ����..*/
    if( F_IceOut == SET )
    {
        return;
    }
    else{}

    /* �ð� ������� �߿��� ó�� �ȵǵ��� ���� 250529 CH.PARK */
    if(bit_time_setting_start == SET)
    {
        return;
    }
    else {  }

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if(bit_manual_drain_start == SET)
    {
        return;
    }


    if( mu8_mode == SETTING_ENABLE )
    {
        if( F_IceOn == CLEAR )
        {
            F_IceOn = SET;
            
            F_IR = SET;               // ��������
            F_Low_IR = SET;           // ��������

            play_voice_setting_ice_on_149();
            start_button_set_display( BUTTON_SET_ICE_OFF_DISPLAY );
            bit_ice_setting_double_disable = SET;
        }
        else
        {
            bit_ice_setting_double_disable = CLEAR;
        }
    }
    else
    {
        if( F_IceOn == SET && bit_ice_setting_double_disable == CLEAR )
        {
            F_IceOn = CLEAR;
            F_IceDoorClose = SET;
            F_IceSelectDoorClose = SET;
            
            play_voice_setting_ice_off_150();
            start_button_set_display( BUTTON_SET_ICE_OFF_DISPLAY );
        }
        else
        {
            bit_ice_setting_double_disable = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_water_enable_setting_job( U8 mu8_mode )
{
    if( F_All_Lock == SET )
    {
        return;
    }
    else{}

    if( F_WaterOut == SET )
    {
        return;
    }
    else{}

    if( F_IceOut == SET )
    {
        return;
    }
    else{}

    /* �ð� ������� �߿��� ó�� �ȵǵ��� ���� 250529 CH.PARK */
    if(bit_time_setting_start == SET)
    {
        return;
    }
    else {  }

    if(bit_manual_drain_start == SET)
    {
        return;
    }


    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( mu8_mode == SETTING_ENABLE )
    {
        if( F_Cold_Enable == CLEAR )
        {
            F_Cold_Enable = SET;
            water_select_return_timer_control(0);

            /*..hui [25-2-27���� 5:44:09] �ӽ�..*/
            play_voice_setting_cold_on_124();

            /*..hui [24-4-24���� 5:48:35] �ü� ON, OFF �� ǥ��..*/
            start_button_set_display( BUTTON_SET_COLD_DISPLAY );

            /*..hui [18-1-31���� 9:43:54] �ü� �̼��� ���¿��� �������� ����� 5�� very longŰ ����....*/
            /*..hui [18-1-31���� 9:44:00] Ű ������������ �����ؼ� �����ƴ� �����Ǵ� ����..*/
            bit_cold_setting_double_disable = SET;
        }
        else
        {
            bit_cold_setting_double_disable = CLEAR;
        }
    }
    else
    {
        if(F_Cold_Enable == SET && bit_cold_setting_double_disable == CLEAR)
        {
            F_Cold_Enable = CLEAR;
            water_select_return_timer_control(1);

            /*..hui [20-1-6���� 8:06:19] �ü� ��ư���� �ü� ���� �ü� ������ OFF�� ����..*/
            /*..hui [20-2-24���� 7:44:02] �ü� ONOFF�� �ü��µ� ���� �޴� �и�..*/
            /*gu8_cold_setting_level = COLD_TEMP_OFF;*/

            /*..hui [25-2-27���� 5:44:05] �ӽ�..*/
            play_voice_setting_cold_off_125();

            /*..hui [24-4-24���� 5:48:35] �ü� ON, OFF �� ǥ��..*/
            start_button_set_display( BUTTON_SET_COLD_DISPLAY );
        }
        else
        {
            bit_cold_setting_double_disable = CLEAR;
        }
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_mode_start(void)
{
    /*..hui [17-12-28���� 1:03:15] �����߿��� ������ϵ��� ����..*/
    if( F_WaterOut == SET || F_IceOut == SET )
    {
        return;
    }
    else{}

    /*if(F_All_Lock == SET)*/
    if( F_All_Lock == SET )
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_volume_setting_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if(bit_manual_drain_start == SET)
    {
        return;
    }

    if( bit_setting_mode_start == CLEAR )
    {
        bit_setting_mode_start = SET;
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_job(void)
{
    /*..hui [23-6-14���� 10:37:57] �������� ����Ǹ� �ð����� ����..*/
    if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( F_All_Lock == SET )
    {
        //start_all_lock_flick();
        return;
    }
    else{}

    if( F_WaterOut == SET || F_IceOut == SET )
    {
        return;
    }
    else{}

    if(bit_setting_mode_start == SET)
    {
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    if( bit_volume_setting_start == SET )
    {
        return;
    }
    else{}

    //if( bit_ice_tank_ster_start == SET )
    //{
        /*play_melody_warning_197();*/
    //    return;
    ///}
    //else{}

    /*..hui [23-9-14���� 3:38:14] ����ð�, �����ð� �����ÿ��� ���Ը��ϰ�..*/
    //if( bit_time_setting_start == SET )
    //{
    //    /*play_melody_warning_197();*/
    //    return;
    //}
    //else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_time_setting_start == CLEAR )
    {
        play_voice_time_setting_start_144();
        start_time_setting_mode( CURRENT_TIME_SETTING_MODE );
    }
    else
    {
        gu8_time_setting_step = SETTING_TIME_FINISH;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_ice_water_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit0_Ice_Water_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_time_setting_ice_long_select_job(void)
{
    if( bit_time_setting_start == CLEAR )
    {
        return;
    }
    else{}

    if( gu8_Led_Display_Step == LED_Display__TIME_SETTING )
    {
        Bit1_Ice_Continue = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_setting_all_lock_off(void)
{
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    if( F_All_Lock == CLEAR )
    {
        return;
    }
    else{}

    if(bit_time_setting_start == SET)
    {
        return;
    }

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    F_All_Lock = CLEAR;
    play_voice_all_lock_finish_128();
    Bit4_All_Lock_Indicator = CLEAR;

    send_wifi_each_data_control( WIFI_FUNC_0005_LOCK_SEL );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_manual_ice_tank_ster(void) 
{
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        return;
    }
    else {  }

    if( bit_setting_mode_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /*..hui [23-5-22���� 7:17:44] �켱 ������, ���������߿��� ���°ɷ�..*/
    if( F_WaterOut == SET || F_IceOut == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_time_setting_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if(bit_time_setting_start == SET)
    {
        return;
    }

    if( bit_ice_tank_ster_start != SET )
    {
        if( Bit3_Ice_Tank_Ster_Operation_Disable_State == SET )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        if( F_First_Hot_Effluent == SET )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        if( F_Tank_Cover_Input == CLEAR )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        /*..hui [23-7-28���� 3:42:30] �߰��� ���̵�Ŀ��, RO ���� ���� �����Ǹ� ����..*/
        if( bit_filter_all == CLEAR )
        {
            play_melody_warning_197();
            return;
        }
        else{}

        /* ���λ�� �����߿��� ���� ��»�� �Ұ��� */
        if(cody_water_line.gu8_start == SET)
        {
            play_melody_warning_197();
            return;
        }
        else {  }

        /* �����巹�� �����߿��� ���� ��»�� �Ұ��� */
        if(bit_manual_drain_start == SET)
        {
            play_melody_warning_197();
            return;
        }
        else {  }

        // /* ��»�� �ü� Ű �Է� 3ȸ �̸� �� ���۾ȵ� (��Ҵ� ����) */
        // if(gu8_passive_hot_ster_key_input_count < 3)
        // {
        //     play_melody_warning_197();
        //     return;
        // }
        // else {  }

        /*..hui [23-10-27���� 11:56:29] ����Ż�����̾����� ����Ż�� ���..*/
        if( F_IceInit == SET )
        {
            F_IceInit = CLEAR;
            gu8InitStep = 0;
            gu16IceMakeTime = 0;
            gu16IceHeaterTime = 0;
        }
        else {  }

        play_melody_setting_on_198();

        start_ice_tank_ster();      // ���� ��»��
    }
    else
    {
        // bit_ice_tank_ster_start = CLEAR;
        // play_melody_setting_off_199();

        // stop_ice_tank_ster();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Memento Here!
***********************************************************************************************************************/
void    key_memento_mode_job(void)
{
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        return;
    }
    else {  }

    bit_memento_start = SET;

    play_melody_select_196();
    memento_display_step_conv(MEMENTO_DISPLAY_START);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : Cody Water Line Clean Service
***********************************************************************************************************************/
void key_cody_water_line_clean_job(void)
{  
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        return;
    }
    else{}

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        return;
    }
    else {  }

    if(bit_time_setting_start == SET)
    {
        return;
    }

    if(cody_water_line.gu8_start == CLEAR)
    {
        /* �ڵ��ո�� E01,E09 �߻� ���¿����� ���Ծȵǰ� ����� �߻� 250716 CH.PARK */
        if((Bit3_Leakage_Sensor_Error__E01 == SET)
        || (Bit6_Main_Water_Flow_Block_Error__E09 == SET)
        )
        {
            play_melody_warning_197();
        }
        else
        {
            cody_water_line.gu8_start = SET;
            play_melody_setting_on_198();
        }
        
    }
    else
    {
        cody_water_clean_mode_clear();
    }
    
    cody_water_line.gu8_step = 0;
    cody_water_line.gu16_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : 
***********************************************************************************************************************/
void cold_func_onoff_long_key_job(void)
{
    if(gu8_flushing_mode > FLUSHING_NONE_STATE)
    {
        return;
    }

    if(special_mode_check_U8() == CLEAR)
    {
        if(F_Cold_Enable == CLEAR)
        {
            F_Cold_Enable = SET;
            gu16_cold_off_flick_timer = 0;          /* flick Ÿ�̸� ���� �ʱ�ȭ�ؾ��� ǥ�� ����� ����� 250318 CH.PARK */
            Bit2_Cold_Off_Indicator = CLEAR;
            play_voice_setting_cold_on_124();
        }
        else
        {
            F_Cold_Enable = CLEAR;
            play_voice_setting_cold_off_125();
        }
    }
    else
    {

    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_long_flushing_cancel_job(void)
{
    /* �÷��� ��� */
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
    {
            if((u8FilterResetState == NEO_INO_FILTER_CHANGE)
            && (bit_yes_no_popup == SET)
            )
            {
                cancel_filter_flushing();
            }
            else {  }
        }
        else {  }
    }
    else {  }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_flushing_test_mode_start(void)
{
    /* 2KG�� ����Ű 3ȸ �̻����� ���� */
    if( gu8_flushing_finish_input_count >= 3 )
    {
        play_voice_test_mode_151();
        gu8_flushing_mode = FLUSHING_NONE_STATE;
    }
    else
    {
        play_melody_warning_197();
    }
}


