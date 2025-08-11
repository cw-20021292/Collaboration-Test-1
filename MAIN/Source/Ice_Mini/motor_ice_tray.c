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
#include    "motor_ice_tray.h"


U8 icetray_check_E61();
U8 icetray_check_E62_E63();


void icetray_control(void);
void icetray_abnormal_control(void);
void motor_ice_tray_output(void);
void Set_Step_Direction(U8      direction, U16 Pulse);


void control_ice_tray(void);
U8 init_ice_tray(void);
U8 up_ice_tray( void );
U8 down_ice_tray( void );
void control_ice_tray_motor( void );
void ice_tray_motor_movestep( void );
void ice_tray_motor_operation( U8 mode );
void run_init_ice_tray(void);
void run_down_ice_tray(void);
void run_up_ice_tray(void);
void run_stop_ice_tray(void);

extern void GasSwitchHotGas(void);
extern U16 get_hotgas_time(void);
extern U8 hot_gas_operation(void);
extern U8 get_hotgas_mode_comp_rps(void);
extern void set_comp_rps( U8 mu8_target );
extern void up_tray_motor(void);
extern void stop_tray_motor(void);
extern void down_tray_motor(void);

U16 gu16_ro_drain_target;
U16 gu16_ro_drain_current;

U8 gu8_ro_drain_hold_start_step;
U8 gu8_ro_drain_hold_stop_step;


U8 gu8_ice_tray_current_step;
U8 gu8_ice_tray_prev_step;

const U8 gu8IceTrayPhaseTable[ ICE_TRAY_STEP_NUM ] =
{ 0x01, 0x02, 0x03, 0x04 };

U8 gu8_ro_drain_mode;

U8 gu8_ro_drain_init_step;
U8 gu8_ro_drain_open_step;
U8 gu8_ro_drain_close_step;

U8 gu8_ice_tray_mode;

U16 gu16_ice_tray_target;
U16 gu16_ice_tray_current;
U8 gu8_ice_tray_init_step;
U8 gu8_ice_tray_up_step;
U8 gu8_ice_tray_down_step;
U16 gu16_ice_tray_moving_pulse;
U8 gu8_ice_tray_hold_start_step;
U8 gu8_ice_tray_hold_stop_step;

U16 gu16_ro_drain_open_pulse;
U16 gu16_ro_drain_close_pulse;

U16 gu16_ro_drain_moving_pulse;
U8 gu8_ice_tray_status;
//U8 gu8_11111111;
//U8 gu8_22222222;
U8 gu8_ro_drain_status;

bit F_DoorCW_A;                    // ��� �� ICE Door Reset
U16 gu16StepMotor2_A;
U8 gu8_E62_dummy_iceheat_flag;
bit Bit_E63_Error;
U8 gu8_ice_tray_down_timer;

extern bit F_IceTray;
extern bit F_IceOut;
extern U8 gu8IceClose;
extern bit F_IceInit;
extern U16 gu16IceHeaterTime;
extern ICE_STEP gu8IceStep;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#define MAX_STEP 5000

tsSTEPMOTOR sStepMotor;

ICETRAY_STATE icetray_state_current;
ICETRAY_STATE icetray_state_target;

U16 gu16_icetray_check_timer = 0;
U8 gu8_icetray_check_cnt = 0; 

U16 gu16_E61_check_timer = 0;
U8 gu8_E61_check_cnt = 0;

extern U8 gu8IceTrayLEV;

U16 tray_error_cnt_E61;
U16 tray_error_cnt_E62;
U16 tray_error_cnt_E63;


U8 tray_error_flag_E61;
U8 tray_error_flag_E62;
U8 tray_error_flag_E63;


typedef enum
{
	ABNORMAL_1_,
}ABNORMAL_1;

typedef enum
{
	ABNORMAL_2_,
}ABNORMAL_2;

U16 tray_abnormal_E62_timer;
U16 tray_abnormal_E63_timer;
U8 tray_abnormal_E62_step;
U8 tray_abnormal_E63_step;
U8 abnormal_1_repeat_cnt;
U8 abnormal_2_repeat_cnt;

void control_ice_tray(void)
{
    U8 mu8Ret = FALSE;

    /* Init */
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_INIT )
    {
        mu8Ret = init_ice_tray();
        if( mu8Ret == TRUE )
        {
            gu8_ice_tray_mode = ICE_TRAY_MODE_NONE;
            gu8_ice_tray_init_step = 0;
            gu8_ice_tray_status = ICE_TRAY_STATUS_DOWN;
        }
        else{}

        return;
    }

    /* DOWN */
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_DOWN )
    {
        mu8Ret = down_ice_tray();
        if( mu8Ret == TRUE )
        {
            gu8_ice_tray_mode = ICE_TRAY_MODE_NONE;
            gu8_ice_tray_down_step = 0;
            gu8_ice_tray_status = ICE_TRAY_STATUS_DOWN;
        }
        else{}

        return;
    }

    /* UP */
    if( gu8_ice_tray_mode == ICE_TRAY_MODE_UP )
    {
        mu8Ret = up_ice_tray();
        if( mu8Ret == TRUE )
        {
            gu8_ice_tray_mode = ICE_TRAY_MODE_NONE;
            gu8_ice_tray_up_step = 0;
            gu8_ice_tray_status = ICE_TRAY_STATUS_UP;
        }
        else{}

        return;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 init_ice_tray(void)
{
    switch( gu8_ice_tray_init_step )
    {
        case 0:

            ////gu16_ice_tray_target = 0;

            gu16_ice_tray_current = ICE_TRAY_INIT_PULSE;
            gu16_ice_tray_target = 0;

            gu8_ice_tray_init_step++;
            break;

        case 1:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu16_ice_tray_target = 0;
                gu16_ice_tray_current = 0;
                gu8_ice_tray_init_step++;
            }
            break;

        case 2:
            return TRUE;

    }

    return FALSE;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 up_ice_tray( void )
{
    switch( gu8_ice_tray_up_step )
    {
        case 0:

            gu8_ice_tray_hold_start_step = ICE_TRAY_HOLD_STEP;
            gu8_ice_tray_hold_stop_step = ICE_TRAY_HOLD_STEP;

            #if 0
            if( gu16_ice_tray_target > gu16_ice_tray_moving_pulse )
            {
                gu16_ice_tray_target = gu16_ice_tray_target - gu16_ice_tray_moving_pulse;
            }
            else
            {
                gu16_ice_tray_target = 0;
            }
            #endif

            /*..hui [25-3-17���� 2:24:09] �ִ� �޽���ŭ ���� �ø�..*/
            gu16_ice_tray_target = ICE_TRAY_UP_PULSE;
            gu16_ice_tray_current = 0;

            gu8_ice_tray_up_step++;

            break;

        case 1:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_up_step++;
                gu16_ice_tray_moving_pulse = 0;
            }
            else{}

            break;

        case 2:
            return TRUE;

    }

    return FALSE;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 down_ice_tray( void )
{
    U8 mu8_delay_time = 0;

    if( u8FactoryTestMode == UART_TEST_MODE )
    {
        mu8_delay_time = 1;
    }
    else
    {
        mu8_delay_time = ICE_TRAY_DOWN_DELAY_TIME;
    }

    switch( gu8_ice_tray_down_step )
    {
        case 0:

            gu8_ice_tray_hold_start_step = ICE_TRAY_HOLD_STEP;
            gu8_ice_tray_hold_stop_step = ICE_TRAY_HOLD_STEP;

            /*gu16_ice_tray_target = gu16_ice_tray_target + gu16_ice_tray_moving_pulse;*/
            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_1;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 1:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 2:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_2;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 3:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 4:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_3;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 5:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 6:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_4;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 7:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 8:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_5;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 9:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 10:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_6;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 11:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 12:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_7;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 13:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 14:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_8;
            gu8_ice_tray_down_timer = 0;

            gu8_ice_tray_down_step++;
            break;

        case 15:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_timer++;

                /*if( gu8_ice_tray_down_timer >= ICE_TRAY_DOWN_DELAY_TIME )*/
                if( gu8_ice_tray_down_timer >= mu8_delay_time )
                {
                    gu8_ice_tray_down_step++;
                    gu16_ice_tray_moving_pulse = 0;
                    gu8_ice_tray_down_timer = 0;
                }
                else{}
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
        case 16:

            gu16_ice_tray_target = 0;
            /*..hui [25-3-17���� 2:24:27] �������� ����ֵ� �ִ� ���޽���ŭ ������..*/
            gu16_ice_tray_current = ICE_TRAY_DOWN_PULSE_STEP_9;

            gu8_ice_tray_down_step++;
            break;

        case 17:

            if( gu16_ice_tray_target == gu16_ice_tray_current )
            {
                gu8_ice_tray_down_step++;
                gu16_ice_tray_moving_pulse = 0;
            }
            break;

        case 18:
            return TRUE;

    }

    return FALSE;


}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void control_ice_tray_motor( void )
{
    S16 val = 0;
    S16 target = 0;
    S16 current = 0;

    /* CALC STEP, TARGET - CURRENT */
    ice_tray_motor_movestep();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_tray_motor_movestep( void )
{
    U8 val = 0;

    /* START HOLD */
    if( gu8_ice_tray_hold_start_step > 0 )
    {
        gu8_ice_tray_hold_start_step--;
        val = gu8IceTrayPhaseTable[ gu8_ice_tray_prev_step ];
    }
    else if( gu16_ice_tray_current == gu16_ice_tray_target )
    {
        /* STOP HOLD */
        if( gu8_ice_tray_hold_stop_step > 0 )
        {
            gu8_ice_tray_hold_stop_step--;
            val = gu8IceTrayPhaseTable[ gu8_ice_tray_current_step ];
        }
        else
        {
            /* STOP */
            val = 0x00;
        }
    }
    /* MOVE FORWARD */
    else if( gu16_ice_tray_current < gu16_ice_tray_target )
    {
        /* OPEN */
        /*..hui [21-6-24���� 2:24:48] ������ ���� ���̱��..*/
        gu16_ice_tray_current++;

        #if 0
        if(gu8_ice_tray_current_step == 0)
        {
            gu8_ice_tray_current_step = ICE_TRAY_STEP_NUM - 1;
        }
        else
        {
            gu8_ice_tray_current_step--;
        }
        #endif

        gu8_ice_tray_current_step++;

        if( gu8_ice_tray_current_step >= ICE_TRAY_STEP_NUM )
        {
            gu8_ice_tray_current_step = 0;
        }
        else{}

        gu8_ice_tray_prev_step = gu8_ice_tray_current_step;

        val = gu8IceTrayPhaseTable[ gu8_ice_tray_current_step ];
    }
    /* MOVE BACKWARD */
    else if( gu16_ice_tray_current > gu16_ice_tray_target )
    {
        /* CLOSE */
        gu16_ice_tray_current--;

        #if 0
        gu8_ice_tray_current_step++;
        if( gu8_ice_tray_current_step >= ICE_TRAY_STEP_NUM )
        {
            gu8_ice_tray_current_step = 0;
        }
        else{}
        #endif

        if(gu8_ice_tray_current_step == 0)
        {
            gu8_ice_tray_current_step = ICE_TRAY_STEP_NUM - 1;
        }
        else
        {
            gu8_ice_tray_current_step--;
        }

        gu8_ice_tray_prev_step = gu8_ice_tray_current_step;

        val = gu8IceTrayPhaseTable[ gu8_ice_tray_current_step ];
    }
    else{}

    ice_tray_motor_operation( val );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_tray_motor_operation( U8 mode )
{
    switch( mode )
    {
        case 0:

            pSTEP_MOTOR_ICE_TRAY_1  = 0;
            pSTEP_MOTOR_ICE_TRAY_2  = 0;
            pSTEP_MOTOR_ICE_TRAY_3  = 0;
            pSTEP_MOTOR_ICE_TRAY_4  = 0;

            break;

        case 1:

            pSTEP_MOTOR_ICE_TRAY_1 = 1;
            pSTEP_MOTOR_ICE_TRAY_2 = 0;
            pSTEP_MOTOR_ICE_TRAY_3 = 0;
            pSTEP_MOTOR_ICE_TRAY_4 = 1;

            break;

        case 2:

            pSTEP_MOTOR_ICE_TRAY_1 = 1;
            pSTEP_MOTOR_ICE_TRAY_2 = 1;
            pSTEP_MOTOR_ICE_TRAY_3 = 0;
            pSTEP_MOTOR_ICE_TRAY_4 = 0;

            break;

        case 3:

            pSTEP_MOTOR_ICE_TRAY_1 = 0;
            pSTEP_MOTOR_ICE_TRAY_2 = 1;
            pSTEP_MOTOR_ICE_TRAY_3 = 1;
            pSTEP_MOTOR_ICE_TRAY_4 = 0;

            break;

        case 4:

            pSTEP_MOTOR_ICE_TRAY_1 = 0;
            pSTEP_MOTOR_ICE_TRAY_2 = 0;
            pSTEP_MOTOR_ICE_TRAY_3 = 1;
            pSTEP_MOTOR_ICE_TRAY_4 = 1;

            break;

        default:

            pSTEP_MOTOR_ICE_TRAY_1  = 0;
            pSTEP_MOTOR_ICE_TRAY_2  = 0;
            pSTEP_MOTOR_ICE_TRAY_3  = 0;
            pSTEP_MOTOR_ICE_TRAY_4  = 0;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_init_ice_tray(void)
{
    gu8_ice_tray_mode = ICE_TRAY_MODE_INIT;
    gu8_ice_tray_init_step = 0;
    gu8_ice_tray_up_step = 0;
    gu8_ice_tray_down_step = 0;
    gu16_ice_tray_moving_pulse = 0;

    gu8_ice_tray_hold_start_step = ICE_TRAY_HOLD_STEP;
    gu8_ice_tray_hold_stop_step = ICE_TRAY_HOLD_STEP;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_down_ice_tray(void)
{
    if( gu8_ice_tray_mode != ICE_TRAY_MODE_DOWN )
    {
        gu8_ice_tray_mode = ICE_TRAY_MODE_DOWN;
        gu8_ice_tray_down_step = 0;
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_up_ice_tray(void)
{
    if( gu8_ice_tray_mode != ICE_TRAY_MODE_UP )
    {
        gu8_ice_tray_mode = ICE_TRAY_MODE_UP;
        gu8_ice_tray_up_step = 0;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void run_stop_ice_tray(void)
{
    gu8_ice_tray_mode = ICE_TRAY_MODE_NONE;
    gu8_ice_tray_up_step = 0;
    gu8_ice_tray_down_step = 0;
    gu16_ice_tray_moving_pulse = 0;
    gu16_ice_tray_target = 0;
    gu16_ice_tray_current = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


