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
#include    "auto_drain_manual.h"

void key_manual_drain(void);
void start_manual_drain(void);
void stop_manual_drain(void);

void manual_drain(void);
void manual_drain_pump_output(void);


bit bit_manual_drain_start;
U16 gu16_manual_drain_max_timer;


bit bit_manual_drain_pump_output;
bit bit_manual_drain_valve_output;
U8 gu8_before_manual_drain_level;
U16 gu16_manual_drain_op_timer;


U16 gu16_manual_drain_finish_timer;
U8 gu8_manual_drain_no_water_timer;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_manual_drain(void)
{
	if( bit_filter_all == CLEAR )
	{
        play_melody_warning_197();
        return;
	}
	else{}

    if( F_All_Lock == SET )
    {
        play_melody_warning_197();
        return;
    }
    else{}

    if( bit_memento_start == SET )
    {
        return;
    }
    else{}
        

    if( bit_manual_drain_start == CLEAR )
    {
        start_manual_drain();
    }
    else
    {
        stop_manual_drain();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_manual_drain(void)
{
    //
    if( bit_filter_all == CLEAR
    || Bit16_Drain_Pump_Error__E60 == SET
    || Bit3_Leakage_Sensor_Error__E01 == SET
    || F_DrainStatus == SET
    || F_WaterOut == SET )
    {
        play_melody_warning_197();
    }
    else
    {
        play_melody_setting_on_198();
        bit_manual_drain_start = SET;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_manual_drain(void)
{
    //
    play_melody_setting_off_199();
    bit_manual_drain_start = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_drain(void)
{
    //
    /*..hui [23-8-14���� 1:30:31] ������� ������ ���� �Ǵ� ���� ���� ������ ����..*/
    if( bit_manual_drain_start == SET )
    {
        if( bit_filter_all == CLEAR
            || Bit16_Drain_Pump_Error__E60 == SET
            || Bit3_Leakage_Sensor_Error__E01 == SET
            || F_DrainStatus == SET )

        {
            play_melody_warning_197();
            bit_manual_drain_start = CLEAR;
        }
        else{}
    }
    else{}

    if( bit_manual_drain_start == CLEAR )
    {
        gu16_manual_drain_max_timer = 0;
        bit_manual_drain_pump_output = CLEAR;
        bit_manual_drain_valve_output = CLEAR;
        gu8_before_manual_drain_level = DRAIN_LEVEL_EMPTY;
        gu16_manual_drain_op_timer = 0;
        gu16_manual_drain_finish_timer = 0;
        gu8_manual_drain_no_water_timer = 0;
    }
    else
    {
        gu16_manual_drain_max_timer++;

        /*..hui [23-8-14���� 11:43:15] ������� �ִ� ���۽ð��� �ִ� 1�ð�..*/
        /*if(gu16_manual_drain_max_timer >= MANUAL_DRAIN_MAX_TIME)*/
        if(gu16_manual_drain_max_timer >= 3000)
        {
            gu16_manual_drain_max_timer = 0;
            bit_manual_drain_pump_output = CLEAR;
            bit_manual_drain_valve_output = CLEAR;
            gu8_before_manual_drain_level = DRAIN_LEVEL_EMPTY;
            gu16_manual_drain_op_timer = 0;
            gu16_manual_drain_finish_timer = 0;
            gu8_manual_drain_no_water_timer = 0;

        	bit_manual_drain_start = CLEAR;
        }
        else
        {
            manual_drain_pump_output();
    		// bit_manual_drain_pump_output = CLEAR;
    		bit_manual_drain_valve_output = SET;
        }


	
        #if 0
        gu16_manual_drain_max_timer++;

        /*..hui [23-8-14���� 11:43:15] ������� �ִ� ���۽ð��� �ִ� 1�ð�..*/
        /*if(gu16_manual_drain_max_timer >= MANUAL_DRAIN_MAX_TIME)*/
        if(gu16_manual_drain_max_timer >= 6000)
        {
            gu16_manual_drain_max_timer = 0;
            bit_manual_drain_pump_output = CLEAR;
            bit_manual_drain_valve_output = CLEAR;
            gu8_before_manual_drain_level = DRAIN_LEVEL_EMPTY;
            gu16_manual_drain_op_timer = 0;
            gu16_manual_drain_finish_timer = 0;
            gu8_manual_drain_no_water_timer = 0;
        }
        else
        {
            manual_drain_pump_output();
        }
		#endif
    }
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void manual_drain_pump_output(void)
{

    /*..hui [23-8-14���� 4:17:30] �巹�� �ð� - ���������� ����..*/
    /* 600
       710
       757
       780
       775
       930
       930 */


    switch(u8DrainWaterLevel)
    {
        case DRAIN_LEVEL_EMPTY :

             bit_manual_drain_pump_output = CLEAR;
             bit_manual_drain_valve_output = SET;

             gu8_before_manual_drain_level = DRAIN_LEVEL_EMPTY;
             gu16_manual_drain_op_timer = 0;
             gu8_manual_drain_no_water_timer = 0;

			 gu16_manual_drain_finish_timer++;
			 
			 /*..hui [23-8-14���� 1:37:19] x�е��� �巹�ι�� �����µ� ������ �̻� ���� �ȵǸ� ����..*/
			 if( gu16_manual_drain_finish_timer >= MANUAL_DRAIN_FINISH_CHECK_TIME )
			 {
				 gu16_manual_drain_finish_timer = 0;
				 gu16_manual_drain_max_timer = MANUAL_DRAIN_MAX_TIME;
			 }
			 else{}

             #if 0
             /*..hui [23-8-14���� 2:04:53] �ü���ũ ������ �̰��� ���Ͽ����� Ȯ���ϵ���..*/
             if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
             {
                 gu16_manual_drain_finish_timer++;

                 /*..hui [23-8-14���� 1:37:19] x�е��� �巹�ι�� �����µ� ������ �̻� ���� �ȵǸ� ����..*/
                 if( gu16_manual_drain_finish_timer >= MANUAL_DRAIN_FINISH_CHECK_TIME )
                 {
                     gu16_manual_drain_finish_timer = 0;
                     gu16_manual_drain_max_timer = MANUAL_DRAIN_MAX_TIME;
                 }
                 else{}
             }
             else
             {
                 gu16_manual_drain_finish_timer = 0;
             }
			 #endif
			 

            break;

        case DRAIN_LEVEL_LOW :

             gu16_manual_drain_finish_timer = 0;

             /*..hui [18-1-14���� 6:06:23] ������ ���¿��� �ü� ������ ON ���·� ������ �����ϸ�..*/
             if(gu8_before_manual_drain_level == DRAIN_LEVEL_EMPTY)
             {
                 gu16_manual_drain_op_timer++;

                 /*..hui [18-1-14���� 6:06:47] 40�� �̻� �ü� ����ߴµ��� �������� �������� ���ϸ�..*/
                 /*..hui [18-1-14���� 6:07:00] �ٽ� �巹������ �����ؼ� �巹�� ����..*/
                 /*..hui [18-1-14���� 6:11:06] ���� ������, ���θ������� ������.. �����ũ ��ġ�� �ʰ� �ϱ�����..???..*/
                 if(gu16_manual_drain_op_timer >= DRAIN_VALVE_OPEN_TIME)
                 {
                     bit_manual_drain_pump_output = SET;
                     bit_manual_drain_valve_output = CLEAR;

                     /*..hui [18-1-25���� 4:11:59] �巹������ �������� ��ȯ�ϰ� 3���Ŀ� �ǵ�� Ȯ��..*/
                     if(gu16_manual_drain_op_timer >= DRAIN_VALVE_OPEN_TIME + 30)
                     {
                         /*..hui [18-1-25���� 4:12:27] �ǵ�� �����̸� �ٽ� �ü� ��� ON..*/
                         if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                         {
                             gu16_manual_drain_op_timer = 0;
                         }
                         else
                         {
                             /*..hui [18-1-25���� 4:12:45] �ǵ�� �ʰ��̸� �巹������ ON ���� ����..*/
                             gu16_manual_drain_op_timer = DRAIN_VALVE_OPEN_TIME + 30;
                         }
                     }
                     else{}
                 }
                 else
                 {
                     bit_manual_drain_pump_output = CLEAR;
                     bit_manual_drain_valve_output = SET;
                 }
             }
             else
             {
                 gu16_manual_drain_op_timer = 0;
                 /*..hui [18-1-14���� 6:15:33] ������ �����ǰ� �巹������ �����Ͽ� ���������� ����������..*/
                 /*..hui [18-1-14���� 6:21:04] �̰͵� ���� �������� ���� ������� ������ ���������� �� �ȳ�������..*/
                 /*..hui [18-1-14���� 6:21:55] �ٽ� �巹������ OFF�ϰ� �ü� ��� ON�Ͽ� �������� ������....*/
                 if(gu16_AD_Drain_Pump_Current <= DRAIN_COMPLETE_FEEDBACK)
                 {
                     gu8_manual_drain_no_water_timer++;

                     if( gu8_manual_drain_no_water_timer >= 100 )
                     {
                         gu8_manual_drain_no_water_timer = 100;
                         bit_manual_drain_pump_output = CLEAR;
                         bit_manual_drain_valve_output = SET;
                     }
                     else
                     {
                         bit_manual_drain_pump_output = SET;
                         bit_manual_drain_valve_output = CLEAR;
                     }
                 }
                 else
                 {
                     bit_manual_drain_pump_output = SET;
                     bit_manual_drain_valve_output = CLEAR;
                     gu8_manual_drain_no_water_timer = 0;
                 }
             }

            break;

        case DRAIN_LEVEL_ERROR :
        case DRAIN_LEVEL_HIGH :

             bit_manual_drain_pump_output = SET;
             bit_manual_drain_valve_output = CLEAR;
             gu8_before_manual_drain_level = DRAIN_LEVEL_HIGH;
             gu8_manual_drain_no_water_timer = 0;

            break;

        //=====================================================
        default :

             bit_manual_drain_pump_output = CLEAR;
             bit_manual_drain_valve_output = CLEAR;
             gu8_before_manual_drain_level = DRAIN_LEVEL_EMPTY;

            break;
      }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


