/*
 * timer.h
 *
 *  Created on: Oct 26, 2025
 *      Author: josh
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int timer4_flag;
extern int timer5_flag;

extern const int TIMER_CYCLE;
uint32_t get_time(void);

void timerRun();

void setTimer1(uint32_t duration);
void setTimer2(uint32_t duration);
void setTimer3(uint32_t duration);
void setTimer4(uint32_t duration);
void setTimer5(uint32_t duration);

void SCH_Update(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern uint8_t real_time;

#endif /* INC_TIMER_H_ */
