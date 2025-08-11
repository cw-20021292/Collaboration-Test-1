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
#include    "hot_water_error.h"



void hot_water_error_check(void);
void check_error_room_overheat(void);

void check_error_hot_flow_block(void);
void check_error_hot_overheat(void);
void check_error_hot_low_water(void);

U8 gu8_hot_overheat_on_timer;
U8 gu8_hot_overheat_off_timer;


U16 gu16_hot_flow_block_err_chk_timer;
U16 gu16_hot_flow_block_err_clr_timer;

U16 gu16_hot_overheat_err_chk_timer;
U16 gu16_hot_overheat_err_clr_timer;


bit F_Hot_Temp_Much_Difference_State;

U8 gu8_room_overheat_on_timer;
U8 gu8_room_overheat_off_timer;

U16 gu16_hot_low_water_check_timer;
U16 gu16_hot_low_water_clear_timer;

bit bit_hot_overheat;
bit bit_hot_low_water;

U8 gu8_clear_hot_block_error;

bit F_hot_flow_error;           //cbr_test
U16 gu16_hot_low_flow_clear_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void hot_water_error_check(void)
{
    /*..hui [23-5-17���� 7:48:26] �¼� ���� ���� ����..*/
    /*check_error_hot_overheat();*/
    /*..sean [25-02-03] ���� Ÿ������ ���� ���� ����..*/
    /*check_error_room_overheat();*/
	/*.. sean [25-02-03] ����Ÿ�� �������� ���Ͽ� ���� ����..*/
	check_error_hot_flow_block();       /* �÷��� �¼���ũ ä��� �� FLOW BLOCK ���� */
    
    // check_error_hot_overheat();      /* �ʰ�¼� ������ �ӽ� ���� 250227 CH.PARK */

    check_error_hot_low_water();        /* �¼� ���� �� FLOW BLOCK ���� */
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_hot_flow_block(void)
{
    U8 u8_check_enable = CLEAR;
    U8 u8_block_error_fix = CLEAR;
    U8 mu8_err_check_time = 0;
    U8 mu8_err_check_hz = 0;

    return;     /* �̻�� [2025-07-08 ���� 2��38��] ����_����_SW ��� �޼��� Ȯ�� */
    
    /*..hui [21-8-31���� 9:36:51] ������ ������ �ȵ�....*/
    /*..hui [21-8-31���� 9:37:02] ���� �¼� �������?������ �������� ������ �ȵ�..*/
    /*..hui [21-8-31���� 9:37:14] �¼� �������?������ ù�� �巹�ν� ���������� �����ϴϱ� �׶� üũ..*/
    /*..hui [21-8-31���� 9:37:21] �������� �������� �Ǵ�.. ��¿ �� ����..*/
    if( F_First_Hot_Effluent == SET && bit_hot_filling_start == SET
        && (gu8_Hot_Filling_Step >= 3 && gu8_Hot_Filling_Step <= 6) )
    {
        /*..hui [19-8-28���� 7:20:26] ���� ��ä��⶧��?1��..*/
        /*..hui [20-2-13���� 2:44:23] �¼� ù���� 14Hz ���� 1�� �̻� ������ ���?�¼��������?�߻�..*/
        /*..hui [20-2-13���� 2:44:44] 5hz�� �� ����.. ���������� ���� ���� 12Hz���� ����..*/
        /*..hui [20-4-3���� 11:12:36] ù �� �巹�ζ��� ���� �������� 2�ʷ� ����..*/
        u8_check_enable = SET;
        //mu8_err_check_time = 30;
        mu8_err_check_time = 50;
        //mu8_err_check_hz = HOT_FIRST_BLOCKED_FLOW_HZ;
        mu8_err_check_hz = HOT_FIRST_BLOCKED_FLOW_HZ;
    }
    else
    {
        u8_check_enable = CLEAR;
    }


    if( u8_check_enable == SET )
    {
        if( Bit0_Hot_Water_Flow_Block_Error__E08 != SET )
        {
            /*..hui [19-8-28���� 7:15:10] 5Hz ������ ���?.*/
            /*if( gu8_Flow_1sec <= HOT_BLOCKED_FLOW_HZ )*/
            if( gu8_Flow_1sec <= mu8_err_check_hz )
            {
                gu16_hot_flow_block_err_chk_timer++;

                /*if(gu16_hot_flow_block_err_chk_timer >= HOT_FLOW_BLOCK_ERROR_CHECK_TIME)*/
                if(gu16_hot_flow_block_err_chk_timer >= mu8_err_check_time)
                {
                    Bit0_Hot_Water_Flow_Block_Error__E08 = SET;
					//�¼� �ܼ� �� ��������� ���� �߰� 25-06-12
                    Play_Voice(VOICE_7_CALL_AS_WATER_SUPPLY_ERROR);
                    gu16_hot_flow_block_err_chk_timer = 0;

	                gu16_firstEffluent_hotwater_timer = 0;	// �� 2025-06-10 Phil
	                F_firstEffluent_hotWater = CLEAR;				// �� 2025-06-10 Phil
	                F_firstEffluent_hotWaterHeat = CLEAR;
                }
                else{}
            }
            else
            {
                gu16_hot_flow_block_err_chk_timer = 0;
            }
        }
        else
        {
            gu16_hot_flow_block_err_chk_timer = 0;
        }
    }
    else
    {
        gu16_hot_flow_block_err_chk_timer = 0;
    }

    if(Bit0_Hot_Water_Flow_Block_Error__E08 == SET)
    {
        gu16_hot_flow_block_err_clr_timer++;

        if(gu16_hot_flow_block_err_clr_timer >= HOT_FLOW_BLOCK_ERROR_CLEAR_TIME)
        {
            Bit0_Hot_Water_Flow_Block_Error__E08 = CLEAR;
            gu16_hot_flow_block_err_clr_timer = 0;
        }
        else{}
    }
    else
    {
        gu16_hot_flow_block_err_clr_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_hot_overheat(void)
{
    U8 u8_check_enable = CLEAR;

    if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
    {
        /*..hui [20-12-24���� 9:57:00] ���� �߿��� �巹�ζ��� ���� ���ϰ� ���� ���� �����ϴ� ���������� Ȯ���ϵ��� ����..*/
        if( (gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE  && gu8_Preheat_Step >= 3)
            || gu8_Water_Out_Step == STATE_30_EXTRACT_VALVE_ON_STATE
            || gu8_Water_Out_Step == STATE_31_WATER_EXTRACT_STATE )
        {
            u8_check_enable = SET;
        }
        else
        {
            u8_check_enable = CLEAR;
        }
    }
    else
    {
        u8_check_enable = CLEAR;
    }

    if( u8_check_enable == SET )
    {
        if( Bit5_Hot_Heater_OverHeat_Error__E40 != SET )
        {
            if(gu8_Hot_Out_Temperature_One_Degree >= 102
               || gu8_Hot_Heater_Temperature_One_Degree >= 102)
            {
                gu16_hot_overheat_err_chk_timer++;

                if(gu16_hot_overheat_err_chk_timer >= HOT_OVERHEAT_ERROR_CHECK_TIME)
                {
                    Bit5_Hot_Heater_OverHeat_Error__E40 = SET;
                    gu16_hot_overheat_err_chk_timer = 0;

                    /*..hui [20-4-8���� 7:34:47] ���� ���� �߻� �� 10�ʵ��� �巹�� ���? �߰�..*/
                    bit_hot_overheat = SET;
                }
                else{}
            }
            else
            {
                gu16_hot_overheat_err_chk_timer = 0;
            }
        }
        else{}
    }
    else
    {
        gu16_hot_overheat_err_chk_timer = 0;
    }

    if(Bit5_Hot_Heater_OverHeat_Error__E40 == SET)
    {
        gu16_hot_overheat_err_clr_timer++;

        if(gu16_hot_overheat_err_clr_timer >= HOT_OVERHEAT_ERROR_CLEAR_TIME)
        {
            Bit5_Hot_Heater_OverHeat_Error__E40 = CLEAR;
            gu16_hot_overheat_err_clr_timer = 0;
        }
        else{}
    }
    else
    {
        gu16_hot_overheat_err_clr_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_hot_low_water(void)
{
    U8 u8_check_enable = CLEAR;
    U8 u8_block_error_fix = CLEAR;
    U8 mu8_err_check_time = 0;
    U8 mu8_err_check_hz = 0;

    if( gu8_flushing_mode == FLUSHING_FILL_HOT_TANK_STATE
        && F_First_Hot_Effluent == SET && bit_hot_filling_start == SET
        && (gu8_Hot_Filling_Step >= 3 && gu8_Hot_Filling_Step <= 6) )
    {
        /*..hui [19-8-28���� 7:20:26] ���� ��ä��⶧�� 1��..*/
        /*..hui [20-2-13���� 2:44:23] �¼� ù���� 14Hz ���� 1�� �̻� ������ ��� �¼�������� �߻�..*/
        /*..hui [20-2-13���� 2:44:44] 5hz�� �� ����.. ���������� ���� ���� 12Hz���� ����..*/
        /*..hui [20-4-3���� 11:12:36] ù �� �巹�ζ��� ���� �������� 2�ʷ� ����..*/
        u8_check_enable = SET;
        mu8_err_check_time = 50;
        mu8_err_check_hz = HOT_FIRST_BLOCKED_FLOW_HZ;
    }
    else if(F_WaterOut == SET && u8WaterOutState == HOT_WATER_SELECT)
    {
        /******************************************************************************************************/
        if( gu8_Water_Out_Step == STATE_20_HOT_PRE_HEATING_STATE
            && (gu8_Preheat_Step >= 1  && gu8_Preheat_Step <= 2)
            && gu8_preheat_max_timer >= 10)
        {
            /*..hui [19-8-29���� 11:12:58] ���� �� ���� 1�� ���ĺ��� ����..*/
            /*..hui [19-8-28���� 7:17:20] �ʱ� �����߿��� 1.0��..*/
            u8_check_enable = SET;
            mu8_err_check_time = 20;

            if(bit_Holding_Flow_Block_Error__E08) {u8_check_enable = CLEAR;} // ��2025-06-02 Phil
            /*..hui [20-4-3���� 11:17:19] ���� ���� ���� �� 5hz �̻� Ȯ��..*/
            mu8_err_check_hz = HOT_BLOCKED_FLOW_HZ;
        }
        else if( gu8_Water_Out_Step == STATE_30_EXTRACT_VALVE_ON_STATE
                 || gu8_Water_Out_Step == STATE_31_WATER_EXTRACT_STATE
                 || gu8_Water_Out_Step == STATE_32_WATER_AIR_VENT_STATE )
        {
            /*..hui [19-8-28���� 7:17:29] ���� �����߿��� 1.5��..*/
            u8_check_enable = SET;
            mu8_err_check_time = 15;

            /*mu8_err_check_hz = HOT_BLOCKED_FLOW_HZ;*/
            /*..hui [21-11-9���� 9:46:53] �������� ���� ������ ���� ���� �������϶��� 0.2lpm���� ����..*/
            mu8_err_check_hz = HOT_FIRST_BLOCKED_FLOW_HZ;
        }
        else{}
    }
    	else if( bit_ice_tank_ster_start == SET )
    {
        if( gu8_ice_ster_mode == STER_MODE_HOT_PREHEAT )
        {
            if( gu8_preheat_ster_step >= 3 )
            {
                u8_check_enable = SET;
                mu8_err_check_time = 20;
                mu8_err_check_hz = HOT_BLOCKED_FLOW_HZ;
            }
            else{}
        }
        else if( gu8_ice_ster_mode == STER_MODE_HOT_INPUT_STATE )
        {
            if( gu8_hot_input_ster_step <= 2 )
            {
                u8_check_enable = SET;
                mu8_err_check_time = 20;
                mu8_err_check_hz = HOT_BLOCKED_FLOW_HZ;
            }
            else{}
        }
        else{}
    }
    else
    {
        u8_check_enable = CLEAR;
    }


    if( u8_check_enable == SET )
    {
        if( Bit0_Hot_Water_Flow_Block_Error__E08 != SET )
        {
            if( gu8_Flow_1sec <= mu8_err_check_hz )
            {
                gu16_hot_low_water_check_timer++;

                if( gu16_hot_low_water_check_timer >= mu8_err_check_time )
                {
                    Bit0_Hot_Water_Flow_Block_Error__E08 = SET;
					//�¼� �ܼ� �� ��������� ���� �߰� 25-06-12
					F_hot_flow_error = SET; //cbr_test
					//������ �����ɷ��� ���� ���� �ȵǴ� ���� ����
	            	F_WaterOut = CLEAR;
                    Play_Voice(VOICE_7_CALL_AS_WATER_SUPPLY_ERROR);
                    gu16_hot_low_water_check_timer = 0;
                }
                else{}
            }
            else
            {
                gu16_hot_low_water_check_timer = 0;
				/*..sean [25-07-08] �����׸��ý� �����ϱ� ���ؼ� ���� Ÿ�̸� ��..*/
            	gu16_hot_low_flow_clear_timer++;
            	if(gu16_hot_low_flow_clear_timer >= mu8_err_check_time)
            	{
                	F_hot_flow_error = CLEAR;   //cbr_test
                	gu16_hot_low_flow_clear_timer = 0;
            	}
				else {}
            }
        }
        else
        {
            gu16_hot_low_water_check_timer = 0;
            //cbr_test
            if( (gu8_Flow_1sec > mu8_err_check_hz) && ( u8WaterOutState == HOT_WATER_SELECT ) )
            {
            	gu16_hot_low_flow_clear_timer++;
            	if(gu16_hot_low_flow_clear_timer >= mu8_err_check_time)
            	{
                	F_hot_flow_error = CLEAR;   //cbr_test
                	gu16_hot_low_flow_clear_timer = 0;
            	}
				else {}
            }//cbr_test
            else {}
        }
    }
    else
    {
        gu16_hot_low_water_check_timer = 0;
    }

    if(gu8_clear_hot_block_error == SET)
    {
        gu8_clear_hot_block_error = CLEAR;
        gu16_hot_low_water_clear_timer = HOT_LOW_WATER0_CLEAR_TIME;
    }
    else{}

    if(Bit0_Hot_Water_Flow_Block_Error__E08 == SET)
    {
        gu16_hot_low_water_clear_timer++;

        if(gu16_hot_low_water_clear_timer >= HOT_LOW_WATER0_CLEAR_TIME)
        {
            Bit0_Hot_Water_Flow_Block_Error__E08 = CLEAR;
            gu16_hot_low_water_clear_timer = 0;
        }
        else{}
		
        //cbr_test
        if( (gu8_Flow_1sec > mu8_err_check_hz) && ( u8WaterOutState == HOT_WATER_SELECT ) )
        {
        	gu16_hot_low_flow_clear_timer++;
        	if(gu16_hot_low_flow_clear_timer >= mu8_err_check_time)
        	{
            	F_hot_flow_error = CLEAR;   //cbr_test
            	gu16_hot_low_flow_clear_timer = 0;
        	}
			else {}
        }//cbr_test
        else {}
    }
    else
    {
        gu16_hot_low_water_clear_timer = 0;
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_room_overheat(void)
{
#if 0
    if( Bit2_Room_Temp_Open_Short_Error__E42 == SET )
    {
        Bit1_Room_OverHeat_Error__E49 = CLEAR;
        gu8_room_overheat_off_timer = 0;
        gu8_room_overheat_on_timer = 0;
        return;
    }
    else{}

    if( gu8_Room_Temperature_One_Degree >= ROOM_OVERHEAT_ERROR_TEMP )
    {
        gu8_room_overheat_off_timer = 0;
        gu8_room_overheat_on_timer++;

        if( gu8_room_overheat_on_timer >= ROOM_OVERHEAT_ERROR_CHECK_TIME )
        {
            gu8_room_overheat_on_timer = ROOM_OVERHEAT_ERROR_CHECK_TIME;
            Bit1_Room_OverHeat_Error__E49 = SET;
        }
        else{}
    }
    else
    {
        gu8_room_overheat_on_timer = 0;

        if( gu8_Room_Temperature_One_Degree <= ROOM_OVERHEAT_CLEAR_TEMP )
        {
            gu8_room_overheat_off_timer++;

            if( gu8_room_overheat_off_timer >= ROOM_OVERHEAT_ERROR_CHECK_TIME )
            {
                gu8_room_overheat_off_timer = ROOM_OVERHEAT_ERROR_CHECK_TIME;
                Bit1_Room_OverHeat_Error__E49 = CLEAR;
            }
            else{}
        }
        else
        {
            gu8_room_overheat_off_timer = 0;
        }
    }
#endif
}

