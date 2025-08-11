/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Input.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M4_Input.h"


void Input(void);
//void input_select_bar(void);
//void input_cds(void);

//void input_overflow(void);
void check_ice_full(void);
void check_ice_low(void);       /* �����˻� �߰� 250224 CH.PARK */
void ice_tank_amount_check(void);   /* ����,����,�ߺ� �Ǵ� �߰� 250428 CH.PARK */

//void LeverInput(void);

//bit F_Bar;
//bit F_BeBar;
//bit F_BarSet;
//bit F_SelectBar;
//U8 gu8Bar;

Ice_Amount gu8_ice_tank_ice_amount;
Ice_Amount gu8_ice_tank_ice_amount_old;


bit F_NoUseSave;
bit F_DayNoUseSave;
bit F_NightNoUseSave;             // �� ������ ����

//----------------------------------------------------// IR
/* ���� �Է� ���� */
U8 gu8IRTime, gu8IRCount;
U16 gu16IRInterval;

/* ���� �Է� ���� */
U8 gu8IR_l_Time, gu8IR_l_Count;
U16 gu16IR_l_Interval;
/****************************************************************************/
bit F_IceFull;                        // ����
bit F_IR;                             // ���� �˻�
/****************************************************************************/
bit F_IceLack;                    // ����
bit F_Low_IR;                         // ���� �˻�

/*..hui [18-3-8���� 5:25:49] ó�� ���� ON�� ���� üũ..*/
bit bit_first_ice_full;

U8 gu8ContyCancel;
U8 gu8Out;
U16 gu16Conty;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Input(void)
{
    /*..hui [19-6-26���� 1:54:08] �������� �Է�..*/
    input_water_level();

    /*..hui [19-6-26���� 1:12:26] Ʈ���� ����ũ�ν���ġ �Է�..*/
    input_ice_tray_micro_sw();

    /*..hui [19-6-26���� 1:54:12] ���� �Է�..*/
    check_ice_full();

    /* ���� �Է� 250224 CH.PARK */
    check_ice_low();

    /* ��,��,���� �Ǵ� 250428 CH.PARK */
    ice_tank_amount_check();

    /*..hui [19-7-22���� 7:36:53] ��������..*/
    calculate_flow_input();

    /*..hui [23-6-9���� 2:20:05] ���� ��������..*/
    /////calculate_filter_flow_input();

    /*..hui [19-7-25���� 8:25:00] �������� �ٽ� �߰���..*/
    /*..hui [23-2-28���� 3:34:11] �������� ����..*/
    /*input_cds();*/

    /*detect_front_cds();*/
    
    /* ���͸���, ����Ŀ��, ���ͱ�ü �� ���� �Լ� */
    input_filter();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_ice_full(void)
{
    if(gu8IRTime > 0)
    {
        gu8IRTime--;                             // �����˻� 10��
    }
    else{}

    //==================================================================
    if(F_IR != SET && F_LineTest != SET)
    {
        return;
    }
    else{}
//
    if(pIR_POWER != SET)                                         // IR ��� �������
    {
        pIR_POWER = SET;

        if(F_LineTest == SET)
        {
            gu8IRTime = 30;
        }
        else
        {
            gu8IRTime = 100;
        }
    }
    else{}

    if(gu16ADIceFull >= ICEFULL_LEV)
    {
        gu8IRCount++;
    }
    else{}

    if(gu8IRTime == 0)
    {
        if(F_LineTest == SET)
        {
            if(gu8IRCount >= 10)
            {
                F_IceFull = CLEAR;
            }
            else
            {
                F_IceFull = SET;
            }
        }
        else
        {
            if(gu8IRCount >= 50)
            {
                F_IceFull = CLEAR;
            }
            else
            {
                F_IceFull = SET;
            }
        }

        gu8IRCount = 0;
        pIR_POWER = CLEAR;
        F_IR = CLEAR;

        if(F_LineTest == SET)
        {
            gu16IRInterval = 0;
        }
        else
        {
            gu16IRInterval = IR_INTERVAL;       /* �����˻� : ���� �������� ������ 15�и��� �˻� ���� */
        }
    }
}

/****************************************************************************************************************/
/**
 * @brief ���� �Է� üũ
 * 
 */
void check_ice_low(void)
{
    if(gu8IR_l_Time > 0)
    {
        gu8IR_l_Time--;                             // �����˻� 10��
    }
    else{}

    //==================================================================
    if(F_Low_IR != SET && F_LineTest != SET)
    {
        return;
    }
    else{}
//
    if(pIR_POWER2 != SET)                                         // IR ��� �������
    {
        pIR_POWER2 = SET;

        if(F_LineTest == SET)
        {
            gu8IR_l_Time = 30;
        }
        else
        {
            gu8IR_l_Time = 100;
        }
    }
    else{}

    if(gu16ADIceLow <= ICEFULL_LEV)     // 1kg�� �����ϰ� ����
    {
        gu8IR_l_Count++;
    }
    else{}

    if(gu8IR_l_Time == 0)
    {
        if(F_LineTest == SET)
        {
            if(gu8IR_l_Count >= 10)
            {
                F_IceLack = CLEAR;      /* �̰��� */
            }
            else
            {
                F_IceLack = SET;        /* ���� */
            }
        }
        else
        {
            if(gu8IR_l_Count >= 50)
            {
                F_IceLack = CLEAR;      /* �̰��� */
            }
            else
            {
                F_IceLack = SET;        /* ���� */
            }
        }

        gu8IR_l_Count = 0;
        pIR_POWER2 = CLEAR;
        F_Low_IR = CLEAR;

        if(F_LineTest == SET)
        {
            gu16IR_l_Interval = 0;
        }
        else
        {
            gu16IR_l_Interval = IR_INTERVAL;       /* �����˻� : ���� �������� ������ 15�и��� �˻� ���� */
        }
    }

    /////////F_IceFull = CLEAR;
    //F_Cold_Enable = CLEAR;

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������ũ �� �����ܷ� �Ǵ�
***********************************************************************************************************************/
void ice_tank_amount_check(void)
{
    if((F_IceFull == SET)			/* ���� */
    && (F_IceLack == SET)
    )
    {
        gu8_ice_tank_ice_amount = ICE_TANK_FULL;
    }
    else if((F_IceFull == CLEAR)	/* ���� */
    && (F_IceLack == CLEAR)
    )
    {
        gu8_ice_tank_ice_amount = ICE_TANK_LOW;
    }
    else if((F_IceFull == CLEAR)	/* ���� ~ ���� ���� */
    && (F_IceLack == SET)
    )
    {
        gu8_ice_tank_ice_amount = ICE_TANK_MID;
    }
    else 
    {
        gu8_ice_tank_ice_amount = ICE_TANK_MID;
    }

    if(gu8_ice_tank_ice_amount != gu8_ice_tank_ice_amount_old)
    {
        gu8_ice_tank_ice_amount_old = gu8_ice_tank_ice_amount;

        if(gu8_ice_tank_ice_amount == ICE_TANK_LOW)
        {
            /* ���Ƿε� �̽��� ���� */
            // Play_Voice(VOICE_156_ICE_30_PERCENT_UNDER);
        }
        else {  } 
    }
    else {  } 
}

