/*
 * LED.h
 *
 * Created: 1/20/2020 3:39:00 AM
 *  Author: lenovo
 */ 


#ifndef LED_H_
#define LED_H_


typedef enum{
	//LED Num	= Pin Num
	Led0	=   0,
	Led1	=	1,
	Led2	=	2
}Led_Num_t;
void Led_Init(Led_Num_t Led_Num);
void Led_Handler(Led_Num_t Led_Num,uint8 Level);
void Led_Toggle(Led_Num_t Led_Num);


#endif /* LED_H_ */
