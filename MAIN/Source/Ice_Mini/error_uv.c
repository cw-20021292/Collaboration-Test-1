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
#include    "error_uv.h"

void check_error_uv(void);
void check_error_uv_water_extract(void);
void check_error_uv_ice_one_faucet(void);
void check_error_uv_ice_two_faucet(void);

void check_error_uv_ice_tank_one_two(void);
///void check_error_uv_ice_tank_front(void);
void check_error_uv_ice_tray(void);
void check_error_uv_led(UV_Check* targetUV);

/* PCH ZZANG */
UV_Check uvWaterFaucet;
UV_Check uvIceFaucet_1;
UV_Check uvIceFaucet_2;
UV_Check uvIceTray;
UV_Check uvIceTank_1_2;
UV_Check uvIceTank_3;

U16 gu16_water_uv_error_elasped_timer_hour;
U16 gu16_water_uv_error_elasped_timer_day;
U8 gu8_water_uv_error_elasped_day;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_uv(void)
{
    // /* ������ �Ŀ�� */
    // check_error_uv_water_extract();

    // /*..hui [24-4-3���� 7:53:59] ������ũ ���� UV 2��.. ���� �ִ��ſ� 1���߰�..*/
    // check_error_uv_ice_tank_one_two();

    // /*..hui [24-4-3���� 7:54:21] ���̽� Ʈ���� ���� 2��.. �и����ִ��� 2�� ��ħ..*/
    // check_error_uv_ice_tray();

    /* PCH ZZANG */
    check_error_uv_led(&uvWaterFaucet);
    check_error_uv_led(&uvIceFaucet_1);
    check_error_uv_led(&uvIceFaucet_2);
    check_error_uv_led(&uvIceTray);
    check_error_uv_led(&uvIceTank_1_2);
    check_error_uv_led(&uvIceTank_3);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : PCH ZZANG
***********************************************************************************************************************/
void check_error_uv_led(UV_Check* targetUV)
{
    U8 output_status = 0;
    U16 Result_Current_Feed = 0;

    if((targetUV) == (&uvWaterFaucet))
    {
        // �����Ŀ�� UV ����
        output_status = (U8)bit_uv_extract_faucet_out;
        Result_Current_Feed = gu16_AD_Result_UV_Water_Faucet_Current_Feed;
        Bit23_faucet_UV_Error__E77 = (bit)((*targetUV).gu8_Error_bit);
    }
    else if((targetUV) == (&uvIceFaucet_1))
    {
        // 
        output_status = (U8)bit_uv_ice_faucet_out;
        Result_Current_Feed = gu16_AD_Result_UV_Ice_Faucet_One_Current;
        Bit25_Ice_Faucet_UV_2_Error__E78 = (bit)((*targetUV).gu8_Error_bit);
    }
    else if((targetUV) == (&uvIceFaucet_2))
    {
        output_status = (U8)bit_uv_ice_faucet_out;
        Result_Current_Feed = gu16_AD_Result_UV_Ice_Faucet_Two_Current;
        Bit25_Ice_Faucet_UV_2_Error__E78 = (bit)((*targetUV).gu8_Error_bit);
    }
    else if((targetUV) == (&uvIceTray))
    {
        output_status = (U8)bit_uv_ice_tray_out;
        Result_Current_Feed = gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;
        Bit27_Ice_Tray_1_2_UV_Error__E76 = (bit)((*targetUV).gu8_Error_bit);
    }
    else if((targetUV) == (&uvIceTank_1_2))
    {
        output_status = (U8)bit_uv_ice_tank_out;
        Result_Current_Feed = gu16_AD_Result_UV_Ice_Tank_1_2_Current;
        Bit24_Ice_Tank_UV_Error__E75 = (bit)((*targetUV).gu8_Error_bit);
    }
    else if((targetUV) == (&uvIceTank_3))
    {
        output_status = (U8)bit_uv_ice_tank_out;
        Result_Current_Feed = gu16_AD_Result_UV_Ice_Tank_3_Current_Feed;
        Bit24_Ice_Tank_UV_Error__E75 = (bit)((*targetUV).gu8_Error_bit);
    }

    if( output_status == SET && (*targetUV).gu8_uv_retry_stop_flag == CLEAR )
    {
        /*..hui [24-4-4���� 3:05:58] �ü���ũ UV 2�� ����..*/
        if( Result_Current_Feed >= UV_COUPLE__ERROR_CHECT_OVER_AD
        || Result_Current_Feed <= UV_COUPLE__ERROR_CHECK_UNDER_AD )
        {
            (*targetUV).gu8_error_clear_timer = 0;
            (*targetUV).gu8_error_check_timer++;

            if( (*targetUV).gu8_error_check_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                (*targetUV).gu8_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;

                (*targetUV).gu8_uv_retry_count++;

                if( (*targetUV).gu8_uv_retry_count >= UV_ERROR_RETRY_COUNT )
                {
                    (*targetUV).gu8_uv_retry_count = UV_ERROR_RETRY_COUNT;
                    (*targetUV).gu8_error_check_timer = UV_SENSOR_ERROR_CHECK_TIME;
                    (*targetUV).gu8_Error_bit = SET;
                }
                else
                {
                    (*targetUV).gu8_error_check_timer = 0;
                    (*targetUV).gu8_uv_retry_stop_flag = SET;
                }
            }
            else{}
        }
        else
        {
            (*targetUV).gu8_error_check_timer = 0;
            (*targetUV).gu8_error_clear_timer++;

            if ( (*targetUV).gu8_error_clear_timer >= UV_SENSOR_ERROR_CHECK_TIME )
            {
                (*targetUV).gu8_error_clear_timer = UV_SENSOR_ERROR_CHECK_TIME;
                (*targetUV).gu8_Error_bit = CLEAR;
                (*targetUV).gu8_uv_retry_count = 0;
                gu8_water_uv_error_elasped_day = 0;
            }
            else{}
        }
    }
    else
    {
        (*targetUV).gu8_error_clear_timer = 0;
        (*targetUV).gu8_error_check_timer = 0;

        /* 3�� �� RETRY */
        if((*targetUV).gu8_uv_retry_stop_flag == SET)
        {
            (*targetUV).gu8_uv_retry_timer++;
            if((*targetUV).gu8_uv_retry_timer >= 30)
            {
                (*targetUV).gu8_uv_retry_timer = 0;
                (*targetUV).gu8_uv_retry_stop_flag = CLEAR;
            }
            else {  }
        }
        else
        {
            (*targetUV).gu8_uv_retry_timer = 0;
            (*targetUV).gu8_uv_retry_count = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



