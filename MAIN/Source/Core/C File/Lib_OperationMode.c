/// @file   Lib_OperationMode.c
/// @date
/// @author Jaejin Ham
/// @brief  ���� ��� �ְ� ��� ����

#include "Global_header.h"


U8 gu8OperaionMode = 0;                 // ���� ���� ���� ���
U8 gu8ChangeOperaionMode = 0;           // ������ ���� ���


/// @brief  ���� ���� ��� �ʱ�ȭ �Լ�
/// @param  void
/// @return void
void InitializeOperationMode(void)
{
    gu8OperaionMode = OPERATION_MODE_NONE;
}


/// @brief  ���� ��� ���� �Լ�
/// @param  void
/// @return void
void ChangeOperationMode(U8 mu8OperationMode)
{
    gu8ChangeOperaionMode = mu8OperationMode;
}


/// @brief  ���� ���� ���� ���� �Լ�
/// @param  void
/// @return void
void OperationModeSetup(void)
{
    switch (gu8ChangeOperaionMode)
    {
        case OPERATION_MODE_NORMAL:
            if (gu8OperaionMode != OPERATION_MODE_NORMAL)
            {
                gu8OperaionMode = OPERATION_MODE_NORMAL;
                InitializeTimeScheduler();                  // �����췯 �ʱ�ȭ

                SetupTimeScheduler(AD_Convert_Control, 1, ACT_COUNT_INFINITE);      // AD Convert 1ms ��ƾ ����
// ��)           SetupTimeScheduler(exFunction, 100, ACT_COUNT_INFINITE);            // ���ο� ���� �Լ� ������ ����
                SetupTimeScheduler(WifiControlProcess100ms, 100, ACT_COUNT_INFINITE);   // Wi-Fi 100ms Scheduler ����
            }
            break;

        case OPERATION_MODE_PCB_TEST:
            if (gu8OperaionMode != OPERATION_MODE_PCB_TEST)
            {
                gu8OperaionMode = OPERATION_MODE_PCB_TEST;
                InitializeTimeScheduler();

                SetupTimeScheduler(AD_Convert_Control, 1, ACT_COUNT_INFINITE);      // AD Convert 1ms ��ƾ ����
            }
            break;

        case OPERATION_MODE_FRONT_TEST:
            if (gu8OperaionMode != OPERATION_MODE_FRONT_TEST)
            {
                gu8OperaionMode = OPERATION_MODE_FRONT_TEST;
                InitializeTimeScheduler();

                SetupTimeScheduler(AD_Convert_Control, 1, ACT_COUNT_INFINITE);      // AD Convert 1ms ��ƾ ����
            }
            break;

        case OPERATION_MODE_PTA_TEST_1:
            if (gu8OperaionMode != OPERATION_MODE_PTA_TEST_1)
            {
                gu8OperaionMode = OPERATION_MODE_PTA_TEST_1;
                InitializeTimeScheduler();

                SetupTimeScheduler(AD_Convert_Control, 1, ACT_COUNT_INFINITE);      // AD Convert 1ms ��ƾ ����
            }
            break;

        case OPERATION_MODE_PTA_TEST_2:
            if (gu8OperaionMode != OPERATION_MODE_PTA_TEST_2)
            {
                gu8OperaionMode = OPERATION_MODE_PTA_TEST_2;
                InitializeTimeScheduler();

                SetupTimeScheduler(AD_Convert_Control, 1, ACT_COUNT_INFINITE);      // AD Convert 1ms ��ƾ ����
            }
            break;

        default:
            break;
    }
}




