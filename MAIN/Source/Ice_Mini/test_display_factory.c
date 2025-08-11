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
#include    "test_display_factory.h"

void diplay_test_start(void);
void Display_Test_Main(void);
void display_test_factory_input(void);
void display_test_error(void);
void display_test_factory_job(void);
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value);
void initial_ice_tray(void);
void make_test_mode_rgb_color( U8 mu8_color );
void make_test_mode_ice_inner_rgb_color( U8 mu8_color );
void make_test_mode_ice_outer_rgb_color( U8 mu8_color );

//void Set_Display_Test_KeyInput(DISPLAY_TEST_KEY_INPUT input);

#define SETTING_LED_ICE_SIZE 0x01
#define SETTING_LED_ICE_OFF  0x02
#define SETTING_LED_HOT_LOCK 0x04
#define SETTING_LED_FAST_ICE 0x08
#define SETTING_LED_COLD_TMP 0x10
#define SETTING_LED_SLEEPMOD 0x20
#define SETTING_LED_ICE_LOCK 0x40
#define SETTING_LED_ALL_LOCK 0x80
#define SETTING_LED_COLD_OFF 0x100

U8 key_press_ice;
U8 key_press_icewater;
U8 key_press_hot;
U8 key_press_pure;
U8 key_press_cold;
U8 key_press_amount;
U8 key_press_hidden_1;
U8 key_press_hidden_2;
U8 key_press_hidden_3;
U8 key_press_hidden_4;
U8 key_press_hidden_5;
U8 key_press_hidden_6;
U8 key_press_hidden_7;
U8 key_press_hidden_8;
U8 key_press_extract;

U8 display_test_flick_timer_100ms = 0;
U8 is_display_test_flick = 0;
U8 display_flick_state = 0;
U8 display_test_rgb_color = 0;

bit F_cds_detect;
U8 gu8_user_lcd_output;
U8 gu8_hot_lcd_output;
U8 gu8_room_lcd_output;
U8 gu8_cold_lcd_output;
U8 gu8_cup_lcd_output;

U8 gu8_initial_all_data;
U8 u8_water_select_testmode;
U8 u8_cup_select_testmode;

U8 gu8_hot_temp_off_timer;
U8 gu8_cup_level_off_timer;
U8 gu8_left_fnd_off_timer;
U8 gu8_right_fnd_off_timer;

U8 gu8_display_test_error;
bit bit_display_error_state;

bit bit_tank_cover_first_read;
bit bit_tank_cover_error;

bit bit_side_cover_first_read;
bit bit_side_cover_error;
U8 gu8_reed_first_read_timer;

U8 gu8_ice_feeder_test_on_timer;
U8 gu8_ice_feeder_test_off_timer;

U8 gu8_display_reed_test_step;
U8 gu8_display_reed_test_timer;

bit bit_display_test_neo_filter;
bit bit_display_test_ro_filter;
bit bit_display_test_ino_filter;


bit bit_display_test_neo_filter_old;
bit bit_display_test_ro_filter_old;
bit bit_display_test_ino_filter_old;


bit bit_display_test_filter_reed_error;


U8 gu8_water_color_change_timer;
U8 gu8_ice_color_change_timer;

U16 gu16_display_tds_in_max;
U16 gu16_display_tds_out_max;

U16 gu16_tds_test_timer;

DISPLAY_TEST_STEP Disp_test_step;

bit bit_uart_ice_test_finish;
bit bit_uart_ice_water_test_finish;
bit bit_uart_hot_test_finish;
bit bit_uart_ambient_test_finish;
bit bit_uart_cold_tst_finish;
bit bit_uart_amount_test_finish;
bit bit_uart_ice_size_test_finish;
bit bit_uart_ice_off_test_finish;
bit bit_uart_hot_lock_test_finish;
bit bit_uart_fast_ice_test_finish;
bit bit_uart_cold_temp_test_finish;
bit bit_uart_sleep_mode_test_finish;
bit bit_uart_ice_lock_test_finish;
bit bit_uart_all_lock_test_finish;
bit bit_uart_my_test_finish;        /* MY ����Ű �߰� 250213 @CH.PARK */
bit bit_uart_cold_off_finish;       /* �ü�OFF ����Ű �߰� 250213 @CH.PARK */

bit bit_uart_water_extract_test_finish;
bit bit_uart_ice_extract_test_finish;

bit bit_filter_cover_old;

U8 gu8_left_segment_off_timer;
U8 gu8_right_segment_off_timer;
U8 gu8_left_bar_off_timer;
U8 gu8_right_bar_off_timer;

bit bit_touch_test_finish;
bit bit_display_test_tank_cover_old;
bit bit_test_tank_cover_flag;
bit bit_display_test_tank_cover_error;
bit bit_display_test_filter_cover_old;
bit bit_test_filter_cover_flag;
bit bit_display_test_filter_cover_error;
bit bit_is_cover_checked;

U8 gu8_ice_water_select_display_timer;
U8 gu8_ice_select_display_timer;
U8 gu8_hot_select_display_timer;
U8 gu8_pure_select_display_timer;
U8 gu8_cold_select_display_timer;
U8 gu8_amount_select_display_timer;
U8 gu8_my_select_display_timer;
U8 gu8_ice_off_display_timer;
U8 gu8_ice_size_display_timer;
U8 gu8_hot_lock_display_timer;
U8 gu8_fast_ice_display_timer;
U8 gu8_cold_off_display_timer;

U8 gu8_water_rgb_test_step;
U8 gu8_ice_rgb_test_step;
extern void output_ice_tray_motor(void);
extern void play_melody_warning_197( void );
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void diplay_test_start(void)
{
    gu8_test_mode_timeout_1s = 0;
    
    play_voice_test_mode_151();

    off_all_control_led();
    UARTest_NO_LOAD_Set();
    // F_TrayMotorUP = 0;
    //F_TrayMotorDOWN = 0;

    /*..hui [17-12-28���� 10:54:12] ������ ǥ��..*/
    F_FW_Version_Display_Mode = CLEAR;
    gu8_led_version_step = 2;
    gu8_version_display_Timer = 0;

    u8FactoryTestMode = DISPLAY_TEST_MODE;

    /*..hui [19-11-5���� 5:57:28] EEPROM / RTC �ð� �ʱ�ȭ..*/
    gu8_initial_all_data = 1;

    /*..hui [19-12-19���� 1:26:46] ���� �µ����� ���� ON..*/
    pROOM_TH_POWER = SET;
    bit_adc_room_start = SET;
    /*..hui [19-12-19���� 1:27:21] �ü� �µ����� ���� ON..*/
    pCOLD_TH_POWER = SET;
    bit_adc_cold_start = SET;

    /*..hui [20-1-14���� 8:15:16] 12V ���� ON..*/
    Bit2_Uart_Test_Mode_State = SET;

    bit_uart_ice_test_finish = CLEAR;
    bit_uart_ice_water_test_finish = CLEAR;
    bit_uart_hot_test_finish = CLEAR;
    bit_uart_ambient_test_finish = CLEAR;
    bit_uart_cold_tst_finish = CLEAR;
    bit_uart_amount_test_finish = CLEAR;
    bit_uart_ice_size_test_finish = CLEAR;
    bit_uart_ice_off_test_finish = CLEAR;
    bit_uart_hot_lock_test_finish = CLEAR;
    bit_uart_fast_ice_test_finish = CLEAR;
    bit_uart_cold_temp_test_finish = CLEAR;
    bit_uart_sleep_mode_test_finish = CLEAR;
    bit_uart_my_test_finish = CLEAR;
    bit_uart_cold_off_finish = CLEAR;

    bit_uart_water_extract_test_finish = CLEAR;
    bit_uart_ice_lock_test_finish = CLEAR;
    bit_uart_all_lock_test_finish = CLEAR;

    bit_manual_test_start = CLEAR;

    ///all_breath_stop();

    bit_tank_cover_first_read = CLEAR;
    bit_side_cover_first_read = CLEAR;
    gu8_reed_first_read_timer = 0;

    bit_filter_reed_old = SET;
    bit_filter_cover_old = bit_filter_cover;

    gu8_display_reed_test_step = 0;
    bit_display_test_filter_reed_error = CLEAR;

    gu16_IceSelect_StepMotor = STEP_ANGLE_SELECT;
    gu16_Ice_Door_StepMotor = STEP_ANGLE_DOOR;

    bit_display_test_filter_cover_old = pREED_FILTER_COVER;
    bit_display_test_tank_cover_old = pREED_TANK_COVER_2;

    gu8_water_rgb_test_step = 0;
    gu8_ice_rgb_test_step = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 1
void Display_test_step_Handler(void)
{
	led_blink_timer();
	//all_breath_stop();
	all_duty_100_percent();

    if((Disp_test_step != DISPLAY_TEST_FINISH)
    && (Disp_test_step > DISPLAY_TEST_START)
    )
    {
        fnd_left_display_test();
        fnd_right_display_test();
    }
    else {  }


	switch(Disp_test_step)
	{
		case DISPLAY_TEST_NONE:
			if(F_FW_Version_Display_Mode != SET)
			{
				display_version();
			}
			else
			{
                Disp_test_step = DISPLAY_TEST_START;
                play_voice_test_mode_151();
			}
			break;

		case DISPLAY_TEST_START:
			fnd_left_out( FIXED_DISPLAY, DISPLAY_NUM_8, DISPLAY_NUM_8, DISPLAY_NUM_8);
			fnd_right_out( FIXED_DISPLAY, DISPLAY_NUM_8, DISPLAY_NUM_8, DISPLAY_NUM_8);
			
            gu8_front_left_led = 0xFF;
            gu8_front_left_led_2 = 0x3F;
			gu8_front_right_led = 0xFF;
			gu8_front_temp_setting_bar_led = 0x1F;
			gu8_front_amount_setting_bar_led = 0x1F;
			gu8_front_center_recipe_led = 0x3F;
			gu8_front_select_led = 0x7F;

			gu8_front_setting_led = 0x7F;
            gu8_front_setting_led_2 = 0x7F;
			gu8_front_under_text_led = 0xFF;
			gu8_front_under_icon_led = 0x7A;        // BLUE �Ⱦ�
			break;

		case DISPLAY_TEST_BTN1: // [������] Ŭ�� ��
			gu8_ice_water_select_display_timer++;

            if(gu8_ice_water_select_display_timer <= 2)
            {
                // ������
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = SET;
                Bit4_Front_Center_MY_2_Text = SET;
                Bit5_Front_Center_MY_3_Text = SET;

                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 4)
            {
                // ������
                Bit1_Front_Led_Ice_Water_Select = (CLEAR);

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = (CLEAR);
                Bit4_Front_Center_MY_2_Text = SET;
                Bit5_Front_Center_MY_3_Text = SET;

                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 6)
            {
                // ������
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = SET;

                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 8)
            {
                // ������
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;

                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
            }
            else if(gu8_ice_water_select_display_timer <= 10)
            {
                // ������
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;

                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
            }
            else
            {
                gu8_ice_water_select_display_timer = 10;

                // ������
                Bit1_Front_Led_Ice_Water_Select = CLEAR;

                // MY 1,2,3
                Bit3_Front_Center_MY_1_Text = CLEAR;
                Bit4_Front_Center_MY_2_Text = CLEAR;
                Bit5_Front_Center_MY_3_Text = CLEAR;
                // ����Ŀ��
                Bit0_Front_Left_Led_Eff_Faucet_Text = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN2: // [����] Ŭ�� ��
            gu8_ice_select_display_timer++;
            if(gu8_ice_select_display_timer <= 2)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = SET;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
                Bit1_Front_Center_Tea_Text = SET;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 4)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
                Bit1_Front_Center_Tea_Text = SET;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 6)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = SET;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 8)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 10)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 12)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
            }
            else if(gu8_ice_select_display_timer <= 14)
            {
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
            }
            else
            {
                gu8_ice_select_display_timer = 14;
                // ����
                Bit0_Front_Led_Ice_Select = CLEAR;
                
                // ���, �帳Ŀ��, ��
                Bit0_Front_Center_Recipe_Ramen_Text = CLEAR;
                Bit2_Front_Center_Recipe_Drip_Coffee_Text = CLEAR;
                Bit1_Front_Center_Tea_Text = CLEAR;
                
                // ��������
                Bit1_Front_Left_Led_Ice_Shortae_Text = CLEAR;

                // ���� �Ϲ�/����
                Bit6_Front_Under_Txt_Led_Ice_Normal = CLEAR;
                Bit7_Front_Under_Txt_Led_Ice_Piece = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN3: // [�¼�] Ŭ�� ��
            gu8_hot_select_display_timer++;
            if(gu8_hot_select_display_timer <= 2)
            {
                // �¼�
                Bit2_Front_Led_Hot_Select = CLEAR;
                
                // ��������, ����������
                Bit0_Front_Left_Led_Ice_Full_Text = SET;
                Bit4_Front_Left_Led_Sleep_Icon = SET;

                // �����Ŀ��
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 4)
            {
                // �¼�
                Bit2_Front_Led_Hot_Select = CLEAR;
                
                // ��������, ����������
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = SET;

                // �����Ŀ��
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 6)
            {
                // �¼�
                Bit2_Front_Led_Hot_Select = CLEAR;
                
                // ��������, ����������
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // �����Ŀ��
                Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
            }
            else if(gu8_hot_select_display_timer <= 8)
            {
                // �¼�
                Bit2_Front_Led_Hot_Select = CLEAR;
                
                // ��������, ����������
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // �����Ŀ��
                Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
            }
            else
            {
                gu8_hot_select_display_timer = 8;
                // �¼�
                Bit2_Front_Led_Hot_Select = CLEAR;
                
                // ��������, ����������
                Bit0_Front_Left_Led_Ice_Full_Text = CLEAR;
                Bit4_Front_Left_Led_Sleep_Icon = CLEAR;

                // �����Ŀ��
                Bit1_Front_Left_Led_Ice_Faucet_Text = CLEAR;
            }

            break;

		case DISPLAY_TEST_BTN4: // [����] Ŭ�� ��
            gu8_pure_select_display_timer++;
            if(gu8_pure_select_display_timer <= 2)
            {
                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = SET;
                Bit3_Front_Left_Led_Hot_Ster_Text = SET;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 4)
            {
                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = SET;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 6)
            {
                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 8)
            {
                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = SET;
            }
            else if(gu8_pure_select_display_timer <= 10)
            {
                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
            }
            else
            {
                gu8_pure_select_display_timer = 10;

                // ����
                Bit3_Front_Led_Ambient_Select = CLEAR;

                // UV���, ��»��
                Bit2_Front_Left_Led_UV_Ster_Text = CLEAR;
                Bit3_Front_Left_Led_Hot_Ster_Text = CLEAR;

                // : 
                Bit6_Front_Left_Led_Clock_Colon_Icon = CLEAR;

                // ����Ʈ����
                Bit2_Front_Left_Led_Ice_Tray_Text = CLEAR;
            }

			break;

		case DISPLAY_TEST_BTN5: // [�ü�] Ŭ�� ��
            gu8_cold_select_display_timer++;
            if(gu8_cold_select_display_timer <= 2)
            {
                // �ü�
                Bit4_Front_Led_Cold_Select = CLEAR;

                // �������� ������
                Bit4_Front_Led_Icon_Fast_Ice = SET;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
            }
            else if(gu8_cold_select_display_timer <= 4)
            {
                // �ü�
                Bit4_Front_Led_Cold_Select = CLEAR;

                // �������� ������
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
            }
            else if(gu8_cold_select_display_timer <= 6)
            {
                // �ü�
                Bit4_Front_Led_Cold_Select = CLEAR;

                // �������� ������
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
            }
            else
            {
                gu8_cold_select_display_timer = 6;
                // �ü�
                Bit4_Front_Led_Cold_Select = CLEAR;

                // �������� ������
                Bit4_Front_Led_Icon_Fast_Ice = CLEAR;

                // 'C
                Bit7_Front_Left_Led_Celcius_oC_Icon = CLEAR;
            }
			break;

		case DISPLAY_TEST_BTN6: // [�뷮] Ŭ�� ��
            gu8_amount_select_display_timer++;
            if(gu8_amount_select_display_timer <= 2)
            {
                // �뷮
                Bit5_Front_Led_Amount_Select = CLEAR;

                // ��,����,���
                Bit2_Front_Right_Led_Sunny_Icon = SET;
                Bit3_Front_Right_Led_Cloud_Icon = SET;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 4)
            {
                // �뷮
                Bit5_Front_Led_Amount_Select = CLEAR;

                // ��,����,���
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = SET;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 6)
            {
                // �뷮
                Bit5_Front_Led_Amount_Select = CLEAR;

                // ��,����,���
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = SET;
            }
            else if(gu8_amount_select_display_timer <= 8)
            {
                // �뷮
                Bit5_Front_Led_Amount_Select = CLEAR;

                // ��,����,���
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = CLEAR;
            }
            else
            {
                gu8_amount_select_display_timer = 8;
                // �뷮
                Bit5_Front_Led_Amount_Select = CLEAR;

                // ��,����,���
                Bit2_Front_Right_Led_Sunny_Icon = CLEAR;
                Bit3_Front_Right_Led_Cloud_Icon = CLEAR;
                Bit4_Front_Right_Led_Rain_Icon = CLEAR;
            }
			break;

        case DISPLAY_TEST_BTN6_2: // [MY] Ŭ�� ��
            gu8_my_select_display_timer++;
            if(gu8_my_select_display_timer <= 2)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // ���������
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = SET;

                // ���ͼ�ô
                Bit4_Front_Right_Led_Filter_Clean_Text = SET;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 4)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // ���������
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // ���ͼ�ô
                Bit4_Front_Right_Led_Filter_Clean_Text = SET;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 6)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // ���������
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // ���ͼ�ô
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = SET;
            }
            else if(gu8_my_select_display_timer <= 8)
            {
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // ���������
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // ���ͼ�ô
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = CLEAR;
            }
            else
            {
                gu8_my_select_display_timer = 8;
                // MY
                Bit6_Front_Led_My_Select = CLEAR;

                // ���������
                Bit3_Front_Left_Led_Ice_Storage_Box_Text = CLEAR;

                // ���ͼ�ô
                Bit4_Front_Right_Led_Filter_Clean_Text = CLEAR;

                // .
                Bit5_Front_Right_Seg_Dot_Text = CLEAR;
            }
            
			break;

		case DISPLAY_TEST_BTN7: // [����OFF] Ŭ�� ��
            gu8_ice_off_display_timer++;
            if(gu8_ice_off_display_timer <= 2)
            {
                // ����OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = SET;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
            }
            else if(gu8_ice_off_display_timer <= 4)
            {
                // ����OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
            }
            else if(gu8_ice_off_display_timer <= 6)
            {
                // ����OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }
            else
            {
                gu8_ice_off_display_timer = 6;
                // ����OFF
                Bit1_Front_Led_Ice_Off = CLEAR;

                // WIFI ICON
                Bit0_Front_Right_Led_Wifi_Icon_White = CLEAR;
                Bit1_Front_Right_Led_Wifi_Icon_Blue = CLEAR;
            }

            /* OUTLINE RED */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN8: // [�������] Ŭ�� ��
            gu8_ice_size_display_timer++;
            if(gu8_ice_size_display_timer <= 2)
            {
                // ����ũ��
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = SET;
                Bit6_Front_Right_Led_Liter_L_Icon = SET;
            }
            else if(gu8_ice_size_display_timer <= 4)
            {
                // ����ũ��
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = SET;

            }
            else if(gu8_ice_size_display_timer <= 6)
            {
                // ����ũ��
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
            }
            else
            {
                gu8_ice_size_display_timer = 6;
                // ����ũ��
                Bit0_Front_Led_Ice_Size = CLEAR;

                // L, ml
                Bit7_Front_Right_Led_ml_Icon = CLEAR;
                Bit6_Front_Right_Led_Liter_L_Icon = CLEAR;
            }

            /* OUTLINE GREEN */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

		case DISPLAY_TEST_BTN9: // [�¼����] Ŭ�� ��
            gu8_hot_lock_display_timer++;
            if(gu8_hot_lock_display_timer <= 2)
            {
                // �¼����
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // �¼���� ������
                Bit3_Front_Led_Icon_Led_Hot_Locker = SET;

                // %
                Bit5_Front_Right_Led_Percent_Icon = SET;

                // �ü� DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 4)
            {
                // �¼����
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // �¼���� ������
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = SET;

                // �ü� DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 6)
            {
                // �¼����
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // �¼���� ������
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // �ü� DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = SET;
            }
            else if(gu8_hot_lock_display_timer <= 8)
            {
                // �¼����
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // �¼���� ������
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // �ü� DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
            }
            else
            {
                gu8_hot_lock_display_timer = 8;
                // �¼����
                Bit2_Front_Led_Hot_Lock_Text = CLEAR;

                // �¼���� ������
                Bit3_Front_Led_Icon_Led_Hot_Locker = CLEAR;

                // %
                Bit5_Front_Right_Led_Percent_Icon = CLEAR;

                // �ü� DOT WHITE
                Bit5_Front_Led_Icon_Comp_Blue = CLEAR;
            }

            /* OUTLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN10: // [��������] Ŭ�� ��
			gu8_fast_ice_display_timer++;
            if(gu8_fast_ice_display_timer <= 2)
            {
                // ��������
                Bit3_Front_Led_Ice_First = CLEAR;

                // �ü� DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = SET;

                // �ܰ�
                Bit5_Front_Left_Led_Step_Text = SET;

                // WELCOME LED (����)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 4)
            {
                // ��������
                Bit3_Front_Led_Ice_First = CLEAR;

                // �ü� DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // �ܰ�
                Bit5_Front_Left_Led_Step_Text = SET;

                // WELCOME LED (����)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 6)
            {
                // ��������
                Bit3_Front_Led_Ice_First = CLEAR;

                // �ü� DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // �ܰ�
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (����)
                Bit6_Front_Under_Led_Welcome_2 = SET;
            }
            else if(gu8_fast_ice_display_timer <= 8)
            {
                // ��������
                Bit3_Front_Led_Ice_First = CLEAR;

                // �ü� DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // �ܰ�
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (����)
                Bit6_Front_Under_Led_Welcome_2 = CLEAR;
            }
            else
            {
                gu8_fast_ice_display_timer = 8;
                // ��������
                Bit3_Front_Led_Ice_First = CLEAR;

                // �ü� DOT BLUE
                Bit6_Front_Led_Icon_Comp_White = CLEAR;

                // �ܰ�
                Bit5_Front_Left_Led_Step_Text = CLEAR;

                // WELCOME LED (����)
                Bit6_Front_Under_Led_Welcome_2 = CLEAR;
            }

            /* INLINE RED */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN11: // [�ü�����] Ŭ�� ��
            gu8_left_bar_off_timer++;
            if(gu8_left_bar_off_timer <= 2)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;
            }
            else if(gu8_left_bar_off_timer <= 4)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;
                
            }
            else if(gu8_left_bar_off_timer <= 6)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;
                
            }
            else if(gu8_left_bar_off_timer <= 8)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;
                
            }
            else if(gu8_left_bar_off_timer <= 10)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;         
            }
            else if(gu8_left_bar_off_timer <= 12)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR; 

                Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 14)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 16)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;            
            }
            else if(gu8_left_bar_off_timer <= 18)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit4_Front_Led_Cold_Temp = CLEAR;
            }
            else if(gu8_left_bar_off_timer <= 20)
            {
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                Bit5_Front_Under_Led_Welcome = CLEAR;
            }
            else
            {
                gu8_left_bar_off_timer = 20;
                
                Bit0_Front_Led_Temp_Setting_Bar_1_1 = CLEAR;
                Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
                Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
                Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
                Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;

                // �ü��µ�
                Bit4_Front_Led_Cold_Temp = CLEAR;

                // �� | ��
                Bit3_Front_Under_Txt_Led_Cold_High = CLEAR;
                Bit4_Front_Under_Txt_Led_Cold_Center_Bar = CLEAR;
                Bit5_Front_Under_Txt_Led_Cold_Low = CLEAR;

                // WELCOME LED (����)
                Bit5_Front_Under_Led_Welcome = CLEAR;
            }

            /* INLINE GREEN */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN12: // [�ü�OFF] Ŭ�� ��
            gu8_cold_off_display_timer++;
            if(gu8_cold_off_display_timer <= 2)
            {
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = SET;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = SET;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 4)
            {
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = SET;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 6)
            {
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;
            }
            else if(gu8_cold_off_display_timer <= 8)
            {
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = SET;

            }
            else if(gu8_cold_off_display_timer <= 10)
            {
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
            }
            else
            {
                gu8_cold_off_display_timer = 10;
                // �ü�OFF
                Bit6_Front_Led_Cold_Off = CLEAR;

                // ������� ������
                Bit2_Front_Led_Icon_Led_Ice_Locker = CLEAR;

                // �� | ��
                Bit0_Front_Under_Txt_Led_Ice_Large = CLEAR;
                Bit1_Front_Under_Txt_Led_Ice_Center_bar = CLEAR;
                Bit2_Front_Under_Txt_Led_Ice_Small = CLEAR;
            }

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN13: // [��ħ���] Ŭ�� ��
            // �뷮�� 5��
            gu8_right_bar_off_timer++;
            if(gu8_right_bar_off_timer <= 2)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            }
            else if(gu8_right_bar_off_timer <= 4)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                
            }
            else if(gu8_right_bar_off_timer <= 6)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                
            }
            else if(gu8_right_bar_off_timer <= 8)
            {
                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
                
            }
            else if(gu8_right_bar_off_timer <= 10)
            {
                Bit5_Front_Led_Sleep_Mode_Text = SET;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;    
            }
            else if(gu8_right_bar_off_timer <= 12)
            {
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;       
            }
            else
            {
                gu8_right_bar_off_timer = 12;

                // ��ħ���
                Bit5_Front_Led_Sleep_Mode_Text = CLEAR;

                Bit0_Front_Led_Amount_Setting_Bar_2_1 = CLEAR;
                Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
                Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
                Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
                Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
            }

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            /* RED */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

		case DISPLAY_TEST_BTN14: // [�������] Ŭ�� ��
            gu8_uart_setting_ice_lock_test_input = 1;
			Bit0_Front_Led_Ice_Lock = CLEAR;

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            
            /* GREEN */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

        case DISPLAY_TEST_BTN15: // [��ü���] Ŭ�� �� 
			Bit1_Front_Led_All_Lock = CLEAR;
            gu8_uart_setting_all_lock_test_input = 1;

            /* INLINE BLUE */
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            /* BLUE */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			break;

        case DISPLAY_TEST_BTN_ICE_EXTRACT: // [���� ���� ��ư] Ŭ�� ��
            display_test_flick_timer_100ms++;

            Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
            Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;

            if( display_test_flick_timer_100ms <= 3 )
            {
                // ���� �ܺ� white LED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }
            else if( display_test_flick_timer_100ms <= 6 )
            {
                // ���� ���� �ܺ� RED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 9 )
            {
                // ���� ���� �ܺ� GREEN only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 12 )
            {
                // ���� ���� �ܺ� BLUE only   
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 15 )
            {
                // ���� ���� ���� RED only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 18 )
            {
                // ���� ���� ���� GREEN only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 21 )
            {
                // ���� ���� ���� BLUE only
                Bit3_Front_Under_Ice_Outer_White_Extract = SET;
                Bit1_Front_Under_Ice_Inner_White_Extract = SET;

                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            }
            else if( display_test_flick_timer_100ms <= 24 )
            {
                Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }
            else
            {
                display_test_flick_timer_100ms = 24;
                Bit3_Front_Under_Ice_Outer_White_Extract = CLEAR;
                Bit1_Front_Under_Ice_Inner_White_Extract = CLEAR;
                make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
                set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, EXTRACT__DIMMING__40_PERCETN );
            }  

            /* WHITE */
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
            break;

		case DISPLAY_TEST_BTN_EXTRACT: // [�� �����ư] Ŭ�� ��
            display_test_flick_timer_100ms++;
			if(display_test_flick_timer_100ms <= 3) /* 0.1 ~ 1�� ���� */
			{
                /* WHITE */
                Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
			}
            else if(display_test_flick_timer_100ms <= 6) /* 1 ~ 2�� ���� */
			{
                /* RED */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			}
            else if(display_test_flick_timer_100ms <= 9)  /* 2 ~ 3�� ���� */
			{
                /* GREEN */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
			}
            else if(display_test_flick_timer_100ms <= 12)
            {
                /* BLUE */
				Bit4_Front_Under_Water_White_Extract = SET;
                make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            }
            else if(display_test_flick_timer_100ms <= 15)
            {
                Bit4_Front_Under_Water_White_Extract = CLEAR;
                make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );

                display_test_flick_timer_100ms = 0;
                Disp_test_step = DISPLAY_TEST_FINISH;
            }
            else
            {
                display_test_flick_timer_100ms = 0;
                Disp_test_step = DISPLAY_TEST_FINISH;
                
                /* �������ϱ� ������ ����Ŀ�� ü�Ῡ�� ĸ�� [�ڿ��� ��û] 250722 CH.PARK */
                bit_filter_cover = pREED_FILTER_COVER;
                bit_filter_cover_old = bit_filter_cover;
                bit_is_cover_checked = (bit)CLEAR;
            }
			break;

		case DISPLAY_TEST_FINISH: // �˻�Ϸ� -> ����

            bit_filter_cover = pREED_FILTER_COVER;

            /* ����Ŀ�� ���彺��ġ [���� <-> �̰���] �������� �Ǵ� 250314 CH.PARK */
            if(bit_filter_cover != bit_filter_cover_old)
            {
                bit_filter_cover_old = bit_filter_cover;
                play_voice_test_mode_151();
                bit_is_cover_checked = (bit)TRUE;
            }
            else {  }

			if( (gu8_front_left_led == 0x00)
            && (gu8_front_left_led_2 == 0x00)
			&& (gu8_front_right_led == 0x00)
			&& (gu8_front_temp_setting_bar_led == 0x00)
			&& (gu8_front_amount_setting_bar_led == 0x00)
			&& (gu8_front_center_recipe_led == 0x00)
			&& (gu8_front_select_led == 0x00)
			&& (gu8_front_setting_led == 0x00)
            && (gu8_front_setting_led_2 == 0x00)
			&& (gu8_front_under_text_led == 0x00)
			&& (gu8_front_under_icon_led == 0x00)
			&& (is_display_test_flick == CLEAR)
            && (bit_is_cover_checked != (bit)CLEAR)
            )
			{
				is_display_test_flick = SET;
				display_test_rgb_color = TEST_MODE_RGB_OFF;
				gu8_rgb_red_on_time = 0;
				gu8_rgb_green_on_time = 0;
				gu8_rgb_blue_on_time = 0;
				gu8_rgb_pwm_period = 0;
			}

			if(is_display_test_flick == SET)
			{
                display_test_flick_timer_100ms++;
				if(display_test_flick_timer_100ms >= 5)
				{
					display_test_flick_timer_100ms = 0;
					display_flick_state ^= SET;

					if(display_flick_state == SET)
					{
						on_all_control_led();
                        make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );    
                        make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
                    }
					else
					{
						off_all_control_led();
                        make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
                        make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
					}
				}

			}

			break;

		default:
			break;


	}
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Test_Main(void)
{
    /////all_breath_stop();
    all_duty_100_percent();

    if( F_FW_Version_Display_Mode != SET )
    {
        display_version();
    }
    else
    {
        display_test_error();           // ��������
        display_test_factory_input();
        display_test_factory_job();

        fnd_left_display_test();
        fnd_right_display_test();

        /*..hui [23-6-30���� 1:22:01] ���÷��� �˻��Ҷ��� DC FAN�� �׽� ON�ϵ���..*/
        pDC_FAN = SET;
    }

    initial_all_data();
    initial_ice_tray();
    motor_ice_door_output();
    motor_ice_select_output();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_input(void)
{
    if( gu8_front_temp_fnd_hundred == 0
    && gu8_front_temp_fnd_ten == 0
    && gu8_front_temp_fnd_one == 0

    && gu8_front_amount_fnd_hundred == 0
    && gu8_front_amount_fnd_ten == 0
    && gu8_front_amount_fnd_one == 0

    && gu8_front_left_led == 0
    && gu8_front_right_led == 0
    && gu8_front_temp_setting_bar_led == 0
    && gu8_front_amount_setting_bar_led == 0
    && gu8_front_center_recipe_led == 0
    && gu8_front_select_led == 0
    && gu8_front_setting_led == 0
    && gu8_front_under_text_led == 0
    && gu8_front_under_icon_led == 0

    // && gu8_front_rcv_filter_reed_data == 1
    && gu8_uart_tray_initial_step == 3
    && gu8_display_test_error == 0 )
    {
        F_cds_detect = 1;
    }
    else{}

    if( bit_uart_ice_water_test_finish == SET
    && bit_uart_ice_test_finish == SET
    && bit_uart_hot_test_finish == SET
    && bit_uart_ambient_test_finish == SET
    && bit_uart_cold_tst_finish == SET
    && bit_uart_amount_test_finish == SET
    && bit_uart_ice_off_test_finish == SET
    && bit_uart_ice_size_test_finish == SET
    && bit_uart_hot_lock_test_finish == SET
    && bit_uart_fast_ice_test_finish == SET
    && bit_uart_cold_temp_test_finish == SET
    && bit_uart_sleep_mode_test_finish == SET
    && bit_uart_ice_lock_test_finish == SET
    && bit_uart_all_lock_test_finish == SET
    && bit_uart_my_test_finish == SET
    && bit_uart_cold_off_finish == SET
    && bit_uart_water_extract_test_finish == SET 
    && bit_uart_ice_extract_test_finish == SET )
    {
        bit_touch_test_finish = SET;

        /* �����ư ���� ������ �� �˻� �̻������� ���� ���� 250718 CH.PARK */
        gu8_ice_color_change_timer = 23;
        gu8_water_color_change_timer = 14;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_error(void)
{
    if(gu16_AD_Result_Cold <= TEMP_SENSOR_SHORT || gu16_AD_Result_Cold >= TEMP_SENSOR_OPEN)                     /* �ü� �µ����� ���� */
    {
        gu8_display_test_error = 1;
    }
    else if(gu16_AD_Result_Hot_Heater <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Heater >= TEMP_SENSOR_OPEN)    /* �¼� ���� �µ����� ���� */
    {
        gu8_display_test_error = 2;
    }
    else if(gu16_AD_Result_Hot_Out <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_Out >= TEMP_SENSOR_OPEN)          /* �¼� ���� �µ����� ���� */
    {
        gu8_display_test_error = 3;
    }
    else if(gu16_AD_Result_Hot_In <= TEMP_SENSOR_SHORT || gu16_AD_Result_Hot_In >= TEMP_SENSOR_OPEN)            /* �¼� �Լ� �µ����� ���� */
    {
        gu8_display_test_error = 4;
    }
    else if(gu16_AD_Result_Room <= TEMP_SENSOR_SHORT || gu16_AD_Result_Room >= TEMP_SENSOR_OPEN)                /* ���� �µ����� ���� */
    {
        gu8_display_test_error = 5;
    }
    else if(gu16_AD_Result_Amb <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb >= TEMP_SENSOR_OPEN)                  /* �ܱ� �µ����� ���� */
    {
        gu8_display_test_error = 6;
    }
    else if(gu16_AD_Result_Amb_Side <= TEMP_SENSOR_SHORT || gu16_AD_Result_Amb_Side >= TEMP_SENSOR_OPEN)
    {
       gu8_display_test_error = 7;
    }
    else if(gu16_AD_Result_Eva_First <= TEMP_SENSOR_SHORT || gu16_AD_Result_Eva_First >= TEMP_SENSOR_OPEN)
    {
       gu8_display_test_error = 8;
    }
    else if(pLEVEL_ICE_DRAIN_LOW == SET)  /* �巹�� ������ ���� ���� */
    {
        gu8_display_test_error = 9;
    }
    else if(pLEVEL_ICE_DRAIN_HIGH == SET) /* �巹�� ������ ���� ���� */
    {
        gu8_display_test_error = 10;
    }
    else if(gu16ADLeakage > 615)          /* �������� ���� */
    {
        gu8_display_test_error = 11;
    }
    else if(pREED_FILTER == SET )         /* ���� ��ü�� */
    {
        gu8_display_test_error = 14;
    }
    else
    {
        if( bit_touch_test_finish == SET )
        {
            if( bit_display_test_filter_cover_error == SET )     // ����Ŀ��
            {
                gu8_display_test_error = 12;
            }
            else if( bit_display_test_tank_cover_error == SET )            // ������ũ Ŀ��
            {
                gu8_display_test_error = 13;
            }
            else
            {
                gu8_display_test_error = 0;
            }
        }
        else
        {
            gu8_display_test_error = 0;
        }
    }

    if( gu8_display_test_error != 0 )
    {
        if( bit_display_error_state == CLEAR )
        {
            bit_display_error_state = SET;
            play_melody_warning_197();
        }
        else{}
    }
    else
    {
        bit_display_error_state = CLEAR;

    }

    gu8_reed_first_read_timer++;

    if( gu8_reed_first_read_timer >= 30 )
    {
        gu8_reed_first_read_timer = 30;
        bit_tank_cover_first_read = SET;
        bit_side_cover_first_read = SET;
    }
    else{}

    // ��ü�� -> ü�� ���°� �Ǿ�߸� ���� ����
    if(bit_display_test_filter_cover_old != pREED_FILTER_COVER)
    {
        bit_display_test_filter_cover_old = pREED_FILTER_COVER;
        bit_test_filter_cover_flag = SET;

        if(pREED_FILTER_COVER == CLEAR)
        {
            bit_display_test_filter_cover_error = CLEAR;
        }
        else
        {
            bit_display_test_filter_cover_error = SET;
        }
    }
    else
    {
        if(bit_test_filter_cover_flag == CLEAR)
        {
            bit_display_test_filter_cover_error = SET;
        }
        else {  }
    }

    if(bit_display_test_tank_cover_old != pREED_TANK_COVER_2)
    {
        bit_display_test_tank_cover_old = pREED_TANK_COVER_2;
        bit_test_tank_cover_flag = SET;

        if(pREED_TANK_COVER_2 == CLEAR)
        {
            bit_display_test_tank_cover_error = CLEAR;
        }
        else
        {
            bit_display_test_tank_cover_error = SET;
        }
    }
    else
    {
        if(bit_test_tank_cover_flag == CLEAR)
        {
            bit_display_test_tank_cover_error = SET;
        }
        else {  }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_factory_job(void)
{
    led_blink_timer();

    if( gu8_display_test_error != 0 )
    {
        gu8_front_amount_fnd_hundred = 0;
        gu8_front_amount_fnd_ten = 0;
        gu8_front_amount_fnd_one = 0;

        gu8_front_left_led = 0;
        gu8_front_left_led_2 = 0;
        gu8_front_right_led = 0;
        gu8_front_temp_setting_bar_led = 0;
        gu8_front_amount_setting_bar_led = 0;
        gu8_front_center_recipe_led = 0;
        
        gu8_front_select_led = 0;
        gu8_front_setting_led = 0;
        gu8_front_setting_led_2 = 0;
        gu8_front_under_text_led = 0;
        gu8_front_under_icon_led = 0;

        return;
    }
    else{}

    /* [������] Ű �Է� */
    if(gu8_uart_ice_water_test_input == 1)
    {
        // ������
        Bit1_Front_Led_Ice_Water_Select = (F_cds_detect & F_Wink_500ms);

        // MY 1,2,3
        Bit3_Front_Center_MY_1_Text = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Center_MY_2_Text = (F_cds_detect & F_Wink_500ms);
        Bit5_Front_Center_MY_3_Text = (F_cds_detect & F_Wink_500ms);

        // ����Ŀ��
        Bit0_Front_Left_Led_Eff_Faucet_Text = (F_cds_detect & F_Wink_500ms);
        bit_uart_ice_water_test_finish = SET;
    }
    else
    {
        if( bit_uart_ice_water_test_finish == CLEAR )
        {
            // ������
            Bit1_Front_Led_Ice_Water_Select = SET;

            // MY 1,2,3
			Bit3_Front_Center_MY_1_Text = SET;
            Bit4_Front_Center_MY_2_Text = SET;
            Bit5_Front_Center_MY_3_Text = SET;

            // ����Ŀ��
            Bit0_Front_Left_Led_Eff_Faucet_Text = SET;
        }
        else
        {
            gu8_uart_ice_water_test_input = 1;
        }
    }

    /* [����] Ű �Է� */
    if(gu8_uart_ice_test_input == 1)
    {       
        // ����
        Bit0_Front_Led_Ice_Select = (F_cds_detect & F_Wink_500ms);
        
        // ���, �帳Ŀ��, ��
        Bit0_Front_Center_Recipe_Ramen_Text = (F_cds_detect & F_Wink_500ms);
        Bit2_Front_Center_Recipe_Drip_Coffee_Text = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Center_Tea_Text = (F_cds_detect & F_Wink_500ms);
        
        // ��������
        Bit1_Front_Left_Led_Ice_Shortae_Text = (F_cds_detect & F_Wink_500ms);

        // ���� �Ϲ�/����
        Bit6_Front_Under_Txt_Led_Ice_Normal = (F_cds_detect & F_Wink_500ms);
        Bit7_Front_Under_Txt_Led_Ice_Piece = (F_cds_detect & F_Wink_500ms);
        bit_uart_ice_test_finish = SET;
    }
    else
    {
        if( bit_uart_ice_test_finish == CLEAR )
        {
            // ����
            Bit0_Front_Led_Ice_Select = SET;
			
            // ���, �帳Ŀ��, ��
            Bit0_Front_Center_Recipe_Ramen_Text = SET;
            Bit2_Front_Center_Recipe_Drip_Coffee_Text = SET;
            Bit1_Front_Center_Tea_Text = SET;
            
            // ��������
            Bit1_Front_Left_Led_Ice_Shortae_Text = SET;

            // ���� �Ϲ�/����
            Bit6_Front_Under_Txt_Led_Ice_Normal = SET;
            Bit7_Front_Under_Txt_Led_Ice_Piece = SET;
        }
        else
        {
            gu8_uart_ice_test_input = 1;
        }
    }

    /* [�¼�] Ű �Է� */
    if(gu8_uart_hot_test_input == 1)
    {
        // �¼�
        Bit2_Front_Led_Hot_Select = (F_cds_detect & F_Wink_500ms);
        
        // ��������, ����������
        Bit0_Front_Left_Led_Ice_Full_Text = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Left_Led_Sleep_Icon = (F_cds_detect & F_Wink_500ms);

        // �����Ŀ��
        Bit1_Front_Left_Led_Ice_Faucet_Text = (F_cds_detect & F_Wink_500ms);
        bit_uart_hot_test_finish = SET;
    }
    else
    {
        if( bit_uart_hot_test_finish == CLEAR )
        {
            // �¼�
			Bit2_Front_Led_Hot_Select = SET;
            
            // ��������, ����������
            Bit0_Front_Left_Led_Ice_Full_Text = SET;
            Bit4_Front_Left_Led_Sleep_Icon = SET;

            // �����Ŀ��
            Bit1_Front_Left_Led_Ice_Faucet_Text = SET;
        }
        else
        {
            gu8_uart_hot_test_input = 1;
        }
    }

    /* [����] Ű �Է� */
    if(gu8_uart_purify_test_input == 1)
    {
        // ����
        Bit3_Front_Led_Ambient_Select = (F_cds_detect & F_Wink_500ms);

        // UV���, ��»��
        Bit2_Front_Left_Led_UV_Ster_Text = (F_cds_detect & F_Wink_500ms);
        Bit3_Front_Left_Led_Hot_Ster_Text = (F_cds_detect & F_Wink_500ms);

        // : 
        Bit6_Front_Left_Led_Clock_Colon_Icon = (F_cds_detect & F_Wink_500ms);

        // ����Ʈ����
        Bit2_Front_Left_Led_Ice_Tray_Text = (F_cds_detect & F_Wink_500ms);

        bit_uart_ambient_test_finish = SET;
    }
    else
    {
        if( bit_uart_ambient_test_finish == CLEAR )
        {
            // ����
			Bit3_Front_Led_Ambient_Select = SET;

            // UV���, ��»��
            Bit2_Front_Left_Led_UV_Ster_Text = SET;
            Bit3_Front_Left_Led_Hot_Ster_Text = SET;

            // : 
            Bit6_Front_Left_Led_Clock_Colon_Icon = SET;

            // ����Ʈ����
            Bit2_Front_Left_Led_Ice_Tray_Text = SET;
        }
        else
        {
            gu8_uart_purify_test_input = 1;
        }
    }

    /* [�ü�] Ű �Է� */
    if(gu8_uart_cold_test_input == 1)
    {
        // �ü�
        Bit4_Front_Led_Cold_Select = (F_cds_detect & F_Wink_500ms);

        // �������� ������
        Bit4_Front_Led_Icon_Fast_Ice = (F_cds_detect & F_Wink_500ms);

        // 'C
        Bit7_Front_Left_Led_Celcius_oC_Icon = (F_cds_detect & F_Wink_500ms);
        bit_uart_cold_tst_finish = SET;
    }
    else
    {
        if( bit_uart_cold_tst_finish == CLEAR )
        {
            // �ü�
			Bit4_Front_Led_Cold_Select = SET;

            // �������� ������
            Bit4_Front_Led_Icon_Fast_Ice = SET;

            // 'C
            Bit7_Front_Left_Led_Celcius_oC_Icon = SET;
        }
        else
        {
            gu8_uart_cold_test_input = 1;
        }
    }

    /* [�뷮] Ű �Է� */
    if(gu8_uart_amount_test_input == 1)
    {
        // �뷮
        Bit5_Front_Led_Amount_Select = (F_cds_detect & F_Wink_500ms);

        // ��,����,���
        Bit2_Front_Right_Led_Sunny_Icon = (F_cds_detect & F_Wink_500ms);
        Bit3_Front_Right_Led_Cloud_Icon = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Right_Led_Rain_Icon = (F_cds_detect & F_Wink_500ms);
        bit_uart_amount_test_finish = SET;
    }
    else
    {
        if( bit_uart_amount_test_finish == CLEAR )
        {
            // �뷮
			Bit5_Front_Led_Amount_Select = SET;

            // ��,����,���
            Bit2_Front_Right_Led_Sunny_Icon = SET;
            Bit3_Front_Right_Led_Cloud_Icon = SET;
            Bit4_Front_Right_Led_Rain_Icon = SET;
        }
        else
        {

            gu8_uart_amount_test_input = 1;
        }
    }

    /* [MY] �Է� ��  */
    if(gu8_uart_setting_my_test_input == 1)
    {
        // MY
        Bit6_Front_Led_My_Select = (F_cds_detect & F_Wink_500ms);

        // ���������
        Bit3_Front_Left_Led_Ice_Storage_Box_Text = (F_cds_detect & F_Wink_500ms);

        // ���ͼ�ô
        Bit4_Front_Right_Led_Filter_Clean_Text = (F_cds_detect & F_Wink_500ms);

        // .
        Bit5_Front_Right_Seg_Dot_Text = (F_cds_detect & F_Wink_500ms);

        bit_uart_my_test_finish = SET;
    }
    else
    {
        if(bit_uart_my_test_finish == CLEAR)
        {
            // MY
			Bit6_Front_Led_My_Select = SET;

            // ���������
            Bit3_Front_Left_Led_Ice_Storage_Box_Text = SET;

            // ���ͼ�ô
            Bit4_Front_Right_Led_Filter_Clean_Text = SET;

            // .
            Bit5_Front_Right_Seg_Dot_Text = SET;
        }
        else
        {
            gu8_uart_setting_my_test_input = 1;
        }
    }

    /* [����OFF] Ű �Է� */
    if(gu8_uart_setting_ice_off_test_input == 1)
    {
        // ����OFF
        Bit1_Front_Led_Ice_Off = (F_cds_detect & F_Wink_500ms);

        // WIFI ICON
        Bit0_Front_Right_Led_Wifi_Icon_White = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Right_Led_Wifi_Icon_Blue = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_off_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 1;
            bit_uart_ice_off_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_ice_off_test_finish == CLEAR )
        {
            // ����OFF
            Bit1_Front_Led_Ice_Off = SET;

            // WIFI ICON
            Bit0_Front_Right_Led_Wifi_Icon_White = SET;
            Bit1_Front_Right_Led_Wifi_Icon_Blue = SET;
        }
        else
        {
            gu8_uart_setting_ice_off_test_input = 1;
        }
    }

    /* [�������] Ű�Է� */
    if(gu8_uart_setting_ice_size_test_input == 1)
    {
        // ����ũ��
        Bit0_Front_Led_Ice_Size = (F_cds_detect & F_Wink_500ms);

        // L, ml
        Bit7_Front_Right_Led_ml_Icon = (F_cds_detect & F_Wink_500ms);
        Bit6_Front_Right_Led_Liter_L_Icon = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_size_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 2;
            bit_uart_ice_size_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_ice_size_test_finish == CLEAR )
        {
            // ����ũ��
			Bit0_Front_Led_Ice_Size = SET;

            // L, ml
            Bit7_Front_Right_Led_ml_Icon = SET;
            Bit6_Front_Right_Led_Liter_L_Icon = SET;
        }
        else
        {
            gu8_uart_setting_ice_size_test_input = 1;
        }
    }

    /* [�¼����] Ű �Է� */
    if(gu8_uart_setting_hot_lock_test_input == 1)
    {      
        // �¼����
        Bit2_Front_Led_Hot_Lock_Text = (F_cds_detect & F_Wink_500ms);

        // �¼���� ������
        Bit3_Front_Led_Icon_Led_Hot_Locker = (F_cds_detect & F_Wink_500ms);

        // %
        Bit5_Front_Right_Led_Percent_Icon = (F_cds_detect & F_Wink_500ms);

        // �ü� DOT WHITE
        Bit5_Front_Led_Icon_Comp_Blue = (F_cds_detect & F_Wink_500ms);
        
        if(bit_uart_hot_lock_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 3;
            bit_uart_hot_lock_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_hot_lock_test_finish == CLEAR )
        {
            // �¼����
            Bit2_Front_Led_Hot_Lock_Text = SET;

            // �¼���� ������
            Bit3_Front_Led_Icon_Led_Hot_Locker = SET;

            // %
            Bit5_Front_Right_Led_Percent_Icon = SET;

            // �ü� DOT WHITE
            Bit5_Front_Led_Icon_Comp_Blue = SET;
        }
        else
        {
            gu8_uart_setting_hot_lock_test_input = 1;
        }
    }

    /* [��������] Ű �Է� */
    if(gu8_uart_setting_fast_ice_test_input == 1)
    {
        // ��������
        Bit3_Front_Led_Ice_First = (F_cds_detect & F_Wink_500ms);

        // �ü� DOT BLUE
        Bit6_Front_Led_Icon_Comp_White = (F_cds_detect & F_Wink_500ms);

        // �ܰ�
        Bit5_Front_Left_Led_Step_Text = (F_cds_detect & F_Wink_500ms);

        // WELCOME LED (����)
        Bit6_Front_Under_Led_Welcome_2 = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_fast_ice_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 4;
            bit_uart_fast_ice_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_fast_ice_test_finish == CLEAR )
        {
            // ��������
			Bit3_Front_Led_Ice_First = SET;

            // �ü� DOT BLUE
            Bit6_Front_Led_Icon_Comp_White = SET;

            // �ܰ�
            Bit5_Front_Left_Led_Step_Text = SET;

            // WELCOME LED (����)
            Bit6_Front_Under_Led_Welcome_2 = SET;
        }
        else
        {
            gu8_uart_setting_fast_ice_test_input = 1;
        }
    }

    /* [�ü�����] Ű �Է� */
    if(gu8_uart_setting_cold_temp_test_input == 1)
    {
        // �µ��� 5��
        gu8_hot_temp_off_timer++;
        if(gu8_hot_temp_off_timer <= 3)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 6)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 9)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else if(gu8_hot_temp_off_timer <= 12)
        {
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = CLEAR;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = CLEAR;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = CLEAR;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = CLEAR;
        }
        else
        {
            gu8_hot_temp_off_timer = 13;
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = (F_cds_detect & F_Wink_500ms);
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = (F_cds_detect & F_Wink_500ms);
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = (F_cds_detect & F_Wink_500ms);
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = (F_cds_detect & F_Wink_500ms);
        }

        // �ü��µ�
        Bit4_Front_Led_Cold_Temp = (F_cds_detect & F_Wink_500ms);

        // �� | ��
        Bit3_Front_Under_Txt_Led_Cold_High = (F_cds_detect & F_Wink_500ms);
        Bit4_Front_Under_Txt_Led_Cold_Center_Bar = (F_cds_detect & F_Wink_500ms);
        Bit5_Front_Under_Txt_Led_Cold_Low = (F_cds_detect & F_Wink_500ms);

        // WELCOME LED (����)
        Bit5_Front_Under_Led_Welcome = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_cold_temp_test_finish == CLEAR)
        {
            gu8_ice_rgb_test_step = 5;
            bit_uart_cold_temp_test_finish = SET;
        }
    }
    else
    {
        if( bit_uart_cold_temp_test_finish == CLEAR )
        {
            // �ü��µ�
			Bit4_Front_Led_Cold_Temp = SET;

            // �� | ��
			Bit3_Front_Under_Txt_Led_Cold_High = SET;
			Bit4_Front_Under_Txt_Led_Cold_Center_Bar = SET;
			Bit5_Front_Under_Txt_Led_Cold_Low = SET;

            // �µ��� 5��
            Bit0_Front_Led_Temp_Setting_Bar_1_1 = SET;
            Bit1_Front_Led_Temp_Setting_Bar_1_2 = SET;
            Bit2_Front_Led_Temp_Setting_Bar_1_3 = SET;
            Bit3_Front_Led_Temp_Setting_Bar_1_4 = SET;
            Bit4_Front_Led_Temp_Setting_Bar_1_5 = SET;

            // WELCOME LED (����)
            Bit5_Front_Under_Led_Welcome = SET;

            gu8_hot_temp_off_timer = 0;
        }
        else
        {
            gu8_uart_setting_cold_temp_test_input = 1;
        }
    }

    /* [�ü�OFF] Ű �Է� */
    if(gu8_uart_setting_cold_off_input == 1)
    {
        // �ü�OFF
        Bit6_Front_Led_Cold_Off = (F_cds_detect & F_Wink_500ms);

        // ������� ������
        Bit2_Front_Led_Icon_Led_Ice_Locker = (F_cds_detect & F_Wink_500ms);

        // �� | ��
        Bit0_Front_Under_Txt_Led_Ice_Large = (F_cds_detect & F_Wink_500ms);
        Bit1_Front_Under_Txt_Led_Ice_Center_bar = (F_cds_detect & F_Wink_500ms);
        Bit2_Front_Under_Txt_Led_Ice_Small = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_cold_off_finish == CLEAR)
        {
            bit_uart_cold_off_finish = SET;
            gu8_ice_rgb_test_step = 6;
        }
    }
    else
    {
        if(bit_uart_cold_off_finish == CLEAR)
        {
            // �ü�OFF
            Bit6_Front_Led_Cold_Off = SET;

            // ������� ������
            Bit2_Front_Led_Icon_Led_Ice_Locker = SET;

            // �� | ��
            Bit0_Front_Under_Txt_Led_Ice_Large = SET;
            Bit1_Front_Under_Txt_Led_Ice_Center_bar = SET;
            Bit2_Front_Under_Txt_Led_Ice_Small = SET;
        }
        else
        {
            gu8_uart_setting_cold_off_input = 1;
        }
    }

    /* [��ħ���] Ű �Է� */
    if(gu8_uart_setting_sleep_mode_test_input == 1)
    {
        // ��ħ���
        Bit5_Front_Led_Sleep_Mode_Text = (F_cds_detect & F_Wink_500ms);

        gu8_cup_level_off_timer++;
        if(gu8_cup_level_off_timer <= 3)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 6)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 9)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else if(gu8_cup_level_off_timer <= 12)
        {
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = CLEAR;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = CLEAR;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = CLEAR;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = CLEAR;
        }
        else
        {
            gu8_cup_level_off_timer = 13;
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = (F_cds_detect & F_Wink_500ms);
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = (F_cds_detect & F_Wink_500ms);
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = (F_cds_detect & F_Wink_500ms);
            Bit4_Front_Led_Amount_Setting_Bar_Continue = (F_cds_detect & F_Wink_500ms);
        }
        
        if(bit_uart_sleep_mode_test_finish == CLEAR)
        {
            bit_uart_sleep_mode_test_finish = SET;
            gu8_water_rgb_test_step = 1;
        }
    }
    else
    {
        if( bit_uart_sleep_mode_test_finish == CLEAR )
        {
            // ��ħ���
			Bit5_Front_Led_Sleep_Mode_Text = SET;

            // �뷮�� 5��
            Bit0_Front_Led_Amount_Setting_Bar_2_1 = SET;
            Bit1_Front_Led_Amount_Setting_Bar_2_2 = SET;
            Bit2_Front_Led_Amount_Setting_Bar_2_3 = SET;
            Bit3_Front_Led_Amount_Setting_Bar_2_4 = SET;
            Bit4_Front_Led_Amount_Setting_Bar_Continue = SET;
            
            gu8_cup_level_off_timer = 0;

        }
        else
        {
            gu8_uart_setting_sleep_mode_test_input = 1;
        }
    }

    /* [�������] Ű �Է� */
    if(gu8_uart_setting_ice_lock_test_input == 1)
    {
        Bit0_Front_Led_Ice_Lock = (F_cds_detect & F_Wink_500ms);

        if(bit_uart_ice_lock_test_finish == CLEAR)
        {
            bit_uart_ice_lock_test_finish = SET;
            gu8_water_rgb_test_step = 2;
        }
    }
    else
    {
        if( bit_uart_ice_lock_test_finish == CLEAR )
        {
            Bit0_Front_Led_Ice_Lock = SET;
        }
        else
        {
            gu8_uart_setting_ice_lock_test_input = 1;
        }
    }

    /* [��ü���] Ű �Է� */
    if(gu8_uart_setting_all_lock_test_input == 1)
    {
        Bit1_Front_Led_All_Lock = (F_cds_detect & F_Wink_500ms);
    
        if(bit_uart_all_lock_test_finish == CLEAR)
        {
            bit_uart_all_lock_test_finish = SET;
            gu8_water_rgb_test_step = 3;
        }
    }
    else
    {
        if( bit_uart_all_lock_test_finish == CLEAR )
        {
            Bit1_Front_Led_All_Lock = SET;
        }
        else
        {
            gu8_uart_setting_all_lock_test_input = 1;
        }
    }

    /* [�ÿ��� ����] Ű */
    if(gu8_water_ext_test_input == 1)
    {
        gu8_water_color_change_timer++;

        if( gu8_water_color_change_timer <= 3 )
        {
            gu8_water_rgb_test_step = 0;
        }
        else if( gu8_water_color_change_timer <= 6 )
        {
            gu8_water_rgb_test_step = 1;
        }
        else if( gu8_water_color_change_timer <= 9 )
        {
            gu8_water_rgb_test_step = 2;
        }
        else if( gu8_water_color_change_timer <= 12 )
        {
            gu8_water_rgb_test_step = 3;
        }
        else if( gu8_water_color_change_timer <= 15 )
        {
            // gu8_water_color_change_timer = 15;
            gu8_water_rgb_test_step = 4;
        }
        else
        {
            // gu8_water_color_change_timer = 15;
            // gu8_water_rgb_test_step = 0;
        }
    }
    else
    {
        gu8_water_color_change_timer = 0;
    }

    /* [���� ����] Ű �Է� */
    if(gu8_ice_ext_test_input == 1)
    {
        gu8_ice_color_change_timer++;

        if( gu8_ice_color_change_timer <= 3 )
        {
            gu8_ice_rgb_test_step = 0;
        }
        else if( gu8_ice_color_change_timer <= 6 )
        {
            gu8_ice_rgb_test_step = 1;
        }
        else if( gu8_ice_color_change_timer <= 9 )
        {
            gu8_ice_rgb_test_step = 2;
        }
        else if( gu8_ice_color_change_timer <= 12 )
        {
            gu8_ice_rgb_test_step = 3;
        }
        else if( gu8_ice_color_change_timer <= 15 )
        {
            gu8_ice_rgb_test_step = 4;
        }
        else if( gu8_ice_color_change_timer <= 18 )
        {
            gu8_ice_rgb_test_step = 5;
        }
        else if( gu8_ice_color_change_timer <= 21 )
        {
            gu8_ice_rgb_test_step = 6;
        }
        else if( gu8_ice_color_change_timer <= 24 )
        {
            // gu8_ice_color_change_timer = 24;
            gu8_ice_rgb_test_step = 7;
        }
        else
        {
            // gu8_ice_color_change_timer = 24;
            // gu8_ice_rgb_test_step = 0;
        }  
    }
    else
    {
        gu8_ice_color_change_timer = 0;
    }

    switch (gu8_ice_rgb_test_step)
    {
        case 0:
            // ���� �ܺ� white LED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__40_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__40_PERCENT );
            break;

        case 1:
            // ���� ���� �ܺ� RED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 2:
            // ���� ���� �ܺ� GREEN only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 3:
            // ���� ���� �ܺ� BLUE only   
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 4:
            // ���� ���� ���� RED only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_RED );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 5:
            // ���� ���� ���� GREEN only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );
            break;

        case 6:
            // ���� ���� ���� BLUE only
            Bit3_Front_Under_Ice_Outer_White_Extract = SET;
            Bit1_Front_Under_Ice_Inner_White_Extract = SET;

            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__0_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__0_PERCENT );

            break;
        
        case 7:
            // �Ϸ�
            bit_uart_ice_extract_test_finish = SET;
            Bit3_Front_Under_Ice_Outer_White_Extract = (F_cds_detect & F_Wink_500ms);
            Bit1_Front_Under_Ice_Inner_White_Extract = (F_cds_detect & F_Wink_500ms);
            make_test_mode_ice_inner_rgb_color( TEST_MODE_RGB_OFF );
            make_test_mode_ice_outer_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT, DIIMMING__40_PERCENT );
            set_duty_percent( DIMMING__PERCENT_ICE_EXTRACT_INNER, DIIMMING__40_PERCENT );
            break;

        default:
        
            break;
    }

    switch (gu8_water_rgb_test_step)
    {
        case 0:
            // white LED only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__40_PERCENT );

            break;

        case 1:
            // �ÿ��� ���� RED only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_RED );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );
            break;

        case 2:
            // �ÿ��� ���� GREEN only      
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_GREEN );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );        
            break;

        case 3:
            // �ÿ��� ���� BLUE only
            Bit4_Front_Under_Water_White_Extract = SET;
            make_test_mode_rgb_color( TEST_MODE_RGB_COLOR_BLUE );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, DIIMMING__0_PERCENT );              
            break;

        case 4:
            // �Ϸ�
            bit_uart_water_extract_test_finish = SET;

            Bit4_Front_Under_Water_White_Extract = (F_cds_detect & F_Wink_500ms);
            make_test_mode_rgb_color( TEST_MODE_RGB_OFF );
            set_duty_percent( DIMMING__PERCENT_WATER_EXTRACT, EXTRACT__DIMMING__40_PERCETN );
            break;

        default:
        
            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

#ifdef _DISPLAY_FCT_SUB_LINE_
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value)
{
	switch(u32key_input_value)
	{
        case KEY_ICE_WATER_SELECT:
			if(Disp_test_step == DISPLAY_TEST_START)
			{
				Disp_test_step++;
				play_voice_test_mode_151();
			}
			break;
		
        case KEY_ICE_SELECT:
            if(Disp_test_step == DISPLAY_TEST_BTN1)
			{
                if(gu8_ice_water_select_display_timer  >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}			
			break;

		case KEY_HOT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN2)
			{
                if(gu8_ice_select_display_timer >= 14)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_AMBIENT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN3)
			{
                if(gu8_hot_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();	
                }
			}
			break;

		case KEY_COLD_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN4)
			{
                if(gu8_pure_select_display_timer >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_AMOUNT_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN5)
			{
                if(gu8_cold_select_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_MY_SELECT:
			if(Disp_test_step == DISPLAY_TEST_BTN6)
			{
                if(gu8_amount_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;


		case KEY_SETTING_ICE_OFF:
			if(Disp_test_step == DISPLAY_TEST_BTN6_2)
			{
                if(gu8_my_select_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
            break;

		case KEY_SETTING_ICE_SIZE:
			if(Disp_test_step == DISPLAY_TEST_BTN7)
			{
                if(gu8_ice_off_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_HOT_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN8)
			{
				if(gu8_ice_size_display_timer >= 6)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ICE_FIRST:
			if(Disp_test_step == DISPLAY_TEST_BTN9)
			{
                if(gu8_hot_lock_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_COLD_TEMP:
			if(Disp_test_step == DISPLAY_TEST_BTN10)
			{
                if(gu8_fast_ice_display_timer >= 8)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_COLD_WATER_OFF:
			if(Disp_test_step == DISPLAY_TEST_BTN11)
			{
                if(gu8_left_bar_off_timer >= 20)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_SLEEP_MODE:
			if(Disp_test_step == DISPLAY_TEST_BTN12)
			{
				if(gu8_cold_off_display_timer >= 10)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ICE_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN13)
			{
                if(gu8_right_bar_off_timer >= 12)
                {
                    Disp_test_step++;
                    play_voice_test_mode_151();
                }
			}
			break;

		case KEY_SETTING_ALL_LOCK:
			if(Disp_test_step == DISPLAY_TEST_BTN14)
			{
				Disp_test_step++;
				play_voice_test_mode_151();
			}
			break;
	}
}
#else
void Display_Test_Mode_Key_Short_Input(U32 u32key_input_value)
{
    play_voice_test_mode_151();

    /* �����ɷ��� ���� �Է°� ó�� ���� 250320 CH.PARK */
    if( gu8_display_test_error == 0 )
    {
        switch(u32key_input_value)
        {
            case KEY_ICE_SELECT:                        /* [����] Ű */
                gu8_uart_ice_test_input++;

                if(gu8_uart_ice_test_input >= 2)
                {
                    gu8_uart_ice_test_input = 0;
                }
                else{}

                break;

            case KEY_ICE_WATER_SELECT:                  /* [������] Ű */
                gu8_uart_ice_water_test_input++;

                if(gu8_uart_ice_water_test_input >= 2)
                {
                    gu8_uart_ice_water_test_input = 0;
                }
                else{}

                break;

            case KEY_HOT_SELECT:                        /* [�¼�] Ű */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_hot_test_input++;

                        if(gu8_uart_hot_test_input >= 2)
                        {
                            gu8_uart_hot_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = HOT_WATER_SELECT;
                        bit_uart_hot_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_hot_test_input++;

                    if(gu8_uart_hot_test_input >= 2)
                    {
                        gu8_uart_hot_test_input = 0;
                    }
                    else{}
                }

                break;

            case KEY_AMBIENT_SELECT:                        /* [����] Ű */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_purify_test_input++;

                        if(gu8_uart_purify_test_input >= 2)
                        {
                            gu8_uart_purify_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = PURE_WATER_SELECT;
                        bit_uart_purify_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_purify_test_input++;

                    if(gu8_uart_purify_test_input >= 2)
                    {
                        gu8_uart_purify_test_input = 0;
                    }
                    else{}
                }

                break;

            case KEY_COLD_SELECT:                           /* [�ü�] Ű */

                if( u8FactoryTestMode == UART_TEST_MODE  )
                {
                    if( gu8_water_ext_test_input == 0 )
                    {
                        #if 1
                        gu8_uart_cold_test_input++;

                        if(gu8_uart_cold_test_input >= 2)
                        {
                            gu8_uart_cold_test_input = 0;
                        }
                        else{}
                        #endif

                        gu8_test_water_out = COLD_WATER_SELECT;
                        bit_uart_cold_extract_finish = CLEAR;
                    }
                    else
                    {
                        ///play_voice_beep_warning();
                    }
                }
                else
                {
                    gu8_uart_cold_test_input++;

                    if(gu8_uart_cold_test_input >= 2)
                    {
                        gu8_uart_cold_test_input = 0;
                    }
                    else{}
                }


                break;

            case KEY_AMOUNT_SELECT:                         /* [�뷮] Ű */

                gu8_uart_amount_test_input++;

                if(gu8_uart_amount_test_input >= 2)
                {
                    gu8_uart_amount_test_input = 0;
                }
                else{}

                break;
            
            case KEY_MY_SELECT:                                    /* [MY] Ű */
                gu8_uart_setting_my_test_input++;

                if(gu8_uart_setting_my_test_input >= 2)
                {
                    gu8_uart_setting_my_test_input = 0;
                }
                else {  }
                break;

            case KEY_SETTING_ICE_SIZE:                      /* [�������] Ű */
                gu8_uart_setting_ice_size_test_input++;

                if(gu8_uart_setting_ice_size_test_input >= 2)
                {
                    gu8_uart_setting_ice_size_test_input = 0;
                }
                else{}

                break;
            
            case KEY_SETTING_ICE_OFF:                       /* [����OFF] Ű */

                gu8_uart_setting_ice_off_test_input++;

                if(gu8_uart_setting_ice_off_test_input >= 2)
                {
                    gu8_uart_setting_ice_off_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_HOT_LOCK:                      /* [�¼����] Ű */

                gu8_uart_setting_hot_lock_test_input++;

                if(gu8_uart_setting_hot_lock_test_input >= 2)
                {
                    gu8_uart_setting_hot_lock_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ICE_FIRST:                     /* [��������] Ű */

                gu8_uart_setting_fast_ice_test_input++;

                if(gu8_uart_setting_fast_ice_test_input >= 2)
                {
                    gu8_uart_setting_fast_ice_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_COLD_TEMP:                    /* [�ü�����] Ű */

                gu8_uart_setting_cold_temp_test_input++;

                if(gu8_uart_setting_cold_temp_test_input >= 2)
                {
                    gu8_uart_setting_cold_temp_test_input = 0;
                }
                else{}

                break;

            case KEY_COLD_WATER_OFF:                        /* [�ü�OFF] Ű */
                gu8_uart_setting_cold_off_input++;

                if(gu8_uart_setting_cold_off_input >= 2)
                {
                    gu8_uart_setting_cold_off_input = 0;
                }
                else {  }
                break;

            case KEY_SETTING_SLEEP_MODE:                    /* [��ħ���] */              

                gu8_uart_setting_sleep_mode_test_input++;

                if(gu8_uart_setting_sleep_mode_test_input >= 2)
                {
                    gu8_uart_setting_sleep_mode_test_input = 0;
                }
                else{}

                break;
                    
            case KEY_SETTING_ICE_LOCK:                      /* [�������] Ű */

                gu8_uart_setting_ice_lock_test_input++;

                if(gu8_uart_setting_ice_lock_test_input >= 2)
                {
                    gu8_uart_setting_ice_lock_test_input = 0;
                }
                else{}

                break;

            case KEY_SETTING_ALL_LOCK:                      /* [��ü���] Ű */

                gu8_uart_setting_all_lock_test_input++;

                if(gu8_uart_setting_all_lock_test_input >= 2)
                {
                    gu8_uart_setting_all_lock_test_input = 0;
                }
                else{}

                break;
        }
    }
    else
    {

    }
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_tray(void)
{
    /*..hui [25-4-22���� 4:28:51] žĿ�� �����ִµ��� ���Ӱ���..*/
    if( pREED_TANK_COVER_2 == SET )
    {
        gu8_ice_feeder_test_on_timer++;
        gu8_ice_feeder_test_off_timer = 0;

        if( gu8_ice_feeder_test_on_timer >= 20 )
        {
            gu8_ice_feeder_test_on_timer = 20;
            /*..hui [23-6-30���� 11:10:15] ��ȸ�� -> ��ȸ������ ����.. �������..*/
            pMOTOR_ICE_OUT_CW = CLEAR;
            pMOTOR_ICE_OUT_CCW = SET;
        }
        else{}
    }
    else
    {
        gu8_ice_feeder_test_off_timer++;
        gu8_ice_feeder_test_on_timer = 0;

        if( gu8_ice_feeder_test_off_timer >= 20 )
        {
            gu8_ice_feeder_test_off_timer = 20;
            pMOTOR_ICE_OUT_CW = CLEAR;
            pMOTOR_ICE_OUT_CCW = CLEAR;
        }
        else{}
    }

    input_ice_tray_micro_sw();

    /*..hui [19-11-8���� 4:58:12] ���̽�Ʈ���� �˻� �Ϸ�ñ��� ���..*/
    if( gu8_uart_tray_initial_step >= 3 )
    {
        F_TrayMotorUP = 0;
        F_TrayMotorDOWN = 0;
        return;
    }
    else{}

    if( gu8_uart_tray_initial_step > 0 )
    {
        gu16_uart_tray_initial_max_timer++;

        if(gu16_uart_tray_initial_max_timer >= 900)
        {
            gu16_uart_tray_initial_max_timer = 0;
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
            gu8_uart_tray_initial_step = 3;
        }
        else{}
    }
    else{}

    output_ice_tray_motor();

    switch( gu8_uart_tray_initial_step )
    {
        case 0:

            gu16_uart_tray_initial_timer++;

            if(gu16_uart_tray_initial_timer >= 10)
            {
                gu16_uart_tray_initial_timer = 0;
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 1:

            up_tray_motor();    // ���ζ��ΰ˻�
            gu8_uart_tray_initial_step++;

            break;

        case 2:

            if(F_TrayMotorUP != SET && gu8IceTrayLEV == ICE_TRAY_POSITION_ICE_MAKING)
            {
                gu8_uart_tray_initial_step++;
            }
            else{}

            break;

        case 3:

            /*..hui [19-10-28���� 2:40:33] ���⼭ ���..*/
            F_TrayMotorUP = 0;
            F_TrayMotorDOWN = 0;
            gu8_uart_tray_initial = 0;
            //gu8_uart_tray_finish = 1;

            break;

        default:

            gu8_uart_tray_initial_step = 0;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22���� 5:01:06] ���常 40%..*/
        gu8_rgb_red_on_time = 16;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 40;
        gu8_rgb_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22���� 5:02:02] �׸� 40%, ��� 80%..*/
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 16;
        gu8_rgb_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_red_on_time = 0;
        gu8_rgb_green_on_time = 0;
        gu8_rgb_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_ice_inner_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22���� 5:01:06] ���常 40%..*/
        gu8_rgb_ice_inner_red_on_time = 16;
        gu8_rgb_ice_inner_green_on_time = 0;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 40;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22���� 5:02:02] �׸� 40%, ��� 80%..*/
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 16;
        gu8_rgb_ice_inner_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_ice_inner_red_on_time = 0;
        gu8_rgb_ice_inner_green_on_time = 0;
        gu8_rgb_ice_inner_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_test_mode_ice_outer_rgb_color( U8 mu8_color )
{
    /*..hui [24-1-10���� 1:09:30] �ֱ� 10ms�� ����.. ��ȣ RO CT ����..*/
    gu8_rgb_pwm_period = 40;

    if( mu8_color == TEST_MODE_RGB_COLOR_RED )
    {
        /*..hui [24-2-22���� 5:01:06] ���常 40%..*/
        gu8_rgb_ice_outer_red_on_time = 16;
        gu8_rgb_ice_outer_green_on_time = 0;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_GREEN )
    {
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 40;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
    else if( mu8_color == TEST_MODE_RGB_COLOR_BLUE )
    {
        /*..hui [24-2-22���� 5:02:02] �׸� 40%, ��� 80%..*/
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 16;
        gu8_rgb_ice_outer_blue_on_time = 32;
    }
    else
    {
        gu8_rgb_ice_outer_red_on_time = 0;
        gu8_rgb_ice_outer_green_on_time = 0;
        gu8_rgb_ice_outer_blue_on_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_door(void)
{
    
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void initial_ice_select(void)
{

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

