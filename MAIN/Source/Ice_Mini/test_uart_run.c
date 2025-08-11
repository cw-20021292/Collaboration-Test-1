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
#include    "test_uart_run.h"


void UARTest_RUN(void);
void UARTest_NO_LOAD_Set(void);

bit F_Relay_Test_Finish;

bit F_AT_Heater_Test_Relay;
U16 gu16AT_Heater_Data_Relay;
U8 gu8AT_Heater_Time1_Relay;

bit F_AT_Heater_Test_Triac;
U16 gu16AT_Heater_Data_Triac;
U8 gu8AT_Heater_Time1_Triac;

/* ���� ���� �����˻�� ������ */
bit F_Door_Heater_Test_Finish;
bit F_Door_Heater_Test_Check;
U16 gu16AT_IceDoor_Heater_Data_Relay;
U8  gu8_Door_Heater_Check_Timer_100ms = CLEAR;
U16 gu16_Door_Heater_IAD_OFF_Data = CLEAR;
U16 gu16_Door_Heater_IAD_ON_Data = CLEAR;


/*U8 gu8UARTData[35];*/
U8 gu8UARTData[45];


U8 gu8_test_cmd;

U8 gu8AT_Wifi_Connect;                              // (������) Wifi ��������

U16 gu16_uart_dc_24v_current;
U16 gu16_uart_dc_12v_current;

U16 gu16_uart_start_time_total;
U16 gu16_uart_current_time_total;

U16 gu16_uart_elapsed_time_total;

extern U16 gu16_uart_ice_tank_3_uv_off_ad;
extern U16 gu16_uart_ice_tank_3_uv_on_ad;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                    (2) AUTO TEST ó��
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// -> ���⼭ ������ �����Ͱ� AT_UART_Tx_Process
void UARTest_RUN(void)
{
    if(u8FactoryTestMode != UART_TEST_MODE)
    {
        return;
    }
    else{}

    switch(AT_gu16_CMD_Mode)                 // �����Ͱ� ��û�� Ŀ�ǵ�
    {
        case AT_UART_No_CMD:

            AT_F_TxStart = 0;

            break;

        // 0x2000 (����) O.K!!
        case AT_UART_CMD_START :

            UARTest_NO_LOAD_Set();
            gu8UARTData[1]= AT_RS232_ACK;                         // 0x06
            gu8UARTData[2]= (U8)(AT_UART_CMD_START / 256);        // 0x20
            gu8UARTData[3]= (U8)(AT_UART_CMD_START % 256);        // 0x00

            gu8UARTData[4]= AT_MODEL_CMD_CHP_ICON_AIS_2KG;        // 0x47

            if( gu8_uart_test_mode == NOT_INCLUDE_FRONT_UART_TEST )
            {
                /* �ڵ��˻� ���Ը�� (�˻� ���� 2���) FRONT ��ü�� �˻� */
                gu8UARTData[5]= 0x01;
            }
            else /*if( gu8_uart_test_mode == INCLUDE_FRNOT_UART_TEST )*/
            {
                /* �ڵ��˻� ���� �� ��� (�˻� ���� 1���) FRONT ü�� �˻� */
                gu8UARTData[5]= 0x02;
            }

            gu8UART_DataLength = 5;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;                    // 0x00
            gu8_uart_comm_start = 1;

            break;

        // 0x3000 �ý��� ���� !!O.K!!
        case AT_UART_CMD_SETTINGS :

             gu8UARTData[1]= AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_SETTINGS / 256);     // 0x30
             gu8UARTData[3]= (U8)(AT_UART_CMD_SETTINGS % 256);     // 0x00

             if( bit_eeprom_err == CLEAR )
             {
                gu8UARTData[4]= 0xA5;                                 // EEPROM �ʱⰪ
             }
             else
             {
                gu8UARTData[4]= 0x00;
             }

             gu8UARTData[5]= 0x01;                                 // FRONT ����
             gu8UARTData[6]= 0x01;                                 // MAIN ����

             gu8UARTData[7]= gu8AltitudeStep;                      // ����� ������(012)
             gu8UARTData[8]= AT_MODEL_CMD_NATION_KOREA;            // �� ���� ����(�ѱ�)
             gu8UARTData[9]= 0x01;                                 // �ÿ¼���

             gu8UART_DataLength = 9;
             AT_F_TxStart = 1;
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

        // 0x3010 Wifi ���� �˻�  !!O.K!!
        case AT_UART_CMD_WIFI :

             gu8UARTData[1]= AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_WIFI / 256);          // 0x30
             gu8UARTData[3]= (U8)(AT_UART_CMD_WIFI % 256);          // 0x10

             if(GetWifiStatusValue(WIFI_STATUS_TEST) == SET)
             {
                gu8UARTData[4] = 1;         //Wifi ���� ���� (0x01 ����/ 0x00; ����ȵ�)
             }
             else
             {
                gu8UARTData[4] = 0;         //Wifi ���� ���� (0x01 ����/ 0x00; ����ȵ�)
             }

             gu8UART_DataLength = 4;
             AT_F_TxStart = 1;
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3011 UV �����Ŀ�� 1,2
        case AT_UART_CMD_UV_ICE_FAUCET_1 :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_ICE_FAUCET_1 / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_ICE_FAUCET_1 % 256);     // 0x11

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ice_faucet_1_uv_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_faucet_1_uv_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_faucet_1_uv_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_faucet_1_uv_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ice_faucet_1_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_faucet_1_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_faucet_1_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_faucet_1_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3012 �������� ���� !!O.K!!
        case AT_UART_CMD_SENSOR_FLOW_FILTER :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SENSOR_FLOW_FILTER / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_SENSOR_FLOW_FILTER % 256);     // 0x12

            gu8UARTData[4] = gu8AT_Flow_1sec_All_Max;
            gu8UARTData[5] = gu8AT_Flow_1sec_Ambient_Extract_Max;
            gu8UARTData[6] = gu8AT_Flow_1sec_Cold_Extract_Max;
            gu8UARTData[7] = gu8AT_Flow_1sec_Hot_Extract_Max;
            gu8UARTData[8] = gu8AT_Flow_1sec_Real;

            gu8UART_DataLength = 8;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        /*..hui [21-7-19���� 9:42:03] 0x3013 ���� ����..*/
        case AT_UART_CMD_CURRENT_CALC :

            gu16_uart_dc_12v_current = calculate_dc_current( gu16_AD_Result_DC_Current_12V );
            gu16_uart_dc_24v_current = calculate_dc_current( gu16_AD_Result_DC_Current_24V );

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_CURRENT_CALC / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_CURRENT_CALC % 256);     // 0x13

            gu8UARTData[4] = 0;
            gu8UARTData[5] = (U8)(gu16_uart_dc_12v_current / 100);
            gu8UARTData[6] = (U8)(gu16_uart_dc_12v_current % 100);

            gu8UARTData[7] = 0;
            gu8UARTData[8] = (U8)(gu16_uart_dc_24v_current / 100);
            gu8UARTData[9] = (U8)(gu16_uart_dc_24v_current % 100);

            gu8UART_DataLength = 9;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3014 UV �����Ŀ�� 3
        case AT_UART_CMD_UV_ICE_FAUCET_2 :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_ICE_FAUCET_2 / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_ICE_FAUCET_2 % 256);     // 0x14

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ice_faucet_2_uv_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_faucet_2_uv_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_faucet_2_uv_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_faucet_2_uv_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ice_faucet_2_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_faucet_2_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_faucet_2_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_faucet_2_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3015 uv water faucet
        case AT_UART_CMD_UV_WATER_FAUCET :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_WATER_FAUCET / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_WATER_FAUCET % 256);     // 0x15

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_water_faucet_uv_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_water_faucet_uv_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_water_faucet_uv_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_water_faucet_uv_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_water_faucet_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_water_faucet_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_water_faucet_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_water_faucet_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3016 dc fan
        case AT_UART_CMD_DC_FAN :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_DC_FAN / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_DC_FAN % 256);     // 0x16

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_dc_fan_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_dc_fan_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_dc_fan_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_dc_fan_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_dc_fan_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_dc_fan_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_dc_fan_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_dc_fan_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x3017 drain pump
        case AT_UART_CMD_DRAIN_PUMP :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_DRAIN_PUMP / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_DRAIN_PUMP % 256);     // 0x17

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_drain_pump_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_drain_pump_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_drain_pump_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_drain_pump_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_drain_pump_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_drain_pump_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_drain_pump_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_drain_pump_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        /* [0x3019] ICE TANK3 (������ũ �����) UV Ŀ�ǵ� �߰� 250311 CH.PARK */
        case AT_UART_CMD_UV_TANK_3 :
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_TANK_3 / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_TANK_3 % 256);     // 0x19

            gu8UARTData[4] = (U8)(gu16_uart_ice_tank_3_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_tank_3_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_tank_3_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_tank_3_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
        break;

        // 0x301B UV ������ũ 1,2
        case AT_UART_CMD_UV_ICE_TANK_1_2 :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_ICE_TANK_1_2 / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_ICE_TANK_1_2 % 256);     // 0x1B

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ice_tank_1_2_uv_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_tank_1_2_uv_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_tank_1_2_uv_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_tank_1_2_uv_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ice_tank_1_2_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_tank_1_2_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_tank_1_2_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_tank_1_2_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x301C UV ���̽� Ʈ���� 1,2
        case AT_UART_CMD_UV_ICE_TRAY_1_2 :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_UV_ICE_TRAY_1_2 / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_UV_ICE_TRAY_1_2 % 256);     // 0x1C

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ice_tray_1_2_uv_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_tray_1_2_uv_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_tray_1_2_uv_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_tray_1_2_uv_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ice_tray_1_2_uv_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ice_tray_1_2_uv_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ice_tray_1_2_uv_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ice_tray_1_2_uv_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        case AT_UART_CMD_ICE_LACK_SENSOR:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_LACK_SENSOR / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_LACK_SENSOR % 256);     // 0x1D

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ir_power_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ir_power_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ir_power_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ir_power_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ir_ice_lack_power_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ir_ice_lack_power_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ir_ice_lack_power_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ir_ice_lack_power_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
        break;

        // 0x301D ice full sensor (��������)
        case AT_UART_CMD_ICE_FULL_SENSOR :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_FULL_SENSOR / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_FULL_SENSOR % 256);     // 0x1D

            #if 0
            gu8UARTData[4] = (U8)(gu16_uart_ir_power_on_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ir_power_on_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ir_power_off_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ir_power_off_ad & 0xFF);
            #endif

            gu8UARTData[4] = (U8)(gu16_uart_ir_power_off_ad >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_ir_power_off_ad & 0xFF);

            gu8UARTData[6] = (U8)(gu16_uart_ir_power_on_ad >> 8);
            gu8UARTData[7] = (U8)(gu16_uart_ir_power_on_ad & 0xFF);

            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x301E rtc
        case AT_UART_CMD_RTC_TIME :

            gu16_uart_current_time_total = (U16)((U16)gu8_rtc_time_Min * 60);
            gu16_uart_current_time_total = gu16_uart_current_time_total + gu8_rtc_time_Sec;

            gu16_uart_start_time_total = (U16)((U16)gu8_uart_start_min * 60);
            gu16_uart_start_time_total = gu16_uart_start_time_total + gu8_uart_start_sec;

            gu16_uart_elapsed_time_total = gu16_uart_current_time_total - gu16_uart_start_time_total;

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_RTC_TIME / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_RTC_TIME % 256);     // 0x1E

            gu8UARTData[4] = (U8)(gu16_uart_elapsed_time_total >> 8);
            gu8UARTData[5] = (U8)(gu16_uart_elapsed_time_total & 0xFF);

            gu8UART_DataLength = 5;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        /* �������� ���� ���� 250312 CH.PARK */
        case AT_UART_CMD_ICE_DOOR_HEATER:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_DOOR_HEATER / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_DOOR_HEATER % 256);     // 0x1F

            // �������� �µ�����
            gu8UARTData[4] = (U8)((gu16_Door_Heater_IAD_OFF_Data >> 8) & 0x03);      // ���������ǵ�� OFF ��������Ʈ
            gu8UARTData[5] = (U8)(gu16_Door_Heater_IAD_OFF_Data & 0xFF);             // ���������ǵ�� OFF ��������Ʈ
            
            gu8UARTData[6] = (U8)((gu16_Door_Heater_IAD_ON_Data >> 8) & 0x03);      // ���������ǵ�� ON ��������Ʈ
            gu8UARTData[7] = (U8)(gu16_Door_Heater_IAD_ON_Data & 0xFF);             // ���������ǵ�� ON ��������Ʈ
            
            gu8UART_DataLength = 7;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
            break;

        // 0x3020 temp sensor
        case AT_UART_CMD_SENSOR_TH :

            gu8UARTData[1]= AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SENSOR_TH / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_SENSOR_TH % 256);     // 0x20
            
            /* �켱������ ���� ���� */
            // �ܱ�µ����� 1
            if( gu16_AD_Result_Amb < 20 || gu16_AD_Result_Amb > 1000 )
            {
                gu8UARTData[4] = (U8)(99);
                gu8UARTData[5] = (U8)(99);
                gu8UARTData[6] = (U8)(99);
                gu8UARTData[7] = (U8)(99);
            }
            else
            {
                gu8UARTData[4] = (U8)(gu16_Amb_Front_Temperature / 10);
                gu8UARTData[5] = (U8)((gu16_Amb_Front_Temperature % 10) * 10);
                gu8UARTData[6] = (U8)(gu16_AD_Result_Amb >> 8);
                gu8UARTData[7] = (U8)(gu16_AD_Result_Amb & 0xFF);
            }

            /*..hui [23-12-8���� 5:15:34] �ܱ� �µ����� 2..*/
            if( gu16_AD_Result_Amb_Side < 20 || gu16_AD_Result_Amb_Side > 1000 )
            {
                gu8UARTData[8] = (U8)(99);
                gu8UARTData[9] = (U8)(99);
                gu8UARTData[10] = (U8)(99);
                gu8UARTData[11] = (U8)(99);
            }
            else
            {
                gu8UARTData[8] = (U8)(gu16_Amb_Side_Temperature / 10);
                gu8UARTData[9] = (U8)((gu16_Amb_Side_Temperature % 10) * 10);
                gu8UARTData[10] = (U8)(gu16_AD_Result_Amb_Side >> 8);
                gu8UARTData[11] = (U8)(gu16_AD_Result_Amb_Side & 0xFF);
            }


            // 3 �ü��µ�����
            if( gu16_AD_Result_Cold < 20 || gu16_AD_Result_Cold > 1000 )
            {
                gu8UARTData[12] = (U8)(99);
                gu8UARTData[13] = (U8)(99);
                gu8UARTData[14] = (U8)(99);
                gu8UARTData[15] = (U8)(99);
            }
            else
            {
                gu8UARTData[12] = (U8)(gu16_Cold_Temperature / 10);
                gu8UARTData[13] = (U8)((gu16_Cold_Temperature % 10) * 10);
                gu8UARTData[14] = (U8)(gu16_AD_Result_Cold >> 8);
                gu8UARTData[15] = (U8)(gu16_AD_Result_Cold & 0xFF);
            }

            // 4 �¼��Լ�����
            if( gu16_AD_Result_Hot_In < 20 || gu16_AD_Result_Hot_In > 1000 )
            {
                gu8UARTData[16] = (U8)(99);
                gu8UARTData[17] = (U8)(99);
                gu8UARTData[18] = (U8)(99);
                gu8UARTData[19] = (U8)(99);
            }
            else
            {
                gu8UARTData[16] = (U8)(gu16_Hot_In_Temperature / 10);
                gu8UARTData[17] = (U8)((gu16_Hot_In_Temperature % 10) * 10);
                gu8UARTData[18] = (U8)(gu16_AD_Result_Hot_In >> 8);
                gu8UARTData[19] = (U8)(gu16_AD_Result_Hot_In & 0xFF);
            }

            /*..5 hui [25-1-24���� 11:59:44] �¼� ��� �µ�����..*/
            if( gu16_AD_Result_Hot_Out < 20 || gu16_AD_Result_Hot_Out > 1000 )
            {
                gu8UARTData[20] = (U8)(99);
                gu8UARTData[21] = (U8)(99);
                gu8UARTData[22] = (U8)(99);
                gu8UARTData[23] = (U8)(99);
            }
            else
            {
                gu8UARTData[20] = (U8)(gu16_Hot_Out_Temperature / 10);
                gu8UARTData[21] = (U8)((gu16_Hot_Out_Temperature % 10) * 10);
                gu8UARTData[22] = (U8)(gu16_AD_Result_Hot_Out >> 8);
                gu8UARTData[23] = (U8)(gu16_AD_Result_Hot_Out & 0xFF);
            }

            // 6 EVA COLD ���� (���߱�)
            if( gu16_AD_Result_Eva_First < 20 || gu16_AD_Result_Eva_First > 1000 )
            {
                gu8UARTData[24] = (U8)(99);
                gu8UARTData[25] = (U8)(99);
                gu8UARTData[26] = (U8)(99);
                gu8UARTData[27] = (U8)(99);
            }
            else
            {
                gu8UARTData[24] = (U8)(gu16_Eva_First_Temperature / 10);
                gu8UARTData[25] = (U8)((gu16_Eva_First_Temperature % 10) * 10);
                gu8UARTData[26] = (U8)(gu16_AD_Result_Eva_First >> 8);
                gu8UARTData[27] = (U8)(gu16_AD_Result_Eva_First & 0xFF);
            }

            // 7 ��������
            if( gu16_AD_Result_Room < 20 || gu16_AD_Result_Room > 1000 )
            {
                gu8UARTData[28] = (U8)(99);
                gu8UARTData[29] = (U8)(99);
                gu8UARTData[30] = (U8)(99);
                gu8UARTData[31] = (U8)(99);
            }
            else
            {
                gu8UARTData[28] = (U8)(gu16_Room_Temperature / 10);
                gu8UARTData[29] = (U8)((gu16_Room_Temperature % 10) * 10);
                gu8UARTData[30] = (U8)(gu16_AD_Result_Room >> 8);
                gu8UARTData[31] = (U8)(gu16_AD_Result_Room & 0xFF);
            }

            /*..8 hui [25-1-24���� 12:01:51] ���� �µ�����..*/
            if( gu16_AD_Result_Hot_Heater < 20 || gu16_AD_Result_Hot_Heater > 1000 )
            {
                gu8UARTData[32] = (U8)(99);
                gu8UARTData[33] = (U8)(99);
                gu8UARTData[34] = (U8)(99);
                gu8UARTData[35] = (U8)(99);
            }
            else
            {
                gu8UARTData[32] = (U8)(gu16_Hot_Heater_Temperature / 10);
                gu8UARTData[33] = (U8)((gu16_Hot_Heater_Temperature % 10) * 10);
                gu8UARTData[34] = (U8)(gu16_AD_Result_Hot_Heater >> 8);
                gu8UARTData[35] = (U8)(gu16_AD_Result_Hot_Heater & 0xFF);
            }

            /*gu8UART_DataLength = 31;*/
            /*gu8UART_DataLength = 39;*/
            gu8UART_DataLength = 35;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

         /*..hui [21-7-19���� 4:53:33] 0x3030 = �������� ���� �˻�..*/
         case AT_UART_CMD_SENSOR_WATER_LEVEL :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_SENSOR_WATER_LEVEL / 256);     // 0x30
             gu8UARTData[3]= (U8)(AT_UART_CMD_SENSOR_WATER_LEVEL % 256);     // 0x30

             gu8UARTData[4] = gu8Drain_LEV_L;
             gu8UARTData[5] = gu8Drain_LEV_H;

             gu8UARTData[6] = gu8_uart_leakage;

             gu8UART_DataLength = 6;
             AT_F_TxStart = 1;
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

         break;


         // 0x3040 ice sensor
         case AT_UART_CMD_SENSOR_ICE :
            
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SENSOR_ICE / 256);     // 0x30
            gu8UARTData[3]= (U8)(AT_UART_CMD_SENSOR_ICE % 256);     // 0x40
            
            /* �켱������ ���� ���� */
            gu8UARTData[4] = 99;      // ��ũĿ�� ���彺��ġ1 �̻������ ���� (LPP)

            if( pREED_TANK_COVER_2 == CLEAR )
            {
                gu8UARTData[5] = 1;
            }
            else
            {
                gu8UARTData[5] = 0;
            }

            if( pREED_FILTER == CLEAR )
            {
                gu8UARTData[6] = 1;
            }
            else
            {
                gu8UARTData[6] = 0;
            }
            
            if( gu8_uart_ice_tray_up == SET && gu8_uart_ice_trray_down == SET )
            {
                /*..hui [23-3-13���� 2:46:58] �Ѵ� ����.. ����..*/
                gu8UARTData[7] = 0x03;
            }
            else if( gu8_uart_ice_tray_up == SET && gu8_uart_ice_trray_down == CLEAR )
            {
                /*..hui [23-3-13���� 2:47:20] Ż���� �̰���..*/
                gu8UARTData[7] = 0x01;
            }
            else if( gu8_uart_ice_tray_up == CLEAR && gu8_uart_ice_trray_down == SET )
            {
                /*..hui [23-3-13���� 2:47:36] ������ �̰���..*/
                gu8UARTData[7] = 0x02;
            }
            else
            {
                /*..hui [23-3-13���� 2:47:47] ��ü �̰���..*/
                gu8UARTData[7] = 0x00;
            }

            
            /* ����Ŀ�� ���彺��ġ �߰� 250311 CH.PARK */
            if( pREED_FILTER_COVER == CLEAR )
            {
                gu8UARTData[8] = 1;
            }
            else
            {
                gu8UARTData[8] = 0;
            }

            gu8UART_DataLength = 8;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
            break;

             //
             // 0x3050 �¼� ���� �˻� (0.3�ʸ�) !!O.K!! �ڡڡڡڡڡ� ���߿� ���� -> ���Ǿ� �Ѽ� ������ ������ �Ѵ�
             case AT_UART_CMD_HEATER :

             if( F_Relay_Test_Finish == CLEAR )
             {
                if(F_AT_Heater_Test_Relay != SET)
                {
                    F_AT_Heater_Test_Relay = 1;

                    UARTest_NO_LOAD_Set();
                    NOP(); NOP(); NOP(); NOP(); NOP();

                    pHEATER_HOT_H_RELAY = 1;
                    pHEATER_HOT_TRIAC_L = 0;

                    gu16AT_Heater_Data_Relay = 0;
                    gu8AT_Heater_Time1_Relay = 0;
                }
                else
                {
                    gu8AT_Heater_Time1_Relay++;

                    if( gu8AT_Heater_Time1_Relay >= 3 )
                    {
                        UARTest_NO_LOAD_Set();              // ���ʹ� �� ���ߵ�
                        pHEATER_HOT_H_RELAY = 0;
                        pHEATER_HOT_TRIAC_L = 0;
                        NOP(); NOP(); NOP(); NOP(); NOP();

                        if(gu8AT_Heater_Time1_Relay >= 12)
                        {
                            gu8AT_Heater_Time1_Relay = 12;

                            F_Relay_Test_Finish = SET;
                        }
                        else
                        {
                            if(gu16_AD_Result_Heater_Current_Feed > gu16AT_Heater_Data_Relay)
                            {
                                gu16AT_Heater_Data_Relay = gu16_AD_Result_Heater_Current_Feed;
                            }
                            else{}
                        }
                    }
                    else
                    {
                        if(gu16_AD_Result_Heater_Current_Feed > gu16AT_Heater_Data_Relay)
                        {
                            gu16AT_Heater_Data_Relay = gu16_AD_Result_Heater_Current_Feed;
                        }
                        else{}
                    }
                }
             }
             else
             {
                if(F_AT_Heater_Test_Triac != SET)
                {
                    F_AT_Heater_Test_Triac = 1;

                    UARTest_NO_LOAD_Set();
                    NOP(); NOP(); NOP(); NOP(); NOP();

                    pHEATER_HOT_H_RELAY = 0;
                    pHEATER_HOT_TRIAC_L = 1;

                    gu16AT_Heater_Data_Triac = 0;
                    gu8AT_Heater_Time1_Triac = 0;
                }
                else
                {
                    gu8AT_Heater_Time1_Triac++;

                    if( gu8AT_Heater_Time1_Triac >= 3 )
                    {
                        UARTest_NO_LOAD_Set();              // ���ʹ� �� ���ߵ�
                        pHEATER_HOT_H_RELAY = 0;
                        pHEATER_HOT_TRIAC_L = 0;
                        NOP(); NOP(); NOP(); NOP(); NOP();

                        if(gu8AT_Heater_Time1_Triac >= 12)
                        {
                            gu8AT_Heater_Time1_Triac = 12;

                            gu8UARTData[1] = AT_RS232_ACK;
                            gu8UARTData[2]= (U8)(AT_UART_CMD_HEATER / 256);     // 0x30
                            gu8UARTData[3]= (U8)(AT_UART_CMD_HEATER % 256);     // 0x50

                            // ���Ϳµ�����
                            gu8UARTData[4] = (U8)((gu16AT_Heater_Data_Relay >> 8) & 0x03);      //14 ���Ϳµ����� ��������Ʈ
                            gu8UARTData[5] = (U8)(gu16AT_Heater_Data_Relay & 0xFF);             //13 ���Ϳµ����� ��������Ʈ
                            gu8UARTData[6] = (U8)((gu16AT_Heater_Data_Triac >> 8) & 0x03);      //14 ���Ϳµ����� ��������Ʈ
                            gu8UARTData[7] = (U8)(gu16AT_Heater_Data_Triac & 0xFF);             //13 ���Ϳµ����� ��������Ʈ
                            
                            gu8UART_DataLength = 7;
                            AT_F_TxStart = 1;
                            AT_gu16_CMD_Mode = AT_UART_No_CMD;
                        }
                        else
                        {
                            if(gu16_AD_Result_Heater_Current_Feed > gu16AT_Heater_Data_Triac)
                            {
                                gu16AT_Heater_Data_Triac = gu16_AD_Result_Heater_Current_Feed;
                            }
                            else{}
                        }
                    }
                    else
                    {
                        if(gu16_AD_Result_Heater_Current_Feed > gu16AT_Heater_Data_Triac)
                        {
                            gu16AT_Heater_Data_Triac = gu16_AD_Result_Heater_Current_Feed;
                        }
                        else{}
                    }
                }
             }

             break;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
         // 0x5000 no load
         case AT_UART_CMD_NO_LOAD :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_NO_LOAD / 256);     // 0x50
            gu8UARTData[3]= (U8)(AT_UART_CMD_NO_LOAD % 256);     // 0x00
            gu8UART_DataLength = 3;
            AT_F_TxStart = 1;
            UARTest_NO_LOAD_Set();
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

         /*..hui [25-1-24���� 12:19:36] 0x5100 �����Լ���� on..*/
         case AT_UART_CMD_ROOM_IN_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ROOM_IN_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_ROOM_IN_VALVE_ON % 256);     // 0x00
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ROOM_IN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:19:36] 0x5101 �����Լ���� off..*/
         case AT_UART_CMD_ROOM_IN_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ROOM_IN_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_ROOM_IN_VALVE_OFF % 256);     // 0x01
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ROOM_IN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:19:36] 0x5102 �ü��Լ���� on..*/
         case AT_UART_CMD_COLD_IN_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COLD_IN_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_COLD_IN_VALVE_ON % 256);     // 0x02
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_COLD_IN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:19:36] 0x5103 �ü��Լ���� off..*/
         case AT_UART_CMD_COLD_IN_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COLD_IN_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_COLD_IN_VALVE_OFF % 256);     // 0x03
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_COLD_IN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:19:36] 0x5104 �¼��Լ���� on..*/
         case AT_UART_CMD_HOT_IN_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_IN_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_IN_VALVE_ON % 256);     // 0x04
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_IN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:19:36] 0x5105 �¼��Լ���� off..*/
         case AT_UART_CMD_HOT_IN_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_IN_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_IN_VALVE_OFF % 256);     // 0x05
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_IN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5106 room valve on
         case AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_ON % 256);     // 0x06
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ROOM_COLD_EXTRACT = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5107 room valve off
         case AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_ROOM_COLD_EXTRACT_VALVE_OFF % 256);     // 0x07
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ROOM_COLD_EXTRACT = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x510A hot valve on
         case AT_UART_CMD_HOT_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_VALVE_ON % 256);     // 0x0A
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_OUT = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x510B hot valve off
         case AT_UART_CMD_HOT_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_VALVE_OFF % 256);     // 0x0B
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_OUT = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

        /* ������ ������ ON Ŀ�ǵ� �߰� 250311 CH.PARK */
        case AT_UART_CMD_ICE_WATER_VALVE_ON:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_WATER_VALVE_ON / 256);     // 0x51
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_WATER_VALVE_ON % 256);     // 0x0B
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            pVALVE_ICE_WATER_EXTRACT = SET;          //
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;
            
       /* ������ ������ OFF Ŀ�ǵ� �߰� 250311 CH.PARK */
       case AT_UART_CMD_ICE_WATER_VALVE_OFF:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_WATER_VALVE_OFF / 256);     // 0x51
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_WATER_VALVE_OFF % 256);     // 0x0B
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            pVALVE_ICE_WATER_EXTRACT = CLEAR;          //
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;
            
         // 0x5110 nos valve on
         case AT_UART_CMD_NOS_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_NOS_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_NOS_VALVE_ON % 256);     // 0x10
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_NOS = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5111 nos valve off
         case AT_UART_CMD_NOS_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_NOS_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_NOS_VALVE_OFF % 256);     // 0x11
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_NOS = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:30:54] 0x5114 �¼���� NOS ON..*/
         case AT_UART_CMD_HOT_DRAIN_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_DRAIN_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_DRAIN_VALVE_ON % 256);     // 0x14
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_DRAIN = SET;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         /*..hui [25-1-24���� 12:30:54] 0x5115 �¼���� NOS OFF..*/
         case AT_UART_CMD_HOT_DRAIN_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_HOT_DRAIN_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_HOT_DRAIN_VALVE_OFF % 256);     // 0x15
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_DRAIN = CLEAR;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5116 tray in on
         case AT_UART_CMD_TRAY_IN_VALVE_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_TRAY_IN_VALVE_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_TRAY_IN_VALVE_ON % 256);     // 0x16
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ICE_TRAY_IN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5117 tray in off
         case AT_UART_CMD_TRAY_IN_VALVE_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_TRAY_IN_VALVE_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_TRAY_IN_VALVE_OFF % 256);     // 0x17
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_ICE_TRAY_IN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x5118 cold drain on
         case AT_UART_CMD_COLD_DRAIN_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COLD_DRAIN_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_COLD_DRAIN_ON % 256);     // 0x18
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_COLD_DRAIN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5119 cold drain off
         case AT_UART_CMD_COLD_DRAIN_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COLD_DRAIN_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_COLD_DRAIN_OFF % 256);     // 0x19
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_COLD_DRAIN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x512A overheating nos on
         case AT_UART_CMD_OVERHEATING_NOS_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_OVERHEATING_NOS_ON / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_OVERHEATING_NOS_ON % 256);     // 0x2A
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_COLD_OVERFLOW = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x512B overheating nos off
         case AT_UART_CMD_OVERHEATING_NOS_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_OVERHEATING_NOS_OFF / 256);     // 0x51
             gu8UARTData[3]= (U8)(AT_UART_CMD_OVERHEATING_NOS_OFF % 256);     // 0x2B
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pVALVE_HOT_COLD_OVERFLOW = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5200 cooling fan on
         case AT_UART_CMD_COOLING_FAN_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COOLING_FAN_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_COOLING_FAN_ON % 256);     // 0x00
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pDC_FAN = 1;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5201 cooling fan off
         case AT_UART_CMD_COOLING_FAN_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_COOLING_FAN_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_COOLING_FAN_OFF % 256);     // 0x01
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pDC_FAN = 0;          //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x5202 gas switch on
         case AT_UART_CMD_GAS_SWITCH_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_GAS_SWITCH_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_GAS_SWITCH_ON % 256);     // 0x02
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             F_GasSwitch_Initial = CLEAR;
             GasSwitchInit();
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5203 gas switch off
         case AT_UART_CMD_GAS_SWITCH_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_GAS_SWITCH_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_GAS_SWITCH_OFF % 256);     // 0x03
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             //
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x5206 ice tray on
         case AT_UART_CMD_ICE_TRAY_MOTOR_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_TRAY_MOTOR_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_TRAY_MOTOR_ON % 256);     // 0x06
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;

             bit_ice_tray_continue = SET;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5207 ice tray off
         case AT_UART_CMD_ICE_TRAY_MOTOR_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_TRAY_MOTOR_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_TRAY_MOTOR_OFF % 256);     // 0x07
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             sStepMotor.TargetPulse = sStepMotor.NowPulse;
             bit_ice_tray_continue = CLEAR;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x5208 ice door on
         case AT_UART_CMD_ICE_DOOR_MOTOR_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_DOOR_MOTOR_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_DOOR_MOTOR_ON % 256);     // 0x08
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             /////F_IceOpen = 1;
             bit_ice_door_continue = SET;   /* ICE DOOR (SELECT, OPEN) �ΰ� ���ÿ� ������ */

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x5209 ice door off
         case AT_UART_CMD_ICE_DOOR_MOTOR_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_DOOR_MOTOR_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_DOOR_MOTOR_OFF % 256);     // 0x09
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             
             F_IceOpen = CLEAR;
             bit_ice_door_continue = CLEAR;
             
             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x520A ice ext motor cw on
         case AT_UART_CMD_ICE_EXTRACT_MOTOR_CW_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_EXTRACT_MOTOR_CW_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_EXTRACT_MOTOR_CW_ON % 256);     // 0x0A
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pMOTOR_ICE_OUT_CW = CLEAR;
             pMOTOR_ICE_OUT_CCW = SET;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x520B ice ext motor cw off
         case AT_UART_CMD_ICE_EXTRACY_MOTOR_CW_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_EXTRACY_MOTOR_CW_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_EXTRACY_MOTOR_CW_OFF % 256);     // 0x0B
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             //
             pMOTOR_ICE_OUT_CW = CLEAR;
             pMOTOR_ICE_OUT_CCW = CLEAR;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;


         // 0x520C ice ext motor ccw on
         case AT_UART_CMD_ICE_EXTRACT_MOTOR_CCW_ON :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_EXTRACT_MOTOR_CCW_ON / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_EXTRACT_MOTOR_CCW_ON % 256);     // 0x0C
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             pMOTOR_ICE_OUT_CW = SET;
             pMOTOR_ICE_OUT_CCW = CLEAR;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;

         // 0x520D ice ext motor ccw off
         case AT_UART_CMD_ICE_EXTRACY_MOTOR_CCW_OFF :

             gu8UARTData[1] = AT_RS232_ACK;
             gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_EXTRACY_MOTOR_CCW_OFF / 256);     // 0x52
             gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_EXTRACY_MOTOR_CCW_OFF % 256);     // 0x0D
             gu8UART_DataLength = 3;

             AT_F_TxStart = 1;
             //
             pMOTOR_ICE_OUT_CW = CLEAR;
             pMOTOR_ICE_OUT_CCW = CLEAR;

             AT_gu16_CMD_Mode = AT_UART_No_CMD;

             break;
        /* [0x520E] ON ���̽� ����Ʈ ���� �߰� 250311 CH.PARK */
        case AT_UART_CMD_ICE_SELECT_MOTOR_ON:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_SELECT_MOTOR_ON / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_SELECT_MOTOR_ON % 256);     // 0x08
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            bit_ice_select_continue = SET;

            AT_gu16_CMD_Mode = AT_UART_No_CMD;
            break;

        /* [0x520F] OFF ���̽� ����Ʈ ���� �߰� 250311 CH.PARK */
        case AT_UART_CMD_ICE_SELECT_MOTOR_OFF:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_SELECT_MOTOR_OFF / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_SELECT_MOTOR_OFF % 256);     // 0x08
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;

            F_IceSelect = CLEAR;
            bit_ice_select_continue = CLEAR;
            
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
            break;

        // 0x5210 swing bar on
        case AT_UART_CMD_SWING_BAR_ON :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SWING_BAR_ON / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_SWING_BAR_ON % 256);     // 0x10
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            pSWING_BAR = SET;

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // 0x5211 swing bar off
        case AT_UART_CMD_SWING_BAR_OFF :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SWING_BAR_OFF / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_SWING_BAR_OFF % 256);     // 0x11
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            //
            pSWING_BAR = CLEAR;

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // 0x5212 �¼� ������ ON !!O.K!!
        case AT_UART_CMD_FLOW_MOTOR_OPEN:

              gu8UARTData[1] = AT_RS232_ACK;
              gu8UARTData[2]= (U8)(AT_UART_CMD_FLOW_MOTOR_OPEN / 256);     // 0x52
              gu8UARTData[3]= (U8)(AT_UART_CMD_FLOW_MOTOR_OPEN % 256);     // 0x12

              gu8UART_DataLength = 3;
              AT_F_TxStart = 1;
              /*run_decrease_flow( 1000 );*/
              run_init_flow();
              bit_hot_flow_continue = CLEAR;

              AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x5213 �¼� ������ OFF !!O.K!!
        case AT_UART_CMD_FLOW_MOTOR_CLOSE:

              gu8UARTData[1] = AT_RS232_ACK;
              gu8UARTData[2]= (U8)(AT_UART_CMD_FLOW_MOTOR_CLOSE / 256);     // 0x52
              gu8UARTData[3]= (U8)(AT_UART_CMD_FLOW_MOTOR_CLOSE % 256);     // 0x13

              gu8UART_DataLength = 3;
              AT_F_TxStart = 1;
              /*run_decrease_flow( 0 );*/
              run_decrease_flow( 1500 );
              bit_hot_flow_continue = CLEAR;

              AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x5214 �¼� ������ ON !! O.K!!
        case AT_UART_CMD_FLOW_MOTOR_CONTINUE:

              gu8UARTData[1] = AT_RS232_ACK;
              gu8UARTData[2]= (U8)(AT_UART_CMD_FLOW_MOTOR_CONTINUE / 256);     // 0x52
              gu8UARTData[3]= (U8)(AT_UART_CMD_FLOW_MOTOR_CONTINUE % 256);     // 0x14

              gu8UART_DataLength = 3;
              AT_F_TxStart = 1;

              run_init_flow();
              bit_hot_flow_continue = SET;

              AT_gu16_CMD_Mode = AT_UART_No_CMD;

        break;

        // 0x5215 �¼� ������ OFF !!O.K!!
        case AT_UART_CMD_FLOW_MOTOR_INIT:

              gu8UARTData[1] = AT_RS232_ACK;
              gu8UARTData[2]= (U8)(AT_UART_CMD_FLOW_MOTOR_INIT / 256);     // 0x52
              gu8UARTData[3]= (U8)(AT_UART_CMD_FLOW_MOTOR_INIT % 256);     // 0x15

              gu8UART_DataLength = 3;
              AT_F_TxStart = 1;
              run_init_flow();
              bit_hot_flow_continue = CLEAR;

              AT_gu16_CMD_Mode = AT_UART_No_CMD;
        break;
        /* [0x5216] ON ���� �м���� ���� 250311 CH.PARK */
        case AT_UART_CMD_ICE_BREAK_MOTOR_ON:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_BREAK_MOTOR_ON / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_BREAK_MOTOR_ON % 256);     // 0x16
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            P_OUT_ICE_CRUSH = SET;          //
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
        break;

        /* [0x5216] OFF ���� �м���� ���� 250311 CH.PARK */
        case AT_UART_CMD_ICE_BREAK_MOTOR_OFF:
            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_BREAK_MOTOR_OFF / 256);     // 0x52
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_BREAK_MOTOR_OFF % 256);     // 0x17
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            P_OUT_ICE_CRUSH = CLEAR;          //
            AT_gu16_CMD_Mode = AT_UART_No_CMD;
        break;

        // 0x5302 drain pump on
        case AT_UART_CMD_DRAIN_PUMP_ON :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_DRAIN_PUMP_ON / 256);     // 0x53
            gu8UARTData[3]= (U8)(AT_UART_CMD_DRAIN_PUMP_ON % 256);     // 0x02
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            start_drain_pump( PUMP_PWM_MAX );          //

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // 0x5303 drain pump off
        case AT_UART_CMD_DRAIN_PUMP_OFF :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_DRAIN_PUMP_OFF / 256);     // 0x53
            gu8UARTData[3]= (U8)(AT_UART_CMD_DRAIN_PUMP_OFF % 256);     // 0x03
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            //
            stop_drain_pump();

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // [0x9900] comp on
        case AT_UART_CMD_COMP_ON :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_COMP_ON / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_COMP_ON % 256);     // 0x00
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            /*pCOMP = 1;*/          //
            /* COMP ����� test_uart_comm.c�� ���ǵǾ� ���� */

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // [0x9901] comp off
        case AT_UART_CMD_COMP_OFF :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_COMP_OFF / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_COMP_OFF % 256);     // 0x01
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            //
            /*pCOMP = 0;*/          //
            /*gu8_uart_comp_start = CLEAR;*/
            gu8_uart_comp_rps = 0;

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // [0x9902] gas switch ice (����)
        case AT_UART_CMD_ICE_SWITCH_ICE :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_SWITCH_ICE / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_SWITCH_ICE % 256);     // 0x02
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            GasSwitchIce();
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;


        // [0x9903] gas switch cold (�ð�)
        case AT_UART_CMD_ICE_SWITCH_COLD :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_SWITCH_COLD / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_SWITCH_COLD % 256);     // 0x03
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            GasSwitchCold();
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // [0x9904] gas switch hotgas (Ż��)
        case AT_UART_CMD_ICE_SWITCH_HOTGAS :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_ICE_SWITCH_HOTGAS / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_ICE_SWITCH_HOTGAS % 256);     // 0x04
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            GasSwitchHotGas();
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

        // [0x9910] bldc comp error
        case AT_UART_CMD_BLDC_COMP_ERROR :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_BLDC_COMP_ERROR / 256);     // 0x99
            gu8UARTData[3]= (U8)(AT_UART_CMD_BLDC_COMP_ERROR % 256);     // 0x10

            /*..hui [24-12-2���� 10:56:50] BLDC ���� �����̸� 1, �������̸� 0..*/
            if( gu8_uart_bldc_comm_error == CLEAR )
            {
                gu8UARTData[4] = 1;
            }
            else
            {
                gu8UARTData[4] = 0;
            }

            gu8UART_DataLength = 4;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;


        // [0xFF00] complete
        case AT_UART_CMD_SYSTEM_COMPLETE :

            gu8UARTData[1] = AT_RS232_ACK;
            gu8UARTData[2]= (U8)(AT_UART_CMD_SYSTEM_COMPLETE / 256);     // 0xFF
            gu8UARTData[3]= (U8)(AT_UART_CMD_SYSTEM_COMPLETE % 256);     // 0x00
            gu8UART_DataLength = 3;

            AT_F_TxStart = 1;
            UARTest_NO_LOAD_Set();
            F_Uart_Final = 1;

            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

        default :

            gu8UARTData[1] = AT_RS232_NAK;
            gu8UARTData[2] = (U8)(AT_gu16_CMD_Mode / 256);
            gu8UARTData[3] = (U8)(AT_gu16_CMD_Mode % 256);

            gu8UART_DataLength = 3;
            AT_F_TxStart = 1;
            AT_gu16_CMD_Mode = AT_UART_No_CMD;

            break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void UARTest_NO_LOAD_Set(void)
{
    /*p12V_POWER = CLEAR;*/
    pUV_LED_WATER_FAUCET = CLEAR;
    pUV_LED_ICE_FAUCET_1 = CLEAR;
    pUV_LED_ICE_FAUCET_2 = CLEAR;
    pUV_LED_ICE_TANK_1_2 = CLEAR;
    pUV_LED_ICE_TRAY_1_2 = CLEAR;
    pUV_LED_ICE_TANK_3 = CLEAR;

    /*..hui [23-4-4���� 3:06:47] Ʈ���� �׽�Ʈ �Ϸ� ���� ��� �׽�Ʈ �����Ҽ�����..*/
    #if 0
    if( gu8_uart_ice_tray_test_step >= 4 )
    {
        pMOTOR_ICE_TRAY_CW = CLEAR;
        pMOTOR_ICE_TRAY_CCW = CLEAR;
    }
    else{}
    #endif

    pMOTOR_ICE_OUT_CW = CLEAR;
    pMOTOR_ICE_OUT_CCW = CLEAR;
    pCOMP = CLEAR;

    #if 0
    if( gu8_uart_hot_heater == SET )
    {
        gu8_uart_hot_heater = CLEAR;
        gu8_uart_hot_heater_finish = SET;
    }
    else{}
    #endif

    pHEATER_HOT_H_RELAY = CLEAR;
    pHEATER_HOT_TRIAC_L = CLEAR;

    /* �������� ���� */
    pHEATER_ICE_DOOR = CLEAR;
    
    /* �м���� �߰� */
    P_OUT_ICE_CRUSH = CLEAR;

    pSWING_BAR = CLEAR;
    pDC_FAN = CLEAR;
    pIR_POWER = CLEAR;
    pIR_POWER2 = CLEAR;

    pVALVE_ROOM_IN = CLEAR;
    pVALVE_COLD_IN = CLEAR;
    pVALVE_HOT_IN = CLEAR;
    pVALVE_HOT_OUT = CLEAR;
    pVALVE_HOT_DRAIN = CLEAR;
    pVALVE_ICE_TRAY_IN = CLEAR;
    pVALVE_COLD_DRAIN = CLEAR;
    pVALVE_NOS = CLEAR;
    pVALVE_ROOM_COLD_EXTRACT = CLEAR;
    pVALVE_HOT_COLD_OVERFLOW = CLEAR;
    pVALVE_ICE_WATER_EXTRACT = CLEAR;   /* ������ ������ �߰� */

    bit_hot_flow_continue = CLEAR;
    bit_ice_door_continue = CLEAR;
    bit_ice_select_continue = CLEAR;
    bit_ice_tray_continue = CLEAR;

    stop_drain_pump();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


