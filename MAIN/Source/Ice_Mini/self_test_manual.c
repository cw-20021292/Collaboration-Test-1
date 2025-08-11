/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include "Macrodriver.h"
#include "Global_Variable.h"
#include "Port_Define.h"
#include "self_test_manual.h"
// #include "self_test_manual_load.h"
/***********************************************************************************************************************/
void self_test(void);
void self_test_manual(void);
/***********************************************************************************************************************/
void initial_each_self_data( U8 mu8_num );

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �� ���� ��ü OFF �� üũ
 */
U8 off_all_test_load(void);

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� ����
 */
void start_self_test(void);

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �Ϸ�
 */
void finish_self_test(void);

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �����Լ�
 */
void self_test_manual(void);

/***********************************************************************************************************************/
/**
 * @brief �ִ� ���ܽð� ���� 
 */
void self_max_limit_timer(void);

/***********************************************************************************************************************/
/**
 * @brief �������� ��Ʈ��
 */
void self_tesr_proc(void);

/***********************************************************************************************************************/
/**
 * @brief �������� ���� ������ �ʱ�ȭ
 */
void initial_self_data(void);

/***********************************************************************************************************************/
/**
 * @brief �������� ���� ������ ���� �ʱ�ȭ
 */
void initial_each_self_data( U8 mu8_num );


/***********************************************************************************************************************/
extern void stop_drain_pump( void );
extern U8 manual_test_flow(void);
extern U8 manual_test_load(void);
/***********************************************************************************************************************/
TYPE_SELF_TEST_DATA             SELF_Test_Result_Data;
#define U16_VALVE_NOS_0001                        SELF_Test_Result_Data.word[DC_LOAD__NOS_VALVE]
#define U16_VALVE_HOT_OUT_0002                    SELF_Test_Result_Data.word[DC_LOAD__HOT_OUT_VALVE]
#define U16_VALVE_COLD_PURE_OUT_0005              SELF_Test_Result_Data.word[DC_LOAD__COLD_PURE_OUT_VALVE]
#define U16_VALVE_PURE_IN_0007                    SELF_Test_Result_Data.word[DC_LOAD__PURE_IN_VALVE]
#define U16_VALVE_HOT_IN_0009                     SELF_Test_Result_Data.word[DC_LOAD__HOT_IN_VALVE]
#define U16_VALVE_HOT_DRAIN_000A                  SELF_Test_Result_Data.word[DC_LOAD__HOT_DRAIN_VALVE]
#define U16_VALVE_HOT_AIR_0008                    SELF_Test_Result_Data.word[DC_LOAD__OVERFLOW_VALVE]
#define U16_VALVE_COLD_IN_000C                    SELF_Test_Result_Data.word[DC_LOAD__COLD_IN_VALVE]
#define U16_VALVE_COLD_DRAIN_000D                 SELF_Test_Result_Data.word[DC_LOAD__COLD_DRAIN_VALVE]
#define U16_VALVE_ICETRAY_IN_0015                 SELF_Test_Result_Data.word[DC_LOAD__ICETRAY_IN_VALVE]
#define U16_ICE_WATER_VALVE_0023                  SELF_Test_Result_Data.word[DC_LOAD__ICE_WATER_EXTRACT_VALVE]        // 2KG MAX

#define U16_COLD_BLDC_COMP_0201                   SELF_Test_Result_Data.word[DC_LOAD__BLDC_COMP]
#define U16_COLD_FAN_0204                         SELF_Test_Result_Data.word[DC_LOAD__COLD_FAN]

#define U16_HEATER_TRIAC_0302                     SELF_Test_Result_Data.word[AC_LOAD_HOT_TRIAC]
#define U16_HEATER_RELAY_0303                     SELF_Test_Result_Data.word[AC_LOAD_HOT_RELAY]

#define U16_HOT_FLOW_VALVE_0304                   SELF_Test_Result_Data.word[DC_LOAD__FLOWVALVE_MOTOR]
#define U16_FLOW_BLOCK_ERROR_E08_030A             SELF_Test_Result_Data.word[DC_LOAD__FLOW_SENSOR]

#define U16_UV_FAUCET_0501                        SELF_Test_Result_Data.word[DC_LOAD__UV_FAUCET]
#define U16_UV_ICE_FAUCET_0502                    SELF_Test_Result_Data.word[DC_LOAD__UV_ICE_FAUCET1]
#define U16_UV_ICE_FAUCET_2_                      SELF_Test_Result_Data.word[DC_LOAD__UV_ICE_FAUCET2]
#define U16_UV_ICE_TANK_0503                      SELF_Test_Result_Data.word[DC_LOAD__UV_ICE_TANK_1_2]
#define U16_UV_ICE_TRAY_0504                      SELF_Test_Result_Data.word[DC_LOAD__UV_ICE_TRAY]
#define U16_UV_ICE_TRAY_0508                      SELF_Test_Result_Data.word[DC_LOAD__UV_ICE_TANK_3]

#define U16_SENSOR_ICEFULL_0801                   SELF_Test_Result_Data.word[DC_LOAD__ICE_FULL_SENSOR]

#define U16_SWINGBAR_0802                         SELF_Test_Result_Data.word[DC_LOAD__SWING_BAR]
#define U16_ICETRAY_STEPMOTOR_0804                SELF_Test_Result_Data.word[DC_LOAD__ICE_TRAY_MOTOR]
#define U16_TRAY_MICROSWITCH_0805                 SELF_Test_Result_Data.word[DC_LOAD__MICRO_SWITCH]
#define U16_ICEDOOR_STEPMOTOR_0807                SELF_Test_Result_Data.word[DC_LOAD__ICE_DOOR_MOTOR]
#define U16_GAS_SWITCH_MOTOR                      SELF_Test_Result_Data.word[DC_LOAD__GAS_SWITCH_MOTOR]

#define U16_DRAIN_PUMP_080A                       SELF_Test_Result_Data.word[DC_LOAD__DRAIN_PUMP]
#define U16_DRAIN_PUMP_ERROR_E60_080E             SELF_Test_Result_Data.word[DC_LOAD__DRAIN_PUMP_ERROR_E60]

#define U16_ICE_DOOR_HEATER                       SELF_Test_Result_Data.word[DC_LOAD__ICE_DOOR_HEATER]              // 2KG MAX
#define U16_ICE_CRUSH_MOTOR                       SELF_Test_Result_Data.word[DC_LOAD__ICE_CRUSH_MOTOR]              // 2KG MAX
#define U16_ICE_SELECT_DOOR                       SELF_Test_Result_Data.word[DC_LOAD__ICE_SELECT_DOOR_MOTOR]        // 2KG MAX
#define U16_ICE_LACK_SENSOR_0814                  SELF_Test_Result_Data.word[DC_LOAD__ICE_LACK_SENSOR]              // 2KG MAX
/***********************************************************************************************************************/
bit bit_self_test_start;
bit bit_self_test_stop;
U8 gu8_self_test_manual_step;
U16 gu16_self_test_manual_timer;
U8 gu8_self_test_no_load_max_timer;
U8 gu8_selfselfself;
bit bit_current_check_disable;
U16 gu16_self_max_lilit_timer;
/***********************************************************************************************************************/
/***********************************************************************************************************************/
extern U8 gu8_component_test_step;
extern U16 gu16_component_test_timer;
/***********************************************************************************************************************/
extern U8 gu8_current_check_step;
extern U16 gu16_current_check_timer;
/***********************************************************************************************************************/
extern U8 gu8_self_flow_test_step;
extern U16 gu16_self_flow_test_timer;
/***********************************************************************************************************************/
extern U16 gu16_AD_Result_DC_Current_24V;
extern bit F_WaterOut;
/***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void self_test(void)
{
    self_test_manual();
    periodic_self_test();
}

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �����Լ�
 */
void self_test_manual(void)
{
    if( bit_self_test_start == SET )
    {
        self_max_limit_timer();

        if( bit_self_test_stop == SET )
        {
            finish_self_test();
        }
        else
        {
            self_tesr_proc();
        }
    }
    else
    {
        gu8_self_test_manual_step = 0;
        gu16_self_test_manual_timer = 0;
        gu16_self_max_lilit_timer = 0;
        
        gu16_diagnos_flow_val = 0;
    }
}

/***********************************************************************************************************************/
/**
 * @brief �ִ� ���ܽð� ���� 
 */
void self_max_limit_timer(void)
{
    gu16_self_max_lilit_timer++;

    if( gu16_self_max_lilit_timer >= 6000 )
    {
        gu16_self_max_lilit_timer = 6000;
        bit_self_test_stop = SET;
    }
    else{}
}

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� ����
 */
void start_self_test(void)
{
    bit_self_test_start = SET;

    off_all_test_load();

    /*..hui [23-12-22���� 5:11:58] �������̾����� ����..*/
    /*..sean [25-03-12] Ż���� Test�Ϸ� �Ŀ� ����..*/
    stop_ice_cody_mode();

    gu8_self_test_manual_step = 0;

    //Bit2_Uart_Test_Mode_State = SET;

    gu16_gas_switch_current_max = 0;
    play_voice_smart_test_mode_16();
}

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �� ���� ��ü OFF �� üũ
 */
U8 off_all_test_load(void)
{
    U8 mu8_return = 0;

    if( pMOTOR_ICE_OUT_CW == CLEAR
    && pMOTOR_ICE_OUT_CCW == CLEAR
    && pCOMP == CLEAR

    && pSWING_BAR == CLEAR
    && pDC_FAN == CLEAR
    && pIR_POWER == CLEAR
    && pIR_POWER2 == CLEAR

    && pVALVE_NOS == CLEAR
    && pVALVE_HOT_DRAIN == CLEAR
    && pVALVE_HOT_OUT == CLEAR
    && pVALVE_ICE_TRAY_IN == CLEAR
    && pVALVE_ROOM_COLD_EXTRACT == CLEAR
    && pVALVE_COLD_DRAIN == CLEAR
    && pVALVE_HOT_COLD_OVERFLOW == CLEAR
    && pVALVE_COLD_IN == CLEAR
    && pVALVE_ROOM_IN == CLEAR
    && pVALVE_HOT_IN == CLEAR
    && pVALVE_COLD_DRAIN == CLEAR
    && pVALVE_ICE_WATER_EXTRACT == CLEAR        // 2KG MAX

    && pUV_LED_WATER_FAUCET == CLEAR
    && pUV_LED_ICE_FAUCET_1 == CLEAR
    && pUV_LED_ICE_FAUCET_2 == CLEAR
    && pUV_LED_ICE_TANK_1_2 == CLEAR
    && pUV_LED_ICE_TANK_3 == CLEAR
    && pUV_LED_ICE_TRAY_1_2 == CLEAR

    && P_OUT_ICE_CRUSH == CLEAR                 // 2KG MAX
    && pHEATER_ICE_DOOR == CLEAR                // 2KG MAX
    )
    {
        mu8_return = SET;
    }
    else
    {
        pMOTOR_ICE_OUT_CW = CLEAR;
        pMOTOR_ICE_OUT_CCW = CLEAR;
        pCOMP = CLEAR;

        pSWING_BAR = CLEAR;
        pDC_FAN = CLEAR;
        pIR_POWER = CLEAR;
        pIR_POWER2 = CLEAR;

        pVALVE_NOS = CLEAR;
        pVALVE_HOT_DRAIN = CLEAR;
        pVALVE_HOT_OUT = CLEAR;
        pVALVE_ICE_TRAY_IN = CLEAR;
        pVALVE_ROOM_COLD_EXTRACT = CLEAR;
        pVALVE_COLD_DRAIN = CLEAR;
        pVALVE_HOT_COLD_OVERFLOW = CLEAR;
        pVALVE_COLD_IN = CLEAR;
        pVALVE_ROOM_IN = CLEAR;
        pVALVE_HOT_IN = CLEAR;
        pVALVE_COLD_DRAIN = CLEAR;
        pVALVE_ICE_WATER_EXTRACT = CLEAR;

        pUV_LED_WATER_FAUCET = CLEAR;
        pUV_LED_ICE_FAUCET_1 = CLEAR;
        pUV_LED_ICE_FAUCET_2 = CLEAR;
        pUV_LED_ICE_TANK_1_2 = CLEAR;
        pUV_LED_ICE_TANK_3 = CLEAR;
        pUV_LED_ICE_TRAY_1_2 = CLEAR;

        P_OUT_ICE_CRUSH = CLEAR;
        pHEATER_ICE_DOOR = CLEAR;

        stop_drain_pump();
    }

    return mu8_return;
}

/***********************************************************************************************************************/
/**
 * @brief ����Ʈ �������� �Ϸ�
 */
void finish_self_test(void)
{
    /*..hui [24-1-9���� 1:46:00] �߰��� �ߴ��Ұ�� ������.. ��������..*/
    if( bit_self_test_stop == SET )
    {
        //play_melody_setting_on_198();
    }
    else{}

    bit_self_test_start = CLEAR;
    bit_self_test_stop = CLEAR;

    off_all_test_load();

    gu8_self_test_manual_step = 0;
    gu8_component_test_step = 0;
    gu16_self_test_manual_timer = 0;

    gu16_gas_switch_current_max = 0;
	
	/*..sean [25-03-12] ����Ʈ �������� �߿��� ���� ���� �Ϸ� �� Ż�� ����..*/
    stop_ice_cody_mode();

    /*..hui [24-1-9���� 12:07:50] WIFI�ʿ��� �ڵ� ���..*/
    /*play_voice_finish_self_no_error_test_62();*/

   // Bit2_Uart_Test_Mode_State = CLEAR;
}

/***********************************************************************************************************************/
/**
 * @brief �������� ��Ʈ��
 */
void self_tesr_proc(void)
{
    U16 mu16_val = 0;
    U8 mu8_decision = 0;
    U8 mu8_ok = 0;
    U8 mu8_return = 0;

	//wifi ó��
	//���� ���� ���� �߿��� �Ϲݵ��� ���� �ȵǵ��� ����
	if(gu8_self_test_manual_step != 0)
	{
		// SetWifiSystemStatus(WIFI_RX_STATUS, SET);
		// SetWifiSystemStatus(WIFI_SMART_SENSING_STATUS, SET);	
		//SetWifiSystemStatus(WIFI_FOTA_POSSIBLE_STATUS, SET);	
	}
	else
	{
		// SetWifiSystemStatus(WIFI_RX_STATUS, CLEAR);
		// SetWifiSystemStatus(WIFI_SMART_SENSING_STATUS, CLEAR);	
		//SetWifiSystemStatus(WIFI_FOTA_POSSIBLE_STATUS, CLEAR);	
	}
	
    switch( gu8_self_test_manual_step )
    {
        case 0 :

            gu8_component_test_step = 0;
            gu8_current_check_step = 0;
            gu8_self_flow_test_step = 0;
            gu8_self_test_no_load_max_timer = 0;

            gu16_self_test_manual_timer = 0;
            gu8_self_test_manual_step++;

            ///////////gu8_Lcd_Display_Step = LCD_Display__SELF_TEST;

        break;

        case 1 :

            F_WaterOut = CLEAR;
            /*..hui [20-10-30���� 9:50:06] �����ϱ� ���� ���� ����Ÿ �ʱ�ȭ..*/
            initial_self_data();

            /*..sean [25-03-12] ���� ������ �Ϸ� �� ������..*/
			gu8_self_test_manual_step++;
#if 0
            /*..hui [23-12-22���� 4:41:59] ���� ��������̾����� �Ϸ�ɶ����� ���..*/
            if( gu8IceStep == STATE_0_STANDBY )
            {
                gu8_self_test_manual_step++;
            }
            else{}
#endif
        break;

        case 2 :

            mu8_return = off_all_test_load();

            if( mu8_return == SET )
            {
                gu16_self_test_manual_timer++;

                /*..hui [20-10-28���� 7:53:40] ���� �ǵ�� 10 ���Ϸ� ���� or �ִ� 2�� �̳�..*/
                if( gu16_AD_Result_DC_Current_24V <= 20
                || gu16_self_test_manual_timer >= 20 )
                //if(  gu16_self_test_manual_timer >= 20 )
                {
                    gu16_self_test_manual_timer = 0;
                    gu8_self_test_no_load_max_timer = 0;
                    gu8_self_test_manual_step++;
                }
                else{}
            }
            else
            {
                gu16_self_test_manual_timer = 0;

                gu8_self_test_no_load_max_timer++;

                if( gu8_self_test_no_load_max_timer >= 20 )
                {
                    gu16_self_test_manual_timer = 0;
                    gu8_self_test_no_load_max_timer = 0;
                    gu8_self_test_manual_step++;
                }
                else{}
            }

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 3 :

            /*..hui [21-8-25���� 2:44:37] ���� �׽�Ʈ �� ����..*/
            /*..hui [23-12-21���� 11:34:13] Ʈ���� �Լ� ��������, RO �巹�� �������� ���� ����..*/
            mu8_return = manual_test_flow();        // ���� ���� �׽�Ʈ

            if( mu8_return == SET )
            {
                off_all_test_load();
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step++;
            }
            else{}

        break;

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 4 :

            /*..hui [20-10-29���� 11:38:05] DC �� AC ���� ���� �׽�Ʈ..*/
            /*..hui [23-12-21���� 11:43:29] DC ���� �׽�Ʈ..*/
            mu8_return = manual_test_load();        // ��� ���� �׽�Ʈ

            if( mu8_return == SET )
            {
                off_all_test_load();
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step++;
            }
            else{}

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
        case 5 :
            mu8_return = manual_test_heater();      // ���� ���� �׽�Ʈ

            if( mu8_return == SET )
            {
                off_all_test_load();
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step++;
            }
            else{}
        break;

        case 6 :
            gu16_self_test_manual_timer++;

            if( gu16_self_test_manual_timer >= 10 )
            {
                gu16_self_test_manual_timer = 0;
                gu8_self_test_manual_step = 0;

                finish_self_test();
            }
            else{}
        break;


        default :

            gu8_self_test_manual_step = 0;
            gu16_self_test_manual_timer = 0;

        break;
    }
}

/***********************************************************************************************************************/
/**
 * @brief �������� ���� ������ ��ü �ʱ�ȭ
 */
void initial_self_data(void)
{
    U8 mu8_i = 0;

    for(mu8_i = 0; mu8_i < SELF_TEST_RESULT_DATA_LENGTH; mu8_i++)
    {
        SELF_Test_Result_Data.word[ mu8_i ] = SELF_TEST_INITIAL_DATA;
    }

    /*gu16_wifi_hot_target_time_min = SELF_TEST_INITIAL_DATA;*/
}

/***********************************************************************************************************************/
/**
 * @brief �������� ���� ������ ���� �ʱ�ȭ
 */
void initial_each_self_data( U8 mu8_num )
{
    U8 mu8_i = 0;

    SELF_Test_Result_Data.word[ mu8_num ] = SELF_TEST_INITIAL_DATA;
}

