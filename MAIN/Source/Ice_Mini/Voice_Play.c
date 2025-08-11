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
#include    "Voice_Play.h"


void play_melody_continue_extract_start_192( void );
void play_melody_normal_extract_start( void );
void play_voice_hot_water_extract( void );
void play_melody_extract_complete_194( void );
void play_melody_power_on_195( void );
void play_melody_select_196( void );
void play_melody_warning_197( void );
void play_melody_setting_on_198( void );
void play_melody_setting_off_199( void );


void play_voice_top_cover_open_2( void );
void play_voice_filter_cover_open_3( void );
void play_voice_top_cover_close_6( void );
void play_voice_cold_error_7( void );
void play_voice_hot_error_9( void );
void play_voice_ice_error_10( void );

void play_voice_flow_block_error_11( void );
void play_voice_leakage_error_12( void );
void play_voice_1_3_filter_change_detect_18( void );
void play_voice_1_3_filter_change_finish_19( void );

void play_voice_filter_flushing_start_23( void );
void play_voice_filter_flushing_finish_24( void );
void play_voice_filter_flushing_cancle_25( void );
void play_voice_replace_filter_1_3_26( void );
void play_voice_replace_filter_1_2_3_49( void );

void play_voice_install_guide_75( void );
/*void play_voice_pairing_auto_start_76( void );*/

void play_voice_hot_lcok_hot_select_93( void );

void play_voice_cold_off_cold_select_96( void );

void play_voice_ice_lock_ice_out_98( void );
void play_voice_ice_off_ice_out_99( void );

void play_voice_all_lock_select_103( void );

void play_voice_setting_hot_lock_on_112( void );
void play_voice_setting_hot_lock_off_113( void );

void play_voice_setting_hot_on_121( void );
void play_voice_setting_hot_off_122( void );

void play_voice_setting_cold_on_124(void);
void play_voice_setting_cold_off_125(void);
void play_voice_all_lock_start_127( void );
void play_voice_all_lock_finish_128( void );

void play_voice_sound_setting_voice_129( void );
void play_voice_sound_setting_melody_130( void );
void play_voice_sound_setting_mute_131( void );

void play_voice_time_setting_start_144( void );
void play_voice_time_setting_finish_145( void );
void play_voice_setting_ice_lock_on_147( void );
void play_voice_setting_ice_lock_off_148( void );
void play_voice_setting_ice_on_149( void );
void play_voice_setting_ice_off_150( void );
void play_voice_dispense_my_waters(U16 U16_p_mp3);

void play_voice_test_mode_151( void );
void play_voice_replace_filter( void );


U8 gu8_125_select;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_normal_extract_start( void )
{
    //LSH zzang
    if(bit_myWater_setting_start == SET)
    {
        if(my_recipe_select == MY_INDEX_RAMEN)
        {
            play_voice_dispense_my_waters(VOICE_147_INFORM_RAMYEON_RECIPE);
        }
        else if(my_recipe_select == MY_INDEX_DRIPCOFFEE)
        {
            play_voice_dispense_my_waters(VOICE_148_INFORM_RAMYEON_DRIP_COFFEE);
        }
        else if(my_recipe_select == MY_INDEX_TEA)
        {            
            play_voice_dispense_my_waters(VOICE_149_INFORM_TEA_RECIPE);
        }
        else if(my_recipe_select == MY_INDEX_MY1)
        {
            play_voice_dispense_my_waters(VOICE_150_INFORM_MY1_RECIPE);
        }
        else if(my_recipe_select == MY_INDEX_MY2)
        {
            play_voice_dispense_my_waters(VOICE_151_INFORM_MY2_RECIPE);
        }
        else if(my_recipe_select == MY_INDEX_MY3)
        {
            play_voice_dispense_my_waters(VOICE_152_INFORM_MY3_RECIPE);
        }
        else { /* nothing */ }
    }
    else
    {
        /*..hui [21-9-2���� 3:17:18] �޴����� ���� �̿� ���� �� ���� �Ҷ�..*/
        if(( u8WaterOutState == HOT_WATER_SELECT ) 
        && (u8IceOutState == ICE_SELECT__NONE )
        )
        {
            if( gu8Sound_Type == SOUND_TYPE_VOICE )
            {
                Play_Voice(VOICE_40_CAUTION_HOT_WATER);
            }
            else if( gu8Sound_Type == SOUND_TYPE_MELODY )
            {
                Play_Voice(VOICE_193_MELODY_DISPENSE_START);
            }
            else{}
        }
        else if(u8WaterOutState == COLD_WATER_SELECT)
        {
            Play_Voice(VOICE_193_MELODY_DISPENSE_START);
        }
        else
        {
            Play_Voice(VOICE_193_MELODY_DISPENSE_START);
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���� ��������
***********************************************************************************************************************/
void play_melody_continue_extract_start_192( void )
{
    /*..hui [21-9-2���� 3:16:16] �޴����� ���� �����ϰ� ����������..*/
    if(( u8WaterOutState == HOT_WATER_SELECT ) 
    && (u8IceOutState == ICE_SELECT__NONE )
    )
    {
        if( gu8Sound_Type == SOUND_TYPE_VOICE )
        {
            Play_Voice(VOICE_41_CAUTION_CONTINUOUS_HOT_WATER);
        }
        else if( gu8Sound_Type == SOUND_TYPE_MELODY )
        {
            Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
        }
        else{}
    }
    else if(u8WaterOutState == COLD_WATER_SELECT)
    {
        Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
    }
    else
    {
        Play_Voice(VOICE_192_MELODY_DISPENSE_CONTINUOUS);
    }
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_extract_complete_194( void )
{
    Play_Voice(VOICE_194_MELODY_DISPENSE_FINISH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_power_on_195( void )
{
    Play_Voice(VOICE_191_MELODY_PLUG_IN_COWAY);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_select_196( void )
{
    Play_Voice(VOICE_196_MELODY_SELECT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_warning_197( void )
{
    Play_Voice(VOICE_197_MELODY_WARNING);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_setting_on_198( void )
{
    Play_Voice(VOICE_198_MELODY_SET_ON);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_melody_setting_off_199( void )
{
    Play_Voice(VOICE_199_MELODY_SET_OFF);
}





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_top_cover_open_2( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_1_STOP_ICE_ICETANK_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else {}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_cover_open_3( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_2_SHUTOFF_WATER_FRONT_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_reed_sw_open_4( void )
{
    // Play_Voice(VOICE_1_SHUTOFF_WATER_FILTER_COVER);

    #if 0
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_3_SHUTOFF_WATER_SIDE_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
    #endif
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_top_cover_close_6( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_3_RESTART_ICE_COVER_OK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else {}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_cold_error_7( void )
{
    Play_Voice(VOICE_4_CALL_AS_COLD_WATER_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_error_9( void )
{
    Play_Voice(VOICE_5_CALL_AS_HOT_WATER_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_error_10( void )
{
    Play_Voice(VOICE_6_CALL_AS_ICE_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_flow_block_error_11( void )
{
    Play_Voice(VOICE_7_CALL_AS_WATER_SUPPLY_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_leakage_error_12( void )
{
    Play_Voice(VOICE_8_CALL_AS_WATER_LEAKAGE_ERROR);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_1_3_filter_change_detect_18( void )
{

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_1_3_filter_change_finish_19( void )
{
    Play_Voice(VOICE_9_PRESS_YES_OR_NO_AFTER_FILTER);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_start_23( void )
{
    Play_Voice(VOICE_35_INFORM_FLUSHING_START);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_finish_24( void )
{
    Play_Voice(VOICE_36_INFORM_FLUSHING_FINISH);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_filter_flushing_cancle_25( void )
{
    Play_Voice(VOICE_13_CHECK_FILTER_FLUSHING_MANUAL);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter_1_3_26( void )
{

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter_1_2_3_49( void )
{

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_install_guide_75( void )
{
    Play_Voice(VOICE_33_INFORM_PROEDUCT_BEFORE_FLUSHING);
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_hot_lcok_hot_select_93( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_45_INFORM_HOT_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_cold_off_cold_select_96( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_126_INFORM_COLD_FUNCTION_OFF_1_2KG);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_lock_ice_out_98( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_49_INFORM_ICE_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_ice_off_ice_out_99( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_50_PRESS_BUTTON_ICE_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_select_103( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_53_PRESS_SETTING_MODE_ALL_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_lock_on_112( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_45_INFORM_HOT_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_lock_off_113( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_55_DEACTIVATE_SETTING_HOT_LOCK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_on_121( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        // Play_Voice(VOICE_121_INFORM_HOT_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_hot_off_122( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {

    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

void play_voice_setting_cold_on_124( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_72_INFORM_COLD_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

void play_voice_setting_cold_off_125( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_71_INFORM_COLD_FUNCTION_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_start_127( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_63_INFORM_ALL_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_all_lock_finish_128( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_64_INFORM_ALL_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_time_setting_start_144( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_75_SETTING_MODE_CLOCK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_time_setting_finish_145( void )
{
    gu8_125_select = 1;

    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_76_MODE_SET_CLOCK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_lock_on_147( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_78_INFORM_ICE_LOCK_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_lock_off_148( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_79_INFORM_ICE_LOCK_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_on_149( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_80_INFORM_ICE_FUNCTION_ON);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_setting_ice_off_150( void )
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_81_INFORM_ICE_FUNCTION_OFF);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �ü� �� ���� �� ����
***********************************************************************************************************************/
void play_voice_cold_temp_strong_140(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_140_TRANSFER_WEAK_TO_STRONG);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �ü� �� ���� �� ����
***********************************************************************************************************************/
void play_voice_cold_temp_weak_139(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_139_TRANSFER_STRONG_TO_WEAK);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���� �� ���� �� ����
***********************************************************************************************************************/
void play_voice_ice_size_large_144(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_144_TRANSFER_SMALL_TO_BIG);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���� �� ���� �� ����
***********************************************************************************************************************/
void play_voice_ice_size_small_143(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_143_TRANSFER_BIG_TO_SAMLL);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������� ���� ��
***********************************************************************************************************************/
void play_voice_sleep_mode_enable_145(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_145_ACTIVATE_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������� ���� ��
***********************************************************************************************************************/
void play_voice_sleep_mode_disable_146(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_146_DEACTIVAT_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ����Ʈ�������� ���� ��
***********************************************************************************************************************/
void play_voice_smart_test_mode_16(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_16_START_SMART_TESTING_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���� �������� ��
***********************************************************************************************************************/
void play_voice_ice_type_break_select_157(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_157_BREAK_ICE_SELECTED);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ��� ���� ��
***********************************************************************************************************************/
void play_voice_ramyeon_recipe_select_147(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_147_INFORM_RAMYEON_RECIPE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �帳Ŀ�� ���� ��
***********************************************************************************************************************/
void play_voice_drip_coffee_recipe_select_148(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_148_INFORM_RAMYEON_DRIP_COFFEE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : �� ���� ��
***********************************************************************************************************************/
void play_voice_tea_recipe_select_149(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_149_INFORM_TEA_RECIPE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : MY1 ���� ��
***********************************************************************************************************************/
void play_voice_my1_recipe_select_150(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_150_INFORM_MY1_RECIPE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : MY2 ���� ��
***********************************************************************************************************************/
void play_voice_my2_recipe_select_151(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_151_INFORM_MY2_RECIPE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : MY3 ���� ��
***********************************************************************************************************************/
void play_voice_my3_recipe_select_152(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_152_INFORM_MY3_RECIPE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_select_196();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������� ���� ��
***********************************************************************************************************************/
void play_voice_setting_mode_in_43(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_43_CLICK_3S_FOR_SETTING_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������� ���� ��
***********************************************************************************************************************/
void play_voice_setting_mode_out_77(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_77_FINISH_SETTING_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_off_199();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���ڸ�� (��ħ���) ���Ұ� ��
***********************************************************************************************************************/
void play_voice_eco_mode_not_available_51(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_51_SET_CLOCK_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���� ��ſ� ��
***********************************************************************************************************************/
void play_voice_filter_not_detected_14(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_14_NO_REPLACE_WITH_COVER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ����Ŀ���� �������� ��
***********************************************************************************************************************/
void play_voice_filter_cover_opened_44(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_44_INFORM_WATER_OPEN_FILER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ������ ������ ��
***********************************************************************************************************************/
void play_voice_ice_water_extract_92(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_92_INFORM_CLICK_ICE_WATER);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ��»�� �������� ��
***********************************************************************************************************************/
void play_voice_ice_tray_hot_ster_is_going_86(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_86_INFORM_ICE_TRAY_STER_NO_ICE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_warning_197();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : MY���� ���� �� �߻��Ǵ� ���� �Լ�
***********************************************************************************************************************/
void play_voice_dispense_my_waters(U16 U16_p_mp3)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        switch (U16_p_mp3)
        {
            case VOICE_147_INFORM_RAMYEON_RECIPE:
            case VOICE_148_INFORM_RAMYEON_DRIP_COFFEE:
            case VOICE_149_INFORM_TEA_RECIPE:
            case VOICE_150_INFORM_MY1_RECIPE:
            case VOICE_151_INFORM_MY2_RECIPE:
            case VOICE_152_INFORM_MY3_RECIPE:
                Play_Voice(U16_p_mp3);
                break;
            default:
                /* nothing */
                break;
        }
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        Play_Voice(VOICE_193_MELODY_DISPENSE_START);
    }
    else { /* nothing */ }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  : ���߿� ���� "Ư������Դϴ�."
***********************************************************************************************************************/
void play_voice_test_mode_151( void )
{
    Play_Voice(VOICE_151_SPECIAL_FUNCTION);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_replace_filter( void )
{
    /*..hui [24-1-10���� 3:31:21] ���� ���� �˶� ǥ�� �� ù �� ���� �����ϰ� ���� �˶� ȭ�� ǥ���Ҷ� ..*/
    /*..hui [24-1-10���� 3:31:25] 1ȸ�� ���� ���..*/
    if( bit_filter_alarm_1_3_voice == SET )
    {
        play_voice_replace_filter_1_3_26();
    }
    else if( bit_filter_alarm_1_2_3_voice == SET )
    {
        play_voice_replace_filter_1_2_3_49();
    }
    else{}

    bit_filter_alarm_1_3_voice = CLEAR;
    bit_filter_alarm_1_2_3_voice = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void play_voice_sleep_mode_ice_extract_52(void)
{
    if( gu8Sound_Type == SOUND_TYPE_VOICE )
    {
        Play_Voice(VOICE_52_NO_GUARANTEE_ICE_ECO_MODE);
    }
    else if( gu8Sound_Type == SOUND_TYPE_MELODY )
    {
        play_melody_setting_on_198();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



