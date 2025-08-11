/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "Comp_Control.h"

void output_comp_control(void);
void comp_stable_check(void);
U8 cold_init_operation( U8 mu8_disable );
void comp_off(void);
void comp_on(void);
void bldc_comp_off(void);
void bldc_comp_on(void);
void set_comp_rps( U8 mu8_target );
void check_comp_off_time(void);
U8 get_cold_mode_comp_rps(void);

void UART2_Receive_Interrupt(U8 mu8RxData);
void UART2_Error_Interrupt(void);




TYPE_WORD          U16CompOnW;
#define            u16CompOn                               U16CompOnW.word
#define            u8CompOn_L                              U16CompOnW.byte[0]
#define            u8CompOn_H                              U16CompOnW.byte[1]
#define            Bit0_Cold_Mode_On_State                 U16CompOnW.Bit.b0
#define            Bit1_Ice_Make_On_State                  U16CompOnW.Bit.b1
#define            Bit2_Ice_Init_On_State                  U16CompOnW.Bit.b2
#define            Bit3_Ice_Tray_Melt_On_State             U16CompOnW.Bit.b3
#define            Bit4_test_State                         U16CompOnW.Bit.b4




TYPE_WORD          U16CompOffW;
#define            u16CompOff                              U16CompOffW.word
#define            u8CompOff_L                             U16CompOffW.byte[0]
#define            u8CompOff_H                             U16CompOffW.byte[1]
#define            Bit0_Restart_5min_Delay_State           U16CompOffW.Bit.b0
#define            Bit1_Max_90min_CutOff_State             U16CompOffW.Bit.b1
#define            Bit2_Safty_Routine_State                U16CompOffW.Bit.b2
#define            Bit3_Ice_Making_Err_State               U16CompOffW.Bit.b3
#define            Bit4_Self_Test_COMP_Off_State           U16CompOffW.Bit.b4




bit F_Comp_Output;
U16 gu16_Comp_fisrt_turn_on_timer;
U32 gu32_Comp_max_turn_on_timer;

U16 gu16_mid_temp_90s_keep_timer;

U16 gu16_air_temp_delay_sec_timer;
U16 gu16_air_temp_delay_min_timer;
U16 gu16_air_comp_restart_time;


U16 gu16_hot_water_comp_delay_tiemr;
bit F_Comp_On_Off_Decision;
U8 gu8_Comp_Stable_Time;
U8 gu8_Comp_Stable_State;

U8  gu8AirTempLevel;
U16 gu16CompOffDelay;

bit F_Cold_Operation_Init;
U8 gu8_cold_init_step;

U8 gu8_cold_setting_level;
U8 gu8_cold_setting_level_old;


U8 gu8_bldc_off_step;
U16 gu16_bldc_off_timer;
U8 gu8_bldc_on_step;
U16 gu16_bldc_on_timer;

U16 gu16_comp_on_timer;
U16 gu16_comp_off_timer;
bit bit_start_preheat;

U16 gu16ColdDelayTimer = 0;         // �ð� ���� ���� �ð� Timer
U16 gu16CoolerActTime = 0;          // �ð� ���� �ð� Ÿ�̸�
U16 gu16CoolUnderTempDelay = 0;     // 5.5�� ���� ���޽� 5�а� �� �ð� �����ϵ��� �ϴ� Delay Timer

bit F_UART2Ok;                      // UART��� OK Flag
bit F_UART2CommunicationErrorDetect;  // UART��� �̻� ��Ŷ ���� Flag
bit F_UART2CommunicationError;
U8 gu8UART2CommunicationErrorCounter = 0;
U16 gu16UART2CommunicationNoiseTimer = 0;   // UART��� ������ ���� Ÿ�̸�
U8 gu8BLDCCommunicationErrorNum = 0;        // BLDC Comp�� ��� ���� �߻� ī����
U8 gu8BLDCErrorCounter = 0;         // BLDC Comp�� Error Code ���� ī����(���� ���� ���� Counter)
U8 gu8BLDCErrorClearCounter = 0;    // BLDC Comp�� Error Code �̼��� ī����(���� ���� ���� Counter)
U8 gu8BLDCErrorNum = 0;             // BLDC Comp�� Error �߻� ī����
const U8 gu8BLDC_FrequencyData[36] = {BLDC_40Hz, BLDC_41Hz, BLDC_42Hz, BLDC_43Hz, BLDC_44Hz, BLDC_45Hz,
                                      BLDC_46Hz, BLDC_47Hz, BLDC_48Hz, BLDC_49Hz, BLDC_50Hz,
                                      BLDC_51Hz, BLDC_52Hz, BLDC_53Hz, BLDC_54Hz, BLDC_55Hz,
                                      BLDC_56Hz, BLDC_57Hz, BLDC_58Hz, BLDC_59Hz, BLDC_60Hz,
                                      BLDC_61Hz, BLDC_62Hz, BLDC_63Hz, BLDC_64Hz, BLDC_65Hz,
                                      BLDC_66Hz, BLDC_67Hz, BLDC_68Hz, BLDC_69Hz, BLDC_70Hz,
                                      BLDC_71Hz, BLDC_72Hz, BLDC_73Hz, BLDC_74Hz, BLDC_75Hz};

U8 gu8BLDC_ErrorCode = 0;
U8 gu8BLDC_TargetHz = 0;
U8 gu8BLDC_FeedbackHz = 0;
U8 gu8BLDCRxDataBuffer[3] = {0, 0, 0};
U8 gu8UART2_RXD_Sequence = 0;
U8 gu8RXD2_CheckTimer = 0;
U8 gu8BLDC_TXDPeroid = 0;
U8 gu8ColdPumpControlVolt = 0;
U16 gu16ColdPumpControlTimer = 0;     // �ð� ��ȯ ���� ���� Ÿ�̸�
U16 gu16ColdEffluentEndPumpActTimer = 0;  // �ü� ���� �� ���� ���� Ÿ�̸�

bit F_UART2ErrorInterrupt;
bit F_CompActStart;               // �ð� ���� ���� Flag
bit F_BLDCCompError;                  // BLDC Comp ���� ����

bit bit_comp_comm_temp_error;
U8 gu8_comp_1s_timer;
U8 gu8_cold_init_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_comp_control(void)
{
/***********************************************************************************************************/
/***********************************************************************************************************/
    /* ON */
    if(Bit0_Cold_Make_Go == SET)
    {
        Bit0_Cold_Mode_On_State = cold_init_operation( Bit0_Restart_5min_Delay_State );
    }
    else
    {
        Bit0_Cold_Mode_On_State = CLEAR;
        gu8_cold_init_step = 0;
        gu8_cold_init_timer = 0;
    }

    #if 0
    if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
    {
        if( gu16IceMakeTime > 0 )
        {
            Bit1_Ice_Make_On_State = Bit1_Ice_Make_Go;
        }
        else
        {
            Bit1_Ice_Make_On_State = CLEAR;
        }
    }
    else
    {
        Bit1_Ice_Make_On_State = CLEAR;
    }
    #endif

    if( Bit1_Ice_Make_Go == SET )
    {
        /*..hui [23-7-21���� 2:13:29] ������ ���� �� ���� ���� ���������� ä�� �� ����..*/
        /*..hui [23-7-21���� 2:13:49] ���� ������ COMP ���� ����ϵ���..*/
        if( gu8IceStep == STATE_0_STANDBY )
        {
        	/*
            if( F_WaterInit != SET )
            {
                Bit1_Ice_Make_On_State = CLEAR;
            }
            else{}
			*/
        }
        else{}

        if( gu8IceStep == STATE_7_PREHEAT_OPERATION )
        {
            Bit1_Ice_Make_On_State = SET;
        }
        else{}

        if( gu8IceStep >= STATE_31_MAIN_ICE_MAKING && gu8IceStep <= STATE_51_FINISH_ICE_MAKE )
        {
            Bit1_Ice_Make_On_State = SET;
        }
        else{}
    }
    else
    {
        Bit1_Ice_Make_On_State = CLEAR;
    }


    /*..hui [23-4-13���� 11:08:46] ��������, �ְ�������..*/
    if( gu8InitStep >= 5 && gu8InitStep <= 7 )
    {
        Bit2_Ice_Init_On_State = F_IceInit;

        #if 0
        if( gu16IceMakeTime > 0 )
        {
            Bit2_Ice_Init_On_State = F_IceInit;
        }
        else
        {
            Bit2_Ice_Init_On_State = CLEAR;
        }
        #endif
    }
    else
    {
        Bit2_Ice_Init_On_State = CLEAR;
    }


    #if 0
    /*..hui [23-9-4���� 2:51:07] Ʈ���� �������� ��õ��� �غ��۾� �ְ��� �����Ҷ� ����..*/
    if( F_Safety_Routine == SET && F_Ice_Tray_Down_Move_Reset == SET )
    {
        if( gu8_over_ice_melt_proc == 5 )
        {
            Bit3_Ice_Tray_Melt_On_State = SET;
        }
        else
        {
            Bit3_Ice_Tray_Melt_On_State = CLEAR;
        }
    }
    else
    {
        Bit3_Ice_Tray_Melt_On_State = CLEAR;
    }
    #endif

    /*..hui [23-9-22���� 9:44:29] �غ� ���� �� �ְ��� ���� ����..*/
    Bit3_Ice_Tray_Melt_On_State = CLEAR;

/***********************************************************************************************************/
/***********************************************************************************************************/
    /* OFF */
    //===========================================================================//
    /*..hui [18-10-23���� 3:24:08] COMP 150�� ���� ������ ���� ����..*/
    if( F_Comp_Output == CLEAR )
    {
        gu32_Comp_max_turn_on_timer = 0;
        Bit1_Max_90min_CutOff_State = CLEAR;
    }
    else
    {
        gu32_Comp_max_turn_on_timer++;
        if( gu32_Comp_max_turn_on_timer >= COMP_MAX_TURN_ON_150MIN_TIME )
        {
            gu32_Comp_max_turn_on_timer = COMP_MAX_TURN_ON_150MIN_TIME;

            /*..hui [19-7-26���� 8:53:31] ����� ��ȣ�ð� �ʰ��� �������� �������� �������ϰ� COMP OFF..*/
            if( gu8IceStep == STATE_0_STANDBY )
            {
                Bit1_Max_90min_CutOff_State = SET;
            }
            else{}
        }
        else
        {
            Bit1_Max_90min_CutOff_State = CLEAR;
        }
    }

    //===========================================================================//
    /*..hui [18-10-23���� 3:28:54] ���� ���� �� ���� �� �����ð� 5�� ���Ŀ� �� �ð� ���� ������ �� �ð� ����..*/
    if(F_Comp_Output == SET)
    {
        gu16CompOffDelay = COMP_START_TIME;                       // ���� ��⵿��� 5��
        Bit0_Restart_5min_Delay_State = CLEAR;
    }
    else
    {
        if(gu16CompOffDelay > 0)
        {
            gu16CompOffDelay--;                                   // ���� 5�� ��⵿���
            Bit0_Restart_5min_Delay_State = SET;
        }
        else
        {
            Bit0_Restart_5min_Delay_State = CLEAR;
        }
    }


    //===========================================================================//
    /*..hui [19-12-18���� 7:26:16] �ð�/���� �� �� �����ϋ�..*/
    Bit3_Ice_Making_Err_State = (Bit2_Ice_Operation_Disable_State & Bit0_Cold_Operation_Disable_State);


    /*..hui [23-12-20���� 5:12:03] �������� �������϶�..*/
    Bit4_Self_Test_COMP_Off_State = bit_self_test_start;

    //===========================================================================//

/***********************************************************************************************************/
    if( u16CompOff > 0 )            /*off*/
    {
        comp_off();
        F_Comp_Output = CLEAR;
    }
    else
    {
        if( u16CompOn > 0 )          /*on*/
        {
            comp_on();
            F_Comp_Output = SET;
        }
        else                       /*off*/
        {
            comp_off();
            F_Comp_Output = CLEAR;
        }
    }

    /*if( F_Comp_Output == SET )*/
    if( pCOMP == SET )
    {
        Bldc_Comp_Communication();
    }
    else
    {
        clear_bldc_buffer();
    }

    comp_stable_check();
    check_comp_off_time();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_stable_check(void)
{
    /*if(F_Comp_Output == CLEAR)*/
    /*..hui [24-2-5���� 5:33:14] ���� ������� ����..*/
    if( pCOMP == CLEAR )
    {
        gu8_Comp_Stable_Time = 0;
        gu8_Comp_Stable_State = SET;
    }
    else
    {
        gu8_Comp_Stable_Time++;

        if(gu8_Comp_Stable_Time >= COMP_STABLE_TIME)
        {
            gu8_Comp_Stable_Time = COMP_STABLE_TIME;
            gu8_Comp_Stable_State = SET;
        }
        else
        {
            gu8_Comp_Stable_State = CLEAR;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �ð� �ʱ⵿��
***********************************************************************************************************************/
U8 cold_init_operation( U8 mu8_disable )
{
    U8 mu8_return = 0;
    U8 mu8_comp_rps = 0;

    if(mu8_disable == SET)
    {
        gu8_cold_init_step = 0;
        gu8_cold_init_timer = 0;
        return mu8_return;
    }
    else{}

    switch(gu8_cold_init_step)
    {
        case 0:

            gu8_cold_init_timer++;

            if( gu8_cold_init_timer >= 10 )
            {
                gu8_cold_init_timer = 0;
                gu8_cold_init_step++;
            }
            else{}

        break;

        case 1:

            GasSwitchCold();
            gu8_cold_init_step++;

        break;

        case 2:

            if(gu8_GasSwitch_Status == GAS_SWITCH_COLD)
            {
                gu8_cold_init_step++;
            }
            else{}

        break;

        case 3:

            mu8_comp_rps = get_cold_mode_comp_rps();
            set_comp_rps( mu8_comp_rps );

            mu8_return = SET;

        break;

        default:

            gu8_cold_init_step = 0;

        break;
    }

    #if 0
    /*..hui [19-7-26���� 4:47:09] ���� �������̶�� �������� ��� �ü������� �̵�..*/
    if(F_Comp_Output == SET)
    {
        mu8_return = SET;
    }
    else{}
    #endif

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_off(void)
{
    /*if( F_Comp_Output == SET )*/
    if( pCOMP == SET )
    {
        bldc_comp_off();
    }
    else
    {
        pCOMP = CLEAR;
        //////F_Comp_Output = CLEAR;

        gu8_bldc_on_step = 0;
        gu16_bldc_on_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void comp_on(void)
{
    /*if( F_Comp_Output == CLEAR )*/
    if( pCOMP == CLEAR )
    {
        bldc_comp_on();
    }
    else
    {
        pCOMP = SET;
        /////F_Comp_Output = SET;

        gu8_bldc_off_step = 0;
        gu16_bldc_off_timer = 0;
    }
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void bldc_comp_off(void)
{
    gu8_bldc_target_hz = BLDC_COMP_OFF_0_HZ;

    switch( gu8_bldc_off_step )
    {
        case 0:

            if( gu8_bldc_opration_hz == BLDC_COMP_OFF_0_HZ )
            {
                gu8_bldc_off_step++;
                gu16_bldc_off_timer = 0;
            }
            else if( bit_temporary_comm_error == SET )
            {
                /*..hui [23-7-4���� 10:57:55] ��ſ����϶�.. ����� �ȵǹǷ� �ٷ� OFF..*/
                /*..hui [23-7-4���� 11:13:31] �����ڵ�� OFF�ɶ��� ����.. ����� �ǹǷ� ��ٸ���..*/
                gu8_bldc_off_step++;
                gu16_bldc_off_timer = 0;
            }
            else
            {
                gu16_bldc_off_timer++;

                if( gu16_bldc_off_timer >= 300 )
                {
                    /*gu16_bldc_off_timer = 300;*/
                    /*..hui [23-5-8���� 2:24:33] ���� �߰� ..*/
                    gu8_bldc_off_step++;
                    gu16_bldc_off_timer = 0;
                }
                else{}
            }

        break;

        case 1:

            gu16_bldc_off_timer++;

            if( gu16_bldc_off_timer >= 30 )
            {
                gu16_bldc_off_timer = 0;
                gu8_bldc_off_step++;
            }
            else{}

        break;

        case 2:

            pCOMP = CLEAR;
            F_Comp_Output = CLEAR;

        break;

        default:
            gu16_bldc_off_timer = 0;
            gu8_bldc_off_step = 0;
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void bldc_comp_on(void)
{
    /*gu8_bldc_target_hz = BLDC_COMP_40Hz;*/

    switch( gu8_bldc_on_step )
    {
        case 0:

            gu16_bldc_on_timer++;

            if( gu16_bldc_on_timer >= 10 )
            {
                gu16_bldc_on_timer = 0;
                gu8_bldc_on_step++;
            }
            else{}

        break;

        case 1:

            pCOMP = SET;

        break;

        default:
            gu16_bldc_on_timer = 0;
            gu8_bldc_on_step = 0;
        break;
    }


    #if 0
    switch( gu8_bldc_on_step )
    {
        case 0:

            gu16_bldc_on_timer++;

            if( gu16_bldc_on_timer >= 10 )
            {
                gu16_bldc_on_timer = 0;
                gu8_bldc_on_step++;
            }
            else{}

        break;

        case 1:

            pCOMP = SET;
            /*F_Comp_Output = SET;*/
            gu16_bldc_on_timer = 0;
            gu8_bldc_on_step++;

        break;

        case 2:

            gu16_bldc_on_timer++;

            if( gu16_bldc_on_timer >= 30 )
            {
                gu16_bldc_on_timer = 0;
                gu8_bldc_on_step++;
            }
            else{}

        break;

        case 3:

            pCOMP = SET;
            F_Comp_Output = SET;

        break;

        default:
            gu16_bldc_on_timer = 0;
            gu8_bldc_on_step = 0;
        break;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void set_comp_rps( U8 mu8_target )
{
    gu8_bldc_target_hz = mu8_target;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_comp_off_time(void)
{
    if( F_Comp_Output == SET )
    {
        gu16_comp_off_timer = 0;
        gu16_comp_on_timer++;

        /*..hui [23-4-12���� 2:21:16] 3�� �̻� �������� ��쿡�� Ŭ����..*/
        if( gu16_comp_on_timer >= PREHEAT_CLEAR_COMP_ON_TIME )
        {
            gu16_comp_on_timer = PREHEAT_CLEAR_COMP_ON_TIME;
            bit_start_preheat = CLEAR;
        }
        else{}
    }
    else
    {
        /*..hui [23-4-7���� 4:48:23] �ܱ� �µ� 25�� �̸��� ���¿��� ����� ���� �ð��� 30�� �ʰ��� ���..*/
        /*..hui [23-4-7���� 4:48:30] ���� ���� ���� ���� ���� ����..*/
        gu16_comp_on_timer = 0;
        gu16_comp_off_timer++;

        if( gu16_comp_off_timer >= PREHEAT_SET_COMP_OFF_TIME )
        {
            gu16_comp_off_timer = PREHEAT_SET_COMP_OFF_TIME;
            bit_start_preheat = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �ð� �ʱ�⵿ (250429) (�ð����̺�)
***********************************************************************************************************************/
U8 get_cold_mode_comp_rps(void)
{
    U8 mu8_return = 0;

    if( gu8_Amb_Temperature_One_Degree <= 10 )
    {
        /*..hui [23-4-7���� 11:15:58] 10�� ����..*/
        if( bit_cold_first_op == SET )                  /* �ʱ� */
        {
            mu8_return = BLDC_COMP_50Hz;                /* V18 �ð����̺� */
        }
        else
        {
            mu8_return = BLDC_COMP_40Hz;                /* V18 �ð����̺� */
        }
    }
    else if( gu8_Amb_Temperature_One_Degree <= 20 )
    {
        /*..hui [23-4-7���� 11:16:02] 20�� ����..*/
        if( bit_cold_first_op == SET )
        {
            mu8_return = BLDC_COMP_50Hz;                /* V18 �ð����̺� */
        }
        else
        {
            /* V11 �ð����̺� */
            if( gu16_Cold_Temperature >= 65 )
            {
                mu8_return = BLDC_COMP_40Hz;
            }
            else
            {
                mu8_return = BLDC_COMP_45Hz;
            }
        }
    }
    else if( gu8_Amb_Temperature_One_Degree <= 30 )
    {
        /*..hui [23-4-7���� 11:16:10] 30�� ����..*/
        mu8_return = BLDC_COMP_45Hz;                    /* V18 �ð����̺� */
    }
    else
    {
        /*..hui [23-4-7���� 11:16:14] 30�� �ʰ�..*/
        mu8_return = BLDC_COMP_45Hz;                    /* V18 �ð����̺� */
    }

    return mu8_return;
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


