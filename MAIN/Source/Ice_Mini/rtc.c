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
#include    "rtc.h"

void InitRtc(void);
static void EnableRtcCCR(void);
static void DisableRtcCCR(void);
U8 IsRtcBatBackUpMode(void);
void ReadRtcTime(void);
void WriteRtcTime(void);
void ProcessRtc(void);

U8 IsRTC_Error(void);
void InitRtcTime(void);


//U8 test_pcb_check_rtc_init(void);
U8 IsRTC_Reset(void);
U8 IsRTC_OSCF_Error(void);

void rtc_error_check(void);

U8 over_max_year(void);


void Delay_MS( U16 ms );
void Delay_US( U8 us );


U8 gu8_rtc_read_buf_1[8];
U8 gu8_rtc_read_buf_2[8];
U8 gu8_rtc_write_buf[8];

U8 gu8_rtc_time_Y2K;       // 19 or 20
U8 gu8_rtc_time_DayWeek;   // 0 ~ 6
U8 gu8_rtc_time_Year;      // 0 ~ 99
U8 gu8_rtc_time_Month;     // 1 ~ 12
U8 gu8_rtc_time_Date;      // 1 ~ 31
U8 gu8_rtc_time_Hour;      // 0 ~ 23
U8 gu8_rtc_time_Min;       // 0 ~ 59
U8 gu8_rtc_time_Sec;       // 0 ~ 59
U8 gu8_rtc_time_AmPm;



U8 gu8_rtc_init_success;


U16 gu16_rtc_error_cnt;
U16 gu16_rtc_error_timer;

bit bit_rtc_error_state;
bit bit_rtc_comm_error_state;


bit F_Rtc_Write;
U8 gu8_Rtc_Reg_Status;


U8 u8_test;
U8 gu8_uart_rtc_test_finish;
U8 gu8_uart_rtc_test_total_timer;

U8 gu8_rtc_garbage_timer;
U8 gu8_pba_rtc_test_finish;
bit bit_pba_rtc_error_state;
U8 u8_rtc_test_timer;


U8 gu8_rtc_time_Year_Before;
U8 gu8_rtc_time_Month_Before;
U8 gu8_rtc_time_Date_Before;
U8 gu8_rtc_time_Hour_Before;
U8 gu8_rtc_time_Min_Before;
U8 gu8_rtc_time_Sec_Before;

U8 gu8_rtc_stop_error_timer;
bit bit_rtc_stop_error_state;

U8 gu8_rtc_read_timer;

bit bit_rtc_time_read;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void InitRtc(void)
{
    U16 mu16Delay = 30;
    U8 mu8_rtc_err = 0;

    // ���� ���͸� ���� �����ϴ� ���̸�, ��õ�...
    do
    {
        Delay_MS( 100 );
        mu16Delay--;
        if( mu16Delay == 0 )
        {
            break;
        }
        else{}

    } while( IsRtcBatBackUpMode() == TRUE );


    EnableRtcCCR();
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_CTR_PWR, 0x00 );
    DisableRtcCCR();

    EnableRtcCCR();
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_CTR_DTR, 0x03 );  // Digital Trimming
    DisableRtcCCR();

    EnableRtcCCR();
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_CTR_ATR, (0x20|0x10) );
    DisableRtcCCR();

    //EnableRtcCCR();
    //HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_CTR_INT, 0x18 );  // Output freq 32.768khz
    //DisableRtcCCR();

    EnableRtcCCR();
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_CTR_BL,  0x00 );
    DisableRtcCCR();

    // Read RTC Status
    HAL_RTC_ByteRead( DEV_ADDR_RTC, ADDR_RTC_STATUS, &gu8_Rtc_Reg_Status);

    mu8_rtc_err = IsRTC_Reset();

    if( mu8_rtc_err == SET )
    {
        /*..hui [20-1-10���� 7:37:44] �����Ȼ���..*/
        InitRtcTime();
    }
    else
    {
        ReadRtcTime();

        if(gu8_rtc_init_success == SET)
        {
            /*..hui [20-6-10���� 7:29:49] �ð��� ���� ���� �̿��� ��� ������ �ʱ�ȭ�ϵ��� ����..*/
            /*..hui [20-6-10���� 7:30:03] ���ο��� �����Ⱚ ��.. ���Ʋ�..*/
            if( (gu8_rtc_time_Year >= SETTING_MIN_YEAR && gu8_rtc_time_Year <= SETTING_MAX_YEAR)
                && (gu8_rtc_time_Month >= 1 && gu8_rtc_time_Month <= 12)
                && (gu8_rtc_time_Date  >= 1 && gu8_rtc_time_Date  <= 31)
                && gu8_rtc_time_Hour  <= 23
                && gu8_rtc_time_Min   <= 59
                && gu8_rtc_time_Sec   <= 59 )
            {

            }
            else
            {
                InitRtcTime();
            }
        }
        else
        {
            /*..hui [20-6-16���� 10:38:53] ��� �����Ұ�� ���� �ʱ�ȭ..*/
            gu8_rtc_time_Year = RTC_DEFAULT_YEAR;
            gu8_rtc_time_Month = RTC_DEFAULT_MONTH;
            gu8_rtc_time_Date = RTC_DEFAULT_DATE;
            gu8_rtc_time_Hour = RTC_DEFAULT_HUOR;
            gu8_rtc_time_Min = RTC_DEFAULT_MIN;
            gu8_rtc_time_Sec = RTC_DEFAULT_SEC;
            gu8_rtc_time_DayWeek = RTC_DEFAULT_DAYWEEK;
            gu8_rtc_time_Y2K = RTC_DEFAULT_Y2K;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static void EnableRtcCCR(void)
{
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_RTC_STATUS, 0x02 );
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_RTC_STATUS, 0x06 );
    Delay_MS(200);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
static void DisableRtcCCR(void)
{
    HAL_RTC_ByteWrite( DEV_ADDR_RTC, ADDR_RTC_STATUS, 0x00 );
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 IsRTC_Reset(void)
{
    if( (gu8_Rtc_Reg_Status & (MASK_RTCF)) == 0 )
    {
        return CLEAR; // ����
    }
    else{}

    return SET; //ERROR
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ProcessRtc(void)
{
    U8 mu8_rtc_err = 0;
    U8 mu8_return = 0;
    U8 mu8_reset = 0;

    /*..hui [20-4-1���� 5:50:14] �ð� �����̶� ��¥ ������ ������..*/
    /*..hui [20-4-1���� 5:50:18] �޴� �ϳ����� ����..*/
    /*..hui [20-4-27���� 11:20:11] LCD ������ �̵�..*/
    mu8_return = over_max_year();

    if(mu8_return == SET)
    {
        InitRtcTime();
        /*lcd_time_init();*/
        return;
    }
    else{}

    // Read Time from RTC
    gu8_rtc_read_timer++;

    if( gu8_rtc_read_timer >= RTC_READ_TIME || F_FW_Version_Display_Mode == CLEAR )
    {
        /*..hui [20-6-19���� 1:33:38] 20�ʸ��� �ѹ��� �е��� ����..*/
        gu8_rtc_read_timer = 0;

        // Read RTC Status
        HAL_RTC_ByteRead( DEV_ADDR_RTC, ADDR_RTC_STATUS, &gu8_Rtc_Reg_Status);

        /*..hui [20-6-11���� 9:38:33] �����ǰų� ũ����Ż �ҷ��� ����..*/
        mu8_rtc_err = IsRTC_Error();

        // RTC ����
        if( mu8_rtc_err == SET )
        {
            /*..hui [20-1-10���� 7:37:44] �����Ȼ���..*/
            gu16_rtc_error_cnt++;
            /*..hui [20-2-18���� 10:00:22] ������������ �ð� �ʱ�ȭ�� ���ϴ°ɷ�..*/
            /*..hui [20-2-18���� 10:00:36] �׳� �����ð����� �̾ ���۵ǵ���.. �׷��� ������ �����״�..*/
            /*..hui [20-2-18���� 1:38:42] ���µǸ� RTC ��ü���� �ð� �ʱ�ȭ��..*/
            /*..hui [20-4-17���� 8:41:41] �ִ� 100�������� ����..*/

            bit_rtc_error_state = SET;
        }
        else
        {
            /*..hui [20-4-17���� 8:42:42] rtc ���� ���� Ŭ����..*/
            gu16_rtc_error_timer = 0;
            bit_rtc_error_state = CLEAR;
        }

        ReadRtcTime();
        bit_rtc_time_read = SET;

        /*..hui [20-6-10���� 7:29:49] �ð��� ���� ���� �̿��� ��� ������ �ʱ�ȭ�ϵ��� ����..*/
        /*..hui [20-6-10���� 7:30:03] ���ο��� �����Ⱚ ��.. ���Ʋ�..*/
        if( (gu8_rtc_time_Year >= SETTING_MIN_YEAR && gu8_rtc_time_Year <= SETTING_MAX_YEAR)
            && (gu8_rtc_time_Month >= 1 && gu8_rtc_time_Month <= 12)
            && (gu8_rtc_time_Date  >= 1 && gu8_rtc_time_Date  <= 31)
            && gu8_rtc_time_Hour  <= 23
            && gu8_rtc_time_Min   <= 59
            && gu8_rtc_time_Sec   <= 59 )
        {
            gu8_rtc_garbage_timer = 0;

            rtc_error_check();
        }
        else
        {
            if( bit_rtc_comm_error_state == CLEAR && bit_rtc_error_state == CLEAR )
            {
                gu8_rtc_garbage_timer++;
            }
            else
            {
                gu8_rtc_garbage_timer = 0;
            }

            /*..hui [20-6-11���� 9:46:21] 5ȸ ���� �����Ⱚ�� ������� �ʱ�ȭ �߰�..*/
            /*..hui [20-6-19���� 1:47:26] 3�е��� ��������..*/
            if( gu8_rtc_garbage_timer >= 9 )
            {
                gu8_rtc_garbage_timer = 0;
                InitRtcTime();
            }
            else{}
        }
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 over_max_year(void)
{
    U8 mu8_return = 0;

    if( gu8_rtc_time_Year > SETTING_MAX_YEAR
        && gu8_rtc_time_Month == 1
        && gu8_rtc_time_Date == 1 )
    {
        mu8_return = SET;
    }
    else{}

    return mu8_return;
}




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 IsRtcBatBackUpMode(void)
{
    U8 mu8Ret = 0;
    U8 mu8Reg = 0;

    mu8Ret = HAL_RTC_ByteRead( DEV_ADDR_RTC, ADDR_RTC_STATUS, &mu8Reg );

    if( mu8Ret != TRUE )
    {
        return TRUE;    // Erro
    }
    else{}

    if( (mu8Reg & MASK_BAT) != 0 )
    {
        return TRUE;   // Battery BackUp Mode
    }
    else{}

    return FALSE;  // Vcc Mode
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void ReadRtcTime(void)
{
    U8 mu8Ret_1 = 0;
    U8 mu8Ret_2 = 0;
    U16 mu16_wait_cycle = 1000;

    // Read time buffer
    //mu8Ret_1 = HAL_RTC_SeqRead( DEV_ADDR_RTC, ADDR_RTC_SECONDS, &gu8_rtc_read_buf_1[0], 8 );

    mu8Ret_1 = HAL_RTC_SeqRead( DEV_ADDR_RTC, ADDR_RTC_SECONDS, gu8_rtc_read_buf_1, 8 );

    if( mu8Ret_1 == FALSE )
    {
        /*..hui [20-4-20���� 9:52:22] RTC ��� ����..*/
        bit_rtc_comm_error_state = SET;
        return;
    }
    else{}

    ///////////////////////////wait
    /*..hui [20-3-13���� 1:36:39] �������� �б����� �����ð� ���(�� 60us).. ������ ����� ����..*/
    while (mu16_wait_cycle--)
    {
        ;
    }

    // Read aging time buffer
    //mu8Ret_2 = HAL_RTC_SeqRead( DEV_ADDR_RTC, ADDR_RTC_SECONDS, &gu8_rtc_read_buf_2[0], 8 );

    mu8Ret_2 = HAL_RTC_SeqRead( DEV_ADDR_RTC, ADDR_RTC_SECONDS, gu8_rtc_read_buf_2, 8 );

    if( mu8Ret_2 == FALSE )
    {
        bit_rtc_comm_error_state = SET;
        return;
    }
    else{}

    // [0] ������ sec ���� �����ϰ� ������ �ð��� �����ϸ� �ð��� ������.
    // read �������� �ð� ���� noise�� ���ؼ� �ջ�Ǵ� ���� ���� ���� ���� �����
    if( gu8_rtc_read_buf_1[1] == gu8_rtc_read_buf_2[1]
        && gu8_rtc_read_buf_1[2] == gu8_rtc_read_buf_2[2]
        && gu8_rtc_read_buf_1[3] == gu8_rtc_read_buf_2[3]
        && gu8_rtc_read_buf_1[4] == gu8_rtc_read_buf_2[4]
        && gu8_rtc_read_buf_1[5] == gu8_rtc_read_buf_2[5]
        && gu8_rtc_read_buf_1[6] == gu8_rtc_read_buf_2[6]
        && gu8_rtc_read_buf_1[7] == gu8_rtc_read_buf_2[7] )
    {
        gu8_rtc_time_Sec = Hex2Dec( gu8_rtc_read_buf_2[0] );
        gu8_rtc_time_Min = Hex2Dec( gu8_rtc_read_buf_2[1] );
        gu8_rtc_time_Hour = Hex2Dec( gu8_rtc_read_buf_2[2] & 0x3F );
        gu8_rtc_time_Date = Hex2Dec( gu8_rtc_read_buf_2[3] );
        gu8_rtc_time_Month = Hex2Dec( gu8_rtc_read_buf_2[4] );
        gu8_rtc_time_Year = Hex2Dec( gu8_rtc_read_buf_2[5] );
        gu8_rtc_time_DayWeek = Hex2Dec( gu8_rtc_read_buf_2[6] );
        gu8_rtc_time_Y2K = Hex2Dec( gu8_rtc_read_buf_2[7] );

        gu8_rtc_init_success = SET;
        bit_rtc_comm_error_state = CLEAR;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void WriteRtcTime(void)
{
    I8 mLastedDate;
    U8 mu8Ret = 0;

    /*..hui [20-3-12���� 2:06:18] 0�϶� ���͸� �߰�..*/
    if( (gu8_rtc_time_Year >= SETTING_MIN_YEAR && gu8_rtc_time_Year <= SETTING_MAX_YEAR)
        && (gu8_rtc_time_Month >= 1 && gu8_rtc_time_Month <= 12)
        && (gu8_rtc_time_Date  >= 1 && gu8_rtc_time_Date  <= 31)
        && gu8_rtc_time_Hour  <= 23
        && gu8_rtc_time_Min   <= 59
        && gu8_rtc_time_Sec   <= 59 )
    {
        //
    }
    else
    {
        return;
    }


    gu8_rtc_write_buf[0] =  Dec2Hex(gu8_rtc_time_Sec);
    gu8_rtc_write_buf[1] =  Dec2Hex(gu8_rtc_time_Min);
    gu8_rtc_write_buf[2] =  Dec2Hex(gu8_rtc_time_Hour) | MASK_MIL;
    gu8_rtc_write_buf[3] =  Dec2Hex(gu8_rtc_time_Date);
    gu8_rtc_write_buf[4] =  Dec2Hex(gu8_rtc_time_Month);
    gu8_rtc_write_buf[5] =  Dec2Hex(gu8_rtc_time_Year);
    gu8_rtc_write_buf[6] =  Dec2Hex(gu8_rtc_time_DayWeek);
    gu8_rtc_write_buf[7] =  Dec2Hex(gu8_rtc_time_Y2K);

    EnableRtcCCR();
    HAL_RTC_PageWrite( DEV_ADDR_RTC, ADDR_RTC_SECONDS, gu8_rtc_write_buf, 8 );
    DisableRtcCCR();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void InitRtcTime(void)
{
    I8 mLastedDate;
    U8 mu8Ret = 0;

    /*..hui [19-10-16���� 7:16:13] RTC ����Ʈ�� 2019�� 1�� 1�� ȭ���� ���� 1�� 00��..*/
    /*..hui [19-11-5���� 5:56:07] RTC ����Ʈ�� 2020�� 1�� 1�� ������ ���� 1�� 00��..*/
    gu8_rtc_time_Year = RTC_DEFAULT_YEAR;
    gu8_rtc_time_Month = RTC_DEFAULT_MONTH;
    gu8_rtc_time_Date = RTC_DEFAULT_DATE;
    gu8_rtc_time_Hour = RTC_DEFAULT_HUOR;
    gu8_rtc_time_Min = RTC_DEFAULT_MIN;
    gu8_rtc_time_Sec = RTC_DEFAULT_SEC;
    gu8_rtc_time_DayWeek = RTC_DEFAULT_DAYWEEK;
    gu8_rtc_time_Y2K = RTC_DEFAULT_Y2K;

    gu8_rtc_write_buf[0] =  Dec2Hex(gu8_rtc_time_Sec);
    gu8_rtc_write_buf[1] =  Dec2Hex(gu8_rtc_time_Min);
    gu8_rtc_write_buf[2] =  Dec2Hex(gu8_rtc_time_Hour) | MASK_MIL;
    gu8_rtc_write_buf[3] =  Dec2Hex(gu8_rtc_time_Date);
    gu8_rtc_write_buf[4] =  Dec2Hex(gu8_rtc_time_Month);
    gu8_rtc_write_buf[5] =  Dec2Hex(gu8_rtc_time_Year);
    gu8_rtc_write_buf[6] =  Dec2Hex(gu8_rtc_time_DayWeek);
    gu8_rtc_write_buf[7] =  Dec2Hex(gu8_rtc_time_Y2K);

    EnableRtcCCR();
    HAL_RTC_PageWrite( DEV_ADDR_RTC, ADDR_RTC_SECONDS, gu8_rtc_write_buf, 8 );
    DisableRtcCCR();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/* RTC IC ���� Ȯ��
 *
 * Return
 *  TRUE : RTC ����!!
 *  FALSE : RTC ����!!
 *
 */
U8 IsRTC_Error(void)
{
    if( (gu8_Rtc_Reg_Status & (MASK_OSCF|MASK_RTCF)) == 0 )
    {
        return CLEAR; // ����
    }
    else{}

    return SET; //ERROR
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 IsRTC_OSCF_Error(void)
{
    if( (gu8_Rtc_Reg_Status & (MASK_OSCF)) == 0 )
    {
        return CLEAR; // ����
    }
    else{}

    return SET; //ERROR
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void rtc_error_check(void)
{
    /*..hui [20-6-18���� 3:59:08] RTC �ð��� ������� ���� ��� LCD �ð����� ��ȯ�ϱ� ���� �߰�..*/
    if( gu8_rtc_time_Year == gu8_rtc_time_Year_Before
        && gu8_rtc_time_Month == gu8_rtc_time_Month_Before
        && gu8_rtc_time_Date == gu8_rtc_time_Date_Before
        && gu8_rtc_time_Hour == gu8_rtc_time_Hour_Before
        && gu8_rtc_time_Min == gu8_rtc_time_Min_Before
        && gu8_rtc_time_Sec == gu8_rtc_time_Sec_Before )
    {
        gu8_rtc_stop_error_timer++;

        /*..hui [20-6-19���� 1:38:00] 1�п���..*/
        /*..hui [20-6-19���� 1:46:23] ������ RTC �ٽ� �о����� ������ ������ �׶����� �ٽ� LCD�� �������ָ� �ǹǷ�..*/
        /*..hui [20-6-19���� 1:46:35] �׳� �ѹ��� �����ϰ� ������ LCD �ð� ������ ���ϴ°ɷ�..*/
        if( gu8_rtc_stop_error_timer >= 1 )
        {
            gu8_rtc_stop_error_timer = 1;
            bit_rtc_stop_error_state = SET;
        }
        else{}
    }
    else
    {
        gu8_rtc_time_Year_Before = gu8_rtc_time_Year;
        gu8_rtc_time_Month_Before = gu8_rtc_time_Month;
        gu8_rtc_time_Date_Before = gu8_rtc_time_Date;
        gu8_rtc_time_Hour_Before = gu8_rtc_time_Hour;
        gu8_rtc_time_Min_Before = gu8_rtc_time_Min;
        gu8_rtc_time_Sec_Before = gu8_rtc_time_Sec;

        gu8_rtc_stop_error_timer = 0;
        bit_rtc_stop_error_state = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Delay_MS( U16 ms )
{
    U16 i;
    U8      j;

    /*..hui [19-10-21���� 1:32:34] ���� �� 86.8ms..*/
    for( i = 0 ; i < ms ; i++ )
    {
        for( j = 0; j < 4 ; j++ )   // 1ms loop delay
        {
            Delay_US( 250 );
            WDTE = (U8)0xAC;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Delay_US( U8 us )
{
    while( us-- )
    {
        NOP();
        NOP();
        NOP();
        NOP();
    }

}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



