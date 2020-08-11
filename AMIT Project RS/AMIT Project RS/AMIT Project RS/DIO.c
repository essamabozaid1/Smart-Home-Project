/*
 * DIO.c
 *
 * Created: 1/19/2020 10:15:46 PM
 *  Author: lenovo
 */ 
#include "STD_Types.h"
#include "DIO.h"

extern const DIO_Pin_State_t Pin_State[];

uint8 DIO_ReadPin(DIO_Port_t Port_Num,uint8 Pin_Num){
	volatile uint8 Pin_Level =LOW;
	switch(Port_Num){
		case PA: 
			//Clear_Bit(DDRA,Pin_Num);
			Pin_Level=Read_Bit(PINA,Pin_Num);
			break;
		case PB:
			//Clear_Bit(DDRB,Pin_Num);
			Pin_Level=Read_Bit(PINB,Pin_Num);
			break;
		case PC:
			//Clear_Bit(DDRC,Pin_Num);
			Pin_Level=Read_Bit(PINC,Pin_Num);
		break;
		case PD:
			//Clear_Bit(DDRD,Pin_Num);
			Pin_Level=Read_Bit(PIND,Pin_Num);
		break;
		default:
		break;
	}
	return Pin_Level;
	
}
void DIO_WritePin(DIO_Port_t Port_Num,uint8 Pin_Num,uint8 Level){
	switch(Port_Num){
		case PA :
				//Set_Bit(DDRA,Pin_Num);
				if(HIGH==Level){
					Set_Bit(PORTA,Pin_Num);
				}else{
					Clear_Bit(PORTA,Pin_Num);
				}
				break;
			case PB :
				//Set_Bit(DDRB,Pin_Num);
				if(HIGH==Level){
					Set_Bit(PORTB,Pin_Num);
				}else{
					Clear_Bit(PORTB,Pin_Num);
				}
				break;
			case PC :
				//Set_Bit(DDRC,Pin_Num);
				if(HIGH==Level){
					Set_Bit(PORTC,Pin_Num);
				}else{
					Clear_Bit(PORTC,Pin_Num);
				}
				break;
			case PD :
				//Set_Bit(DDRD,Pin_Num);
				if(HIGH==Level){
					Set_Bit(PORTD,Pin_Num);
				}else{
					Clear_Bit(PORTD,Pin_Num);
				}
				break;
			default:
				break;
	}
}
void DIO_TogglePin(DIO_Port_t Port_Num,uint8 Pin_Num){
	switch(Port_Num){
		case PA :
		//Set_Bit(DDRA,Pin_Num);
			Toggle_Bit(PORTA,Pin_Num);
		break;
		case PB :
		//Set_Bit(DDRB,Pin_Num);
			Toggle_Bit(PORTB,Pin_Num);
		break;
		case PC :
		//Set_Bit(DDRC,Pin_Num);
			Toggle_Bit(PORTC,Pin_Num);
		break;
		case PD :
		//Set_Bit(DDRD,Pin_Num);
			Toggle_Bit(PORTD,Pin_Num);
		break;
		default:
		break;
	}
}
void DIO_SetDirPin(DIO_Port_t Port_Num,uint8 Pin_Num,DIO_Pin_State_t value){
	switch(Port_Num){
		case PA :
			if(OUTPUT==value){
				Set_Bit(DDRA,Pin_Num);
			}else{
				Clear_Bit(DDRA,Pin_Num);
				if(INPULLUP==value){
					Set_Bit(PORTA,Pin_Num);
				}else{
					
				}
			}
		break;
		case PB :
			if(OUTPUT==value){
				Set_Bit(DDRB,Pin_Num);
			}else{
				Clear_Bit(DDRB,Pin_Num);
				if(INPULLUP==value){
					Set_Bit(PORTB,Pin_Num);
				}else{
						
				}
			}
		break;
		case PC :
			if(OUTPUT==value){
				Set_Bit(DDRC,Pin_Num);
			}else{
				Clear_Bit(DDRC,Pin_Num);
				if(INPULLUP==value){
					Set_Bit(PORTC,Pin_Num);
				}else{
						
				}
			}	
		break;
		case PD :
			if(OUTPUT==value){
				Set_Bit(DDRD,Pin_Num);
			}else{
				Clear_Bit(DDRD,Pin_Num);
				if(INPULLUP==value){
					Set_Bit(PORTD,Pin_Num);
				}else{
						
				}
			}
		break;
		default:
		break;
	}
}

void DIO_Init(void){
	DIO_Port_t Port_Num;
	uint8 Pin_num,i;
	for(i=0;i<Last_Pin;i++){
		Port_Num=i/8;
		Pin_num=i%8;
		switch(Port_Num){
			case PA :
				if(OUTPUT==Pin_State[i]){
					Set_Bit(DDRA,Pin_num);
				}else{
					Clear_Bit(DDRA,Pin_num);
					if(INPULLUP==Pin_State[i]){
						Set_Bit(PORTA,Pin_num);
					}else{
						
					}
				}
			case PB :
				if(OUTPUT==Pin_State[i]){
					Set_Bit(DDRB,Pin_num);
				}else{
					Clear_Bit(DDRB,Pin_num);
					if(INPULLUP==Pin_State[i]){
						Set_Bit(PORTB,Pin_num);
					}else{
					
					}
				}
			case PC :
				if(OUTPUT==Pin_State[i]){
					Set_Bit(DDRC,Pin_num);
				}else{
					Clear_Bit(DDRC,Pin_num);
					if(INPULLUP==Pin_State[i]){
						Set_Bit(PORTC,Pin_num);
					}else{
					
					}
				}
			case PD :
				if(OUTPUT==Pin_State[i]){
					Set_Bit(DDRD,Pin_num);
				}else{
					Clear_Bit(DDRD,Pin_num);
					if(INPULLUP==Pin_State[i]){
						Set_Bit(PORTD,Pin_num);
					}else{
					
					}
				}
			
		}	
	}
	
}