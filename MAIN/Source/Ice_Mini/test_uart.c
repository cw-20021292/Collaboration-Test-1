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
#include    "test_uart.h"

void uart_test_mode_decision(void);
void TestUartStart(void);
void Uart_Test_Main(void);
void factory_test(void);
void test_uart_input(void);
void input_uart_level(void);
void input_uart_drain_level(void);
void input_uart_leakage(void);
void input_uart_ice_sensor(void);
void input_ice_lack(void);
void input_ice_full(void);
void input_drain_pump_ad(void);
void input_uart_uv(void);
void input_reed_sw(void);
void test_uart_ice_tray(void);
void input_uart_flow(void);
void test_comp_control(void);
void test_extract(void);
void test_hot_flow_motor(void);
void test_uart_ice_door_heater(void);
void motor_test(void);
void check_off_ad(void);
void uart_start_input_check(U8 mu8_onoff, U8 mu8_num );
void display_led_factory(void);
void display_factory_1_mode(void);
void display_factory_2_mode(void);
void display_factory_manual_mode(void);
void motor_test_continue(void);

void initial_all_data(void);
void manual_test(void);
void manual_test_start(void);
void comp_manual_test(void);





TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Uart_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

U8 gu8R_LEV_H;
U8 gu8R_LEV_L;
U8 gu8Drain_LEV_H;
U8 gu8Drain_LEV_L;
U8 gu8Ovf_LEV;

U8 gu8_test_mode_timeout_1s;
U8 gu8_factory_test_step;

U8 gu8_uart_test_start;

U8 gu8_uart_hot_out_temp;
U8 gu8_uart_hot_heater_temp;
U8 gu8_uart_eva_first_temp;
U8 gu8_uart_eva_second_temp;
U8 gu8_uart_amb_temp;
U8 gu8_uart_cold_temp;
U8 gu8_uart_room_temp;

U8 gu8_uart_leakage;

/*U16 gu16_uart_ir_ad;*/

/* �������� */
U16 gu16_uart_ir_power_on_ad;
U16 gu16_uart_ir_power_off_ad;
U8 gu8_uart_ir_check_timer;
U8 gu8_uart_ir_off_check_timer;

/* �������� */
U16 gu16_uart_ir_ice_lack_power_on_ad;
U16 gu16_uart_ir_ice_lack_power_off_ad;
U8 gu8_uart_ir_ice_lack_check_timer;
U8 gu8_uart_ir_ice_lack_off_check_timer;

U16 gu16_uart_drain_pump_on_ad;
U16 gu16_uart_drain_pump_off_ad;

U8 gu8_uart_dpump_check_timer;

U16 gu16_uart_tray_pump_on_ad;
U16 gu16_uart_tray_pump_off_ad;

U8 gu8_uart_hpump_check_timer;

U8 gu8_uart_ir_check_timer;

U8 gu8_uart_ice_tray_up;
U8 gu8_uart_ice_trray_down;
U8 gu8_uart_ice_tray_test_step;
U16 gu16_uart_ice_tray_test_timer;

U8 gu8_uart_ice_tray_continue_step;
U16 gu16_uart_ice_tray_continue_timer;

U8 gu8_uart_uv_check_timer;

U16 gu16_uart_water_faucet_uv_on_ad;
U16 gu16_uart_ice_faucet_1_uv_on_ad;
U16 gu16_uart_ice_faucet_2_uv_on_ad;
U16 gu16_uart_ice_tank_1_2_uv_on_ad;
U16 gu16_uart_ice_tray_1_2_uv_on_ad;
U16 gu16_uart_ice_tank_3_uv_on_ad;

U16 gu16_uart_water_faucet_uv_off_ad;
U16 gu16_uart_ice_faucet_1_uv_off_ad;
U16 gu16_uart_ice_faucet_2_uv_off_ad;
U16 gu16_uart_ice_tank_1_2_uv_off_ad;
U16 gu16_uart_ice_tray_1_2_uv_off_ad;
U16 gu16_uart_ice_tank_3_uv_off_ad;

U8 gu8_uart_ice_heater;
U8 gu8_uart_ice_heater_timer;
U8 gu8_uart_ice_heater_finish;

U8 gu8_uart_hot_heater;
U8 gu8_uart_hot_heater_timer;
U8 gu8_uart_hot_heater_finish;

U8 gu8AT_Flow_1sec_All_Max;
U8 gu8AT_Flow_1sec_Ambient_Extract_Max;
U8 gu8AT_Flow_1sec_Cold_Extract_Max;
U8 gu8AT_Flow_1sec_Hot_Extract_Max;
U8 gu8AT_Flow_1sec_Real;

U8 gu8AT_Filter_Flow_1sec;

U8 gu8_flow_check_start;

U8 gu8_uart_comm_start;

U8 gu8_uart_ice_test_start;
U8 gu8_uart_ice_test_step;
U8 gu8_uart_ice_test_timer;
U8 gu8_uart_ice_result;
U8 gu8_uart_cold_result;
U8 gu8_start_temp_eva_cold;
U8 gu8_start_temp_eva_ice;

U8 gu8_uart_tray_initial;
U8 gu8_uart_tray_initial_step;
U16 gu16_uart_tray_initial_timer;
U16 gu16_uart_tray_initial_max_timer;



U8 gu8_uart_tray_finish;

U8 gu8_uart_rtc_initial;

U8 gu8_manual_test_low_level_on_cnt;
U8 gu8_manual_test_low_level_off_cnt;

U8 gu8_manual_test_start;

U16 gu16_uart_dc_fan_on_ad;
U16 gu16_uart_dc_fan_off_ad;

bit bit_flow_detect;
U8 gu8_flow_detect_timer;
bit bit_display_test_finish;
U8 gu8_display_test_delay_timer;

U8 gu8_ice_motor_test_timer;
bit bit_flow_buzzer;

bit bit_testets;

U8 gu8_uart_start_timer;

bit bit_tank_cover_one_old;
bit bit_tank_cover_two_old;

bit bit_filter_old;
bit bit_acid_old;

bit bit_uart_tank_cover_reed_two;

bit bit_uart_filter_reed;
bit bit_uart_filter_cover_reed;

bit bit_uart_acid_reed_1;
bit bit_uart_acid_reed_final;

bit bit_manual_test_start;

U16 gu16_manaul_comp_delay_timer;

bit bit_manual_test_first;

U8 gu8_check_off_ad_timer;

U8 gu8_eeprom_test_timer;

U16 gu16_uart_test_pulse;

/////U16 gu16_uart_tds_in_max;
/////U16 gu16_uart_tds_out_max;
U8 gu8_uart_bldc_comm_error;

U8 gu8_github_test;

U8 gu8_test_water_out;
U8 gu8_uart_extract_limit_timer;

U8 gu8_uart_ice_test_input;
U8 gu8_uart_ice_water_test_input;
U8 gu8_uart_hot_test_input;
U8 gu8_uart_purify_test_input;
U8 gu8_uart_cold_test_input;
U8 gu8_uart_amount_test_input;

U8 gu8_uart_setting_ice_size_test_input;
U8 gu8_uart_setting_ice_off_test_input;
U8 gu8_uart_setting_hot_lock_test_input;
U8 gu8_uart_setting_fast_ice_test_input;
U8 gu8_uart_setting_cold_temp_test_input;
U8 gu8_uart_setting_sleep_mode_test_input;
U8 gu8_uart_setting_ice_lock_test_input;
U8 gu8_uart_setting_all_lock_test_input;
U8 gu8_uart_setting_my_test_input;  /* MY ����Ű �߰� 250213 @CH.PARK */
U8 gu8_uart_setting_cold_off_input; /* �ü�OFF ����Ű �߰� 250213 @CH.PARK */

bit bit_uart_purify_extract_finish;
bit bit_uart_cold_extract_finish;
bit bit_uart_hot_extract_finish;

U8 gu8_uart_start_hour;
U8 gu8_uart_start_min;
U8 gu8_uart_start_sec;

U8 gu8_uart_flow_timer;

U16 gu16_uart_key_check;

bit bit_hot_flow_continue;
bit bit_ice_door_continue;
bit bit_ice_select_continue;    /* ���̽� ����Ʈ ���� �߰� 250311 CH.PARK */
bit bit_ice_tray_continue;

U8 gu8_tray_continue_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//
void uart_test_mode_decision(void)
{
    /*..hui [17-12-28���� 10:45:49] PCB �׽�Ʈ ��� ���� ���¿����� ���� �Ұ�..*/
    if(gu8_test_mode_timeout_1s == 0 || u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    gu8_uart_start_timer++;

    if( gu8_uart_start_timer >= 30 )
    {
        gu8_uart_start_timer = 30;
    }
    else
    {
        return;
    }

    /*..hui [23-3-14���� 4:47:45] ������� �����ϱ⶧���� ..*/
    AT_UART_Communication();

    /*..hui [20-1-20���� 8:58:56] ���� �д½ð� ���, ���� ���÷��� �Ϸ�� �� ����..*/
    /* �����˻� : �˻��� 1 ���� */
    if( (gu16ADLeakage >= 750)
    && (F_FW_Version_Display_Mode == SET)
    && (gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST || gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST) 
    )
    {
        gu8_uart_test_start = SET;
        TestUartStart();
    }
    else
    {
        gu8_uart_test_start = CLEAR;
    }

    #ifdef __UART_TEST_MODE__
    gu8_uart_test_start = SET;
    TestUartStart();
    #endif

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void TestUartStart(void)
{
    /*play_melody_select_196();*/
    play_voice_test_mode_151();

    UARTest_NO_LOAD_Set();
    AT_gu8TX_ERROR = 0;
    AT_F_Rx_NG = 0;
    gu8_test_mode_timeout_1s = 0;
    gu8_factory_test_step = 0;
    u8FactoryTestMode = UART_TEST_MODE;

    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [19-11-5���� 5:57:28] EEPROM / RTC �ð� �ʱ�ȭ..*/
    gu8_initial_all_data = 1;

    /*..hui [20-1-14���� 8:15:16] 12V ���� ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    gu8_uart_ice_heater = CLEAR;
    gu8_uart_ice_heater_finish = CLEAR;
    gu8_uart_hot_heater = CLEAR;
    gu8_uart_hot_heater_finish = CLEAR;

    bit_flow_detect = CLEAR;

    bit_uart_ice_test_finish = CLEAR;
    bit_uart_ice_water_test_finish = CLEAR;
    bit_uart_hot_test_finish = CLEAR;
    bit_uart_ambient_test_finish = CLEAR;
    bit_uart_cold_tst_finish = CLEAR;
    bit_uart_amount_test_finish = CLEAR;
    bit_uart_ice_size_test_finish = CLEAR;
    bit_uart_ice_off_test_finish = CLEAR;
    bit_uart_hot_lock_test_finish = CLEAR;
    bit_uart_fast_ice_test_finish = CLEAR;
    bit_uart_cold_temp_test_finish = CLEAR;
    bit_uart_sleep_mode_test_finish = CLEAR;
    bit_uart_my_test_finish = CLEAR;
    bit_uart_cold_off_finish = CLEAR;

    bit_uart_water_extract_test_finish = CLEAR;
    bit_uart_ice_lock_test_finish = CLEAR;
    bit_uart_all_lock_test_finish = CLEAR;


    gu8_uart_ice_tray_test_step = 0;
    gu16_uart_ice_tray_test_timer = 0;
    gu8_eeprom_test_timer = 0;

    gu8_uart_ice_tray_continue_step = 0;
    gu16_uart_ice_tray_continue_timer = 0;

    F_ErrTrayMotor_DualInital = CLEAR;

    /*..hui [21-2-18���� 5:08:19] WIFI ���� �˻� �߰�..*/
    //WifiKey(WIFI_KEY_TEST);
	SetWifiSystemStatus(WIFI_FACTORY_STATUS, SET);

    gu8_uart_comp_start = 0;
    gu8_uart_comp_rps = 0;

    ///////////all_breath_stop();

    /*..hui [23-7-3���� 2:20:40] ���� ��а˻���..*/
    if( bit_manual_test_start == SET )
    {
        gu8_uart_test_mode = INCLUDE_FRNOT_UART_TEST;
        gu8_factory_test_step = 2;
        off_all_control_led();

        GasSwitchInit();

        /*..hui [23-7-6���� 12:34:20] ó���� ���� �ٷ� �����ǰ�..*/
        gu16_manaul_comp_delay_timer = COMP_START_TIME;

        gu8_icewater_test_input = 0;
        gu8_ice_test_input = 0;
        gu8_cold_test_input = 0;
        gu8_hot_test_input = 0;

        bit_manual_test_first = SET;
    }
    else{}

    gu16_uart_ir_power_off_ad = 1024;

    gu16_uart_water_faucet_uv_off_ad = 1024;
    gu16_uart_ice_faucet_1_uv_off_ad = 1024;
    gu16_uart_ice_faucet_2_uv_off_ad = 1024;
    gu16_uart_ice_tray_1_2_uv_off_ad = 1024;
    gu16_uart_ice_tank_1_2_uv_off_ad = 1024;
    gu16_uart_ice_tank_3_uv_off_ad = 1024;      /* 2kg �߰� 250226 CH.PARK */

    gu16_uart_drain_pump_off_ad = 1024;
    gu16_uart_tray_pump_off_ad = 1024;
    gu16_uart_dc_fan_off_ad = 1024;

    /* �������� �߰� */
    gu16_Door_Heater_IAD_OFF_Data = 1024;
    gu16_Door_Heater_IAD_ON_Data = 0;

    gu8AT_Flow_1sec_All_Max = 0;
    gu8AT_Flow_1sec_Ambient_Extract_Max = 0;
    gu8AT_Flow_1sec_Cold_Extract_Max = 0;
    gu8AT_Flow_1sec_Hot_Extract_Max = 0;
    gu8AT_Flow_1sec_Real = 0;

    gu8_uart_bldc_comm_error = CLEAR;

    gu8_test_water_out = CLEAR;
    gu8_uart_hot_test_input = 0;
    gu8_uart_purify_test_input = 0;
    gu8_uart_cold_test_input = 0;

    bit_uart_purify_extract_finish = CLEAR;
    bit_uart_cold_extract_finish = CLEAR;
    bit_uart_hot_extract_finish = CLEAR;

    /* �ڵ������˻��� �����ϱ� ���� NOS��� ������ ���� ���� 250321 CH.PARK */
    pVALVE_NOS = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_Test_Main(void)
{
    all_duty_100_percent();

    led_blink_timer();

    ProcessRtc();

    if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST )
    {
        if( gu8_factory_test_step == 0 )
        {
            /*uart_mode_display_test();*/
            bit_display_test_finish = SET;
        }
        else if( gu8_factory_test_step == 1 )
        {
            /*..hui [23-3-15���� 2:28:58] ��� �׽�Ʈ �����ϸ� FND, LED ��ü �� �Ѵ°ɷ�..*/
            ///Bit0_Front_Left_Led_Ice_Full_Text ^= SET;
            fnd_left_uart_test();
            fnd_right_uart_test();
        }
        else
        {
            if( bit_manual_test_start == CLEAR )
            {
                off_all_control_led();
                fnd_left_uart_test();
                fnd_right_uart_test();
            }
            else
            {
                if( bit_manual_test_first == SET )
                {
                    off_all_control_led();
                    bit_manual_test_first = CLEAR;
                }
                else{}
            }
        }
    }
    else
    {
        /*off_all_control_led();*/
        fnd_left_uart_test();
        fnd_right_uart_test();
        bit_display_test_finish = SET;
    }

    /*..hui [23-3-14���� 5:47:23] ������ �Է�..*/
    test_uart_input();

    /*..hui [23-3-14���� 5:47:39] �˻� �����ϸ� ���̽�Ʈ���� �÷ȴ� ����..*/
    test_uart_ice_tray();

    /* ���̽����� ���� �߰� */
    test_uart_ice_door_heater();

    /*..hui [23-3-14���� 5:48:41] ���� �� �ð� �׽�Ʈ�� �׺����� �ϴ°ɷ� ����..*/
    /*test_ice_system();*/
    ControlGasSwitch();

    /*..hui [23-3-14���� 5:48:46] EEPROM ����Ÿ �ʱ�ȭ..*/
    initial_all_data();

    /*..hui [22-8-17���� 10:49:14] ��õ���� �����˻��� �߰�..*/
    /*..hui [23-3-22���� 1:35:05] �����˻� ��� ����.. �������.. ������ ���� ������ �ǵ� OPEN��..*/
    /*input_manual_test();*/

    /* ����Ʈ���� ���� �Լ� �߰� 250425 CH.PARK */
    inverse_direction_time_check();
    check_error_micro_sw_movement();
    control_ice_tray();

    gu8_eeprom_test_timer++;

    if( gu8_eeprom_test_timer >= 20 )
    {
        gu8_eeprom_test_timer = 20;
        eeprom_test();
    }
    else{}

    ControlFlow();

    /*..hui [19-7-22���� 7:36:53] ��������..*/
    calculate_flow_input();

    /*..hui [25-1-23���� 7:34:11] �� ���� �׽�Ʈ..*/
    test_extract();
    test_hot_flow_motor();

    /*..hui [25-1-23���� 7:36:40] ���� üũ..*/
    input_uart_flow();

    test_comp_control();


    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    factory_test();
    display_led_factory();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void factory_test(void)
{
    switch(gu8_factory_test_step)
    {
        case 0:         /* �˻� 1��� */

            motor_test();
            
            if((bit_uart_tank_cover_reed_two == SET)        // ��ũĿ�� �̰���->����
            && (bit_uart_filter_reed == SET)                // ���͸��� �̰���->����
            && (gu16_uart_key_check == 0x07)                // �ÿ��� ���� ���� 0x32 �̻� ����
            && (gu16ADLeakage < 50)                         // ���� �̰���
            )
            {
                /* �����˻� 2��� ���� ���� */
                UARTest_NO_LOAD_Set();
                gu8_factory_test_step++;

                F_GasSwitch_Initial = CLEAR;
                GasSwitchInit();

                off_all_control_led();
                gu8_check_off_ad_timer = 0;

                gu8_uart_start_hour = gu8_rtc_time_Hour;
                gu8_uart_start_min = gu8_rtc_time_Min;
                gu8_uart_start_sec = gu8_rtc_time_Sec;
            }
            else{}

            #ifdef __UART_TEST_MODE__
            UARTest_NO_LOAD_Set();
            // gu8_factory_test_step++;

            F_GasSwitch_Initial = CLEAR;
            GasSwitchInit();

            // off_all_control_led();
            gu8_check_off_ad_timer = 0;

            gu8_uart_start_hour = gu8_rtc_time_Hour;
            gu8_uart_start_min = gu8_rtc_time_Min;
            gu8_uart_start_sec = gu8_rtc_time_Sec;
            #endif

            break;


        case 1:         /* �˻� 2��� (�ڵ������˻�) */
            #ifdef __UART_TEST_MODE__
            bit_hot_flow_continue = SET;
            bit_ice_door_continue = SET;
            bit_ice_select_continue = SET;
            bit_ice_tray_continue = SET;
            #endif

            check_off_ad();
            AT_UART_Communication();
            UARTest_RUN();
            motor_test_continue();

            if(F_Uart_Final == SET)
            {
                UARTest_NO_LOAD_Set();
                off_all_control_led();
                gu8_factory_test_step++;
            }
            else{}

            break;

        case 2:

            // ���
            manual_test();
            comp_manual_test();
            fnd_left_uart_test();
            fnd_right_uart_test();

            break;

        default:

            gu8_factory_test_step = 0;

            break;
    }






}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_input(void)
{
    input_uart_level();

    /*..hui [19-10-28���� 2:17:55] ���� ���� ����..*/
    input_uart_ice_sensor();

    input_uart_uv();

    input_reed_sw();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_level(void)
{
    /*..hui [19-6-26���� 1:54:08] �������� �Է�..*/
    input_uart_drain_level();
    /*..hui [19-10-28���� 1:16:52] �������� �Է�..*/
    input_uart_leakage();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_drain_level(void)
{
    if( pLEVEL_ICE_DRAIN_HIGH == SET )
    {
        gu8Drain_LEV_H = 0;
    }
    else
    {
        gu8Drain_LEV_H = 1;
    }

    if( pLEVEL_ICE_DRAIN_LOW == SET )
    {
        gu8Drain_LEV_L = 0;
    }
    else
    {
        gu8Drain_LEV_L = 1;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_leakage(void)
{
    /* 5. ���� ���� - Ŀ���� Short �˻� */
    if( gu16ADLeakage < 50 )
    {
        gu8_uart_leakage = 0x00;  // ����
    }
    else
    {
        gu8_uart_leakage = 0x01;  // Short
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_ice_sensor(void)
{
    input_ice_lack();   /* �������� �߰� */
    input_ice_full();
    input_drain_pump_ad();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_lack(void)
{
    #if 0
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*983 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ��Ʈ / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ��Ʈ*/
    /*on / off*/
    /*1023/ 1023*/
    #endif


    //----------------- �������� IR ����------------------------------------
    gu8_uart_ir_ice_lack_check_timer++;

    if(gu8_uart_ir_ice_lack_check_timer >= 70)
    {
        pIR_POWER2 = CLEAR;

        if( gu8_uart_ir_ice_lack_check_timer >= 90 )
        {
            gu8_uart_ir_ice_lack_check_timer = 90;

            /*..hui [23-11-15���� 1:38:56] �����߽� OFF�ϰ� AD�� üũ(��ƮȮ��)..*/
            gu8_uart_ir_ice_lack_off_check_timer++;

            if( gu8_uart_ir_ice_lack_off_check_timer < 30 )
            {
                if( gu16ADIceLow < gu16_uart_ir_ice_lack_power_off_ad )
                {
                    gu16_uart_ir_ice_lack_power_off_ad = gu16ADIceLow;
                }
                else{}
            }
            else
            {
                gu8_uart_ir_ice_lack_off_check_timer = 30;
            }
        }
        else
        {
            gu8_uart_ir_ice_lack_off_check_timer = 0;
        }

        return;
    }
    else{}

    pIR_POWER2 = SET;

    if( gu16ADIceLow > gu16_uart_ir_ice_lack_power_on_ad )
    {
        gu16_uart_ir_ice_lack_power_on_ad = gu16ADIceLow;
    }
    else{}

    gu16_uart_ir_ice_lack_power_off_ad = 1024;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_ice_full(void)
{
    #if 0
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*983 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ��Ʈ / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ����*/
    /*on / off*/
    /*0 / 0*/
    /*�߽� ���� / ���� ��Ʈ*/
    /*on / off*/
    /*1023/ 1023*/
    #endif


    //----------------- �������� IR ����------------------------------------
    gu8_uart_ir_check_timer++;

    if(gu8_uart_ir_check_timer >= 70)
    {
        pIR_POWER = CLEAR;

        if( gu8_uart_ir_check_timer >= 90 )
        {
            gu8_uart_ir_check_timer = 90;

            /*..hui [23-11-15���� 1:38:56] �����߽� OFF�ϰ� AD�� üũ(��ƮȮ��)..*/
            gu8_uart_ir_off_check_timer++;

            if( gu8_uart_ir_off_check_timer < 30 )
            {
                if( gu16ADIceFull < gu16_uart_ir_power_off_ad )
                {
                    gu16_uart_ir_power_off_ad = gu16ADIceFull;
                }
                else{}
            }
            else
            {
                gu8_uart_ir_off_check_timer = 30;
            }
        }
        else
        {
            gu8_uart_ir_off_check_timer = 0;
        }

        return;
    }
    else{}

    pIR_POWER = SET;

    if( gu16ADIceFull > gu16_uart_ir_power_on_ad )
    {
        gu16_uart_ir_power_on_ad = gu16ADIceFull;
    }
    else{}

    gu16_uart_ir_power_off_ad = 1024;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_drain_pump_ad(void)
{
    /*..hui [23-3-24���� 12:15:07] 1��忡���� ��� �����ϴ°ɷ� ����.. ���� ����� ��û..*/
    if(gu8_factory_test_step != 0)
    {
        return;
    }
    else{}

    start_drain_pump( PUMP_PWM_MAX );

    if( gu16_AD_Drain_Pump_Current > gu16_uart_drain_pump_on_ad )
    {
        gu16_uart_drain_pump_on_ad = gu16_AD_Drain_Pump_Current;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_uv(void)
{
    if( gu8_factory_test_step == 1 || gu8_factory_test_step == 2 )
    {
        gu8_uart_uv_check_timer = 0;
        pUV_LED_WATER_FAUCET = CLEAR;
        pUV_LED_ICE_FAUCET_1 = CLEAR;
        pUV_LED_ICE_FAUCET_2 = CLEAR;
        pUV_LED_ICE_TANK_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3 = CLEAR;
        pUV_LED_ICE_TRAY_1_2 = CLEAR;

        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;

        return;
    }
    else{}

    gu8_uart_uv_check_timer++;

    /*..hui [19-10-28���� 3:13:29] UV������ 3�ʸ�..*/
    if(gu8_uart_uv_check_timer >= 30)
    {
        /*gu8_uart_uv_check_timer = 30;*/
        pUV_LED_WATER_FAUCET = CLEAR;
        pUV_LED_ICE_FAUCET_1 = CLEAR;
        pUV_LED_ICE_FAUCET_2 = CLEAR;
        pUV_LED_ICE_TANK_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3 = CLEAR;
        pUV_LED_ICE_TRAY_1_2 = CLEAR;

        Bit1_Ice_Tank_UV_12V_Out_State = CLEAR;

        if( gu8_uart_uv_check_timer >= 50 )
        {
            gu8_uart_uv_check_timer = 50;

            if( gu16_AD_Result_UV_Ice_Faucet_One_Current < gu16_uart_ice_faucet_1_uv_off_ad )
            {
                gu16_uart_ice_faucet_1_uv_off_ad = gu16_AD_Result_UV_Ice_Faucet_One_Current;
            }
            else{}

            if( gu16_AD_Result_UV_Ice_Faucet_Two_Current < gu16_uart_ice_faucet_2_uv_off_ad )
            {
                gu16_uart_ice_faucet_2_uv_off_ad = gu16_AD_Result_UV_Ice_Faucet_Two_Current;
            }
            else{}

            if( gu16_AD_Result_UV_Ice_Tank_1_2_Current < gu16_uart_ice_tank_1_2_uv_off_ad )
            {
                gu16_uart_ice_tank_1_2_uv_off_ad = gu16_AD_Result_UV_Ice_Tank_1_2_Current;
            }
            else{}

            if( gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed < gu16_uart_ice_tray_1_2_uv_off_ad )
            {
                gu16_uart_ice_tray_1_2_uv_off_ad = gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;
            }
            else{}

            if( gu16_AD_Result_UV_Water_Faucet_Current_Feed < gu16_uart_water_faucet_uv_off_ad )
            {
                gu16_uart_water_faucet_uv_off_ad = gu16_AD_Result_UV_Water_Faucet_Current_Feed;
            }
            else{}

            /* ������ũ UV 3 LED �߰� 250226 CH.PARK */
            if(gu16_AD_Result_UV_Ice_Tank_3_Current_Feed < gu16_uart_ice_tank_3_uv_off_ad)
            {
                gu16_uart_ice_tank_3_uv_off_ad = gu16_AD_Result_UV_Ice_Tank_3_Current_Feed;
            }
            else{}
        }
    }
    else
    {
        pUV_LED_WATER_FAUCET = SET;
        pUV_LED_ICE_FAUCET_1 = SET;
        pUV_LED_ICE_FAUCET_2 = SET;
        pUV_LED_ICE_TANK_1_2 = SET;
        pUV_LED_ICE_TANK_3 = SET;
        pUV_LED_ICE_TRAY_1_2 = SET;

        Bit1_Ice_Tank_UV_12V_Out_State = SET;

        if( gu16_AD_Result_UV_Ice_Faucet_One_Current > gu16_uart_ice_faucet_1_uv_on_ad )
        {
            gu16_uart_ice_faucet_1_uv_on_ad = gu16_AD_Result_UV_Ice_Faucet_One_Current;
        }
        else{}

        if( gu16_AD_Result_UV_Ice_Faucet_Two_Current > gu16_uart_ice_faucet_2_uv_on_ad )
        {
            gu16_uart_ice_faucet_2_uv_on_ad = gu16_AD_Result_UV_Ice_Faucet_Two_Current;
        }
        else{}

        if( gu16_AD_Result_UV_Ice_Tank_1_2_Current > gu16_uart_ice_tank_1_2_uv_on_ad )
        {
            gu16_uart_ice_tank_1_2_uv_on_ad = gu16_AD_Result_UV_Ice_Tank_1_2_Current;
        }
        else{}

        if( gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed > gu16_uart_ice_tray_1_2_uv_on_ad )
        {
            gu16_uart_ice_tray_1_2_uv_on_ad = gu16_AD_Result_UV_Ice_Tray_1_2_Current_Feed;
        }
        else{}

        if( gu16_AD_Result_UV_Water_Faucet_Current_Feed > gu16_uart_water_faucet_uv_on_ad )
        {
            gu16_uart_water_faucet_uv_on_ad = gu16_AD_Result_UV_Water_Faucet_Current_Feed;
        }
        else{}

        /* ������ũ UV 3 LED �߰� 250226 CH.PARK */
        if(gu16_AD_Result_UV_Ice_Tank_3_Current_Feed > gu16_uart_ice_tank_3_uv_on_ad)
        {
            gu16_uart_ice_tank_3_uv_on_ad = gu16_AD_Result_UV_Ice_Tank_3_Current_Feed;
        }
        else { }
    }

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_reed_sw(void)
{
    if( gu8_factory_test_step != 0 )
    {
        return;
    }
    else{}

    if( pREED_TANK_COVER_2 == CLEAR )
    {
        if( bit_tank_cover_two_old == SET )
        {
            bit_tank_cover_two_old = CLEAR;

            /*..hui [21-10-6���� 7:50:14] �̰��� -> ������ ����� ��쿡�� ����..*/
            bit_uart_tank_cover_reed_two = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_tank_cover_two_old == CLEAR )
        {
            bit_tank_cover_two_old = SET;
            play_melody_warning_197();
        }
        else{}
    }

    /*..hui [21-10-6���� 7:48:43] ����..*/
    if( pREED_FILTER == CLEAR )
    {
        if( bit_filter_old == SET )
        {
            bit_filter_old = CLEAR;

            /*..hui [21-10-6���� 7:50:14] �̰��� -> ������ ����� ��쿡�� ����..*/
            bit_uart_filter_reed = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        if( bit_filter_old == CLEAR )
        {
            bit_filter_old = SET;
            play_melody_warning_197();
        }
        else{}
    }

    // /* ����Ŀ�� ���彺��ġ �߰� 250311 CH.PARK */
    // if( pREED_FILTER_COVER == CLEAR )
    // {
    //     if( bit_filter_reed_old == SET )
    //     {
    //         bit_filter_reed_old = CLEAR;

    //         /*..hui [21-10-6���� 7:50:14] �̰��� -> ������ ����� ��쿡�� ����..*/
    //         bit_uart_`_reed = SET;
    //         play_melody_warning_197();
    //     }
    //     else{}
    // }
    // else
    // {
    //     if( bit_filter_reed_old == CLEAR )
    //     {
    //         bit_filter_reed_old = SET;
    //         play_melody_warning_197();
    //     }
    //     else{}
    // }
}

void test_uart_ice_door_heater(void)
{
    /* �˻� 2��忡������ ���۵� �� �ֵ��� �� */
    if( gu8_factory_test_step != 1 )
    {
        gu8_Door_Heater_Check_Timer_100ms = 0;
        pHEATER_ICE_DOOR = CLEAR;
        return;
    }
    else{}

    gu8_Door_Heater_Check_Timer_100ms++;
    if(gu8_Door_Heater_Check_Timer_100ms >= 30)     /* 3�� �� ���� �� ���� */
    {
        pHEATER_ICE_DOOR = CLEAR;

        if( gu16_AD_Result_IceDoor_Heater_Current < gu16_Door_Heater_IAD_OFF_Data )
        {
            gu16_Door_Heater_IAD_OFF_Data = gu16_AD_Result_IceDoor_Heater_Current;
        }
        else{}
    }
    else
    {
        pHEATER_ICE_DOOR = SET;

        if( gu16_AD_Result_IceDoor_Heater_Current > gu16_Door_Heater_IAD_ON_Data )
        {
            gu16_Door_Heater_IAD_ON_Data = gu16_AD_Result_IceDoor_Heater_Current;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_uart_ice_tray(void)
{
    input_ice_tray_micro_sw();

    if( bit_manual_test_start == SET )
    {
        return;
    }
    else{}

    if( gu8_uart_ice_tray_test_step >= 4 )
    {
        /*..hui [19-11-8���� 5:12:28] Ʈ���� �˻� �Ϸ� �� ���� �˻��Ҷ� Ʈ���� ������������ �̵�..*/
        return;
    }
    else{}

    /*..hui [19-10-28���� 3:06:51] ����ũ�ν���ġ ���� ������ ����..*/
    /*..hui [19-10-28���� 3:08:17] Ʈ���� �˻� �Ϸ�ÿ��� ����..*/
    #if 0
    if( F_ErrTrayMotor_DualInital == SET )
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;
        return;
    }
    else{}
    #endif

    #if 0
    if( gu8_uart_ice_tray_test_step > 0 )
    {
        gu16_uart_ice_tray_test_timer++;

        /*..hui [19-11-5���� 12:26:04] �ִ� 35�� ����..*/
        if(gu16_uart_ice_tray_test_timer >= 500)
        {
            gu16_uart_ice_tray_test_timer = 0;
            pMOTOR_ICE_TRAY_CW = CLEAR;
            pMOTOR_ICE_TRAY_CCW = CLEAR;
            gu8_uart_ice_tray_test_step = 4;
        }
        else{}
    }
    else{}

    /*..hui [18-2-9���� 1:09:49] CW CCW ���� ���� �� 5�� ��� �� ��ȯ..*/
    inverse_direction_time_check();

    check_error_micro_sw_movement();
    #endif

    switch( gu8_uart_ice_tray_test_step )
    {
        case 0:
            gu16_uart_ice_tray_test_timer = 0;
            gu8_uart_ice_tray_test_step++;
            break;

        case 1:
            up_tray_motor();   // �ڵ������˻�
            gu8_uart_ice_tray_test_step++;
            break;

        case 2:
            if((gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING) 
            && (sStepMotor.state == STEP_STATE_DEACTIVE)
            )
            {
                gu8_uart_ice_tray_up = SET;
                down_tray_motor();   // Ʈ�������� �Լ�����
                gu8_uart_ice_tray_test_step++;
            }
            else
            {
                if( sStepMotor.state == STEP_STATE_DEACTIVE )
                {
                    gu16_uart_ice_tray_test_timer++;

                    if( gu16_uart_ice_tray_test_timer >= 20 )
                    {
                        gu16_uart_ice_tray_test_timer = 0;
                        up_tray_motor();    // �ڵ������˻�
                    }
                    else{}
                }
                else
                {
                    gu16_uart_ice_tray_test_timer = 0;
                }
            }

            break;

        case 3:
            if((gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW) 
            && (sStepMotor.state == STEP_STATE_DEACTIVE)
            )
            {
                gu8_uart_ice_trray_down = SET;
                gu8_uart_ice_tray_test_step++;
            }
            else
            {
                if( sStepMotor.state == STEP_STATE_DEACTIVE )
                {
                    gu16_uart_ice_tray_test_timer++;

                    if( gu16_uart_ice_tray_test_timer >= 20 )
                    {
                        gu16_uart_ice_tray_test_timer = 0;
                        down_tray_motor();    // Ʈ�������� �Լ����� 
                    }
                    else{}
                }
                else
                {
                    gu16_uart_ice_tray_test_timer = 0;
                }
            }

            break;

        case 4:
            /*..hui [19-10-28���� 2:40:33] ���⼭ ���..*/
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
            break;

        default:

            gu8_uart_ice_tray_test_step = 0;

            break;
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_uart_flow(void)
{
    /*..hui [23-12-8���� 4:37:31] 1���, 2��� ��� Ȯ��.. ���� �����..*/
    if( gu8_factory_test_step == 2 )
    {
        return;
    }
    else{}

    /*..hui [25-1-23���� 7:41:53] ��ü ���� MAX, 1~2��忡�� Ȯ��..*/
    if( gu8_Flow_1sec > gu8AT_Flow_1sec_All_Max )
    {
        gu8AT_Flow_1sec_All_Max = gu8_Flow_1sec;
    }
    else{}

    /*..hui [25-1-23���� 7:42:03] ���� �ǽð� ���� ��, 1~2 ��忡�� Ȯ��..*/
    gu8AT_Flow_1sec_Real = gu8_Flow_1sec;


    /*..hui [25-1-23���� 7:42:38] ������� 1��忡���� Ȯ���ϴ� ���� ��..*/
    if( gu8_factory_test_step == 1 )
    {
        return;
    }
    else{}

    if( gu8_water_ext_test_input == 1 )
    {
        if( gu8_test_water_out == PURE_WATER_SELECT )
        {
            /*..hui [25-1-23���� 7:45:24] ��������� ���� �ִ밪..*/
            if( gu8_Flow_1sec > gu8AT_Flow_1sec_Ambient_Extract_Max )
            {
                gu8AT_Flow_1sec_Ambient_Extract_Max = gu8_Flow_1sec;
            }
            else{}


        }
        else if( gu8_test_water_out == COLD_WATER_SELECT )
        {
            /*..hui [25-1-23���� 7:45:30] �ü� ����� ���� �ִ밪..*/
            if( gu8_Flow_1sec > gu8AT_Flow_1sec_Cold_Extract_Max )
            {
                gu8AT_Flow_1sec_Cold_Extract_Max = gu8_Flow_1sec;
            }
            else{}
        }
        else if( gu8_test_water_out == HOT_WATER_SELECT )
        {
            /*..hui [25-1-23���� 7:45:35] �¼� ����� ���� �ִ밪..*/
            if( gu8_Flow_1sec > gu8AT_Flow_1sec_Hot_Extract_Max )
            {
                gu8AT_Flow_1sec_Hot_Extract_Max = gu8_Flow_1sec;
            }
            else{}
        }
        else{}
    }
    else{}


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_comp_control(void)
{
    gu8_bldc_target_hz = gu8_uart_comp_rps;

    if( gu8_bldc_target_hz == 0 )
    {
        comp_off();
    }
    else
    {
        comp_on();
    }

    if( pCOMP == SET )
    {
        Bldc_Comp_Communication();
    }
    else
    {
        clear_bldc_buffer();
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_extract(void)
{
    if( gu8_factory_test_step == 1 )
    {
        gu8_water_ext_test_input = 0;
        ///gu8_uart_purify_test_input = 0;
        ///gu8_uart_cold_test_input = 0;
        ///gu8_uart_hot_test_input = 0;
        gu8_uart_extract_limit_timer = 0;
        gu8_test_water_out = 0;
        return;
    }
    else{}

    if( gu8_water_ext_test_input == 1 )
    {
        #if 0
        if( (gu8_uart_purify_test_input == 0 && gu8_uart_cold_test_input == 0 && gu8_uart_hot_test_input == 0) )
        {
            gu8_test_water_out = 0;
        }
        else
        #endif

        if( gu8_test_water_out == PURE_WATER_SELECT )
        {
            #if 0
            gu8_uart_extract_limit_timer++;

            if( gu8_uart_extract_limit_timer >= 10 )
            {
                gu8_uart_extract_limit_timer = 10;
                pVALVE_ROOM_IN = CLEAR;
                pVALVE_ROOM_COLD_EXTRACT = CLEAR;

                gu8_water_ext_test_input = 0;
            }
            else
            {
                pVALVE_ROOM_IN = SET;
                pVALVE_ROOM_COLD_EXTRACT = SET;
            }
            #endif

            pVALVE_ROOM_IN = SET;
            pVALVE_ROOM_COLD_EXTRACT = SET;
        }
        else if( gu8_test_water_out == COLD_WATER_SELECT )
        {
            #if 0
            gu8_uart_extract_limit_timer++;

            if( gu8_uart_extract_limit_timer >= 10 )
            {
                gu8_uart_extract_limit_timer = 10;
                pVALVE_COLD_IN = CLEAR;
                pVALVE_ROOM_COLD_EXTRACT = CLEAR;
                pVALVE_HOT_COLD_OVERFLOW = CLEAR;

                gu8_water_ext_test_input = 0;
            }
            else
            {
                pVALVE_COLD_IN = SET;
                pVALVE_ROOM_COLD_EXTRACT = SET;
                pVALVE_HOT_COLD_OVERFLOW = SET;
            }
            #endif

            pVALVE_COLD_IN = SET;
            pVALVE_ROOM_COLD_EXTRACT = SET;
            pVALVE_HOT_COLD_OVERFLOW = SET;

            /*check_hps_off();*/
        }
        else if( gu8_test_water_out == HOT_WATER_SELECT )
        {
            pVALVE_HOT_IN = SET;
            pVALVE_HOT_OUT = SET;
            pVALVE_HOT_DRAIN = SET;
            pVALVE_HOT_COLD_OVERFLOW = SET;
            /*check_hps_off();*/
        }
        else
        {
            gu8_water_ext_test_input = 0;
        }
    }
    else
    {
        pVALVE_ROOM_IN = CLEAR;
        pVALVE_ROOM_COLD_EXTRACT = CLEAR;

        pVALVE_COLD_IN = CLEAR;
        pVALVE_HOT_COLD_OVERFLOW = CLEAR;

        pVALVE_HOT_IN = CLEAR;
        pVALVE_HOT_OUT = CLEAR;
        pVALVE_HOT_DRAIN = CLEAR;

        gu8_uart_extract_limit_timer = 0;
    }

    #if 0
    if( gu8_water_ext_test_input == 1 )
    {
        Bit4_Front_Under_Water_White_Extract ^= SET;
    }
    else
    {
        Bit4_Front_Under_Water_White_Extract = CLEAR;
    }

    /*..hui [21-7-16���� 11:14:46] LED�� ���� ��ư ���� ���� ǥ�� ���� / �������� �� ��������..*/
    if( gu8_uart_purify_test_input == 1 )
    //if( gu8_test_water_out == PURE_WATER_SELECT )
    {
        if( gu8_test_water_out == PURE_WATER_SELECT )
        {
            Bit3_Front_Led_Ambient_Select ^= SET;
        }
        else
        {
            Bit3_Front_Led_Ambient_Select = SET;
        }
    }
    else
    {
        Bit3_Front_Led_Ambient_Select = CLEAR;
    }

    if( gu8_uart_cold_test_input == 1 )
    //if( gu8_test_water_out == COLD_WATER_SELECT )
    {
        if( gu8_test_water_out == COLD_WATER_SELECT )
        {
            Bit4_Front_Led_Cold_Select ^= SET;
        }
        else
        {
            Bit4_Front_Led_Cold_Select = SET;
        }
    }
    else
    {
        Bit4_Front_Led_Cold_Select  = CLEAR;
    }

    if( gu8_uart_hot_test_input == 1 )
    //if( gu8_test_water_out == HOT_WATER_SELECT )
    {
        if( gu8_test_water_out == HOT_WATER_SELECT )
        {
            Bit2_Front_Led_Hot_Select ^= SET;
        }
        else
        {
            Bit2_Front_Led_Hot_Select = SET;
        }
    }
    else
    {
        Bit2_Front_Led_Hot_Select  = CLEAR;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void test_hot_flow_motor(void)
{
    if( gu8_factory_test_step == 1 )
    {
        return;
    }
    else{}

    if( gu8_water_ext_test_input == 1 )
    {
        if( gu8_test_water_out == HOT_WATER_SELECT )
        {
            if( gu8_hot_flow_mode == FLOW_MODE_NONE )
            {
                if( gu16_flow_info_current == 0 )
                {
                    run_decrease_flow( 300 );
                }
                else if( gu16_flow_info_current == 300 )
                {
                    run_increase_flow( 300 );
                }
                else{}
            }
            else{}
        }
        else{}
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void motor_test(void)
{
    /*..hui [19-10-28���� 9:23:38] ��� ���� �������� ���� �׽�Ʈ..*/
    if(gu8_uart_comm_start == 1)
    {
        return;
    }
    else{}

    gu8_ice_motor_test_timer++;

    if( gu8_ice_motor_test_timer <= 20 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = SET;
    }
    else if( gu8_ice_motor_test_timer <= 25 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if( gu8_ice_motor_test_timer <= 45 )
    {
        pMOTOR_ICE_OUT_CW = SET;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else if( gu8_ice_motor_test_timer <= 50 )
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
    }
    else
    {
        gu8_ice_motor_test_timer = 0;
    }

    /* 2KG ICE SELECT DOOR �߰� 250226 CH.PARK */
    if( gu16_IceSelect_StepMotor == 0 )
    {
        F_IceSelect = SET;
    }
    else if (gu16_IceSelect_StepMotor == STEP_ANGLE_SELECT)
    {
        F_IceSelect = CLEAR;
    }
    else{}

    if( gu16_Ice_Door_StepMotor == 0 )
    {
        F_IceOpen = SET;
    }
    else if (gu16_Ice_Door_StepMotor == STEP_ANGLE_DOOR)
    {
        F_IceOpen = CLEAR;
    }
    else{}


    /*..hui [23-12-15���� 9:30:33] 1��忡�� Ʈ���� �Լ���� ON �߰�.. ���� ����� ��û..*/
    ////////pVALVE_ICE_TRAY_IN_FEED = SET;

    /*..hui [23-3-15���� 2:19:52] ���� ���� �׽�Ʈ�Ҷ� �ð��ҵ� ����..*/
    pDC_FAN = SET;

    if( gu16_AD_Result_Fan_Current > gu16_uart_dc_fan_on_ad )
    {
        gu16_uart_dc_fan_on_ad = gu16_AD_Result_Fan_Current;
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_off_ad(void)
{
    gu8_check_off_ad_timer++;

    if( gu8_check_off_ad_timer >= 50 )
    {
        gu8_check_off_ad_timer = 50;
        return;
    }
    else{}

    if( pDC_FAN == CLEAR )
    {
        if( gu16_AD_Result_Fan_Current < gu16_uart_dc_fan_off_ad )
        {
            gu16_uart_dc_fan_off_ad = gu16_AD_Result_Fan_Current;
        }
        else{}
    }
    else{}

    if( gu16_drain_pwm_out == 0 )
    {
        if( gu16_AD_Drain_Pump_Current < gu16_uart_drain_pump_off_ad )
        {
            gu16_uart_drain_pump_off_ad = gu16_AD_Drain_Pump_Current;
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void uart_start_input_check(U8 mu8_onoff, U8 mu8_num )
{
    U16 u16KeyMask = 0x01;

    if( mu8_onoff == OFF)
    {
        gu16_uart_key_check &= ~(U16)(u16KeyMask << (U16)mu8_num);
    }
    else
    {
        gu16_uart_key_check |= (U16)(u16KeyMask << (U16)mu8_num);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_led_factory(void)
{
    if( gu8_factory_test_step == 0 )
    {
        display_factory_1_mode();
    }
    else if( gu8_factory_test_step == 1 )
    {
        display_factory_2_mode();
    }
    else /*if( gu8_factory_test_step == 2 )*/
    {
        display_factory_manual_mode();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_factory_1_mode(void)
{
    /*..hui [25-2-3���� 2:02:18] ���� ���� LED ����..*/
    /*..hui [25-2-3���� 2:05:23] �� ���� LED �ҵ� ����..*/
    Bit3_Front_Under_Ice_Outer_White_Extract = F_Wink_500ms;
    Bit1_Front_Under_Ice_Inner_White_Extract = F_Wink_500ms;
    /*Bit4_Front_Under_Water_White_Extract = CLEAR;*/

    if( gu8_water_ext_test_input == 1 )
    {
        Bit4_Front_Under_Water_White_Extract = SET;

        if( gu8_test_water_out == PURE_WATER_SELECT )
        {
            if( gu8_Flow_1sec >= FCT_FLOW_OKAY_VALUE )
            {
                gu8_uart_flow_timer++;

                if( gu8_uart_flow_timer >= 10 )
                {
                    gu8_uart_flow_timer = 0;
                    Bit3_Front_Led_Ambient_Select = SET;
                    gu8_water_ext_test_input = 0;
                    bit_uart_purify_extract_finish = SET;

                    /* �����˻翡�� ������ Ȯ�εǾ�߸� KEY CHECK �Ѿ���� ���� */
                    uart_start_input_check( ON, UART_CHECK_ROOM_EXTRACT );
                }
                else
                {
                    Bit3_Front_Led_Ambient_Select = F_Wink_500ms;
                }
            }
            else
            {
                gu8_uart_flow_timer = 0;
                Bit3_Front_Led_Ambient_Select = F_Wink_500ms;
            }
        }
        else if( gu8_test_water_out == COLD_WATER_SELECT )
        {
            if( gu8_Flow_1sec >= FCT_FLOW_OKAY_VALUE )
            {
                gu8_uart_flow_timer++;

                if( gu8_uart_flow_timer >= 10 )
                {
                    gu8_uart_flow_timer = 0;
                    Bit4_Front_Led_Cold_Select = SET;
                    gu8_water_ext_test_input = 0;
                    bit_uart_cold_extract_finish = SET;

                    
                    /* �����˻翡�� ������ Ȯ�εǾ�߸� KEY CHECK �Ѿ���� ���� */
                    uart_start_input_check( ON, UART_CHECK_COLD_EXTRACT );
                }
                else
                {
                    Bit4_Front_Led_Cold_Select = F_Wink_500ms;
                }
            }
            else
            {
                gu8_uart_flow_timer = 0;
                Bit4_Front_Led_Cold_Select = F_Wink_500ms;
            }
        }
        else if( gu8_test_water_out == HOT_WATER_SELECT )
        {
            if( gu8_Flow_1sec >= FCT_FLOW_OKAY_VALUE )
            {
                gu8_uart_flow_timer++;

                if( gu8_uart_flow_timer >= 10 )
                {
                    gu8_uart_flow_timer = 0;
                    Bit2_Front_Led_Hot_Select = SET;
                    // gu8_water_ext_test_input = 0;        /* �¼��� �����ư ������ ���� 250519 */
                    bit_uart_hot_extract_finish = SET;

                    /* �����˻翡�� ������ Ȯ�εǾ�߸� KEY CHECK �Ѿ���� ���� */
                    uart_start_input_check( ON, UART_CHECK_HOT_EXTRACT );
                }
                else
                {
                    Bit2_Front_Led_Hot_Select = F_Wink_500ms;
                }
            }
            else
            {
                gu8_uart_flow_timer = 0;
                Bit2_Front_Led_Hot_Select = F_Wink_500ms;
            }
        }
        else
        {
            gu8_water_ext_test_input = 0;
            gu8_uart_flow_timer = 0;
        }
    }
    else
    {
        gu8_uart_flow_timer = 0;

        Bit4_Front_Under_Water_White_Extract = CLEAR;

        if( bit_uart_purify_extract_finish == CLEAR )
        {
            if( gu8_test_water_out == PURE_WATER_SELECT )
            {
                Bit3_Front_Led_Ambient_Select = F_Wink_500ms;
            }
            else
            {
                Bit3_Front_Led_Ambient_Select = CLEAR;
            }
        }
        else
        {
            Bit3_Front_Led_Ambient_Select = SET;
        }

        if( bit_uart_cold_extract_finish == CLEAR )
        {
            if( gu8_test_water_out == COLD_WATER_SELECT )
            {
                Bit4_Front_Led_Cold_Select = F_Wink_500ms;
            }
            else
            {
                Bit4_Front_Led_Cold_Select = CLEAR;
            }
        }
        else
        {
            Bit4_Front_Led_Cold_Select = SET;
        }

        if( bit_uart_hot_extract_finish == CLEAR )
        {
            if( gu8_test_water_out == HOT_WATER_SELECT )
            {
                Bit2_Front_Led_Hot_Select = F_Wink_500ms;
            }
            else
            {
                Bit2_Front_Led_Hot_Select = CLEAR;
            }
        }
        else
        {
            Bit2_Front_Led_Hot_Select = SET;
        }
    }

    if( bit_uart_tank_cover_reed_two == SET )
    {
        Bit1_Front_Led_Ice_Water_Select = SET;
        Bit0_Front_Led_Ice_Select = SET;
    }
    else
    {
        Bit1_Front_Led_Ice_Water_Select = CLEAR;
        Bit0_Front_Led_Ice_Select = CLEAR;
    }

    if( bit_uart_filter_reed == SET )
    {
        Bit5_Front_Led_Amount_Select = SET;
    }
    else
    {
        Bit5_Front_Led_Amount_Select = CLEAR;
    }




}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_factory_2_mode(void)
{
    Bit3_Front_Under_Ice_Outer_White_Extract = SET;
    Bit1_Front_Under_Ice_Inner_White_Extract = SET;
    Bit4_Front_Under_Water_White_Extract = CLEAR;

    Bit0_Front_Led_Ice_Select = CLEAR;
    Bit1_Front_Led_Ice_Water_Select = CLEAR;
    Bit2_Front_Led_Hot_Select = CLEAR;
    Bit3_Front_Led_Ambient_Select = CLEAR;
    Bit4_Front_Led_Cold_Select = CLEAR;
    Bit5_Front_Led_Amount_Select = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_factory_manual_mode(void)
{
    /*..hui [25-2-3���� 2:00:39] �����ϴ°����� ó��..*/
    #if 0
    Bit3_Front_Under_Ice_Outer_White_Extract = SET;
    Bit4_Front_Under_Water_White_Extract = SET;

    Bit0_Front_Led_Ice_Select = CLEAR;
    Bit1_Front_Led_Ice_Water_Select = CLEAR;
    Bit2_Front_Led_Hot_Select = CLEAR;
    Bit3_Front_Led_Ambient_Select = CLEAR;
    Bit4_Front_Led_Cold_Select = CLEAR;
    Bit5_Front_Led_Amount_Select = CLEAR;
    #endif

    if( bit_manual_test_start == SET )
    {
        Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
        Bit4_Front_Under_Water_White_Extract = CLEAR;
        return;
    }
    else{}

    Bit3_Front_Under_Ice_Outer_White_Extract = SET;
    Bit1_Front_Under_Ice_Inner_White_Extract = SET;
    Bit4_Front_Under_Water_White_Extract = SET;

    Bit0_Front_Led_Ice_Select = CLEAR;
    Bit1_Front_Led_Ice_Water_Select = CLEAR;
    Bit2_Front_Led_Hot_Select = CLEAR;
    Bit3_Front_Led_Ambient_Select = CLEAR;
    Bit4_Front_Led_Cold_Select = CLEAR;
    Bit5_Front_Led_Amount_Select = CLEAR;

}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void motor_test_continue(void)
{
    /* ����������� FULL OPEN/CLOSE �ȵǴ� ���� ���� */
    if( gu8_hot_flow_mode == FLOW_MODE_NONE )
    {
        if( bit_hot_flow_continue == SET )
        {
            if( gu16_flow_info_current == 0 )
            {
                run_decrease_flow( 1500 );
            }
            else if( gu16_flow_info_current == 1500 )
            {
                run_increase_flow( 1500 );
            }
            else{}
        }
        else{}
    }
    else{}

    if( bit_ice_door_continue == SET )
    {
        if( gu16_Ice_Door_StepMotor == 0 )
        {
            F_IceOpen = SET;
        }
        else if (gu16_Ice_Door_StepMotor == STEP_ANGLE_DOOR)
        {
            F_IceOpen = CLEAR;
        }
        else{}
    }
    else
    {
        F_IceOpen = CLEAR;
    }

    /* 2KG ICE SELECT DOOR �߰� 250226 CH.PARK */
    if(bit_ice_select_continue == SET)
    {
        if( gu16_IceSelect_StepMotor == 0 )
        {
            F_IceSelect = SET;
        }
        else if (gu16_IceSelect_StepMotor == STEP_ANGLE_SELECT)
        {
            F_IceSelect = CLEAR;
        }
        else{}
    }
    else
    {
        F_IceSelect = CLEAR;
    }

    if( bit_ice_tray_continue == CLEAR )
    {
        gu16_uart_ice_tray_continue_timer = 0;
        gu8_uart_ice_tray_continue_step = 0;
        return;
    }
    else{}

    switch( gu8_uart_ice_tray_continue_step )
    {
        case 0:

            gu16_uart_ice_tray_continue_timer = 0;
            gu8_uart_ice_tray_continue_step++;

            break;

        case 1:

            up_tray_motor();   // �ڵ������˻�
            gu16_uart_ice_tray_continue_timer = 0;
            gu8_uart_ice_tray_continue_step++;

            break;

        case 2:

            //////if(F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING && sStepMotor.state == STEP_STATE_DEACTIVE )
            {
                /* ������ġ�� �ö������ �ݴ�� ������ 250321 CH.PARK */
                down_tray_motor();   // Ʈ�������� �Լ�����
                gu8_uart_ice_tray_continue_step++;
            }
            else
            {
                if( sStepMotor.state == STEP_STATE_DEACTIVE )
                {
                    gu16_uart_ice_tray_continue_timer++;

                    if( gu16_uart_ice_tray_continue_timer >= 10 )
                    {
                        gu16_uart_ice_tray_continue_timer = 0;
                        up_tray_motor();    // �ڵ������˻�
                    }
                    else{}
                }
                else
                {
                    gu16_uart_ice_tray_continue_timer = 0;
                }
            }

            break;

        case 3:

            /////if(F_TrayMotorDOWN != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            if(gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW && sStepMotor.state == STEP_STATE_DEACTIVE )
            {
                /* Ż����ġ�� �� ���������� �ٽ� ó������ 250321 CH.PARK */
                gu8_uart_ice_tray_continue_step = 0;
            }
            else
            {
                if( sStepMotor.state == STEP_STATE_DEACTIVE )
                {
                    gu16_uart_ice_tray_continue_timer++;

                    if( gu16_uart_ice_tray_continue_timer >= 10 )
                    {
                        gu16_uart_ice_tray_continue_timer = 0;
                        down_tray_motor();    // Ʈ�������� �Լ����� 
                    }
                    else{}
                }
                else
                {
                    gu16_uart_ice_tray_continue_timer = 0;
                }
            }

            break;


        default:

            gu8_uart_ice_tray_continue_step = 0;

            break;
    }





}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_all_data(void)
{
    if(gu8_initial_all_data == 1)
    {
        eeprom_initial();
        gu8_initial_all_data = 0;
        /*FactoryResetRtc();*/
        InitRtcTime();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_test(void)
{
    /*..hui [22-8-18���� 10:44:09] �޴����׽�Ʈ or ��Ű˻� ���� �� FAN ���� ����..*/
    pDC_FAN = SET;

//////////////////////////////////////////////////////////////////////////////////////////
    /* -------------��� ����-------------------------------- */
    /*..hui [23-12-8���� 4:59:12] �Լ� NOS ����..*/
    pVALVE_NOS = CLEAR;

    /*..hui [25-1-23���� 8:38:54] ���� �Լ� ����..*/
    pVALVE_ROOM_IN = SET;

    /*..hui [25-1-23���� 8:38:58] �ü� �Լ� ����..*/
    pVALVE_COLD_IN = SET;

    /*..hui [25-1-23���� 8:39:05] �¼� �Լ� ����..*/
    pVALVE_HOT_IN = SET;

    /*..hui [25-1-23���� 8:39:22] �¼� ��� ����..*/
    pVALVE_HOT_DRAIN = CLEAR;

    /* -------------��� ����-------------------------------- */
    /*..hui [25-1-23���� 8:38:03] Ʈ���� �Լ� ����..*/
    pVALVE_ICE_TRAY_IN = CLEAR;

    /*..hui [25-1-23���� 8:38:21] �¼�����/�ü������÷ο� ����..*/
    pVALVE_HOT_COLD_OVERFLOW = SET;

    /*..hui [25-1-23���� 8:39:17] �ü� ��� ����..*/
    pVALVE_COLD_DRAIN = CLEAR;

    /*..hui [25-1-23���� 8:38:09] ��/�� ���� ����..*/
    pVALVE_ROOM_COLD_EXTRACT = CLEAR;

    /*..hui [25-1-23���� 8:38:13] �¼� ���� ����..*/
    pVALVE_HOT_OUT = CLEAR;

    /* ������ ������ ���� 250609 CH.PARK */
    pVALVE_ICE_WATER_EXTRACT = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_test_start(void)
{
    if(gu8_test_mode_timeout_1s == 0 || u8FactoryTestMode != NONE_TEST_MODE)
    {
        return;
    }
    else{}

    bit_manual_test_start = SET;
    TestUartStart();
    gu16_manaul_comp_delay_timer = COMP_START_TIME;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_manual_test(void)
{
    U8 mu8_test_rps = 0;

    if( bit_manual_test_start == CLEAR )
    {
        return;
    }
    else{}

    /*initial_ice_tray();*/

    /* [�뷮] ���� */
    if((gu8_uart_amount_test_input == 1) 
    && (gu16_manaul_comp_delay_timer >= COMP_START_TIME)
    )
    {
        gu16_manaul_comp_delay_timer = COMP_START_TIME;
        Bit5_Front_Led_Amount_Select ^= SET;

        if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
        {
            mu8_test_rps = get_ice_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
        else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
        {
            mu8_test_rps = get_cold_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
        {
            mu8_test_rps = get_hotgas_mode_comp_rps();
            gu8_uart_comp_rps = mu8_test_rps;
        }
    }
    else
    {
        if( gu8_uart_amount_test_input == 1 )
        {
            gu8_uart_amount_test_input = 0;
            play_melody_warning_197();
        }
        else{}

        Bit5_Front_Led_Amount_Select = CLEAR;

        if( gu8_uart_comp_rps > 0 )
        {
            gu16_manaul_comp_delay_timer = 0;
            gu8_uart_comp_rps = 0;
        }
        else{}

        gu16_manaul_comp_delay_timer++;

        if( gu16_manaul_comp_delay_timer >= COMP_START_TIME )
        {
            gu16_manaul_comp_delay_timer = COMP_START_TIME;
        }
        else{}
    }

    if( gs16_sm_info_target == gs16_sm_info_current )
    {
        if( gu8_GasSwitch_Status == GAS_SWITCH_ICE )
        {
            Bit0_Front_Led_Ice_Select = SET;
            Bit2_Front_Led_Hot_Select = CLEAR;
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
        else if( gu8_GasSwitch_Status == GAS_SWITCH_COLD )
        {
            Bit0_Front_Led_Ice_Select = CLEAR;
            Bit2_Front_Led_Hot_Select = CLEAR;
            Bit4_Front_Led_Cold_Select = SET;
        }
        else /*if( gu8_GasSwitch_Status == GAS_SWITCH_HOTGAS )*/
        {
            Bit0_Front_Led_Ice_Select = CLEAR;
            Bit2_Front_Led_Hot_Select = SET;
            Bit4_Front_Led_Cold_Select = CLEAR;
        }
    }
    else
    {
        Bit0_Front_Led_Ice_Select ^= SET;
        Bit2_Front_Led_Hot_Select ^= SET;
        Bit4_Front_Led_Cold_Select ^= SET;
    }

    /* [����] ��ư ���� */
    if( gu8_uart_ice_test_input == 1 )
    {
        GasSwitchIce();             /* ���� �ð� */
        gu8_uart_ice_test_input = 0;
        gu8_uart_cold_test_input = 0;
        gu8_uart_hot_test_input = 0;
    }
    else{}

    /* [�ü�] ��ư ���� */
    if( gu8_uart_cold_test_input == 1 )
    {
        GasSwitchCold();            /* �ü� �ð� */
        gu8_uart_ice_test_input = 0;
        gu8_uart_cold_test_input = 0;
        gu8_uart_hot_test_input = 0;
    }
    else{}

    /* [�¼�] ��ư ���� */
    if( gu8_uart_hot_test_input == 1 )
    {
        GasSwitchHotGas();
        gu8_uart_ice_test_input = 0;
        gu8_uart_cold_test_input = 0;
        gu8_uart_hot_test_input = 0;
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

