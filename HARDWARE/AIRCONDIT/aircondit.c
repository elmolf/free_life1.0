/**
 * @file aircondit.c
 * @author linf (elmo_lf@126.com)
 * @brief 
 * @version 1.0
 * @date 2020-10-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "aircondit.h"
#include "rtc.h" 	

const u8 AIRCOND_commd[3][236] = {{0xFD, 0xFD, 0x30, 0x03, 0x63, 0x8B, 0x00, 0x34, 0x12, 0x01, 0x2B, 0x02, 0x63, 0x00, 0x2A, 0x00, 0x1E,
                                   0x00, 0x29, 0x00, 0xD5, 0x04, 0x2A, 0x00, 0x00, 0x00, 0x26, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x22, 0x12, 0x12, 0x21, 0x12, 0x12, 0x22, 0x22, 0x22, 0x22,
                                   0x11, 0x22, 0x22, 0x21, 0x21, 0x22, 0x12, 0x32, 0x22, 0x21, 0x22, 0x21, 0x12, 0x22, 0x12, 0x22, 0x22,
                                   0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x76, 0x3F, 0x8C, 0xDF, 0xDF},
                                  {0xFD, 0xFD, 0x30, 0x03, 0x63, 0x8B, 0x00, 0x34, 0x14, 0x01, 0x29, 0x02, 0x65, 0x00, 0x27, 0x00, 0x1F,
                                   0x00, 0x28, 0x00, 0xD8, 0x04, 0x26, 0x00, 0x00, 0x00, 0x22, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x22, 0x11, 0x22, 0x11, 0x12, 0x12, 0x22, 0x22, 0x22, 0x22,
                                   0x11, 0x22, 0x22, 0x21, 0x21, 0x22, 0x12, 0x32, 0x22, 0x21, 0x22, 0x21, 0x12, 0x22, 0x12, 0x22, 0x22,
                                   0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x24, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x76, 0x01, 0x86, 0xDF, 0xDF},
                                  {0xFD, 0xFD, 0x30, 0x03, 0x63, 0x8B, 0x00, 0x34, 0x15, 0x01, 0x28, 0x02, 0x65, 0x00, 0x26,
                                   0x00, 0x21, 0x00, 0x27, 0x00, 0xD9, 0x04, 0x26, 0x00, 0x00, 0x00, 0x26, 0x00, 0xFF, 0xFF,
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x22, 0x21, 0x22, 0x21,
                                   0x12, 0x12, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x21, 0x21, 0x22, 0x12, 0x32, 0x22,
                                   0x21, 0x22, 0x21, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x14,
                                   0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x76, 0x3F, 0x68, 0xDF, 0xDF}};

void AIRCOND_send_commd(u8 commd_type)
{
    for (uint8_t i = 0; i < 236; i++)
    {
        USART_SendData(USART1, AIRCOND_commd[commd_type - 1][i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}
void AIRCOND_init(void)
{
    alarm[0].hour=22;
    alarm[0].min=0;
    alarm[0].sec=0;
    alarm[0].event=1;
    alarm[0].command=1;
}
