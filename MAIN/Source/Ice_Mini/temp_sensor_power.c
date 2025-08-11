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
#include    "temp_sensor_power.h"

void output_temp_power(void);
void output_room_temp_power(void);
void output_cold_temp_power(void);

/***********************************************************************************************************************/
TYPE_BYTE          U8RoomTempPowerONB;
#define            u8RoomTempPowerON                        U8RoomTempPowerONB.byte
#define            Bit0_Room_Temp_Ice_Making_Read_State     U8RoomTempPowerONB.Bit.b0
#define            Bit1_Room_Temp_Hot_Extarct_State         U8RoomTempPowerONB.Bit.b1
#define            Bit2_Room_Temp_Error_State               U8RoomTempPowerONB.Bit.b2
#define            Bit3_Room_Temp_Init_State                U8RoomTempPowerONB.Bit.b3
#define            Bit4_Room_Temp_Doctor_Test_State         U8RoomTempPowerONB.Bit.b4
#define            Bit5_Room_Temp_Periodic_Read_State       U8RoomTempPowerONB.Bit.b5
#define            Bit6_Room_Temp_Self_Test_State           U8RoomTempPowerONB.Bit.b6


TYPE_BYTE          U8ColdTempPowerONB;
#define            u8ColdTempPowerON                        U8ColdTempPowerONB.byte
#define            Bit0_Cold_Temp_Periodic_Read_State       U8ColdTempPowerONB.Bit.b0
#define            Bit1_Cold_Temp_Error_State               U8ColdTempPowerONB.Bit.b1
#define            Bit2_Cold_Temp_Init_State                U8ColdTempPowerONB.Bit.b2
#define            Bit3_Cold_Temp_Doctor_Test_State         U8ColdTempPowerONB.Bit.b3
#define            Bit4_Cold_Temp_Extract_State             U8ColdTempPowerONB.Bit.b4
#define            Bit5_Cold_Temp_Self_Test_State           U8ColdTempPowerONB.Bit.b5


/***********************************************************************************************************************/

U16 u16_cold_power_timer;
U16 u16_room_power_timer;

U16 u16_temp_power_init_timer;

U8 u8_cold_adc_on_delay_timer;
U8 u8_cold_adc_off_delay_timer;
bit bit_adc_cold_start;

U8 u8_room_adc_on_delay_timer;
U8 u8_room_adc_off_delay_timer;
bit bit_adc_room_start;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_temp_power(void)
{
    output_room_temp_power();
    output_cold_temp_power();

    //pROOM_TH_POWER = SET;
    //pCOLD_TH_POWER = SET;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_room_temp_power(void)
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 1:30:08] �����Ҷ� ���̽�Ʈ���� �Լ� ~ ����ON �������� ���� ON..*/
    if(  gu8IceStep >= STATE_20_WATER_IN_ICE_TRAY
      && gu8IceStep <= STATE_30_CALC_ICE_MAKING_TIME )
    {
        Bit0_Room_Temp_Ice_Making_Read_State = SET;
    }
    else
    {
        Bit0_Room_Temp_Ice_Making_Read_State = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    /*..hui [19-12-19���� 1:31:53] �¼� ������ ���� �µ����� ���� ���� ON..*/
    if( F_Model_Select == MODEL_CHPI )
    {
        if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
        {
            Bit1_Room_Temp_Hot_Extarct_State = SET;
        }
        else
        {
            Bit1_Room_Temp_Hot_Extarct_State = CLEAR;
        }
    }
    else
    {
        Bit1_Room_Temp_Hot_Extarct_State = CLEAR;
    }
    #endif

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 1:36:43] �������� ���� �߻� �� ���� ���� ON / �ڵ����� ����..*/
    /*Bit2_Room_Temp_Error_State = Bit2_Room_Temp_Open_Short_Error__E42;*/

    /*..hui [23-12-18���� 2:22:07] ���� ���������϶��� �׽� ON..*/
    Bit2_Room_Temp_Error_State = Bit2_Room_Temp_Open_Short_Error__E42;

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 5:51:06] �ʱ� ���� �ΰ� �� 1�� ���� ����..*/
    u16_temp_power_init_timer++;

    /*..hui [23-6-9���� 5:59:57] 10������ ����.. �����缭 ����..*/
    if(u16_temp_power_init_timer >= 6000)
    {
        u16_temp_power_init_timer = 6000;
        Bit3_Room_Temp_Init_State = CLEAR;
    }
    else
    {
        Bit3_Room_Temp_Init_State = SET;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [20-2-17���� 5:58:13] �ڵ� �׽�Ʈ ��� �� ������ ��忡���� ON..*/
    #if 0
    if( gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        Bit4_Room_Temp_Doctor_Test_State = SET;
    }
    else
    {
        Bit4_Room_Temp_Doctor_Test_State = CLEAR;
    }
    #endif


    u16_room_power_timer++;

    if( u16_room_power_timer <= COLD_TEMP_POWER_ON_TIME)
    {
        Bit5_Room_Temp_Periodic_Read_State = SET;
    }
    else
    {
        Bit5_Room_Temp_Periodic_Read_State = CLEAR;

        if( u16_room_power_timer >= COLD_TEMP_POWER_OFF_TIME)
        {
            u16_room_power_timer = 0;
        }
        else{}
    }

    Bit6_Room_Temp_Self_Test_State = bit_self_test_start;

    ////////////////////////////////////////////////////////////////////////////////////////////
    if( u8RoomTempPowerON > 0 )
    {
        /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
        pROOM_TH_POWER = SET;

        /*u8_room_adc_off_delay_timer = 0;*/

        u8_room_adc_on_delay_timer++;

        /*..hui [20-1-22���� 10:00:48] ���� �Ѱ� 1s �� �µ����� ����..*/
        if( u8_room_adc_on_delay_timer >= ADC_DELAY_ON_DELAYTIME )
        {
            u8_room_adc_on_delay_timer = ADC_DELAY_ON_DELAYTIME;
            bit_adc_room_start = SET;
        }
        else{}
    }
    else
    {
        /*..hui [19-12-19���� 1:26:51] ���� �µ����� ���� OFF..*/
        /*..hui [20-1-29���� 1:51:28] ���� �����ð��� ����..*/
        pROOM_TH_POWER = CLEAR;
        bit_adc_room_start = CLEAR;

        u8_room_adc_on_delay_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_cold_temp_power(void)
{

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 2:14:18] 10�� ON 50�� OFF �ݺ�..*/
    /*..hui [19-12-19���� 4:53:10] �ü� �������� ��쿡��..*/
    if( F_Cold_Enable == SET )
    {
        u16_cold_power_timer++;

        if( u16_cold_power_timer <= COLD_TEMP_POWER_ON_TIME)
        {
            Bit0_Cold_Temp_Periodic_Read_State = SET;
        }
        else
        {
            Bit0_Cold_Temp_Periodic_Read_State = CLEAR;

            if( u16_cold_power_timer >= COLD_TEMP_POWER_OFF_TIME)
            {
                u16_cold_power_timer = 0;
            }
            else{}
        }
    }
    else
    {
        u16_cold_power_timer = 0;
        Bit0_Cold_Temp_Periodic_Read_State = CLEAR;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 1:36:43] �ü����� ���� �߻� �� ���� ���� ON / �ڵ����� ����..*/
    Bit1_Cold_Temp_Error_State = Bit14_Cold_Temp_Open_Short_Error__E44;

    ////////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-12-19���� 5:51:06] �ʱ� ���� �ΰ� �� 1�� ���� ����..*/
    Bit2_Cold_Temp_Init_State = Bit3_Room_Temp_Init_State;

    ////////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    if( gu8_Led_Display_Step == LED_Display__DEBUG )
    {
        Bit3_Cold_Temp_Doctor_Test_State = SET;
    }
    else
    {
        Bit3_Cold_Temp_Doctor_Test_State = CLEAR;
    }
    #endif
    ////////////////////////////////////////////////////////////////////////////////////////////
    if( F_WaterOut == SET )
    {
        #if 0
        /*..hui [23-12-18���� 2:25:29] �¼� �Ǵ� ���� �����Ҷ� �ü� �µ������� ����ϹǷ�....*/
        if( u8WaterOutState == HOT_WATER_SELECT || u8WaterOutState == PURE_WATER_SELECT )
        {
            Bit4_Cold_Temp_Extract_State = SET;
        }
        else
        {
            Bit4_Cold_Temp_Extract_State = CLEAR;
        }
        #endif

        /*..hui [23-12-18���� 3:03:44] �ü� �����ҋ��� ON.. �ü� �����Ҷ� �ü� �µ� ��ȭ�� ����� �ֱ⶧��..*/
        Bit4_Cold_Temp_Extract_State = SET;
    }
    else
    {
        /*..hui [23-12-18���� 2:27:27] ������ ���ϴ��� �¼� ���� ���¿����� 7�� ���� ���������� �е���..*/
        if( u8WaterOutState == HOT_WATER_SELECT )
        {
            Bit4_Cold_Temp_Extract_State = SET;
        }
        else
        {
            Bit4_Cold_Temp_Extract_State = CLEAR;
        }
    }

    Bit5_Cold_Temp_Self_Test_State = bit_self_test_start;

    ////////////////////////////////////////////////////////////////////////////////////////////
    if( u8ColdTempPowerON > 0 )
    {
        /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
        pCOLD_TH_POWER = SET;

        /*u8_cold_adc_off_delay_timer = 0;*/

        u8_cold_adc_on_delay_timer++;

        /*..hui [20-1-22���� 10:00:48] ���� �Ѱ� 500ms �� �µ����� ����..*/
        if( u8_cold_adc_on_delay_timer >= ADC_DELAY_ON_DELAYTIME )
        {
            u8_cold_adc_on_delay_timer = ADC_DELAY_ON_DELAYTIME;
            bit_adc_cold_start = SET;
        }
        else{}
    }
    else
    {
        /*..hui [19-12-19���� 1:27:27] �ü� �µ����� ���� OFF..*/
        /*..hui [20-1-29���� 1:51:28] ���� �����ð��� ����..*/
        pCOLD_TH_POWER = CLEAR;
        bit_adc_cold_start = CLEAR;

        u8_cold_adc_on_delay_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


