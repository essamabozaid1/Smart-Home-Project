/*
 * ADC.h
 *
 * Created: 2/28/2020 8:10:46 PM
 *  Author: lenovo
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "STD_Types.h"
typedef enum{
	ADC0_CH,
	ADC1_CH,
	ADC2_CH,
	ADC3_CH,
	ADC4_CH,
	ADC5_CH,
	ADC6_CH,
	ADC7_CH
	}ADCChannals_t;
typedef enum{
	AREF_Pin=0,
	AVCC_Pin=1,
	Internal_Volt=3,
	}Ref_Pin_t;


void ADC_Init(uint8 With_Interrupt);
uint16 ADC_Read(ADCChannals_t channal_num,Ref_Pin_t Ref_Pin);



#endif /* ADC_H_ */