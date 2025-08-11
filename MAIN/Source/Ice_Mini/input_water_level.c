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
#include    "input_water_level.h"



void input_water_level(void);
///void input_room_water_level(void);
///void room_low_water_level_input(void);
///void room_high_water_level_input(void);
///void room_water_level_confirm(void);

void input_drain_tank_level(void);
void drain_tank_low_water_level_input(void);
void drain_tank_high_water_level_input(void);
void drain_tank_water_level_confirm(void);




//U16 gu16_ice_level_delay;
U16 gu16ColdVVOnTime;
// 20140318 ���� �� �������� ���� 1L(50�� ����) ���� �� �޼� ���� , ���� �� �������� ��� ����
//U16 gu16IceVVTime1;

U16 gu16IceWaterExtDelay;



U8 gu8IceDrainLEV;
U8 gu8BeIceDrainLEV;
U8 gu8IceDrainSenLEV;
U8 gu8IceDrainLEVDelay;

//U8 gu8NFC_Feed_Check;

bit F_Low;                        // ����������
bit F_Feed;                       // �ǵ���

//----------------------------------------------------// ����ħ����
U8 gu8OVF;
bit F_OVF;
bit F_BeOVF;
bit F_OVFSet;
bit F_Overflow;


//----------------------------------------------------// ���� ��������
U8 gu8_Room_Water_Level;
U8 gu8BeRoomWaterLEV;
U8 gu8_room_level;
U8 gu8_be_room_level;
U8 gu8_room_level_delay;

//----------------------------------------------------// �ü� ��������
//U8 gu8ColdWaterLEV;
//U8 gu8BeColdWaterLEV;
//U8 gu8ColdLEV;
//U8 gu8BeColdLEV;
//U8 gu8ColdLEVDelay;

//----------------------------------------------------// ��� ��������
U8 gu8DrainWaterLEV;
U8 gu8BeDrainWaterLEV;
U8 gu8DrainLEV;
U8 gu8BeDrainLEV;
U8 gu8DrainLEVDelay;


U8 u8drain_low_level_on_decision_cnt;
U8 u8drain_low_level_off_decision_cnt;

U8 u8drain_high_level_on_decision_cnt;
U8 u8drain_high_level_off_decision_cnt;

bit F_drain_water_level_low;
bit F_drain_water_level_high;

TYPE_BYTE          U8DrainWaterLevelB;
#define            u8DrainWaterLevel                       U8DrainWaterLevelB.byte
#define            Bit0_Drain_Water_Empty                U8DrainWaterLevelB.Bit.b0      // 1
#define            Bit1_Drain_Water_Low                 U8DrainWaterLevelB.Bit.b1       // 2
#define            Bit2_Drain_Water_High                U8DrainWaterLevelB.Bit.b2       // 4
#define            Bit3_Drain_Water_Error                U8DrainWaterLevelB.Bit.b3      // 8


U16 gu16_room_low_level_on_timer;
U16 gu16_room_low_level_off_timer;
U16 gu16_room_high_level_on_timer;
U16 gu16_room_high_level_off_timer;

bit bit_room_water_level_low;
bit bit_room_water_level_high;

/////U16 u16_drain_level_power_timer;
/////bit bit_drain_level_power_output;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_water_level(void)
{
    /*..hui [19-6-26���� 1:12:15] ������ũ �������� �Է�..*/
    /*input_room_water_level();*/

    /*..hui [17-12-15���� 10:09:46] �巹�� ��ũ ���� ����..*/
    input_drain_tank_level();

    /*..hui [19-12-18���� 9:30:18] ����ħ ���� �߰�..*/
    /*input_overflow();*/
}


#if 0
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_room_water_level(void)
{
    /*..hui [24-1-24���� 12:13:36] �������� ���� ���� ����..*/
    room_low_water_level_input();
    room_high_water_level_input();
    room_water_level_confirm();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void room_low_water_level_input(void)
{
    if( pLEVEL_PURIFY_LOW == CLEAR )
    {
        gu16_room_low_level_on_timer = 0;
        gu16_room_low_level_off_timer++;

        if( gu16_room_low_level_off_timer >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            gu16_room_low_level_off_timer = ROOM_WATER_LEVEL_DETECT_TIME;

            if( bit_room_water_level_low == SET )
            {
                bit_room_water_level_low = CLEAR;
            }
            else{}
        }
        else{}
    }
    else
    {
        gu16_room_low_level_off_timer = 0;
        gu16_room_low_level_on_timer++;

        if ( gu16_room_low_level_on_timer >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            gu16_room_low_level_on_timer = ROOM_WATER_LEVEL_DETECT_TIME;

            if( bit_room_water_level_low == CLEAR )
            {
                bit_room_water_level_low = SET;
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
void room_high_water_level_input(void)
{
    if( pLEVEL_PURIFY_HIGH == CLEAR )
    {
        gu16_room_high_level_on_timer = 0;
        gu16_room_high_level_off_timer++;

        if( gu16_room_high_level_off_timer >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            gu16_room_high_level_off_timer = ROOM_WATER_LEVEL_DETECT_TIME;

            if( bit_room_water_level_high == SET )
            {
                bit_room_water_level_high = CLEAR;
            }
            else{}
        }
        else{}
    }
    else
    {
        gu16_room_high_level_off_timer = 0;
        gu16_room_high_level_on_timer++;

        if ( gu16_room_high_level_on_timer >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            gu16_room_high_level_on_timer = ROOM_WATER_LEVEL_DETECT_TIME;

            if( bit_room_water_level_high == CLEAR )
            {
                bit_room_water_level_high = SET;
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
void room_water_level_confirm(void)
{
    U8 mu8_room_level = 0;

    mu8_room_level |= (U8)(bit_room_water_level_low);
    mu8_room_level |= (U8)(bit_room_water_level_high << 1);


    switch(mu8_room_level)
    {
        case 0 :

            gu8_Room_Water_Level = ROOM_LEVEL_LOW;

            break;

        case 1 :

            gu8_Room_Water_Level = ROOM_LEVEL_MID;

            break;

        case 2 :

            gu8_Room_Water_Level = ROOM_LEVEL_ERROR;

            break;

        case 3 :

            gu8_Room_Water_Level = ROOM_LEVEL_FULL;

            break;

        default :
             //
            break;
    }

}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_drain_tank_level(void)
{
    /*..hui [24-11-13���� 3:59:49] �巹�� ���� ����..*/
    /*drain_level_power();*/

    /*..hui [17-12-15���� 10:08:42] �巹����ũ ������ �Է�..*/
    drain_tank_low_water_level_input();
    /*..hui [17-12-15���� 10:08:48] �巹����ũ ����� �Է�..*/
    drain_tank_high_water_level_input();
    /*..hui [17-12-15���� 10:08:55] �巹����ũ ���� ���� ����..*/
    drain_tank_water_level_confirm();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void drain_tank_low_water_level_input(void)
{
    if(pLEVEL_ICE_DRAIN_LOW == CLEAR)
    {
        u8drain_low_level_on_decision_cnt = 0;
        u8drain_low_level_off_decision_cnt++;

        if( u8drain_low_level_off_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
        {
            u8drain_low_level_off_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;

            if( F_drain_water_level_low == SET )
            {
                F_drain_water_level_low = CLEAR;
                send_wifi_system_function();
            }
            else{}
        }
        else{}
    }
    else
    {
        if( pLEVEL_ICE_DRAIN_LOW == SET )
        {
            u8drain_low_level_off_decision_cnt = 0;
            u8drain_low_level_on_decision_cnt++;

            if ( u8drain_low_level_on_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )
            {
                u8drain_low_level_on_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;

                if( F_drain_water_level_low == CLEAR )
                {
                    F_drain_water_level_low = SET;
                    send_wifi_system_function();
                }
                else{}
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
void drain_tank_high_water_level_input(void)
{
    U8 mu8_drain_detect_time = 0;

    /*..hui [23-10-23���� 2:10:22] �� �ܿ��� 2��..*/
    mu8_drain_detect_time = 20;


    #if 0
    if( bit_ice_tank_ster_start == SET )
    {
        /*..hui [23-10-23���� 2:10:12] �¼���ô�Ҷ��� 5��..*/
        mu8_drain_detect_time = 50;
    }
    else if( gu8_acid_clean_mode == ACID_CLEAN_PREPARE && gu8_acid_prepare_step == 4 )
    {
        /*..hui [24-7-30���� 5:16:18] �巹����ũ ������ ä�ﶧ�� 5��..*/
        mu8_drain_detect_time = 50;
    }
    else
    {
        /*..hui [23-10-23���� 2:10:22] �� �ܿ��� 2��..*/
        mu8_drain_detect_time = 20;
    }
    #endif

    #if 0
    /*..hui [24-11-13���� 4:00:55] �巹�� ���� ����..*/
    if( bit_drain_level_power_output == CLEAR )
    {
        /*..hui [24-7-26���� 5:37:14] 1�� ���� ���ȿ� �ʱ�ȭ ����.. �ٽ� ���� ���� �̾ ī�����ϵ���..*/
        /*u8drain_high_level_on_decision_cnt = 0;*/
        /*u8drain_high_level_off_decision_cnt = 0;*/
        return;
    }
    else{}
    #endif

    if(pLEVEL_ICE_DRAIN_HIGH == CLEAR)
    {
        u8drain_high_level_on_decision_cnt = 0;
        u8drain_high_level_off_decision_cnt++;

        /*if( u8drain_high_level_off_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )*/
        if( u8drain_high_level_off_decision_cnt >= mu8_drain_detect_time )
        {
            /*u8drain_high_level_off_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;*/
            u8drain_high_level_off_decision_cnt = mu8_drain_detect_time;

            if( F_drain_water_level_high == SET )
            {
                F_drain_water_level_high = CLEAR;
                send_wifi_system_function();
            }
            else{}
        }
        else{}
    }
    else
    {
        if( pLEVEL_ICE_DRAIN_HIGH == SET )
        {
            u8drain_high_level_off_decision_cnt = 0;
            u8drain_high_level_on_decision_cnt++;

            /*if ( u8drain_high_level_on_decision_cnt >= DRAIN_WATER_LEVEL_DETECT_TIME )*/
            if ( u8drain_high_level_on_decision_cnt >= mu8_drain_detect_time )
            {
                /*u8drain_high_level_on_decision_cnt = DRAIN_WATER_LEVEL_DETECT_TIME;*/
                u8drain_high_level_on_decision_cnt = mu8_drain_detect_time;

                if( F_drain_water_level_high == CLEAR )
                {
                    F_drain_water_level_high = SET;
                    send_wifi_system_function();
                }
                else{}
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
void drain_tank_water_level_confirm(void)
{
    U8 gu8water_levle_temp = 0;

    gu8water_levle_temp |= (U8)(F_drain_water_level_low);
    gu8water_levle_temp |= (U8)(F_drain_water_level_high << 1);


    switch(gu8water_levle_temp)
    {
        case 0 :

            u8DrainWaterLevel = DRAIN_LEVEL_EMPTY;

            break;


        case 1 :

            u8DrainWaterLevel = DRAIN_LEVEL_LOW;

            break;

        case 2 :

            u8DrainWaterLevel = DRAIN_LEVEL_ERROR;

            break;


        case 3 :

            u8DrainWaterLevel = DRAIN_LEVEL_HIGH;

            break;

        default :
             //
            break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


