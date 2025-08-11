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
#include    "M9_Front_Communication.h"


void Front_Communication(void);
void front_rx_communication(void);
void convert_received_data_asc_to_dec(void);
U8 calculate_checksum(void);
void apply_receive_data(U8 *mu8_rx_data);
void front_tx_communication(void);
void make_front_tx_data(void);
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length);
void Uart_ISR0_Front_Panel_Rx(void);
void Uart_ISR0_Front_Panel_Tx ( void );
void front_transmit_error_check(void);
void front_transmit_start(void);









/*..hui [18-8-9���� 1:10:24] �ƽ�Ű�� ���� ������ ����..*/
//U8 gu8_front_rx_buffer_temp[FRONT_RX_BUFFER_SIZE];
/*..hui [18-8-9���� 1:10:38] �ƽ�Ű�� 10������ ��ȯ�� ���� ������ ����..*/
U8 gu8_front_rx_buffer[FRONT_RX_BUFFER_SIZE];

//U8 gu8_front_tx_buffer_temp[FRONT_TX_BUFFER_SIZE];

U8 gu8_front_tx_buffer[FRONT_TX_BUFFER_SIZE];
U8 gu8_front_rx_receive_cnt;
U8 gu8_front_tx_count;

BIT F_Front_Rx_Complete;
BIT F_Front_Tx_Request;

U32 gu32_front_rcv_select_key_data;
U8 gu8_front_rcv_extract_key_data;
U8 gu8_front_rcv_filter_reed_data;

U8 gu8_front_rcv_service_input_data;

U8 gu8_front_tx_retry_cnt;

U8 asdfasdf[9];
I8 fedfwefew[9];


U8 gu8_cs_error_cnt;
U8 gu8_busy_error_cnt;
U8 gu8_comm_error_cnt;
U8 gu8_front_comm_error_timer;

U8 gu8_front_version;
U8 gu8_front_model;

bit bit_voice_reset;


U8 gu8_play;
U8 gu8_volume;
U16 gu16_address;
U8 gu8_hk16_bright;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Front_Communication(void)
{
    front_rx_communication();
    front_tx_communication();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_rx_communication(void)
{
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;

    if(F_Front_Rx_Complete == SET)
    {
        /*convert_received_data_asc_to_dec();*/

        mu16_cal_crc = (U16)Rx_CRC_CCITT(gu8_front_rx_buffer, FRONT_CRC_CALC_RANGE);

        mu8_crc_high = (U8)HighByte(mu16_cal_crc);
        mu8_crc_low = (U8)LowByte(mu16_cal_crc);

        if((gu8_front_rx_buffer[FRONT_CRC_HIGH_ROCATION] == mu8_crc_high)
        && (gu8_front_rx_buffer[FRONT_CRC_LOW_ROCATION] == mu8_crc_low)
        )
        {
            switch( gu8_front_rx_buffer[DEVICE_ID_ROCATION] )
            {
                case PROTOCOL_DEVICE_ID_MAIN:

                    F_Front_Tx_Request = SET;
                    apply_receive_data(gu8_front_rx_buffer);

                    break;

                default :

                    break;
            }
        }
        else
        {
            gu8_cs_error_cnt++;
        }

        F_Front_Rx_Complete = CLEAR;
        gu8_front_comm_error_timer = 0;

        if( bit_voice_reset == SET )
        {
            bit_voice_reset = CLEAR;
            /////Initial_Voice_Next_Lab();
        }
        else{}
    }
    else
    {
        gu8_front_comm_error_timer++;

        if( gu8_front_comm_error_timer >= 30 )
        {
            /*..hui [24-1-9���� 10:11:54] 3�� �̻� ����̻� �߻� �� ���� ���͵Ǹ� ���̽�IC ����..*/
            bit_voice_reset = SET;
            /////Port_VOICE_RESET = CLEAR;
        }
        else{}

        /*..hui [19-12-13���� 7:01:15] 5�� ���� ��� �ȵɰ�� Ű �Է� �ʱ�ȭ..*/
        if(gu8_front_comm_error_timer >= 100)
        {
            gu8_front_comm_error_timer = 100;
            /*..hui [19-7-17���� 7:51:24] ��� ���� �߻� �� Ű �Է� �ʱ�ȭ..*/
            gu8_Key_Water_Extract = 0;
            gu8_Key_Ice_Extract = 0;
            gu32_Key_Input = 0;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_received_data_asc_to_dec(void)
{
#if 0
    gu8_front_rx_buffer[0] = gu8_front_rx_buffer_temp[0];
    gu8_front_rx_buffer[1] = gu8_front_rx_buffer_temp[1];
    gu8_front_rx_buffer[2] = gu8_front_rx_buffer_temp[2];

    gu8_front_rx_buffer[3] = AscToHex(gu8_front_rx_buffer_temp[3], gu8_front_rx_buffer_temp[4]);
    gu8_front_rx_buffer[4] = AscToHex(gu8_front_rx_buffer_temp[5], gu8_front_rx_buffer_temp[6]);
    gu8_front_rx_buffer[5] = AscToHex(gu8_front_rx_buffer_temp[7], gu8_front_rx_buffer_temp[8]);
    gu8_front_rx_buffer[6] = AscToHex(gu8_front_rx_buffer_temp[9], gu8_front_rx_buffer_temp[10]);

    gu8_front_rx_buffer[7] = gu8_front_rx_buffer_temp[11];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 calculate_checksum(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U8 mu8_cal_cs = 0;

    for(mu8_temp = 0; mu8_temp < 6; mu8_temp++ )
    {
        mu8_cal_cs += gu8_front_rx_buffer[mu8_temp];
    }

    return mu8_cal_cs;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void apply_receive_data(U8 *mu8_rx_data)
{
    U8 mu8_voice = 0;

    #if 0
    gu32_front_rcv_select_key_data = (U16)((mu8_rx_data[3] * 256) + mu8_rx_data[4]);

    gu8_Key_Water_Extract = (U8)((gu32_front_rcv_select_key_data >> 3) & 0x01);
    gu8_Key_Ice_Extract  = (U8)((gu32_front_rcv_select_key_data >> 2) & 0x01);
    gu32_Key_Input = (U16)(gu32_front_rcv_select_key_data & 0xFFF0);

    gu8_front_version = mu8_rx_data[5];
    #endif

    gu8_front_model = mu8_rx_data[2];
    gu8_front_version = mu8_rx_data[3];
    /* Ű �߰��� ���� �߰� 250210 @CH.PARK */
    gu32_front_rcv_select_key_data = (U32)((U32)((U32)mu8_rx_data[4] * 0x00010000) + (U32)((U32)mu8_rx_data[5] * 0x00000100) + mu8_rx_data[6]);
    gu32_front_rcv_select_key_data = (U32)(gu32_front_rcv_select_key_data & 0x0007FFFF);
    // gu8_front_rcv_filter_reed_data = mu8_rx_data[7];

    mu8_voice = mu8_rx_data[8];

    if((F_PlayVoice == SET)
    && (gu8_play == SET)
    )
    {
        if( mu8_voice == CLEAR )
        {
            F_PlayVoice = CLEAR;
            gu8_play = CLEAR;
        }
        else{}
    }
    else{}

    gu8_Key_Water_Extract = (U8)((gu32_front_rcv_select_key_data >> 1) & 0x01);           // �� ���� ��ư
    gu8_Key_Ice_Extract  = (U8)((U32)(gu32_front_rcv_select_key_data >> 15) & 0x02);      // ���� �� ������ ���� ��ư 
    gu32_Key_Input = (U32)(gu32_front_rcv_select_key_data & 0xFFFEFFFE);                  // �� �����ư�� ������ ��� ��ư �Է�
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_tx_communication(void)
{
    front_transmit_error_check();
    front_transmit_start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_start(void)
{
    U8 u8Uart1_Busy_Chk = 0;

    if( (U16)((SSR00) & (U16)0x0040) == (U16)0x0040)
    {
        u8Uart1_Busy_Chk = SET;
    }
    else
    {
        u8Uart1_Busy_Chk = CLEAR;
    }

    /* ���� ó���� ����. �ʿ��ϸ� �߰��ϱ� */
    // if(u8Uart1_Busy_Chk == CLEAR)
    // {
    //     if(F_Front_Tx_Request == SET)
    //     {
    //         make_front_tx_data();
    //         TXD0 = gu8_front_tx_buffer[0];
    //         gu8_front_tx_count = 1;
    //     }
    //     else{}
    // }
    // else
    // {
    //     gu8_busy_error_cnt++;
    // }

    if(1)
    {
        if(F_Front_Tx_Request == SET)
        {
            make_front_tx_data();
            TXD0 = gu8_front_tx_buffer[0];
            gu8_front_tx_count = 1;
        }
        else{}
    }
    else
    {
        gu8_busy_error_cnt++;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_transmit_error_check(void)
{
    if(F_Front_Tx_Request == CLEAR)
    {
        gu8_front_tx_retry_cnt++;

        if(gu8_front_tx_retry_cnt >= TX_RETRY_COUNT)
        {
            gu8_comm_error_cnt++;
            gu8_front_tx_retry_cnt = 0;
            F_Front_Tx_Request = SET;
            R_UART0_Start();
        }
        else{}
    }
    else
    {
        gu8_front_tx_retry_cnt = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void make_front_tx_data(void)
{
    U8 mu8_temp = 0;
    U8 mu8_cnt = 0;
    U16 mu16_cal_crc = 0;
    U8 mu8_crc_high = 0;
    U8 mu8_crc_low = 0;
    U8 mu8_buffer[FRONT_TX_BUFFER_SIZE];

    gu8_front_tx_buffer[0] = PROTOCOL_STX;
    gu8_front_tx_buffer[1] = PROTOCOL_DEVICE_ID_FRONT;
    
    /* ���� Segments */
    gu8_front_tx_buffer[2] = gu8_front_temp_fnd_hundred;
    gu8_front_tx_buffer[3] = gu8_front_temp_fnd_ten;
    gu8_front_tx_buffer[4] = gu8_front_temp_fnd_one;
    
    /* ������ Segments */
    gu8_front_tx_buffer[5] = gu8_front_amount_fnd_hundred;
    gu8_front_tx_buffer[6] = gu8_front_amount_fnd_ten;
    gu8_front_tx_buffer[7] = gu8_front_amount_fnd_one;

    /* Icon LEDs */
    gu8_front_tx_buffer[8] = gu8_front_left_led;
    gu8_front_tx_buffer[9] = gu8_front_left_led_2;      // LED �߰� @CH.PARK
    gu8_front_tx_buffer[10] = gu8_front_right_led;

    /* �¿��� BARs, ��� Icon LEDs */
    gu8_front_tx_buffer[11] = gu8_front_temp_setting_bar_led;
    gu8_front_tx_buffer[12] = gu8_front_amount_setting_bar_led;
    gu8_front_tx_buffer[13] = gu8_front_center_recipe_led;

    /* ���ú� LEDs */
    gu8_front_tx_buffer[14] = gu8_front_select_led;
    gu8_front_tx_buffer[15] = gu8_front_setting_led;
    gu8_front_tx_buffer[16] = gu8_front_setting_led_2;
    gu8_front_tx_buffer[17] = gu8_front_under_text_led;
    gu8_front_tx_buffer[18] = gu8_front_under_icon_led;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
    gu8_front_tx_buffer[19] = gu8_dimming_set_one;
    gu8_front_tx_buffer[20] = gu8_dimming_set_two;
    gu8_front_tx_buffer[21] = gu8_dimming_set_three;
    gu8_front_tx_buffer[22] = gu8_dimming_set_four;
    gu8_front_tx_buffer[23] = gu8_dimming_set_five;
    gu8_front_tx_buffer[24] = gu8_dimming_set_six;
    gu8_front_tx_buffer[25] = gu8_dimming_set_seven;
    gu8_front_tx_buffer[26] = gu8_dimming_set_eight;
    gu8_front_tx_buffer[27] = gu8_dimming_set_nine;
    gu8_front_tx_buffer[28] = gu8_dimming_set_ten;
    gu8_front_tx_buffer[29] = gu8_dimming_set_eleven;
    gu8_front_tx_buffer[30] = gu8_dimming_set_twelve;
    gu8_front_tx_buffer[31] = gu8_dimming_set_thirteen;
    gu8_front_tx_buffer[32] = gu8_dimming_set_fourteen;
    gu8_front_tx_buffer[33] = gu8_dimming_set_fifteen;
    gu8_front_tx_buffer[34] = gu8_dimming_set_sixteen;
    gu8_front_tx_buffer[35] = gu8_dimming_set_seventeen;
    gu8_front_tx_buffer[36] = gu8_dimming_set_eighteen;
    gu8_front_tx_buffer[37] = gu8_dimming_set_nineteen;
    gu8_front_tx_buffer[38] = gu8_dimming_set_twenty;
    gu8_front_tx_buffer[39] = gu8_dimming_set_twenty_one;
    gu8_front_tx_buffer[40] = gu8_dimming_set_twenty_two;
    gu8_front_tx_buffer[41] = gu8_dimming_set_twenty_three;
    gu8_front_tx_buffer[42] = gu8_dimming_set_twenty_four;
    gu8_front_tx_buffer[43] = gu8_dimming_set_twenty_five;
    gu8_front_tx_buffer[44] = gu8_dimming_set_twenty_six;
    gu8_front_tx_buffer[45] = gu8_dimming_set_twenty_seven;
    gu8_front_tx_buffer[46] = gu8_dimming_set_twenty_eight;
    gu8_front_tx_buffer[47] = gu8_dimming_set_twenty_nine;
    gu8_front_tx_buffer[48] = gu8_dimming_set_thirty;
    gu8_front_tx_buffer[49] = gu8_dimming_set_thirty_one;
    gu8_front_tx_buffer[50] = gu8_dimming_set_thirty_two;
    gu8_front_tx_buffer[51] = gu8_dimming_set_thirty_three;
    gu8_front_tx_buffer[52] = gu8_dimming_set_thirty_four;
    gu8_front_tx_buffer[53] = gu8_dimming_set_thirty_five;
    gu8_front_tx_buffer[54] = gu8_dimming_set_thirty_six;
    
    gu8_front_tx_buffer[55] = gu8_dimming_set_thirty_seven;
    gu8_front_tx_buffer[56] = gu8_dimming_set_thirty_eight;
    gu8_front_tx_buffer[57] = gu8_dimming_set_thirty_nine;
    gu8_front_tx_buffer[58] = gu8_dimming_set_fourty;
    
    
    gu8_front_tx_buffer[59] = gu8_etc_1;
    gu8_front_tx_buffer[60] = gu8_etc_2;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
    gu8_front_tx_buffer[61] = u8AnimationDimming_L;
    gu8_front_tx_buffer[62] = u8AnimationDimming_H;

    gu8_front_tx_buffer[63] = gu8_animation_time;
    gu8_front_tx_buffer[64] = gu8_animation_duty;

    gu8_front_tx_buffer[65] = u8AnimationDimmingTwo_L;
    gu8_front_tx_buffer[66] = u8AnimationDimmingTwo_H;

    gu8_front_tx_buffer[67] = gu8_animation_dimming_three;
    gu8_front_tx_buffer[68] = gu8_animation_dimming_four;
    gu8_front_tx_buffer[69] = gu8_animation_dimming_five;
    gu8_front_tx_buffer[70] = gu8_animation_dimming_six;
    gu8_front_tx_buffer[71] = gu8_animation_dimming_seven;
    gu8_front_tx_buffer[72] = gu8_animation_dimming_eight;      // LPP �߰�
    
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
    gu8_front_tx_buffer[73] = gu8_fota_start;

    /*..hui [23-6-23���� 1:51:48] Ȥ�ø��� ���� �߰�..*/
    gu8_front_tx_buffer[74] = gu8_animation_dimming_six;
    gu8_front_tx_buffer[75] = gu8_rgb_pwm_period;
    gu8_front_tx_buffer[76] = gu8_rgb_red_on_time;
    gu8_front_tx_buffer[77] = gu8_rgb_green_on_time;
    gu8_front_tx_buffer[78] = gu8_rgb_blue_on_time;

    gu8_front_tx_buffer[79] = gu8_rgb_ice_outer_red_on_time;
    gu8_front_tx_buffer[80] = gu8_rgb_ice_outer_green_on_time;
    gu8_front_tx_buffer[81] = gu8_rgb_ice_outer_blue_on_time;
    
    gu8_front_tx_buffer[82] = gu8_rgb_ice_inner_red_on_time;
    gu8_front_tx_buffer[83] = gu8_rgb_ice_inner_green_on_time;
    gu8_front_tx_buffer[84] = gu8_rgb_ice_inner_blue_on_time;
    
    #if 0
    gu8_front_tx_buffer[64] = gu8_play;
    gu8_front_tx_buffer[65] = gu8_volume;
    gu8_front_tx_buffer[66] = (U8)(gu16_address/(U16)256);
    gu8_front_tx_buffer[67] = (U8)(gu16_address%(U16)256);
    #endif

    if( F_PlayVoice == SET )
    {
        gu8_play = SET;
    }
    else{}

    /*gu8_front_tx_buffer[64] = F_PlayVoice;*/
    gu8_front_tx_buffer[85] = gu8_play;
    
    if(bit_sleep_mode_start == SET 
    && bit_sleep_mode_enable == SET
    && bit_power_on_voice == SET)
    {
        gu8_front_tx_buffer[86] = SOUND_VOLUME_LEVEL_1;
    }
    else
    {
      gu8_front_tx_buffer[86] = gu8VoiceVolumeLevel;
    }

    gu8_front_tx_buffer[87] = (U8)(gu16_voice_address/(U16)256);
    gu8_front_tx_buffer[88] = (U8)(gu16_voice_address%(U16)256);
    gu8_front_tx_buffer[89] = gu8_hk16_bright;

    gu8_front_tx_buffer[90] = gu8_etc_3;
    gu8_front_tx_buffer[91] = gu8_etc_4;

    mu16_cal_crc = Rx_CRC_CCITT(gu8_front_tx_buffer, MAIN_CRC_CALC_RANGE);

    mu8_crc_high = (U8)HighByte(mu16_cal_crc);
    mu8_crc_low = (U8)LowByte(mu16_cal_crc);

    gu8_front_tx_buffer[92] = mu8_crc_high;
    gu8_front_tx_buffer[93] = mu8_crc_low;
    
    gu8_front_tx_buffer[94] = PROTOCOL_ETX;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void convert_final_asc_data(U8 *mu8_tx_data, U8 mu8_length)
{
#if 0
    gu8_front_tx_buffer[0] = mu8_tx_data[0];
    gu8_front_tx_buffer[1] = mu8_tx_data[1];
    gu8_front_tx_buffer[2] = mu8_tx_data[2];

    gu8_front_tx_buffer[3] = (U8)( (HexToAsc(mu8_tx_data[3]) >> 8) & 0xFF );
    gu8_front_tx_buffer[4] = (U8)( (HexToAsc(mu8_tx_data[3])) & 0xFF );

    gu8_front_tx_buffer[5] = (U8)( (HexToAsc(mu8_tx_data[4]) >> 8) & 0xFF );
    gu8_front_tx_buffer[6] = (U8)( (HexToAsc(mu8_tx_data[4])) & 0xFF );

    gu8_front_tx_buffer[7] = (U8)( (HexToAsc(mu8_tx_data[5]) >> 8) & 0xFF );
    gu8_front_tx_buffer[8] = (U8)( (HexToAsc(mu8_tx_data[5])) & 0xFF );

    gu8_front_tx_buffer[9] = (U8)( (HexToAsc(mu8_tx_data[6]) >> 8) & 0xFF );
    gu8_front_tx_buffer[10] = (U8)( (HexToAsc(mu8_tx_data[6])) & 0xFF );

    gu8_front_tx_buffer[11] = (U8)( (HexToAsc(mu8_tx_data[7]) >> 8) & 0xFF );
    gu8_front_tx_buffer[12] = (U8)( (HexToAsc(mu8_tx_data[7])) & 0xFF );

    gu8_front_tx_buffer[13] = (U8)( (HexToAsc(mu8_tx_data[8]) >> 8) & 0xFF );
    gu8_front_tx_buffer[14] = (U8)( (HexToAsc(mu8_tx_data[8])) & 0xFF );

    gu8_front_tx_buffer[15] = (U8)( (HexToAsc(mu8_tx_data[9]) >> 8) & 0xFF );
    gu8_front_tx_buffer[16] = (U8)( (HexToAsc(mu8_tx_data[9])) & 0xFF );

    gu8_front_tx_buffer[17] = (U8)( (HexToAsc(mu8_tx_data[10]) >> 8) & 0xFF );
    gu8_front_tx_buffer[18] = (U8)( (HexToAsc(mu8_tx_data[10])) & 0xFF );

    gu8_front_tx_buffer[19] = (U8)( (HexToAsc(mu8_tx_data[11]) >> 8) & 0xFF );
    gu8_front_tx_buffer[20] = (U8)( (HexToAsc(mu8_tx_data[11])) & 0xFF );

    gu8_front_tx_buffer[21] = mu8_tx_data[12];
#endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR0_Front_Panel_Rx(void)
{
    U8 mu8_rx_buffer = RXD0;
    U8 mu8_packet_length = 0;

    if( (F_Front_Rx_Complete == CLEAR) && (F_Front_Tx_Request == CLEAR) )
    {
        gu8_front_rx_buffer[gu8_front_rx_receive_cnt] = mu8_rx_buffer;

        if (gu8_front_rx_buffer[0] == PROTOCOL_STX)
        {
            switch(gu8_front_rx_receive_cnt)
            {
                case DEVICE_ID_ROCATION:

                    if( gu8_front_rx_buffer[DEVICE_ID_ROCATION] != PROTOCOL_DEVICE_ID_MAIN )
                    {
                        gu8_front_rx_receive_cnt = 0;
                    }
                    else{}

                    break;

                default :

                    break;
            }

            if(gu8_front_rx_receive_cnt >= (U8)(FRONT_TO_MAIN_DATA_TOTAL_LENGTH - 1))
            {
                if(gu8_front_rx_buffer[gu8_front_rx_receive_cnt] == PROTOCOL_ETX)
                {
                    gu8_front_rx_receive_cnt = 0;
                    F_Front_Rx_Complete = SET;
                }
                else
                {
                    gu8_front_rx_receive_cnt = 0;
                }
            }
            else
            {
                gu8_front_rx_receive_cnt++;
            }
        }
        else
        {
            gu8_front_rx_receive_cnt = 0;
        }
    }
    else
    {
        gu8_front_rx_receive_cnt = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Uart_ISR0_Front_Panel_Tx ( void )
{
    if(gu8_front_tx_count < MAIN_TO_FRONT_DATA_TOTAL_LENGTH)
    {
        TXD0 = gu8_front_tx_buffer[gu8_front_tx_count];
        gu8_front_tx_count++;
    }
    else
    {
        F_Front_Tx_Request = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

