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
#include    "display_fnd_right_tray_clean.h"


void fnd_right_tray_clean(void);
void led_tray_clean(void);

U8 gu8_tray_clean_percent;

extern void hot_ster_text_out(void);
extern void percent_icon_out(void);
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void fnd_right_tray_clean(void)
{
    U8 mu8_temporary_thousand = 0;
    U8 mu8_temporary_hundred = 0;
    U8 mu8_temporary_ten = 0;
    U8 mu8_temporary_one = 0;
    U8 mu8_flick_state = 0;

    if( gu8_ice_ster_mode == STER_MODE_PREPARE )
    {
        if( gu8_prepare_ster_step <= 3 )
        {
            gu8_tray_clean_percent = 0;
        }
        else
        {
            gu8_tray_clean_percent = 10;
        }
    }
    else if( gu8_ice_ster_mode == STER_MODE_HOT_PREHEAT )
    {
        gu8_tray_clean_percent = 20;
    }
    else if( gu8_ice_ster_mode == STER_MODE_HOT_INPUT_STATE )
    {
        gu8_tray_clean_percent = 30;
    }
    else if( gu8_ice_ster_mode == STER_MODE_HOT_WAIT_STATE )
    {
        if( gu8_hot_wait_step == 0 )
        {
            gu8_tray_clean_percent = 40;
        }
        else if( gu8_hot_wait_step == 1 )
        {
            if( gu16_hot_wait_timer <= 450 )
            {
                gu8_tray_clean_percent = 40;
            }
            else if( gu16_hot_wait_timer <= 900 )
            {
                gu8_tray_clean_percent = 50;
            }
            else if( gu16_hot_wait_timer <= 1350 )
            {
                gu8_tray_clean_percent = 60;
            }
            else /*if( gu16_hot_wait_timer <= 1800 )*/
            {
                gu8_tray_clean_percent = 70;
            }
        }
        else
        {
            gu8_tray_clean_percent = 70;
        }

    }
    else /*if( gu8_ice_ster_mode == STER_MODE_FINISH )*/
    {
        if( gu8_wait_finish_step <= 2 )
        {
            gu8_tray_clean_percent = 80;
        }
        else if( gu8_wait_finish_step == 3 )
        {
            if( gu16_wait_finish_timer <= 600 )
            {
                gu8_tray_clean_percent = 80;
            }
            else
            {
                gu8_tray_clean_percent = 90;
            }
        }
        else
        {
            gu8_tray_clean_percent = 100;
        }
    }

    if( gu8_tray_clean_percent < 100 )
    {
        if( gu8_tray_clean_percent == 0 )
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = DISPLAY_OFF;
            mu8_temporary_one = DISPLAY_NUM_0;
        }
        else
        {
            mu8_temporary_hundred = DISPLAY_OFF;
            mu8_temporary_ten = (gu8_tray_clean_percent / 10);
            mu8_temporary_one = (gu8_tray_clean_percent % 10);
        }
    }
    else
    {
        mu8_temporary_hundred = DISPLAY_NUM_1;
        mu8_temporary_ten = DISPLAY_NUM_0;
        mu8_temporary_one = DISPLAY_NUM_0;
    }

    if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_HUNDRED, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_TEN, SLEEP_MODE_DIMMING_PERCENT );
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_ONE, SLEEP_MODE_DIMMING_PERCENT );
    }
    else
    {
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_HUNDRED, right_normal_state_percent );
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_TEN, right_normal_state_percent );
        set_duty_percent( DIMMING__PERCENT_SEG_RIGHT_ONE, right_normal_state_percent );
    }

    fnd_right_out( FIXED_DISPLAY, mu8_temporary_hundred, mu8_temporary_ten, mu8_temporary_one);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_tray_clean(void)
{
    #if 0
    /*funcition_led_output();*/
    setting_function_led();
    /*level_led_output();*/
    setting_led_output();
    /*extract_led_output();*/
    /*recipe_led_output();*/

    /*icon_led_output();*/
    ice_first_icon_out();
    sleep_icon_out();
    ice_size_text_out();
    cold_temp_text_out();
    ice_lock_icon_output();
    hot_lock_icon_output();
    #endif

    hot_ster_text_out();
    percent_icon_out();
    extract_led_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


