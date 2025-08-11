/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Output.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M5_Output.h"

void Output(void);
//void output_swing_bar(void);
//void IceWaterExtrate(void);
//void output_feed_valve(void);
void output_valve_ice_tray_feed3(void) ;
//void CyclePump(void);
//void start_drain_pump( U16 u16_data );
//void stop_drain_pump( void );
void output_valve(void);
void output_pump(void);








bit F_IceWaterExt;
U8 gu8IceWaterExtDelay;
bit F_IceWaterExt_Set;


bit F_LineTestEnd;


U8 u8_system_init_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Output(void)
{
    output_swing_bar();

    output_ac_motor();

    output_comp_control();

    output_fan();

    output_pump();

    output_valve();

    ControlGasSwitch();

    /* �����м� DC���� ���� �߰� 250217 CH.PARK */
    MOTOR_ICE_BREAK_OUTPUT();

    /*..hui [19-10-24���� 7:59:26] UV ���� ��� �߰�..*/
    output_ice_tank_uv();
    output_ice_tray_uv();
    output_ice_faucet_uv();
    output_extract_faucet_uv();

    /*..hui [23-6-1���� 3:10:46] ���÷��� �����ð� ǥ�ÿ�..*/
    /////calc_uv_remain_time();

    /*..hui [19-12-19���� 2:15:31] ����/�ü� ���� ���� ON/OFF ��� �߰�..*/
    output_temp_power();

    /*..hui [23-3-24���� 11:26:27] �ν�Ʈ ���� ��� �߰�..*/
    /*output_boost_pump();*/

    /* �ϴ� �������� ���ʹ� 100ms ������ 100% ������� ���� - H/W��Ʈ Ȯ�οϷ� 250228 CH.PARK */
    OUTPUT_HEATER_ICE_DOOR();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_pump(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    output_drain_pump();

    /*..hui [23-2-6���� 11:00:45] Ʈ���� ����.. �¼� ���������� ����..*/
    //////output_tray_pump();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve(void)
{
    /*..hui [19-7-18���� 5:01:36] ���� �� ���������� ��ٸ���..*/
    #if 0
    if(u8_system_init_timer < 50)
    {
        u8_system_init_timer++;
        return;
    }
    else
    {
        u8_system_init_timer = 50;
    }
    #endif

    if(u8_system_init_timer < 30)
    {
        u8_system_init_timer++;
        return;
    }
    else
    {
        u8_system_init_timer = 30;
    }

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    /* ������ ������ ���� 250212 CH.PARK */
    OUTPUT_VALVE_ICE_WATER_OUT_FEED6();

    /*..hui [24-12-16���� 4:52:02] NOS ���..*/
    output_valve_nos();

    /*..hui [24-12-16���� 4:52:05] ���� �Լ� ���..*/
    output_valve_room_in_feed1();

    /*..hui [24-12-16���� 4:52:09] �ü� �Լ� ���..*/
    output_valve_cold_in_feed2();

    /*..hui [24-12-16���� 4:52:12] �¼� �Լ� ���..*/
    output_valve_hot_in_feed9();

    /*..hui [24-12-16���� 4:52:15] �¼� �巹�� ���..*/
    output_valve_hot_drain_nos7();

    /*..hui [24-12-16���� 5:23:48] �¼� ������..*/
    output_valve_hot_out_feed_8();

    /*..hui [24-12-16���� 4:52:18] ���� / �ü� ���� ���..*/
    output_valve_room_cold_extract_feed5();

    /*..hui [24-12-16���� 4:52:22] ���̽� Ʈ���� �Լ� ���..*/
    output_valve_ice_tray_feed3();

    /*..hui [24-12-16���� 4:52:29] �ü� / �¼� �����÷ο� ���..*/
    output_valve_overflow_nos4();

    /*..hui [24-12-16���� 4:52:33] �ü� ��� ���..*/
    output_cold_drain_valve_feed6();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


