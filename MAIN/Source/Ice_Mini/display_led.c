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
#include    "display_led.h"



void led_normal_state(void);
void led_flushing_state(void);
void funcition_led_output(void);
void level_led_output(void);
void cup_level_led_out(void);
void cup_level_normal_out(void);
void hot_level_led_out(void);
void setting_led_output(void);
void extract_led_output(void);
void make_rgb_color( U8 mu8_color );
void make_ice_outer_rgb_color( U8 mu8_color );
void make_ice_inner_rgb_color( U8 mu8_color );
void recipe_led_output(void);
void welcome_led_output(void);
void cup_level_extract_out(void);
void led_filter_open_state(void);
void all_lock_setting_led(void);

TYPE_WORD          U16ButtonIndicatorB;
#define            gu8_bitton_indicator                        U16ButtonIndicatorB.word
#define            gu8_button_indicator_L                      U16ButtonIndicatorB.byte[0]
#define            gu8_button_indicator_H                      U16ButtonIndicatorB.byte[1]
#define            Bit0_Ice_Lock_Indicator                     U16ButtonIndicatorB.Bit.b0
#define            Bit1_Hot_Lock_Indicator                     U16ButtonIndicatorB.Bit.b1
#define            Bit2_Cold_Off_Indicator                     U16ButtonIndicatorB.Bit.b2
#define            Bit3_Hot_Off_Indicator                      U16ButtonIndicatorB.Bit.b3
#define            Bit4_All_Lock_Indicator                     U16ButtonIndicatorB.Bit.b4
#define            Bit5_Ice_Off_Indicator                      U16ButtonIndicatorB.Bit.b6
#define            Bit6_Icewater_Off_Indicator                 U16ButtonIndicatorB.Bit.b7
#define            Bit7_water_extract_Indicator                U16ButtonIndicatorB.Bit.b8



U8 gu8_cup_led_select;
U8 gu8_cup_led_off_time;

U8 gu8_hot_flick_state;
U8 gu8_cold_flick_state;
U8 gu8_ice_flick_state;
U8 gu8_ice_lock_flick_state;
U8 gu8_icewater_flick_state;
U8 gu8_all_lock_flick_state;

U8 gu8_welcome_light_setting;
bit bit_welcome_on_flag;
bit bit_welcome_start;
bit bit_welcome_wifi_start;
U16 gu16_welcome_timer;

U8 left_normal_state_percent;
U8 right_normal_state_percent;
U8 setting_mode_function_extra_percent;
U8 setting_mode_function_main_percent;
U8 funtion_led_percent;
U8 setting_led_percent;
U8 setting_led_side_percent;
U8 water_extract_led_percent;
U8 ice_extract_outer_led_percent;
U8 ice_extract_inner_led_percent;
U8 bar_led_percent;
U8 receipe_led_percent;
U8 receipe_led_dripcoffee_percent;
U8 big_ster_led_percent;
U8 small_ster_led_percent;
U8 top_small_led_percent;
U8 middle_small_led_percent;
U8 setting_led_side_percent;
U8 receipe_led_dripcoffee_percent;
U8 welcome_left_led_percent;
U8 welcome_right_led_percent;
U8 colon_dot_led_percent;
U8 ice_type_led_percent;

U8 gu8_rgb_r_test_water_extract;
U8 gu8_rgb_g_test_water_extract;
U8 gu8_rgb_b_test_water_extract;

U8 gu8_rgb_r_test_ice_inner_extract;
U8 gu8_rgb_g_test_ice_inner_extract;
U8 gu8_rgb_b_test_ice_inner_extract;

U8 gu8_rgb_r_test_ice_outer_extract;
U8 gu8_rgb_g_test_ice_outer_extract;
U8 gu8_rgb_b_test_ice_outer_extract;

extern U16 gu16_water_select_return_time;
extern U8 gu8_clock_hide_state;
extern bit bit_first_time_setting;
extern U16 gu16_hot_off_flick_timer;
extern U16 gu16_cold_off_flick_timer;
extern U16 gu16_ice_off_flick_timer;
extern U16 gu16_icewater_off_flick_timer;
extern U16 gu16_ice_lock_flick_timer;
extern U8 gu8_clock_hide_state;
extern bit bit_myWater_setting_start;

extern bit F_IceOn;
extern bit F_All_Lock;
extern FLUSHING_STEP gu8_flushing_mode;
extern U8 gu8_Setting_Focus;
extern bit bit_fast_ice_make;
extern bit F_Hot_Enable;
extern special_func cody_water_line;
extern bit F_Wink_500ms; 
extern U8 gu8_Icewater_level;
extern void stop_cold_off_flick();
extern void stop_hot_off_flick();
extern void stop_ice_off_flick();
extern void stop_icewater_off_flick();
extern void stop_ice_lock_flick(void);
extern U8 hot_off_flickering_timer(U8 flick_time, U8 interval);
extern U8 ice_lock_flickering_timer(U8 flick_time, U8 interval);
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_normal_state(void)
{
	if(F_All_Lock == SET)
	{
		fnd_left_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);
		fnd_right_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);

        gu8_front_left_led = 0;
        gu8_front_left_led_2 = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        gu8_front_center_recipe_led = 0;

        gu8_front_select_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_setting_led_2 = 0x02;
        gu8_front_under_text_led = 0;
        gu8_front_under_icon_led = 0;

        

		all_duty_100_percent();
	}
	else
	{
		funcition_led_output();
		setting_led_output();
		extract_led_output();
		recipe_led_output();

		level_led_output();

		icon_led_output();
	}
}


void led_flushing_state(void)
{
    /* ���ͱ�ü ���� ����ǥ�� �� �ü���ư LED On */
    if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
	{
		///////if( gu8_filter_flushing_state == SET && bit_filter_flushing_no_cancel == CLEAR )
		if( ( bit_filter_flushing_check == CLEAR ) && (bit_yes_no_popup == SET) )
		{
			Bit4_Front_Led_Cold_Select = SET;
		}
		else
		{
			Bit4_Front_Led_Cold_Select = CLEAR;
		}
	}
	else
	{
		Bit4_Front_Led_Cold_Select = CLEAR;
	}

    extract_led_output();
    percent_icon_out();
    wifi_icon_output();
    filter_clean_txt_out();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_setting_state(void)
{ 
	if(F_All_Lock == SET)
	{
		fnd_left_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);
		fnd_right_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);

		gu8_front_left_led = 0;
		gu8_front_right_led = 0;
		gu8_front_temp_setting_bar_led = 0;
		gu8_front_amount_setting_bar_led = 0;
		gu8_front_center_recipe_led = 0;

		gu8_front_select_led = 0;
		gu8_front_under_text_led = 0;
		gu8_front_under_icon_led = 0;

        all_duty_100_percent();
	}
	else
	{
		gu8_front_left_led = 0;
		gu8_front_right_led = 0;
		gu8_front_temp_setting_bar_led = 0;
		gu8_front_amount_setting_bar_led = 0;
		gu8_front_center_recipe_led = 0;
		
		Bit0_Front_Led_Ice_Select = CLEAR;
		Bit1_Front_Led_Ice_Water_Select = CLEAR;
		Bit2_Front_Led_Hot_Select = CLEAR;
		Bit3_Front_Led_Ambient_Select = CLEAR;
		Bit4_Front_Led_Cold_Select = CLEAR;
		Bit5_Front_Led_Amount_Select = SET;
		Bit6_Front_Led_My_Select = CLEAR; 
	
		funcition_led_output();
		//level_led_output();
		setting_led_output();
		extract_led_output();
		//recipe_led_output();
		under_text_led_output();
		under_icon_led_output();

		icon_led_output();
	}
}

void led_time_setting_state(void)
{ 
    Bit0_Front_Led_Ice_Select = SET;
    Bit1_Front_Led_Ice_Water_Select = SET;
    Bit5_Front_Led_Amount_Select = SET;
    Bit6_Front_Left_Led_Clock_Colon_Icon = SET;
    
    set_duty_percent( DIMMING__PERCENT_ICE_SELECT, funtion_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_WATER_SELECT, funtion_led_percent );
    set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, funtion_led_percent );
    set_duty_percent( DIMMING__PERCENT_CLOCK_COLON_ICON, colon_dot_led_percent );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void funcition_led_output(void)
{
    U8 mu8_flick_state = 0;
    U8 mu8_cold_flick_state = 0;
    U8 mu8_hot_flick_state = 0;
    U8 mu8_hot_lock_flick_state = 0;
    U8 mu8_ice_flick_state = 0;
    U8 mu8_ice_water_flick_state = 0;

    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_ICE_SELECT, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_ICE_WATER_SELECT, SLEEP_MODE_DIMMING_PERCENT );

        set_duty_percent( DIMMING__PERCENT_HOT_SELECT, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, SLEEP_MODE_DIMMING_PERCENT );

        set_duty_percent( DIMMING__PERCENT_COLD_SELECT, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_MY_SELECT, SLEEP_MODE_DIMMING_PERCENT );
    }
    else if(gu8_Led_Display_Step == LED_Display__SETTING)
    {
        set_duty_percent( DIMMING__PERCENT_ICE_SELECT, setting_mode_function_extra_percent );
        set_duty_percent( DIMMING__PERCENT_ICE_WATER_SELECT, setting_mode_function_extra_percent );

        set_duty_percent( DIMMING__PERCENT_HOT_SELECT, setting_mode_function_extra_percent );
        set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, setting_mode_function_extra_percent );

        set_duty_percent( DIMMING__PERCENT_COLD_SELECT, setting_mode_function_extra_percent );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, setting_mode_function_main_percent );
        set_duty_percent( DIMMING__PERCENT_MY_SELECT, setting_mode_function_extra_percent );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_ICE_SELECT, funtion_led_percent );
        set_duty_percent( DIMMING__PERCENT_ICE_WATER_SELECT, funtion_led_percent );

        set_duty_percent( DIMMING__PERCENT_HOT_SELECT, funtion_led_percent );
        set_duty_percent( DIMMING__PERCENT_AMBIENT_SELECT, funtion_led_percent );

        set_duty_percent( DIMMING__PERCENT_COLD_SELECT, funtion_led_percent );
        set_duty_percent( DIMMING__PERCENT_AMOUNT_SELECT, funtion_led_percent );
        set_duty_percent( DIMMING__PERCENT_MY_SELECT, funtion_led_percent );
    }

    if( bit_setting_mode_start == SET )
    {
        if(F_IceOn == SET)
        {
            Bit0_Front_Led_Ice_Select = SET;
            Bit1_Front_Led_Ice_Water_Select = SET;
        }
        else
        {
            Bit0_Front_Led_Ice_Select = CLEAR;
            Bit1_Front_Led_Ice_Water_Select = CLEAR;
        }

        if(F_Cold_Enable == SET)
        {
            Bit4_Front_Led_Cold_Select = SET;
        }
        else
        {
            Bit4_Front_Led_Cold_Select = CLEAR;
        }

        Bit6_Front_Led_My_Select = SET;
        Bit2_Front_Led_Hot_Select = SET;
        Bit3_Front_Led_Ambient_Select = SET;
        return;
    }

    if(bit_display_sleep_start == SET)
    {
        Bit6_Front_Led_My_Select         = CLEAR;
        Bit0_Front_Led_Ice_Select        = CLEAR;
        Bit1_Front_Led_Ice_Water_Select  = CLEAR;
        Bit2_Front_Led_Hot_Select        = CLEAR;
        Bit3_Front_Led_Ambient_Select    = CLEAR;
        Bit4_Front_Led_Cold_Select       = CLEAR;
        Bit5_Front_Led_Amount_Select     = CLEAR;
        return;
    }

    if(bit_myWater_setting_start == SET)
    {
        Bit6_Front_Led_My_Select = SET;
    }
    else
    {
        Bit6_Front_Led_My_Select = CLEAR;
    }

    if(F_Ice_Lock == SET)
    {
        if(Bit0_Ice_Lock_Indicator == SET)
        {
            gu8_ice_lock_flick_state = ice_lock_flickering_timer(5, 5);
        }
        else
        {
            gu8_ice_lock_flick_state = 0;
        }
        Bit0_Front_Led_Ice_Select = CLEAR;

        /* ������� ���¸� ������ ���� LED ��! 250714 CH.PARK */
        Bit1_Front_Led_Ice_Water_Select = CLEAR;
    }
    else
    {
        stop_ice_lock_flick();
        if(F_IceOn == SET)
        {
            if( u8IceOutState == ICE_SELECT__ICE )
            {
                Bit0_Front_Led_Ice_Select = SET;
            }
            else
            {
                Bit0_Front_Led_Ice_Select = CLEAR;
                stop_ice_off_flick();
            }
        }
        else
        {
            if( u8IceOutState == ICE_SELECT__ICE )
            {
                if(Bit5_Ice_Off_Indicator == SET)
                {
                    gu8_ice_flick_state = ice_off_flickering_timer(5, 5);
                }
                else
                {
                    gu8_ice_flick_state = 0;
                }
                Bit0_Front_Led_Ice_Select = SET;
            }
            else
            {
                Bit0_Front_Led_Ice_Select = CLEAR;
                stop_ice_off_flick();
            }
        }

        if(F_IceOn == SET)
        {
            if( u8IceOutState == ICE_SELECT__ICE_WATER )
            {
                Bit1_Front_Led_Ice_Water_Select = SET;
            }
            else
            {
                Bit1_Front_Led_Ice_Water_Select = CLEAR;
                stop_icewater_off_flick();
            }
        }
        else
        {
            if( u8IceOutState == ICE_SELECT__ICE_WATER )
            {
                if(Bit6_Icewater_Off_Indicator == SET)
                {
                    gu8_icewater_flick_state = icewater_off_flickering_timer(5, 5);
                }
                else
                {
                    gu8_icewater_flick_state = 0;
                }
                Bit1_Front_Led_Ice_Water_Select = SET;
            }
            else
            {
                Bit1_Front_Led_Ice_Water_Select = CLEAR;
                stop_icewater_off_flick();
            }
        }
    }

    /* �¼� ���ù�ư */
    if( F_Hot_Lock == SET )
    {
        if(Bit3_Hot_Off_Indicator == SET)
        {
            gu8_hot_flick_state = hot_off_flickering_timer(5, 5);
        }
        else
        {
            gu8_hot_flick_state = 0;
        }

        Bit2_Front_Led_Hot_Select = CLEAR;
    }
    else
    {
        stop_hot_off_flick();
        
        if(u8IceOutState != ICE_SELECT__NONE)
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
        else if(bit_myWater_setting_start == SET)
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
        else if( u8WaterOutState == HOT_WATER_SELECT )
        {
            Bit2_Front_Led_Hot_Select = SET;
        }
        else
        {
            Bit2_Front_Led_Hot_Select = CLEAR;
        }
    }

    /* ���� ���ù�ư */
    if(u8IceOutState != ICE_SELECT__NONE)
    {
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }
    else if(bit_myWater_setting_start == SET)
    {
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }
    else
    {
        if( u8WaterOutState == PURE_WATER_SELECT )
        {
            Bit3_Front_Led_Ambient_Select = SET;
        }
        else
        {
            Bit3_Front_Led_Ambient_Select = CLEAR;
        }
    }

    /* �ü� ���ù�ư */
    if(u8IceOutState != ICE_SELECT__NONE)
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
        
        /* �������� ����OFF�� ����, �ü� OFF�� ���� FLICKER ǥ�ø� �ؾ���.
        ��, ����OFF FLICKER�� �켱�� 250722 CH.PARK */
        if( u8IceOutState == ICE_SELECT__ICE_WATER )
        {
            if(Bit2_Cold_Off_Indicator == SET)
            {
                gu8_cold_flick_state = cold_off_flickering_timer(5, 5);
            }
            else
            {
                gu8_cold_flick_state = 0;
            }
            Bit1_Front_Led_Ice_Water_Select = SET;
        }
        else
        {
            Bit1_Front_Led_Ice_Water_Select = CLEAR;
            stop_cold_off_flick();
        }
    }
    else if(bit_myWater_setting_start == SET)
    {
        Bit4_Front_Led_Cold_Select = CLEAR;
    }
    else
    {
        if( F_Cold_Enable == SET )
        {
            if( u8WaterOutState == COLD_WATER_SELECT )
            {
                Bit4_Front_Led_Cold_Select = SET;
            }
            else
            {
                Bit4_Front_Led_Cold_Select = CLEAR;
            }
        }
        else
        {
            if( u8WaterOutState == COLD_WATER_SELECT )
            {
                if(Bit2_Cold_Off_Indicator == SET)
                {
                    gu8_cold_flick_state = cold_off_flickering_timer(5, 5);
                }
                else
                {
                    gu8_cold_flick_state = 0;
                }

                Bit4_Front_Led_Cold_Select = SET;
            }
            else
            {
                Bit4_Front_Led_Cold_Select = CLEAR;
                stop_cold_off_flick();
            }
        }
    }

    /* �뷮 ���ù�ư */
    if(gu16_ice_lock_flick_timer != 0)
    {
        if( gu8_ice_lock_flick_state == SET )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            Bit5_Front_Led_Amount_Select = CLEAR;
        }
    }
    else if(gu16_hot_off_flick_timer != 0 )
    {
        if( gu8_hot_flick_state == SET )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            Bit5_Front_Led_Amount_Select = CLEAR;
        }
    }
    else if(gu16_cold_off_flick_timer != 0 )
    {
        if( gu8_cold_flick_state == SET )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            Bit5_Front_Led_Amount_Select = CLEAR;
        }
    }
    else if(gu16_ice_off_flick_timer != 0 )
    {
        if( gu8_ice_flick_state == SET )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            Bit5_Front_Led_Amount_Select = CLEAR;
        }
    }
    else if(gu16_icewater_off_flick_timer != 0)
    {
        if( gu8_icewater_flick_state == SET )
        {
            Bit5_Front_Led_Amount_Select = SET;
        }
        else
        {
            Bit5_Front_Led_Amount_Select = CLEAR;
        }
    }
    else
    {
        if( gu8_cup_led_select == SET )
        {
            /*..hui [20-1-7���� 10:01:44] �� �����ϸ� ��� OFF..*/
            if( F_WaterOut == SET )
            {
                gu8_cup_led_select = CLEAR;
            }
            else{}

            gu8_cup_led_off_time++;

            /*..hui [20-1-7���� 10:01:54] �����ϰ� 7�� �� OFF..*/
            if( gu8_cup_led_off_time < CUP_SELECT_LED_OFF_TIME )
            {
                Bit5_Front_Led_Amount_Select = SET;
            }
            else
            {
                gu8_cup_led_select = CLEAR;
            }
	    }
	    else
	    {
            if(bit_myWater_setting_start == SET)
            {
                Bit5_Front_Led_Amount_Select = CLEAR;
            }
            else
            {
                Bit5_Front_Led_Amount_Select = SET;
            }
	        gu8_cup_led_off_time = 0;
	    }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void level_led_output(void)
{
    cup_level_led_out();
    hot_level_led_out();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_led_out(void)
{
    if( F_WaterOut == SET )
    {
        /*..hui [25-5-30���� 2:04:00] ���������϶��� ����, �� �� �����϶��� ���� ���� ����.. ������..*/
        if( u8Extract_Continue == SET )
        {
            /*..hui [24-2-26���� 1:24:30] �� �������ʰ� ���� ���� �����ϵ���....*/
            cup_level_extract_out();
        }
        else
        {
            cup_level_normal_out();
        }
    }
    else if( F_IceOut == SET)
    {
        /*..hui [25-5-30���� 2:06:14] �������⶧�� ����, ������ ���⶧�� ���� ���� ����.. ������..*/
        if( u8IceOutState == ICE_SELECT__ICE )
        {
            cup_level_extract_out();
        }
        else
        {
            cup_level_normal_out();
        }
    }
    else
    {
        cup_level_normal_out();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_normal_out(void)
{
    if(bit_display_sleep_start == SET)
    {
        Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
		Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
		Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
		Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
		Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
    }
    else if( (bit_first_time_setting == SET )
	&& ( gu8_cup_led_select == CLEAR ) 
    && ( gu16_water_select_return_time == 0 )
    && (bit_myWater_setting_start == 0)
	&& (gu8_clock_hide_state == CLEAR) 
    && (F_WaterOut == CLEAR) 
    && (F_IceOut == CLEAR)
    )
	{
		Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
		Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
		Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
		Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
		Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
	}
	else
	{
        /* ������ ������ ���¸�, �뷮 ǥ�� �κ��� ��� OFF */
        if(u8IceOutState == ICE_SELECT__ICE || bit_myWater_setting_start == SET)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else
        {
            if((Bit2_Cold_Off_Indicator != 0) 
            || (Bit0_Ice_Lock_Indicator != 0)
            || (Bit6_Icewater_Off_Indicator != 0)
            || (Bit5_Ice_Off_Indicator != 0)
            )
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
            }
            else
            {
                /* �������� �� */
                if( u8IceOutState == ICE_SELECT__ICE_WATER )
                {
                    Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                    Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                    Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                    Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                    Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

                    if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_1_150ML)
                    {
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
                        }

                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
                    }
                    else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_2_250ML)
                    {
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, bar_led_percent );
                        }

                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
                    }
                    else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_3_350ML)
                    {
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, bar_led_percent );
                        }

                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
                    }
                    else if(gu8_Icewater_level == ICEWATER_CUP_LEVEL_4_500ML)
                    {
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, bar_led_percent );
                        }

                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
                    }
                    else
                    {
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
                        }

                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
                    }
                }
                else
                {
                    if( gu8Cup_level == CUP_LEVEL_1_120ML )
                    {
                        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                        
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, bar_led_percent );
                        }
        
                        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        
                        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        
                        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
                        
                        // ������ �������̸� �������� ��
                        if(u8IceOutState == ICE_SELECT__ICE_WATER)
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
                        }
                        else
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
                        }
                    }
                    else if( gu8Cup_level == CUP_LEVEL_2_250ML )
                    {
                        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        
                        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, bar_led_percent );
                        }

                        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        
                        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        
                        // ������ �������̸� �������� ��
                        if(u8IceOutState == ICE_SELECT__ICE_WATER)
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
                        }
                        else
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
                        }
                    }
                    else if( gu8Cup_level == CUP_LEVEL_3_500ML )
                    {
                        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        
                        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        
                        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, bar_led_percent );
                        }
        
                        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        
                        // ������ �������̸� �������� ��
                        if(u8IceOutState == ICE_SELECT__ICE_WATER)
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
                        }
                        else
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
                        }
                    }
                    else if( gu8Cup_level == CUP_LEVEL_4_1000ML )
                    {
                        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        
                        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        
                        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        
                        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, bar_led_percent );
                        }
                        
                        // ������ �������̸� �������� ��
                        if(u8IceOutState == ICE_SELECT__ICE_WATER)
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
                        }
                        else
                        {
                            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
                        }
        
                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_RIGHT_SEG_DOT, colon_dot_led_percent );
                        }
                    }
                    else
                    {
                        Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
        
                        Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
        
                        Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
        
                        Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                        set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
        
                        Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;

                        if( gu8_Led_Display_Step == LED_Display__SLEEP )
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, SLEEP_MODE_DIMMING_PERCENT );
                        }
                        else
                        {
                            set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, bar_led_percent );
                        }
                    }
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_level_led_out(void)
{
    /*..hui [23-8-18���� 11:28:50] ���� �����߿��� ����..*/
    /*if( F_IceOut == SET && gu8_Led_Display_Step == LED_Display__MY_WATER_EXTRACT )*/
    
    /* ��ħ��� ���� ���¸� ��� OFF */
    if(bit_display_sleep_start == SET)
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        return;
    }
    else {  }

    if(u8IceOutState != ICE_SELECT__NONE)
    {
        if((Bit2_Cold_Off_Indicator != 0) 
        || (Bit0_Ice_Lock_Indicator != 0)
        || (Bit6_Icewater_Off_Indicator != 0)
        || (Bit5_Ice_Off_Indicator != 0)
        )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else
        {
            if(gu8_ice_amount_step == ICE_LEVEL_1_STEP)
            {
                if( gu8_Led_Display_Step == LED_Display__SLEEP )
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, SLEEP_MODE_DIMMING_PERCENT );
                }
                else
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, bar_led_percent );
                }
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_2_STEP)
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                if( gu8_Led_Display_Step == LED_Display__SLEEP )
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, SLEEP_MODE_DIMMING_PERCENT );
                }
                else
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, bar_led_percent );
                }
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_3_STEP)
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );

                if( gu8_Led_Display_Step == LED_Display__SLEEP )
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, SLEEP_MODE_DIMMING_PERCENT );
                }
                else
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, bar_led_percent );
                }
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else if(gu8_ice_amount_step == ICE_LEVEL_4_STEP)
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );

                if( gu8_Led_Display_Step == LED_Display__SLEEP )
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
                }
                else
                {
                    set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
                }
            }

            /* ���� �������� �� �����뷮 �����ٴ� OFF */
            if(gu8_ice_out_continue == SET)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
            }
            else
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
            }
        }
    }
    else if(bit_myWater_setting_start == SET)             /* ���,�帳Ŀ��,��,MY1,MY2,MY3 */
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
    }
    else if( u8WaterOutState == PURE_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
    }
    else if( u8WaterOutState == COLD_WATER_SELECT )
    {
        Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
        Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
        Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
        Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
        Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
    }
    else /*if( u8WaterOutState == HOT_WATER_SELECT )*/
    {
        if( gu8_hot_setting_temperature == selected_hot_temp[0] )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
            
            if( gu8_Led_Display_Step == LED_Display__SLEEP )
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
            }
            else
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
            }
        }
        else if( gu8_hot_setting_temperature == selected_hot_temp[1])
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

            if( gu8_Led_Display_Step == LED_Display__SLEEP )
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, SLEEP_MODE_DIMMING_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, bar_led_percent );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
        }
        else if( gu8_hot_setting_temperature == selected_hot_temp[2] )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

            if( gu8_Led_Display_Step == LED_Display__SLEEP )
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, SLEEP_MODE_DIMMING_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, bar_led_percent );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
        }
        else if (gu8_hot_setting_temperature == selected_hot_temp[3] )
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

            if( gu8_Led_Display_Step == LED_Display__SLEEP )
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, SLEEP_MODE_DIMMING_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
            else
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, bar_led_percent );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, DIIMMING__10_PERCENT );
            }
        }
        else
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
            
            if( gu8_Led_Display_Step == LED_Display__SLEEP )
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, SLEEP_MODE_DIMMING_PERCENT );
            }
            else
            {
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_1, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_2, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_3, DIIMMING__10_PERCENT );
                set_duty_percent( DIMMING__PERCENT_TEMP_BAR_1_4, bar_led_percent );
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void setting_led_output(void)
{
    U8 mu8_flick_state = 0;
    
    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_SIZE, setting_led_percent );
    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_OFF, setting_led_percent );

    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_FIRST, setting_led_percent );
    set_duty_percent( DIMMING__PERCENT_SETTING_COLD_TEMP, setting_led_percent );

    set_duty_percent( DIMMING__PERCENT_SETTING_SLEEP_MODE, setting_led_percent );
    set_duty_percent( DIMMING__PERCENT_SETTING_ICE_LOCK, setting_led_side_percent );

    set_duty_percent( DIMMING__PERCENT_SETTING_ALL_LOCK, setting_led_side_percent );
    set_duty_percent( DIMMING__PERCENT_SETTING_HOT_LOCK, setting_led_percent );

    set_duty_percent( DIMMING__PERCENT_COLD_OFF, setting_led_percent );
    
    if( gu8_Led_Display_Step == LED_Display__ERROR )
    {
        set_duty_percent( DIMMING__PERCENT_FAST_ICE_ICON, DIIMMING__0_PERCENT );
    }
    else if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_FAST_ICE_ICON, SLEEP_MODE_DIMMING_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_FAST_ICE_ICON, top_small_led_percent );
    }

    if( bit_setting_mode_start == SET )
    {
        Bit0_Front_Led_Ice_Size = SET;
        Bit1_Front_Led_Ice_Off = SET;
        Bit2_Front_Led_Hot_Lock_Text = SET;
        Bit3_Front_Led_Ice_First = SET;
        Bit4_Front_Led_Cold_Temp = SET;
        Bit5_Front_Led_Sleep_Mode_Text = SET;
        Bit0_Front_Led_Ice_Lock = SET;
        Bit1_Front_Led_All_Lock = SET;

        /* �������� �������´� ��� ������ 250512 CH.PARK */
        if(bit_fast_ice_make == ICE_FIRST_ICE_MAKE)
        {
            Bit4_Front_Led_Icon_Fast_Ice = SET;
        }
        else
        {
            Bit4_Front_Led_Icon_Fast_Ice = CLEAR;
        }
    }
    else
    {
        if(bit_display_sleep_start == SET)
        {
            Bit4_Front_Led_Icon_Fast_Ice = CLEAR;
        }
        else
        {
            /* �������� �������´� ��� ������ 250512 CH.PARK */
            if(bit_fast_ice_make == ICE_FIRST_ICE_MAKE && F_IceOn == SET)
            {
                Bit4_Front_Led_Icon_Fast_Ice = SET;
            }
            else
            {
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;
            }
        }

        if( Bit0_Ice_Lock_Indicator == SET )
        {
            if(gu16_ice_lock_flick_timer != 0)
            {
                if( gu8_ice_lock_flick_state == SET )
                {
                    Bit0_Front_Led_Ice_Lock = SET;
                }
                else
                {
                    Bit0_Front_Led_Ice_Lock = CLEAR;
                }
            }
            else
            {
                Bit0_Front_Led_Ice_Lock = CLEAR;
            }

            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit1_Front_Led_Ice_Off = CLEAR;
            Bit2_Front_Led_Hot_Lock_Text = CLEAR;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;

            Bit1_Front_Led_All_Lock = CLEAR;
            Bit6_Front_Led_Cold_Off = CLEAR;
						
        }
        else if( Bit1_Hot_Lock_Indicator == SET )
        {
            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit1_Front_Led_Ice_Off = CLEAR;
            //Bit2_Front_Led_Hot_Lock_Text = Bit0_Front_Led_Set_Select;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            Bit0_Front_Led_Ice_Lock = CLEAR;
            Bit1_Front_Led_All_Lock = CLEAR;
            Bit6_Front_Led_Cold_Off = CLEAR;
        }
        else if(Bit2_Cold_Off_Indicator == SET)
        {
            if(gu16_cold_off_flick_timer != 0 )
            {
                if( gu8_cold_flick_state == SET )
                {
                    Bit6_Front_Led_Cold_Off = SET;
                }
                else
                {
                    Bit6_Front_Led_Cold_Off = CLEAR;
                }
            }

            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit1_Front_Led_Ice_Off = CLEAR;
            Bit2_Front_Led_Hot_Lock_Text = CLEAR;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            Bit0_Front_Led_Ice_Lock = CLEAR;
            Bit1_Front_Led_All_Lock = CLEAR;
        }
        else if(Bit3_Hot_Off_Indicator == SET)
        {
            if(gu16_hot_off_flick_timer != 0 )
            {
                if( gu8_hot_flick_state == SET )
                {
                    Bit2_Front_Led_Hot_Lock_Text = SET;
                }
                else
                {
                    Bit2_Front_Led_Hot_Lock_Text = CLEAR;
                }
            }

            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit1_Front_Led_Ice_Off = CLEAR;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            Bit0_Front_Led_Ice_Lock = CLEAR;
            Bit1_Front_Led_All_Lock = CLEAR;
            Bit6_Front_Led_Cold_Off = CLEAR;
        }
        else if(Bit5_Ice_Off_Indicator == SET)
        {
            if(gu16_ice_off_flick_timer != 0 )
            {
                if( gu8_ice_flick_state == SET )
                {
                    Bit1_Front_Led_Ice_Off = SET;
                }
                else
                {
                    Bit1_Front_Led_Ice_Off = CLEAR;
                }
            }

                Bit0_Front_Led_Ice_Size = CLEAR;
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;
                Bit3_Front_Led_Ice_First = CLEAR;
                Bit4_Front_Led_Cold_Temp = CLEAR;
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
                Bit0_Front_Led_Ice_Lock = CLEAR;
                Bit1_Front_Led_All_Lock = CLEAR;
                Bit6_Front_Led_Cold_Off = CLEAR;
        }
        else if(Bit6_Icewater_Off_Indicator == SET)
        {
            if(gu16_icewater_off_flick_timer != 0 )
            {
                if( gu8_icewater_flick_state == SET )
                {
                    Bit1_Front_Led_Ice_Off = SET;
                }
                else
                {
                    Bit1_Front_Led_Ice_Off = CLEAR;
                }
            }

            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit2_Front_Led_Hot_Lock_Text = CLEAR;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            Bit0_Front_Led_Ice_Lock = CLEAR;
            Bit1_Front_Led_All_Lock = CLEAR;
            Bit6_Front_Led_Cold_Off = CLEAR;
        }
        else
        {
            Bit0_Front_Led_Ice_Size = CLEAR;
            Bit1_Front_Led_Ice_Off = CLEAR;
            Bit2_Front_Led_Hot_Lock_Text = CLEAR;
            Bit3_Front_Led_Ice_First = CLEAR;
            Bit4_Front_Led_Cold_Temp = CLEAR;
            Bit5_Front_Led_Sleep_Mode_Text = CLEAR;
            Bit0_Front_Led_Ice_Lock = CLEAR;
            Bit1_Front_Led_All_Lock = CLEAR;
            Bit6_Front_Led_Cold_Off = CLEAR;
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void extract_led_output(void)
{
    set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, ice_extract_outer_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, ice_extract_inner_led_percent );

    /*..hui [23-6-2���� 12:23:06] �÷��� ����� ����..*/
    if((gu8_Led_Display_Step == LED_Display__FLUSHING) 
    && (gu8_flushing_mode == FLUSHING_STANDBY_STATE)
    )
    {
        Bit4_Front_Under_Water_White_Extract = F_Wink_500ms;
        Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        
        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
        return;
    }
    else if( gu8_Led_Display_Step == LED_Display__FLUSHING
    && gu8_flushing_mode > FLUSHING_STANDBY_STATE )
    {
        Bit4_Front_Under_Water_White_Extract = SET;
        Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        
        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
        return;
    }

    /* �ð�������� */
    if(bit_time_setting_start == SET)
    {
        Bit4_Front_Under_Water_White_Extract = CLEAR;
        Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        
        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
        return;
    }
    else {  }

    /* �����巹�� */
    if( bit_manual_drain_start == SET )
    {
		Bit4_Front_Under_Water_White_Extract ^= SET;
		Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;

        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
		return;
    }
	else{}

    /* ��� ��� ���� �� ���� ����� LED�� WHITE��. (��, ��������� ������ OFF) 250725 CH.PARK */
    if(bit_ice_tank_ster_start == SET)
    {
        Bit4_Front_Under_Water_White_Extract = SET;
        Bit3_Front_Under_Ice_Outer_White_Extract = SET;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        
        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
        return;
    }
    else {  }

    /* ���ø�忡���� ���� ��ư�� LED ��ü OFF 250218 CH.PARK */
    if(special_mode_check_U8() != CLEAR)
    {
        Bit4_Front_Under_Water_White_Extract = CLEAR;
        Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        make_rgb_color( RGB_OFF );
        make_ice_outer_rgb_color(RGB_OFF);
        make_ice_inner_rgb_color(RGB_OFF);
    }
    else
    {
        /* MY���� ������ */
        if(bit_myWater_setting_start == SET)        /* ���, Ŀ��, Ƽ, MY123 ���ø�� (�������� �¼��µ� �����̱� ������ Red ǥ��) 250218 CH.PARK */
        {
            if(my_setting[my_recipe_select].temp == 6)
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_COLOR_COLD );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else if(my_setting[my_recipe_select].temp == 27)
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
            }
            else
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_COLOR_HOT );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
        }
        else
        {
            /* �ÿ��� */
            if( u8WaterOutState == HOT_WATER_SELECT )
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_COLOR_HOT );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else if( u8WaterOutState == COLD_WATER_SELECT )
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_COLOR_COLD );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else /*if( u8WaterOutState == PURE_WATER_SELECT )*/
            {
                Bit4_Front_Under_Water_White_Extract = SET;
                make_rgb_color( RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
            }
        }

        if(u8IceOutState == ICE_SELECT__ICE_WATER)      /* ������ ���� �� */
        {
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;

            /* ����[����] ���� �� */
            if(F_IceBreak == SET)
            {
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;
                make_ice_inner_rgb_color(RGB_COLOR_COLD);
            }
            else
            {
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
                make_ice_inner_rgb_color(RGB_OFF);
            }

            make_ice_outer_rgb_color(RGB_COLOR_COLD);
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
        }
        else
        {
            /* ���� ���� �� or ���� ���� �̼������� �� (Default) 250625 CH.PARK */
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            
            /* ����[����] ���� �� */
            if(F_IceBreak == SET)
            {
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            }
            else
            {
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            }

            make_ice_inner_rgb_color(RGB_OFF);
            make_ice_outer_rgb_color(RGB_OFF);

            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, ice_extract_outer_led_percent );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, ice_extract_inner_led_percent );
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == RGB_COLOR_HOT )
    {
        gu8_rgb_r_test_water_extract = 40;      // �¼��� 40%
        gu8_rgb_g_test_water_extract = 0;
        gu8_rgb_b_test_water_extract = 0;

        gu8_rgb_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_water_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_water_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_water_extract * gu8_rgb_pwm_period) / 100);
    }
    else if( mu8_color == RGB_COLOR_COLD )
    {
        gu8_rgb_r_test_water_extract = 0;
        gu8_rgb_g_test_water_extract = 40;
        gu8_rgb_b_test_water_extract = 60;

        gu8_rgb_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_water_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_water_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_water_extract * gu8_rgb_pwm_period) / 100);
    }
    else
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_ice_inner_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == RGB_COLOR_HOT )
    {
        gu8_rgb_r_test_ice_inner_extract = 40;      // �¼��� 40%
        gu8_rgb_g_test_ice_inner_extract = 0;
        gu8_rgb_b_test_ice_inner_extract = 0;

        gu8_rgb_ice_inner_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_inner_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_inner_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
    }
    else if( mu8_color == RGB_COLOR_COLD )
    {
        gu8_rgb_r_test_ice_inner_extract = 0;
        gu8_rgb_g_test_ice_inner_extract = 40;
        gu8_rgb_b_test_ice_inner_extract = 60;

        gu8_rgb_ice_inner_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_inner_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_inner_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_ice_inner_extract * gu8_rgb_pwm_period) / 100);
    }
    else
    {
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 0;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_ice_outer_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == RGB_COLOR_HOT )
    {
        gu8_rgb_r_test_ice_outer_extract = 40;      // �¼��� 40%
        gu8_rgb_g_test_ice_outer_extract = 0;
        gu8_rgb_b_test_ice_outer_extract = 0;

        gu8_rgb_ice_outer_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_outer_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_outer_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
    }
    else if( mu8_color == RGB_COLOR_COLD )
    {
        gu8_rgb_r_test_ice_outer_extract = 0;
        gu8_rgb_g_test_ice_outer_extract = 40;
        gu8_rgb_b_test_ice_outer_extract = 60;

        gu8_rgb_ice_outer_red_on_time = (U8)((U16)((U16)gu8_rgb_r_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_outer_green_on_time = (U8)((U16)((U16)gu8_rgb_g_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
        gu8_rgb_ice_outer_blue_on_time = (U8)((U16)((U16)gu8_rgb_b_test_ice_outer_extract * gu8_rgb_pwm_period) / 100);
    }
    else
    {
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 0;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void recipe_led_output(void)
{
    /* ��ħ��� ���� ���¸� ��� OFF */
    if(bit_display_sleep_start == SET)
    {
        Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
        Bit1_Front_Center_Tea_Text = CLEAR;
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
        Bit3_Front_Center_MY_1_Text = CLEAR;
        Bit4_Front_Center_MY_2_Text = CLEAR;
        Bit5_Front_Center_MY_3_Text = CLEAR;
        return;
    }
    else {  }

    if(bit_myWater_setting_start == CLEAR)
    {
        Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
        Bit1_Front_Center_Tea_Text = CLEAR;
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
        Bit3_Front_Center_MY_1_Text = CLEAR;
        Bit4_Front_Center_MY_2_Text = CLEAR;
        Bit5_Front_Center_MY_3_Text = CLEAR;
    }
    else
    {
        if(F_WaterOut == SET)
        {
            switch (my_recipe_select)
            {
                case RECIPE_RAMEN:
                    Bit0_Front_Center_Recipe_Ramen_Text = SET;
                    Bit1_Front_Center_Tea_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                    Bit3_Front_Center_MY_1_Text = CLEAR;
                    Bit4_Front_Center_MY_2_Text = CLEAR;
                    Bit5_Front_Center_MY_3_Text = CLEAR;

                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, receipe_led_percent );
                    break;

                case RECIPE_DRIPCOFFEE:
                    Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
                    Bit1_Front_Center_Tea_Text = CLEAR;
                    Bit3_Front_Center_MY_1_Text = CLEAR;
                    Bit4_Front_Center_MY_2_Text = CLEAR;
                    Bit5_Front_Center_MY_3_Text = CLEAR;

                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, receipe_led_dripcoffee_percent );
                    break;

                case RECIPE_TEA:
                    Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                    Bit1_Front_Center_Tea_Text = SET;
                    Bit3_Front_Center_MY_1_Text = CLEAR;
                    Bit4_Front_Center_MY_2_Text = CLEAR;
                    Bit5_Front_Center_MY_3_Text = CLEAR;

                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, receipe_led_percent );
                    break;

                case RECIPE_MY1:
                    Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                    Bit1_Front_Center_Tea_Text = CLEAR;
                    Bit3_Front_Center_MY_1_Text = SET;
                    Bit4_Front_Center_MY_2_Text = CLEAR;
                    Bit5_Front_Center_MY_3_Text = CLEAR;
                    
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, receipe_led_percent );
                    break;

                case RECIPE_MY2:
                    Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                    Bit1_Front_Center_Tea_Text = CLEAR;
                    Bit3_Front_Center_MY_1_Text = CLEAR;
                    Bit4_Front_Center_MY_2_Text = SET;
                    Bit5_Front_Center_MY_3_Text = CLEAR;
                    
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, receipe_led_percent );
                    break;

                case RECIPE_MY3:
                    Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                    Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                    Bit1_Front_Center_Tea_Text = CLEAR;
                    Bit3_Front_Center_MY_1_Text = CLEAR;
                    Bit4_Front_Center_MY_2_Text = CLEAR;
                    Bit5_Front_Center_MY_3_Text = SET;
                    
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, receipe_led_percent );
                    break;

                default:
                    gu8_front_center_recipe_led = CLEAR;
                    break;
            }
        }
        else
        {            
            Bit0_Front_Center_Recipe_Ramen_Text = SET;
            Bit1_Front_Center_Tea_Text = SET;
            Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;

            if(my_setting[MY_INDEX_MY1].use == SET)
            {
                Bit3_Front_Center_MY_1_Text = SET;
            }
            else
            {
                Bit3_Front_Center_MY_1_Text = CLEAR;
            }

            if(my_setting[MY_INDEX_MY2].use == SET)
            {
                Bit4_Front_Center_MY_2_Text = SET;
            }
            else
            {
                Bit4_Front_Center_MY_2_Text = CLEAR;
            }

            if(my_setting[MY_INDEX_MY3].use == SET)
            {
                Bit5_Front_Center_MY_3_Text = SET;
            }
            else
            {
                Bit5_Front_Center_MY_3_Text = CLEAR;
            }

            switch (my_recipe_select)
            {
                case RECIPE_RAMEN:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, receipe_led_percent );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, DIIMMING__20_PERCENT );
                    break;

                case RECIPE_DRIPCOFFEE:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, receipe_led_dripcoffee_percent );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, DIIMMING__20_PERCENT );
                    break;

                case RECIPE_TEA:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, receipe_led_percent );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, DIIMMING__20_PERCENT );
                    break;

                case RECIPE_MY1:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, receipe_led_percent );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, DIIMMING__20_PERCENT );
                    break;

                case RECIPE_MY2:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, receipe_led_percent );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, DIIMMING__20_PERCENT );
                    break;

                case RECIPE_MY3:
                    set_duty_percent( DIMMING__PERCENT_RAMEN_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_DRIP_COFFEE_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_TEA_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_1_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_2_TEXT, DIIMMING__20_PERCENT );
                    set_duty_percent( DIMMING__PERCENT_MY_3_TEXT, receipe_led_percent );
                    break;

                default:
                    gu8_front_center_recipe_led = CLEAR;
                    break;
            }
        }

        Bit6_Front_Led_My_Select = SET;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void welcome_led_output(void)
{
    if( gu8_Led_Display_Step == LED_Display__VERSION )
    {
        gu16_welcome_timer = WELCOME_LED_ON_TIME;
        bit_welcome_start = CLEAR;
        bit_welcome_wifi_start = CLEAR;
        bit_welcome_on_flag = CLEAR;
        return;
    }
    else {  }

    /* ���� LED ��� ���� */
    if( F_Welcome_Led_OnOff == CLEAR )
    {
        Bit5_Front_Under_Led_Welcome = CLEAR;
        Bit6_Front_Under_Led_Welcome_2 = CLEAR;

        bit_welcome_start = CLEAR;
        bit_welcome_wifi_start = CLEAR;
        gu16_welcome_timer = WELCOME_LED_ON_TIME;
        bit_welcome_on_flag = CLEAR;
        return;
    }
    else{}
	
    if( bit_welcome_start == SET )
    {
        bit_welcome_start = CLEAR;
        
        bit_welcome_on_flag = SET;
        gu16_welcome_timer = WELCOME_LED_ON_TIME;

        Bit5_Front_Under_Led_Welcome = SET;
        Bit6_Front_Under_Led_Welcome_2 = SET;
    }
    else if(bit_welcome_wifi_start == SET)
    {
        /* �������� ������� WELCOME ��� ���� �� 7�� ON */
        bit_welcome_wifi_start = CLEAR;
        
        bit_welcome_on_flag = SET;
        gu16_welcome_timer = WELCOME_LED_WIFI_ON_TIME;

        Bit5_Front_Under_Led_Welcome = SET;
        Bit6_Front_Under_Led_Welcome_2 = SET;
    }
    else
    {
        if( bit_welcome_on_flag == SET )
        {
            if(( F_WaterOut == SET )
            || (F_IceOut == SET)
            )
            {
                gu16_welcome_timer = WELCOME_LED_ON_TIME;
            }
            else
            {
                /* count up->down ������� ���� */
                if(gu16_welcome_timer > 0)
                {
                    gu16_welcome_timer--;
                }
                else { /* nothing */ }
            }

            if(gu16_welcome_timer == CLEAR)     /* ���� �̻�� �� 1�� ��� �� ON */
            {
                gu16_welcome_timer = WELCOME_LED_ON_TIME;

                Bit5_Front_Under_Led_Welcome = CLEAR;
                Bit6_Front_Under_Led_Welcome_2 = CLEAR;
                bit_welcome_on_flag = CLEAR;
            }
            else
            {
                if((gu8_Led_Display_Step == LED_Display__WATER_EXTRACT)
                || (gu8_Led_Display_Step == LED_Display__ICE_EXTRACT)
                )
                {
                    if( F_WaterOut == SET )
                    {
                        Bit5_Front_Under_Led_Welcome = SET;
                    }
                    else
                    {
                        Bit5_Front_Under_Led_Welcome = CLEAR;
                    }

                    if(F_IceOut == SET)
                    {
                        Bit6_Front_Under_Led_Welcome_2 = SET;
                    }
                    else
                    {
                        Bit6_Front_Under_Led_Welcome_2 = CLEAR;
                    }
                }
                else if(gu8_Led_Display_Step == LED_Display__ICE_WATER_EXTRACT)
                {
                    Bit5_Front_Under_Led_Welcome = CLEAR;
                    Bit6_Front_Under_Led_Welcome_2 = SET;
                }
                else if(gu8_Led_Display_Step == LED_Display__MY_WATER_EXTRACT)
                {
                    Bit5_Front_Under_Led_Welcome = SET;
                    Bit6_Front_Under_Led_Welcome_2 = CLEAR;
                }
                else
                {
                    Bit5_Front_Under_Led_Welcome = SET;
                    Bit6_Front_Under_Led_Welcome_2 = SET;
                }
            }
        }
        else
        {
            gu16_welcome_timer = WELCOME_LED_ON_TIME;
            bit_welcome_on_flag = CLEAR;
            Bit5_Front_Under_Led_Welcome = CLEAR;
            Bit6_Front_Under_Led_Welcome_2 = CLEAR;
        }
    }

    set_duty_percent( DIMMING__PERCENT_WELCOME_LED, welcome_right_led_percent );
    set_duty_percent( DIMMING__PERCENT_WELCOME_LED_2, welcome_left_led_percent );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_level_extract_out(void)
{
    Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
    Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
    Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
    Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
    Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;

    // set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_1, DIIMMING__10_PERCENT );
    // set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_2, DIIMMING__10_PERCENT );
    // set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_3, DIIMMING__10_PERCENT );
    // set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_2_4, DIIMMING__10_PERCENT );
    // set_duty_percent( DIMMING__PERCENT_AMOUNT_BAR_CONTINUE, DIIMMING__10_PERCENT );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_button_set(void)
{
    funcition_led_output();
    /*level_led_output();*/
    setting_led_output();
    extract_led_output();
    /*recipe_led_output();*/

    /*icon_led_output();*/
    under_text_led_output();
    under_icon_led_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_filter_open_state(void)
{
    /*extract_led_output();*/
    
    Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
    
    Bit3_Front_Under_Ice_Outer_White_Extract = SET;
    Bit4_Front_Under_Water_White_Extract = SET;
    
    make_rgb_color( RGB_OFF );
    make_ice_outer_rgb_color(RGB_OFF);
    make_ice_inner_rgb_color(RGB_OFF);

    set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, ice_extract_outer_led_percent );
    set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, ice_extract_inner_led_percent );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �����巹�� ����� ǥ��
***********************************************************************************************************************/
void led_manual_drain_state(void)
{
    /*extract_led_output();*/
    Bit4_Front_Under_Water_White_Extract ^= SET;
    Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
    Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
    Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
    Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    make_rgb_color( RGB_OFF );

    set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, water_extract_led_percent );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_all_lock(void)
{
    all_lock_setting_led();
    
    /* ��ü��� �� RGB�� ���ߵ� */
    make_rgb_color( RGB_OFF );
    make_ice_outer_rgb_color(RGB_OFF);
    make_ice_inner_rgb_color(RGB_OFF);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void all_lock_setting_led(void)
{
    U8 mu8_all_lock_flick_state = 0;

    if( Bit4_All_Lock_Indicator == CLEAR )
    {
        Bit1_Front_Led_All_Lock = SET;
    }
    else
    {
        mu8_all_lock_flick_state = all_lock_flickering_timer(3, 5);

        if( mu8_all_lock_flick_state == SET )
        {
            Bit1_Front_Led_All_Lock = SET;
        }
        else
        {
            Bit1_Front_Led_All_Lock = CLEAR;
        }
    }

    set_duty_percent( DIMMING__PERCENT_SETTING_ALL_LOCK, setting_led_side_percent );
}

/**
 * @brief �ÿ��� ������ ���� ICON ǥ��
 * 
 */
void led_water_extract_state(void)
{
    if(F_All_Lock == SET)
	{
		fnd_left_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);
		fnd_right_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);

        gu8_front_left_led = 0;
        gu8_front_left_led_2 = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        gu8_front_center_recipe_led = 0;

        gu8_front_select_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_setting_led_2 = 0x02;
        gu8_front_under_text_led = 0;
        gu8_front_under_icon_led = 0;
        
		all_duty_100_percent();
	}
	else
	{
		funcition_led_output();
		setting_led_output();
		extract_led_output();
		recipe_led_output();


		level_led_output();

        left_icon_led_output();		// ['C], [���], [:], [�ܰ�]
        right_icon_led_output();	// [WIFI], [����], [DOT], [ml], [L]
        under_text_led_output();	// [�������], [�ü�����], [�Ϲ�/����], [�ü�OFF]
        under_icon_led_output();	// [COMP LED], [�ڹ���]
	}
}

/**
 * @brief ���� ������ ���� ICON ǥ��
 * 
 */
void led_ice_extract_state(void)
{
    if(F_All_Lock == SET)
	{
		fnd_left_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);
		fnd_right_out( FIXED_DISPLAY, DISPLAY_OFF, DISPLAY_OFF, DISPLAY_OFF);

        gu8_front_left_led = 0;
        gu8_front_left_led_2 = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        gu8_front_center_recipe_led = 0;

        gu8_front_select_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_setting_led_2 = 0x02;
        gu8_front_under_text_led = 0;
        gu8_front_under_icon_led = 0;
        
		all_duty_100_percent();
	}
	else
	{
		funcition_led_output();
		setting_led_output();
		extract_led_output();
		recipe_led_output();

		level_led_output();

		left_icon_led_output();		// ['C], [���], [:], [�ܰ�]
        right_icon_led_output();	// [WIFI], [����], [DOT], [ml], [L]
        under_text_led_output();	// [�������], [�ü�����], [�Ϲ�/����], [�ü�OFF]
        under_icon_led_output();	// [COMP LED], [�ڹ���]
	}
}