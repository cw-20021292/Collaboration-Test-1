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
#include    "m_wifi_smart_control.h"
#include    "WIFI_Status.h"

void wifi_smart_control(void);
void get_wifi_info_data(void);
void get_wifi_connect(void);
void get_wifi_pairing(void);
void get_wifi_error(void);
void get_wifi_power(void);
U8 change_error_number( U8 mu8_error );
/////void get_wifi_filter_period(void);
/////void change_filter_period(void);
void get_wifi_cert(void);
void get_smart_image(void);
U8 decision_day_or_night(void);
void get_server_connect(void);





U8 gu8_wifi_weather;
U8 gu8_wifi_aqi;

S8 gs8_signed_wifi_temperature;
U8 gu8_unsigned_wifi_temperature;

U8 gu8_wifi_temperature;


U8 gu8_Wifi_Connect_State;

U8 gu8_Wifi_Pairing_State;
U8 gu8_Wifi_Pairing_Error;
U8 gu8_Wifi_Last_Error;


U8 gu8_smart_image;
U8 gu8_smart_text;

U8 gu8_ap_mode;

U8 gu8_smart_standby_mode;

U8 gu8_custom_cup_setting;


U8 gu8_wifi_power_temporary;
U8 gu8_wifi_ap_first_temporary;

U8 gu8_wifi_ap_mode;
U8 gu8_ble_ap_mode;

U8 gu8_wifi_disp_timer;

U16 gu16_wifi_pairing_30min_timer;
U8 gu8_wifi_pairing_5sec_timer;
bit bit_pairing_5s_display_start;

U8 gu8_fota_start;


U8 gu8_wifi_filter_cycle_percent;
bit bit_filter_cycle_change;

U16 gu16_define_filter_period__neo;
U16 gu16_define_filter_period__ro;
U16 gu16_define_filter_period__ino;

U16 gu16_test_cycle;

U8 gu8_Wifi_Cert_State;

bit bit_wifi_pairing_start;
bit bit_display_last_error;

U8 gu8_Server_Connect_State;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_smart_control(void)
{
    get_wifi_connect();
    get_wifi_pairing();
    get_wifi_error();
    get_wifi_power();

    /////get_wifi_filter_period();
    get_wifi_info_data();
    get_smart_image();

    get_server_connect();
    get_wifi_cert();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_info_data(void)
{
    U8 mu8_connect_state = 0;
    U8 mu8_data = 0;
    S8 ms8_temp = 0;
    U8 mu8_temp = 0;
    U8 mu8_aqi = 0;

    mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_WEATHER );

    /*if( mu8_data >= WEATHER_SUNNY && mu8_data <= WEATHER_FOG )*/
    if( mu8_data >= SMART_WEATHER_MIN && mu8_data <= SMART_WEATHER_MAX )
    {
        gu8_wifi_weather = mu8_data;
    }
    else{}

    mu8_aqi  = (U8)GetWifiRequestValue( WIFI_RQST_AQI );

    if( mu8_aqi >= AQI_GOOD && mu8_aqi <= AQI_VERY_BAD )
    {
        gu8_wifi_aqi = mu8_data;
    }
    else{}

    /*..hui [21-3-12���� 2:49:14] ���̿��� ���� �̻� �� ����, �̼�����, �ð� �� 0xFF�� ���� - ����..*/
    /*..hui [21-3-12���� 2:49:45] �µ��� 0xff�� ������ ���ԵǹǷ� aqi ������ ���� �̻� Ȯ�� �� ����..*/
    /*..hui [21-3-12���� 2:51:29] ���̿��� ���� ����ÿ��� ���� �� ǥ�� ����..*/
    /*if( mu8_data != 0xff )*/

    #if 0
    /*..hui [21-3-24���� 3:33:20] AQI ������ ���͸�..*/
    if( mu8_aqi != 99 )
    {
        /*..hui [24-6-27���� 1:33:46] ����µ�..*/
        mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_CURRENT_TEMP );

        /*..hui [21-3-24���� 3:33:25] �µ������� �ѹ� �� ���͸�..*/
        if( mu8_data != 99 )
        {
            gu8_unsigned_wifi_current_temperature = mu8_data;

            if( gu8_unsigned_wifi_current_temperature >= 128 )
            {
                if( gu8_unsigned_wifi_current_temperature <= MIN_TEMPATURE )
                {
                    gu8_wifi_current_temperature = MIN_TEMPATURE;
                }
                else
                {
                    gu8_wifi_current_temperature = gu8_unsigned_wifi_current_temperature;
                }
            }
            else
            {
                if( gu8_unsigned_wifi_current_temperature >= MAX_TEMPERATURE )
                {
                    gu8_wifi_current_temperature = MAX_TEMPERATURE;
                }
                else
                {
                    gu8_wifi_current_temperature = gu8_unsigned_wifi_current_temperature;
                }
            }
        }
        else{}
    }
    else{}

    if( mu8_aqi != 99 )
    {
        /*..hui [24-6-27���� 1:33:50] �����µ�..*/
        mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_LOW_TEMP );

        /*..hui [21-3-24���� 3:33:25] �µ������� �ѹ� �� ���͸�..*/
        if( mu8_data != 99 )
        {
            gu8_unsigned_wifi_low_temperature = mu8_data;

            if( gu8_unsigned_wifi_low_temperature >= 128 )
            {
                if( gu8_unsigned_wifi_low_temperature <= MIN_TEMPATURE )
                {
                    gu8_wifi_low_temperature = MIN_TEMPATURE;
                }
                else
                {
                    gu8_wifi_low_temperature = gu8_unsigned_wifi_low_temperature;
                }
            }
            else
            {
                if( gu8_unsigned_wifi_low_temperature >= MAX_TEMPERATURE )
                {
                    gu8_wifi_low_temperature = MAX_TEMPERATURE;
                }
                else
                {
                    gu8_wifi_low_temperature = gu8_unsigned_wifi_low_temperature;
                }
            }
        }
        else{}
    }
    else{}

    if( mu8_aqi != 99 )
    {
        /*..hui [24-6-27���� 1:33:55] �ְ�µ�..*/
        mu8_data = (U8)GetWifiRequestValue( WIFI_RQST_HIGH_TEMP );

        /*..hui [21-3-24���� 3:33:25] �µ������� �ѹ� �� ���͸�..*/
        if( mu8_data != 99 )
        {
            gu8_unsigned_wifi_high_temperature = mu8_data;

            if( gu8_unsigned_wifi_high_temperature >= 128 )
            {
                if( gu8_unsigned_wifi_high_temperature <= MIN_TEMPATURE )
                {
                    gu8_wifi_high_temperature = MIN_TEMPATURE;
                }
                else
                {
                    gu8_wifi_high_temperature = gu8_unsigned_wifi_high_temperature;
                }
            }
            else
            {
                if( gu8_unsigned_wifi_high_temperature >= MAX_TEMPERATURE )
                {
                    gu8_wifi_high_temperature = MAX_TEMPERATURE;
                }
                else
                {
                    gu8_wifi_high_temperature = gu8_unsigned_wifi_high_temperature;
                }
            }
        }
        else{}
    }
    else{}
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_connect(void)
{
    U8 mu8_connect_state = 0;

    mu8_connect_state = GetWifiStatusValue( WIFI_STATUS_DISP );
    // mu8_connect_state = GetWifiStatusValue( WIFI_STATUS_SERVER_CON );

    if( mu8_connect_state == WIFI_DISP_OFF )
    {
        gu8_Wifi_Connect_State = WIFI_OFF;
    }
    else if( mu8_connect_state == WIFI_DISP_CONNECT )
    {
        gu8_Wifi_Connect_State = WIFI_CONNECT;
    }
    else
    {
        gu8_Wifi_Connect_State = WIFI_DISCONNECT;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_pairing(void)
{
    U8 mu8_pairing_state = 0;

    mu8_pairing_state = GetWifiStatusValue( WIFI_STATUS_DISP );

    gu8_wifi_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_MODE );
    gu8_ble_ap_mode  = GetWifiStatusValue( WIFI_STATUS_AP_BLE );

    // if( gu8_Wifi_Connect_State == WIFI_CONNECT )
    // {
    //     gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP_FINISH;
    //     return;
    // }
    // else{}

    if( gu8_wifi_ap_mode == SET )
    {
        if( mu8_pairing_state == WIFI_DISP_AP_START )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP0 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP0_PREPARE;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP1 )
        {
            /*..hui [23-12-20���� 1:22:03] ���������Ǹ� STEP1�� �����.. �׶����� 25%�� ȭ�� ǥ�� ����..*/
            if( gu8_Wifi_Pairing_State != WIFI_PAIRING_STEP1_25_PERCENT )
            {
                gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP1_25_PERCENT;

                if( gu8_Wifi_Pairing_Error == 0 )
                {
                    bit_wifi_pairing_start = SET;
                    bit_display_last_error = CLEAR;
                }
                else{}
            }
            else{}

        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP2 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP2_50_PERCENT;
        }
        else if( mu8_pairing_state == WIFI_DISP_AP_STEP3 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP3_75_PERCENT;
        }
        else
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
    }
    else if( gu8_ble_ap_mode == SET )
    {
        if( mu8_pairing_state == WIFI_DISP_BLE_START )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP0 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP0_PREPARE;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP1 )
        {
            /*..hui [23-12-20���� 1:22:03] ���������Ǹ� STEP1�� �����.. �׶����� 25%�� ȭ�� ǥ�� ����..*/
            if( gu8_Wifi_Pairing_State != WIFI_PAIRING_STEP1_25_PERCENT )
            {
                gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP1_25_PERCENT;

                if( gu8_Wifi_Pairing_Error == 0 )
                {
                    bit_wifi_pairing_start = SET;
                    bit_display_last_error = CLEAR;
                }
                else{}
            }
            else{}
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP2 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP2_50_PERCENT;
        }
        else if( mu8_pairing_state == WIFI_DISP_BLE_STEP3 )
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STEP3_75_PERCENT;
        }
        else
        {
            gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        }
    }
    else
    {
        gu8_Wifi_Pairing_State = WIFI_PAIRING_STANDBY;
        bit_wifi_pairing_start = CLEAR;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_error(void)
{
    U8 mu8_error = 0;

    mu8_error = GetWifiStatusValue(WIFI_STATUS_AP_ERROR);

    gu8_Wifi_Pairing_Error = change_error_number( mu8_error );


    mu8_error = GetWifiStatusValue(WIFI_STATUS_ERROR);

    gu8_Wifi_Last_Error = change_error_number( mu8_error );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_power(void)
{
    /*..hui [21-8-2���� 8:23:11] ���� ���� �� ù �� ����..*/
    /*..hui [21-8-2���� 8:23:24] �������� ������ �ʿ��� ������ ��������..*/
    gu8_wifi_power_temporary = GetWifiStatusValue(WIFI_STATUS_POWER);

    gu8_wifi_ap_first_temporary = GetWifiApStatus(STATUS_AP_FIRST);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 change_error_number( U8 mu8_error )
{
    U8 mu8_return = 0;

    if( mu8_error == WIFI_DISP_AP1 )
    {
        /*..hui [21-10-5���� 2:10:03] AP1 - ���������� ��ȣ����ġ..*/
        mu8_return = WIFI_FAIL_PASS__AP1;
    }
    else if( mu8_error == WIFI_DISP_AP2 )
    {
        /*..hui [21-10-5���� 2:10:13] AP2 - ���������� �̰˻� 1��..*/
        mu8_return = WIFI_NO_ACK__AP2;
    }
    else if( mu8_error == WIFI_DISP_AP3 )
    {
        /*..hui [21-10-5���� 2:10:25] AP3 - ���������� ���Ӱź�..*/
        mu8_return = WIFI_ERROR_DENY__AP3;
    }
    else if( mu8_error == WIFI_DISP_AP4 )
    {
        /*..hui [21-10-5���� 2:10:33] AP4 - ���������� �������..*/
        mu8_return = WIFI_NO_AP__AP4;
    }
    else if( mu8_error == WIFI_DISP_AP5 )
    {
        /*..hui [21-10-5���� 2:10:41] AP5 - ���� �������..*/
        mu8_return = WIFI_NO_SERVER__AP5;
    }
    else
    {
        mu8_return = 0;
    }

    return mu8_return;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void get_wifi_filter_period(void)
{
    U16 mu16_data = 0;
    U8 mu8_final = 0;

    /*..hui [21-3-9���� 1:01:08] �����������..*/
    if( gu8_Wifi_Connect_State != WIFI_CONNECT )
    {
        return;
    }
    else{}

    mu16_data = GetWifiRequestValue(WIFI_RQST_FILTER_CHANGE_CYCLE);
    /*mu16_data = gu16_test_cycle;*/

    if( mu16_data >= WIFI_FILTER_CHANGE_CYCLE_MIN && mu16_data <= WIFI_FILTER_CHANGE_CYCLE_MAX )
    {
        //gu8_wifi_filter_cycle_percent = (U8)mu16_data;
        if( gu8_wifi_filter_cycle_percent != (U8)mu16_data )
        {
            gu8_wifi_filter_cycle_percent = (U8)mu16_data;
            change_filter_period();

            bit_filter_cycle_change = SET;
        }
        else{}
    }
    else{}


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void change_filter_period(void)
{
    F32 mf32_month = 0;
    F32 mf32_day = 0;
    U16 mu16_a = 0;
    U16 mu16_final = 0;

    if( gu8_wifi_filter_cycle_percent < WIFI_FILTER_CHANGE_CYCLE_MIN || gu8_wifi_filter_cycle_percent > WIFI_FILTER_CHANGE_CYCLE_MAX )
    {
        gu16_define_filter_period__neo = FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__NEO;
        gu16_define_filter_period__ro = FILTER_RESET_DEFAULT_24_MONTH_912_DAY_HOUR__RO;
        gu16_define_filter_period__ino = FILTER_RESET_DEFAULT_12_MONTH_456_DAY_HOUR__INO;
    }
    else{}

    mf32_month = ((F32)(FILTER_RESET_DEFAULT_MONTH__NEO * (F32)gu8_wifi_filter_cycle_percent) / (F32)100);
    mu16_a = get_round( mf32_month );

    /*..hui [24-2-15���� 5:24:35] �ϼ��� ��ȯ..*/
    mf32_day = (F32)mu16_a * 30.4f;
    mf32_day = mf32_day * 24;
    mu16_final = get_round( mf32_day );

    // gu16_define_filter_period__neo = mu16_final * 24;
    gu16_define_filter_period__neo = mu16_final;
    // gu16_define_filter_period__ino = mu16_final * 24;
    gu16_define_filter_period__ino = mu16_final;

    mf32_month = ((F32)(FILTER_RESET_DEFAULT_MONTH__RO * (F32)gu8_wifi_filter_cycle_percent) / (F32)100);
    mu16_a = get_round( mf32_month );

    /*..hui [24-2-15���� 5:24:35] �ϼ��� ��ȯ..*/
    mf32_day = (F32)mu16_a * 30.4f;
    mf32_day = mf32_day * 24;
    mu16_final = get_round( mf32_day );

    // gu16_define_filter_period__ro = mu16_final * 24;
    gu16_define_filter_period__ro = mu16_final;

}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_wifi_cert(void)
{
    U8 mu8_connect_state = 0;

    gu8_Wifi_Cert_State = GetWifiStatusValue(WIFI_STATUS_BLE_CERT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_smart_image(void)
{
    U8 mu8_day = 0;

    /*..hui [21-3-8���� 6:59:16] �������� ���� �ȵ����� �������� ���� �ǰ� �̹���..*/
    if( gu8_Wifi_Connect_State == WIFI_OFF )
    {
        gu8_smart_image = SMART_ICON_NONE;
        return;
    }
    else if( gu8_Wifi_Connect_State == WIFI_DISCONNECT )
    {
        gu8_smart_image = SMART_ICON_NONE;
        return;
    }
    else{}

    /*mu8_day = decision_day_or_night();*/

    switch ( gu8_wifi_weather )
    {
        case WEATHER_SUNNY:
        case WEATHER_BIT_CLOUD:

            gu8_smart_image = SMART_ICON_SUNNY;

        break;

        case WEATHER_LOTS_CLOUD:
        case WEATHER_CLOUDY:
        case WEATHER_THUNDER:
        case WEATHER_FOG:
            gu8_smart_image = SMART_ICON_CLOUDY;
        break;

        case WEATHER_CLOUDY_AND_RAINY:
        case WEATHER_CLOUDY_AND_SNOWY:
        case WEATHER_SUNNY_AFTER_RAINY:
        case WEATHER_SHOWER:
        case WEATHER_RAINY_OR_SNOWY:
        case WEATHER_SNOWY_OR_RAINY:
            gu8_smart_image = SMART_ICON_RAINY;
        break;


        default:
            gu8_wifi_weather = SMART_ICON_NONE;
        break;
    }


    #if 0
    /*..hui [21-3-8���� 6:59:16] �������� ���� �ȵ����� �������� ���� �ǰ� �̹���..*/
    if( gu8_Wifi_Connect_State == WIFI_OFF )
    {
        gu8_smart_image = SMART_IMAGE_SUNNY;
        return;
    }
    else if( gu8_Wifi_Connect_State == WIFI_DISCONNECT )
    {
        gu8_smart_image = SMART_IMAGE_SUNNY;
        return;
    }
    else{}

    mu8_day = decision_day_or_night();

    switch ( gu8_wifi_weather )
    {
        case WEATHER_SUNNY:

            if( mu8_day == SMART_DAY )
            {
                /*..hui [21-3-8���� 6:55:48] ����(��ü�� ����)..*/
                /*..hui [24-8-19���� 1:50:13] ��..*/
                gu8_smart_image = SMART_IMAGE_SUNNY;
            }
            else
            {
                /*..hui [24-8-19���� 1:50:32] ��..*/
                gu8_smart_image = SMART_IMAGE_SUNNY_NIGHT;
            }

        break;

        case WEATHER_BIT_CLOUD:
        case WEATHER_LOTS_CLOUD:
        case WEATHER_CLOUDY:

            /*..hui [21-3-8���� 6:56:00] ��������/��������/�帲..*/
            gu8_smart_image = SMART_ICON_CLOUDY;

        break;

        case WEATHER_CLOUDY_AND_RAINY:

            /*..hui [21-3-8���� 6:56:05] �帮���..*/
            gu8_smart_image = SMART_ICON_RAINY;

        break;

        case WEATHER_CLOUDY_AND_SNOWY:

            /*..hui [21-3-8���� 6:56:26] �帮�� ��..*/
            gu8_smart_image = SMART_IMAGE_SNOWY;

        break;

        case WEATHER_SUNNY_AFTER_RAINY:

            if( mu8_day == SMART_DAY )
            {
                /*..hui [21-3-8���� 6:56:55] ��� �� ��..*/
                /*..hui [24-8-19���� 1:51:00] �帰�ڸ��� ��..*/
                gu8_smart_image = SMART_IMAGE_SUNNY_AFTER_RAINY;
            }
            else
            {
                /*..hui [24-8-19���� 1:51:40] �帰�ڸ��� ��..*/
                gu8_smart_image = SMART_IMAGE_SUNNY_AFTER_RAINY_NIGHT;
            }

        break;

        case WEATHER_SHOWER:

            /*..hui [21-3-8���� 6:56:15] �ҳ���..*/
            gu8_smart_image = SMART_IMAGE_SHOWER;

        break;

        case WEATHER_RAINY_OR_SNOWY:
        case WEATHER_SNOWY_OR_RAINY:

            /*..hui [21-3-8���� 6:56:36] �� �Ǵ� ��/�� �Ǵ� ��..*/
            gu8_smart_image = SMART_IMAGE_RAINY_OR_SNOWY;

        break;

        case WEATHER_THUNDER:

            /*..hui [21-3-8���� 6:56:45] õ�չ���..*/
            gu8_smart_image = SMART_IMAGE_THUNDER;

        break;

        case WEATHER_FOG:

            /*..hui [21-3-8���� 6:56:18] �Ȱ�..*/
            gu8_smart_image = SMART_IMAGE_FOG;

        break;

        default:

            gu8_wifi_weather = WEATHER_SUNNY;

        break;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 decision_day_or_night(void)
{
    U8 mu8_return = 0;

    /*..hui [21-3-8���� 6:57:55] ��ħ 5:00 ���� ~ ���� 17�� 59�� ���� ��..*/
    if( gu8_rtc_time_Hour >= 5 && gu8_rtc_time_Hour < 18  )
    {
        mu8_return = SMART_DAY;
    }
    else
    {
        mu8_return = SMART_NIGHT;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_server_connect(void)
{
    U8 mu8_connect_state = 0;

    mu8_connect_state = GetWifiStatusValue( WIFI_STATUS_SERVER_CON );

    if( mu8_connect_state == SERVER_CONNECT )
    {
        gu8_Server_Connect_State = SERVER_CONNECT;
    }
    else /*if( mu8_connect_state == SERVER_DISCONNECT )*/
    {
        gu8_Server_Connect_State = SERVER_DISCONNECT;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


