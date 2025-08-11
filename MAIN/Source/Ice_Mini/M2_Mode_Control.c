/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Mode_Control.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M2_Mode_Control.h"

void Mode_Control(void);
void cold_temp_level_decision(void);
void hot_temp_level_decision(void);

void System(void);
void cody_test_mode(void);
void stop_ice_cody_mode(void);
void cold_level_setting_hi(void);
void get_final_small_amb_temp(void);
U8 get_final_large_amb_temp(void);


bit F_6HourNoUse;                 // 미사용 절전
//----------------------------------------------------// 냉수,온수
U8 gu8ColdTemp;
U8 gu8HotTemp;
//----------------------------------------------------// Heater
U8 gu8HotH2_On;
U8 gu8HotH3_On;
U8 gu8HotH2_Off;
U8 gu8HotH3_Off;





//----------------------------------------------------// Test
U8 gu8TestGo;
U8 gu8TestTemp;
U8 gu8VersionCount;
U8 gu8VersionTime;
//U16 gu16TestTime;

bit F_Reset;
U16 ucErrOvice_Valve;
U16 ucErrOVice_Heater;
U16 ucTime_10min_cycle;
U16 ucErrOvice_Time;
// 20130315 NFC TEST MODE에서 무부하 전류 5초 → 8초 변경




//U16 gu16MeltTime;

bit F_TrayCut;
bit F_NoSelectBar;
bit F_Melt;
bit F_Safety_Routine;
bit F_TrayStop;                       // 토출중 트레이이동 정지
bit F_Tray_up_moving_retry_state;
bit F_Trayretry1;
bit F_Trayretryfinal;



TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State              U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State              U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State               U8WaterOutStateB.Bit.b2

TYPE_BYTE          U8IceOutStateB;
#define            u8IceOutState                             U8IceOutStateB.byte
#define            Bit0_Ice_Only_Select_State                U8IceOutStateB.Bit.b0
#define            Bit1_Ice_Plus_Water_Select_State          U8IceOutStateB.Bit.b1


//----------------------------------------------------// Altitude
U8 gu8AltitudeTime;
U8 gu8AltitudeStep;



U16 gu16Water_Extract_Timer;


bit bit_child_lock_enable;

U8 gu8_cooling_display_mode;
U8 gu8_heating_display_mode;

U16 gu16_display_cold_on_temp;
U16 gu16_display_cold_off_temp;
bit bit_cooling_complete_5degree;

extern void hot_ster_control(void);
extern void time_setting();
extern void wifi_time_setting();
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Mode_Control(void)
{
    /*model_select();*/
    /*..sean [24-6-19] TDS 기능 재추가..*/
    /*..hui [24-11-13오후 2:34:15] TDS 다시 삭제..*/
    /*tds_control();*/

    uart_test_mode_decision();

    cold_temp_level_decision();
    //hot_temp_level_decision();

    System();

    continued_extract_control();

    water_extract_control();

    /*..hui [25-1-10오후 1:46:00] 얼음 정량 추출..*/
    ice_extract_control();

    my_cup_return_decision();

    // hot_ster_control();

    /*..hui [20-3-5오후 2:57:22] 온수 첫잔 드레인 자동으로 되도록 개선.........*/
    /////hot_water_filling_control();
    /////hot_water_extract_control();

    /*..hui [20-4-9오전 9:41:09] 온수 과열에러 발생시 히터 쿨링..*/
    //////hot_cooling_control();

    /*..hui [23-5-24오후 5:25:38] 온수 관련 제어..*/
    /////hot_control();

    logic_decision();

    /*..hui [19-11-1오후 7:31:38] 전기 사용량 계산 추가..*/
    /////calculate_electric_rate();

    /*..hui [18-1-14오후 5:50:58] 순환배수 기능 추가..*/
    auto_drain_control();


    /*..hui [23-8-14오후 2:07:11] 수동배수 기능 추가..*/
    manual_drain();

    /*..hui [17-12-29오후 1:22:03] 서버스 점검..*/
    //service_check();

    /*..hui [18-1-23오후 2:33:06] 24시간 마다 아이스도어 CLOSE..*/
    ice_door_close_24_hour();
    ice_select_door_close_24_hour();

    /*..hui [19-7-25오후 8:27:11] 절전진입시 만빙 후 6시간 제빙 정지..*/
    /*check_ice_stop();*/

    /*..hui [19-10-23오후 8:26:29] 서비스체크 추가..*/
    /*service_check();*/

    /*..hui [20-1-8오후 4:22:39] 코디 테스트 모드..*/
    cody_test_mode();

    /*..hui [23-2-28오후 7:36:37] 아이스탱크 온수 고온 살균 기능 추가..*/
    ice_tray_ster_control();

    calc_water_usage();

    /*..hui [23-6-12오후 4:39:12] 시간 설정..*/
    time_setting();

    /*..hui [21-7-27오후 12:43:14] WIFI 관련 제어..*/
    wifi_operation_control();
    wifi_smart_control();
    wifi_time_setting();

    save_mode();

    child_lock();

    /*..hui [23-9-7오후 1:52:27] 품질 에이징 테스트..*/
    water_durable_test();

	check_ice_system_ok();
    /*..hui [24-2-22오전 11:12:17] CT 모드..*/
    /////ct_mode();

    /*..hui [24-5-23오후 7:23:35] 구연산 세척..*/
    /////acid_control();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_temp_level_decision(void)
{
    /*..hui [19-12-18오후 10:50:28] 냉수센서 에러시 3단으로 고정..*/
    if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET )
    {
        /*gu8_cooling_display_mode = COOLING_DISPLAY_1_ON;*/
        gu8_cooling_display_mode = COOLING_DISPLAY_0_OFF;
        return;
    }
    else{}

    /*..hui [23-12-22오후 4:39:02] 냉수 만들지 않는 에러 조건 전부 포함.. 인식..*/
    if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET
        || Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit7_BLDC_Communication_Error__E27 == SET
        || bit_bldc_operation_error_total == SET )
    {
        gu8_cooling_display_mode = COOLING_DISPLAY_0_OFF;
        return;
    }
    else{}

    /*..hui [20-1-6오후 9:08:55] 냉수 설정 해제 시 1단..*/
    if( F_Cold_Enable == CLEAR )
    {
        /*gu8_cooling_display_mode = COOLING_DISPLAY_1_ON;*/
        gu8_cooling_display_mode = COOLING_DISPLAY_0_OFF;
        return;
    }
    else{}

    cold_level_setting_hi();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cold_level_setting_hi(void)
{
    switch( gu8_cooling_display_mode )
    {
        case COOLING_DISPLAY_0_OFF :
            bit_cooling_complete_5degree = CLEAR;

            /*if( gu8_Cold_Temperature_One_Degree <= 8 )*/
            if( gu16_Cold_Temperature <= gu16_display_cold_off_temp )
            {
                gu8_cooling_display_mode = COOLING_DISPLAY_2_COMPLETE;
            }
            /*else if( gu8_Cold_Temperature_One_Degree > 10 )*/
            else if( gu16_Cold_Temperature >= gu16_display_cold_on_temp )
            {
                gu8_cooling_display_mode = COOLING_DISPLAY_1_OPERATION;
            }
            else
            {
                if( Bit0_Cold_Mode_On_State == SET )
                {
                    gu8_cooling_display_mode = COOLING_DISPLAY_1_OPERATION;
                }
                else
                {
                    gu8_cooling_display_mode = COOLING_DISPLAY_2_COMPLETE;
                }
            }

            break;

        case COOLING_DISPLAY_1_OPERATION :

            /*..hui [23-11-21오전 10:14:17] 냉수온도 8도 이하..*/
            /*if( gu8_Cold_Temperature_One_Degree <= 8 )*/
            if( gu16_Cold_Temperature <= gu16_display_cold_off_temp )
            {
                gu8_cooling_display_mode = COOLING_DISPLAY_2_COMPLETE;
				bit_cooling_complete_5degree = SET;
            }
            else{}

            break;

        case COOLING_DISPLAY_2_COMPLETE :

            /*if( gu8_Cold_Temperature_One_Degree > 10 )*/
            if( gu16_Cold_Temperature >= gu16_display_cold_on_temp )
            {
                gu8_cooling_display_mode = COOLING_DISPLAY_1_OPERATION;
				bit_cooling_complete_5degree = CLEAR; 
            }
            else{}

            break;

        default :

            gu8_cooling_display_mode = COOLING_DISPLAY_0_OFF;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_temp_level_decision(void)
{
#if 0
    /*..hui [19-12-18오후 10:50:28] 냉수센서 에러시 1단으로 고정..*/
    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET )
    {
        gu8_heating_display_mode = HEATING_DISPLAY_0_INIT;
        return;
    }
    else{}

    /*..hui [23-12-22오후 4:39:53] 온수 만들지않는 조건 전부 포함..*/
    if( Bit0_Hot_Tank_Temp_Open_Short_Error__E45 == SET
        || Bit3_Leakage_Sensor_Error__E01 == SET
        || Bit4_Room_Low_Water_Level_Error__E21 == SET
        || Bit1_Room_OverHeat_Error__E49 == SET )
    {
        gu8_heating_display_mode = HEATING_DISPLAY_0_INIT;
        return;
    }
    else{}

    /*..hui [20-1-6오후 9:08:55] 냉수 설정 해제 시 1단..*/
    if( F_Hot_Enable == CLEAR )
    {
        gu8_heating_display_mode = HEATING_DISPLAY_0_INIT;
        return;
    }
    else{}


    switch( gu8_heating_display_mode )
    {
        case HEATING_DISPLAY_0_INIT :
        case HEATING_DISPLAY_1_OFF :

                if( gu8_Hot_Tank_Temperature_One_Degree <= (gu8_display_heater_on_temp - 2) )
                {
                    gu8_heating_display_mode = HEATING_DISPLAY_2_ON;
                }
                else{}

                break;

        case HEATING_DISPLAY_2_ON :

                /*..hui [23-11-21오전 10:14:17] 냉수온도 8도 이하..*/
                if( gu8_Hot_Tank_Temperature_One_Degree >= gu8_display_heater_off_temp )
                {
                    gu8_heating_display_mode = HEATING_DISPLAY_1_OFF;
                }
                else{}

                break;

        default :

                gu8_heating_display_mode = HEATING_DISPLAY_1_OFF;

                break;
    }
#endif
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : System
// 개요       :
//----------------------------------------------------------------------------
// 기능       :
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************

void System(void)
{
    if(gu16IRInterval > 0)
    {
        gu16IRInterval--;            // 만빙검사 주기 15분
    }
    else{}

    if(gu16IRInterval == 0)
    {
        F_IR = SET;
    }
    else{}

    if(gu16IR_l_Interval > 0)
    {
        gu16IR_l_Interval--;            // 저빙검사 주기 15분
    }
    else{}

    if(gu16IR_l_Interval == 0)
    {
        F_Low_IR = SET;
    }
    else{}

    //===================================================// 취침모드시 6시간 제빙정지
    //if(F_Sleep == SET && F_IceFull == SET && F_IceStop != SET)
    //{
    //    F_IceStop = SET;
    //    gu16IceStopTime = ICESTOP_TIME_SIX_HOURS;
    //}
    //else if(F_Sleep != SET || gu16IceStopTime == 0)
    //{
    //    F_IceStop = CLEAR;
    //}
    //else{}


    /*..hui [18-3-6오후 5:17:36] 테스트모드 자동 해제..*/
    //if(gu16TestTime == 0 && F_LineTest == SET)
    //{
    //    F_LineTest = CLEAR;
    //    system_reset();
    //}
    //else{}

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cody_test_mode(void)
{
    cody_ice_tray_test();
    cody_service();
    cody_takeoff_ice();
    
    /* Cody Water Line Clean Service */
    cody_water_line_clean();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_ice_cody_mode(void)
{
    if( F_IceInit == SET )
    {
        /*..hui [20-2-19오후 3:26:02] 더미탈빙 대기 중 또는 진행 중 강제 탈빙하면 더미탈빙 취소..*/
        /*..hui [20-2-19오후 3:26:14] 최인식과 협의 아이스소다 동일..*/
        F_IceInit = CLEAR;
        gu8InitStep = 0;
        gu16IceMakeTime = 0;
        gu16IceHeaterTime = 0;
    }
    else
    {
        if( gu8IceStep != STATE_0_STANDBY )
        {
            /*if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP
                && gu8IceStep <= STATE_30_CALC_ICE_MAKING_TIME )*/
            if( gu8IceStep <= STATE_30_CALC_ICE_MAKING_TIME )
            {
                if( F_Comp_Output == CLEAR )
                {
                    /*..hui [20-1-29오후 3:48:29] 제빙 전단계이면 바로 만빙체크 후 종료..*/
                    /*..hui [20-2-19오후 7:46:55] 수정 - 제빙 안들어갔으므로 만빙 체크 없이 즉시 종료..*/
                    gu8IceStep = STATE_51_FINISH_ICE_MAKE;
                    /*..hui [20-1-29오후 3:53:01] 트레이도 올라가는 중이었으면 내리고..*/
                    down_tray_motor();
                }
                else
                {
                    /*..hui [23-7-21오후 5:43:03] 연속제빙.. 컴프가 동작중이면 핫가스 탈빙으로..*/
                    gu8IceStep = STATE_40_ICE_TRAY_MOVE_DOWN;
                    /*..hui [20-1-29오후 3:53:01] 트레이도 올라가는 중이었으면 내리고..*/
                    down_tray_motor();
                }
            }
            else if( gu8IceStep == STATE_31_MAIN_ICE_MAKING )
            {
                /*..hui [23-7-21오후 5:35:02] 제빙 시간에 상관없이 무조건 핫가스 탈빙 진행.. ..*/
                /*..hui [23-7-21오후 5:35:20] 냉동.. 저온에서 핫가스 탈빙해도 내구성 문제없음..*/
                gu16IceMakeTime = 0;
            }
            else if( gu8IceStep >= STATE_40_ICE_TRAY_MOVE_DOWN
                     && gu8IceStep <= STATE_43_ICE_TAKE_OFF )
            {
                /*..hui [20-1-29오후 3:47:24] 탈빙 이동중이거나 탈빙중일경우 하던거 계속 진행..*/

            }
            else{}
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void get_final_small_amb_temp(void)
{
    /*..hui [23-9-20오전 9:21:55] 둘 다 고장일경우 25도로..*/
    if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET
        && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        gu8_Amb_Temperature_One_Degree = 25;
        return;
    }
    else{}

    /*..hui [23-9-19오후 1:18:26] 외기센서2 고장시 1값으로..*/
    if( Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        gu8_Amb_Temperature_One_Degree = gu8_Amb_Front_Temperature_One_Degree;
        return;
    }
    else{}

    /*..hui [23-9-19오후 1:18:34] 외기센서1 고장시 2값으로..*/
    if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET )
    {
        gu8_Amb_Temperature_One_Degree = gu8_Amb_Side_Temperature_One_Degree;
        return;
    }
    else{}

    /*..hui [23-9-19오전 11:19:28] 청래. 두개 중 낮은 값 적용, 미사용 절전만 높은 값 적용..*/
    if( gu8_Amb_Side_Temperature_One_Degree > gu8_Amb_Front_Temperature_One_Degree )
    {
        gu8_Amb_Temperature_One_Degree = gu8_Amb_Front_Temperature_One_Degree;
    }
    else
    {
        gu8_Amb_Temperature_One_Degree = gu8_Amb_Side_Temperature_One_Degree;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_final_large_amb_temp(void)
{
    U8 mu8_return = 0;

    /*..hui [23-9-19오후 1:17:53] 둘다 고장일경우 미사용절전 진입하도록.. 우선....*/
    if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET
        && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        mu8_return = 25;
        return mu8_return;
    }
    else{}

    /*..hui [23-9-19오후 1:18:26] 외기센서2 고장시 1값으로..*/
    if( Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET )
    {
        mu8_return = gu8_Amb_Front_Temperature_One_Degree;
        return mu8_return;
    }
    else{}

    /*..hui [23-9-19오후 1:18:34] 외기센서1 고장시 2값으로..*/
    if( Bit15_Amb_Temp_Open_Short_Error__E43 == SET )
    {
        mu8_return = gu8_Amb_Side_Temperature_One_Degree;
        return mu8_return;
    }
    else{}

    /*..hui [23-9-19오전 11:19:28] 청래. 두개 중 낮은 값 적용, 미사용 절전만 높은 값 적용..*/
    /*..hui [23-9-19오후 1:18:45] 미사용 절전 조건에서는 큰 값으로..*/
    if( gu8_Amb_Side_Temperature_One_Degree > gu8_Amb_Front_Temperature_One_Degree )
    {
        mu8_return = gu8_Amb_Side_Temperature_One_Degree;
    }
    else
    {
        mu8_return = gu8_Amb_Front_Temperature_One_Degree;
    }

    return mu8_return;
}






/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

