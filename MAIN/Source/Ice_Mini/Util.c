/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Port_Define.h"
#include    "Util.h"


U16 HexToAsc(U8 mu8RxdData);
U8 AscToHex(U8 mu8RxdData1, U8 mu8RxdData2);
U8 Nibble(U8 mu8RxdData);
U8 Hex2Dec(U8 mu8Hex);
U8 Dec2Hex(U8 mu8Dec);
U16 Rx_CRC_CCITT(U8 *puchMsg, U8 usDataLen);
//U8 get_CheckSum(const U8 *pData, U8 len);
U8 get_Fahrenheit( U8 mu8_celcius );
U16 DecToAsc(U8 mu8RxdData);
U16 get_round( F32 f32_data );



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : HexToAsc
// ����       : Hex to Asc ��ȯ
//----------------------------------------------------------------------------
// ���       : Hex 1 byte -> Asc 2 byte �� ��ȯ
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U16 HexToAsc(U8 mu8RxdData)
{
    U8 mu8Temp_Data1;
    U16 mu16Temp_Data1;

    mu8Temp_Data1 = mu8RxdData >> 4;                           // ����4��Ʈ
    mu8Temp_Data1 = mu8Temp_Data1 & 0x0f;
    mu8RxdData = mu8RxdData & 0x0f;                            // ����4��Ʈ

    if(mu8Temp_Data1>=0x0a) mu8Temp_Data1 = mu8Temp_Data1 + 0x37;
    else mu8Temp_Data1 = mu8Temp_Data1 + 0x30;

    if(mu8RxdData>=0x0a) mu8RxdData = mu8RxdData + 0x37;
    else mu8RxdData = mu8RxdData + 0x30;

    mu16Temp_Data1 = 0;
    mu16Temp_Data1 = mu8Temp_Data1;
    mu16Temp_Data1 = mu16Temp_Data1<<8;
    mu16Temp_Data1 = mu16Temp_Data1 + mu8RxdData;

    return mu16Temp_Data1;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : AscToHex
// ����       : ASC to Hex ��ȯ
//----------------------------------------------------------------------------
// ���       : ASC 2 byte -> HEX 1 byte �� ��ȯ
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U8 AscToHex(U8 mu8RxdData1, U8 mu8RxdData2)
{
    U8 mu8Temp_Data1, mu8Temp_Data2;

    mu8Temp_Data1 = Nibble(mu8RxdData1);
    mu8Temp_Data2 = Nibble(mu8RxdData2);

    mu8Temp_Data1 = mu8Temp_Data1<<4;
    mu8Temp_Data1 = mu8Temp_Data1 | mu8Temp_Data2;

    return mu8Temp_Data1;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : Nibble
// ����       : ASC to Hex ��ȯ
//----------------------------------------------------------------------------
// ���       : ASC 1 byte -> HEX 1 nibble �� ��ȯ
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U8 Nibble(U8 mu8RxdData)
{
    U8 mu8Temp_Data1, mu8Temp_Data2;

    mu8Temp_Data1 = mu8RxdData - 0x30;
    if(mu8RxdData<0x30) return mu8Temp_Data1;

    mu8Temp_Data2 = (U8)(mu8Temp_Data1 + 0xe9);
    if(mu8Temp_Data1>0x16) return mu8Temp_Data2;

    mu8Temp_Data1 = mu8Temp_Data2 + 0x06;

    if(mu8Temp_Data2 > 0xf9)
    {
        mu8Temp_Data2 = mu8Temp_Data1 + 0x0a;
        return mu8Temp_Data2;
    }

    mu8Temp_Data2= mu8Temp_Data1 + 0x07;
    if(mu8Temp_Data1>0xf8) return mu8Temp_Data2;
    else mu8Temp_Data1 = mu8Temp_Data2 + 0x0a;

    return mu8Temp_Data1;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/* 0 ~ 99 */
U8 Hex2Dec(U8 mu8Hex)
{
    U8 mu8Dec;

    mu8Dec = (mu8Hex & 0x0F);
    mu8Dec += ((mu8Hex & 0xF0) >> 4) * 10;

    return mu8Dec;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
/* 0 ~ 99 */
U8 Dec2Hex(U8 mu8Dec)
{
    U8 mu8Hex;

    mu8Hex = mu8Dec % 10;
    mu8Hex += (mu8Dec / 10) * 16;

    return mu8Hex;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 Rx_CRC_CCITT(U8 *puchMsg, U8 usDataLen)
{
    U8 i = 0;
    unsigned short  wCRCin = 0x0000;
    unsigned short  wCPoly = 0x1021;
    U16 wChar = 0;

    while (usDataLen--)
    {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);

        for(i = 0; i < 8; i++)
        {
            if (wCRCin & 0x8000)
            {
                wCRCin = (wCRCin << 1) ^ wCPoly;
            }
            else
            {
                wCRCin = wCRCin << 1;
            }
        }
    }

    return (wCRCin);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
#if 0
U8 get_CheckSum(const U8 *pData, U8 len)
{
    U16 sum = 0;
    U8 i = 0;

    for (i = 0; i < len; ++i)
    {
        sum += pData[i];
    }

    return (U8)(~sum + 1);
}
#endif
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 get_Fahrenheit( U8 mu8_celcius )
{
    U8 mu8_return = 0;
    U16 mu16_calc = 0;

    /*..hui [23-6-16���� 12:36:12] �ִ� 100�� ����..*/
    if( mu8_celcius >= 100 )
    {
        mu16_calc = 100;
    }
    else
    {
        mu16_calc = mu8_celcius;
    }

    mu8_return = (U8)((U16)( 9 * mu16_calc ) / 5);

    mu8_return = mu8_return + 32;

    return mu8_return;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
//""SUBR COMMENT""************************************************************
// ID         : DecToAsc
// ����         : Dec to Asc ��ȯ
//----------------------------------------------------------------------------
// ���       : Dec 1 byte(0~99��) -> Asc 2 byte �� ��ȯ
//----------------------------------------------------------------------------
//""SUBR COMMENT END""********************************************************
U16 DecToAsc(U8 mu8RxdData)
{
    U8 mu8Temp_Data1;
    U16 mu16Temp_Data1;

    mu8Temp_Data1 = mu8RxdData/10;                         // ����4��Ʈ
    mu8RxdData = mu8RxdData%10;                            // ����4��Ʈ

    mu8Temp_Data1 = mu8Temp_Data1 + 0x30;
    mu8RxdData = mu8RxdData + 0x30;

    mu16Temp_Data1 = 0;
    mu16Temp_Data1 = mu8Temp_Data1;
    mu16Temp_Data1 = mu16Temp_Data1<<8;
    mu16Temp_Data1 = mu16Temp_Data1 + mu8RxdData;

    return mu16Temp_Data1;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U16 get_round( F32 f32_data )
{
    U16 mu16_return = 0;
    U16 mu16_calc = 0;

    if( f32_data > 0 )
    {
        mu16_calc = (U16)(f32_data + 0.5f);
    }
    else{}

    mu16_return = mu16_calc;

    return mu16_return;
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


