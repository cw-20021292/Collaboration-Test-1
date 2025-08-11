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
#include    "drain_operation.h"







void output_drain_pump(void);
void detect_no_water(void);
void drain_pump_output_decision(void);
void detect_drain_tank_high_level( void );

void keep_3_hour_check(void);
void ice_full_condition_check(void);
void detect_drain_pump_error(void);
U8 drain_pump_error_retry_proc( void );
void forced_drain_check(void);
void ice_off_check(void);
void ice_off_24hour_check(void);
void flushing_drain_check(void);

void first_drain_check(void);
void ice_make_drain_check(void);
void tray_ster_drain_check(void);
//////void acid_drain_check(void);

void detect_drain_tank_error_level( void );

void start_drain_pump( U16 u16_data );
void stop_drain_pump( void );
void drain_melt_water(void);






TYPE_WORD          U16DrainOperateB;
#define            u16DrainOperate                             U16DrainOperateB.word
#define            u8DrainOperate_L                            U16DrainOperateB.byte[0]
#define            Bit0_Drain_Level_Full                       U16DrainOperateB.Bit.b0      /* �巹����ũ ������ �� ���� */
#define            Bit1_Drain_Low_3_Hour                       U16DrainOperateB.Bit.b1      /* �߼��� 3�ð� �̻� ���� �� ���� */
#define            Bit2_Drain_Ice_Full                         U16DrainOperateB.Bit.b2      /* �������� ���� �� ���� */
#define            Bit3_Drain_Forced                           U16DrainOperateB.Bit.b3      /* ��,���������� ��ũĿ�� ������ ��  */
#define            Bit4_Drain_Flushing                         U16DrainOperateB.Bit.b4      /* �ü���ũ �÷��� �� */
#define            Bit5_Drain_Ice_Off                          U16DrainOperateB.Bit.b5      /* ����OFF �� (�߼��� �̻��� �� )*/
#define            Bit6_Drain_First                            U16DrainOperateB.Bit.b6      /* ù ���� �ΰ� �� (�߼����� ��) */
#define            Bit7_Drain_Ice_Making                       U16DrainOperateB.Bit.b7      /* ����-�ְ��� ���� �� (�߼����� ��) */
#define            Bit8_Drain_Tray_ster                        U16DrainOperateB.Bit.b8      /* Ʈ���� ��»�� ���� ���� �� */
#define            Bit9_Drain_Ice_Off_24_Hour                  U16DrainOperateB.Bit.b9      /* ����OFF�� ���� 24�ð� ���� (�߼��� �̻��� ��) */
// #define            Bit10_Drain_Level_Error                     U16DrainOperateB.Bit.b10

TYPE_BYTE          U8DrainPumpONB;
#define            u8DrainPumpON                        U8DrainPumpONB.byte
#define            Bit0_Drain_Tank_Level_Full_State     U8DrainPumpONB.Bit.b0
#define            Bit1_Drain_Error_Check_On_State      U8DrainPumpONB.Bit.b1
#define            Bit2_Drain_Melt_Ice_State            U8DrainPumpONB.Bit.b2
#define            Bit3_Drain_Tank_Flushing_State       U8DrainPumpONB.Bit.b3
#define            Bit4_Auto_drain_State                U8DrainPumpONB.Bit.b4
#define            Bit5_Manual_drain_State              U8DrainPumpONB.Bit.b5
#define            Bit6_Acid_Clean_State                U8DrainPumpONB.Bit.b6



TYPE_BYTE          U8DrainPumpOFFB;
#define            u8DrainPumpOFF                       U8DrainPumpOFFB.byte
#define            Bit0_Drain_Error_Check_Off_State     U8DrainPumpOFFB.Bit.b0
#define            Bit1_Drain_Error_Confirm_State       U8DrainPumpOFFB.Bit.b1
#define            Bit2_Bldc_Over_Current_Off_State     U8DrainPumpOFFB.Bit.b2
#define            Bit3_Hot_Filling_Drain_Off_State     U8DrainPumpOFFB.Bit.b3
#define            Bit4_Hot_Cooling_Drain_Off_State     U8DrainPumpOFFB.Bit.b4


U8 gu8drain_1s_time;


U16 gu16_drain_pump_first_op_timer;
U8 gu8_drain_pump_retry_step;

U16 gu16_drain_pump_1min_off_timer;
U16 gu16_drain_pump_2min_on_timer;

U16 gu16_drain_low_water_1min_tmr;
U16 gu16_drain_low_water_3hour_tmr;





bit F_Drain_Pump_Output;


U8 gu8_drain_err_10_count;

bit F_old_ice_full;
bit F_old_ice_on;

U16 gu16_ice_off_drain_timer;

//bit Bit2_Drain_Ice_Full;

bit bit_drain_err_check_on_state;
bit bit_drain_err_check_off_state;


bit bit_drain_error_check_enable;

U8 gu8_drain_pump_max_operation_count;



bit F_forced_drain_enable;

U8 gu8_forced_drain_add_timer;


bit F_Drain_Pump_Output;

U16 gu16_drain_pwm_out;


U16 gu16_drain_test_timer;
bit bit_first_drain;


U16 gu16_over_current_off_timer;
U16 gu16_over_current_detect_timer;

U16 gu16_drain_max_timer;
bit bit_drain_no_water_detect;
U8 gu8_drain_no_load_min_timer;

/*..hui [24-4-5���� 3:57:34] ������ ����, ������ �̰��� ��õ� Ƚ��..*/
U8 gu8_drain_error_retry_cnt;

U32 gu32_ice_off_24h_teimer;
bit bit_ice_off_24h_start;


U16 gu16_drain_level_error_timer;
U8 gu8_drain_no_water_detect_timer;
U8 gu8_drain_no_water_clear_timer;

bit bit_drain_level_error_detect;

U32 gu32_drain_melt_standby_timer;
bit bit_ice_melt_2_hour;
bit bit_drain_melt_pump_output;
U16 gu16_drain_melt_op_timer;
U8 gu8_drain_melt_cnt;
bit bit_drain_melt_finish;

U8 gu8_drain_error_clear_timer;

extern COLDTANK_FLUSHING_STEP gu8_cold_tank_flushing_step;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_drain_pump(void)
{
    #if 0
    ///�������� 179~187   / 159~162
    ///�������� 298~315   / 328~342
    /*..hui [23-11-13���� 3:08:52] bldc..*/
    /*..hui [23-7-7���� 2:31:45] �巹����ũ 350cc..*/
    /*..hui [23-7-7���� 2:31:54] �巹�� ���� 0.7lpm..*/
    /*..hui [23-7-7���� 2:32:10] ���� �������� ad 500..*/
    #endif

    #if 0
    /*..hui [23-11-13���� 3:09:07] �Ϲ� DC ����..*/
    /*..hui [23-11-13���� 3:09:13] �������� : 130~140..*/
    /*..hui [23-11-13���� 3:09:18] �������� : 200~..*/
    /*..hui [23-11-13���� 3:09:23] �� ������ : 65~79..*/
    /*..hui [24-3-28���� 7:02:04] ���� ����ġ.. ��������..773mv = 158..*/
    /*..hui [24-3-28���� 7:03:01] ���� ����ġ.. ��������.. 1.41V(70%) = 288, 2.26V(100%) = 462 ..*/
    /*..hui [24-3-28���� 7:03:31] ���� ����ġ.. �� ������.. 367mv ==75..*/
    #endif

    #if 0
    /*..hui [24-4-4���� 5:27:10] ȸ�� �ǵ�� ��� �����Ѱ�..*/
    /*..hui [24-4-4���� 5:25:34] ### 70% ###..*/
    /*..hui [24-4-4���� 5:25:39] �� ���� / ��� ���� === 240..*/
    /*..hui [24-4-4���� 5:25:49] �� ���� / ��� ���� === 420..*/
    /*..hui [24-4-4���� 5:25:53] �� ���� / ��� ���� === 120.. */
    /*..hui [24-4-4���� 5:26:01] �� ���� / ��� ���� === 230 ~ 300..*/
    /*..hui [24-4-4���� 5:26:07] ### 100% ###..*/
    /*..hui [24-4-4���� 5:26:12] �� ���� / ��� ���� === 390..*/
    /*..hui [24-4-4���� 5:26:17] �� ���� / ��� ���� === 790..*/
    /*..hui [24-4-4���� 5:26:23] �� ���� / ��� ���� === 120..*/
    /*..hui [24-4-4���� 5:26:28] �� ���� / ��� ���� === 230 ~ 300..*/
    /*..hui [24-4-4���� 5:26:34] ���� ���� : 170..*/
    /*..hui [24-4-4���� 5:26:43] ########### 12V �巹������ ������ ����� ��..*/
    #endif

    /*..hui [17-12-18���� 5:49:56] �巹������ ���� Ȯ��..*/
    detect_drain_pump_error();

    /*..hui [24-3-28���� 1:05:16] �巹�� ���� ���� �߻� �� ��ũ �� ���� ���� �� ���.. �� 30�ð� ����..*/
    drain_melt_water();

    /*..hui [17-12-18���� 5:50:02] ���� ��� ����..*/
    drain_pump_output_decision();


    if( u8DrainPumpOFF > 0 )
    {
        stop_drain_pump();  /*off*/
        gu8_drain_pump_max_operation_count = 0;
        F_Drain_Pump_Output = CLEAR;
        Bit6_Drain_Pump_FeedBack_12V_Out_State = CLEAR;
    }
    else
    {
        if( u8DrainPumpON > 0 )
        {
            /*..hui [18-1-30���� 3:11:35] ���� �ʹ� 3�ʵ��� max�� �����ϴٰ� �� 66%�� ����.. ..*/
            /*..hui [18-1-30���� 3:11:53] �ٸ����� 75%��� �������� �����δ� 66%��..*/
            gu8_drain_pump_max_operation_count++;
            if(gu8_drain_pump_max_operation_count >= DRAIN_PUMP_MAX_OP_TIME)
            {
                gu8_drain_pump_max_operation_count = DRAIN_PUMP_MAX_OP_TIME;

                /*..hui [18-7-19���� 1:31:20] ��õ� 10ȸ �� 2ȸ°���ʹ� Full duty�� �����Ѵ�...*/
                /*..hui [18-7-19���� 1:31:46] ��� �ȵǼ� ���� �߻��ϴ� �� ���� �������°� �� ����....*/
                if(gu8_drain_err_10_count >= DRAIN_PUMP_MAX_OUTPUT_ERROR_COUNT)
                {
                    start_drain_pump( PUMP_PWM_MAX ); /*on*/
                }
                else
                {
                    start_drain_pump( PUMP_PWM ); /*on*/
                }
            }
            else
            {
                start_drain_pump( PUMP_PWM_MAX ); /*on*/
            }

            F_Drain_Pump_Output = SET;
            /*..hui [24-4-4���� 5:30:42] �����̰� ȸ�� �����ϸ鼭 �巹������ �Ӷ� 12V �������..*/
            /*..hui [24-4-4���� 5:30:58] ���� �ǵ�� ���� �����ϸ鼭 5V -> 12V�� �ٲ�..*/
            Bit6_Drain_Pump_FeedBack_12V_Out_State = SET;
        }
        else
        {
            stop_drain_pump(); /*off*/
            gu8_drain_pump_max_operation_count = 0;
            F_Drain_Pump_Output = CLEAR;
            Bit6_Drain_Pump_FeedBack_12V_Out_State = CLEAR;
        }
    }

    detect_no_water();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_no_water(void)
{
    /*..hui [24-4-1���� 5:17:02] �巹�� ���� �������϶��� Ȯ��..*/
    if( F_Drain_Pump_Output == SET )
    {
        gu8_drain_no_load_min_timer++;

        if( gu8_drain_no_load_min_timer >= 100 )
        {
            /*..hui [24-4-1���� 7:09:11] �����ϰ� 10�� �ĺ��� üũ.. AD ����ȭ �ð�..*/
            gu8_drain_no_load_min_timer = 100;

            /*..hui [24-3-28���� 7:21:27] �ֽ� �ð� ���� ���� ���� AD�� �� ���� �� ������ ��� ���� ����..*/
            if( gu16_AD_Drain_Pump_Current <= DRAIN_NO_WATER_FEEDBACK_AD )
            {
                gu8_drain_no_water_clear_timer = 0;
                gu8_drain_no_water_detect_timer++;

                /*if( gu8_drain_no_water_detect_timer >= 50 )*/
                if( gu8_drain_no_water_detect_timer >= 100 )
                {
                    gu8_drain_no_water_detect_timer = 100;
                    bit_drain_no_water_detect = SET;
                }
                else{}
            }
            else
            {
                gu8_drain_no_water_detect_timer = 0;
                gu8_drain_no_water_clear_timer++;

                if( gu8_drain_no_water_clear_timer >= 100 )
                {
                    gu8_drain_no_water_clear_timer = 100;
                    bit_drain_no_water_detect = CLEAR;
                }
                else{}
            }
        }
        else
        {
            gu8_drain_no_water_detect_timer = 0;
            gu8_drain_no_water_clear_timer = 0;
        }
    }
    else
    {
        gu8_drain_no_water_detect_timer = 0;
        gu8_drain_no_water_clear_timer = 0;
        gu8_drain_no_load_min_timer = 0;
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_pump_output_decision(void)
{
/***************************************************************************************************/

    /*..hui [18-1-14���� 8:57:59] ��ȯ��� ��� �������϶��� ����üũ ����..*/
    /*Bit1_Drain_Error_Check_On_State = bit_drain_err_check_on_state & ~F_DrainStatus & ~bit_manual_drain_start;*/
    /*..hui [24-3-28���� 10:51:41] ��ȯ���, �޴��� �巹���� ����üũ�ϴ� ������ �ѹ� �Ÿ��⶧���� ..*/
    Bit1_Drain_Error_Check_On_State = bit_drain_err_check_on_state;

    /*..hui [24-3-28���� 10:51:56] ��ȯ��� ���� �� �巹������ ����..*/
    Bit4_Auto_drain_State = bit_auto_drain_pump_out;

    /*..hui [23-8-14���� 1:16:49] ������� ��� �߰�..*/
    if( bit_manual_drain_start == SET )
    {
        Bit5_Manual_drain_State = bit_manual_drain_pump_output;
    }
    else
    {
        Bit5_Manual_drain_State = CLEAR;
    }

    /*..hui [24-3-28���� 10:58:58] �巹�� ���� �߻��ϰ��� ���� ������ ���� ���..*/
    Bit2_Drain_Melt_Ice_State = bit_drain_melt_pump_output;

    #if 0
    /*..hui [24-5-24���� 5:57:19] ��ũ �÷����߿��� ���� ����..*/
    if( gu8_flushing_mode == FLUSHING_TANK_STATE && bit_flushing_tank_start == SET && gu8_flushing_tank_step == 10 )
    {
        Bit3_Drain_Tank_Flushing_State = bit_tank_drain_pump_output;
    }
    else if( bit_acid_clean_start == SET && gu8_acid_clean_step == 9 )
    {
        Bit3_Drain_Tank_Flushing_State = bit_tank_drain_pump_output;
    }
    else if( bit_acid_clean_start == SET && gu8_acid_clean_step >= 23 && gu8_acid_clean_step <= 25 )
    {
        Bit3_Drain_Tank_Flushing_State = bit_tank_drain_pump_output;
    }
    else if( bit_acid_clean_start == SET && gu8_acid_clean_step == 33 )
    {
        Bit3_Drain_Tank_Flushing_State = bit_tank_drain_pump_output;
    }
    else
    {
        Bit3_Drain_Tank_Flushing_State = CLEAR;
    }
    #endif

    /*..hui [24-5-24���� 5:57:19] ��ũ �÷����߿��� ���� ����..*/
		/*
    if( gu8_flushing_mode == FLUSHING_TANK_STATE && bit_flushing_tank_start == SET && gu8_flushing_tank_step == 10 )
    {
        Bit3_Drain_Tank_Flushing_State = bit_tank_drain_pump_output;
    }
    else
    {
        Bit3_Drain_Tank_Flushing_State = CLEAR;
    }
*/

    if(gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE)
    {
        if(gu8_cold_tank_fill_step == COLD_TANK_FILL_DRAIN)
        {
            Bit3_Drain_Tank_Flushing_State = SET;
        }
        else
        {
            Bit3_Drain_Tank_Flushing_State = CLEAR;
        }
    }
    else if(gu8_flushing_mode == FLUSHING_COLD_TANK)
    {
        if(gu8_cold_tank_flushing_step == COLDTANK_FLUSHING_DRAIN)
        {
            Bit3_Drain_Tank_Flushing_State = SET;
        }
        else
        {
            Bit3_Drain_Tank_Flushing_State = CLEAR;
        }
    }
    else
    {
        Bit3_Drain_Tank_Flushing_State = CLEAR;
    }

    Bit6_Acid_Clean_State = CLEAR;

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

    /*..hui [24-3-28���� 10:56:19] �̰͵� �ʿ����.. ������ ����üũ�ϴ� �κп��� ��ȯ���, �޴��� �巹���̸� ���߰� ������..*/
    /*Bit0_Drain_Error_Check_Off_State = bit_drain_err_check_off_state & ~F_DrainStatus & ~bit_manual_drain_start;*/

    /*Bit1_Drain_Error_Confirm_State = Bit16_Drain_Pump_Error__E60;*/

    if( Bit16_Drain_Pump_Error__E60 == SET )
    {
        /*..hui [24-3-28���� 11:09:02] ���� �ɸ� ���¿����� ������ ���� ����Ҷ��� �����ϵ���..*/
        if( bit_drain_melt_pump_output == SET )
        {
            Bit1_Drain_Error_Confirm_State = CLEAR;
        }
        else
        {
            Bit1_Drain_Error_Confirm_State = Bit16_Drain_Pump_Error__E60;
        }
    }
    else
    {
        Bit1_Drain_Error_Confirm_State = CLEAR;
    }


/***************************************************************************************************/

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_full_condition_check(void)
{
    /*..hui [18-1-8���� 3:50:20] ���� �������� �߰�..*/
    if( F_IceFull == SET )
    {
        if( F_old_ice_full != F_IceFull )
        {
            F_old_ice_full = F_IceFull;

            /*if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)*/
            /*..hui [24-3-28���� 7:11:46] �����϶� ����.. ���� ó���ؾ���..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_LOW || u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
            {
                Bit2_Drain_Ice_Full = SET;
            }
            else
            {
                Bit2_Drain_Ice_Full = CLEAR;
            }
        }
        else
        {
            if(Bit2_Drain_Ice_Full == SET)
            {
                /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
                /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
                {
                    Bit2_Drain_Ice_Full = CLEAR;
                }
                else{}
            }
            else
            {

            }
        }
    }
    else
    {
        F_old_ice_full = CLEAR;

        /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        {
            Bit2_Drain_Ice_Full = CLEAR;
        }
        else{}
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void keep_3_hour_check(void)
{
    /*..hui [17-12-18���� 1:05:30] ������ ���� 3�ð� �̻� ������ ������ �̰������� ��� ..*/
    if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
    {
        /*..hui [17-12-18���� 1:16:57] �巹������ �����߿��� ī��Ʈ ����..*/
        if(Bit1_Drain_Low_3_Hour == SET)
        {

        }
        else
        {
            gu16_drain_low_water_1min_tmr++;
        }

        if(gu16_drain_low_water_1min_tmr >= 600)
        {
            gu16_drain_low_water_1min_tmr = 0;

            gu16_drain_low_water_3hour_tmr++;

            /*if(gu16_drain_low_water_3hour_tmr >= 180)*/
            if(gu16_drain_low_water_3hour_tmr >= 120)
            {
                Bit1_Drain_Low_3_Hour = SET;
                gu16_drain_low_water_3hour_tmr = 0;
            }
            else{}
        }
        else{}
    }
    else
    {
        if(Bit1_Drain_Low_3_Hour == SET)
        {
            /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
            /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
            {
                Bit1_Drain_Low_3_Hour = CLEAR;
            }
            else{}
        }
        else
        {
            gu16_drain_low_water_1min_tmr = 0;
            gu16_drain_low_water_3hour_tmr = 0;
        }
    }
}



#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 detect_drain_tank_high_level( U8 mu8_current_state )
{
    U8 mu8_return = 0;

    /*..hui [17-12-15���� 10:40:27] ������ ������ ������ �̰����ɶ����� �巹������ ����..*/
    /*..hui [17-12-18���� 10:27:56] �������� ������(������ �̰���,����� ����)���� ��� ����..*/
    if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)
    {
        mu8_current_state = SET;
    }
    else
    {
        if(Bit0_Drain_Tank_Level_Full_State == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                mu8_current_state = CLEAR;
            }
            else{}
        }
        else{}
    }

    return mu8_current_state;

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_drain_tank_high_level( void )
{
    U8 mu8_return = 0;

    /*..hui [17-12-15���� 10:40:27] ������ ������ ������ �̰����ɶ����� �巹������ ����..*/
    /*..hui [17-12-18���� 10:27:56] �������� ������(������ �̰���,����� ����)���� ��� ����..*/
    /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)*/

    /*..hui [23-7-7���� 2:26:32] ���� ������ �и�..*/
    /*if( u8DrainWaterLevel == DRAIN_LEVEL_HIGH )*/
    /*if(u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)*/
    /*..hui [24-3-28���� 7:07:52] ���� ���� ���� �и�..*/
    if( u8DrainWaterLevel == DRAIN_LEVEL_HIGH || u8DrainWaterLevel == DRAIN_LEVEL_ERROR)
    {
        Bit0_Drain_Level_Full = SET;
    }
    else
    {
        if( Bit0_Drain_Level_Full == SET )
        {
            /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
            /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
            {
                Bit0_Drain_Level_Full = CLEAR;
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
void ice_off_check(void)
{
    /*..hui [19-12-2���� 2:07:02] ���� ��� ON->OFF�� ��� ������ �̻��̸� �巹�� ���� ����..*/
    /*if(F_IceOn == CLEAR)*/

    /*if( gu8_ice_setting == ICE_SETTING_OFF )*/
    if(F_IceOn == CLEAR)
    {
        if( F_old_ice_on == SET )
        {
            F_old_ice_on = CLEAR;

            /*if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)*/
            /*..hui [24-3-28���� 7:11:46] �����϶� ����.. ���� ó���ؾ���..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_LOW || u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
            {
                Bit5_Drain_Ice_Off = SET;
            }
            else
            {
                Bit5_Drain_Ice_Off = CLEAR;
            }

            bit_ice_off_24h_start = SET;
        }
        else
        {
            if(Bit5_Drain_Ice_Off == SET)
            {
                /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
                /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
                /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
                /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
                {
                    Bit5_Drain_Ice_Off = CLEAR;
                }
                else{}
            }
            else{}
        }
    }
    else
    {
        F_old_ice_on = SET;
        bit_ice_off_24h_start = CLEAR;

        /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        {
            Bit5_Drain_Ice_Off = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_off_24hour_check(void)
{
    if( bit_ice_off_24h_start == SET )
    {
        gu32_ice_off_24h_teimer++;

        /*..hui [23-7-7���� 2:46:22] OFF�ϰ� 24�ð� �Ŀ� ������ �̻��̸� �巹��..*/
        if( gu32_ice_off_24h_teimer >= 864000 )
        {
            gu32_ice_off_24h_teimer = 0;
            bit_ice_off_24h_start = CLEAR;

            /*if(u8DrainWaterLevel >= DRAIN_LEVEL_LOW)*/
            /*..hui [24-3-28���� 7:11:46] �����϶� ����.. ���� ó���ؾ���..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_LOW || u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
            {
                Bit9_Drain_Ice_Off_24_Hour = SET;
            }
            else
            {
                Bit9_Drain_Ice_Off_24_Hour = CLEAR;
            }
        }
        else{}
    }
    else
    {
        gu32_ice_off_24h_teimer = 0;

        if( Bit9_Drain_Ice_Off_24_Hour == SET )
        {
            /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
            /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
            /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
            {
                Bit9_Drain_Ice_Off_24_Hour = CLEAR;
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
void first_drain_check(void)
{
    /*..hui [23-4-4���� 2:35:55] �巹�� ��ũ ���� �д½ð� ���..*/
    if(F_FW_Version_Display_Mode == CLEAR)
    {
        return;
    }
    else{}

    if( bit_first_drain == SET )
    {
        bit_first_drain = CLEAR;

        if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
        {
            Bit6_Drain_First = SET;
        }
        else
        {
            Bit6_Drain_First = CLEAR;
        }
    }
    else
    {
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        {
            Bit6_Drain_First = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void detect_drain_tank_error_level( void )
{
    U8 mu8_return = 0;

    /*..hui [23-7-7���� 2:26:32] ���� ������ �и�..*/
    if( u8DrainWaterLevel == DRAIN_LEVEL_ERROR && bit_drain_level_error_detect == CLEAR )
    {
        Bit10_Drain_Level_Error = SET;
        bit_drain_level_error_detect = SET;
        gu16_drain_level_error_timer = 0;
        /*gu8_drain_no_water_detect_timer = 0;*/
    }
    else
    {
        if( Bit10_Drain_Level_Error == SET )
        {
            /*..hui [24-4-1���� 1:44:52] �� ���� ������ ��� ����..*/
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                Bit10_Drain_Level_Error = CLEAR;
                gu16_drain_level_error_timer = 0;
                /*gu8_drain_no_water_detect_timer = 0;*/

                /*..hui [24-4-5���� 4:02:24] ���� �� ���� ���� �� ��õ� Ƚ�� �ʱ�ȭ..*/
                gu8_drain_error_retry_cnt = 0;
            }
            else
            {
                gu16_drain_level_error_timer++;

                /*..hui [24-3-28���� 7:20:40] �巹�� �������� �����ϰ�� �ּ� 1�а� ����..*/
                /*if( gu16_drain_level_error_timer >= 600 )*/
                /*..hui [24-4-1���� 1:46:59] �ּ� 2�а� ����..*/
                /*..hui [24-4-5���� 3:58:58] �ּ� 5�а� �������� ����..*/
                if( gu16_drain_level_error_timer >= DRAIN_LEVEL_ERROR_OPERATION_MIN_TIME )
                {
                    gu16_drain_level_error_timer = DRAIN_LEVEL_ERROR_OPERATION_MIN_TIME;

                    /*..hui [24-4-1���� 7:19:54] �Լ��� �и�.. �򰥸�..*/
                    /*..hui [24-4-1���� 7:20:06] �׸��� ������ �ľ��ִ� ���ۿ����� ����ؾ���..*/
                    if( bit_drain_no_water_detect == SET )
                    {
                        /*Bit10_Drain_Level_Error = CLEAR;*/
                        gu8_drain_error_retry_cnt++;

                        if( gu8_drain_error_retry_cnt >= DRAIN_LEVEL_ERROR_RETYR_COUNT )
                        {
                            gu8_drain_error_retry_cnt = DRAIN_LEVEL_ERROR_RETYR_COUNT;
                        }
                        else
                        {
                            Bit10_Drain_Level_Error = CLEAR;
                        }
                    }
                    else{}
                }
                else{}
            }
        }
        else
        {
            gu16_drain_level_error_timer = 0;
            /*gu8_drain_no_water_detect_timer = 0;*/

            /*..hui [24-4-1���� 2:57:13] �巹�� ��������.. �������� ���ƿ��� �������� ����..*/
            /*..hui [24-4-1���� 2:57:52] �巹�� ���� ���� -> ������ ���� -> �������� �����ؼ� �巹�� -> �������� �ٽ� ���� ���� ����..*/
            if( u8DrainWaterLevel != DRAIN_LEVEL_ERROR )
            {
                bit_drain_level_error_detect = CLEAR;
            }
            else{}

            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                /*..hui [24-4-5���� 4:02:24] ���� �� ���� ���� �� ��õ� Ƚ�� �ʱ�ȭ..*/
                gu8_drain_error_retry_cnt = 0;
            }
            else{}
        }
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void detect_drain_pump_error(void)
{
    U8 mu8_error_chk_enable = 0;

    /*..hui [17-12-15���� 10:40:27] ������ ������ ������ �̰����ɶ����� �巹������ ����..*/
    /*..hui [17-12-18���� 1:19:04] �������� ������ ���� �߰�..*/
    detect_drain_tank_high_level();

    /*..hui [17-12-18���� 5:49:40] ������ 3�ð� ���� Ȯ��..*/
    keep_3_hour_check();

    /*..hui [17-12-18���� 5:49:47] ���� ���� Ȯ��..*/
    ice_full_condition_check();

    /*..hui [19-12-2���� 2:16:19] ������� OFF üũ..*/
    ice_off_check();


    /*..hui [23-7-7���� 2:38:42] ���� OFF �� 24�ð� �Ŀ� �巹��..*/
    ice_off_24hour_check();

    /*..hui [18-2-12���� 4:08:15] ��ũ ���� ��� ��� ���� Ȯ��..*/
    forced_drain_check();

    /*..hui [23-4-4���� 2:38:22] ���� ���� ON�� �巹�� ������ ���� �����̸� ����.. �����ܾ��̽� ��� �߰�..*/
    first_drain_check();

    /*..hui [23-5-15���� 4:55:48] ���̽�Ʈ���� �Լ� ������ Ʈ���� ������ ������ �巹�� ���ش�..*/
    /*..hui [23-5-15���� 4:56:02] �ִ��� �巹����ũ �� ���� ���� �����ϵ���.. �����Ѻ���..*/
    ice_make_drain_check();
    
    /*..hui [25-4-17���� 3:44:27] �÷����Ҷ� �巹��..*/
    flushing_drain_check();

    /*..hui [23-5-22���� 1:08:55] ������ũ ����Ҷ� �巹��..*/
    tray_ster_drain_check();

    /*..hui [24-7-25���� 4:08:10] ������ ��ô �����Ҷ� �巹��..*/
    /////acid_drain_check();

    /*..hui [23-7-7���� 2:27:48] �巹����ũ �������� �����϶�..*/
    /*Bit10_Drain_Level_Error = CLEAR;*/
    // detect_drain_tank_error_level();

    /*check_empty_icedetect_drain_pump_error_tray_in();*/

    /*..hui [18-1-22���� 4:34:56] ��ȯ��� ��� �۵����϶� �������� �ʵ��� ����..*/
    /*..hui [19-10-23���� 11:39:05] �¼� �������϶��� �����ߴ� ó������ �ٽ� ����(���� ��)..*/
    /*..hui [20-4-21���� 12:30:57] ù�ܵ巹�� �� ���� �𸵽� �巹�� ���� �� �ٽ� ���� �߰�..*/
    /*..hui [23-4-4���� 2:40:31] ���� ���� ON�� �������ϰ�� ���� �߰� - �����ܾ��̽� ��� - �ŷڼ�..*/
    #if 0
    bit_drain_error_check_enable
        = ( ( Bit0_Drain_Level_Full | Bit1_Drain_Low_3_Hour
              | Bit2_Drain_Ice_Full | Bit3_Drain_Forced | Bit5_Drain_Ice_Off | Bit6_Drain_First | Bit7_Drain_Ice_Making | Bit8_Drain_Tray_ster
              | Bit9_Drain_Ice_Off_24_Hour | bit_tank_drain_pump_output )
              & ~F_DrainStatus & ~bit_manual_drain_start );
    #endif

    #if 0
    if( u16DrainOperate > 0 || bit_tank_drain_pump_output == SET )
    {
        if( F_DrainStatus == CLEAR && bit_manual_drain_start == CLEAR )
        {
            bit_drain_error_check_enable = SET;
        }
        else
        {
            bit_drain_error_check_enable = CLEAR;
        }
    }
    else
    {
        bit_drain_error_check_enable = CLEAR;
    }
    #endif

    #if 0
    if( u16DrainOperate > 0 )
    {
        if( F_DrainStatus == CLEAR && bit_manual_drain_start == CLEAR )
        {
            /*..hui [24-5-24���� 5:54:23] ��ũ �÷��� - ��ũ ����߿��� ���� ����..*/
            if( gu8_flushing_mode == FLUSHING_TANK_STATE && bit_flushing_tank_start == SET  && gu8_flushing_tank_step == 10 )
            {
                bit_drain_error_check_enable = CLEAR;
            }
            else if( bit_acid_clean_start == SET && gu8_acid_clean_step == 9 )
            {
                bit_drain_error_check_enable = CLEAR;
            }
            else if( bit_acid_clean_start == SET && gu8_acid_clean_step >= 23 && gu8_acid_clean_step <= 25 )
            {
                bit_drain_error_check_enable = CLEAR;
            }
            else if( bit_acid_clean_start == SET && gu8_acid_clean_step == 33 )
            {
                bit_drain_error_check_enable = CLEAR;
            }
            else
            {
                bit_drain_error_check_enable = SET;
            }
        }
        else
        {
            bit_drain_error_check_enable = CLEAR;
        }
    }
    else
    {
        bit_drain_error_check_enable = CLEAR;
    }
    #endif

    /* 2KG�� ������ ������ ��� ������ ��ɿ� ���� üũ�� �����ؾ� �� (����� Ư��) 250623 CH.PARK */
    if( u16DrainOperate > 0 )
    {
        bit_drain_error_check_enable = SET;   
    }
    else
    {
        bit_drain_error_check_enable = CLEAR;
    }

    /*if(mu8_error_chk_enable != SET || Bit16_Drain_Pump_Error__E60 == SET)*/
    if( bit_drain_error_check_enable == CLEAR || Bit16_Drain_Pump_Error__E60 == SET)
    {
        gu16_drain_pump_first_op_timer = 0;
        /*gu8_drain_pump_retry_step = DRAIN_RETRY_PUMP_1MIN_OFF;*/
        gu8_drain_pump_retry_step = DRAIN_RETRY_INIT;
        gu16_drain_pump_2min_on_timer = 0;
        gu16_drain_pump_1min_off_timer = 0;
        bit_drain_err_check_on_state = CLEAR;
        /*bit_drain_err_check_off_state = CLEAR;*/
        gu8_drain_err_10_count = 0;
    }
    else
    {
        gu16_drain_pump_first_op_timer++;

        if( gu16_drain_pump_first_op_timer >= DRAIN_ERROR_PUMP_ON_10_MIN )   //10min
        {
            gu16_drain_pump_first_op_timer = DRAIN_ERROR_PUMP_ON_10_MIN;

            bit_drain_err_check_on_state = drain_pump_error_retry_proc();
            /*bit_drain_err_check_off_state = ~bit_drain_err_check_on_state;*/
        }
        else
        {
            bit_drain_err_check_on_state = SET;
            /*bit_drain_err_check_off_state = CLEAR;*/
        }
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 drain_pump_error_retry_proc( void )
{
    U8 mu8_return = CLEAR;

    /*..hui [17-12-18���� 3:29:43] 10�� �����ص� ������ ������ �ȵǸ� 2�� ON, 1�� OFF 10ȸ �ݺ�..*/
    switch( gu8_drain_pump_retry_step )
    {
        case DRAIN_RETRY_INIT :

            gu16_drain_pump_1min_off_timer++;

            /*..hui [24-3-28���� 2:30:21] 1�а� ���..*/
            if( gu16_drain_pump_1min_off_timer >= DRAIN_ERROR_PUMP_OFF_1_MIN )
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;

                /*..hui [24-3-28���� 2:30:53] 10�� �����Ŀ� ������ ������ ����, ������ �̰����� ���..*/
                /*..hui [24-3-28���� 2:31:04] ������ ���� ����￡ ���� �Ͻ��� �������� ����..*/
                /*..hui [24-4-1���� 7:29:22] AD �Էµ� Ȯ��... ��� ���� ���.. �� ������������ �ü� �巹�� ���� �ȵ�..*/
                /*..hui [24-4-5���� 5:47:09] ������ũ ��ô�߿��� �ü� �巹�� ����..*/
                #if 0
                if( u8DrainWaterLevel == DRAIN_LEVEL_LOW
                    && bit_drain_no_water_detect == SET
                    && bit_ice_tank_ster_start == CLEAR )
                #endif

                /*..hui [24-4-8���� 3:50:16] ������ũ ��ô �߿��� �����ϰ�....*/
                if( u8DrainWaterLevel == DRAIN_LEVEL_LOW
                && bit_drain_no_water_detect == SET )
                {
                    gu8_drain_pump_retry_step = DRAIN_RETRY_COLD_DRIN_ON;
                }
                else
                {
                    /*..hui [24-3-28���� 2:25:26] �� ���� ��쿡�� �ٷ� ��õ� �������� ����..*/
                    gu8_drain_pump_retry_step = DRAIN_RETRY_PUMP_1MIN_OFF;
                }
            }
            else{}

            break;

        case DRAIN_RETRY_COLD_DRIN_ON :
            gu16_drain_pump_2min_on_timer++;

            /*..hui [24-3-28���� 2:45:34] �ü� �巹�� ��� 15�� ���� ON..1�ʴ� ���� �� 12ml = 180ml ����..*/
            if( gu16_drain_pump_2min_on_timer >= 150 )
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;
                gu8_drain_pump_retry_step = DRAIN_RETRY_PUMP_1MIN_OFF;
            }
            else{}

            break;

        case DRAIN_RETRY_PUMP_1MIN_OFF :

            gu16_drain_pump_1min_off_timer++;

            if( gu16_drain_pump_1min_off_timer >= DRAIN_ERROR_PUMP_OFF_1_MIN )
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;
                gu8_drain_pump_retry_step = DRAIN_RETRY_PUMP_2MIN_ON;
                /*mu8_return = SET;*/

                /*if(gu8_drain_err_10_count >= 10)*/
                if(gu8_drain_err_10_count >= 12)
                {
                    /*..hui [17-12-18���� 5:33:37] ���� set..*/
                    gu8_drain_err_10_count = 0;

                    Bit16_Drain_Pump_Error__E60 = SET;
                    mu8_return = CLEAR;
                }
                else
                {
                    mu8_return = SET;
                }
            }
            else
            {
                mu8_return = CLEAR;
            }

            break;

        case DRAIN_RETRY_PUMP_2MIN_ON :

            gu16_drain_pump_2min_on_timer++;

            if(gu16_drain_pump_2min_on_timer >= DRAIN_ERROR_PUMP_ON_2_MIN)
            {
                gu16_drain_pump_1min_off_timer = 0;
                gu16_drain_pump_2min_on_timer = 0;
                gu8_drain_pump_retry_step = DRAIN_RETRY_PUMP_1MIN_OFF;

                gu8_drain_err_10_count++;
                mu8_return = CLEAR;
            }
            else
            {
                mu8_return = SET;
            }

            break;

        default :
             //
             mu8_return = CLEAR;
            break;
    }

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void forced_drain_check(void)
{
    /*..hui [18-2-12���� 4:13:12] ������ũ, �ü���ũ �������϶� �巹����ũ�� ������ �̻��̸� ������� ��� ����..*/
    if( /*u8DrainWaterLevel >= DRAIN_LEVEL_LOW*/
        ( u8DrainWaterLevel == DRAIN_LEVEL_LOW || u8DrainWaterLevel == DRAIN_LEVEL_HIGH )
        && gu8_Room_Water_Level == ROOM_LEVEL_LOW
        && F_Tank_Cover_Input == CLEAR )
    {
        Bit3_Drain_Forced = SET;
        gu8_forced_drain_add_timer = 0;
    }
    else
    {
        if(Bit3_Drain_Forced == SET)
        {
            if(u8DrainWaterLevel == DRAIN_LEVEL_EMPTY)
            {
                gu8_forced_drain_add_timer++;

                /*..hui [18-2-12���� 4:14:14] ��� �Ϸ� �� 10�� �߰� ���..*/
                if(gu8_forced_drain_add_timer >= FORCED_DRAIN_ADDITIONAL_TIME)
                {
                    gu8_forced_drain_add_timer = 0;
                    Bit3_Drain_Forced = CLEAR;
                }
                else
                {
                    Bit3_Drain_Forced = SET;
                }
            }
            else{}
        }
        else
        {
            gu8_forced_drain_add_timer = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_make_drain_check(void)
{
    /*..hui [23-5-15���� 5:20:05] Ʈ���� �� ������ �ְ��� �ð� ����Ҷ� �������̸� �巹�� ����..*/
    /*..hui [23-5-15���� 5:20:31] 1ȸ�� ����.. �������ϰ�쿡�� ������� �巹�ε�..*/
    if( gu8IceStep == STATE_42_CALC_HOT_GAS_TIME )
    {
        if(u8DrainWaterLevel == DRAIN_LEVEL_LOW)
        {
            Bit7_Drain_Ice_Making = SET;
        }
        else
        {
            Bit7_Drain_Ice_Making = CLEAR;
        }
    }
    else
    {
        /*..hui [23-7-7���� 1:29:17] �ּ� �����ð� ���� ���� ������ ���� ���� �� ����..*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || bit_drain_no_water_detect == SET )*/
        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )*/
        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
        // if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
        {
            Bit7_Drain_Ice_Making = CLEAR;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flushing_drain_check(void)
{
    if( gu8_flushing_mode > FLUSHING_NONE_STATE )
    {
        if( gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE )
        {
            if( gu8_cold_tank_fill_step == 1 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    Bit4_Drain_Flushing = SET;
                }
                else
                {
                    if( Bit4_Drain_Flushing == SET )
                    {
                        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                        {
                            Bit4_Drain_Flushing = CLEAR;
                        }
                        else{}
                    }
                    else{}
                }
            }
            else
            {
                Bit4_Drain_Flushing = CLEAR;
            }
        }
        else
        {
            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                Bit4_Drain_Flushing = CLEAR;
            }
            else{}
        }
    }
    else
    {
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
        {
            Bit4_Drain_Flushing = CLEAR;
        }
        else{}
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void tray_ster_drain_check(void)
{
	if( bit_ice_tank_ster_start == SET )
	{
		if( gu8_ice_ster_mode == STER_MODE_PREPARE )
		{
			if( gu8_prepare_ster_step <= 3 )
			{
				if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
				{
					Bit8_Drain_Tray_ster = SET;
				}
				else
				{
					if( Bit8_Drain_Tray_ster == SET )
					{
						if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
						{
							Bit8_Drain_Tray_ster = CLEAR;
						}
						else{}
					}
					else{}
				}
			}
			else
			{
				if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
				{
					Bit8_Drain_Tray_ster = CLEAR;
				}
				else{}
			}
		}
		else if( gu8_ice_ster_mode == STER_MODE_HOT_WAIT_STATE )
		{
			/*if( gu8_hot_wait_step == 4 )*/
			if( gu8_hot_wait_step == 6 )
			{
				if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
				{
					Bit8_Drain_Tray_ster = SET;
				}
				else
				{
					if( Bit8_Drain_Tray_ster == SET )
					{
						if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
						{
							Bit8_Drain_Tray_ster = CLEAR;
						}
						else{}
					}
					else{}
				}
			}
			else
			{
				if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
				{
					Bit8_Drain_Tray_ster = CLEAR;
				}
				else{}
			}
		}
		else if( gu8_ice_ster_mode == STER_MODE_FINISH )
		{
			if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
			{
				Bit8_Drain_Tray_ster = SET;
			}
			else
			{
				if( Bit8_Drain_Tray_ster == SET )
				{
					if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
					{
							Bit8_Drain_Tray_ster = CLEAR;
					}
					else{}
				}
				else{}
			}
		}
		else
		{
			if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
			{
				Bit8_Drain_Tray_ster = CLEAR;
			}
			else{}
		}
	}
	else
	{
		if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
		{
			Bit8_Drain_Tray_ster = CLEAR;
		}
		else{}
	}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void acid_drain_check(void)
{
    /*..hui [24-7-22���� 5:15:27] ������ ��ô�Ҷ� �巹��..*/
    if( bit_acid_clean_start == SET )
    {
        if( gu8_acid_clean_mode == ACID_CLEAN_NONE_STATE )
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_STANDBY )
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE )
        {
            if( gu8_acid_prepare_step == 2 || gu8_acid_prepare_step == 3 )
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    Bit10_Drain_Acid_Clean = SET;
                }
                else
                {
                    if( Bit10_Drain_Acid_Clean == SET )
                    {
                        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
                        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )*/
                        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                        {
                            Bit10_Drain_Acid_Clean = CLEAR;
                        }
                        else{}
                    }
                    else{}
                }
            }
            else
            {
                Bit10_Drain_Acid_Clean = CLEAR;
            }
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_CHANGE_FILTER )
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_WAIT_1_HOUR )
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
        else if( gu8_acid_clean_mode == ACID_CLEAN_RINSE )
        {
            if( gu8_acid_rinse_step == 1 || gu8_acid_rinse_step == 10 || gu8_acid_rinse_step == 13 )
            {
                Bit10_Drain_Acid_Clean = CLEAR;
            }
            else
            {
                if( u8DrainWaterLevel == DRAIN_LEVEL_LOW )
                {
                    Bit10_Drain_Acid_Clean = SET;
                }
                else
                {
                    if( Bit10_Drain_Acid_Clean == SET )
                    {
                        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
                        /*if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )*/
                        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
                        {
                            Bit10_Drain_Acid_Clean = CLEAR;
                        }
                        else{}
                    }
                    else{}
                }
            }
        }
        else /*if( gu8_acid_clean_mode == ACID_CLEAN_FINISH )*/
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
    }
    else
    {
        /*..hui [24-4-1���� 5:03:29] ���� �����ϰ�쿡�� ����.. ���� ���� �Լ����� ���� ó��..*/
        if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY || u8DrainWaterLevel == DRAIN_LEVEL_ERROR )
        {
            Bit10_Drain_Acid_Clean = CLEAR;
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_drain_pump( U16 u16_data )
{
    gu16_drain_pwm_out = u16_data;
    TDR13 = gu16_drain_pwm_out;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_drain_pump( void )
{
    gu16_drain_pwm_out = 0;
    TDR13 = gu16_drain_pwm_out;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_melt_water(void)
{
    U16 mu16_drain_time = 0;
    U32 mu32_standby_time = 0;

    if( Bit16_Drain_Pump_Error__E60 == CLEAR )
    {
        gu32_drain_melt_standby_timer = 0;
        gu16_drain_melt_op_timer = 0;
        bit_drain_melt_pump_output = CLEAR;
        bit_ice_melt_2_hour = CLEAR;
        gu8_drain_melt_cnt = 0;
        bit_drain_melt_finish = CLEAR;
        gu8_drain_error_clear_timer = 0;
        return;
    }
    else
    {
        /*..hui [24-3-28���� 9:47:39] ���� �ɸ� �� ��ũ ������ ���� ��� ����.. ���ĺ��ʹ� ���� ���� �Ѿ� ���� ������..*/
        if( bit_drain_melt_finish == SET )
        {
            return;
        }
        else{}
    }


    if( gu8_drain_melt_cnt < 6 )
    {
        /*..hui [24-3-28���� 9:37:53] 6ȸ������ 2�ð� ����..*/
        mu32_standby_time = 72000;
    }
    else
    {
        /*..hui [24-3-28���� 9:38:06] 7ȸ���ʹ� 3�ð� ����..*/
        mu32_standby_time = 108000;
    }

    gu32_drain_melt_standby_timer++;

    /*..hui [24-3-27���� 4:50:29] ���� �߻��ϰ� 2�ð� ��� Ȯ��..*/
    /*if( gu32_drain_melt_standby_timer >= 72000 )*/
    if( gu32_drain_melt_standby_timer >= mu32_standby_time )
    {
        /*gu8_drain_melt_cnt++;*/

        if( gu8_drain_melt_cnt >= 12 )
        {
            gu8_drain_melt_cnt = 12;
            /*gu32_drain_melt_standby_timer = 72000;*/
            gu32_drain_melt_standby_timer = 0;
            bit_ice_melt_2_hour = CLEAR;

            /*..hui [24-3-28���� 9:47:02] ��ũ ������ ������� ����..*/
            bit_drain_melt_finish = SET;
        }
        else
        {
            gu8_drain_melt_cnt++;
            gu32_drain_melt_standby_timer = 0;
            bit_ice_melt_2_hour = SET;
        }
    }
    else{}

    if( gu8_drain_melt_cnt <= 6 )
    {
        /*..hui [24-3-28���� 9:38:21] 6ȸ������ 1�е��� ���..*/
        mu16_drain_time = 600;
    }
    else
    {
        /*..hui [24-3-28���� 9:38:27] 7ȸ���ʹ� 30�ʰ� ���..*/
        mu16_drain_time = 300;
    }

    /*..hui [24-3-27���� 4:50:35] 2�ð� �����..*/
    if( bit_ice_melt_2_hour == SET )
    {
        gu16_drain_melt_op_timer++;

        /*..hui [24-3-27���� 4:50:42] 1�е��� ������ �巹�� ���� ����..*/
        /*if( gu16_drain_melt_op_timer >= 600 )*/
        if( gu16_drain_melt_op_timer >= mu16_drain_time )
        {
            gu16_drain_melt_op_timer = 0;
            bit_drain_melt_pump_output = CLEAR;
            bit_ice_melt_2_hour = CLEAR;
        }
        else
        {
            bit_drain_melt_pump_output = SET;

            if( u8DrainWaterLevel == DRAIN_LEVEL_EMPTY )
            {
                gu8_drain_error_clear_timer++;

                /*..hui [24-3-28���� 10:00:42] �巹�� ���������� 5�� ���� �� ���� ���� �� ���� ���� �� ���� ����..*/
                if( gu8_drain_error_clear_timer >= 50 )
                {
                    gu8_drain_error_clear_timer = 0;
                    Bit16_Drain_Pump_Error__E60 = CLEAR;
                }
                else{}
            }
            else
            {
                gu8_drain_error_clear_timer = 0;
            }
        }
    }
    else
    {
        gu16_drain_melt_op_timer = 0;
        bit_drain_melt_pump_output = CLEAR;
        gu8_drain_error_clear_timer = 0;
    }


}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



