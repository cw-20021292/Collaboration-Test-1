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
#include    "logic_decision.h"
#include "WIFI_SetFunctionData.h"
#include "WIFI_A101x_FunctionList.h"

void logic_decision(void);
void water_select_return_decision(void);
void water_select_return_timer_control( U8 mu8_flag );
void cup_select_return_decision(void);
void water_out_disable_time_check(void);
void room_water_init_check(void);
void forced_key_clear_decision(void);
void setting_mode_return_decision(void);
void hot_water_setting_mode_timeout_check(void);
void sound_setting_mode_timeout_check(void);
void ice_select_return_decision(void);
void instruction_mode_timeout_check(void);

TYPE_WORD          U16CupLevelSelectW;
#define            u16CupLevelSelect                          U16CupLevelSelectW.word
#define            u8CupLevelSelect_L                         U16CupLevelSelectW.byte[0]
#define            u8CupLevelSelect_H                         U16CupLevelSelectW.byte[1]
#define            Bit0_4_Oz_Select__120_ml                   U16CupLevelSelectW.Bit.b0
#define            Bit1_6_Oz_Select__175_ml                   U16CupLevelSelectW.Bit.b1
#define            Bit2_8_Oz_Select__235_ml                   U16CupLevelSelectW.Bit.b2
#define            Bit3_10_Oz_Select__295_ml                  U16CupLevelSelectW.Bit.b3
#define            Bit4_12_Oz_Select__355_ml                  U16CupLevelSelectW.Bit.b4
#define            Bit5_14_Oz_Select__415_ml                  U16CupLevelSelectW.Bit.b5
#define            Bit6_16_Oz_Select__475_ml                  U16CupLevelSelectW.Bit.b6
#define            Bit7_20_Oz_Select__590_ml                  U16CupLevelSelectW.Bit.b7
#define            Bit8_32_Oz_Select__945_ml                  U16CupLevelSelectW.Bit.b8
#define            Bit9_Continue_Select__Continue             U16CupLevelSelectW.Bit.b9

U8 gu8_cup_level_order;


U16 gu16_water_select_return_time;

CUP_LEVEL gu8Cup_level;
U8 gu8Cup_level_Default;
U8 gu8Cup_level_Old;
U16 gu16_cup_level_default_return_time;



U8 gu8_pre_water_out_state;
U8 gu8_recovery_water_out_state;
bit F_WaterOut_Change_State;

U8 gu8_waterout_disable_time;
bit F_WaterOut_Disable_State;

U8 gu8_cup_level_time_init;
U8 gu8_hot_select_time_init;



U16 gu16_user_default_return_timer;

U8 gu8_water_state;
U8 gu8_cup_state;

U8 gu8_clock_hide_state;
U8 gu8_clock_hide_timer;

U8 gu8_direction_key_disable;
U8 gu8_direction_key_disable_time;

U16 gu16_setting_finish_timer;
bit bit_setting_mode_time_init;

U8 gu8_altitude_return_time;
U8 gu8_altutude_setting_timeout;


U8 gu8_low_level_delay_timer;

U8 gu8_sound_setting_return_time;

U16 gu16_ice_select_return_time;

U8 gu8_instruction_return_timer;
bit bit_instruction_mode_time_init;

ICE_LEVEL  gu8_ice_amount_step;        /* ���� ���ⷮ (�ܰ�) : 1 ~ 4�ܰ� */

/**********************************************************************************************************************/
extern bit bit_instruction_mode_start;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void logic_decision(void)
{
    ice_select_return_decision();

    /*..hui [17-12-19���� 2:03:11] ���� ���� ����..*/
    water_select_return_decision();

    /*..hui [17-12-19���� 2:03:31] �������� ����..*/
    cup_select_return_decision();

    /*..hui [19-8-22���� 5:18:54] ����� ���� ����..*/
    /*user_select_return_decision();*/

    /*..hui [18-3-14���� 3:54:53] ���� ���� �� 500ms �� ���� disable..*/
    water_out_disable_time_check();

    /*..hui [19-6-26���� 1:07:42] ���������� ���� �� ���� ����..*/
    //room_water_init_check();

    /*..hui [19-10-24���� 5:25:23] �����ڸ�� ���� Ű ī��Ʈ..*/
    forced_key_clear_decision();

    /*..hui [19-11-4���� 8:55:38] ���� ��忡�� ����/������ ��ư ���� ���� ����..*/
    /*..hui [19-11-4���� 8:55:50] LCD ������ �� �����. ȭ�� �и����󶧹�..*/
    /*direction_key_disable_time_check();*/

    /*..hui [23-2-9���� 6:23:30] 20�� ���� ��ư �Է� ������� �ڵ�����..*/
    setting_mode_return_decision();

    /*..hui [23-2-22���� 12:34:34] ����� 10�ʰ� ��ư �Է� ������ �ڵ� ����..*/
    hot_water_setting_mode_timeout_check();

    /*..hui [23-11-23���� 5:52:41] ���� ���� 7�ʰ� �ƹ� �Է� ������ �ڵ� ����..*/
    sound_setting_mode_timeout_check();

    instruction_mode_timeout_check();

#if 1
	if(gu8_clock_hide_state == SET)
	{
        if((F_WaterOut == CLEAR)
        && (F_IceOut == CLEAR)
        )
        {
            gu8_clock_hide_timer++;
            if(gu8_clock_hide_timer > 200)
            {
                gu8_clock_hide_timer = 0;
                gu8_clock_hide_state = CLEAR;
            }
        }
        else
        {
            gu8_clock_hide_timer = 0;
        }
	}
	else
	{
		gu8_clock_hide_timer = 0;
		gu8_clock_hide_state = CLEAR;
	}

#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_select_return_decision(void)
{
    if(u8IceOutState == ICE_SELECT__ICE)
    {
        if( F_IceOut == SET )
        {
            gu16_ice_select_return_time = 0;
        }
        else{}    
    }
    else if(u8IceOutState == ICE_SELECT__ICE_WATER)
    {
        /* ������ ������ ������ ������ �Ϸ�Ǿ�� ������ ���ư� �� ���� */
        if((F_IceOut == SET )
        || (F_WaterOut == SET)
        )
        {
            gu16_ice_select_return_time = 0;
        }
        else{  }
    }

    if( u8IceOutState != ICE_SELECT__NONE )
    {
        gu16_ice_select_return_time++;

        /* ����/������ �������̸� 7�� �� ���� �������� ���� */
        if( gu16_ice_select_return_time >= 70 )
        {
            gu16_ice_select_return_time = 0;
            u8IceOutState = ICE_SELECT__NONE;
            Extract_Stack.U8_iceSelect = CLEAR;
        }
        else{}
    }
    else
    {
        gu16_ice_select_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_select_return_decision(void)
{
    /*..hui [19-8-22���� 2:45:46] �¼� ���� �� �����/���� ��ư ���� ��� ���� �ð� �ʱ�ȭ..ĳ�� ���..*/
    if(gu8_hot_select_time_init == SET)
    {
        gu8_hot_select_time_init = CLEAR;

        if(u8WaterOutState == HOT_WATER_SELECT)
        {
            water_select_return_timer_control(0);
        }
        else if(u8WaterOutState == COLD_WATER_SELECT && F_Cold_Enable != SET)
        {
            /*..hui [20-3-6���� 5:23:15] �ü� OFF ���¿��� �ü� ����, ���� ����/����� ��ư ������ ������ ���� �ʱ�ȭ..*/
            water_select_return_timer_control(0);
        }
        else{}
    }
    else{}

    /*..hui [18-1-10���� 10:05:31] ���� ��ư ������ ������..*/
    if(gu8_pre_water_out_state != u8WaterOutState)
    {
        /*..hui [18-1-10���� 10:05:50] �ü� ���� ��ư�� ���õ�����..*/
        if(u8WaterOutState == COLD_WATER_SELECT)
        {
            if(F_Cold_Enable != SET)
            {
                /*..hui [18-1-10���� 10:09:06] �ð���� OFF�� 7�� �� ������ ����..*/
                F_WaterOut_Change_State = SET;
            }
            else
            {
                /*..hui [18-1-10���� 10:09:16] �ð���� ON�� ���� ���� ����..*/
                F_WaterOut_Change_State = CLEAR;
            }
        }
        else
        {
            /*..hui [18-1-10���� 10:06:48] �¼� ��ư�� ���õ�����..*/
            if(u8WaterOutState == HOT_WATER_SELECT)
            {
                F_WaterOut_Change_State = SET;
                /*..hui [18-1-10���� 10:07:23] �¼� ��� �� ���� �� ���� ���� ����..*/
                gu8_recovery_water_out_state = gu8_pre_water_out_state;
            }
            else
            {
                /*..hui [18-1-10���� 10:07:50] ���� ��ư�� ���õ����� �׳� ���� ���� ����..*/
                F_WaterOut_Change_State = CLEAR;
            }
        }

        gu8_pre_water_out_state = u8WaterOutState;
        gu16_water_select_return_time = 0;
    }
    else {  }

    /*..hui [18-1-10���� 10:09:40] ��� �� ���� �����̸�..*/
    if(F_WaterOut_Change_State == SET)
    {
        /*..hui [17-12-14���� 4:53:30] �� �������϶��� ���� �����ϰ� 7��..*/
        if(F_WaterOut == SET)
        {
            if(u8WaterOutState == COLD_WATER_SELECT)
            {
                /*..hui [18-1-10���� 10:17:58] �ð���� OFF ���¿��� �ü� �����ϰ� �����ϸ� ���� �����ϰ� �ٷ� ������ ����..*/
                if(F_Cold_Enable != SET)
                {
                    gu16_water_select_return_time = 69;
                }
                else
                {
                    /*..hui [18-1-10���� 10:28:06] �ð���� ON ������ ���.. ������ ����....*/
                    gu16_water_select_return_time = 0;
                }
            }
            else
            {
                /*..hui [19-8-22���� 2:14:09] �����¼��̹Ƿ� �¼�OFF�϶� ���� ����..*/
                gu16_water_select_return_time = 0;

                #if 0
                if(u8WaterOutState == HOT_WATER_SELECT)
                {
                    /*..hui [18-1-10���� 10:19:07] �¼���� OFF ���¿��� �¼� �����ϰ� �����ϸ� ���� �����ϰ� �ٷ� ���� ���·� ����..*/
                    if(F_Hot_Enable != SET)
                    {
                        gu16_water_select_return_time = 69;
                    }
                    else
                    {
                        /*..hui [18-1-10���� 10:23:58] �¼���� ON �����̸� �ð� �ʱ�ȭ..*/
                        gu16_water_select_return_time = 0;
                    }
                }
                else
                {
                    /*..hui [18-1-10���� 10:24:13] ���� ����̸� �ð� �ʱ�ȭ..*/
                    /*..hui [18-1-10���� 10:24:38] ���� ���� ���¸� ������ ����������.....*/
                    gu16_water_select_return_time = 0;
                }
                #endif
            }
        }
        else
        {
            gu16_water_select_return_time++;
            // /* �ÿ��� �߿� �¼��� ������ �� MY���� ���� �� 
            // �ڿ��� �ÿ��� ������ �ʱ�ȭ�ż� ��鷹���ǿ��� ���������ų� �ü� ������ �� ����
            // (�¼� ���� �ʱ�ȭ ���� Ÿ�̸� ����) 250703 CH.PARK */
            // if(bit_myWater_setting_start == SET)
            // {
            //     if(gu16_water_select_return_time >= 69)
            //     {
            //         gu16_water_select_return_time = 69;
            //     }
            //     else {  }
            // }
            // else {  }
        }

        /*..hui [17-12-14���� 4:31:12] ���� �ð� 7��..*/
        if(gu16_water_select_return_time >= 70)
        {
            gu16_water_select_return_time = 0;
            F_WaterOut_Change_State = CLEAR;

            /*..hui [18-1-10���� 10:10:24] �¼� ���� ���¿�����..*/
            if(u8WaterOutState == HOT_WATER_SELECT)
            {
                /*..hui [18-1-10���� 10:10:35] ���� ���°� �ü� ���� �̾�����..*/
                if(gu8_recovery_water_out_state == COLD_WATER_SELECT)
                {
                    if(F_Cold_Enable == SET)
                    {
                        /*..hui [18-1-10���� 10:10:46] �ð� ON�̸� �ü��� ����..*/
                        u8WaterOutState = COLD_WATER_SELECT;
                        gu8_pre_water_out_state = u8WaterOutState;
                    }
                    else
                    {
                        /*..hui [18-1-10���� 10:10:53] �ð� OFF�̸� ������ ����..*/
                        u8WaterOutState = PURE_WATER_SELECT;
                        gu8_pre_water_out_state = u8WaterOutState;
                    }
                }
                else
                {
                    /*..hui [18-1-10���� 10:11:08] ���� ���°� ���� ���� �̾����� �׳� ������ ����..*/
                    u8WaterOutState = PURE_WATER_SELECT;
                    gu8_pre_water_out_state = u8WaterOutState;
                }
            }
            else
            {
                /*..hui [18-1-10���� 10:11:52] �ð��� OFF�̸� ������ ����..*/
                if(F_Cold_Enable != SET)
                {
                    u8WaterOutState = PURE_WATER_SELECT;
                    gu8_pre_water_out_state = u8WaterOutState;

                    /*..hui [20-3-6���� 5:58:36] ����ڵ� �ʱ�ȭ..*/
                    /*..hui [20-3-6���� 5:58:55] �ü�OFF / ����� ���� / �� ���� �Ϸ�� ��� ������ ����ǰ�..*/
                    /*..hui [20-3-6���� 5:59:01] ����ڴ� �״�� ��������..*/
                    /*..hui [20-3-6���� 5:59:12] �⺻ ������ �� ������ �ٲ�� ����ڵ� �ʱ�ȭ�Ǿ�..*/
                    //gu8_Select_user = USER_SELECT_NONE;
                }
                else{}
            }

            /*..hui [17-12-19���� 2:00:48] �¼� ������ �¼���� ������ �ٷ� ����..*/
            if(u8WaterOutState == HOT_WATER_SELECT && F_Hot_Lock == SET)
            {
                gu16_water_select_return_time = 70;
            }
            else{}

        }
        else{}
    }
    else
    {
        /*..hui [18-1-10���� 10:12:41] �ð��� OFF�̸� ������ ����..*/
        /*..hui [18-1-10���� 10:08:41] �ü� ����,�µ��� ǥ���ϴ� ���� �߻��� ������ ����..*/
        if(F_Cold_Enable != SET)
        {
            u8WaterOutState = PURE_WATER_SELECT;
            gu8_pre_water_out_state = u8WaterOutState;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_select_return_timer_control( U8 mu8_flag )
{
    if(mu8_flag == 0)
    {
        if(F_WaterOut_Change_State == SET)
        {
            gu16_water_select_return_time = 0;
        }
        else{}
    }
    else
    {
        if(F_WaterOut_Change_State == SET)
        {
            gu16_water_select_return_time = 70;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_select_return_decision(void)
{
    /*..hui [19-8-22���� 2:23:13] ������ ��/��/��/�����/���� ���������� �ʱ�ȭ.. ĳ�� ����..*/
    if(gu8_cup_level_time_init == SET)
    {
        /*..hui [19-2-8���� 3:49:45] ���� Ű ��� ���������� �ð� �ʱ�ȭ �߰�..*/
        gu8_cup_level_time_init = CLEAR;
        gu16_cup_level_default_return_time = 0;
        gu8_cup_led_off_time = 0;
    }
    else{}

    if(gu8Cup_level != gu8Cup_level_Default)
    {
        if( u8IceOutState == ICE_SELECT__ICE_WATER )
        {
            if(F_IceOut == SET)
            {
                gu16_cup_level_default_return_time = 0;
            }
            else
            {
                gu16_cup_level_default_return_time++;
            }
        }
        else
        {
            /*..hui [17-12-19���� 2:07:16] �����߿��� �ð� �ʱ�ȭ..*/
            if(F_WaterOut == SET)
            {
                gu16_cup_level_default_return_time = 0;
            }
            else
            {
                gu16_cup_level_default_return_time++;
            }
        }

        if(gu16_cup_level_default_return_time >= CUP_LEVEL_RETURN_TIME)
        {
            gu8Cup_level = gu8Cup_level_Default;
        }
        else{}
        
    }
    else
    {
        gu16_cup_level_default_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_out_disable_time_check(void)
{
    /*..hui [18-3-14���� 12:48:04] �� ���� �� ���� ����Ǵ� �������� 500ms ���� �� ���� �Է� ���� �ʴ´�..*/
    /*..hui [18-3-14���� 12:48:47] ���� ���� ��ư �����µ� ����Ǵ� ������ ���ļ� �ѹ� �� ����Ǵ� ���󶧹�..*/
    /*..hui [18-3-14���� 12:49:16] ǰ���� ��û����.. �� ȿ���� ���� �� ����..*/
    if(F_WaterOut_Disable_State == SET)
    {
        gu8_waterout_disable_time++;

        if(gu8_waterout_disable_time >= 5)
        {
            gu8_waterout_disable_time = 5;
            F_WaterOut_Disable_State = CLEAR;
        }
        else
        {
            /*F_WaterOut_Disable_State = SET;*/
        }
    }
    else
    {
        gu8_waterout_disable_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void room_water_init_check(void)
{
	
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void forced_key_clear_decision(void)
{
    /*..hui [20-3-13���� 2:48:40] ������ ��� Ű ī��Ʈ �ʱ�ȭ..*/
    if(gu8_debug_finish_count > 0)
    {
        gu16_develop_key_clear_time++;

        if(gu16_develop_key_clear_time >= 100)
        {
            gu16_develop_key_clear_time = 0;
            gu8_debug_finish_count = 0;
        }
        else{}
    }
    else
    {
        gu16_develop_key_clear_time = 0;
    }

    /* ��»���� ���� [�ü�] Ű �Է� ī��Ʈ �ʱ�ȭ 250617 CH.PARK */
    if(gu8_passive_hot_ster_key_input_count > 0)
    {
        gu16_passive_hot_ster_key_clear_timer++;

        if(gu16_passive_hot_ster_key_clear_timer >= 100)
        {
            gu16_passive_hot_ster_key_clear_timer = 0;
            gu8_passive_hot_ster_key_input_count = 0;
        }
        else{}
    }
    else
    {
        gu16_passive_hot_ster_key_clear_timer = 0;
    }


    if( gu8_flushing_finish_input_count > 0 )
    {
        gu16_flushing_finish_key_clear_time++;

        if(gu16_flushing_finish_key_clear_time >= 100)
        {
            gu16_flushing_finish_key_clear_time = 0;
            gu8_flushing_finish_input_count = 0;
        }
        else{}
    }
    else
    {
        gu16_flushing_finish_key_clear_time = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_mode_return_decision(void)
{
    if(bit_setting_mode_time_init == SET)
    {
        bit_setting_mode_time_init = CLEAR;
        gu16_setting_finish_timer = 0;
    }
    else{}

    if( bit_setting_mode_start == SET )
    {
        /* ������� 20�� ���� �� TIMEOUT */
        gu16_setting_finish_timer++;
        if( gu16_setting_finish_timer >= SETTING_MODE_EXIT_TIME )
        {
            gu16_setting_finish_timer = 0;
            bit_setting_mode_start = CLEAR;
        }
        else{}
    }
    else
    {
        gu16_setting_finish_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_water_setting_mode_timeout_check(void)
{
    if( bit_altitude_setting_start == SET )
    {
        /*..hui [23-8-2���� 9:45:42] ���� ���� ������ ���� ����..*/
        if( bit_filter_all == CLEAR )
        {
            gu8_altitude_return_time = 0;
            bit_altitude_setting_start = CLEAR;
        }
        else{}

        gu8_altitude_return_time++;

        if( gu8_altitude_return_time >= 100 )
        {
            gu8_altitude_return_time = 0;
            bit_altitude_setting_start = CLEAR;
            play_melody_setting_off_199();
        }
        else{}
    }
    else
    {
        gu8_altitude_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sound_setting_mode_timeout_check(void)
{
    if( bit_volume_setting_start == SET )
    {
        /*..hui [23-8-2���� 9:45:42] ���� ���� ������ ���� ����..*/
        if( bit_filter_all == CLEAR )
        {
            gu8_sound_setting_return_time = 0;
            bit_volume_setting_start = CLEAR;

            send_wifi_each_data_control( WIFI_FUNC_0031_VOICE_SEL );
        }
        else{}

        gu8_sound_setting_return_time++;

        /*..hui [23-11-23���� 5:54:13] 7��������..*/
        if( gu8_sound_setting_return_time >= 70 )
        {
            gu8_sound_setting_return_time = 0;
            bit_volume_setting_start = CLEAR;
            play_melody_setting_off_199();

            send_wifi_each_data_control( WIFI_FUNC_0031_VOICE_SEL );
        }
        else{}
    }
    else
    {
        gu8_sound_setting_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void instruction_mode_timeout_check(void)
{
    if( bit_instruction_mode_time_init == SET )
    {
        bit_instruction_mode_time_init = CLEAR;
        gu8_instruction_return_timer = 0;
    }
    else{}

    if( bit_instruction_mode_start == SET )
    {
        gu8_instruction_return_timer++;

        if( gu8_instruction_return_timer >= 200 )
        {
            gu8_instruction_return_timer = 0;
            bit_instruction_mode_start = CLEAR;
            play_melody_setting_off_199();
        }
        else{}
    }
    else
    {
        gu8_instruction_return_timer = 0;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


