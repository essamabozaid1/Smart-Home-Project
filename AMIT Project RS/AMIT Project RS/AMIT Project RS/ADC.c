/*
 * ADC.c
 *
 * Created: 2/28/2020 8:10:32 PM
 *  Author: lenovo
 */ 
#include "ADC.h"

void ADC_Init(uint8 With_Interrupt){
	
	/*choose Right Adjust for ADC DATA Register*/
	Clear_Bit(ADMUX,ADLAR);
	
	/*Disable Auto Trigger*/ 
	Clear_Bit(ADCSRA,ADATE);
	/*Select the Prescalar division factor to 128 ( Freq= F_CPU/128)=125KHz*/
	Set_Bit(ADCSRA,ADPS0);
	Set_Bit(ADCSRA,ADPS1);
	Set_Bit(ADCSRA,ADPS2);
	/*enable Analog to Digital Conversion*/
	Set_Bit(ADCSRA,ADEN);
	/* Enable ADC Interrupt*/
	if (With_Interrupt==1)
	{
		cli();
		Set_Bit(ADCSRA,ADIE);
		sei();
	}else{
		Clear_Bit(ADCSRA,ADIE);
	}
}
uint16 ADC_Read(ADCChannals_t channal_num,Ref_Pin_t Ref_Pin){
	/* Voltage Refrernce selection set to AVCC  0 | 1 */
	switch(Ref_Pin){
		case AREF_Pin:
			Clear_Bit(ADMUX,REFS0);
			Clear_Bit(ADMUX,REFS1);
			break;
		case AVCC_Pin:
			Set_Bit(ADMUX,REFS0);
			Clear_Bit(ADMUX,REFS1);
			break;
		case Internal_Volt:
			Set_Bit(ADMUX,REFS0);
			Set_Bit(ADMUX,REFS1);
			break;
		default:
			break;
	}
	if(channal_num>=0 && channal_num<=31){
		(Read_Bit(channal_num,0)==HIGH) ? Set_Bit(ADMUX,MUX0):Clear_Bit(ADMUX,MUX0);
		(Read_Bit(channal_num,1)==HIGH) ? Set_Bit(ADMUX,MUX1):Clear_Bit(ADMUX,MUX1);
		(Read_Bit(channal_num,2)==HIGH) ? Set_Bit(ADMUX,MUX2):Clear_Bit(ADMUX,MUX2);
		(Read_Bit(channal_num,3)==HIGH) ? Set_Bit(ADMUX,MUX3):Clear_Bit(ADMUX,MUX3);
		(Read_Bit(channal_num,4)==HIGH) ? Set_Bit(ADMUX,MUX4):Clear_Bit(ADMUX,MUX4);
		
		/* start single conversion */
		Set_Bit(ADCSRA,ADSC);
		//wait for conversion to complete
		//ADSC becomes ’0? again
		//till then, run loop continuously
		if (!Read_Bit(ADCSRA,ADIE))
		{
			while(Read_Bit(ADCSRA,ADSC));
		}		
	}
	return ADC;
}
