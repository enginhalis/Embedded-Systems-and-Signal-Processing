/*
 * main.h
 *
 *  Created on: 21 Nis 2026
 *      Author: hsann
 */

#ifndef MAIN_H_
#define MAIN_H_



#endif /* MAIN_H_ */

void enable_faults(void);

uint32_t get_psp_value(void);
void save_psp_value(uint32_t current_psp_value);
void update_next_task(void);
void update_global_tick_count(void);

__attribute__((naked)) void switch_sp_to_psp(void);

void idle_task(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

void task_delay(uint32_t tick_count);

void init_systick_timer(uint32_t tick_hz);
__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);


#define MAX_TASKS 						5

#define SIZE_TASK_STACK					1024U
#define SIZE_SCHED_STACK				1024U

#define SRAM_START						0x20000000U
#define SIZE_SRAM						( (128) * (1024) )
#define SRAM_END						( (SRAM_START) + (SIZE_SRAM))

#define T1_STACK_START					SRAM_END
#define T2_STACK_START					( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START					( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START					( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START				( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START				( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define TASK_READY_STATE 				0x00
#define TASK_BLOCKED_STATE 				0xFF

#define TICK_HZ 						1000U

#define HSI_CLOCK						16000000
#define SYSTICK_TIM_CLK					HSI_CLOCK

#define DUMMY_XPSR						0X01000000

#define INTERRUPT_DISABLE()		do{__asm volatile ("MOV R0,#0x01"); __asm volatile("MSR PRIMASK,R0"); } while(0)
#define INTERRUPT_ENABLE()		do{__asm volatile ("MOV R0,#0x00"); __asm volatile("MSR PRIMASK,R0"); } while(0)
