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
#include "temperature.h"
u8 test_commd;
#define         HDC_1080_ADD                            0x40
#define         Configuration_register_add              0x02
#define         Temperature_register_add                0x00
#define         Humidity_register_add                   0x01
void TEMPERATURE_init()
{
    uint16_t config_reg_value=0x1000;
	uint8_t data_send[2];
    IIC_Init();
    
    data_send[0]= (config_reg_value>>8);
	data_send[1]= (config_reg_value&0x00ff);
    
    IIC_Start();
    IIC_Send_Byte(0x80);
    if (IIC_Wait_Ack())
    {
        while(1)
        {
            IIC_SDA=1;
            IIC_SCL=1;
            delay_ms(1000);
            IIC_SDA=0;
            IIC_SCL=0;
            delay_ms(1000);
            
        }
    }
    IIC_Send_Byte(data_send[0]);
    IIC_Wait_Ack();
    IIC_Send_Byte(data_send[1]);
    IIC_Wait_Ack();
    IIC_Stop();
    delay_us(10);
	//IIC_Write_One_Byte(Configuration_register_add,data_send[0]);
    //IIC_Write_One_Byte(Configuration_register_add,data_send[1]);
}
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
extern u8 remote_val_rec[3];
extern u8 remote_val_get;
u8 REMOTE_commd[3][7]={{0xFD,0x01,0x91,0x80,0xE1,0x90,0xDF},{0xFD,0x01,0xFE,0x1E,0xB1,0x50,0xDF},{0xFD,0x01,0x48,0x13,0x08,0x50,0xDF}};
void check_remote()
{
    if (remote_val_get)
    {
        if ((remote_val_rec[0]==0x91)&&(remote_val_rec[1]==0x80)&&(remote_val_rec[2]==0xD1))
        {
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[0][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
            delay_ms(1200);
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[1][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
            delay_ms(1200);
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[2][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
        }
        if ((remote_val_rec[0]==0xFE)&&(remote_val_rec[1]==0x1E)&&(remote_val_rec[2]==0xA1))
        {
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[0][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
            delay_ms(1200);
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[1][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
            delay_ms(1200);
            for (uint8_t i = 0; i < 7; i++)
            {
                USART_SendData(USART1, REMOTE_commd[2][i]);
                while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
            }
        }
        remote_val_get=0;
    }
}
void LAMP_init()
{
    ;
}
void REMOTE_init()
{
    ;
}
u8 iic_rec[4]={0};
void TEMPERATURE_get()
{
    IIC_Start();   
    IIC_Send_Byte(0x81);   
    IIC_Wait_Ack();
    IIC_Send_Byte(0x00);
    IIC_Wait_Ack(); 
    delay_ms(15);
    iic_rec[0]=IIC_Read_Byte(0); 
    iic_rec[1]=IIC_Read_Byte(0);
    iic_rec[2]=IIC_Read_Byte(0);
    iic_rec[3]=IIC_Read_Byte(0);
    IIC_Stop();
}
u8 temp_start=0;
int main(void)
{
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);
    LED_Init();
    LAMP_init();
    RTC_Init();
    //TEMPERATURE_init();
    AIRCOND_init();
    while (1)
    {
        check_event();
        check_remote();
        if (temp_start)
        {
            TEMPERATURE_get();
             temp_start=0;
        }
        delay_ms(500);
    }
}
