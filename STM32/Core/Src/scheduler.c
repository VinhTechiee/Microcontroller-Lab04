/*
 * scheduler.c
 *
 *  Created on: Oct 26, 2025
 *      Author: josh
 */


#include "main.h"
#include "timer.h"
#include "scheduler.h"
#include "string.h"
#include "stdio.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void)
{
    memset(SCH_tasks_G, 0, sizeof(SCH_tasks_G));
}


void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].inUse == 0) {
            SCH_tasks_G[i].pTask = pFunction;
            SCH_tasks_G[i].Delay = DELAY / TIMER_CYCLE;
            SCH_tasks_G[i].Period = PERIOD / TIMER_CYCLE;
            SCH_tasks_G[i].RunMe = 0;
            SCH_tasks_G[i].TaskID = i;
            SCH_tasks_G[i].inUse = 1;
            return;
        }
    }
}


void SCH_Update(void)
{
    for (int i = 0; i < SCH_MAX_TASKS; i++)
    {
        if (SCH_tasks_G[i].inUse &&
            SCH_tasks_G[i].pTask != 0)
        {
            if (SCH_tasks_G[i].Delay > 0)
            {
                SCH_tasks_G[i].Delay--;
            }

            if (SCH_tasks_G[i].Delay == 0)
            {
                if (SCH_tasks_G[i].RunMe < 255)
                {
                    SCH_tasks_G[i].RunMe++;
                }

                if (SCH_tasks_G[i].Period > 0)
                {
                    SCH_tasks_G[i].Delay =
                        SCH_tasks_G[i].Period;
                }
                else
                {
                    SCH_tasks_G[i].Delay =
                        UINT32_MAX;
                }
            }
        }
    }
}

void SCH_Dispatch_Tasks(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].inUse == 0) continue;
        if (SCH_tasks_G[i].RunMe > 0) {
            SCH_tasks_G[i].RunMe--;
            (*SCH_tasks_G[i].pTask)();

            if (SCH_tasks_G[i].Period == 0) {
                SCH_Delete_Task(i);
            }
        }
    }
}

void SCH_Delete_Task(uint32_t index) {
    if (SCH_tasks_G[index].inUse == 0) return;

    for (int i = index; i < SCH_MAX_TASKS - 1; i++) {
        SCH_tasks_G[i] = SCH_tasks_G[i + 1];
        SCH_tasks_G[i].TaskID = i;
    }

    SCH_tasks_G[SCH_MAX_TASKS - 1].pTask = 0x0000;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Delay = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].TaskID = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].inUse = 0;
}


void print_time_10ms(void)
{
    char msg[40];

    int len = snprintf(
        msg, sizeof(msg),
        "%lu ms\r\n",
        (unsigned long)get_time()
    );

    if (len > 0)
    {
        HAL_UART_Transmit(
            &huart2,
            (uint8_t*)msg,
            (uint16_t)len,
            1000
        );
    }
}




//task is defined from here
extern UART_HandleTypeDef huart2;
//time stamp is stored here
char buf_time[8];
char red_call[] = " : Toggle red\r";
char yellow_call[] = " : Toggle yellow\r";
char green_call[] = " : Toggle green\r";
char blue_call[] = " : Toggle blue\r";
char aqua_call[] = " : Toggle aqua\r";


void red()
{
	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)red_call, sizeof(red_call), 2000);
}

void yellow()
{
	HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)yellow_call, sizeof(yellow_call), 2000);
}

void green()
{
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
	sprintf(buf_time,"%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)green_call, sizeof(green_call), 2000);
}

void blue()
{
	HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)blue_call, sizeof(blue_call), 2000);
}

void aqua()
{
	HAL_GPIO_TogglePin(AQUA_LED_GPIO_Port, AQUA_LED_Pin);
	sprintf(buf_time, "%d",real_time);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf_time,strlen(buf_time) , 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)aqua_call, sizeof(aqua_call), 2000);
}
