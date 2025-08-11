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
#include    "cody_tray_test.h"


void start_ice_tray_test(void);
void cody_ice_tray_test(void);
void stop_ice_tray_test_mode(void);


U8 u8_ice_tray_test_step;
U8 u8_ice_tray_test_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_ice_tray_test(void)
{
    if( F_All_Lock == SET)
    {
        return;
    }
    else{}

    Bit2_Ice_Tray_Test_Start = SET;
    stop_ice_tray_test_mode();
    play_melody_setting_on_198();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_ice_tray_test(void)
{
    //if( gu8_Lcd_Display_Step != LCD_Display_CODY_INSPECT)
    //{
    //    Bit2_Ice_Tray_Test_Start = CLEAR;
    //}
    //else{}

    if(Bit2_Ice_Tray_Test_Start == CLEAR)
    {
        u8_ice_tray_test_step = 0;
        u8_ice_tray_test_timer = 0;
        return;
    }
    else{}

    if( u8_ice_tray_test_step >= 1 && u8_ice_tray_test_step <= 4 )
    {
        if( F_Ice_Tray_Up_Move_Reset == SET 
        || F_Ice_Tray_Down_Move_Reset == SET 
        || F_ErrTrayMotor_DualInital == SET )
        {
            play_melody_warning_197();
            u8_ice_tray_test_step = 6;
        }
        else{}
    }
    else{}

    switch( u8_ice_tray_test_step )
    {
        case 0:

            u8_ice_tray_test_timer++;

            if( u8_ice_tray_test_timer >= 10 )
            {
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
                reset_micro_sw_move_err_check_state();
            }
            else{}

            break;

        case 1:

            /*..hui [20-2-26���� 8:41:12] �̵��ϴ��� �Ϸ� �� �����ܰ� �̵�..*/
            /*if( F_TrayMotorUP == CLEAR && F_TrayMotorDOWN == CLEAR )*/
            /*..hui [23-7-21���� 5:47:38] �ְ��� Ż�� ������ ����忡����..*/
            /*..hui [23-7-21���� 5:47:45] Ʈ���̿� ���� ������������..*/
            //if( F_TrayMotorUP == CLEAR && F_TrayMotorDOWN == CLEAR && gu8IceStep == STATE_0_STANDBY )
			if( F_TrayMotorUP == CLEAR 
            && F_TrayMotorDOWN == CLEAR 
            && gu8IceStep == STATE_0_STANDBY )
            {
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }
            else{}

            break;

        case 2:

            /*..hui [20-4-28���� 12:43:42] �������� ��ġ�������� �ٷ� Ʈ���� ����..*/
            /*..hui [20-4-28���� 12:44:00] �� �� Ż�� ���� �Ǵ� �̵����̸� Ʈ���� �ø�..*/
            if( gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING )
            {
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }
            else
            {
                /*.. sean [25-02-05] Ʈ���� �̰��� �̽��� ���ܸ��� pulse �߰�..*/
                up_tray_motor();        // �ڵ����� �� ���
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }

            break;

        case 3:
            if(F_TrayMotorUP != SET 
            && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
			{
                /*.. sean [25-02-05] Ʈ���� �̰��� �̽��� ���ܸ��� pulse �߰�..*/
                down_tray_motor();
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }
            else{}

            break;

        case 4:
            /* Ż����ġ ���� */
            if(F_TrayMotorDOWN != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_THROW)
            {
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }
            else{}

            break;

        case 5:
            u8_ice_tray_test_timer++;
            if(u8_ice_tray_test_timer >= 20)
            {
                u8_ice_tray_test_timer = 0;
                u8_ice_tray_test_step++;
            }
            else{}

            break;

        case 6:

            Bit2_Ice_Tray_Test_Start = CLEAR;
            u8_ice_tray_test_timer = 0;
            u8_ice_tray_test_step = 0;
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;

            reset_micro_sw_move_err_check_state();
            gu8_Err_Tray_Down_Count = 0;
            gu8_err_tray_down_acc_count = 0;
            gu8_Err_Tray_Up_Count = 0;

            break;

        default:

            u8_ice_tray_test_step = 0;

            break;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_ice_tray_test_mode(void)
{
    if( F_IceInit == SET )
    {
        /*..hui [20-2-19���� 3:26:02] ����Ż�� ��� �� �Ǵ� ���� �� ���� Ż���ϸ� ����Ż�� ���..*/
        /*..hui [20-2-19���� 3:26:14] ���νİ� ���� ���̽��Ҵ� ����..*/
        F_IceInit = CLEAR;
        gu8InitStep = 0;
        gu16IceMakeTime = 0;
        gu16IceHeaterTime = 0;
    }
    else
    {
        if( gu8IceStep != STATE_0_STANDBY )
        {
            if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP
                && gu8IceStep <= STATE_30_CALC_ICE_MAKING_TIME )
            {
                if( F_Comp_Output == CLEAR )
                {   
                    /*..hui [20-1-29���� 3:48:29] ���� ���ܰ��̸� �ٷ� ����üũ �� ����..*/
                    /*..hui [20-2-19���� 7:46:55] ���� - ���� �ȵ����Ƿ� ���� üũ ���� ��� ����..*/
                    gu8IceStep = STATE_51_FINISH_ICE_MAKE;
                    /*.. sean [25-02-05] Ʈ���� �̰��� �̽��� ���ܸ��� pulse �߰�..*/
                    down_tray_motor();
                }
                else
                {
                    /*..hui [23-7-21���� 5:43:03] ��������.. ������ �������̸� �ְ��� Ż������..*/
                    gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;
                    /*.. sean [25-02-05] Ʈ���� �̰��� �̽��� ���ܸ��� pulse �߰�..*/
                    down_tray_motor();
                }
            }
            else if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
            {
                /*..hui [23-7-21���� 5:35:02] ���� �ð��� ������� ������ �ְ��� Ż�� ����.. ..*/
                /*..hui [23-7-21���� 5:35:20] �õ�.. ���¿��� �ְ��� Ż���ص� ������ ��������..*/
                gu16IceMakeTime = 0;
            }
            else if( gu8IceStep >= STATE_40_ICE_TRAY_MOVE_DOWN
                     && gu8IceStep <= STATE_43_ICE_TAKE_OFF )
            {
                /*..hui [20-1-29���� 3:47:24] Ż�� �̵����̰ų� Ż�����ϰ�� �ϴ��� ��� ����..*/

            }
            else{}
        }
        else{}
    }
}


