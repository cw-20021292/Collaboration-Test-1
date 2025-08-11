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
#include    "motor_ice_select.h"

void motor_ice_select_output(void);

bit F_SelectCW;                    // 살균 후 ICE Door Reset
U16 gu16_IceSelect_StepMotor;

// U16 gu16IceSelectDoorCloseTimer_Min = 0; /* 60s x 60min x 24h = 86400 24Hour */
// U16 gu16IceSelectDoorCloseTimer_Hour = 0; /* 60s x 60min x 24h = 86400 24Hour */
// U16 gu16IceDoorCloseResetTimer = 0;

U16 gu16IceSelectDoorCloseTimer_Min = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceSelectDoorCloseTimer_Hour = 0; /* 60s x 60min x 24h = 86400 24Hour */
U16 gu16IceSelectDoorCloseResetTimer = 0;
bit F_IceSelectDoorClose;        /* 아이스 도어 닫힘 */

bit F_IceSelect;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : StepMotor
// 개요       : 스텝모터 구동 Door 3msec cycle
//----------------------------------------------------------------------------
// 기능       :
//              ICE Door 열림 닫힘
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void motor_ice_select_output(void)
{
    if(F_IceSelect == SET)                                       // 열림
    {
        if(F_SelectCW != SET)
        {
            F_SelectCW = SET;
        }
        else{}

        if(gu16_IceSelect_StepMotor < STEP_ANGLE_SELECT)
        {
            gu16_IceSelect_StepMotor++;
            //gu8ErrDoor = 30;
        }
        else
        {
            gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
            
            pSTEP_MOTOR_ICE_SELECT_1 = 0;
            pSTEP_MOTOR_ICE_SELECT_2 = 0;
            pSTEP_MOTOR_ICE_SELECT_3 = 0;
            pSTEP_MOTOR_ICE_SELECT_4 = 0;
            if(F_IceOut != SET)
            {
                F_IceSelect = CLEAR;              // Door 열림 완료 후 Off
            }
            else{}
        }
    }
    else                                                  // 닫힘
    {
        if(F_SelectCW == SET)
        {
            gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
            F_SelectCW = 0;
        }
        else{}

        if(gu16_IceSelect_StepMotor > 0)
        {
            // 셀렉트 도어는 즉시 닫기
            gu16_IceSelect_StepMotor--;

        }
        else
        {
            gu16_IceSelect_StepMotor=0;
            pSTEP_MOTOR_ICE_SELECT_1 = 0;
            pSTEP_MOTOR_ICE_SELECT_2 = 0;
            pSTEP_MOTOR_ICE_SELECT_3 = 0;
            pSTEP_MOTOR_ICE_SELECT_4 = 0;
        }
    }

    if(gu16_IceSelect_StepMotor == 0 || gu16_IceSelect_StepMotor == STEP_ANGLE_SELECT)
    {
        pSTEP_MOTOR_ICE_SELECT_1 = 0;
        pSTEP_MOTOR_ICE_SELECT_2 = 0;
        pSTEP_MOTOR_ICE_SELECT_3 = 0;
        pSTEP_MOTOR_ICE_SELECT_4 = 0;
    }
    else
    {
        switch(gu16_IceSelect_StepMotor % 8)
        {
            case 0 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 1 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 2 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 3 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 1;

                    break;

            case 4 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 0;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 5 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 1;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 6 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 0;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            case 7 :

                    pSTEP_MOTOR_ICE_SELECT_1 = 1;
                    pSTEP_MOTOR_ICE_SELECT_2 = 1;
                    pSTEP_MOTOR_ICE_SELECT_3 = 0;
                    pSTEP_MOTOR_ICE_SELECT_4 = 0;

                    break;

            default:

                break;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ice_select_door_close_24_hour(void)
{
    U16 mu16_forced_close_time_min = 0;
    U16 mu16_forced_close_time_hour = 0;
    U8 mu8_return = 0;

    //====================================================
    /* 아이스 도어 주기적으로 닫는 로직( 24시간 기준으로 반복 )
     * 아이스 도어가 강제로 열린 경우를 가정해서 24시간 기준으로 닫아 준다.*/

    if( F_LineTest == SET )
    {
        /*..hui [18-1-23오후 2:29:46] 테스트 모드시 60초..*/
        mu16_forced_close_time_min = 600;
        /*..hui [18-1-23오후 2:29:52] 테스트 모드시 1분..*/
        mu16_forced_close_time_hour = 5;
    }
    else
    {
        /*..hui [18-1-23오후 2:29:03] 일반 모드시 60분..*/
        mu16_forced_close_time_min = 36000;
        /*..hui [18-1-23오후 2:29:09] 일반 모드시 24시간..*/
        mu16_forced_close_time_hour = 24;
    }

    mu8_return = finish_ice_setting();

    if( mu8_return == SET )
    {
        F_IceSelectDoorClose = SET;
    }
    else{}

    if( F_IceOut == SET )
    {
        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour = 0;
    }
    else{}

    /*..hui [18-1-23오후 2:12:10] 60분 타이머..*/
    gu16IceSelectDoorCloseTimer_Min++;

    if(gu16IceSelectDoorCloseTimer_Min >= mu16_forced_close_time_min)
    {
        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour++;
    }
    else{}

    /*..hui [18-1-23오후 2:12:15] 24시간 타이머..*/
    if(gu16IceSelectDoorCloseTimer_Hour >= mu16_forced_close_time_hour)
    {
        F_IceSelectDoorClose = SET;
        gu16IceSelectDoorCloseTimer_Hour = 0;
    }
    else{}

    if( F_IceSelectDoorClose == SET )
    {
        F_IceSelectDoorClose = CLEAR;

        gu16IceSelectDoorCloseTimer_Min = 0;
        gu16IceSelectDoorCloseTimer_Hour = 0;

        gu16IceSelectDoorCloseResetTimer = 70;
        gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
    }
    else{}

    /*..hui [18-1-23오후 2:44:04] 아이스도어 강제 CLOSE중에 얼음 추출할경우 FULL OPEN..*/
    if(gu16IceSelectDoorCloseResetTimer > 0)
    {
        gu16IceSelectDoorCloseResetTimer--;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




/***********************************************************************************************************************/

/***********************************************************************************************************************/

/***********************************************************************************************************************/

/***********************************************************************************************************************/