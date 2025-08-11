/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  : AT+CONNECT=74F07DB01010
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "display_breath.h"

void breath_control(void);



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void breath_control(void)
{
    #if 0
    if( gu8_Led_Display_Step == LED_Display__VERSION )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
    else if( gu8_Led_Display_Step == LE_DDisplay__FLUSHING )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__SLEEP )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
	else if( gu8_Led_Display_Step == LED_Display__MANUAL_DRAIN )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
    else if( gu8_Led_Display_Step == LED_Display__WIFI_PAIRING )
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
    else
    {
        Bit1_Animation_Dimming_Water_Extract_State = SET;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = SET;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = SET;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = SET;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = SET;
    }
    #endif

    if( gu8_Led_Display_Step == LED_Display__MAIN )
    {
        Bit1_Animation_Dimming_Water_Extract_State = SET;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = SET;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = SET;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = SET;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = SET;
    }
    else
    {
        Bit1_Animation_Dimming_Water_Extract_State = CLEAR;
        Bit0_Animation_Dimming_Ice_Extract_Outer_State = CLEAR;
        Bit7_Animation_Dimming_Ice_Extract_Inner_State = CLEAR;
        Bit2_Front_Under_Ice_Outer_Blue_Extract = CLEAR;
        Bit1_Front_Under_Ice_Inner_Blue_Extract = CLEAR;
    }
}



