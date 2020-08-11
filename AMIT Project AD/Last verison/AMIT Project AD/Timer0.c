
/*
 * Timer0.S
 *
 * Created: 3/14/2020 5:05:00 PM
 *  Author: moham
 */ 
 #include "Timer0.h"
 
 void  TIMER0_Init(TIMER0_Mode_t mode)
{
	cli();
	
	Clear_Bit(TCCR0,FOC0);
	
	Read_Bit(mode,0) == HIGH ? Set_Bit(TCCR0,WGM00): Clear_Bit(TCCR0,WGM00);
	Read_Bit(mode,1) == HIGH ? Set_Bit(TCCR0,WGM01): Clear_Bit(TCCR0,WGM01);
	switch(mode){
		case NORMAL:
			Set_Bit(TIMSK,TOIE0);
		break;
		case PHASE_CORRECT:
		case F_PWM:
			Set_Bit(TIMSK,TOIE0);
			Set_Bit(TIMSK,OCIE0);
		break;
		case CTC:
			Set_Bit(TIMSK,OCIE0);		
		break;
		default:
		break;
	}
	TCNT0 = 0;
	OCR0  = 0;
	 
    sei();
}
void  TIMER0_Start(TIMER0_Prescaler_t presc)
{
	Read_Bit(presc,0) == HIGH ? Set_Bit(TCCR0,CS00):Clear_Bit(TCCR0,CS00);
	Read_Bit(presc,1) == HIGH ? Set_Bit(TCCR0,CS01):Clear_Bit(TCCR0,CS01);
	Read_Bit(presc,2) == HIGH ? Set_Bit(TCCR0,CS02):Clear_Bit(TCCR0,CS02);
}
void  TIMER0_Stop(void)
{
	TIMER0_Start(NO_CLK);
}
uint8 TIMER0_GetCount(void)
{
	return TCNT0;
}
void  TIMER0_SetDutyCycle(uint8 duty)
{
	uint8 OutMode = Read_Bit(TCCR0,COM00) | (Read_Bit(TCCR0,COM01)<<1);
	if(OutMode == INVERTING)
	{
		/* DUTY_CYCLE = (0xFF-OCR0)/0xFF*/
		OCR0  = 0xFF - ((duty/100.0)*0xFF);
	}
	else if (OutMode == NIN_INVERTING)
	{
		/* DUTY_CYCLE = OCR0/0xFF*/
		OCR0 = ((duty/100.0)*0xFF);
	}
	else{
			// Not Correct as a good driver but in the kit the OC0 is Connected to LCD_E
			OCR0 = ((duty/100.0)*0xFF);
		}
}
void  TIMER0_SetCompareValue(uint8 comp)
{
	OCR0 = comp;
}
void  TIMER0_SetOutputMode(TIMER0_Output_Mode_t mode)
{
	Read_Bit(mode,0) == HIGH ? Set_Bit(TCCR0,COM00): Clear_Bit(TCCR0,COM00);
	Read_Bit(mode,1) == HIGH ? Set_Bit(TCCR0,COM01): Clear_Bit(TCCR0,COM01);
}