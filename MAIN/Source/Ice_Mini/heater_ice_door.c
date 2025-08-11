
/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : heater_ice_door.c
* Device(s)    : R5F100SJ
* Creation Date: 2025/02/28
* Copyright    : Coway_Electronics Engineering Team (CH.Park)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "heater_ice_door.h"
/**********************************************************************************************************************/
void OUTPUT_HEATER_ICE_DOOR(void);
/**********************************************************************************************************************/
TYPE_BYTE          U8HEATERIceDoorONB;
#define            u8HEATIceDoorON                        U8HEATERIceDoorONB.byte
#define            Bit0_Ice_Enable_State                  U8HEATERIceDoorONB.Bit.b0
#define            Bit1_Ice_Making_State                  U8HEATERIceDoorONB.Bit.b1

TYPE_BYTE          U8HEATERIceDoorOFFB;
#define            u8HEATIceDoorOFF                       U8HEATERIceDoorOFFB.byte
#define            Bit0_Ice_Out_H_Off_State               U8HEATERIceDoorOFFB.Bit.b0
/**********************************************************************************************************************/
bit Bit_IceDoor_Heater_Output;                          /* ��������� ���� ��� ��Ȳ */
U8  U8_Door_Heater_No_FB_Detect_Timer_100ms = CLEAR;    /* ��������� ���� �����ǵ�� ���� ���� Ÿ�̸� */
U8  U8_Door_Heater_No_FB_Clear_Timer_100ms = CLEAR;     /* ��������� ���� �����ǵ�� ���� ���� Ÿ�̸� */
U8  U8_Door_Heater_No_FB_Start_Timer_100ms = CLEAR;     /* ��������� ���� �����ǵ�� �Ǵ� ���� Ÿ�̸� */
U8  gu8_ice_on_door_heater_op_timer_100ms  = CLEAR;     /* �������� ���� ���� ���� 10�� */
/**********************************************************************************************************************/
extern ICE_STEP gu8IceStep;
/**********************************************************************************************************************/

/**
 * @brief ���� ���� ���� ���� �ǵ�� Ȯ�� �Լ�
 * 
 */
void    DETECT_ICE_DOOR_HEATER_NO_FB(void);

/**********************************************************************************************************************/
/**
 * @brief ���̽� ���� ���漭 ���� ���� ���� �Լ�
 * 
 */
void OUTPUT_HEATER_ICE_DOOR(void)
{
    if( bit_self_test_start == SET )
    {
        return;
    }
    else{}

    Bit0_Ice_Enable_State = F_IceOn;

    /* �������� ���� �� 250618 CH.PARK */
    if((gu8IceStep >= STATE_11_WAIT_ROOM_WATER_FULL)
    && (gu8IceStep <= STATE_50_ICE_FULL_IR_CHECK)
    )
    {
        Bit1_Ice_Making_State = SET;
    }
    else
    {
        Bit1_Ice_Making_State = CLEAR;
    }
    
    // /* (�ӽ�) ���������� ���� �ӽ������� ���� OFF */
    // if(F_IceOut == SET)
    // {
    //     Bit0_Ice_Out_H_Off_State = SET;
    // }
    // else
    // {
    //     Bit0_Ice_Out_H_Off_State = CLEAR;
    // }
    
    /* ----------------------------------- */
    if(u8HEATIceDoorOFF > CLEAR)
    {
        pHEATER_ICE_DOOR = CLEAR;
        Bit_IceDoor_Heater_Output = CLEAR;
    }
    else
    {
        if(u8HEATIceDoorON > CLEAR)
        {
            pHEATER_ICE_DOOR = SET;
            Bit_IceDoor_Heater_Output = SET;
        }
        else
        {
            pHEATER_ICE_DOOR = CLEAR;
            Bit_IceDoor_Heater_Output = CLEAR;
        }
    }

    DETECT_ICE_DOOR_HEATER_NO_FB();
}

/**********************************************************************************************************************/
/**
 * @brief ���� ���� ���� ���� �ǵ�� Ȯ�� �Լ�
 * 
 */
void    DETECT_ICE_DOOR_HEATER_NO_FB(void)
{
    if(Bit_IceDoor_Heater_Output == SET)
    {
        U8_Door_Heater_No_FB_Start_Timer_100ms++;
        /* ���� ���� �� 3�� ���ĺ��� ���� ���� (AD�� ����ȭ) 250228 CH.PARK */
        if(U8_Door_Heater_No_FB_Start_Timer_100ms >= 3)
        {
            U8_Door_Heater_No_FB_Start_Timer_100ms = 3;

            /* ���� AD�� ���Ϸ� �����Ǹ� ���� ī��Ʈ ���� 250228 CH.PARK */
            if(gu16_AD_Result_IceDoor_Heater_Current <= ICE_DOOR_HEATER_FB_AD)
            {
                U8_Door_Heater_No_FB_Clear_Timer_100ms = CLEAR;

                U8_Door_Heater_No_FB_Detect_Timer_100ms++;
                if(U8_Door_Heater_No_FB_Detect_Timer_100ms >= 100)
                {
                    U8_Door_Heater_No_FB_Detect_Timer_100ms = 100;
                    // ���� �߻�
                }
                else {  }
            }
            else
            {
                U8_Door_Heater_No_FB_Detect_Timer_100ms = CLEAR;

                U8_Door_Heater_No_FB_Clear_Timer_100ms++;
                if(U8_Door_Heater_No_FB_Clear_Timer_100ms >= 100)
                {
                    U8_Door_Heater_No_FB_Clear_Timer_100ms = 100;
                    // ���� ����
                }
                else {  }
            }
        }
    }
    else
    {
        U8_Door_Heater_No_FB_Start_Timer_100ms = CLEAR;
        U8_Door_Heater_No_FB_Detect_Timer_100ms = CLEAR;
        U8_Door_Heater_No_FB_Clear_Timer_100ms = CLEAR;
    }
}
/**********************************************************************************************************************/
