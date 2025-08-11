/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _FLUSHING_H_
#define _FLUSHING_H_

//

extern void BuzStep(U8 mu8Step);
extern void WifiKey ( E_WIFI_KEY_T mu8Key );
extern U8 GetWifiStatusValue ( E_WIFI_STATUS_T mType );
extern void down_tray_motor(void);
extern void up_tray_motor(void);
extern void run_open_ro_drain(void);
extern void run_close_ro_drain(void);
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_voice_install_guide_75( void );
//extern void play_voice_pairing_auto_start_76( void );
extern void play_voice_filter_flushing_start_23( void );
extern void play_voice_filter_flushing_finish_24( void );
extern void play_voice_test_mode_151( void );
extern void calc_flushing_water(void);
extern void init_filter_data(void);
extern void finish_ct_forced_flushing(void);
extern void Play_Voice(U16 mu16MemoryAddress);
extern void play_voice_filter_not_detected_14(void);
extern void play_voice_filter_cover_opened_44(void);
extern void diplay_test_start(void);
extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                                    U32ControlErrorsD.dward
#define         Bit0_Hot_Water_Flow_Block_Error__E08              	U32ControlErrorsD.Bit.b0    //E08
#define         Bit1_Main_Water_Flow_Leaked_Error__E02              U32ControlErrorsD.Bit.b1    //E02
#define         Bit2_Room_Temp_Open_Short_Error__E42                U32ControlErrorsD.Bit.b2    //E42
#define         Bit3_Leakage_Sensor_Error__E01                      U32ControlErrorsD.Bit.b3    //E01
#define         Bit4_Hot_In_Temp_Open_Short_Error__E46              U32ControlErrorsD.Bit.b4    //E46
#define         Bit5_Hot_Heater_OverHeat_Error__E40			        U32ControlErrorsD.Bit.b5    //E40
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








extern TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3



extern TYPE_BYTE          U8FilterResetStateB;
#define            u8FilterResetState                            U8FilterResetStateB.byte
#define            Bit0_Neo_Filter_1_Reset_State                 U8FilterResetStateB.Bit.b0
#define            Bit1_Ro_Filter_2_Reset_State                  U8FilterResetStateB.Bit.b1
#define            Bit2_Ino_Filter_3_Reset_State                 U8FilterResetStateB.Bit.b2

extern TYPE_BYTE          U8CTFilterReplaceB;
#define            gu8CTFilterReplace                           U8CTFilterReplaceB.byte
#define            Bit0_CT_Neo_Filter_1_Replace                 U8CTFilterReplaceB.Bit.b0
#define            Bit1_CT_Ro_Filter_2_Replace                  U8CTFilterReplaceB.Bit.b1
#define            Bit2_CT_Ino_Filter_3_Replace                 U8CTFilterReplaceB.Bit.b2

extern TYPE_BYTE       U8OperationB;
#define         u8Operation                                       U8OperationB.byte
#define         Bit0_Cold_Operation_Disable_State                 U8OperationB.Bit.b0
#define         Bit1_Hot_Operation_Disable_State                  U8OperationB.Bit.b1
#define         Bit2_Ice_Operation_Disable_State                  U8OperationB.Bit.b2
#define         Bit3_Ice_Tank_Ster_Operation_Disable_State        U8OperationB.Bit.b3



#define FLUSHING_DELAY_TIME                  5
/*..hui [23-6-2���� 10:17:43] ��ġ�÷��� 30��..*/
#define INSTALL_FLUSHING_TIME                30


#define NEO_INO_REPLACE_FLUSHING_TIME        2


/////#define FLUSHING_TANK_MAX_TIME               24000
#define FLUSHING_TANK_MAX_TIME               18000


///#define FLUSHING_LOW_WATER_MAX_TIME          9000
///#define FLUSHING_HIGH_WATER_MAX_TIME         9000
/*#define FLUSHING_LOW_WATER_MAX_TIME          36000*/
//#define FLUSHING_LOW_WATER_MAX_TIME          54000
//#define FLUSHING_HIGH_WATER_MAX_TIME         36000

/*..hui [23-11-13���� 10:02:08] ���������� 2�ð�.. ���������� 1�ð�30������ ����..*/
/*..hui [23-11-13���� 10:02:17] ���� �÷ῡ�� 20PSI �ܼ� �ɷ���..*/
/*#define FLUSHING_LOW_WATER_MAX_TIME          72000*/
/*#define FLUSHING_HIGH_WATER_MAX_TIME         54000*/

#define FLUSHING_LOW_WATER_MAX_TIME          90000
#define FLUSHING_HIGH_WATER_MAX_TIME         72000


#define ICE_TRAY_FLUSHING_TIME               600
#define FLUSHING_AIR_REMOVE_TIME             100



#define RO_DRAIN_FLUSHING_TIME               300

extern U8 gu8_filter_change_type;
extern bit bit_yes_no_popup;
extern U8 gu8_wifi_ap_first_temporary;
extern bit bit_filter_reed;
extern bit bit_ro_filter_2_reed;
extern bit bit_filter_all;
extern bit bit_filter_cover;
extern bit bit_filter_reset_yes;
extern bit bit_filter_reset_no;
extern U16 gu16_AD_Drain_Pump_Current;
extern U8 gu8_Room_Water_Level;
extern U8 gu8IceTrayLEV;
extern U8 gu8_ro_drain_status;
extern bit bit_flushing_water_start;

extern U8 gu8_ice_system_ok;

extern U8 gu8_flushing_finish_input_count;

extern U8 gu8_ct_forced_flushing_start;
extern bit bit_ct_flushing_standby_start;
extern U32 gu32_acid_clean_timer;
extern bit F_All_Lock;



#endif
