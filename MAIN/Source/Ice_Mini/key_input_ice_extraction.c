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
#include    "key_input_ice_extraction.h"
/*************************************************************************************************************************/
void key_input_ice_extract(void);
void input_ice_extract_key(void);
void ice_ext_button_operation(void);
void ice_extraction_start(void);
void ice_extraction_finish(void);
void ice_extract_key(void);
void ice_extract_key_management(void);
void Uart_Test_Mode_Ice_Extract_Key_Short_Input(void);
void Display_Test_Mode_Ice_Extract_Key_Short_Input(void);
/*************************************************************************************************************************/
/* ����, ������ ���� ���õ� Ű ���� */
U8  gu8_Key_Ice_Or_Water_Extract;
U8  u8_Ice_Or_Water_Extract_Key_Buffer;
U8  u8_Ice_Or_Water_Extract_Key_Input_Value;
bit F_Ice_Or_Water__Key_Short_Push_State;

U8 gu8_Icewater_level;

bit F_Ice_Or_Water__Key_Long_Push_State;
bit F_Ice_Or_Water__Key_Very_Long_Push_State;
U16  u16_Ice_Or_Water__Key_Sampling_Counter;
U16  u16_Ice_Or_Water__Key_Long_Counter;
U16  u16_Ice_Or_Water__Key_Short_Counter;
/*************************************************************************************************************************/
U16 gu16_ice_ext_on_decision_timer;
U16 gu16_ice_ext_off_decision_timer;
/*************************************************************************************************************************/
U8 gu8_Key_Ice_Extract;
bit F_Key_IceExtraction;
/*************************************************************************************************************************/
U8 gu8_ice_out_continue;
extern U16 gu16_extract_display_hz;
/*************************************************************************************************************************/
bit bit_ice_water_extract;
U8  gu8_ice_water_ext_start_timer_100ms;
/*************************************************************************************************************************/
extern bit F_Effluent_OK;
extern U16 gu16_extract_display_hz;
extern U8 gu8_cup_led_select;
extern U8 gu8_cup_led_off_time;
extern U8 gu8_dripcoffee_percent;
extern U16 drip_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 1
void key_input_ice_extract(void)
{
    input_ice_extract_key();
    ice_extract_key_management();
    
    // if(u8FactoryTestMode == NONE_TEST_MODE)
    // {
    //     ice_ext_button_operation();
    // }
    // else
    // {
    //     ////////PCB_Test_Mode_Ice_Key_Short_Input();
    // }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 1
void input_ice_extract_key(void)
{
    if(gu8_Key_Ice_Extract == u8_Ice_Or_Water_Extract_Key_Buffer)
    {
        if(u8_Ice_Or_Water_Extract_Key_Buffer == UKey_Mask)
        {
            u16_Ice_Or_Water__Key_Sampling_Counter = 0;
            F_Ice_Or_Water__Key_Short_Push_State = CLEAR;
            F_Ice_Or_Water__Key_Long_Push_State = CLEAR;
            F_Ice_Or_Water__Key_Very_Long_Push_State = CLEAR;
        }
        else
        {
            u16_Ice_Or_Water__Key_Sampling_Counter++;
        }

        if(u16_Ice_Or_Water__Key_Sampling_Counter >= 1)
        {
            u16_Ice_Or_Water__Key_Short_Counter = u16_Ice_Or_Water__Key_Sampling_Counter;
            u16_Ice_Or_Water__Key_Long_Counter++;

            /*..hui [19-11-19���� 4:26:26] Ű �����ִµ��� �¼� ���� ī���� �ʱ�ȭ..*/
            /*gu16_water_select_return_time = 0;*/
        }
        else{}
    }
    else
    {
        u8_Ice_Or_Water_Extract_Key_Buffer = gu8_Key_Ice_Extract;

        u16_Ice_Or_Water__Key_Sampling_Counter = 0;
        u16_Ice_Or_Water__Key_Long_Counter = 0;
        u16_Ice_Or_Water__Key_Short_Counter = 0;
    }
}
#endif

void ice_extract_key_management(void)
{
    if(F_Ice_Or_Water__Key_Short_Push_State == CLEAR)
    {
        if((u16_Ice_Or_Water__Key_Short_Counter >= 1) 
        && (u16_Ice_Or_Water__Key_Short_Counter < 2000)
        )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                ice_extraction_start();
            }
            else if (u8FactoryTestMode == DISPLAY_TEST_MODE)         /* ����Ʈ TEST MODE */
            {
                Display_Test_Mode_Ice_Extract_Key_Short_Input();
            }
            else if (u8FactoryTestMode == UART_TEST_MODE)               /* �����˻��� */
            {
                Uart_Test_Mode_Ice_Extract_Key_Short_Input();
            }
            else if(u8FactoryTestMode == PCB_TEST_MODE)                 /* PCB �׽�Ʈ��� */
			{
				PCB_Test_Mode_Ice_Extract_Key_Short_Input();
			}
            
            F_Ice_Or_Water__Key_Short_Push_State = SET;
            u16_Ice_Or_Water__Key_Short_Counter = 0;
        }
        else
        {
            /* ���������� ���ǿ� ������� ���� ��� �ߴ� 250716 CH.PARK */
            if( F_IceOut == SET && gu8_ice_out_continue == SET )
            {
                ice_extraction_finish();
            }
            else{}
        }
    }
    else
    {
        if(F_Ice_Or_Water__Key_Long_Push_State == CLEAR)
        {
            if( u16_Ice_Or_Water__Key_Short_Counter >= 2000 )
            {
                F_Ice_Or_Water__Key_Long_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    ice_extract_long_key();
                }
                else{}
            }
            else{}
        }
        else{}
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void ice_ext_button_operation(void)
{
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    #if 0
    /*..hui [23-2-9���� 2:03:49] ���ø�忡���� ���������� ����ȵ�..*/
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    /*..hui [23-8-2���� 1:20:19] ���� ������ ���� ���� ������ �������⵵ ����..*/
    /*..hui [23-8-2���� 1:20:39] ���� ������ �ʿ�� ������.. ���� �������� ���� ���� �������Ƿ� �����ϰ� �ϱ� ���ؼ�....*/
    if( bit_filter_all == CLEAR )
    {
        if( F_IceOut == SET )
        {
            F_Key_IceExtraction = CLEAR;
        }
        else{}
    }
    else{}
    #endif

    if( F_Key_IceExtraction == SET )
    {
        if( F_ExtractKeySet == CLEAR )
        {
            if( F_All_Lock == SET )
            {
                //////////start_all_lock_flick();
                play_voice_all_lock_select_103();
            }
            else
            {
                ice_extraction_start();
            }

            F_ExtractKeySet = SET;
        }
        else
        {
            /*..hui [25-1-9���� 7:19:50] �������� �߰��� ����?..*/
            ice_extraction_finish();
        }
    }
    else
    {
        ice_extraction_finish();
        F_ExtractKeySet = CLEAR;
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_start(void)
{
    /*..hui [23-5-12���� 3:27:25] ��ư ���� ON, OFF ǥ���� ��ư ������ ǥ�� �ٷ� ����..*/
    ///////stop_button_set_display();
    /*..hui [24-4-25���� 7:12:26] LED �������̴��� ����..*/
    ////////off_all_flick();
    #if 1
    gu8_clear_block_error = SET;

    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else {  }

    /* �÷���+�ڵ� ������ �ƴ� ������ �׳� �ƹ��Ҹ����� �Է� �ȵǰ� ���� */
    if( gu8_flushing_mode > FLUSHING_NONE_STATE && bit_instruction_mode_start == CLEAR )
    {
        return;
    }
    else {  }

    /* ����Ŀ�� ���� �� ����Ұ� */
    if(bit_filter_cover == CLEAR)
    {
        play_voice_filter_cover_opened_44();
        return;
    }
    
    if(bit_filter_all == CLEAR)
    {
        play_voice_filter_not_detected_14();
        return;
    }

    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
        return;
    }

    /* ��Ÿ�� ���� �Ҹ����� �ȵ�! */
    if( gu8_fota_start == SET )
    {
        return;
    }
    else{}
    
    if( bit_setting_mode_start == SET )
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}

    /* ��»�� �߿��� ������� */
    if(bit_ice_tank_ster_start == SET)
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else {  }

    if(bit_time_setting_start == SET)
    {
        return;
    }
    #endif

    if(( F_WaterOut == CLEAR )
    && (F_IceOut == CLEAR)
    )
    {
        bit_welcome_start = SET;
    }
    else {  }

    bit_30_min_no_use_start = CLEAR;
    gu32_no_use_30_min_timer = CLEAR;

    /* ���λ�� �� ���� ��ư �Է� �� ��� �ߴ�
    Cody Water Line Clean Service */
    if(cody_water_line.gu8_start == SET)
    {
        cody_water_clean_mode_clear();
        return;
    }
    else {  }

    /* ����, ������ �������� �ʾҴµ� ���� ��ư ������ ���� */
    if((u8IceOutState == ICE_SELECT__NONE)
    && (F_IceOut == CLEAR)
    )
    {
        key_ice_select_job();
        return;
    }

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

    if(bit_volume_setting_start == SET)
    {
        return;
    }
    else {  }

    /* ��»�� �߿��� ������� */
    if(bit_ice_tank_ster_start == SET)
    {
        play_voice_ice_tray_hot_ster_is_going_86();
        return;
    }
    else {  }

    
    if(F_Ice_Lock == SET)
    {
        play_voice_ice_lock_ice_out_98();
        return;
    }

    if( bit_manual_drain_start == SET )
    {
        return;
    }

    /*..hui [25-6-2���� 1:16:55] ���� ��ǰ ���� ���� �����ư ����..*/
    /* �÷���+�ڵ� �������� ������ �׳� ��������鼭 �Է� �ȵǰ� ���� */
    if( gu8_flushing_mode > FLUSHING_NONE_STATE && bit_instruction_mode_start == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    /* ��ȯ��� ��� */
    auto_drain_key_off_check();

    /* �� �� ����ڰ� � ��ư�� ������ �ٷ� ��ǥ�ô� Ǯ����. 250714 CH.PARK */
    if(( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    // && (gu8_Wifi_Pairing_State == )
    )
    {
        //bit_wifi_pairing_start = CLEAR;
        finish_pairing_screen();
    }
    else {  }

    /*..sean [25-02-03] E08 ���� �ȵǾ��־ �߰�..*/
    if( Bit3_Leakage_Sensor_Error__E01 == SET )
        //|| Bit1_Main_Water_Flow_Leaked_Error__E02 == SET
        //|| Bit6_Main_Water_Flow_Block_Error__E09 == SET
        //|| Bit0_Hot_Water_Flow_Block_Error__E08 == SET )
    {
        /*..hui [21-7-23���� 7:12:37] ���� ���� �߻������� �����ϰ� ������ �층�층..*/
        play_melody_warning_197();
        return;
    }
    else{}


    /* ���������� ������ ����Ϸ� �ư�, ���� �������� �� */        
    if( u8IceOutState == ICE_SELECT__ICE_WATER )
    {
        if( (F_IceOut == SET)
        || (F_WaterOut == SET)
        )
        {           
            play_melody_extract_complete_194();
            
            F_WaterOut = CLEAR;
            ice_extraction_finish();

            gu16_extract_display_hz = 0;
        }
        else
        {
            /* ������ ���� ���� */
            F_IceOut = SET;
            play_voice_ice_water_extract_92();

            /* ����, ������ ���� �� flick ǥ�� ��� ���� 250624 CH.PARK */
            stop_ice_lock_flick();
            stop_icewater_off_flick();
            stop_cold_off_flick();
            stop_hot_off_flick();

            /* ����Ÿ�� : [�Ϲ�] ���� �� ���� */
            if(F_IceBreak == CLEAR)
            {
                F_IceSelect = SET;          /* ��������Ʈ ���� ���� */
                F_IceOpen = SET;            /* ���� 1�� ���� ���� */

                F_IceOutCCW = SET;          /* ���� ������� ȸ�� (��) */
                gu8IceOutCCWInterval = 20;  /* ������� 2�� ��� Ÿ�̸� */

                /*..hui [20-4-16���� 10:39:30] ��ȸ�� �������̾����� ���..*/
                bit_ice_out_back_state = CLEAR;
                bit_ice_out_back_1s_state = CLEAR;

                /* ���̽� ���� ���� ���� ��ɰ� ��ġ�� ��� FULL OPEN */
                if( gu16IceDoorCloseResetTimer  != 0 )
                {
                    gu16_Ice_Door_StepMotor = 0;
                }
                else {  }

                if(gu16IceSelectDoorCloseResetTimer != 0)
                {
                    gu16_IceSelect_StepMotor  = 0;                    
                }
                else {  }
            }
            else
            {
                /* ����Ÿ�� : [����] ���� �� ���� */
                F_IceOutCCW = SET;          /* ���� ������� ȸ�� (��) */
                gu8IceOutCCWInterval = 20;  /* ������� 2�� ��� Ÿ�̸� */
                
                F_IceSelect = CLEAR;          /* ���� 1�� ���� ���� */
                F_IceOpen = SET;              /* ���� ��������  ���� */

                /*..hui [20-4-16���� 10:39:30] ��ȸ�� �������̾����� ���..*/
                bit_ice_out_back_state = CLEAR;
                bit_ice_out_back_1s_state = CLEAR;
            }

            /* ���� ���� �� ������ �����ȳ� */
            /*.. sean [25-5-31] �̻��� �ִ� ��� �ļ����� �ִ� ������ ��µǱ� ������ �ش� �������� �߰�..*/
            if( Bit3_Leakage_Sensor_Error__E01 == SET )
            {
                // play_voice_leakage_error_12();
                play_melody_warning_197();
                gu8_error_popup_enable = SET;
            }
    #if 0
            else if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
            || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
            || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
            || Bit16_Drain_Pump_Error__E60 == SET
            || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
            || Bit7_BLDC_Communication_Error__E27 == SET
            || bit_bldc_operation_error_total == SET )
            {
                /*..hui [24-1-10���� 3:42:03] ����������.. Ʈ���̿���, �巹����������, �ܱ⼾������, ��������..*/
                /*..hui [24-2-1���� 4:30:53] ���� �µ����� ������ �߰�..*/
                play_voice_ice_error_10();
            }
    #endif
            else if( bit_sleep_mode_start == SET )
            {
                play_voice_sleep_mode_ice_extract_52();
            }
            else {  }
        }
    }
    else
    {
        /* ������ �� */
        if( u8IceOutState == ICE_SELECT__ICE )
        {
            if( F_IceOut != SET )
            {
                F_IceOut = SET;

                play_melody_setting_on_198();

                /* ����, ������ ���� �� flick ǥ�� ��� ���� 250624 CH.PARK */
                stop_ice_lock_flick();
                stop_icewater_off_flick();

                /* ����Ÿ�� : [�Ϲ�] ���� �� ���� */
                if(F_IceBreak == CLEAR)
                {
                    F_IceSelect = SET;          /* ��������Ʈ ���� ���� */
                    F_IceOpen = SET;            /* ���� 1�� ���� ���� */

                    F_IceOutCCW = SET;          /* ���� ������� ȸ�� (��) */
                    gu8IceOutCCWInterval = 20;  /* ������� 2�� ��� Ÿ�̸� */

                    /*..hui [20-4-16���� 10:39:30] ��ȸ�� �������̾����� ���..*/
                    bit_ice_out_back_state = CLEAR;
                    bit_ice_out_back_1s_state = CLEAR;

                    /* ���̽� ���� ���� ���� ��ɰ� ��ġ�� ��� FULL OPEN */
                    if( gu16IceDoorCloseResetTimer  != 0 )
                    {
                        gu16_Ice_Door_StepMotor = 0;
                    }
                    else {  }

                    if(gu16IceSelectDoorCloseResetTimer != 0)
                    {
                        gu16_IceSelect_StepMotor  = 0;                    
                    }
                    else {  }
                }
                else
                {
                    /* ����Ÿ�� : [����] ���� �� ���� */
                    F_IceOutCCW = SET;          /* ���� ������� ȸ�� (��) */
                    gu8IceOutCCWInterval = 20;  /* ������� 2�� ��� Ÿ�̸� */
                    
                    F_IceSelect = CLEAR;          /* ���� 1�� ���� ���� */
                    F_IceOpen = SET;              /* ���� ��������  ���� */

                    /*..hui [20-4-16���� 10:39:30] ��ȸ�� �������̾����� ���..*/
                    bit_ice_out_back_state = CLEAR;
                    bit_ice_out_back_1s_state = CLEAR;
                }
                
                /* ���� ���� �� ������ �����ȳ� */
                /*.. sean [25-5-31] �̻��� �ִ� ��� �ļ����� �ִ� ������ ��µǱ� ������ �ش� �������� �߰�..*/
                if( Bit3_Leakage_Sensor_Error__E01 == SET )
                {
                    // play_voice_leakage_error_12();
                    play_melody_warning_197();
                    gu8_error_popup_enable = SET;
                }
    #if 0
                else if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
                || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
                || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET
                || Bit16_Drain_Pump_Error__E60 == SET
                || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
                || Bit7_BLDC_Communication_Error__E27 == SET
                || bit_bldc_operation_error_total == SET )
                {
                    /*..hui [24-1-10���� 3:42:03] ����������.. Ʈ���̿���, �巹����������, �ܱ⼾������, ��������..*/
                    /*..hui [24-2-1���� 4:30:53] ���� �µ����� ������ �߰�..*/
                    play_voice_ice_error_10();
                }
    #endif
                else if( bit_sleep_mode_start == SET )
                {
                    play_voice_sleep_mode_ice_extract_52();
                }
                else {  }
            }
            else
            {
                ice_extraction_finish();
            }
        }
        else
        {
            ice_extraction_finish();
        }
    }
    
    gu8_clock_hide_state = SET;
    gu8_clock_hide_timer = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extraction_finish(void)
{
    if( F_IceOut == SET )
    {
        F_IceOut = CLEAR;
        gu8_ice_out_continue = CLEAR;
        F_IceBreak_Motor_Out = CLEAR;

        /* �ÿ��� + ���� ���ÿ� �������� �� ���ⷮ ������ 1L������ �Ǵ� ���� ���� 250718 CH.PARK */
        // u8Extract_Continue = CLEAR;
        Extract_Stack.U8_iceSelect = CLEAR;

        gu8_normal_ice_acc_cur_count_100ms = CLEAR;
        gu8_normal_ice_acc_set_count_100ms = CLEAR;
        gu8_normal_ice_stay_count = CLEAR;
        bit_normal_ice_out_start = CLEAR;

        /*..hui [20-4-22���� 10:44:03] ��ȸ�� ���� �������� ������� ��� ���� ����..*/
        /*..hui [20-4-22���� 10:44:15] ��ȸ�� �����̸� ��ȸ�� �Ϸ��ϰ� ���� ����..*/
        if( bit_ice_out_back_state == CLEAR )
        {
            F_IR = SET;
            F_Low_IR = SET;
        }
        else{}

        F_IceOutCCW = CLEAR;
        gu8IceClose = 30;         // �������� �������� 3��
        F_ExtractKeySet = CLEAR;

        gu8_Ice_Out_Step = STATE_0_ICE_STANDBY_STATE;
        gu16_ice_out_timer = 0;
        
        // gu16_extract_display_hz = 0;
        // u8Extract_Continue = CLEAR;

        /* ���������� ������ �������� �Ϸ��� �߻� */
        if(u8IceOutState == ICE_SELECT__ICE_WATER)
        {
            /* �������� �� ������ �ƴ� ���¶�� ���� ������ �����ٴ� �� ǥ�� 250730 CH.PARK */
            if(F_WaterOut == CLEAR)
            {
                play_melody_setting_off_199();
            }
            else {  }
        }
        else 
        {
            /* �� �������ε� ���� ������ �Ϸ��ϸ� ���� ���û��� ��� ���� */
            if(F_WaterOut == SET)
            {
                u8IceOutState = ICE_SELECT__NONE;
            }
            else {  }
            
            if(bit_sleep_mode_start == CLEAR)
            {
                play_melody_setting_off_199();
            }
            else {}
        }
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_extract_key(void)
{
    if( F_All_Lock == SET )
    {
        play_voice_all_lock_select_103();
        start_all_lock_flick();
    }
    else
    {
        ice_extraction_start();
    }
}

#ifdef _DISPLAY_FCT_SUB_LINE_
void Display_Test_Mode_Ice_Extract_Key_Short_Input(void)
{
	if(Disp_test_step == DISPLAY_TEST_BTN15)
	{
        Disp_test_step++;
        display_test_flick_timer_100ms = 0;
        play_voice_test_mode_151();
	}
}
#else
void Display_Test_Mode_Ice_Extract_Key_Short_Input(void)
{
    if(gu8_ice_ext_test_input < 1)
    {
        gu8_ice_ext_test_input++;
    }
    else {  }

    // if(gu8_ice_ext_test_input >= 2)
    // {
    //     gu8_ice_ext_test_input = 0;
    // }
    // else{}
    
    play_voice_test_mode_151();
}
#endif

void Uart_Test_Mode_Ice_Extract_Key_Short_Input(void)
{
	gu8_ice_ext_test_input++;

    if(gu8_ice_ext_test_input >= 2)
    {
        gu8_ice_ext_test_input = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

