/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)   - TST02FQP2361500101
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "m_wifi_make_data.h"
#include "WIFI_SetFunctionData.h"
#include "WIFI_Common.h"

void wifi_operation_control(void);
void send_wifi_data(void);
void check_water_out_state(void);
U8 check_error_state(void);
void make_wifi_app_data(void);
void wifi_water_select(void);
void avg_mixing_water_temp(void);
void silver_care(void);
void cody_care(void);
void filter_change(void);
void power_check(void);
void init_wifi_elec_watt(void);
void water_quantity(void);
void init_water_quantity(void);
void send_wifi_system_function(void);
void send_wifi_manual_test_function(void);
void send_wifi_self_test_function(void);
void send_wifi_each_data_control( U8 mu8_data );
void send_wifi_water_select_data_control( U8 mu8_data );

void check_wifi_auto_drain_state(void);
void check_wifi_uv_state(void);
void wifi_ice_out_time(void);
void init_wifi_ice_out_time(void);

///void wifi_water_level_state(void);
///void check_cold_tank_low_level_state(void);
///void check_cold_tank_high_level_state(void);
///void wifi_ice_tank_ster_state(void);
void wifi_hot_heater_state(void);
void init_wifi_hot_heater(void);

void wifi_comp_state(void);
void init_wifi_comp(void);

void wifi_ice_full(void);
void wifi_ice_step(void);

//void wifi_uv_water_tank_state(void);
void wifi_uv_ice_tank_state(void);
void wifi_uv_ice_tray_state(void);
//void wifi_uv_ice_tank_front_state(void);

void wifi_no_use_save_mode(void);
void wifi_ice_data_all(void);
void init_wifi_ice_data_all(void);

void wifi_flushing(void);
void wifi_no_use_time(void);
void init_wifi_no_use_time(void);

void wifi_smart_save_state(void);
void wifi_sleep_mode(void);
void wifi_neo_filter_alarm(void);
void wifi_ro_filter_alarm(void);
void wifi_ino_filter_alarm(void);
void wifi_neo_ino_filter_alarm_start(void);
void wifi_neo_ino_filter_alarm_stop(void);
void wifi_neo_ro_ino_filter_alarm_start(void);
void wifi_neo_ro_ino_filter_alarm_stop(void);


void check_self_manual_state(void);
void check_prohibit_state(void);


TYPE_LONG          U32ErrOldW;
#define            u32ErrOld                               U32ErrOldW.dward
#define            Bit0_Err_Old_0                          U32ErrOldW.Bit.b0
#define            Bit1_Err_Old_1                          U32ErrOldW.Bit.b1
#define            Bit2_Err_Old_2                          U32ErrOldW.Bit.b2
#define            Bit3_Err_Old_3                          U32ErrOldW.Bit.b3
#define            Bit4_Err_Old_4                          U32ErrOldW.Bit.b4
#define            Bit5_Err_Old_5                          U32ErrOldW.Bit.b5
#define            Bit6_Err_Old_6                          U32ErrOldW.Bit.b6
#define            Bit7_Err_Old_7                          U32ErrOldW.Bit.b7
#define            Bit8_Err_Old_8                          U32ErrOldW.Bit.b8
#define            Bit9_Err_Old_9                          U32ErrOldW.Bit.b9
#define            Bit10_Err_Old_10                        U32ErrOldW.Bit.b10
#define            Bit11_Err_Old_11                        U32ErrOldW.Bit.b11
#define            Bit12_Err_Old_12                        U32ErrOldW.Bit.b12
#define            Bit13_Err_Old_13                        U32ErrOldW.Bit.b13
#define            Bit14_Err_Old_14                        U32ErrOldW.Bit.b14
#define            Bit15_Err_Old_15                        U32ErrOldW.Bit.b15
#define            Bit16_Err_Old_16                        U32ErrOldW.Bit.b16
#define            Bit17_Err_Old_17                        U32ErrOldW.Bit.b17
#define            Bit18_Err_Old_18                        U32ErrOldW.Bit.b18
#define            Bit19_Err_Old_19                        U32ErrOldW.Bit.b19
#define            Bit20_Err_Old_20                        U32ErrOldW.Bit.b20
#define            Bit21_Err_Old_21                        U32ErrOldW.Bit.b21
#define            Bit22_Err_Old_22                        U32ErrOldW.Bit.b22
#define            Bit23_Err_Old_23                        U32ErrOldW.Bit.b23
#define            Bit24_Err_Old_24                        U32ErrOldW.Bit.b24
#define            Bit25_Err_Old_25                        U32ErrOldW.Bit.b25
#define            Bit26_Err_Old_26                        U32ErrOldW.Bit.b26
#define            Bit27_Err_Old_27                        U32ErrOldW.Bit.b27
#define            Bit28_Err_Old_28                        U32ErrOldW.Bit.b28
#define            Bit29_Err_Old_29                        U32ErrOldW.Bit.b29
#define            Bit30_Err_Old_30                        U32ErrOldW.Bit.b30


TYPE_BYTE          U8WifiSendStateB;
#define            u8WifiSendState                         U8WifiSendStateB.byte
#define            Bit0_Wifi_Auto_Drain_Start_State        U8WifiSendStateB.Bit.b0
#define            Bit1_Wifi_UV_Start_State                U8WifiSendStateB.Bit.b1


bit F_Wifi_Tx_Condition;
bit F_Wifi_Each_Data_Tx_Condition;
U8 gu8_change_data;

bit F_Wifi_Self_Test_Tx_Condition;

bit F_Wifi_Self_Periodic_Tx_Condition;

U8 u8OutHot_Temp_AVG;             // ��� ����µ��� (App��)


U16 gu16_silver_timer_sec;
U16 gu16_silver_timer_min;
bit F_Siver_Care_Alarm;             // �ǹ��ɾ� ���� ���� �÷���(App��)
U8 u8FirstSilverCare;


U8 gu8_cody_care_timer_msec;
U16 gu16_cody_care_timer_sec;


U16 gu16_hot_heater_watt;
U16 gu16_ice_heater_watt;
U16 gu16_comp_watt;
U16 gu16_wifi_total_watt;

U16 gu16_power_check_timer;


U16 gu16_wifi_normal_quant;
U16 gu16_wifi_hot_quant;
U16 gu16_wifi_total_quant;
U8 gu8_wifi_water_send_count;
U8 gu8_wifi_ice_send_count;

U8 gu8_Err_Code_Wifi;

bit F_Wifi_Water_Out;

bit F_Wifi_Flushing;


U8 gu8_hot_avg_timer;


bit F_Tank_Cover_Wifi;

bit F_Filter_Cover_Wifi;
bit F_Filter_1_Neo_Cover_Wifi;
bit F_Filter_2_Ro_Cover_Wifi;
bit F_Filter_3_Ino_Cover_Wifi;
bit F_Acid_Filter_Wifi;


bit bit_wifi_first_sleep_mode;


U8 gu8_err_cnt;
U8 gu8_tx_cnt;


U8 gu8_wifi_uv_start;
U8 gu8_wifi_uv_operation;
U8 gu8_wifi_uv_step;

U8 gu8_wifi_uv_send_cnt;

U8 gu8_water_send_timer;

U16 gu16_wifi_water_acc;


U8 gu8_wifi_tds_update;


U8 gu8_wifi_auto_drain_op;
U8 gu8_wifi_first_auto_drain;

U8 gu8_wifi_uv_op;
U8 gu8_wifi_first_uv;



U8 gu8_before_faucet;


U8 gu8_wifi_self_test_op;
U8 gu8_wifi_self_test_state;
U8 gu8_wifi_self_test_progress;
U8 gu8_wifi_self_test_timer;

bit bit_wifi_self_test_finish;


U32 gu32_wifi_ice_out_time;
bit bit_first_ice_send;


U8 gu8_wifi_cold_low_on_timer;
U8 gu8_wifi_cold_low_off_timer;
bit bit_wifi_cold_low;
bit bit_wifi_first_cold_low;

U8 gu8_wifi_cold_high_on_timer;
U8 gu8_wifi_cold_high_off_timer;
bit bit_wifi_cold_high;
bit bit_wifi_first_cold_high;


bit bit_wifi_first_drain_low;
bit bit_wifi_first_drain_high;



bit bit_wifi_first_ice_tank_ster;
bit bit_wifi_ice_tank_ster_old;

bit bit_wifi_first_hot_heater;
bit bit_wifi_hot_heater;
bit bit_wifi_heater_on_time_update;

bit bit_wifi_first_comp;
bit bit_wifi_comp;
bit bit_wifi_comp_on_time_update;

U16 gu16_wifi_total_usage_water;

bit bit_wifi_first_ice_full;
bit bit_wifi_ice_full_old;


U8 gu8_wifi_ice_make_state;
U8 gu8_wifi_ice_make_state_timer;

bit bit_wifi_first_water_tank_uv;
bit bit_wifi_water_tank_uv_old;

bit bit_wifi_first_ice_tank_uv;
bit bit_wifi_ice_tank_uv_old;

bit bit_wifi_first_ice_tray_uv;
bit bit_wifi_ice_tray_uv_old;

bit bit_wifi_first_ice_tank_front_uv;
bit bit_wifi_ice_tank_front_uv_old;


U32 gu32_hot_target_reach_timer_ms;
U16 gu16_hot_target_reach_timer_sec;


U32 gu32_cold_target_reach_timer_ms;
U16 gu16_cold_target_reach_timer_sec;


U16 gu16_wifi_filter_remain_day;


bit bit_wifi_first_no_use_save;
bit bit_wifi_no_use_save_old;

bit bit_wifi_first_sleep;
bit bit_wifi_sleep_old;


U8 gu8_wifi_water_select;

U16 WifiSmartCheckResultData = 0U;

U32 gu32_wifi_ice_make_time;
U32 gu32_wifi_hot_gas_time;
U16 gu16_wifi_tray_in_time;
U16 gu16_wifi_tray_in_flow;
bit bit_wifi_ice_data_send;

U8 gu8_wifi_flushing_state;

U16 gu16_wifi_no_use_timer_sec;
U16 gu16_wifi_no_use_timer_min;
U8 gu8_wifi_no_use_key;
U8 gu8_wifi_no_use_time_send;

U8 gu8_smart_operation_mode_old;
bit bit_smart_first_send;
U8 gu8_wifi_smart_save;


bit bit_wifi_neo_filter_1_alarm;
bit bit_wifi_ro_filter_2_alarm;
bit bit_wifi_ino_filter_3_alarm;


bit bit_wifi_neo_alarm_old;
bit bit_wifi_ro_alarm_old;
bit bit_wifi_ino_alarm_old;

bit bit_wifi_first_neo_alarm;
bit bit_wifi_first_ro_alarm;
bit bit_wifi_first_ino_alarm;

U8 gu8_wifi_ice_ster_state;

U8 gu8_wifi_acid_clean_state;

bit bit_wifi_first_faucet_uv;
bit bit_wifi_faucet_uv_old;

U32 gu32_wifi_ice_make_time;
U32 gu32_wifi_ice_heater_timer;
U32 gu32_wifi_hot_gas_time;
U16 gu16_wifi_tray_in_time;
U16 gu16_wifi_tray_in_flow;
bit bit_wifi_ice_data_send;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_operation_control(void)
{
    make_wifi_app_data();
    send_wifi_data();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_data(void)
{
    U8 mu8_error_change = 0;

    /*..hui [21-3-15���� 7:08:48] �� ���� ���� ��..*/
    check_water_out_state();

    /*..hui [21-9-6���� 10:36:57] �������� ����..*/
    check_self_manual_state();

    /*..hui [21-8-3���� 7:26:37] 1. TDS ���� �Ϸ�������..*/
    /*..hui [21-8-3���� 7:26:52] 2. ��ư - ��ü��� ����..*/
    /*..hui [21-8-3���� 7:26:56] 3. ��ư - �¼���� ����..*/
    /*..hui [21-8-3���� 7:27:06] 4. ��ư - �ü� ON/OFF ����..*/
    /*..hui [21-8-3���� 7:27:14] 5. LCD - �⺻�뷮 ����..*/
    /*..hui [21-8-3���� 7:27:20] 6. LCD - �ü��µ� ����..*/
    /*..hui [21-8-3���� 7:27:26] 7. LCD - ���� ����..*/
    /*..hui [21-8-3���� 7:27:34] 8. LCD - ���񽺸�� ����..*/
    /*..hui [21-8-3���� 7:27:41] 9. LCD - �Ŀ�� ���ð� ����..*/
    /*..hui [21-8-3���� 7:27:50] 10. LCD - ��ü��� ���� - CP��..*/
    /*..hui [21-8-3���� 7:28:05] 11. UV ��� ��..*/
    /*..hui [21-8-3���� 7:28:08] 12. �ڵ���� ��..*/
    if( F_Wifi_Tx_Condition == SET )
    {
        // WifiSendData(WIFI_DATA_FUNCTION);
        F_Wifi_Tx_Condition = CLEAR;

        gu8_tx_cnt++;
    }
    else{}


    if( F_Wifi_Each_Data_Tx_Condition == SET )
    {
        /*..hui [23-6-28���� 11:01:09] ��ǰ���� ���� ����� ���� �����Ҷ�..*/
        // WifiSendDataControl(WIFI_DATA_FUNCTION_CONTROL, gu8_change_data);
        F_Wifi_Each_Data_Tx_Condition = CLEAR;

        gu8_tx_cnt++;
    }
    else{}


    if( F_Wifi_Self_Test_Tx_Condition == SET )
    {
        WifiSendData(WIFI_DATA_EXAMINE);
        F_Wifi_Self_Test_Tx_Condition = CLEAR;

        gu8_tx_cnt++;
    }
    else{}

    if( F_Wifi_Self_Periodic_Tx_Condition == SET )
    {
        // WifiSendData(WIFI_DATA_PART);
        F_Wifi_Self_Periodic_Tx_Condition = CLEAR;

        gu8_tx_cnt++;
    }
    else{}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

    mu8_error_change = check_error_state();

    if( mu8_error_change == SET )
    {
        // WifiSendData(WIFI_DATA_ERROR);
        gu8_err_cnt++;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_water_out_state(void)
{
    /*..hui [21-3-5���� 2:01:13] �� ���� ����� ��..*/
    if( F_WaterOut == SET )
    {
        if( F_Wifi_Water_Out == CLEAR )
        {
            F_Wifi_Water_Out = SET;
            gu8_water_send_timer = 0;

            /*..hui [21-9-8���� 10:52:32] �ڰ����� ������ ���⼭ �����°ɷ�..*/
            gu8_wifi_self_test_state = WIFI_SELF_TEST_PROHIBIT;
            gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;

            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( F_Wifi_Water_Out == SET )
        {
            gu8_water_send_timer++;

            if( gu8_water_send_timer >= 5 )
            {
                gu8_water_send_timer = 0;
                F_Wifi_Water_Out = CLEAR;

                /*..hui [21-11-2���� 7:42:57] �ü���ũ ä������ ������ �¼� �巹�� ���� �� ���� ������ ������..*/
                /*..hui [21-11-2���� 7:43:20] �� ������ ����� ���������� �������� �����ؾ���..*/
                if( gu8_flushing_mode == FLUSHING_NONE_STATE && F_IceOut == CLEAR )
                {
                    gu8_wifi_self_test_state = WIFI_SELF_TEST_NO_OPERATION;
                    gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;
                }
                else{}

                /*send_wifi_system_function();*/
                send_wifi_each_data_control( WIFI_FUNC_000D_WATER_OUTQUANTITY );
                /*..hui [24-1-9���� 1:29:37] 1010������ 1014���� ������ ���� �ʱ�ȭ�ϱ����� ī��Ʈ..*/
                /*gu8_wifi_water_send_count = 0;*/
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
U8 check_error_state(void)
{
    U8 mu8_return = 0;
/*
    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET )
    {
        if( Bit0_Err_Old_0 != SET )
        {
            Bit0_Err_Old_0 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit0_Err_Old_0 == SET )
        {
            Bit0_Err_Old_0 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
*/
    /*..hui [21-3-12���� 3:12:16] �¼� ���� ���� ����..*/
#if 0
    if( Bit1_Room_OverHeat_Error__E49 == SET )
    {
        if( Bit1_Err_Old_1 != SET )
        {
            Bit1_Err_Old_1 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit1_Err_Old_1 == SET )
        {
            Bit1_Err_Old_1 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
#endif
    if( Bit2_Room_Temp_Open_Short_Error__E42 == SET )
    {
        if( Bit2_Err_Old_2 != SET )
        {
            Bit2_Err_Old_2 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit2_Err_Old_2 == SET )
        {
            Bit2_Err_Old_2 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit3_Leakage_Sensor_Error__E01 == SET )
    {
        if( Bit3_Err_Old_3 != SET )
        {
            Bit3_Err_Old_3 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit3_Err_Old_3 == SET )
        {
            Bit3_Err_Old_3 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
#if 0
    if( Bit4_Room_Low_Water_Level_Error__E21 == SET )
    {
        if( Bit4_Err_Old_4 != SET )
        {
            Bit4_Err_Old_4 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit4_Err_Old_4 == SET )
        {
            Bit4_Err_Old_4 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
#endif
    #if 0
    if( Bit5_Hot_Heater_OverHeat_Error__E40_Not_Use == SET )
    {
        if( Bit5_Err_Old_5 != SET )
        {
            Bit5_Err_Old_5 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit5_Err_Old_5 == SET )
        {
            Bit5_Err_Old_5 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
    #endif

    if( Bit6_Main_Water_Flow_Block_Error__E09 == SET )
    {
        if( Bit6_Err_Old_6 != SET )
        {
            Bit6_Err_Old_6 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit6_Err_Old_6 == SET )
        {
            Bit6_Err_Old_6 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
    if( Bit7_BLDC_Communication_Error__E27 == SET )
    {
        if( Bit7_Err_Old_7 != SET )
        {
            Bit7_Err_Old_7 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit7_Err_Old_7 == SET )
        {
            Bit7_Err_Old_7 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit8_BLDC_Operation_Error_Current_Sensing__E81 == SET )
    {
        if( Bit8_Err_Old_8 != SET )
        {
            Bit8_Err_Old_8 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit8_Err_Old_8 == SET )
        {
            Bit8_Err_Old_8 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }


    if( Bit9_BLDC_Operation_Error_Starting_Fail__E82 == SET )
    {
        if( Bit9_Err_Old_9 != SET )
        {
            Bit9_Err_Old_9 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit9_Err_Old_9 == SET )
        {
            Bit9_Err_Old_9 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit10_BLDC_Operation_Error_Over_Current__E83 == SET )
    {
        if( Bit10_Err_Old_10 != SET )
        {
            Bit10_Err_Old_10 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit10_Err_Old_10 == SET )
        {
            Bit10_Err_Old_10 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit11_BLDC_Operation_Error_Overheat__E84 == SET )
    {
        if( Bit11_Err_Old_11 != SET )
        {
            Bit11_Err_Old_11 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit11_Err_Old_11 == SET )
        {
            Bit11_Err_Old_11 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit12_BLDC_Operation_Error_Disconnection_Comm__E85 == SET )
    {
        if( Bit12_Err_Old_12 != SET )
        {
            Bit12_Err_Old_12 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit12_Err_Old_12 == SET )
        {
            Bit12_Err_Old_12 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86 == SET )
    {
        if( Bit13_Err_Old_13 != SET )
        {
            Bit13_Err_Old_13 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit13_Err_Old_13 == SET )
        {
            Bit13_Err_Old_13 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

    if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
    {
        if( Bit14_Err_Old_14 != SET )
        {
            Bit14_Err_Old_14 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit14_Err_Old_14 == SET )
        {
            Bit14_Err_Old_14 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET )
    {
        if( Bit15_Err_Old_15 != SET )
        {
            Bit15_Err_Old_15 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit15_Err_Old_15 == SET )
        {
            Bit15_Err_Old_15 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit16_Drain_Pump_Error__E60 == SET )
    {
        if( Bit16_Err_Old_16 != SET )
        {
            Bit16_Err_Old_16 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit16_Err_Old_16 == SET )
        {
            Bit16_Err_Old_16 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET )
    {
        if( Bit17_Err_Old_17 != SET )
        {
            Bit17_Err_Old_17 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit17_Err_Old_17 == SET )
        {
            Bit17_Err_Old_17 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET )
    {
        if( Bit18_Err_Old_18 != SET )
        {
            Bit18_Err_Old_18 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit18_Err_Old_18 == SET )
        {
            Bit18_Err_Old_18 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
    {
        if( Bit19_Err_Old_19 != SET )
        {
            Bit19_Err_Old_19 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit19_Err_Old_19 == SET )
        {
            Bit19_Err_Old_19 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
#if 0
    if( Bit20_Mixing_Out_Temp_Open_Short_Error__E52 == SET )
    {
        if( Bit20_Err_Old_20 != SET )
        {
            Bit20_Err_Old_20 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit20_Err_Old_20 == SET )
        {
            Bit20_Err_Old_20 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
#endif
    if( Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        if( Bit21_Err_Old_21 != SET )
        {
            Bit21_Err_Old_21 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit21_Err_Old_21 == SET )
        {
            Bit21_Err_Old_21 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    #if 0
    if( Bit22_Tray_In_Temp_Open_Short_Error__E41_Not_Use == SET )
    {
        if( Bit22_Err_Old_22 != SET )
        {
            Bit22_Err_Old_22 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit22_Err_Old_22 == SET )
        {
            Bit22_Err_Old_22 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit23_Water_Tank_1_2_UV_Error__E74 == SET )
    {
        if( Bit23_Err_Old_23 != SET )
        {
            Bit23_Err_Old_23 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit23_Err_Old_23 == SET )
        {
            Bit23_Err_Old_23 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit24_Ice_Tank_1_2_Back_UV_Error__E75 == SET )
    {
        if( Bit24_Err_Old_24 != SET )
        {
            Bit24_Err_Old_24 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit24_Err_Old_24 == SET )
        {
            Bit24_Err_Old_24 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit25_Ice_Tray_1_2_UV_Error__E76 == SET )
    {
        if( Bit25_Err_Old_25 != SET )
        {
            Bit25_Err_Old_25 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit25_Err_Old_25 == SET )
        {
            Bit25_Err_Old_25 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit26_Ice_Tank_3_Front_UV_Error__E79 == SET )
    {
        if( Bit26_Err_Old_26 != SET )
        {
            Bit26_Err_Old_26 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit26_Err_Old_26 == SET )
        {
            Bit26_Err_Old_26 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
    #endif

    #if 0
    /*..hui [24-7-18���� 9:25:12] 2���� �ϳ��� �ɷ��� ����..*/
    if( Bit27_Tds_In_Temp_Open_Short_Error__E90 == SET
        || Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90 == SET )
    {
        if( Bit27_Err_Old_27 != SET )
        {
            Bit27_Err_Old_27 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit27_Err_Old_27 == SET )
        {
            Bit27_Err_Old_27 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit28_Tds_Out_Temp_Open_Short_Error__E91 == SET
        || Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91 == SET )
    {
        if( Bit28_Err_Old_28 != SET )
        {
            Bit28_Err_Old_28 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit28_Err_Old_28 == SET )
        {
            Bit28_Err_Old_28 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit29_Tds_In_Data_Error__E92 == SET
        || Bit2_No_Display_Tds_In_Data_Error__E92 == SET )
    {
        if( Bit29_Err_Old_29 != SET )
        {
            Bit29_Err_Old_29 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit29_Err_Old_29 == SET )
        {
            Bit29_Err_Old_29 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit30_Tds_Out_Data_Error__E93 == SET
        || Bit3_No_Display_Tds_Out_Data_Error__E93 == SET )
    {
        if( Bit30_Err_Old_30 != SET )
        {
            Bit30_Err_Old_30 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit30_Err_Old_30 == SET )
        {
            Bit30_Err_Old_30 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit4_No_Display_Tds_In_Pollution_Error__E98 == SET )
    {
        if( Bit27_Err_Old_27 != SET )
        {
            Bit27_Err_Old_27 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit27_Err_Old_27 == SET )
        {
            Bit27_Err_Old_27 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }

    if( Bit5_No_Display_Tds_Remove_Error__E99 == SET )
    {
        if( Bit28_Err_Old_28 != SET )
        {
            Bit28_Err_Old_28 = SET;
            mu8_return = SET;
        }
        else{}
    }
    else
    {
        if( Bit28_Err_Old_28 == SET )
        {
            Bit28_Err_Old_28 = CLEAR;
            mu8_return = SET;
        }
        else{}
    }
    #endif


    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_wifi_app_data(void)
{
    /*..hui [23-9-25���� 3:35:50] 7���� ���ͽÿ��� ������ȵ�..*/
    /*..hui [23-9-25���� 3:36:12] Ű �������� ����ÿ��� A1014�� ��������..*/
    /*wifi_water_select();*/

    /*avg_mixing_water_temp();*/

    silver_care();

    cody_care();

    filter_change();

    power_check();

    water_quantity();

    wifi_ice_out_time();

    /////wifi_water_level_state();

    /////wifi_ice_tank_ster_state();

    wifi_hot_heater_state();

    wifi_comp_state();

    wifi_ice_full();

    wifi_ice_step();

    //wifi_uv_water_tank_state();
    wifi_uv_ice_tank_state();
    wifi_uv_ice_tray_state();
    //wifi_uv_ice_tank_front_state();

    wifi_no_use_save_mode();

    /*..hui [23-8-29���� 4:56:28] ���� �ý��� ���� ����Ÿ..*/
    wifi_ice_data_all();

    /*..hui [23-8-30���� 9:48:04] �÷��� ���� ����Ÿ..*/
    wifi_flushing();

    /*..hui [23-8-31���� 2:48:21] ��ǰ �̻�� �ð�..*/
    wifi_no_use_time();

    /*..hui [23-8-31���� 2:48:27] ����Ʈ ���� ����\..*/
    wifi_smart_save_state();

    /*..hui [23-12-6���� 10:39:35] ��ħ��� ����..*/
    wifi_sleep_mode();

    /*..hui [23-12-19���� 10:41:52] ���� �˶�..*/
    wifi_neo_filter_alarm();
    wifi_ro_filter_alarm();
    wifi_ino_filter_alarm();



}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_water_select(void)
{
    #if 0
    /*..hui [23-8-2���� 5:12:16] �ÿ��� ������� �߰�..*/
    /*..hui [23-8-2���� 5:12:21] ��� �̰� 1010�� ����..*/
    if( u8WaterOutState != gu8_wifi_water_select )
    {
        gu8_wifi_water_select = u8WaterOutState;
        send_wifi_water_select_data_control( WIFI_FUNC_000B_WATER_SEL );
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void avg_mixing_water_temp(void)
{
    #if 0
    gu8_hot_avg_timer++;

    if( gu8_hot_avg_timer >= 10 )
    {
        gu8_hot_avg_timer = 0;
    }
    else
    {
        return;
    }

    /*..hui [23-6-26���� 7:18:28] �̿¼� ����..*/
    if( F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT )
    {
        if( gu8_hot_setting_temperature == HOT_SET_TEMP_2__TEA__70_oC
            || gu8_hot_setting_temperature == HOT_SET_TEMP_1__MILK__43_oC )
        {
            u8OutHot_Temp_AVG += gu8_Mixing_Out_Temperature_One_Degree;
            u8OutHot_Temp_AVG = u8OutHot_Temp_AVG/2;
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
void silver_care(void)
{
    if( F_WaterOut == SET )
    {
        gu16_silver_timer_sec = 0;
        gu16_silver_timer_min = 0;
        F_Siver_Care_Alarm = CLEAR;
    }
    else{}

    gu16_silver_timer_sec++;

    if( gu16_silver_timer_sec >= 600 )
    {
        gu16_silver_timer_sec = 0;
        gu16_silver_timer_min++;
    }
    else{}

    if( gu16_silver_timer_min >= SILVER_CARE_TIME_MIN )
    {
        gu16_silver_timer_min = SILVER_CARE_TIME_MIN;

        if( F_Siver_Care_Alarm != SET )
        {
            F_Siver_Care_Alarm = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_care(void)
{
    #if 0
    /*..hui [21-3-5���� 9:58:17] Ŀ�� ����..*/
    if( bit_filter_reed != F_Tank_Cover_Wifi )
    {
        F_Tank_Cover_Wifi = bit_filter_reed;
        send_wifi_system_function();
    }
    else{}
    #endif

    /*..hui [21-3-5���� 9:58:17] Ŀ�� ����..*/
    if( F_Tank_Cover_Input != F_Tank_Cover_Wifi )
    {
        F_Tank_Cover_Wifi = F_Tank_Cover_Input;
        send_wifi_system_function();
    }
    else{}

    /*..hui [21-3-12���� 4:50:57] ���������� ī��Ʈ..*/
    if( F_Tank_Cover_Input == CLEAR )
    {
        gu8_cody_care_timer_msec++;

        if( gu8_cody_care_timer_msec >= 10 )
        {
            gu8_cody_care_timer_msec = 0;
            gu16_cody_care_timer_sec++;
        }
        else{}

        if( gu16_cody_care_timer_sec >= CODY_CARE_MAX_TIME )
        {
            gu16_cody_care_timer_sec = CODY_CARE_MAX_TIME;
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void filter_change(void)
{
    if( bit_filter_reed != F_Filter_Cover_Wifi )
    {
        F_Filter_Cover_Wifi = bit_filter_reed;
        send_wifi_system_function();
    }
    else{}

    /*..hui [23-10-4���� 1:27:43] �׿� ���� ���� �߰�..*/
    if( bit_neo_filter_1_reed != F_Filter_1_Neo_Cover_Wifi )
    {
        F_Filter_1_Neo_Cover_Wifi = bit_neo_filter_1_reed;
        send_wifi_system_function();
    }
    else{}

    if( bit_ro_filter_2_reed != F_Filter_2_Ro_Cover_Wifi )
    {
        F_Filter_2_Ro_Cover_Wifi = bit_ro_filter_2_reed;
        send_wifi_system_function();
    }
    else{}

    /*..hui [23-10-4���� 1:27:48] �̳� ���� ���� �߰�..*/
    if( bit_ino_filter_3_reed != F_Filter_3_Ino_Cover_Wifi )
    {
        F_Filter_3_Ino_Cover_Wifi = bit_ino_filter_3_reed;
        send_wifi_system_function();
    }
    else{}

    /*..hui [24-7-30���� 2:49:13] ������ ���� �߰�..*/
    #if 0
    if( bit_acid_reed != F_Acid_Filter_Wifi )
    {
        F_Acid_Filter_Wifi = bit_acid_reed;
        send_wifi_system_function();
    }
    else{}
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void power_check(void)
{
    /*..hui [21-8-3���� 3:15:27] ���� ����Ÿ�� 1�п� �ѹ��� ���� - �����̰�..*/
    /*..hui [23-6-28���� 10:57:18] 5�п� �ѹ��� �����°ɷ� ����.. �հ���..*/
    gu16_power_check_timer++;

    if( gu16_power_check_timer >= 10 )
    {
        gu16_power_check_timer = 0;
    }
    else
    {
        return;
    }

    /*..hui [21-3-5���� 11:58:23] �¼����� 2920/3600 = 0.81 = 0.80 = 0.65..*/
    /*..hui [21-3-5���� 11:58:55] COMP 100/3600 = 0.027 = 0.03..*/
    /*..hui [21-3-5���� 11:59:18] Ż������ 150/3600 = 0.04..*/
    /*..hui [23-6-26���� 7:45:15] �¼����� 500/3600 = 0.138 = 0.138..*/
    /*..hui [23-7-25���� 5:15:15] �¼����� 430/3600 = 0.119..*/
    #if 0
    if( pHEATER_HOT == SET )
    {
        gu16_hot_heater_watt += HOT_HEATER_WATT_FULL;

        /*..hui [21-10-15���� 5:12:31] �ִ� 50W ����..*/
        if( gu16_hot_heater_watt >=  MAX_HOT_HEATER_WATT )
        {
            gu16_hot_heater_watt = MAX_HOT_HEATER_WATT;
        }
        else{}
    }
    else{}
    #endif

    #if 0
    if( F_Comp_Output == SET )
    {
        if( gu8_bldc_target_hz <= BLDC_COMP_45Hz )
        {
            /*..hui [23-6-27���� 9:43:13] 45hz ���� 29.7w == 29.7/3600 = 0.008..*/
            gu16_comp_watt += COMP_45HZ_UNDER_WATT;
        }
        else if( gu8_bldc_target_hz <= BLDC_COMP_60Hz )
        {
            /*..hui [23-6-27���� 9:43:55] 60hz ���� 39.7w == 39.7/3600 == 0.011..*/
            gu16_comp_watt += COMP_60HZ_UNDER_WATT;
        }
        else
        {
            /*..hui [23-6-27���� 9:44:37] 60hz �ʰ� 43.5w == 43.5/3600 == 0.012..*/
            gu16_comp_watt += COMP_60HZ_OOVER_WATT;
        }
    }
    else{}
    #endif


    if( F_Comp_Output == SET )
    {
        if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
        {
            /*..hui [23-11-9���� 9:33:43] �ܱ� 30�� �ʰ�. �ð� 90W == 90/3600 = 0.025..*/
            gu16_comp_watt += COMP_COLD_90_WATT;
        }
        else
        {
            /*..hui [23-11-9���� 9:34:20] �ܱ� 30�� �ʰ�. ���� 80W == 80/3600 == 0.022..*/
            gu16_comp_watt += COMP_ICE_80_WATT;
        }
    }
    else{}

    if( gu16_comp_watt >= MAX_COMP_WATT )
    {
        gu16_comp_watt = MAX_COMP_WATT;
    }
    else{}

    gu16_wifi_total_watt = gu16_hot_heater_watt + gu16_comp_watt;

    if( gu16_wifi_total_watt >= MAX_TOTAL_WATT )
    {
        gu16_wifi_total_watt = MAX_TOTAL_WATT;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_elec_watt(void)
{
    gu16_hot_heater_watt = 0;
    gu16_comp_watt = 0;
    gu16_wifi_total_watt = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_quantity(void)
{
    /*..hui [21-3-5���� 12:36:51] ����� acc_water ���..*/
    /*gu16_wifi_total_quant = gu16_wifi_normal_quant + gu16_wifi_hot_quant;*/


    gu16_wifi_total_quant = gu16_wifi_water_acc;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_water_quantity(void)
{
    gu16_wifi_total_quant = 0;
    gu16_wifi_water_acc = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_system_function(void)
{
    /*..hui [21-3-5���� 2:03:48] WIFI ���� ���� ����Ÿ �۽�..*/
    F_Wifi_Tx_Condition = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_manual_test_function(void)
{
    /*..hui [21-3-5���� 2:03:48] WIFI ���� ���� ����Ÿ �۽�..*/
    F_Wifi_Self_Test_Tx_Condition = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_self_test_function(void)
{
    F_Wifi_Self_Periodic_Tx_Condition = SET;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_each_data_control( U8 mu8_data )
{
    F_Wifi_Each_Data_Tx_Condition = SET;
    gu8_change_data = mu8_data;

    /*..hui [23-6-28���� 11:01:09] ��ǰ���� ���� ����� ���� �����Ҷ�..*/
    /*WifiSendDataControl(WIFI_DATA_FUNCTION_CONTROL, mu8_data);*/

    /*..hui [23-7-21���� 6:55:28] ���� ���� ����ÿ���..*/
    /*..hui [23-7-21���� 6:56:10] ���� ���� ����ÿ��� ��ü �����͵� �Բ� ����.. �հ���..*/
    send_wifi_system_function();

    /*..hui [24-1-9���� 1:29:37] 1010������ 1014���� ������ ���� �ʱ�ȭ�ϱ����� ī��Ʈ �ʱ�ȭ..*/
    if( gu8_change_data == WIFI_FUNC_000D_WATER_OUTQUANTITY )
    {
        gu8_wifi_water_send_count = 0;
    }
    else if( gu8_change_data == WIFI_FUNC_0030_ICE_MAKETIME )
    {
        gu8_wifi_ice_send_count = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void send_wifi_water_select_data_control( U8 mu8_data )
{
    F_Wifi_Each_Data_Tx_Condition = SET;
    gu8_change_data = mu8_data;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_wifi_auto_drain_state(void)
{
    #if 0
    if( bit_auto_drain_start == SET )
    {
        if( gu8_wifi_auto_drain_op == WIFI_AUTO_DRAIN_OPERATION_OFF )
        {
            gu8_wifi_auto_drain_op = WIFI_AUTO_DRAIN_OPERATION_ON;
            send_wifi_system_function();
        }
        else
        {
            if( gu8_wifi_auto_drain_op == WIFI_AUTO_DRAIN_OPERATION_ON )
            {
                gu8_wifi_auto_drain_op = WIFI_AUTO_OPERATION_GOING;
                send_wifi_system_function();
            }
            else{}
        }
    }
    else
    {
        if( gu8_wifi_auto_drain_op != WIFI_AUTO_DRAIN_OPERATION_OFF )
        {
            gu8_wifi_auto_drain_op = WIFI_AUTO_DRAIN_OPERATION_OFF;
            send_wifi_system_function();
        }
        else{}
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_wifi_uv_state(void)
{
    #if 0
    /*..hui [21-9-9���� 10:23:49] �Ͻ� �����߿��� 0���� ������ ������Ҷ� �ٽ�~..*/
    if( F_UV_Control_State == SET && u8UvSensorOFF == 0 )
    {
        if( gu8_wifi_uv_op == WIFI_UV_OPERATION_OFF )
        {
            gu8_wifi_uv_op = WIFI_UV_OPERATION_ON;
            send_wifi_system_function();
        }
        else
        {
            if( gu8_wifi_uv_op == WIFI_UV_OPERATION_ON )
            {
                gu8_wifi_uv_op = WIFI_UV_OPERATION_GOING;
                send_wifi_system_function();
            }
            else{}
        }
    }
    else
    {
        if( gu8_wifi_uv_op != WIFI_UV_OPERATION_OFF )
        {
            gu8_wifi_uv_op = WIFI_UV_OPERATION_OFF;
            send_wifi_system_function();
        }
        else{}
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_out_time(void)
{
    /*..hui [23-8-2���� 4:48:04] ��ũ�� ���� �ð��� ���..*/
    if( F_IceOut == SET && pMOTOR_ICE_OUT_CCW == SET )
    {
        gu32_wifi_ice_out_time++;

        if( gu32_wifi_ice_out_time >= MAX_ICE_OUT_TIME )
        {
            gu32_wifi_ice_out_time = MAX_ICE_OUT_TIME;
        }
        else{}

        bit_first_ice_send = SET;
    }
    else
    {
        if( gu32_wifi_ice_out_time >= 5 )
        {
            if( bit_first_ice_send == SET )
            {
                bit_first_ice_send = CLEAR;
                /*send_wifi_system_function();*/

                send_wifi_each_data_control( WIFI_FUNC_0030_ICE_MAKETIME );
            }
            else{}
        }
        else
        {
            gu32_wifi_ice_out_time = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_ice_out_time(void)
{
    gu32_wifi_ice_out_time = 0;

}


#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_water_level_state(void)
{
    /*..hui [23-6-23���� 4:45:23] �ü� ������/��������..*/
    /*..hui [23-6-23���� 4:45:35] �巹����ũ ������/�������� water_level ���ʿ��� ó��..*/
    check_cold_tank_low_level_state();
    check_cold_tank_high_level_state();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_cold_tank_low_level_state(void)
{
    if( pLEVEL_PURIFY_LOW == SET )
    {
        gu8_wifi_cold_low_on_timer++;
        gu8_wifi_cold_low_off_timer = 0;

        if( gu8_wifi_cold_low_on_timer >= 20 )
        {
            gu8_wifi_cold_low_on_timer = 20;

            if( bit_wifi_cold_low == CLEAR )
            {
                bit_wifi_cold_low = SET;
                send_wifi_system_function();
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_wifi_cold_low_on_timer = 0;
        gu8_wifi_cold_low_off_timer++;

        if( gu8_wifi_cold_low_off_timer >= 20 )
        {
            gu8_wifi_cold_low_off_timer = 20;

            if( bit_wifi_cold_low == SET )
            {
                bit_wifi_cold_low = CLEAR;
                send_wifi_system_function();
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
void check_cold_tank_high_level_state(void)
{
    if( pLEVEL_PURIFY_HIGH == SET )
    {
        gu8_wifi_cold_high_on_timer++;
        gu8_wifi_cold_high_off_timer = 0;

        if( gu8_wifi_cold_high_on_timer >= 20 )
        {
            gu8_wifi_cold_high_on_timer = 20;

            if( bit_wifi_cold_high == CLEAR )
            {
                bit_wifi_cold_high = SET;
                send_wifi_system_function();
            }
            else{}
        }
        else{}
    }
    else
    {
        gu8_wifi_cold_high_on_timer = 0;
        gu8_wifi_cold_high_off_timer++;

        if( gu8_wifi_cold_high_off_timer >= 20 )
        {
            gu8_wifi_cold_high_off_timer = 20;

            if( bit_wifi_cold_high == SET )
            {
                bit_wifi_cold_high = CLEAR;
                send_wifi_system_function();
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
void wifi_ice_tank_ster_state(void)
{
    if( bit_ice_tank_ster_start == SET )
    {
        if( bit_wifi_ice_tank_ster_old == CLEAR )
        {
            bit_wifi_ice_tank_ster_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_ice_tank_ster_old == SET )
        {
            bit_wifi_ice_tank_ster_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_hot_heater_state(void)
{
	//�����¼� ����̱� ������ �ʿ����
	#if 0
    /*if( pHEATER_HOT == SET )*/
    if( F_Heater_Output == SET )
    {
        gu32_hot_target_reach_timer_ms++;

        if( gu32_hot_target_reach_timer_ms >= 99990 )
        {
            gu32_hot_target_reach_timer_ms = 99990;
        }
        else{}

        gu16_hot_target_reach_timer_sec = (U16)(gu32_hot_target_reach_timer_ms / 10);

        if( bit_wifi_hot_heater == CLEAR )
        {
            bit_wifi_hot_heater = SET;
            bit_wifi_heater_on_time_update = CLEAR;
            send_wifi_system_function();

            init_wifi_hot_heater();
        }
        else{}
    }
    else
    {
        if( bit_wifi_hot_heater == SET )
        {
            bit_wifi_hot_heater = CLEAR;
            bit_wifi_heater_on_time_update  = SET;
            send_wifi_system_function();
        }
        else{}
    }
	#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_hot_heater(void)
{
    gu32_hot_target_reach_timer_ms = 0;
    gu16_hot_target_reach_timer_sec = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_comp_state(void)
{
    if( F_Comp_Output == SET )
    {
        if( Bit0_Cold_Mode_On_State == SET )
        {
            gu32_cold_target_reach_timer_ms++;

            if( gu32_cold_target_reach_timer_ms >= 99990 )
            {
                gu32_cold_target_reach_timer_ms = 99990;
            }
            else{}

            gu16_cold_target_reach_timer_sec = (U16)(gu32_cold_target_reach_timer_ms / 10);
        }
        else
        {
            gu32_cold_target_reach_timer_ms = 0;
            gu16_cold_target_reach_timer_sec = 0;
        }

        if( bit_wifi_comp == CLEAR )
        {
            bit_wifi_comp = SET;
            bit_wifi_comp_on_time_update = CLEAR;
            send_wifi_system_function();

            init_wifi_comp();
        }
        else{}
    }
    else
    {
        if( bit_wifi_comp == SET )
        {
            bit_wifi_comp = CLEAR;
            bit_wifi_comp_on_time_update = SET;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_comp(void)
{
    gu32_cold_target_reach_timer_ms = 0;
    gu16_cold_target_reach_timer_sec = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_full(void)
{
    if( F_IceFull == SET )
    {
        if( bit_wifi_ice_full_old == CLEAR )
        {
            bit_wifi_ice_full_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_ice_full_old == SET )
        {
            bit_wifi_ice_full_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �����ʿ�!
***********************************************************************************************************************/
void wifi_ice_step(void)
{
    if( gu8IceStep == STATE_0_STANDBY )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_MAKING_STANDBY )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_MAKING_STANDBY;
            gu8_wifi_ice_make_state_timer = 0;
            send_wifi_system_function();
        }
        else{}
    }
    else if( gu8IceStep == STATE_20_WATER_IN_ICE_TRAY )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_TRAY_IN_START 
        && gu8_wifi_ice_make_state != WIFI_ICE_TRAY_IN_ING )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_TRAY_IN_START;
            gu8_wifi_ice_make_state_timer = 20;
            send_wifi_system_function();
        }
        else
        {
            if(gu8_wifi_ice_make_state_timer > 0)
            {
                gu8_wifi_ice_make_state_timer--;
            }
            else
            {
                gu8_wifi_ice_make_state = WIFI_ICE_TRAY_IN_ING;
            }
        }
    }
    else if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_MAKING_START 
        && gu8_wifi_ice_make_state != WIFI_ICE_MAKING_ING )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_MAKING_START;
            gu8_wifi_ice_make_state_timer = 20;
            send_wifi_system_function();
        }
        else
        {
            if(gu8_wifi_ice_make_state_timer > 0)
            {
                gu8_wifi_ice_make_state_timer--;
            }
            else
            {
                gu8_wifi_ice_make_state = WIFI_ICE_MAKING_ING;
            }
        }
    }
    else if( gu8IceStep == STATE_43_ICE_TAKE_OFF )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_TAKE_OFF_START 
        && gu8_wifi_ice_make_state != WIFI_ICE_TAKE_OFF_ING )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_TAKE_OFF_START;
            gu8_wifi_ice_make_state_timer = 20;
            send_wifi_system_function();
        }
        else
        {
            if(gu8_wifi_ice_make_state_timer > 0)
            {
                gu8_wifi_ice_make_state_timer--;
            }
            else
            {
                gu8_wifi_ice_make_state = WIFI_ICE_TAKE_OFF_ING;
            }
        }

    }
    else if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_MAKING_FINISH_START 
        && gu8_wifi_ice_make_state != WIFI_ICE_MAKING_FINISH_ING )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_MAKING_FINISH_START;
            gu8_wifi_ice_make_state_timer = 20;
            send_wifi_system_function();
        }
        else
        {
            if(gu8_wifi_ice_make_state_timer > 0)
            {
                gu8_wifi_ice_make_state_timer--;
            }
            else
            {
                gu8_wifi_ice_make_state = WIFI_ICE_MAKING_FINISH_ING;
            }
        }
    }
    #if 0
    else if( gu8IceStep == STATE_51_FINISH_ICE_MAKE )
    {
        if( gu8_wifi_ice_make_state != WIFI_ICE_MAKING_FINISH_START )
        {
            gu8_wifi_ice_make_state = WIFI_ICE_MAKING_FINISH_START;
            send_wifi_system_function();
        }
        else{}
    }
    #endif
    else
    {

    }


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void wifi_uv_water_tank_state(void)
{
    /*..hui [24-11-28���� 10:12:38] �����ΰ��� ���� �׽�Ʈ�߿��� �Ⱥ���..*/
    if( bit_uv_fault_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_uv_water_tank_out == SET )
    {
        if( bit_wifi_water_tank_uv_old == CLEAR )
        {
            bit_wifi_water_tank_uv_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_water_tank_uv_old == SET )
        {
            bit_wifi_water_tank_uv_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_uv_ice_tank_state(void)
{
    /*..hui [24-11-28���� 10:12:38] �����ΰ��� ���� �׽�Ʈ�߿��� �Ⱥ���..*/
    if( bit_uv_fault_test_start == SET )
    {
        return;
    }
    else{}

    if( bit_uv_ice_tank_out == SET )
    {
        if( bit_wifi_ice_tank_uv_old == CLEAR )
        {
            bit_wifi_ice_tank_uv_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_ice_tank_uv_old == SET )
        {
            bit_wifi_ice_tank_uv_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_uv_ice_tray_state(void)
{
    /*..hui [24-11-28���� 10:12:38] �����ΰ��� ���� �׽�Ʈ�߿��� �Ⱥ���..*/
    if( bit_uv_fault_test_start == SET )
    {
        return;
    }
    else{}

    /*if( bit_uv_ice_tray_out == SET )*/
    if( bit_uv_ice_tray_out == SET && bit_ice_tray_making_enable == CLEAR )
    {
        if( bit_wifi_ice_tray_uv_old == CLEAR )
        {
            bit_wifi_ice_tray_uv_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_ice_tray_uv_old == SET )
        {
            bit_wifi_ice_tray_uv_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
void wifi_uv_ice_tank_front_state(void)
{
    /*..hui [24-11-28���� 10:12:38] �����ΰ��� ���� �׽�Ʈ�߿��� �Ⱥ���..*/
    if( bit_uv_fault_test_start == SET )
    {
        return;
    }
    else{}

    /*if( bit_uv_ice_tank_front_out == SET )*/
    if( bit_uv_ice_tank_front_out == SET && bit_ice_tray_making_enable == CLEAR )
    {
        if( bit_wifi_ice_tank_front_uv_old == CLEAR )
        {
            bit_wifi_ice_tank_front_uv_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_ice_tank_front_uv_old == SET )
        {
            bit_wifi_ice_tank_front_uv_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_no_use_save_mode(void)
{
    if( bit_9_hour_no_use_start == SET )
    {
        if( bit_wifi_no_use_save_old == CLEAR )
        {
            bit_wifi_no_use_save_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_no_use_save_old == SET )
        {
            bit_wifi_no_use_save_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ice_data_all(void)
{
    /*..hui [23-8-29���� 4:55:49] ���� �Ϸ�ð� / Ż�� �Ϸ�ð� / Ʈ���� �Լ� �ð� / Ʈ���� �Լ� ���� ����..*/
    /*..hui [23-8-29���� 4:55:54] ���� ������ �ѹ濡..*/
    if( gu8IceStep == STATE_50_ICE_FULL_IR_CHECK )
    {
        if( bit_wifi_ice_data_send == CLEAR )
        {
            bit_wifi_ice_data_send = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        bit_wifi_ice_data_send = CLEAR;

        if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP && gu8IceStep <= STATE_14_CHECK_ICE_TRAY_HZ )
        {
            init_wifi_ice_data_all();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_ice_data_all(void)
{
    gu32_wifi_ice_make_time = 0;
    gu32_wifi_hot_gas_time = 0;
    gu16_wifi_tray_in_time = 0;
    gu16_wifi_tray_in_flow = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_flushing(void)
{
    if( gu8_flushing_mode == FLUSHING_NONE_STATE )
    {
        if( gu8_wifi_flushing_state != WIFI_FLUSHING_OFF )
        {
            gu8_wifi_flushing_state = WIFI_FLUSHING_OFF;
        }
        else{}
    }
    else if( gu8_flushing_mode == FLUSHING_STANDBY_STATE )
    {
        if( gu8_wifi_flushing_state != WIFI_FLUSHING_OFF )
        {
            /*..hui [23-8-31���� 1:49:02] �Ͻ������������� ��� going �����ִ°ɷ�.. �ռ�������..*/
            if( gu8_wifi_flushing_state != WIFI_FLUSHING_GOING )
            {
                gu8_wifi_flushing_state = WIFI_FLUSHING_OFF;
            }
            else{}
        }
        else{}
    }
    else if( gu8_flushing_mode == FLUSHING_FILTER 
    || gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_START_STATE 
    || gu8_flushing_mode == FLUSHING_FILL_COLD_TANK_FINISH_STATE
    || gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE
    || gu8_flushing_mode == FLUSHING_COLD_TANK )
    {
        if( gu8_wifi_flushing_state != WIFI_FLUSHING_ON && gu8_wifi_flushing_state != WIFI_FLUSHING_GOING )
        {
            gu8_wifi_flushing_state = WIFI_FLUSHING_ON;
            send_wifi_system_function();
        }
        else
        {
            /* IotĿ��Ʈ���������� �˾Ƽ� "2 (going)" �����Ƿ� ���� */
            // gu8_wifi_flushing_state = WIFI_FLUSHING_GOING;
        }
    }
    else if( gu8_flushing_mode == FLUSHING_FINISH_STATE )
    {
        if( gu8_wifi_flushing_state != WIFI_FLUSHING_DONE )
        {
            gu8_wifi_flushing_state = WIFI_FLUSHING_DONE;
            send_wifi_system_function();
        }
        else{}
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_no_use_time(void)
{
    if( gu8_wifi_no_use_key == SET )
    {
        gu8_wifi_no_use_key = 0;

        if( gu16_wifi_no_use_timer_min >= 10 )
        {
            send_wifi_system_function();
            gu8_wifi_no_use_time_send = SET;
        }
        else{}
    }
    else{}

    gu16_wifi_no_use_timer_sec++;

    if( gu16_wifi_no_use_timer_sec >= 600 )
    {
        gu16_wifi_no_use_timer_sec = 0;

        if( gu16_wifi_no_use_timer_min < 65535 )
        {
            gu16_wifi_no_use_timer_min++;
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void init_wifi_no_use_time(void)
{
    gu16_wifi_no_use_timer_sec = 0;
    gu16_wifi_no_use_timer_min = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_smart_save_state(void)
{
    if( gu8_smart_operation_mode_old != gu8_smart_operation_mode )
    {
        gu8_smart_operation_mode_old = gu8_smart_operation_mode;

        send_wifi_system_function();
        bit_smart_first_send = SET;
    }
    else{}
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_sleep_mode(void)
{
    if( bit_sleep_mode_start == SET )
    {
        if( bit_wifi_sleep_old == CLEAR )
        {
            bit_wifi_sleep_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( bit_wifi_sleep_old == SET )
        {
            bit_wifi_sleep_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_neo_filter_alarm(void)
{
    if( bit_wifi_neo_filter_1_alarm == SET )
    {
        if( bit_wifi_neo_alarm_old == CLEAR )
        {
            bit_wifi_neo_alarm_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        bit_wifi_first_neo_alarm = CLEAR;

        if( bit_wifi_neo_alarm_old == SET )
        {
            bit_wifi_neo_alarm_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ro_filter_alarm(void)
{
    if( bit_wifi_ro_filter_2_alarm == SET )
    {
        if( bit_wifi_ro_alarm_old == CLEAR )
        {
            bit_wifi_ro_alarm_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        bit_wifi_first_ro_alarm = CLEAR;

        if( bit_wifi_ro_alarm_old == SET )
        {
            bit_wifi_ro_alarm_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_ino_filter_alarm(void)
{
    if( bit_wifi_ino_filter_3_alarm == SET )
    {
        if( bit_wifi_ino_alarm_old == CLEAR )
        {
            bit_wifi_ino_alarm_old = SET;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        bit_wifi_first_ino_alarm = CLEAR;

        if( bit_wifi_ino_alarm_old == SET )
        {
            bit_wifi_ino_alarm_old = CLEAR;
            send_wifi_system_function();
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_neo_ino_filter_alarm_start(void)
{
    bit_wifi_neo_filter_1_alarm = SET;
    bit_wifi_ino_filter_3_alarm = SET;

    bit_wifi_first_neo_alarm = CLEAR;
    bit_wifi_first_ino_alarm = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_neo_ino_filter_alarm_stop(void)
{
    bit_wifi_neo_filter_1_alarm = CLEAR;
    bit_wifi_ino_filter_3_alarm = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_neo_ro_ino_filter_alarm_start(void)
{
    bit_wifi_neo_filter_1_alarm = SET;
    bit_wifi_ro_filter_2_alarm = SET;
    bit_wifi_ino_filter_3_alarm = SET;

    bit_wifi_first_neo_alarm = CLEAR;
    bit_wifi_first_ro_alarm = CLEAR;
    bit_wifi_first_ino_alarm = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void wifi_neo_ro_ino_filter_alarm_stop(void)
{
    bit_wifi_neo_filter_1_alarm = CLEAR;
    bit_wifi_ro_filter_2_alarm = CLEAR;
    bit_wifi_ino_filter_3_alarm = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_self_manual_state(void)
{
    check_prohibit_state();

    /*..hui [21-9-8���� 10:54:00] �ڰ����� ���� �����ΰ�� ����..*/
    if( gu8_wifi_self_test_state == WIFI_SELF_TEST_PROHIBIT )
    {
        bit_self_test_start = CLEAR;
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        switch( gu8_wifi_self_test_state )
        {
            case WIFI_SELF_TEST_NO_OPERATION:

                gu8_wifi_self_test_state = WIFI_SELF_TEST_START;
                gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;
                /*..hui [21-9-8���� 10:23:33] �����ϸ� �ڵ����� ���������ʿ��� ����..*/
                /*send_wifi_system_function();*/

                gu8_wifi_self_test_timer = 0;

            break;

            case WIFI_SELF_TEST_START:

                gu8_wifi_self_test_timer++;

                if( gu8_wifi_self_test_timer >= 3 )
                {
                    gu8_wifi_self_test_timer = 3;

                    /*if( gu8_self_test_manual_step >= 4 )*/
                    if( gu8_self_test_manual_step >= 4 )
                    {
                        gu8_wifi_self_test_timer = 0;
                        gu8_wifi_self_test_state = WIFI_SELF_TEST_ING;
                        gu8_wifi_self_test_progress = WIFI_SELF_TEST_10_PERCENT;
                        send_wifi_system_function();
                    }
                    else{}
                }
                else{}

            break;

            case WIFI_SELF_TEST_ING:

                if( gu8_self_test_manual_step == 4 )
                {
                    if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_10_PERCENT )
                    {
                        if( gu8_component_test_step >= 4 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_20_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_20_PERCENT )
                    {
                        if( gu8_component_test_step >= 7 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_30_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_30_PERCENT )
                    {
                        if( gu8_component_test_step >= 10 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_40_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_40_PERCENT )
                    {
                        if( gu8_component_test_step >= 13 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_50_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_50_PERCENT )
                    {
                        if( gu8_component_test_step >= 16 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_60_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_60_PERCENT )
                    {
                        if( gu8_component_test_step >= 18 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_70_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_70_PERCENT )
                    {
                        if( gu8_component_test_step >= 21 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_80_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_80_PERCENT )
                    {
                        if( gu8_component_test_step >= 24 )
                        {
                            gu8_wifi_self_test_progress = WIFI_SELF_TEST_90_PERCENT;
                            send_wifi_system_function();
                        }
                        else{}
                    }
                    else{}
                }
                else if( gu8_self_test_manual_step == 5 )
                {
                    if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_90_PERCENT )
                    {
                        gu8_wifi_self_test_progress = WIFI_SELF_TEST_100_PERCENT;
                        send_wifi_system_function();
                    }
                    else if( gu8_wifi_self_test_progress == WIFI_SELF_TEST_100_PERCENT )
                    {
                        gu8_wifi_self_test_state = WIFI_SELF_TEST_FINISH;
                        gu8_wifi_self_test_progress = WIFI_SELF_TEST_100_PERCENT;
                        send_wifi_system_function();
                    }
                    else{}
                }
                else{}

            break;

            case WIFI_SELF_TEST_FINISH:

                if( bit_wifi_self_test_finish == CLEAR )
                {
                    /*..hui [21-9-7���� 4:26:34] ���� ��� ����Ÿ ����..*/
                    bit_wifi_self_test_finish = SET;
                }
                else{}

            break;

            case WIFI_SELF_TEST_STOP:


            break;

            default:


            break;
        }
    }
    else
    {
        /*..hui [21-9-7���� 4:20:42] ������ 0�� �Ⱥ����൵ ��..*/
        gu8_wifi_self_test_timer = 0;
        gu8_wifi_self_test_state = WIFI_SELF_TEST_NO_OPERATION;
        gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;


        /*..hui [21-9-9���� 4:11:13] ���� ��������͸� ���⼭ �����°ɷ�....*/
        /*..hui [21-9-9���� 4:11:29] ���� ��������� ������ wifi �ʿ��� �����뺸 �ڵ����� �ϴ� �� ����.....*/
        if( bit_wifi_self_test_finish == SET )
        {
            bit_wifi_self_test_finish = CLEAR;
            send_wifi_manual_test_function();
        }
        else{}
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_prohibit_state(void)
{
    #if 1
    /*..hui [23-12-22���� 10:28:58] �÷��� ���϶� ����..*/
    /*..hui [24-3-25���� 4:02:20] ������� �����߿��� ����..*/
    if( gu8_flushing_mode == FLUSHING_NONE_STATE
        && gu8_Led_Display_Step != LED_Display__SETTING
        && bit_ice_tank_ster_start == CLEAR
        && F_IceOut == CLEAR
        && bit_filter_all == SET)
    {
        if( F_Wifi_Flushing == SET && F_WaterOut != SET && F_IceOut != SET )
        {
            F_Wifi_Flushing = CLEAR;

            gu8_wifi_self_test_state = WIFI_SELF_TEST_NO_OPERATION;
            gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;
            send_wifi_system_function();
        }
        else{}
    }
    else
    {
        if( F_Wifi_Flushing == CLEAR )
        {
            F_Wifi_Flushing = SET;

            gu8_wifi_self_test_state = WIFI_SELF_TEST_PROHIBIT;
            gu8_wifi_self_test_progress = WIFI_SELF_TEST_0_PERCENT;
            send_wifi_system_function();
        }
        else{}
    }
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


