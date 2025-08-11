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
#include    "input_ice_tray.h"



void input_ice_tray_micro_sw(void);

U16 gu16_ice_level_delay;
//----------------------------------------------------// �������̼���
U8 gu8IceLEV;
U8 gu8BeIceLEV;
U8 gu8IceTrayLEV;
U8 u8TestIceTrayDelay;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : Ice Tray Level
// ����         : �������� ����
//----------------------------------------------------------------------------
// ���       :  1.gu8IceTrayLEV = 0 : ������ġ
//               2.gu8IceTrayLEV = 1 : Ż����ġ
//
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
void input_ice_tray_micro_sw(void)
{
    if(gu16_ice_level_delay > 0)
    {
        gu16_ice_level_delay--;            // Ice Tray ������
    }
    else{}
	
    //============================================================ Ʈ���� ��ġ ����
    if(pICE_MICRO_SW_HIGH != SET && pICE_MICRO_SW_LOW == SET)
    {
        gu8IceLEV = ICE_TRAY_POSITION_ICE_THROW;            // Ż����ġ (2KG�� �ݴ�� �Ǿ�����)
    }
    else if(pICE_MICRO_SW_HIGH == SET && pICE_MICRO_SW_LOW != SET)
    {
        gu8IceLEV = ICE_TRAY_POSITION_ICE_MAKING;           // ������ġ (2KG�� �ݴ�� �Ǿ�����)
    }
    else if(pICE_MICRO_SW_HIGH == SET && pICE_MICRO_SW_LOW == SET)
    {
        gu8IceLEV = ICE_TRAY_POSITION_MOVING;        // �̵���
    }
    else if(pICE_MICRO_SW_HIGH != SET && pICE_MICRO_SW_LOW != SET)
    {
        gu8IceLEV = ICE_TRAY_POSITION_ERROR;        // ����
    }
    else{}

    if(gu8IceLEV != gu8BeIceLEV)
    {
        gu8BeIceLEV = gu8IceLEV;
        /*gu16_ice_level_delay = 30;*/           // Ʈ���̽ð�������
        /*gu16_ice_level_delay = 3;*/           // Ʈ���̽ð�������
        gu16_ice_level_delay = 7;           // Ʈ���̽ð�������

        return;
    }
    else{}

    if(gu16_ice_level_delay > 0)
    {
        return;
    }
    else{}

    gu8IceTrayLEV = gu8IceLEV;

    if(gu8IceTrayLEV == ICE_TRAY_POSITION_ERROR && Bit17_Tray_Micro_SW_Dual_Detect_Error__E61 != SET)
    {
        F_ErrTrayMotor_DualInital = 1;     // ���� ������ Tray M/S Error �ʱ�߻�
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


