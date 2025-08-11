/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _CODY_SERVICE_H_
#define _CODY_SERVICE_H_

//
extern void stop_ice_cody_mode(void);
extern void play_melody_warning_197( void );
extern void play_melody_setting_on_198( void );
extern void play_melody_setting_off_199( void );
extern void play_voice_top_cover_open_2( void );
extern void play_voice_top_cover_close_6( void );


extern TYPE_LONG       U32ControlErrorsD;
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

extern TYPE_BYTE          U8FrontTempHundredB;
#define            gu8_front_temp_fnd_hundred                  U8FrontTempHundredB.byte
#define            Bit0_Front_Temp_Fnd_Hundred_1               U8FrontTempHundredB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Hundred_2               U8FrontTempHundredB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Hundred_3               U8FrontTempHundredB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Hundred_4               U8FrontTempHundredB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Hundred_5               U8FrontTempHundredB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Hundred_6               U8FrontTempHundredB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Hundred_7               U8FrontTempHundredB.Bit.b6

extern TYPE_BYTE          U8FrontTempTenB;
#define            gu8_front_temp_fnd_ten                      U8FrontTempTenB.byte
#define            Bit0_Front_Temp_Fnd_Ten_1                   U8FrontTempTenB.Bit.b0
#define            Bit1_Front_Temp_Fnd_Ten_2                   U8FrontTempTenB.Bit.b1
#define            Bit2_Front_Temp_Fnd_Ten_3                   U8FrontTempTenB.Bit.b2
#define            Bit3_Front_Temp_Fnd_Ten_4                   U8FrontTempTenB.Bit.b3
#define            Bit4_Front_Temp_Fnd_Ten_5                   U8FrontTempTenB.Bit.b4
#define            Bit5_Front_Temp_Fnd_Ten_6                   U8FrontTempTenB.Bit.b5
#define            Bit6_Front_Temp_Fnd_Ten_7                   U8FrontTempTenB.Bit.b6

extern TYPE_BYTE          U8FrontTempOneB;
#define            gu8_front_temp_fnd_one                      U8FrontTempOneB.byte
#define            Bit0_Front_Temp_Fnd_One_1                   U8FrontTempOneB.Bit.b0
#define            Bit1_Front_Temp_Fnd_One_2                   U8FrontTempOneB.Bit.b1
#define            Bit2_Front_Temp_Fnd_One_3                   U8FrontTempOneB.Bit.b2
#define            Bit3_Front_Temp_Fnd_One_4                   U8FrontTempOneB.Bit.b3
#define            Bit4_Front_Temp_Fnd_One_5                   U8FrontTempOneB.Bit.b4
#define            Bit5_Front_Temp_Fnd_One_6                   U8FrontTempOneB.Bit.b5
#define            Bit6_Front_Temp_Fnd_One_7                   U8FrontTempOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////

/*..hui [25-3-25���� 5:51:11] õ���ڸ� �߰�..*/
extern TYPE_BYTE          U8FrontAmountThousandB;
#define            gu8_front_amount_fnd_thousand               U8FrontAmountThousandB.byte
#define            Bit0_Front_Amount_Fnd_Thousand_1            U8FrontAmountThousandB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Thousand_2            U8FrontAmountThousandB.Bit.b1


extern TYPE_BYTE          U8FrontAmountHundredB;
#define            gu8_front_amount_fnd_hundred                U8FrontAmountHundredB.byte
#define            Bit0_Front_Amount_Fnd_Hundred_1             U8FrontAmountHundredB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Hundred_2             U8FrontAmountHundredB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Hundred_3             U8FrontAmountHundredB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Hundred_4             U8FrontAmountHundredB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Hundred_5             U8FrontAmountHundredB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Hundred_6             U8FrontAmountHundredB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Hundred_7             U8FrontAmountHundredB.Bit.b6

extern TYPE_BYTE          U8FrontAmountTenB;
#define            gu8_front_amount_fnd_ten                    U8FrontAmountTenB.byte
#define            Bit0_Front_Amount_Fnd_Ten_1                 U8FrontAmountTenB.Bit.b0
#define            Bit1_Front_Amount_Fnd_Ten_2                 U8FrontAmountTenB.Bit.b1
#define            Bit2_Front_Amount_Fnd_Ten_3                 U8FrontAmountTenB.Bit.b2
#define            Bit3_Front_Amount_Fnd_Ten_4                 U8FrontAmountTenB.Bit.b3
#define            Bit4_Front_Amount_Fnd_Ten_5                 U8FrontAmountTenB.Bit.b4
#define            Bit5_Front_Amount_Fnd_Ten_6                 U8FrontAmountTenB.Bit.b5
#define            Bit6_Front_Amount_Fnd_Ten_7                 U8FrontAmountTenB.Bit.b6

extern TYPE_BYTE          U8FrontAmountOneB;
#define            gu8_front_amount_fnd_one                    U8FrontAmountOneB.byte
#define            Bit0_Front_Amount_Fnd_One_1                 U8FrontAmountOneB.Bit.b0
#define            Bit1_Front_Amount_Fnd_One_2                 U8FrontAmountOneB.Bit.b1
#define            Bit2_Front_Amount_Fnd_One_3                 U8FrontAmountOneB.Bit.b2
#define            Bit3_Front_Amount_Fnd_One_4                 U8FrontAmountOneB.Bit.b3
#define            Bit4_Front_Amount_Fnd_One_5                 U8FrontAmountOneB.Bit.b4
#define            Bit5_Front_Amount_Fnd_One_6                 U8FrontAmountOneB.Bit.b5
#define            Bit6_Front_Amount_Fnd_One_7                 U8FrontAmountOneB.Bit.b6

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

///////////
extern TYPE_BYTE          U8FrontLeftLEDB;
#define            gu8_front_left_led                          U8FrontLeftLEDB.byte
#define            Bit0_Front_Left_Led_Ice_Full_Text           U8FrontLeftLEDB.Bit.b0
#define            Bit1_Front_Left_Led_UV_Ster_Text            U8FrontLeftLEDB.Bit.b1
#define            Bit2_Front_Left_Led_Hot_Ster_Text           U8FrontLeftLEDB.Bit.b2
#define            Bit3_Front_Left_Led_Sleep_Icon              U8FrontLeftLEDB.Bit.b3
#define            Bit4_Front_Left_Led_Step_Text               U8FrontLeftLEDB.Bit.b4
#define            Bit5_Front_Left_Led_Clock_Colon_Icon        U8FrontLeftLEDB.Bit.b5
#define            Bit6_Front_Left_Led_Celcius_oC_Icon         U8FrontLeftLEDB.Bit.b6
#define            Bit7_Front_Left_Led_Ice_First_Icon          U8FrontLeftLEDB.Bit.b7


extern TYPE_BYTE          U8FrontRightLEDB;
#define            gu8_front_right_led                         U8FrontRightLEDB.byte
#define            Bit0_Front_Right_Led_Wifi_Icon_White        U8FrontRightLEDB.Bit.b0
#define            Bit1_Front_Right_Led_Wifi_Icon_Blue_Not_Use U8FrontRightLEDB.Bit.b1
#define            Bit2_Front_Right_Led_Sunny_Icon             U8FrontRightLEDB.Bit.b2
#define            Bit3_Front_Right_Led_Cloud_Icon             U8FrontRightLEDB.Bit.b3
#define            Bit4_Front_Right_Led_Rain_Icon              U8FrontRightLEDB.Bit.b4
#define            Bit5_Front_Right_Led_Percent_Icon           U8FrontRightLEDB.Bit.b5
#define            Bit6_Front_Right_Led_Liter_L_Icon_Not_Use   U8FrontRightLEDB.Bit.b6
#define            Bit7_Front_Right_Led_ml_Icon                U8FrontRightLEDB.Bit.b7


extern TYPE_BYTE          U8FrontTempSettingLEDB;
#define            gu8_front_temp_setting_bar_led              U8FrontTempSettingLEDB.byte
#define            Bit0_Front_Led_Temp_Setting_Bar_1_1         U8FrontTempSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Temp_Setting_Bar_1_2         U8FrontTempSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Temp_Setting_Bar_1_3         U8FrontTempSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Temp_Setting_Bar_1_4         U8FrontTempSettingLEDB.Bit.b3

extern TYPE_BYTE          U8FrontAmountSettingLEDB;
#define            gu8_front_amount_setting_bar_led            U8FrontAmountSettingLEDB.byte
#define            Bit0_Front_Led_Amount_Setting_Bar_2_1       U8FrontAmountSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Amount_Setting_Bar_2_2       U8FrontAmountSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Amount_Setting_Bar_2_3       U8FrontAmountSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Amount_Setting_Bar_Continue  U8FrontAmountSettingLEDB.Bit.b3

extern TYPE_BYTE          U8FrontCenterRecipeLEDB;
#define            gu8_front_center_recipe_led                 U8FrontCenterRecipeLEDB.byte
#define            Bit0_Front_Center_Recipe_Ramen_Text         U8FrontCenterRecipeLEDB.Bit.b0
#define            Bit1_Front_Center_Recipe_Drip_Coffee_Text   U8FrontCenterRecipeLEDB.Bit.b1
#define            Bit2_Front_Center_MY_1_Text                 U8FrontCenterRecipeLEDB.Bit.b2
#define            Bit3_Front_Center_MY_2_Text                 U8FrontCenterRecipeLEDB.Bit.b3

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_BYTE          U8FrontSelectLEDB;
#define            gu8_front_select_led                        U8FrontSelectLEDB.byte
#define            Bit0_Front_Led_Ice_Water_Select             U8FrontSelectLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Select                   U8FrontSelectLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Select                   U8FrontSelectLEDB.Bit.b2
#define            Bit3_Front_Led_Ambient_Select               U8FrontSelectLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Select                  U8FrontSelectLEDB.Bit.b4
#define            Bit5_Front_Led_Amount_Select                U8FrontSelectLEDB.Bit.b5

extern TYPE_BYTE          U8FrontSettingLEDB;
#define            gu8_front_setting_led                       U8FrontSettingLEDB.byte
#define            Bit0_Front_Led_Ice_Off                      U8FrontSettingLEDB.Bit.b0
#define            Bit1_Front_Led_Ice_Size                     U8FrontSettingLEDB.Bit.b1
#define            Bit2_Front_Led_Hot_Lock                     U8FrontSettingLEDB.Bit.b2
#define            Bit3_Front_Led_Ice_First                    U8FrontSettingLEDB.Bit.b3
#define            Bit4_Front_Led_Cold_Temp                    U8FrontSettingLEDB.Bit.b4
#define            Bit5_Front_Led_Sleep_Mode                   U8FrontSettingLEDB.Bit.b5
#define            Bit6_Front_Led_Ice_Lock                     U8FrontSettingLEDB.Bit.b6
#define            Bit7_Front_Led_All_Lock                     U8FrontSettingLEDB.Bit.b7


extern TYPE_BYTE          U8FrontUnderTextLEDB;
#define            gu8_front_under_text_led                    U8FrontUnderTextLEDB.byte
#define            Bit0_Front_Under_Txt_Led_Ice_Large          U8FrontUnderTextLEDB.Bit.b0
#define            Bit1_Front_Under_Txt_Led_Ice_Center_bar     U8FrontUnderTextLEDB.Bit.b1
#define            Bit2_Front_Under_Txt_Led_Ice_Small          U8FrontUnderTextLEDB.Bit.b2
#define            Bit3_Front_Under_Txt_Led_Cold_High          U8FrontUnderTextLEDB.Bit.b3
#define            Bit4_Front_Under_Txt_Led_Cold_Center_Bar    U8FrontUnderTextLEDB.Bit.b4
#define            Bit5_Front_Under_Txt_Led_Cold_Low           U8FrontUnderTextLEDB.Bit.b5


extern TYPE_BYTE          U8FrontUnderIconLEDB;
#define            gu8_front_under_icon_led                    U8FrontUnderIconLEDB.byte
#define            Bit0_Front_Under_Icon_Led_Ice_Lock          U8FrontUnderIconLEDB.Bit.b0
#define            Bit1_Front_Under_Icon_Led_Hot_Lock          U8FrontUnderIconLEDB.Bit.b1
#define            Bit2_Front_Under_Icon_Led_Comp_Dot_White    U8FrontUnderIconLEDB.Bit.b2
#define            Bit3_Front_Under_Led_Ice_Extract            U8FrontUnderIconLEDB.Bit.b3
#define            Bit4_Front_Under_Water_White_Extract          U8FrontUnderIconLEDB.Bit.b4
#define            Bit5_Front_Under_Led_Welcome                U8FrontUnderIconLEDB.Bit.b5
#define            Bit6_Front_Under_Icon_Led_Comp_Dot_Blue     U8FrontUnderIconLEDB.Bit.b6




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
extern TYPE_DIMMING       U8DimmingPercentNo1;
#define            gu8_dimming_set_one                         U8DimmingPercentNo1.byte
#define            bit_0_3_ice_select                          U8DimmingPercentNo1.nibble.b0_3
#define            bit_4_7_ice_water_select                    U8DimmingPercentNo1.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo2;
#define            gu8_dimming_set_two                         U8DimmingPercentNo2.byte
#define            bit_0_3_hot_select                          U8DimmingPercentNo2.nibble.b0_3
#define            bit_4_7_ambient_select                      U8DimmingPercentNo2.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo3;
#define            gu8_dimming_set_three                       U8DimmingPercentNo3.byte
#define            bit_0_3_cold_select                         U8DimmingPercentNo3.nibble.b0_3
#define            bit_4_7_amount_select                       U8DimmingPercentNo3.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo4;
#define            gu8_dimming_set_four                        U8DimmingPercentNo4.byte
#define            bit_0_3_left_seg_1_0_0                      U8DimmingPercentNo4.nibble.b0_3
#define            bit_4_7_left_seg_0_2_0                      U8DimmingPercentNo4.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo5;
#define            gu8_dimming_set_five                        U8DimmingPercentNo5.byte
#define            bit_0_3_left_seg_0_0_3                      U8DimmingPercentNo5.nibble.b0_3
#define            bit_4_7_right_seg_1_0_0_0                   U8DimmingPercentNo5.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo6;
#define            gu8_dimming_set_six                         U8DimmingPercentNo6.byte
#define            bit_0_3_right_seg_0_2_0_0                   U8DimmingPercentNo6.nibble.b0_3
#define            bit_4_7_right_seg_0_0_3_0                   U8DimmingPercentNo6.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo7;
#define            gu8_dimming_set_seven                       U8DimmingPercentNo7.byte
#define            bit_0_3_right_seg_0_0_0_4                   U8DimmingPercentNo7.nibble.b0_3
#define            bit_4_7_ice_first_icon                      U8DimmingPercentNo7.nibble.b4_7


//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo8;
#define            gu8_dimming_set_eight                       U8DimmingPercentNo8.byte
#define            bit_0_3_ice_full_txt                        U8DimmingPercentNo8.nibble.b0_3
#define            bit_4_7_UV_ster_txt                         U8DimmingPercentNo8.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo9;
#define            gu8_dimming_set_nine                        U8DimmingPercentNo9.byte
#define            bit_0_3_hot_ster_txt                        U8DimmingPercentNo9.nibble.b0_3
#define            bit_4_7_sleep_icon                          U8DimmingPercentNo9.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo10;
#define            gu8_dimming_set_ten                         U8DimmingPercentNo10.byte
#define            bit_0_3_step_txt                            U8DimmingPercentNo10.nibble.b0_3
#define            bit_4_7_clock_colon_icon                    U8DimmingPercentNo10.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo11;
#define            gu8_dimming_set_eleven                      U8DimmingPercentNo11.byte
#define            bit_0_3_oC_icon                             U8DimmingPercentNo11.nibble.b0_3
#define            bit_4_7_fast_ice_icon                       U8DimmingPercentNo11.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo12;
#define            gu8_dimming_set_twelve                      U8DimmingPercentNo12.byte
#define            bit_0_3_wifi_white_icon                     U8DimmingPercentNo12.nibble.b0_3
#define            bit_4_7_no_12_not_use                       U8DimmingPercentNo12.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo13;
#define            gu8_dimming_set_thirteen                    U8DimmingPercentNo13.byte
#define            bit_0_3_sunny_icon                          U8DimmingPercentNo13.nibble.b0_3
#define            bit_4_7_cloud_icon                          U8DimmingPercentNo13.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo14;
#define            gu8_dimming_set_fourteen                    U8DimmingPercentNo14.byte
#define            bit_0_3_rain_icon                           U8DimmingPercentNo14.nibble.b0_3
#define            bit_4_7_percent_icon                        U8DimmingPercentNo14.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo15;
#define            gu8_dimming_set_fifteen                     U8DimmingPercentNo15.byte
#define            bit_0_3_no_15_not_use                       U8DimmingPercentNo15.nibble.b0_3
#define            bit_4_7_ml_txt                              U8DimmingPercentNo15.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo16;
#define            gu8_dimming_set_sixteen                     U8DimmingPercentNo16.byte
#define            bit_0_3_temp_bar_1_1                        U8DimmingPercentNo16.nibble.b0_3
#define            bit_4_7_temp_bar_1_2                        U8DimmingPercentNo16.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo17;
#define            gu8_dimming_set_seventeen                   U8DimmingPercentNo17.byte
#define            bit_0_3_temp_bar_1_3                        U8DimmingPercentNo17.nibble.b0_3
#define            bit_4_7_temp_bar_1_4                        U8DimmingPercentNo17.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo18;
#define            gu8_dimming_set_eighteen                    U8DimmingPercentNo18.byte
#define            bit_0_3_amount_bar_2_1                      U8DimmingPercentNo18.nibble.b0_3
#define            bit_4_7_amount_bar_2_2                      U8DimmingPercentNo18.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo19;
#define            gu8_dimming_set_nineteen                    U8DimmingPercentNo19.byte
#define            bit_0_3_amount_bar_2_3                      U8DimmingPercentNo19.nibble.b0_3
#define            bit_4_7_amount_bar_continue                 U8DimmingPercentNo19.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo20;
#define            gu8_dimming_set_twenty                      U8DimmingPercentNo20.byte
#define            bit_0_3_recipe_ramen_txt                    U8DimmingPercentNo20.nibble.b0_3
#define            bit_4_7_recipe_drip_coffee_txt              U8DimmingPercentNo20.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo21;
#define            gu8_dimming_set_twenty_one                  U8DimmingPercentNo21.byte
#define            bit_0_3_MY_1_txt                            U8DimmingPercentNo21.nibble.b0_3
#define            bit_4_7_MY_2_txt                            U8DimmingPercentNo21.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo22;
#define            gu8_dimming_set_twenty_two                  U8DimmingPercentNo22.byte
#define            bit_0_3_ice_large_txt_not_use               U8DimmingPercentNo22.nibble.b0_3
#define            bit_4_7_ice_center_bar_not_use              U8DimmingPercentNo22.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo23;
#define            gu8_dimming_set_twenty_three                U8DimmingPercentNo23.byte
#define            bit_0_3_ice_small_txt_not_use               U8DimmingPercentNo23.nibble.b0_3
#define            bit_4_7_no_23_not_use                       U8DimmingPercentNo23.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo24;
#define            gu8_dimming_set_twenty_four                 U8DimmingPercentNo24.byte
#define            bit_0_3_cold_high_txt_not_use               U8DimmingPercentNo24.nibble.b0_3
#define            bit_4_7_cold_center_bar_not_use             U8DimmingPercentNo24.nibble.b4_7


extern TYPE_DIMMING       U8DimmingPercentNo25;
#define            gu8_dimming_set_twenty_five                 U8DimmingPercentNo25.byte
#define            bit_0_3_cold_low_txt_not_use                U8DimmingPercentNo25.nibble.b0_3
#define            bit_4_7_no_25_not_use                       U8DimmingPercentNo25.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo26;
#define            gu8_dimming_set_twenty_six                  U8DimmingPercentNo26.byte
#define            bit_0_3_ice_lock_icon_not_use               U8DimmingPercentNo26.nibble.b0_3
#define            bit_4_7_hot_lock_icon_not_use               U8DimmingPercentNo26.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo27;
#define            gu8_dimming_set_twenty_seven                U8DimmingPercentNo27.byte
#define            bit_0_3_comp_operation_dot_white            U8DimmingPercentNo27.nibble.b0_3
#define            bit_4_7_comp_operation_dor_blue             U8DimmingPercentNo27.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo28;
#define            gu8_dimming_set_twenty_eight                U8DimmingPercentNo28.byte
#define            bit_0_3_ice_extract                         U8DimmingPercentNo28.nibble.b0_3
#define            bit_4_7_water_extract                       U8DimmingPercentNo28.nibble.b4_7

extern TYPE_DIMMING       U8DimmingPercentNo29;
#define            gu8_dimming_set_twenty_nine                 U8DimmingPercentNo29.byte
#define            bit_0_3_welcome_led                         U8DimmingPercentNo29.nibble.b0_3
#define            bit_4_7_ice_blue_inner                      U8DimmingPercentNo29.nibble.b4_7
//////////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_DIMMING       U8DimmingPercentNo30;
#define            gu8_dimming_set_thirty                      U8DimmingPercentNo30.byte
#define            bit_0_3_no_30_not_use                       U8DimmingPercentNo30.nibble.b0_3
#define            bit_4_7_no_30_not_use                       U8DimmingPercentNo30.nibble.b4_7

//////////////////////////////////////////////////////////////////////////////////////////////////







/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

extern TYPE_WORD          U16AnimationDimmingW;
#define            gu16_animation_dimming                                     U16AnimationDimmingW.word
#define            u8AnimationDimming_L                                       U16AnimationDimmingW.byte[0]
#define            u8AnimationDimming_H                                       U16AnimationDimmingW.byte[1]
#define            Bit0_Animation_Dimming_Ice_Water_Select_State              U16AnimationDimmingW.Bit.b0
#define            Bit1_Animation_Dimming_Ice_Select_State                    U16AnimationDimmingW.Bit.b1
#define            Bit2_Animation_Dimming_Hot_Select_State                    U16AnimationDimmingW.Bit.b2
#define            Bit3_Animation_Dimming_Ambient_Select_State                U16AnimationDimmingW.Bit.b3
#define            Bit4_Animation_Dimming_Cold_Select_State                   U16AnimationDimmingW.Bit.b4
#define            Bit5_Animation_Dimming_Amount_Select_State                 U16AnimationDimmingW.Bit.b5
#define            Bit6_Animation_Dimming_Left_Seg_1_0_0_State                U16AnimationDimmingW.Bit.b6
#define            Bit7_Animation_Dimming_Left_Seg_0_2_0_State                U16AnimationDimmingW.Bit.b7
#define            Bit8_Animation_Dimming_Left_Seg_0_0_3_State                U16AnimationDimmingW.Bit.b8
#define            Bit9_Animation_Dimming_Right_Seg_1_0_0_0_State             U16AnimationDimmingW.Bit.b9
#define            Bit10_Animation_Dimming_Right_Seg_0_2_0_0_State            U16AnimationDimmingW.Bit.b10
#define            Bit11_Animation_Dimming_Right_Seg_0_0_3_0_State            U16AnimationDimmingW.Bit.b11
#define            Bit12_Animation_Dimming_Right_Seg_0_0_0_4_State            U16AnimationDimmingW.Bit.b12
#define            Bit13_Animation_Dimming_Ice_First_Icon_State               U16AnimationDimmingW.Bit.b13



extern TYPE_WORD          U16AnimationDimmingTwoW;
#define            gu16_animation_dimming_two                                 U16AnimationDimmingTwoW.word
#define            u8AnimationDimmingTwo_L                                    U16AnimationDimmingTwoW.byte[0]
#define            u8AnimationDimmingTwo_H                                    U16AnimationDimmingTwoW.byte[1]
#define            Bit0_Animation_Dimming_Ice_Full_Txt_State                  U16AnimationDimmingTwoW.Bit.b0
#define            Bit1_Animation_Dimming_UV_Ster_Txt_State                   U16AnimationDimmingTwoW.Bit.b1
#define            Bit2_Animation_Dimming_Hot_Ster_Txt_State                  U16AnimationDimmingTwoW.Bit.b2
#define            Bit3_Animation_Dimming_Sleep_Icon_State                    U16AnimationDimmingTwoW.Bit.b3
#define            Bit4_Animation_Dimming_Step_Txt_State_Not_Use              U16AnimationDimmingTwoW.Bit.b4
#define            Bit5_Animation_Dimming_Clock_Colon_Icon_State              U16AnimationDimmingTwoW.Bit.b5
#define            Bit6_Animation_Dimming_oC_Icon_State                       U16AnimationDimmingTwoW.Bit.b6
#define            Bit7_Animation_Dimming_Wifi_Icon_State                     U16AnimationDimmingTwoW.Bit.b7
#define            Bit8_Animation_Dimming_Sunny_Icon_State                    U16AnimationDimmingTwoW.Bit.b8
#define            Bit9_Animation_Dimming_Cloud_Icon_State                    U16AnimationDimmingTwoW.Bit.b9
#define            Bit10_Animation_Dimming_Rain_Icon_State                    U16AnimationDimmingTwoW.Bit.b10
#define            Bit11_Animation_Dimming_Percent_Icon_State                 U16AnimationDimmingTwoW.Bit.b11
#define            Bit12_Animation_Dimming_Liter_Txt_State_Not_Use            U16AnimationDimmingTwoW.Bit.b12
#define            Bit13_Animation_Dimming_ml_txt_State                       U16AnimationDimmingTwoW.Bit.b13


extern TYPE_BYTE          U8AnimationDimmingThreeB;
#define            gu8_animation_dimming_three                                U8AnimationDimmingThreeB.byte
#define            Bit0_Animation_Dimming_Temp_bar_1_1_State                  U8AnimationDimmingThreeB.Bit.b0
#define            Bit1_Animation_Dimming_Temp_bar_1_2_State                  U8AnimationDimmingThreeB.Bit.b1
#define            Bit2_Animation_Dimming_Temp_bar_1_3_State                  U8AnimationDimmingThreeB.Bit.b2
#define            Bit3_Animation_Dimming_Temp_bar_1_4_State                  U8AnimationDimmingThreeB.Bit.b3
#define            Bit4_Animation_Dimming_Amount_bar_2_1_State                U8AnimationDimmingThreeB.Bit.b4
#define            Bit5_Animation_Dimming_Amount_bar_2_2_State                U8AnimationDimmingThreeB.Bit.b5
#define            Bit6_Animation_Dimming_Amount_bar_2_3_State                U8AnimationDimmingThreeB.Bit.b6
#define            Bit7_Animation_Dimming_Amount_bar_Continue_State           U8AnimationDimmingThreeB.Bit.b7


extern TYPE_BYTE          U8AnimationDimmingFourB;
#define            gu8_animation_dimming_four                                 U8AnimationDimmingFourB.byte
#define            Bit0_Animation_Dimming_Recipe_Ramen_txt_State              U8AnimationDimmingFourB.Bit.b0
#define            Bit1_Animation_Dimming_Recipe_Drip_Coffee_txt_State        U8AnimationDimmingFourB.Bit.b1
#define            Bit2_Animation_Dimming_MY_1_txt_State                      U8AnimationDimmingFourB.Bit.b2
#define            Bit3_Animation_Dimming_MY_2_txt_State                      U8AnimationDimmingFourB.Bit.b3
#define            Bit4_Animation_Dimming_Ice_Lock_Icon_State_Not_Use         U8AnimationDimmingFourB.Bit.b4
#define            Bit5_Animation_Dimming_Hot_Lock_Icon_State_Not_Use         U8AnimationDimmingFourB.Bit.b5
#define            Bit6_Animation_Dimming_Comp_Operation_Dot_White_State      U8AnimationDimmingFourB.Bit.b6
#define            Bit7_Animation_Dimming_Comp_Operation_Dot_Blue_State       U8AnimationDimmingFourB.Bit.b7

extern TYPE_BYTE          U8AnimationDimmingFiveB;
#define            gu8_animation_dimming_five                                 U8AnimationDimmingFiveB.byte
#define            Bit0_Animation_Dimming_Ice_Large_txt_State_Not_Use         U8AnimationDimmingFiveB.Bit.b0
#define            Bit1_Animation_Dimming_Ice_Center_Bar_State_Not_Use        U8AnimationDimmingFiveB.Bit.b1
#define            Bit2_Animation_Dimming_Ice_Small_txt_State_Not_Use         U8AnimationDimmingFiveB.Bit.b2
#define            Bit3_Animation_Dimming_Cold_High_txt_State_Not_Use         U8AnimationDimmingFiveB.Bit.b3
#define            Bit4_Animation_Dimming_Cold_Center_Bar_State_Not_Use       U8AnimationDimmingFiveB.Bit.b4
#define            Bit5_Animation_Dimming_Cold_Low_txt_State_Not_Use          U8AnimationDimmingFiveB.Bit.b5


extern TYPE_BYTE          U8AnimationDimmingSixB;
#define            gu8_animation_dimming_six                                  U8AnimationDimmingSixB.byte
#define            Bit0_Animation_Dimming_Ice_Extract_State                   U8AnimationDimmingSixB.Bit.b0
#define            Bit1_Animation_Dimming_Water_Extract_State                 U8AnimationDimmingSixB.Bit.b1
#define            Bit2_Animation_Dimming_Welcome_Led_State                   U8AnimationDimmingSixB.Bit.b2









extern bit F_IceInit;
extern U16 gu16IceMakeTime;


extern bit F_WaterOut;
extern U16 gu16_extract_display_cnt;
extern U16 u16Efluent_Time;
extern U16 gu16Water_Extract_Timer;
extern bit F_IceOut;
extern bit F_FW_Version_Display_Mode;
extern bit bit_tank_reed_read_finish;
extern bit F_Tank_Cover_Input;
extern bit F_All_Lock;
extern ICE_STEP gu8IceStep;
extern bit F_Child_Lock;

extern bit bit_ice_tank_ster_start;






#endif
