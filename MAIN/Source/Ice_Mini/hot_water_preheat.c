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
#include    "hot_water_preheat.h"


U8 preheat_water(void);
void control_hot_flow(void);


U8 gu8_Preheat_Step;
U8 gu8_preheat_max_timer;
U8 gu8_preheat_timer;

U8 gu8_preheat_max_time;
U8 gu8_preheat_drain_max_timer;
U8 gu8_preheat_Closed_max_timer;		// ��2025-06-02 Phil

bit bit_re_hot;

U8 gu8_pre_heater_temp;
U8 gu8_pre_timer;

U8 gu8_test_timer;

U8 gu8_drain_max_flow;
U8 gu8_drain_max_flow_before;

U8 u8_drain_test_time;

bit bit_Hot_InLowTemp_SetHighTemp;											// ��2025-06-11 Phil
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
// [25-05-23 16:46:01] yspark
U8 gu8Pre_hot_setting_temperature = 0;

U8 mu8_coffee_time;
U8 gu8_additionalHeatingTime;
extern bit F_firstEffluent_hotWater;

U8 preheat_water(void)
{
    U8 mu8_return = CLEAR;
    U8 mu8_temp = 0;
    U8 mu8_preheat_ref_temp = 0;
	//for check
    //U8 mu8_coffee_time = 0;
    U8 mu8_buf = 0;
    U8 mu8_max_time = 0;
    U8 mu8_safety_temp = 0;
    U8 mu8_safety_time = 0;

    if(gu8_Preheat_Step >= STATE_1_PREHEAT_CHECK_OUTAGE_STATE 
		&& gu8_Preheat_Step <= STATE_3_PREHEAT_CHECK_TIME)
    {   
        gu8_preheat_max_timer++;

        // [25-05-23 17:03:45] yspark, 95�� �̻� �� �ٷ� ����
		// ���� �µ����� �� ����� ���� ����Ƿ� ����ó�� �߰��ؾ��� 
//        if (gu8_Hot_Heater_Temperature_One_Degree >= 95)
			/*..sean [25-07-07] �ܼ� ���ǿ��� ���õǴ� ���� ����..*/
        //if ((gu8_Hot_Heater_Temperature_One_Degree >= 95) && ( gu8_hot_setting_temperature >= HOT_SET_TEMP____80oC ))		// ��2025-06-08 Phil 
        if ((gu8_Hot_Heater_Temperature_One_Degree >= 95) 
			&& ( gu8_hot_setting_temperature >= HOT_SET_TEMP____70oC ))
			// && ( F_firstEffluent_hotWaterHeat == SET ))		            //2025-07-15 cbr 100�� ���� 30�� �� ������ �� �������� �ȵǹǷ� �����߻�
        {
            gu8_preheat_max_timer = 0;
            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;         
        }
        // [25-05-23 16:46:30] ysaprk, ù�� �� ���� �µ� �����̸� ���� �ܰ� ��ŵ, �巹�� �� �������� �ٷ� ����
        else if (F_firstEffluent_hotWater && (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature))
        {
            gu8_preheat_max_timer = 0;
            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;            
        }
// ��2025-06-08 Phil 
// 100�� -> 45�� �µ� ���̰� ���� ���� ���� �µ� ���� ����
//        // [25-06-05 17:03:45] cbr, 45�� ���� 45�� �̻� �� �ٷ� ����
//        else if( (gu8_Hot_Heater_Temperature_One_Degree >= 45) && ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
//        {
//            gu8_preheat_max_timer = 0;
//            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;         
//        }
// 
//        // [25-05-23 17:03:45] yspark, 95�� �̻� �� �ٷ� ����
//        else if (gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp)
//        {
//            gu8_preheat_max_timer = 0;
//            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;         
//        }
// ��2025-06-08 Phil
		else if(gu8_preheat_max_timer >= gu8_preheat_max_time)
        {
            gu8_preheat_max_timer = 0;
            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
        }
        else{}
        

    }
    else{}
	
//    bit_Hot_InLowTemp_SetHighTemp = 0; // ��2025-06-11 Phil (Ŭ���� �ʱ�ȭ�� ����)

    switch( gu8_Preheat_Step )
    {
        case STATE_0_PREHEAT_PREPARE_STATE : // ���� �ִ� �ð� ���� �ܰ�			
			bit_Hot_InLowTemp_SetHighTemp = 0; // ��2025-06-11 Phil (Ŭ���� �ʱ�ȭ�� ����)

            //if( gu8_Hot_In_Temperature_One_Degree <= 15 )
            if( gu8_Hot_In_Temperature_One_Degree < 10 )
            {
                if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                {
    				/*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
                    {
                        // [25-02-21 13:27:28] yspark, 100���� �����ϰ� ����
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						// ��2025-06-11 Phil	
                    	if( gu8_Hot_In_Temperature_One_Degree <= 25 )
                    	{
	                        bit_Hot_InLowTemp_SetHighTemp = 1;
	                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
						// ��2025-06-11 Phil
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC )
                    {
                        // [25-02-21 13:27:28] yspark, 100���� �����ϰ� ����
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                }
                else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
                {
                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 25;
                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 28;
                	/*.. sean [25-03-28] 100�� �ִ�ð� �߰� ..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
                            || (gu8_hot_setting_temperature == HOT_SET_TEMP____80oC) )  //2025-07-28 cbr
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      // ��2025-06-11 Phil	
						if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                      // ��2025-06-11 Phil
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC)
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        if( gu8_Hot_Heater_Temperature_One_Degree <= 25 )
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
                        else
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
                    }
                }
                else 
                {
                	/*.. sean [25-03-28] 100�� �ִ�ð� �߰� ..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      // ��2025-06-11 Phil	
						if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                      // ��2025-06-11 Phil
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC)
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        if( gu8_Hot_Heater_Temperature_One_Degree <= 25 )
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
						/*
                        if( gu8_Hot_Heater_Temperature_One_Degree <= 10 )
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
						*/
                        else
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                        }
                    }
                }
            }

            //if( gu8_Hot_In_Temperature_One_Degree <= 15 )
            else if( gu8_Hot_In_Temperature_One_Degree <= 15 )
            {
                if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                {
    				/*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        bit_Hot_InLowTemp_SetHighTemp = 1;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;  // �� 2025-06-11 Phil 
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
                    {
                        // [25-02-21 13:27:28] yspark, 100���� �����ϰ� ����
                        // gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      // ��2025-06-11 Phil	
						if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							// gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;          //2025-07-22 cbr
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                      // ��2025-06-11 Phil
                    
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                }
                else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
                {
                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 25;
                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 28;
                	/*.. sean [25-03-28] 100�� �ִ�ð� �߰� ..*/
    				/*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 35;
                        ///[25-05-13] sean ������ ��� ����
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      // ��2025-06-11 Phil	
						if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                      // ��2025-06-11 Phil
                    }
                    else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____80oC) )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 30;
                        ///[25-05-13] sean ������ ��� ����
                        // gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        //2025-07-28 cbr
                        if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        if( gu8_Hot_Heater_Temperature_One_Degree <= 25 )
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
                        else
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                        }
                    }
                }
                else
                {
                	/*.. sean [25-03-28] 100�� �ִ�ð� �߰� ..*/
    				/*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
                    if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )
                    {
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 90;
                        //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 77;
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
                    {
                      	//gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      // ��2025-06-11 Phil	
						if( gu8_Hot_In_Temperature_One_Degree <= 25 )
						{
							bit_Hot_InLowTemp_SetHighTemp = 1;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
						}
						else
						{
							bit_Hot_InLowTemp_SetHighTemp = 0;
							gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
						}
                      // ��2025-06-11 Phil
                    }
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC)
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    }
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
                    else
                    {
                        if( gu8_Hot_Heater_Temperature_One_Degree <= 25 )
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                        }
                        else
                        {
                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                        }
                    }
                }
            }
            else if( gu8_Hot_In_Temperature_One_Degree <= 27 )//( gu8_Hot_In_Temperature_One_Degree > 15 )
            {
                if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                {
// �� 2025-06-09 Phil  
//                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 20;
//                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 25;
//                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 30;
//                    gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    if (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____95oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____90oC)
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                    }
// �� 2025-06-09 Phil  
                }
                else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
                {
//// �� 2025-06-09 Phil  
////                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 18;
////                    //gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 25;
////                    gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
//                    if (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC
//                      || gu8_hot_setting_temperature == HOT_SET_TEMP____95oC
//                      || gu8_hot_setting_temperature == HOT_SET_TEMP____90oC)
//                    {
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
//                    }
//                    else
//                    {
//                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
//                    }
//// �� 2025-06-09 Phil  
//// �� 2025-06-11 Phil  
                    if (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____95oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____90oC)
                    {
// ��2025-06-11 Phil after PM
//                      if( gu8_Hot_In_Temperature_One_Degree <= 25 )
//                        {
//                        	  bit_Hot_InLowTemp_SetHighTemp = 1;
//                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;
//                        }
//                        else
//                        {
//                        	  bit_Hot_InLowTemp_SetHighTemp = 0;
//                            gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
//                        }
													gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
// ��2025-06-11 Phil after PM
					}
					else if (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC)
					{
					  if( gu8_Hot_In_Temperature_One_Degree <= 25 )
					    {
					    	  bit_Hot_InLowTemp_SetHighTemp = 1;
					        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW;
					    }
					    else
					    {
					    	  bit_Hot_InLowTemp_SetHighTemp = 0;
					        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
					    }
					}
                    // ��2025-06-11 Phil after PM
                    else if( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC )
                    {
                    	if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                    	{
                        bit_Hot_InLowTemp_SetHighTemp = 1;										// ��� ���� �Ŀ��� Drain 3�ʷ� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                      else
                      {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                      }
                    }
                    // ��2025-06-11 Phil after PM
					else
					{
					    bit_Hot_InLowTemp_SetHighTemp = 0;
					    gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
					}
                   
// �� 2025-06-11 Phil 
                }
                else
                {
// �� 2025-06-09 Phil  
//                    gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    if (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____95oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____90oC)
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                    }
// �� 2025-06-09 Phil  
                }

            }
            else
            {
                //if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                if(u16Heater_Power_Save <= HEATER_POWER_HIGH)					// �� 2025-06-09 Phil  
                {
                    if (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____95oC
                      || gu8_hot_setting_temperature == HOT_SET_TEMP____90oC)
                    {
						//������ ���Լ� �µ����������� 20�ʱ��� �÷�����. �׽�Ʈ �� ���� ����
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 50;
                    }
                    else
                    {
                        gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG;
                    }
                }
                else
                {
                    gu8_preheat_max_time = PRE_HEAT_MAX_TIME_LONG + 0;
                    // gu8_preheat_max_time = PRE_HEAT_MAX_TIME_FIRST_LOW + 50;    //2025-07-23 cbr
                    // bit_Hot_InLowTemp_SetHighTemp = 1;                  //2025-07-23 cbr 30�� ������ ������
                }
            }

            gu8_preheat_timer = 0;
            gu8_preheat_max_timer = 0;
            gu8_drain_max_flow = 0;
            gu8_preheat_drain_max_timer = 0;
            gu8_preheat_Closed_max_timer = 0;		// ��2025-06-02 Phil
            bit_Holding_Flow_Block_Error__E08 = 0;// ��2025-06-02 Phil

            /*..hui [21-8-4���� 5:08:19] �������? ������ �����?.. �̰� �� �ð��� ���Խ�Ű�� �ʴ´�..*/
			//flow �ʿ� �߰� �� ���� ���� ****
			//if(1)
            if( gu8_hot_flow_mode == FLOW_MODE_NONE  )
            {
                gu8_Preheat_Step++;
            }
            else{}

            gu8_pre_heater_temp = gu8_Hot_Heater_Temperature_One_Degree;

            break;

        case STATE_1_PREHEAT_CHECK_OUTAGE_STATE :
            // �巹�� ���� �Ǵ� �ܰ�
            if(gu8_Flow_1sec > HOT_BLOCKED_FLOW_HZ)
            {
                gu8_preheat_timer++;

                /*if(gu8_preheat_timer >= 9)*/
                /*..hui [20-1-22���� 12:51:11] ���þ��� �巹�νð� 2�ʷ� ����..*/
                /*..hui [20-1-22���� 12:51:23] �����ѻ� ���� �Ҽհ��� ��������..*/
                /*if(gu8_preheat_timer >= 17)*/
                //if(gu8_preheat_timer >= 3)
                //if(gu8_preheat_timer >= 3)
                //if(gu8_preheat_timer >= 10)
                if(gu8_preheat_timer >= 5)		// �� 2025-06-11 Phil 
                {
                    gu8_preheat_timer = 0;
                    gu8_Preheat_Step++;
                }
                else{}

                if( gu8_drain_max_flow < gu8_Flow_1sec )
                {
                    gu8_drain_max_flow = gu8_Flow_1sec;
                }
                else{}
            }
            else
            {
                /*..hui [19-1-18���� 9:54:28] �¼� �ܼ� ���� �߻� ���..*/
                gu8_preheat_timer = 0;
            }

            break;

        case STATE_2_PREHEAT_DRAIN_STATE :
            // �巹�� �ܰ�
            gu8_preheat_drain_max_timer++;
            if(gu8_preheat_Closed_max_timer < 200) gu8_preheat_Closed_max_timer++;		// ��2025-06-02 Phil

            if ( (gu8_hot_setting_temperature == HOT_SET_TEMP____55oC)
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____45oC ) )
            {
                if (gu8_Hot_Heater_Temperature_One_Degree >= 80)
                {
                    mu8_max_time = 90;
                }
                else if (gu8_Hot_Heater_Temperature_One_Degree >= 70)
                {
                    mu8_max_time = 80;
                }
                else if (gu8_Hot_Heater_Temperature_One_Degree >= 60)
                {
                    mu8_max_time = 50;
                }
                else if (gu8_Hot_Heater_Temperature_One_Degree >= 50)
                {
                    mu8_max_time = 10;
                }
            }
            else if ( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
            {
                if (gu8_Hot_Heater_Temperature_One_Degree >= 80)
                {
                    mu8_max_time = 30;
                }
            }
			/*..sean �߰� ..*/
            else if ( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
            {
                if (gu8_Hot_Heater_Temperature_One_Degree >= 80)
                {
                    mu8_max_time = 10;
                }
				else {}
            }
   			 /*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
            else if ( ( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) )
            {
            	//�µ� ���� �߸� ���� �Ǿ� �־� ����
                if (gu8_Hot_Heater_Temperature_One_Degree >= 96)
                {
                    mu8_max_time = 5;
                }
                else if (gu8_Hot_Heater_Temperature_One_Degree >= 90)
                {
                    mu8_max_time = 1;
                }
				else {}
#if 0
                if (gu8_Hot_Heater_Temperature_One_Degree >= 80)
                {
                    mu8_max_time = 1;
                }
                else if (gu8_Hot_Heater_Temperature_One_Degree >= 90)
                {
                    mu8_max_time = 10;
                }
				else {}
#endif
            }
			else {}
#if 0
            else if( gu8_Hot_In_Temperature_One_Degree <= 15 )
            {
                if( gu8_pre_heater_temp >= 80 )
                {
                    mu8_max_time = 30;

                }
                else if( gu8_pre_heater_temp >= 60 )
                {
                    mu8_max_time = 10;
                }
                else
                {
                    mu8_max_time = 8;
                }
            }
            else if( gu8_Hot_In_Temperature_One_Degree <= 25 )
            {
                if( gu8_pre_heater_temp >= 80 )
                {
                    mu8_max_time = 60;
                }
                else if( gu8_pre_heater_temp >= 60 )
                {
                    mu8_max_time = 30;
                }
                else
                {
                    mu8_max_time = 10;
                }
            }
            else
            {
                if( gu8_pre_heater_temp >= 80 )
                {
                    mu8_max_time = 60;
                }
                else if( gu8_pre_heater_temp >= 60 )
                {
                    mu8_max_time = 30;
                }
                else
                {
                    mu8_max_time = 20;
                }
            }
#endif
			u8_drain_test_time = mu8_max_time;
            
            /*..hui [21-2-19���� 10:00:30] �巹�� �ִ�ð� 1.5�ʷ� ����..*/
            if( gu8_preheat_drain_max_timer >= mu8_max_time )
            {
                gu8_preheat_drain_max_timer = mu8_max_time;
            }
            else{}

            // [25-02-21 09:42:31] yspark, 100�� �߰�, ù�� �������� �ð� ����
    		/*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
            if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
            {
                mu8_temp = 0;

                //if( gu8_pre_heater_temp >= 60)					
                if( gu8_pre_heater_temp >= 80)
                {
                    gu8_additionalHeatingTime = 0;
                    bit_re_hot = SET;
                }
                else
                {
                    //gu8_additionalHeatingTime = 100;
                    gu8_additionalHeatingTime = 80;		// ��2025-06-02 Phil
                    bit_re_hot = CLEAR;
                }
            }
			
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
            {
                mu8_temp = 0;

                if( gu8_pre_heater_temp >= 60)
                {
                    gu8_additionalHeatingTime = 0;
                    bit_re_hot = SET;
                }
                else
                {
                    //gu8_additionalHeatingTime = 100;
                    gu8_additionalHeatingTime = 80;		// ��2025-06-02 Phil
                    bit_re_hot = CLEAR;
                }
            }

            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
            {
                mu8_temp = 8;

                if( gu8_pre_heater_temp >= gu8_Hot_Preheat_Temp - 10 )
                {
                    gu8_additionalHeatingTime = 3;
                    bit_re_hot = SET;
                }
                else
                {
                    gu8_additionalHeatingTime = 3;
                    bit_re_hot = CLEAR;
                }
            }
            else
            {
                mu8_temp = 5;

                if( gu8_pre_heater_temp >= gu8_Hot_Preheat_Temp  + 5 )
                {
                    gu8_additionalHeatingTime = 3;
                    bit_re_hot = SET;
                }
                else
                {
                    gu8_additionalHeatingTime = 3;
                    bit_re_hot = CLEAR;
                }
            }
            //�̵� 
            if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            {
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 12 )					
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 5  || gu8_Hot_Heater_Temperature_One_Degree >= 99)
		        if (( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 5) && (gu8_Hot_Heater_Temperature_One_Degree <= gu8_Hot_Preheat_Temp + 10)  // ��2025-06-08 Phil
		        || gu8_Hot_Heater_Temperature_One_Degree >= 99) 																																																	// ��2025-06-08 Phil
		        {
		        	/* sean [25-05-08] ���� ���ϰ� ����������, ����������갡 ���� �ȵǾ����� �� �־� �Ϸ� �Ŀ� ���� skip�ϵ��� ���� */
		            //if (gu16_moving_pulse == 0)
		            // if (1)   //2025-07-03 cbr
                    if (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature)  //2025-07-03 cbr
		            {
			            gu8_preheat_max_timer = 0;
			            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		            }
		            //gu8_preheat_max_timer = 0;
		            //gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		        }
				else {}
            }
            else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
            {
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 12 )				
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 3 || gu8_Hot_Heater_Temperature_One_Degree >= 99)
		        if (( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 3) && (gu8_Hot_Heater_Temperature_One_Degree <= gu8_Hot_Preheat_Temp + 10)  // ��2025-06-08 Phil
		        || gu8_Hot_Heater_Temperature_One_Degree >= 99) 																																																	// ��2025-06-08 Phil
		        {
		            //if (gu16_moving_pulse == 0)
		            // if (1)   //2025-07-03 cbr
                    if (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature)  //2025-07-03 cbr
		            {
			            gu8_preheat_max_timer = 0;
			            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		            }
		            //gu8_preheat_max_timer = 0;
		            //gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		        }
				else {}
            }
            else //(u16Heater_Power_Save > HEATER_POWER_HIGH)
            {
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 10 )				
		        //if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 2  || gu8_Hot_Heater_Temperature_One_Degree >= 99)
		        if (( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 2) && (gu8_Hot_Heater_Temperature_One_Degree <= gu8_Hot_Preheat_Temp + 10)  // ��2025-06-08 Phil
		        || gu8_Hot_Heater_Temperature_One_Degree >= 99) 																																																	// ��2025-06-08 Phil
		        {
		            //if (gu16_moving_pulse == 0)
		            // if (1)   //2025-07-03 cbr
                    if (gu8Pre_hot_setting_temperature == gu8_hot_setting_temperature)  //2025-07-03 cbr
		            {
			            gu8_preheat_max_timer = 0;
			            gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		            }
		            //gu8_preheat_max_timer = 0;
		            //gu8_Preheat_Step = STATE_4_PREHEAT_OPERATE_STATE;
		        }
				else {}
            }
#if 0
            if( ((gu8_Hot_Heater_Temperature_One_Degree < gu8_Hot_Preheat_Temp + mu8_temp) || gu8_preheat_drain_max_timer >= mu8_max_time)
                || (gu8_Hot_Heater_Temperature_One_Degree <= 93 && gu8_hot_setting_temperature != HOT_SET_TEMP_1__MILK__43_oC) )
            {
                gu8_preheat_timer++;

                if(gu8_preheat_timer >= mu8_coffee_time)
                {
                    gu8_preheat_timer = 0;
                    gu8_Preheat_Step++;

                    gu8_pre_timer = 0;
                    gu8_test_timer = 0;
                }
                else{}
            }
            else{}
#endif
            break;

        case STATE_3_PREHEAT_CHECK_TIME :

            /*..hui [19-1-18���� 10:10:13] ���Ⱑ ������ ����Ÿ��..*/
            /*if(gu8_Hot_Out_Temperature_One_Degree >= gu8_Hot_Preheat_Temp)*/
			//coffee + 500ms
            if( gu8_hot_setting_temperature == HOT_SET_TEMP____100oC 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) )
            {
                if( bit_re_hot == SET )
                {
                    mu8_temp = gu8_Hot_Preheat_Temp;

                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        //mu8_coffee_time = 40;
                        //gu8_additionalHeatingTime = 100;
                        gu8_additionalHeatingTime = 80;		// ��2025-06-02 Phil
                    }
                    else if(u16Heater_Power_Save >= HEATER_POWER_HIGH)
                    {
                        gu8_additionalHeatingTime = 26;
                    }
                    else
                    {
                        if(gu8_Hot_In_Temperature_One_Degree <= 12)
                        {
                            //mu8_coffee_time = 60;
                            gu8_additionalHeatingTime = 80;
                        }
                        else if(gu8_Hot_In_Temperature_One_Degree <= 17)
                        {
                            //mu8_coffee_time = 50;
                            gu8_additionalHeatingTime = 70;
                        }
                        else if(gu8_Hot_In_Temperature_One_Degree <= 22)
                        {
                            //mu8_coffee_time = 40;
                            gu8_additionalHeatingTime = 60;
                        }
                        else if(gu8_Hot_In_Temperature_One_Degree <= 27)
                        {
                            //mu8_coffee_time = 30;
                            gu8_additionalHeatingTime = 60;
                        }
                        else if(gu8_Hot_In_Temperature_One_Degree <= 32)
                        {
                            //mu8_coffee_time = 20;
                            gu8_additionalHeatingTime = 60;
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 10;
                        }
#if 0
                        if (gu8_pre_heater_temp >= 70
                            && gu8_Hot_In_Temperature_One_Degree <= 32)
                        {
                            mu8_coffee_time = mu8_coffee_time - 20;
                        }
#endif
                    }

                    if( gu8_pre_heater_temp >= 35 && gu8_pre_heater_temp <= 90)
                    {
                        mu8_buf = (U8)((10 - (gu8_pre_heater_temp / 10)) * 5);
                        gu8_additionalHeatingTime = gu8_additionalHeatingTime + mu8_buf;
                    }
                    else{}
                }
                else
                {
                    mu8_temp = gu8_Hot_Preheat_Temp;

                    if( u16Heater_Power_Save <= HEATER_POWER_HIGH
                        && gu8_pre_heater_temp <= 50 )
                    {
                        //gu8_additionalHeatingTime = 100;
                        gu8_additionalHeatingTime = 80;		// ��2025-06-02 Phil
                    }
                    else
                    {
                        //gu8_additionalHeatingTime = 2;
                        gu8_additionalHeatingTime = 60;
                    }
                }
            }
             else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
			|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
             {
                 if( bit_re_hot == SET )
                 {
                     mu8_temp = gu8_Hot_Preheat_Temp;
                     //mu8_coffee_time = 1;

                     if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                     {
                         //mu8_coffee_time = 25;
                         gu8_additionalHeatingTime = 35;
                     }
                     else if(u16Heater_Power_Save >= HEATER_POWER_HIGH)
                     {
                         //mu8_coffee_time = 18;
                         gu8_additionalHeatingTime = 21;
                     }
                     else
                     {
                         if(gu8_Hot_In_Temperature_One_Degree <= 12)
                         {
                             gu8_additionalHeatingTime = 25;
                         }
                         else if(gu8_Hot_In_Temperature_One_Degree <= 17)
                         {
                             gu8_additionalHeatingTime = 20;
                         }
                         else if(gu8_Hot_In_Temperature_One_Degree <= 22)
                         {
                             //mu8_coffee_time = 15;
                             gu8_additionalHeatingTime = 25;
                         }
                         else if(gu8_Hot_In_Temperature_One_Degree <= 27)
                         {
                             //mu8_coffee_time = 12;
                             gu8_additionalHeatingTime = 22;
                         }
                         else if(gu8_Hot_In_Temperature_One_Degree <= 32)
                         {
                             //mu8_coffee_time = 10;
                             gu8_additionalHeatingTime = 20;
                         }
                         else
                         {
                             gu8_additionalHeatingTime = 5;
                         }
                     }

                     if( gu8_pre_heater_temp >= 35 && gu8_pre_heater_temp <= 90)
                     {
                         mu8_buf = (U8)((10 - (gu8_pre_heater_temp / 10)) * 5);
                         gu8_additionalHeatingTime = gu8_additionalHeatingTime + mu8_buf;
                     }
                     else{}
                 }
                 else // if( bit_re_hot == CLEAR )
                 {
                     mu8_temp = gu8_Hot_Preheat_Temp;

                     if( u16Heater_Power_Save <= HEATER_POWER_HIGH
                         && gu8_pre_heater_temp <= 25 )
                     {
                         gu8_additionalHeatingTime = 4;
                     }
                     else
                     {
                         gu8_additionalHeatingTime = 2;
                     }
                 }
             }
            else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____75oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____70oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____65oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
            {
                if( bit_re_hot == SET )
                {
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        if( gu8_Hot_In_Temperature_One_Degree <= 15 )
                        {
                            //mu8_coffee_time = 20;
                            gu8_additionalHeatingTime = 30;
                        }
                        else if( gu8_Hot_In_Temperature_One_Degree <= 25 )
                        {
                            //mu8_coffee_time = 15;
                            gu8_additionalHeatingTime = 25;
                        }
                        else
                        {
                            //mu8_coffee_time = 10;
                            //mu8_coffee_time = 20;
                            gu8_additionalHeatingTime = 10;
                        }
                    }
                    else if(u16Heater_Power_Save >= HEATER_POWER_HIGH)
                    {
                        gu8_additionalHeatingTime = 21;
                    }
                    else
                    {
                        if( gu8_Hot_In_Temperature_One_Degree < 35 )
                        {
                            gu8_additionalHeatingTime = (U8)( (35 - gu8_Hot_In_Temperature_One_Degree));
                        }
                        else
                        {
							gu8_additionalHeatingTime = 1;
                        }

                        if( gu8_pre_heater_temp >= 33 && gu8_pre_heater_temp <= 90)
                        {
                            //mu8_buf = (U8)(15 - (gu8_pre_heater_temp / 10));
                            mu8_buf = (U8)(10 - (gu8_pre_heater_temp / 10));
                            gu8_additionalHeatingTime = gu8_additionalHeatingTime + mu8_buf;
                        }
                        else{}

                        if( gu8_Hot_In_Temperature_One_Degree >= 25 )
                        {
                            gu8_additionalHeatingTime = gu8_additionalHeatingTime + 10;
                        }
                        else{}

                    }
                }
                else
                {
                    mu8_temp = gu8_Hot_Preheat_Temp;
                    gu8_additionalHeatingTime = 2;
                }
            }
            else
            {
                if( bit_re_hot == SET )
                {
                    //if( gu8_Hot_Heater_Temperature_One_Degree >= 60 )
                    if( gu8_Hot_Heater_Temperature_One_Degree >= 55 )
                    {
                        gu8_additionalHeatingTime = 1;
                    }
                    else if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        if( gu8_Hot_In_Temperature_One_Degree <= 15 )
                        {
                            gu8_additionalHeatingTime = 27;
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 14;
                        }
                    }
                    else if(u16Heater_Power_Save >= HEATER_POWER_HIGH)
                    {
                        if( gu8_Hot_In_Temperature_One_Degree <= 35 )
                        {
                            mu8_coffee_time = (U8)( (35 - gu8_Hot_In_Temperature_One_Degree));

                            if( gu8_Hot_In_Temperature_One_Degree >= 28 && gu8_Hot_Heater_Temperature_One_Degree <= 38 )
                            {
                                gu8_additionalHeatingTime = gu8_additionalHeatingTime + 10;
                            }
                            else{}
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 1;
                        }
                    }
                    else
                    {
                        if( gu8_Hot_In_Temperature_One_Degree < 35 )
                        {
                            gu8_additionalHeatingTime = (U8)( (35 - gu8_Hot_In_Temperature_One_Degree));
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 1;
                        }
                    }
                }
                else
                {
                    mu8_temp = gu8_Hot_Preheat_Temp;

                    if(u16Heater_Power_Save >= HEATER_POWER_HIGH)
                    {
                        if( gu8_Hot_In_Temperature_One_Degree >= 24 )
                        {
                            //mu8_coffee_time = 20;
                            gu8_additionalHeatingTime = 17;
                        }
                        else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
                        {
                            //mu8_coffee_time = 25;
                            //mu8_coffee_time = 15;
                            if( gu8_hot_filling_max_hz >= 70 )
                            {
                                gu8_additionalHeatingTime = 25;
                            }
                            else if( gu8_hot_filling_max_hz >= 60 )
                            {
                                gu8_additionalHeatingTime = 15;
                            }
                            else if( gu8_hot_filling_max_hz >= 50 )
                            {
                                gu8_additionalHeatingTime = 12;
                            }
                            else
                            {
                                gu8_additionalHeatingTime = 10;
                            }

                        }
                        else
                        {
                            gu8_additionalHeatingTime = 5;
                        }
                    }
                    else if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        if( gu8_Hot_In_Temperature_One_Degree >= 24 )
                        {
                            gu8_additionalHeatingTime = 20;
                        }
                        else if( gu8_Hot_In_Temperature_One_Degree >= 15 )
                        {
                            gu8_additionalHeatingTime = 5;
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 1;
                        }
                    }
                    else
                    {
                        if( gu8_Hot_In_Temperature_One_Degree < 30 )
                        {
                            gu8_additionalHeatingTime = (U8)( (35 - gu8_Hot_In_Temperature_One_Degree));
                        }
                        else
                        {
                            gu8_additionalHeatingTime = 5;
                        }

                        if( gu8_pre_heater_temp >= 30 )
                        {
                            gu8_additionalHeatingTime = (gu8_additionalHeatingTime + (U8)(gu8_pre_heater_temp / 10));
                        }
                        else{}

                    }
                }
            }

            if( bit_re_hot == SET )
            {
                mu8_safety_temp = 69;

                if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC )  )
                {
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        mu8_safety_time = 75;
                    }
                    else
                    {
                        mu8_safety_time = 55;
                    }
                }				
                else if( (gu8_hot_setting_temperature == HOT_SET_TEMP____85oC )
					|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
                {
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        mu8_safety_time = 75;
                    }
                    else
                    {
                        mu8_safety_time = 55;
                    }
                }
                else
                {
                    //mu8_safety_time = 130;
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        mu8_safety_time = 130;
                    }
                    else
                    {
                        mu8_safety_time = 45;
                    }
                }
				
			    /*..sean [25-05-12] 90/95�� �ش� ���� �����ϰ� ����..*/
			    /*..sean [25-05-12] 80�� �ش� ���� �����ϰ� ����..*/
                if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC ) 
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____80oC ) )
                {
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        mu8_safety_time = 75;
                    }
                    else
                    {
                        mu8_safety_time = 55;
                    }
                }
                else
                {
                    if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                    {
                        mu8_safety_time = 130;
                    }
                    else
                    {
                        mu8_safety_time = 45;
                    }
                }
            }
            else
            {
                if(u16Heater_Power_Save <= HEATER_POWER_LOW)
                {
                    mu8_safety_temp = 76;
                    mu8_safety_time = 130;
                }
                else
                {
                    if( (gu8_hot_setting_temperature == HOT_SET_TEMP____45oC)
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____50oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____55oC )
				|| ( gu8_hot_setting_temperature == HOT_SET_TEMP____60oC ) )
                    {
                        //mu8_safety_temp = 35;

                        if( gu8_pre_heater_temp > 25 )
                        {
                            //mu8_safety_temp = 34;
                            mu8_safety_temp = 33;
                        }
                        else
                        {
                            mu8_safety_temp = 30;
                        }

                        if( gu8_Hot_Heater_Temperature_One_Degree >= mu8_safety_temp )
                        {
                            #if 0
                            if( gu8_pre_heater_temp >= 25 )
                            {
                                mu8_safety_time = 45;
                            }
                            else
                            {
                                //mu8_safety_time = 55;
                                mu8_safety_time = 50;
                            }
                            #endif

                            if( gu8_pre_heater_temp <= 35 )
                            {
                                mu8_safety_time = (U8)(35 - gu8_pre_heater_temp);
                            }
                            else{}

                            mu8_safety_time = mu8_safety_time + 20;
                        }
                        else
                        {
                            mu8_safety_time = 63;
                        }
                    }
                    else
                    {
                        mu8_safety_temp = 73;
                        mu8_safety_time = 130;
                    }
                }
            }

            gu8_test_timer++;

            if( gu8_test_timer >= mu8_safety_time )																// (1)�簡��(bit_re_hot == SET)�� mu8_safety_time  ����Ǹ� ���� ���� 2°�ܺ��� �µ��� �̴��̸� �� Ÿ�̸� �����ʿ�// ��2025-06-08 Phil 
            {
                gu8_preheat_timer = 0;
                gu8_Preheat_Step++;
            }
            else if( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp // (2) �̸� �����ص� ���� ��ǥ�µ� ����(�̴�)// ��2025-06-08 Phil 
                    || gu8_Hot_Heater_Temperature_One_Degree >= mu8_safety_temp )  // (3) �簡��(bit_re_hot == SET)�� mu8_safety_temp�� �µ� ���ǵ� ���� (1)�� ���� // ��2025-06-08 Phil 
            {
                gu8_preheat_timer++;
								gu8_additionalHeatingTime = 5;													// �� ���ʹ� 40cc���ͷ� �Ʒ��� ���� ��� �ּ�ȭ 0.5�� �߰������� ����// ��2025-06-08 Phil 
                if( gu8_preheat_timer >= gu8_additionalHeatingTime )		// (4) ��ǥ �µ������ص� �����ð� �� ������Ŵ(���Ǹ��� �ٸ�) ���� 90cc���� �������� ����// ��2025-06-08 Phil 
                {
//                    gu8_preheat_timer = 0;
//                    gu8_Preheat_Step++;
				              if( (gu8_hot_setting_temperature == HOT_SET_TEMP____100oC)
				              || ( gu8_hot_setting_temperature == HOT_SET_TEMP____95oC ) 
				              || ( gu8_hot_setting_temperature == HOT_SET_TEMP____90oC ) 
				              || ( gu8_hot_setting_temperature == HOT_SET_TEMP____85oC ) )
				              {
				              	if((gu8_Flow_1sec >= 18 && gu8_Flow_1sec <= u8Target_Hz_Hot - 5)
				              	|| (gu8_Hot_Heater_Temperature_One_Degree >= 95))
				              	{
                    			gu8_preheat_timer = 0;
                    			gu8_Preheat_Step++;						              
                    		}
				              }
				              else
				              {
                    			gu8_preheat_timer = 0;
                    			gu8_Preheat_Step++;				              
				              
				              }

                }
                else{}
            }
            else
            {
                gu8_preheat_timer = 0;
            }

            //gu8_test_timer++;


            break;

        case STATE_4_PREHEAT_OPERATE_STATE :

            gu8_preheat_timer++;
#if 0
			/*..hui [20-10-7���� 10:42:57] Ŀ���϶��� ���ֳ��� ������ ������ �����߻� �ּ�ȭ�ϱ� ����..*/
            /*..hui [20-10-7���� 10:43:11] �������� 500ms �巹������ ����ְ� ����� �Ѿ����..*/
            if( gu8_hot_setting_temperature == HOT_SET_TEMP_4__MAX__100_oC )
            {
            	if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            	{
                	gu8_additionalHeatingTime = 30;
            	}
            	else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
            	{
                	gu8_additionalHeatingTime = 20;
            	}
				else 
            	{
                	gu8_additionalHeatingTime = 10;
            	}
					
            }
            else if( gu8_hot_setting_temperature == HOT_SET_TEMP_3__COFFEE__85_oC )
            {
            	if(u16Heater_Power_Save <= HEATER_POWER_LOW)
            	{
                	gu8_additionalHeatingTime = 20;
            	}
            	else if(u16Heater_Power_Save <= HEATER_POWER_HIGH)
            	{
                	gu8_additionalHeatingTime = 15;
            	}
				else 
            	{
                	gu8_additionalHeatingTime = 10;
            	}
            }
            else
            {
                gu8_additionalHeatingTime = 5;
            }
#endif
            gu8_additionalHeatingTime = 1;

			if(gu8_preheat_timer >= gu8_additionalHeatingTime)
            {
                gu8_preheat_timer = 0;
                gu8_preheat_max_timer = 0;
                gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE;
                mu8_return = SET;
            }
            else{}

			/*sean [25-04-15] ����� ������ �Ǿ�������, ���� Skip�ǵ��� ����*/
	        if ( gu8_Hot_Heater_Temperature_One_Degree >= gu8_Hot_Preheat_Temp + 13 )
	        {
                gu8_preheat_max_timer = 0;
                gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE;
            	mu8_return = SET;
	        }

            gu8Pre_hot_setting_temperature = gu8_hot_setting_temperature;            // ���� ����µ� Ȯ��
            break;

        default:

            gu8_preheat_timer = 0;
            gu8_preheat_max_timer = 0;
            gu8_Preheat_Step = STATE_0_PREHEAT_PREPARE_STATE;

            break;

    }

    return mu8_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


