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
#include    "M7_Error_Control.h"


void Error_Control(void);
void error_check(void);
void search_error_code(void);
void error_management(void);



TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0       // �ð� ���� ����
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1       // �¼� ���� ����
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2       // ���� ���� ����
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3       //





TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Water_Flow_Block_Error__E08              	U32ControlErrorsD.Bit.b0    //E08
#define         Bit1_Main_Water_Flow_Leaked_Error__E02              U32ControlErrorsD.Bit.b1    //E02
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01

#define         Bit4_Hot_In_Temp_Open_Short_Error__E46              U32ControlErrorsD.Bit.b4    //E46
#define         Bit5_Hot_Heater_OverHeat_Error__E40		            U32ControlErrorsD.Bit.b5    //E40
#define         Bit6_Main_Water_Flow_Block_Error__E09               U32ControlErrorsD.Bit.b6    //E09
#define         Bit7_BLDC_Communication_Error__E27                  U32ControlErrorsD.Bit.b7    //E27

#define         Bit8_BLDC_Operation_Error_Current_Sensing__E81      U32ControlErrorsD.Bit.b8    //E81
#define         Bit9_BLDC_Operation_Error_Starting_Fail__E82        U32ControlErrorsD.Bit.b9    //E82
#define         Bit10_BLDC_Operation_Error_Over_Current__E83        U32ControlErrorsD.Bit.b10   //E83
#define         Bit11_BLDC_Operation_Error_Overheat__E84            U32ControlErrorsD.Bit.b11   //E84

#define         Bit12_BLDC_Operation_Error_Disconnection_Comm__E85  U32ControlErrorsD.Bit.b12   //E85
#define         Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86    U32ControlErrorsD.Bit.b13   //E86
#define         Bit14_Cold_Temp_Open_Short_Error__E44               U32ControlErrorsD.Bit.b14   //E44
#define         Bit15_Amb_Temp_Open_Short_Error__E43                U32ControlErrorsD.Bit.b15   //E43

#define         Bit16_Drain_Pump_Error__E60                         U32ControlErrorsD.Bit.b16   //E60
#define         Bit17_Tray_Micro_SW_Dual_Detect_Error__E61          U32ControlErrorsD.Bit.b17   //E61
#define         Bit18_Tray_Micro_SW_Up_Move_Error__E62              U32ControlErrorsD.Bit.b18   //E62
#define         Bit19_Tray_Micro_SW_Down_Move_Error__E63            U32ControlErrorsD.Bit.b19   //E63

#define         Bit20_Hot_Out_Temp_Open_Short_Error__E47	        U32ControlErrorsD.Bit.b20   //E52
#define         Bit21_Amb_Side_Temp_Open_Short_Error__E53           U32ControlErrorsD.Bit.b21   //E53
#define         Bit22_Hot_Heater_Temp_Open_Short_Error__E48		    U32ControlErrorsD.Bit.b22   //E48
#define         Bit23_faucet_UV_Error__E77                  		U32ControlErrorsD.Bit.b23   //E77

#define         Bit24_Ice_Tank_UV_Error__E75					U32ControlErrorsD.Bit.b24   //E75
#define         Bit25_Ice_Faucet_UV_2_Error__E78                    U32ControlErrorsD.Bit.b25   //E78
#define         Bit26_Ice_Tank_1_2_UV_Error__E79                	U32ControlErrorsD.Bit.b26   //E79
#define         Bit27_Ice_Tray_1_2_UV_Error__E76                	U32ControlErrorsD.Bit.b27   //E76


/*..hui [20-1-3���� 9:25:01] ���� ǥ�� �켱���� ���� ����..*/
/*const U8 gu8_error_code[18] = {47, 48, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 65, 63, 63};*/
/*const U8 gu8_error_code[18] = {45, 48, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 63, 63, 63};*/
/*const U8 gu8_error_code[18] = {45, 49, 42, 1, 11, 40, 34, 13, 10, 14, 44, 43, 60, 61, 62, 63, 63, 63};*/
/*const U8 gu8_error_code[18] = {45, 49, 42, 1, 11, 40, 9, 13, 10, 14, 44, 43, 60, 61, 62, 63, 65, 65};*/
/*const U8 gu8_error_code[22] = {45, 49, 42, 1, 11, 40, 9, 27, 29, 14, 44, 43, 60, 61, 62, 63, 74, 75, 76, 76, 65, 65};*/
/*const U8 gu8_error_code[25] = {45, 49, 42, 1, 11, 40, 9, 27, 29, 14, 44, 43, 60, 61, 62, 63, 52, 53, 56, 74, 75, 76, 76, 65, 65};*/
/*const U8 gu8_error_code[25] = {45, 49, 42, 1, 21, 40, 9, 27, 29, 14, 44, 43, 60, 61, 62, 63, 52, 53, 56, 74, 75, 76, 76, 65, 65};*/
/*const U8 gu8_error_code[25] = {45, 49, 42, 1, 21, 40, 9, 27, 29, 14, 44, 43, 60, 61, 62, 63, 52, 53, 56, 74, 75, 76, 79, 65, 65};*/
/*const U8 gu8_error_code[29] = {45, 49, 42, 1, 21, 40, 9, 27, 29, 14, 44, 43, 60, 61, 62, 63, 52, 53, 56, 74, 75, 76, 79, 90, 91, 92, 93, 65, 65};*/

const U8 gu8_error_code[28] = {8, 2, 42, 1, 46, 40, 9, 27, 81, 82, 
                               83, 84, 85, 86, 44, 43, 60, 61, 62, 63,
                               47, 53, 48, 77, 75, 78, 79, 76};





/*..hui [21-9-17���� 1:29:37] TDS ���� ������ ��ǰ���� ǥ�� ����.. ���� �и�..*/
TYPE_BYTE          U8TDS_ErrorB;
#define            gu8_TDS_Error                                             U8TDS_ErrorB.byte
#define            Bit0_No_Display_Tds_In_Temp_Open_Short_Error__E90         U8TDS_ErrorB.Bit.b0
#define            Bit1_No_Display_Tds_Out_Temp_Open_Short_Error__E91        U8TDS_ErrorB.Bit.b1
#define            Bit2_No_Display_Tds_In_Data_Error__E92                    U8TDS_ErrorB.Bit.b2
#define            Bit3_No_Display_Tds_Out_Data_Error__E93                   U8TDS_ErrorB.Bit.b3
#define            Bit4_No_Display_Tds_In_Pollution_Error__E98               U8TDS_ErrorB.Bit.b4
#define            Bit5_No_Display_Tds_Remove_Error__E99                     U8TDS_ErrorB.Bit.b5

bit F_ErrAll;                     // ��ü����
//bit F_HardError;                  // �� ����
bit F_SoftError;                  // �� ����
bit F_ErrOVHRoom;                  // �������� ����
//bit F_ErrPurify;                  // �������ð� �ʰ�
//bit F_ErrColdLEVSet;              // �ü��������� ������
bit F_ErrEEPROM;                  // EEPROM ����
bit F_ErrIceVV;                   // �ü����޹�� ����
bit F_ErrIceTraySet;              // ���̽�Ʈ���� ���� ����
bit F_ErrIceTrayChk;              // ���̽�Ʈ���� ���Ӱ���
//bit F_ErrDrainSet;
//bit F_ErrOVIce;
bit F_ErrHotGas;
bit F_ErrSter;

bit F_ErrIceTray;                 // �������� ���� ����
//bit F_ErrOVCold;                  // ���� ����
//bit F_ErrOVF;                     // ����ħ ����

//----------------------------------
//bit F_ErrOVFeed;                  // ����ħ �ǵ�VV ����
//bit F_ErrOVRoomLEV;               // ����ħ ���������� ����
//bit F_ErrOVLEV;                                     // ����ħ �������� ����
//bit F_ErrRoomLowLEV;              // ���� �������� ����
//bit F_ErrColdLEV;                 // �ü� �������� ����
//----------------------------------
//bit Bit14_Cold_Temp_Open_Short_Error__E44;                  // �ü� TH ����
bit F_ErrHotTH;                   // �¼� TH ����
//bit F_ErrRoomTH;                  // ���� TH ����
bit F_ErrEvaTH;                   // ���߱� TH ����
//bit F_ErrAmbTH;                   // �����µ� TH ����
//bit F_ErrOVHot;                   // ���� ����
//bit F_ErrTrayMotor_Dual;          // �������� ����  M/S Error
//bit F_ErrTrayMotor_Move;          // �������� ���� �̵� ����
//bit F_ErrDrain;                   // �巹������,�������� ����
//bit F_ErrDrainSetFix;
bit F_ErrEWDrain;                 // EW�������
//bit F_ErrBar;                     // ����Ʈ �� ����
//----------------------------------

//bit F_ErrOVFeed_D;                  // �ǵ�VV ����
//bit F_ErrOVRoomLEV_D;               // ����ħ ���������� ����
//bit F_ErrOVLEV_D;                                       // ����ġ �������� ����
//bit F_ErrRoomLowLEV_D;              // ���� �������� ����
//bit F_ErrColdLEV_D;                 // �ü� �������� ����
//----------------------------------
//bit F_ErrColdTH_D;                  // �ü� TH ����
//bit F_ErrHotTH_D;                   // �¼� TH ����
//bit F_ErrRoomTH_D;                  // ���� TH ����
//bit F_ErrEvaTH_D;                   // ���߱� TH ����
//bit F_ErrAmbTH_D;                   // �����µ� TH ����
//bit F_ErrOVHot_D;                   // ���� ����
//bit F_ErrTrayMotor_Dual_D;          // �������� ����  M/S Error
//bit F_ErrTrayMotor_Move_D;          // �������� ���� �̵� ����
//bit F_ErrDrain_D;                   // �巹������,�������� ����
//bit F_ErrEWDrain_D;                 // EW�������
//bit F_ErrBar_D;                     // ����Ʈ �� ����
//----------------------------------


U8 gu8ErrorCode;
U8 gu8ErrorStep;

//-----------------------------------------------------// ERROR
U8 gu8ErrCds;
U8 gu8ErrEEP;
U8 gu8ErrIceMotor;
U8 gu8ErrIceMotorClear;
U8 gu8ErrRTHDelay;
U8 gu8ErrCTHDelay;
U8 gu8ErrHTHDelay;
U8 gu8ErrETHDelay;
U8 gu8ErrATHDelay;
U8 gu8IceDrainError_CNT;
U8 gu8ErrOVCDelay;
U8 gu8ErrOVHDelay;
U16 gu16ErrOVHRoomTime;
U8 gu8ErrI2C;
U8 gu8ErrKey;
U8 gu8ErrIceTray;
//U8 gu8ErrBar;
U8 gu8ErrDoor;
U16 gu16ErrIceOut;
U8 gu8ErrDoorClear;
U8 gu8ErrColdBarCnt;
U8 gu8ErrIceBarCnt;
U16 gu16ErrOVIce;
U16 gu16ErrColdLEVDelay;
U8 gu8ErrHotgas;
U8 gu8ErrHotgasSum;

U8 gu8LeakageCheckCount;
U8 gu8LeakageCheckCount2;
// 20140117 ��� �� �ü� �Լ� ��� ���� �� Ʈ���� �Լ� �̿�
// 20170706 �Ϲݹ������ ���� - 10�� ���� ���� �� ���� �� 1�� ����/2�� ���� 10ȸ �߰�(�������� & ������ ���� ����)
bit F_COLD_VV_In;
bit F_Drain_Retray;


U8 gu8DrainErrorRetrayDelay;                  // ���� �ܼ� ���
U16 gu16IceWaterExtMax;

U16 gu16IceWaterExt;

U8 gu8_Cold_level_err_1s_cnt;


U32 gu32_error_state;
U32 gu32_error_state_old;

U8 gu8_Error_Code;
U8 gu8_Err_Code_Old;
U8 gu8_Last_Error_Code;



U8 u8_re_ice_init_error;

U8 gu8_hot_water_error_code_old;

U8 gu8_hot_water_error_code;
U8 gu8_hot_water_error_year;
U8 gu8_hot_water_error_month;
U8 gu8_hot_water_error_date;



U8 gu8_now_error_occur_year;
U8 gu8_now_error_occur_month;
U8 gu8_now_error_occur_day;

U8 gu8_error_popup_enable;

bit bit_Mixing_Out_Temp_Open_Short_Error__E52;

U32 gu32_ice_init_cancel_timer;


bit bit_bldc_operation_error_total;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Error_Control(void)
{
    error_check();

    search_error_code();

    error_management();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_check(void)
{
    /*..hui [17-12-26���� 9:51:20] ���� ǥ�� �Ϸ� �� ����..*/
    if(F_FW_Version_Display_Mode != SET)
    {
        return;
    }
    else{}

    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    #ifndef __ERROR_CLEAR__
    /*..hui [19-6-26���� 11:19:16] �µ����� ����/��Ʈ ����..*/
    check_error_temp_sensor();

    /*..hui [19-6-26���� 11:36:25] ���� ���� ����..*/
    check_flow_error();

    /*..hui [19-6-26���� 11:41:48] ���� ���� ����..*/
    //check_error_water_level();

    /*..hui [23-6-29���� 7:14:54] UV ����..*/
    check_error_uv();
	
    /*..sean [25-02-03] �¼� ���� ����..*/
    if( F_Model_Select == MODEL_CHPI )
    {
        hot_water_error_check();
    }
    else{}
    #else
    u32ControlErrors = 0;
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void search_error_code(void)
{
    U8 mu8_error_count = 0;
    U8 mu8_detect_error = 0;
    /*U8 temp_error_code = 0;*/

    ////////////////////////////////////////////////////////////////////////////
    /*..hui [19-8-2���� 3:47:56] ���� 47 ; �¼� ��� �µ�����..*/
    /*..hui [19-8-2���� 3:48:00] ���� 48 ; �¼� ���� �µ�����..*/
    /*..hui [19-8-2���� 3:48:05] ���� 44 ; �ü� �µ�����..*/
    /*..hui [19-8-2���� 3:48:10] ���� 42 ; ���� �µ�����..*/
    /*..hui [19-8-2���� 3:48:16] ���� 43 ; ���� �µ�����..*/
    /*..hui [19-8-2���� 3:48:21] ���� 63 ; EVA1 �µ�����..*/
    /*..hui [19-8-2���� 3:48:26] ���� 64 ; EVA2 �µ�����..*/
    /*..hui [19-8-2���� 3:48:31] ���� 01 ; ���� ����..*/
    /*..hui [19-8-2���� 3:48:38] ���� 11 ; ������..*/
    /*..hui [19-8-2���� 3:48:45] ���� 60 ; �巹�� ���� ����..*/
    /*..hui [19-8-2���� 3:49:08] ���� 61 ; ����ũ�� ����ġ ���� ���� ����..*/
    /*..hui [19-8-2���� 3:50:18] ���� 62 ; ����ũ�� ����ġ �̵� ����..*/
    /*..hui [19-8-2���� 3:50:23] ���� 40 ; �¼��µ� ����..*/
    /*..hui [19-8-2���� 3:50:27] ���� 34 ; �¼� ������� �� �¼� �ܼ�..*/
    ////////////////////////////////////////////////////////////////////////////

    if(u32ControlErrors > 0)
    {
        for(mu8_error_count = 0; mu8_error_count < MAX_ERROR_NUM; mu8_error_count++)
        {
            mu8_detect_error = (U8)(((U32)(u32ControlErrors) >> mu8_error_count) & 0x01);

            if(mu8_detect_error == 0x01)
            {
                gu8_Error_Code = gu8_error_code[mu8_error_count];
                return;
            }
            else{}
        }
    }
    else
    {
        gu8_Error_Code = 0;
    }

    /*..hui [24-11-18���� 3:44:45] �������ۿ��� ����..*/
    if( Bit8_BLDC_Operation_Error_Current_Sensing__E81 == SET
        || Bit9_BLDC_Operation_Error_Starting_Fail__E82 == SET
        || Bit10_BLDC_Operation_Error_Over_Current__E83 == SET
        || Bit11_BLDC_Operation_Error_Overheat__E84 == SET
        || Bit12_BLDC_Operation_Error_Disconnection_Comm__E85 == SET
        || Bit13_BLDC_Operation_Error_Abnormal_Voltage__E86 == SET )
    {
        bit_bldc_operation_error_total = SET;
    }
    else
    {
        bit_bldc_operation_error_total = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_management(void)
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [19-8-2���� 6:51:28] ���� �߻� �� �ð� ����..*/
    /*..hui [19-8-2���� 6:51:32] �ü� �µ����� ����..*/
    /*..hui [19-12-18���� 10:41:07] �ǵ���/���� ��߶��� ���� �߰�..*/
    if( Bit14_Cold_Temp_Open_Short_Error__E44 == SET
    || Bit3_Leakage_Sensor_Error__E01 == SET
    || Bit7_BLDC_Communication_Error__E27 == SET
    || bit_bldc_operation_error_total == SET
    || bit_temporary_comm_error == SET
    || bit_temporary_operation_error == SET )
        /*|| Bit7_Room_High_Water_Level_Error__E13_Not_Use == SET*/
        /*|| Bit8_Feed_Valve_Error__E10_Not_Use == SET*/
        /*|| Bit9_Room_Level_Unbalance_Error__E14_Not_Use == SET )*/
    {
        Bit0_Cold_Operation_Disable_State = SET;
    }
    else
    {
        Bit0_Cold_Operation_Disable_State = CLEAR;
    }

    /* ����, �ܼ����� �߻��Ǹ� ���� ��� ���� */
    if( Bit3_Leakage_Sensor_Error__E01 == SET
    || Bit6_Main_Water_Flow_Block_Error__E09 == SET 
    || (Bit0_Hot_Water_Flow_Block_Error__E08 == SET && u8WaterOutState == HOT_WATER_SELECT))
    {
        if( F_WaterOut == SET )
        {
            F_WaterOut = CLEAR;
            u8Extract_Continue = CLEAR;
        }
        else if( F_IceOut == SET )
		{
			F_IceOut = CLEAR;
        	F_IceOutCCW = CLEAR;
            F_IceBreak_Motor_Out = CLEAR;
            gu8_ice_out_continue = CLEAR;
            gu8_Ice_Out_Step = STATE_0_ICE_STANDBY_STATE;
		}
        else{}

        /* �����߻� �� ���� ���� ���õ� ������ Ŭ���� 250731 CH.PARK */
        Extract_Stack.U8_waterSelect = CLEAR;
        Extract_Stack.U8_iceSelect = CLEAR;
    }
    else{}

    /*..hui [23-12-15���� 4:36:27] ���� ���� ���� �߰�..*/
    if( (Bit3_Leakage_Sensor_Error__E01 == SET)
    || (Bit6_Main_Water_Flow_Block_Error__E09 == SET)
    || (Bit0_Hot_Water_Flow_Block_Error__E08 == SET)
    || (Bit4_Hot_In_Temp_Open_Short_Error__E46 == SET) 
    || (Bit20_Hot_Out_Temp_Open_Short_Error__E47 == SET)
    || (Bit22_Hot_Heater_Temp_Open_Short_Error__E48 == SET)
    )
    {
        Bit1_Hot_Operation_Disable_State = SET;
        /*..hui [23-7-27���� 2:36:44] �������� ���̾����� �ߴ�..*/
        /*..hui [23-7-27���� 2:36:56] �¼����� OFF �����̹Ƿ�..*/
        /*stop_hot_preheating();*/
    }
    else
    {
        Bit1_Hot_Operation_Disable_State = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    if(   Bit2_Room_Temp_Open_Short_Error__E42 == SET
       /*|| Bit18_Tray_In_Temp_Open_Short_Error__E41 == SET*/
       || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
       || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
       || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET

       || Bit16_Drain_Pump_Error__E60 == SET
       /*..sean [25-01-20] �������̾ pass..*/
       /*|| Bit4_Room_Low_Water_Level_Error__E21 == SET*/

       /*..hui [23-9-20���� 9:24:23] �� �� ����..*/
       /* �ܱ�µ� ���� �Ѵ� ������ ��� ������ �Ǵ������� ������ ����Ʈ������ �����Ѵ� 250630 CH.PARK */
       // || (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
       /*|| Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET*/

       || Bit3_Leakage_Sensor_Error__E01 == SET
    //    || Bit6_Main_Water_Flow_Block_Error__E09 == SET
       || Bit7_BLDC_Communication_Error__E27 == SET
       || bit_bldc_operation_error_total == SET
       || bit_temporary_comm_error == SET
       || bit_temporary_operation_error == SET )
       /*|| Bit7_Room_High_Water_Level_Error__E13_Not_Use == SET*/
       /*|| bit_tray_in_error_temporary == SET*/
       /*|| Bit8_Feed_Valve_Error__E10_Not_Use == SET*/
       /*|| Bit9_Room_Level_Unbalance_Error__E14_Not_Use == SET )*/
    {
        Bit2_Ice_Operation_Disable_State = SET;

        if( F_IceInit == SET )
        {
            gu32_ice_init_cancel_timer++;

            /*..hui [24-2-6���� 9:43:07] ����Ż�� ���� ���� ���� ���� �߻��ϰ� 2�ð� ������ ����Ż�� ���..*/
            /*..hui [24-2-6���� 9:43:13] �ð� ��ȯ�ؼ� �ð��ϱ� ����..*/
            if( gu32_ice_init_cancel_timer >= ICE_INIT_ERROR_CANCEL_TIME )
            {
                gu32_ice_init_cancel_timer = 0;
                F_IceInit = CLEAR;
                gu8InitStep = 0;
            }
            else{}
        }
        else
        {
            gu32_ice_init_cancel_timer = 0;
        }

        /*..hui [19-12-18���� 7:50:28] ���� �����ǰ� ����Ż�� �����ϴ� ������..*/
        /*..hui [19-12-18���� 10:41:07] �ǵ���/���� ��߶��� ���� �߰�..*/
        /*..hui [19-12-18���� 10:44:09] �ǵ���/���� ��߶����� �ڵ������� �ƴϱ⶧���� �ǹ̾���..*/
        /*..hui [19-12-18���� 10:44:30] ���������� ������ ��������..*/
        /*..hui [19-12-19���� 1:00:22] �����µ������� ���� ���� ���������ϱ� ������ ����..*/
        if(   
           /*..hui [23-9-20���� 9:24:23] �� �� ����..*/
           (Bit15_Amb_Temp_Open_Short_Error__E43 == SET && Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET)
           /*|| Bit21_Amb_Side_Temp_Open_Short_Error__E53 == SET*/

           || Bit3_Leakage_Sensor_Error__E01 == SET )
        {
            if( gu8IceStep >= STATE_31_MAIN_ICE_MAKING
            && gu8IceStep <= STATE_43_ICE_TAKE_OFF )
            {
                /*..hui [19-12-18���� 10:43:42] �����߿� ���� �ɷ������� ���������� ����Ż�� ����..*/
                u8_re_ice_init_error = SET;
            }
            else{}
        }
        else{}

        /*..hui [20-2-13���� 5:42:54] ���� �߻� �� Ʈ���� ����.. Ʈ���̿� �� ���ִ� ��Ȳ �߻��� �� ����..*/
        /*..hui [20-2-14���� 11:20:25] ��, Ʈ���� ���� ������ �׳� ����ġ��� ���ܵ�.. ���� �����ϵ���..*/
        if((Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 != SET)
        && (Bit18_Tray_Micro_SW_Up_Move_Error__E62 != SET)
        && (Bit19_Tray_Micro_SW_Down_Move_Error__E63 != SET)
        )
        {
            if( gu8IceStep >= STATE_10_ICE_TRAY_MOVE_UP )
            {
                if( gu8IceTrayLEV != ICE_TRAY_POSITION_ICE_THROW )
                {
                    down_tray_motor();
                }
                else {  }
            }
            else {  }
        }
        else {  }
    }
    else
    {
        Bit2_Ice_Operation_Disable_State = CLEAR;

        if(u8_re_ice_init_error == SET)
        {
            u8_re_ice_init_error = CLEAR;
            F_IceInit = SET;
        }
        else{}
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    /*..hui [23-3-3���� 2:09:16] �¼���ũ ��� �Ұ� ����..*/
    /*..hui [23-8-24���� 1:24:20] �¼����� ����, ���� ���� ���� �߰�..*/
    /*..hui [24-1-8���� 1:53:19] �ü� �µ����� ���� �߰�....*/
    /*..hui [24-1-8���� 1:53:35] �ʱ� ���Խ� �ü� �µ� Ȯ���ϱ� ����..*/
    /*..hui [24-1-8���� 1:55:13] �ð��� ������ �߰�..*/
    /*..hui [24-2-23���� 9:09:47] �¼� OFF�ϸ� �¼����� ���� ���� ���ϱ� ������ �¼� OFF ������ AD ���� �߰�..*/
    if(   Bit16_Drain_Pump_Error__E60 == SET
       || Bit3_Leakage_Sensor_Error__E01 == SET

       || Bit4_Hot_In_Temp_Open_Short_Error__E46 == SET
       || Bit5_Hot_Heater_OverHeat_Error__E40 == SET
       || Bit20_Hot_Out_Temp_Open_Short_Error__E47 == SET
       || Bit22_Hot_Heater_Temp_Open_Short_Error__E48 == SET

       || Bit0_Hot_Water_Flow_Block_Error__E08 == SET
       || Bit6_Main_Water_Flow_Block_Error__E09 == SET
       || Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 == SET
       || Bit18_Tray_Micro_SW_Up_Move_Error__E62 == SET
       || Bit19_Tray_Micro_SW_Down_Move_Error__E63 == SET )
    {
        Bit3_Ice_Tank_Ster_Operation_Disable_State = SET;
    }
    else
    {
        Bit3_Ice_Tank_Ster_Operation_Disable_State = CLEAR;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( gu8_Error_Code != 0 )
    {
        /*..hui [18-1-10���� 9:05:35] �켱���� ������� �ű� ���� �߰��ɋ����� ������ �︮�� ���� ����..*/
        /*if(gu32_error_state != gu32_error_state_old)*/
        /*..hui [18-1-10���� 9:07:20] ���� �ɸ����� ������ �������.. �����ɶ��� �︮��ȵȴ�....*/
        /*if(u32ControlErrors > gu32_error_state_old)*/
        if(u32ControlErrors > gu32_error_state_old)
        {
            /*..hui [19-3-26���� 11:22:16] ���� �ɷ����� ������ ����� ���ϴ°ɷ�..*/
            /*..hui [19-8-2���� 6:40:37] LCD �ϼ��Ǳ����� ���� �߻����� Ȯ���ϱ�����.....*/
            /*BuzStep(BUZZER_ERROR);*/
            /*gu8_error_popup_enable = SET;*/
        }
        else{}

        if( gu8_Err_Code_Old != gu8_Error_Code )
        {
            #if 0
            /*..hui [20-1-20���� 8:15:50] �켱���� ���� ������ ����������� �˾� ǥ��..*/
            /*..hui [20-1-20���� 8:20:52] ���� �ɸ� ���¿��� �켱���� ���� ���� �ɸ���� �߰� ǥ�� ���Ѵ�..*/
            gu8_error_popup_enable = SET;

            gu8_now_error_occur_year = gu8_rtc_time_Year;
            gu8_now_error_occur_month = gu8_rtc_time_Month;
            gu8_now_error_occur_day = gu8_rtc_time_Date;
            #endif

            /*..hui [23-9-1���� 9:36:48] �����Ҷ��� ǥ���ϴ°ɷ� ����.. ���� �߻��� ǥ�þ��� = ���ν�..*/
            /*..hui [23-11-28���� 4:41:59] �ٽ� ǥ���ϴ°ɷ�..*/
            #if 0
            if( gu8_Error_Code != gu8_Last_Error_Code )
            {
                gu8_Last_Error_Code = gu8_Error_Code;
                gu8_error_popup_enable = SET;
            }
            else{}
            #endif


            if( gu8_Error_Code == 75
            || gu8_Error_Code == 76
            || gu8_Error_Code == 77
            || gu8_Error_Code == 78
            || gu8_Error_Code == 79)
            {
                gu8_error_popup_enable = CLEAR;
            }
            else
            {
                gu8_error_popup_enable = SET;
            }
        }
        else{}

        gu32_error_state_old = u32ControlErrors;
        gu8_Err_Code_Old = gu8_Error_Code;
    }
    else
    {
        gu32_error_state_old = 0;
        gu8_Err_Code_Old = 0;
        //gu8_error_popup_enable = CLEAR;
    }

    ErrorSaveStart( gu8_Error_Code );
    //ErrorSave();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


