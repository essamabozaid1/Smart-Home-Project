/*
 * Timer0.h
 *
 * Created: 3/14/2020 5:05:24 PM
 *  Author: moham
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "STD_Types.h"

typedef enum
{
	NORMAL,
	PHASE_CORRECT,
	CTC,
	F_PWM	
}TIMER0_Mode_t;

typedef enum
{
	NO_CLK,
	NO_PRESC,
	PRESC_8,
	PRESC_64,
	PRESC_256,
	PRESC_1024,
	EXT_T0_FALL,
	EXT_T0_RIS	
}TIMER0_Prescaler_t;

typedef enum
{
	DISCONNECT,
	TOGGLE,
	NIN_INVERTING,
	INVERTING
}TIMER0_Output_Mode_t;

extern void  TIMER0_Init(TIMER0_Mode_t mode);
extern void  TIMER0_Start(TIMER0_Prescaler_t presc);
extern void  TIMER0_Stop(void);
extern uint8 TIMER0_GetCount(void);
extern void  TIMER0_SetDutyCycle(uint8 duty);
extern void  TIMER0_SetCompareValue(uint8 comp);
extern void  TIMER0_SetOutputMode(TIMER0_Output_Mode_t mode);





#endif /* TIMER0_H_ */