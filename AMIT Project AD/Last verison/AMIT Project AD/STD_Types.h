/*
 * STD_Types.h
 *
 * Created: 1/19/2020 9:22:21 PM
 *  Author: lenovo
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define HIGH 1
#define LOW 0
	
#define Set_Bit(REG,BIT)		(REG|=(1<<BIT))
#define Clear_Bit(REG,BIT)		(REG&=(~(1<<BIT)))
#define Toggle_Bit(REG,BIT)	    (REG^=(1<<BIT))
#define Read_Bit(REG,BIT)		(1&(REG>>BIT))

#define Clear_Reg(REG)			(REG=0x00)

#define GetPort(Pin_Num)		(Pin_Num/8)
#define GetPin(Pin_Num)			(Pin_Num%8)



typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;



#endif /* STD_TYPES_H_ */