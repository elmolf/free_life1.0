/**
 * @file main.c
 * @author linf (elmo_lf@126.com)
 * @brief 
 * @version 1.0
 * @date 2020-10-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "rtc.h"
#include "timer.h"
#include "aircondit.h"
u8 test_commd;

void check_event()
{
    
    if (((calendar.hour == 22) && (calendar.min == 00) && (calendar.sec == 00)) || (test_commd == 1))
    {
        AIRCOND_send_commd(AIRCOND_MODE_NORMAL);
    }
    if (((calendar.hour == 0) && (calendar.min == 5) && (calendar.sec == 00)) || (test_commd == 2))
    {
        AIRCOND_send_commd(AIRCOND_MODE_SLEEP);
    }
    if (((calendar.hour == 4) && (calendar.min == 30) && (calendar.sec == 00)) || (test_commd == 3))
    {
        AIRCOND_send_commd(AIRCOND_MODE_POWEROFF);
    }
    if (((calendar.hour == 9) && (calendar.min == 50) && (calendar.sec == 00)) || (test_commd == 3))
    {
        AIRCOND_send_commd(AIRCOND_MODE_POWEROFF);
    }
}

int main(void)
{
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);
    LED_Init();
    RTC_Init();
    AIRCOND_init();
    while (1)
    {
        check_event();
        delay_ms(500);
    }
}
