/// @encoding euc-kr
/// @file   User_Main.c
/// @date
/// @author Jaejin Ham
/// @brief  Program Main File

/// @mainpage ���α׷� ���� ������
/// @section intro �Ұ�
/// - �Ұ� :
/// @section Program ���α׷���
/// - ���α׷���  :
/// - ���α׷� ���� :
/// @section info ���� ����
/// -
/// @section advenced ��� CPU
/// -
/// @section CREATEINFO �ۼ�����
/// - �ۼ���      :   ������
/// - �ۼ���      :
/// @section MODIFYINFO ��������
/// -


#include "Global_header.h"


/// @brief    delay �Լ�
/// @param    mu8Time : delay �ð�(8us)
/// @return   void
void Delay(U16 mu8Time)
{
  U16 mu8i;

  for (mu8i = 0 ; mu8i <= mu8Time ; mu8i++)
  {
    R_WDT_Restart();
  }
}


/// @brief    delay ms �Լ�
/// @param    mu8Time : delay �ð�(ms)
/// @return   void
void Delay_ms(U16 mu16Time)
{
  U16 mu16i = 0;
  U16 mu16j = 0;

  for (mu16i = 0 ; mu16i <= (mu16Time*2) ; mu16i++)
  {
    for (mu16j = 0 ; mu16j <= 830 ; mu16j++)
    {   // constant value for 1msec counter = 830
      R_WDT_Restart();
    }
  }
}


/// @brief    HEX to Decimal
/// @param    mu8HexData : HEX Data
/// @return   mu8ReturnData : DEC Data
U8 HEX2DEC(U8 mu8HexData)
{
  U8 mu8ReturnData = 0;

  mu8ReturnData = (((mu8HexData >> 4) & 0x0F) * 10) + (mu8HexData & 0x0F);

  return  mu8ReturnData;
}


/// @brief    Decimal to HEX
/// @param    mu8DecData : DEC Data
/// @return   mu8ReturnData : HEX Data
U8 DEC2HEX(U8 mu8DecData)
{
  U8 mu8ReturnData = 0;

  mu8ReturnData = (((mu8DecData / 10) << 4) & 0xF0) + (mu8DecData % 10);

  return  mu8ReturnData;
}


/// @brief    HEX to Decimal
/// @param    mu16HexData : HEX Data
/// @return   mu16ReturnData : DEC Data
U16 Bit16HEX2DEC(U16 mu16HexData)
{
  U16 mu16ReturnData = 0;

  mu16ReturnData = ((mu16HexData >> 12) & 0x000F) * 1000;
  mu16ReturnData += ((mu16HexData >> 8) & 0x000F) * 100;
  mu16ReturnData += ((mu16HexData >> 4) & 0x000F) * 10;
  mu16ReturnData += mu16HexData & 0x000F;

  return  mu16ReturnData;
}


/// @brief    Decimal to HEX
/// @param    mu16DecData : DEC Data
/// @return   mu16ReturnData : HEX Data
U16 DEC2Bit16HEX(U16 mu16DecData)
{
  U16 mu16ReturnData = 0;

  mu16ReturnData = ((mu16DecData / 1000) << 12) & 0xF000;
  mu16ReturnData += (((mu16DecData % 1000) / 100) << 8) & 0x0F00;
  mu16ReturnData += (((mu16DecData % 100) / 10) << 4) & 0x00F0;
  mu16ReturnData += (mu16DecData % 10) & 0x000F;

  return  mu16ReturnData;
}


/// @brief    Ascii to HEX
/// @param    mu8HexData : Hex Data
/// @return   mu8ReturnData : Ascii Data
U8 HEX2ASCII(U8 mu8HexData)
{
  U8 mu8ReturnData = 0;

  if (mu8HexData < 0x0A)
  {
    mu8ReturnData = mu8HexData | 0x30;
  }
  else
  {
    mu8ReturnData = (mu8HexData - 9) | 0x40;
  }

  return  mu8ReturnData;
}


/// @brief    Ascii to HEX
/// @param    mu8AsciiData : Ascii Data
/// @return   mu8ReturnData : Hex Data
U8 ASCII2HEX(U8 mu8AsciiData)
{
  U8 mu8ReturnData = 0;

  if (mu8AsciiData >= 0x41)
  {
    mu8ReturnData = (mu8AsciiData & ~0x40) + 9;
  }
  else
  {
    mu8ReturnData = mu8AsciiData & ~0x30;
  }

  return  mu8ReturnData;
}



/// @brief    Interrupt(Timer, ADC, External ��) Start �Լ�
/// @param    void
/// @return   void
void Interrupt_Start(void)
{
    R_TAU0_Channel0_Start();        // Timer Interrupt Start ����
}


/// @brief    ��� UART�� ���  Start �Լ�
/// @param    void
/// @return   void
void UART_Start(void)
{
    R_UART1_Start();    // Wi-Fi Uart1
}


/// @brief    ��� ���� �ʱ�ȭ �Լ�
/// @param    void
/// @return   void
void Main_Initailize(void)
{
    AD_Convert_Initialize();
    InitializeTimeScheduler();
    InitializeOperationMode();
}



// ******************************************************************************
// *                                                                            *
// *                        Program Main Fuction                                *
// *                                                                            *
// ******************************************************************************
/// @brief    Main function
/// @param    void
/// @return   void
void User_Main(void)
{
    DI();
    /* --- R_Systeminit START --- */
    PIOR = 0x00U;

    R_CGC_Get_ResetSource();
    R_CGC_Create();
    R_PORT_Create();
    R_SAU0_Create();
    R_ADC_Create();
    R_TAU0_Create();
    R_TAU1_Create();
    R_WDT_Create();
    R_INTC_Create();

    IAWCTL = 0x00U;
    /* --- R_Systeminit END --- */

    Interrupt_Start();      // ���� Interrupt�� ���� ����

    Delay_ms(1000);         // ���� ����ȭ �ð� Ȯ��. While�� ���� ���Ŀ��� Delay �Լ� ��� ����(Time Scheduler �и� �� ����)

    Main_Initailize();      // ���� �� ��� ���� �ʱ�ȭ

//    ModelCheck();         // Model Type(CHP,CP,HP) Check

    EI();

    UART_Start();           // ���� UART�� ���� ����

    WifiControlProcess(WIFI_TIME_INI);    // Wi-Fi Initialize. EEPROM Initialize ������ ����

    /* --- EEPROM Initialize START --- */
      // EEPROM_PRIMARY();     // EEPROM Initialize
    /* --- EEPROM Initialize END--- */

    WifiControlProcess(WIFI_TIME_SET);    // Wi-Fi WifiOnOffSetting. EEPROM Initialize ���Ŀ� ����
    ChangeOperationMode(OPERATION_MODE_NORMAL);     // �Ϲ� ���� ���� ���� �� �� �ֵ��� ����
    

    while (1)
    {
        R_WDT_Restart();
        OperationModeSetup();       // ���� ��� ����
        GoTimeScheduler();          // Time Scheduler ���� ����
        WifiControlProcess(WIFI_TIME_WHILE);    // Wi-Fi While ����
    }
}





