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
#include    "motor_gas_switch.h"


void ControlGasSwitch(void);
static U8 InitSwitch(void);
static U8 ColdSwitch(void);
static U8 IceSwitch(void);
static U8 HotGasSwitch(void);

void ProcessGasSwitch(void);
void StepMotorTimerInterrupt(void);
void HAL_ControlStepMotor( void );
void HAL_MoveStep( void );
static void HAL_ControlGasValveMotor( U8 mode );
void GasSwitchInit(void);
void GasSwitchCold(void);
void GasSwitchIce(void);
void GasSwitchHotGas(void);
void InitGasSwitch(void);



U8 gu8_GasSwitch_Status;
U8 gu8_GasSwitch_Mode;
U8 gu8_GasSwitch_InitStep;
U8 gu8_GasSwitch_ColdStep;
U8 gu8_GasSwitch_IceStep;
U8 gu8_GasSwitch_HotGasStep;


U8 gu8_GasSwitch_PowerOnTime;

S16 gs16_sm_info_target;
S16 gs16_sm_info_current;
S16 gs16_sm_info_move_step;
S16 gs16_sm_info_hold_start_step;
S16 gs16_sm_info_hold_stop_step;
I8 gi8_sm_info_current_mode;
I8 gi8_sm_info_prev_mode;

const U8 gu8PhaseTable[ PHASE_STEP_NUM ] =
{ 8, 7, 6, 5, 4, 3, 2, 1 };
/*{ 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };*/





bit F_Comp_Output_Old;
bit F_GasSwitch_Initial;





U8 gu8_qqqq;
U8 gu8_wwww;
U8 gu8_eeee;
U8 gu8_rrrr;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ControlGasSwitch(void)
{
    U8 mu8Ret = FALSE;

    if( gu8_qqqq ==1 )
    {
        gu8_qqqq = 0;
        GasSwitchInit();
    }
    else{}

    if( gu8_wwww ==1 )
    {
        gu8_wwww = 0;
        GasSwitchCold();
    }
    else{}

    if( gu8_eeee ==1 )
    {
        gu8_eeee = 0;
        GasSwitchIce();
    }
    else{}

    if( gu8_rrrr ==1 )
    {
        gu8_rrrr = 0;
        GasSwitchHotGas();
    }
    else{}

    if(u8FactoryTestMode == NONE_TEST_MODE)
    {
        ProcessGasSwitch();
    }
    else{}

    /* CONTROL SMPS 12V */
    if( gu8_GasSwitch_Mode != GAS_SWITCH_MODE_NONE )
    {
        /*..hui [20-1-14���� 8:13:59] UV������ 12V ����ϹǷ�..*/
        /*p12V_POWER = CLEAR;*/
        Bit0_Gas_Switch_12V_Out_State = SET;
    }
    else
    {
        /*p12V_POWER = SET;*/
        Bit0_Gas_Switch_12V_Out_State = CLEAR;
    }

    #if 0
    /* Power Init */
    // ������ ��� ���� �ʱ�ȭ �� ��, �ʱ� ��ġ ������ �ü������� �����Ѵ�.
    if( (gu8_GasSwitch_Mode & GAS_SWITCH_MODE_POWER_INIT ) == GAS_SWITCH_MODE_POWER_INIT )
    {
        mu8Ret = InitSwitch();

        if( mu8Ret == TRUE )
        {
            gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_POWER_INIT;
            gu8_GasSwitch_InitStep = 0;
            gu8_GasSwitch_Status = GAS_SWITCH_COLD;
        }
        else{}

        return ;
    }
    else{}
    #endif


    /* Init */
    // �ʱ�ȭ�� �ϰ� ���� ���� ��ġ�� �ü���������,
    // ��ġ ������ ���� �ʴ´�.
    if( (gu8_GasSwitch_Mode & GAS_SWITCH_MODE_INIT ) == GAS_SWITCH_MODE_INIT )
    {
        mu8Ret = InitSwitch();

        if( mu8Ret == TRUE )
        {
            gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_INIT;
            gu8_GasSwitch_InitStep = 0;
            gu8_GasSwitch_Status = GAS_SWITCH_COLD;
        }
        else{}

        return;
    }
    else{}


    /* Cold */
    if( (gu8_GasSwitch_Mode & GAS_SWITCH_MODE_COLD ) == GAS_SWITCH_MODE_COLD )
    {
        mu8Ret = ColdSwitch();

        if( mu8Ret == TRUE )
        {
            gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_COLD;
            gu8_GasSwitch_ColdStep = 0;
            gu8_GasSwitch_Status = GAS_SWITCH_COLD;
        }
        else{}

        return;
    }
    else{}

    /* Ice */
    if( (gu8_GasSwitch_Mode & GAS_SWITCH_MODE_ICE ) == GAS_SWITCH_MODE_ICE )
    {
        mu8Ret = IceSwitch();

        if( mu8Ret == TRUE )
        {
            gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_ICE;
            gu8_GasSwitch_IceStep = 0;
            gu8_GasSwitch_Status = GAS_SWITCH_ICE;
        }
        else{}

        return;
    }
    else{}

    /* HOT-GAS */
    if( (gu8_GasSwitch_Mode & GAS_SWITCH_MODE_HOTGAS ) == GAS_SWITCH_MODE_HOTGAS )
    {
        mu8Ret = HotGasSwitch();

        if( mu8Ret == TRUE )
        {
            gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_HOTGAS;
            gu8_GasSwitch_HotGasStep = 0;
            gu8_GasSwitch_Status = GAS_SWITCH_HOTGAS;
        }
        return;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static U8 InitSwitch(void)
{
    switch( gu8_GasSwitch_InitStep )
    {
        case INIT_POWER_ON:
            gu8_GasSwitch_PowerOnTime = POWER_ON_TIME;
            gu8_GasSwitch_InitStep++;
            break;

        case INIT_WAIT_POWER_ON:
            if( gu8_GasSwitch_PowerOnTime != 0 )
            {
                gu8_GasSwitch_PowerOnTime--;
            }
            else
            {
                gu8_GasSwitch_InitStep++;
            }
            break;

        case INIT_MOVE_ZERO:

            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
            gs16_sm_info_target = GAS_SWITCH_INIT_STEP_VAL;

            gu8_GasSwitch_InitStep++;
            break;

        case INIT_WAIT_ZERO:
            //if( HAL_IsDoneMoveStep( GAS_SWITCH_ID ) == TRUE )
            if( gs16_sm_info_target == gs16_sm_info_current )
            {
                gu8_GasSwitch_InitStep++;

                gs16_sm_info_target = 0;
                gs16_sm_info_current = 0;
            }
            break;

        case INIT_MOVE_COLD:
            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
            gs16_sm_info_target = GAS_SWITCH_COLD_STEP_VAL;

            gu8_GasSwitch_InitStep++;
            break;

        case INIT_WAIT_COLD:
            //if( HAL_IsDoneMoveStep( GAS_SWITCH_ID ) == TRUE )
            if( gs16_sm_info_target == gs16_sm_info_current )
            {
                gu8_GasSwitch_InitStep++;
            }
            else{}
            break;

        case INIT_DONE :
            return TRUE;
            break;

        default :
            gu8_GasSwitch_InitStep = INIT_POWER_ON;
            break;
    }

    return FALSE;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static U8 ColdSwitch(void)
{
    switch( gu8_GasSwitch_ColdStep )
    {
        // POWER ON
        case COLD_POWER_ON:
            gu8_GasSwitch_PowerOnTime = POWER_ON_TIME;
            gu8_GasSwitch_ColdStep++;
            break;

        case COLD_WAIT_POWER_ON:
            if( gu8_GasSwitch_PowerOnTime != 0 )
            {
                gu8_GasSwitch_PowerOnTime--;
            }
            else
            {
                gu8_GasSwitch_ColdStep++;
            }
            break;


            // MOVE
        case COLD_CHECK_POSITION:
            if( gs16_sm_info_target == GAS_SWITCH_COLD_STEP_VAL )
            {
                gu8_GasSwitch_ColdStep = COLD_WAIT;
            }
            else
            {
                gu8_GasSwitch_ColdStep++;
            }
            break;

        case COLD_MOVE:

            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
            gs16_sm_info_target = GAS_SWITCH_COLD_STEP_VAL;

            gu8_GasSwitch_ColdStep++;
            break;

        case COLD_WAIT:
            //if( HAL_IsDoneMoveStep( GAS_SWITCH_ID ) == TRUE )
            if( gs16_sm_info_target == gs16_sm_info_current )
            {
                gu8_GasSwitch_ColdStep++;
            }
            else{}
            break;

        case COLD_DONE:

            return TRUE;
            break;

        default :
            gu8_GasSwitch_ColdStep = COLD_POWER_ON;
            break;
    }
    return FALSE;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static U8 IceSwitch(void)
{
    switch( gu8_GasSwitch_IceStep )
    {
        case ICE_POWER_ON:
            gu8_GasSwitch_PowerOnTime = POWER_ON_TIME;
            gu8_GasSwitch_IceStep++;
            break;

        case ICE_WAIT_POWER_ON:
            if( gu8_GasSwitch_PowerOnTime != 0 )
            {
                gu8_GasSwitch_PowerOnTime--;
            }
            else
            {
                gu8_GasSwitch_IceStep++;
            }
            break;

        // ���� ��ġ�̸� �̵� ���� ���� ����
        case ICE_CHECK_POSITION:
            if( gs16_sm_info_target == GAS_SWITCH_ICE_STEP_VAL )
            {
                gu8_GasSwitch_IceStep = ICE_WAIT;
            }
            else
            {
                gu8_GasSwitch_IceStep++;
            }
            break;

        case ICE_MOVE:
            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
            gs16_sm_info_target = GAS_SWITCH_ICE_STEP_VAL;

            gu8_GasSwitch_IceStep++;
            break;

        case ICE_WAIT:
            //if( HAL_IsDoneMoveStep( GAS_SWITCH_ID ) == TRUE )
            if( gs16_sm_info_target == gs16_sm_info_current )
            {
                gu8_GasSwitch_IceStep++;
            }
            else{}
            break;

        case ICE_DONE:
            return TRUE;
            break;

        default :
            gu8_GasSwitch_IceStep = ICE_POWER_ON;
            break;

    }

    return FALSE;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static U8 HotGasSwitch(void)
{
    switch( gu8_GasSwitch_HotGasStep )
    {
        case HOTGAS_POWER_ON:
            gu8_GasSwitch_PowerOnTime = POWER_ON_TIME;
            gu8_GasSwitch_HotGasStep++;
            break;

        case HOTGAS_WAIT_POWER_ON:
            if( gu8_GasSwitch_PowerOnTime != 0 )
            {
                gu8_GasSwitch_PowerOnTime--;
            }
            else
            {
                gu8_GasSwitch_HotGasStep++;
            }
            break;

        // ?�재 ?�치?�면 ?�동 ?�이 ?�상 종료
        case HOTGAS_CHECK_POSITION:
            /*if( HAL_GetTargetStep( GAS_SWITCH_ID ) == GAS_SWITCH_HOTGAS_STEP_VAL )*/
            if( gs16_sm_info_target == GAS_SWITCH_HOTGAS_STEP_VAL )
            {
                gu8_GasSwitch_HotGasStep = ICE_WAIT;
            }
            else
            {
                gu8_GasSwitch_HotGasStep++;
            }
            break;

        case HOTGAS_MOVE:
            /*HAL_SetHoldStep( GAS_SWITCH_ID, 0 );*/
            /*HAL_SetTargetStep( GAS_SWITCH_ID, GAS_SWITCH_HOTGAS_STEP_VAL );*/
            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
            gs16_sm_info_target = GAS_SWITCH_HOTGAS_STEP_VAL;

            gu8_GasSwitch_HotGasStep++;
            break;

        case HOTGAS_WAIT:
            /*if( HAL_IsDoneMoveStep( GAS_SWITCH_ID ) == TRUE )*/
            if( gs16_sm_info_target == gs16_sm_info_current )
            {
                gu8_GasSwitch_HotGasStep++;
            }
            break;

        case HOTGAS_DONE:
            return TRUE;

        default :
            gu8_GasSwitch_HotGasStep = HOTGAS_POWER_ON;
            break;

    }

    return FALSE;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ProcessGasSwitch(void)
{
    if( F_Comp_Output_Old != F_Comp_Output )
    {
        F_Comp_Output_Old = F_Comp_Output;

        if( F_Comp_Output == OFF )
        {
            F_GasSwitch_Initial = SET;  // ���� �ʱ�ȭ ����
        }
        else{}
    }
    else{}


    // ����� OFF ��, 4�� �Ŀ� ���� �ʱ�ȭ ����
    if( F_GasSwitch_Initial == SET )
    {
        if(Bit0_Restart_5min_Delay_State == SET)
        {
            /*if(gu16CompOffDelay < 600)*/
            if(gu16CompOffDelay < 300)
            {
                F_GasSwitch_Initial = CLEAR;
                GasSwitchInit();
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
/* INTERRUPT SERVICE ROUTIN */
void StepMotorTimerInterrupt(void)
{
    HAL_ControlStepMotor();   // Gas Switch
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void HAL_ControlStepMotor( void )
{
    S16 val = 0;
    S16 target = 0;
    S16 current = 0;

    val = gs16_sm_info_move_step;
    target = gs16_sm_info_target;
    current = gs16_sm_info_current;

    /* CALC STEP, TARGET - CURRENT */
    if( val == 0 )
    {
        if( target != current )
        {
            val = target - current;

            gs16_sm_info_move_step = val;
            gs16_sm_info_hold_start_step = DEFAULT_HOLD_STEP;  /* about 0.5sec */
            gs16_sm_info_hold_stop_step = DEFAULT_HOLD_STEP;  /* aobut 0.5esc */
        }
        else{}
    }
    else{}


    HAL_MoveStep();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void HAL_MoveStep( void )
{
    U8 val = 0;

    /* START HOLD */
    if( gs16_sm_info_hold_start_step > 0 )
    {
        gs16_sm_info_hold_start_step--;
        val = gu8PhaseTable[ gi8_sm_info_prev_mode ];
    }
    else if( gs16_sm_info_move_step == 0 )
    {
        /* STOP HOLD */
        if( gs16_sm_info_hold_stop_step > 0 )
        {
            gs16_sm_info_hold_stop_step--;
            val = gu8PhaseTable[ gi8_sm_info_current_mode ];
        }
        else
        {
            /* STOP */
            val = 0x00;
        }
    }
    /* MOVE FORWARD */
    else if( gs16_sm_info_move_step > 0 )
    {
        /* OPEN */
        gs16_sm_info_move_step--;
        gs16_sm_info_current++;

        gi8_sm_info_prev_mode = gi8_sm_info_current_mode;
        gi8_sm_info_current_mode++;
        if( gi8_sm_info_current_mode >= PHASE_STEP_NUM )
        {
            gi8_sm_info_current_mode = 0;
        }
        else{}

        val = gu8PhaseTable[ gi8_sm_info_current_mode ];
    }
    /* MOVE BACKWARD */
    else if( gs16_sm_info_move_step < 0 )
    {
        /* CLOSE */
        gs16_sm_info_move_step++;
        gs16_sm_info_current--;

        gi8_sm_info_prev_mode = gi8_sm_info_current_mode;
        gi8_sm_info_current_mode--;
        if( gi8_sm_info_current_mode < 0 )
        {
            gi8_sm_info_current_mode = PHASE_STEP_NUM - 1;
        }
        else{}

        val = gu8PhaseTable[ gi8_sm_info_current_mode ];
    }
    else{}

    HAL_ControlGasValveMotor( val );
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/**
 * �ø� ���� ��ȯ ���ܸ���
 */
static void HAL_ControlGasValveMotor( U8 mode )
{
    switch( mode )
    {
        case 0:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;
        case 1:
            pSTEP_MOTOR_GAS_SW_1  = 1;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 1;
            break;
        case 2:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 1;
            break;
        case 3:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 1;
            pSTEP_MOTOR_GAS_SW_4  = 1;
            break;
        case 4:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 1;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;
        case 5:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 1;
            pSTEP_MOTOR_GAS_SW_3  = 1;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;
        case 6:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 1;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;
        case 7:
            pSTEP_MOTOR_GAS_SW_1  = 1;
            pSTEP_MOTOR_GAS_SW_2  = 1;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;
        case 8:
            pSTEP_MOTOR_GAS_SW_1  = 1;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 0;
            pSTEP_MOTOR_GAS_SW_4  = 0;
            break;

        default:
            pSTEP_MOTOR_GAS_SW_1  = 0;
            pSTEP_MOTOR_GAS_SW_2  = 0;
            pSTEP_MOTOR_GAS_SW_3  = 1;
            pSTEP_MOTOR_GAS_SW_4  = 1;
            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void GasSwitchInit(void)
{
    // Set Mode
    gu8_GasSwitch_Mode |= GAS_SWITCH_MODE_INIT;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void GasSwitchCold(void)
{
    // Set Mode
    gu8_GasSwitch_Mode |= GAS_SWITCH_MODE_COLD;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_ICE;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_HOTGAS;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void GasSwitchIce(void)
{
    // Set Mode
    gu8_GasSwitch_Mode |= GAS_SWITCH_MODE_ICE;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_COLD;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_HOTGAS;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void GasSwitchHotGas(void)
{
    // Set Mode
    gu8_GasSwitch_Mode |= GAS_SWITCH_MODE_HOTGAS;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_ICE;
    gu8_GasSwitch_Mode &= ~GAS_SWITCH_MODE_COLD;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void InitGasSwitch(void)
{
    gu8_GasSwitch_Status = GAS_SWITCH_ICE;

    gu8_GasSwitch_Mode = 0;
    gu8_GasSwitch_InitStep = 0;
    gu8_GasSwitch_ColdStep = 0;
    gu8_GasSwitch_IceStep = 0;
    gu8_GasSwitch_HotGasStep = 0;

    gu8_GasSwitch_PowerOnTime = POWER_ON_TIME; // @100ms, 1sec

    #if 0
    gs16_sm_info_current = GAS_SWITCH_ICE_STEP_VAL;
    gs16_sm_info_target = GAS_SWITCH_ICE_STEP_VAL;
    #endif

    gs16_sm_info_current = GAS_SWITCH_END_STEP_VAL;
    gs16_sm_info_target = GAS_SWITCH_END_STEP_VAL;

    F_GasSwitch_Initial = SET;
}


