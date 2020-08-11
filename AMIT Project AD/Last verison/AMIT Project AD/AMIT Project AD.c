/*
 * AMIT_Project_AD.c
 *
 * Created: 4/9/2020 5:05:53 AM
 *  Author: lenovo
 */ 



#include "STD_Types.h"
#include "DIO.h"
#include "LCD.h"
#include "TWI_driver.h"
#include "EEPROM_Internal.h"
#include "LED.h"
#include "Motor.h"
extern volatile uint8 _Data;
extern volatile Ret_t _ret;
typedef struct{
	uint8 ACT_States[11];
	uint8 ACT_Addresses[11];
	}ACT_Table;
typedef enum{
	AC_Motor0_ID=0,
	AC_Motor1_ID  ,
	AC_Motor2_ID  ,
	LED0_ID	   ,
	LED1_ID	   ,
	LED2_ID	   ,
	Door_LED0_ID,
	Door_LED1_ID,
	Door_LED2_ID,
	Door_LED3_ID,
	Door_LED4_ID,	
	}ACT_ID;
ACT_Table ACT_Init(){
	// Create Structue as a table  ACT States | ACT Addresses 
	
	// Read the Last States of Actuator From EEPROM (when happen Error and ECU initiate again) and Put them into the table
	ACT_Table ST;
	//--------------- put Addresses in Table -------------
	ST.ACT_Addresses[0]=Address_AC_Motor0;
	ST.ACT_Addresses[1]=Address_AC_Motor1;
	ST.ACT_Addresses[2]=Address_AC_Motor2;
	
	ST.ACT_Addresses[3]=Address_LED0;
	ST.ACT_Addresses[4]=Address_LED1;
	ST.ACT_Addresses[5]=Address_LED2;
	
	ST.ACT_Addresses[6] =Address_Door_LED0;
	ST.ACT_Addresses[7] =Address_Door_LED1;
	ST.ACT_Addresses[8] =Address_Door_LED2;
	ST.ACT_Addresses[9] =Address_Door_LED3;
	ST.ACT_Addresses[10]=Address_Door_LED4;
	//---------------------------------------------------
	uint8 i;
	//EEPROM_Write(ST.ACT_Addresses[0],0);
	for(i=0;i<11;i++){
		ST.ACT_States[i]=EEPROM_Read(ST.ACT_Addresses[i]);
	}
	return ST; 
}
int main(void)
{
	uint8 Sen_ID,Sen_Reading;
	TWI_SlaveInit(0x7A);
	
	Motor_Init(AC_Motor0);	//Operate depending Readings of temperature sensor > threshold ->High Speed. =threshold -> medium speed. <threshold ->stop
	Motor_Init(AC_Motor1);	//Operate depending Readings of temperature sensor > threshold ->High Speed. =threshold -> medium speed. <threshold ->stop
	Motor_Init(AC_Motor2);	//Operate depending Readings of temperature sensor > threshold ->High Speed. =threshold -> medium speed. <threshold ->stop
	
	Motor_Init(Door_LED0);  // simulate as a led operate depending Motion Detection sensor
	Motor_Init(Door_LED1);	// simulate as a led operate depending Motion Detection sensor
	Motor_Init(Door_LED2);	// simulate as a led operate depending Motion Detection sensor
	Motor_Init(Door_LED3);	// simulate as a led operate depending Motion Detection sensor
	Motor_Init(Door_LED4);	// simulate as a led operate depending Motion Detection sensor
	
	Led_Init(Led0);			 // Operate depending Readings of Lighting Sensor
	Led_Init(Led1);			 // Operate depending Readings of Lighting Sensor
	Led_Init(Led2);			 // Operate depending Readings of Lighting Sensor
	
	ACT_Table ST=ACT_Init();	//read the Actuator states from EEPROM 
    while(1)
    {
		// receiving data from RS
		if(_ret==OK){ // to Reading I2C
			_ret=NOK;
			Sen_ID=_Data>>4;
			Sen_Reading=_Data & 0x0F;
			ST.ACT_States[Sen_ID]=Sen_Reading;
			EEPROM_Write(ST.ACT_Addresses[Sen_ID],Sen_Reading);
			//SensorID++;
		}
		
		//---------------
		//=============== A/C MOTOR=================
		//--------------- A/C MOTOR0---------------
		if(ST.ACT_States[AC_Motor0_ID]==0){
			//stop
			Motor_Handler(AC_Motor0,Stop);
		}else if(ST.ACT_States[AC_Motor0_ID]==1){
			//low Speed
			Motor_Handler(AC_Motor0,Medium_Speed);	
		}else if (ST.ACT_States[AC_Motor0_ID]==2)
		{
			Motor_Handler(AC_Motor0,High_Speed);
			// High Speed
		}else{}
		//--------------- A/C MOTOR1---------------
		if(ST.ACT_States[AC_Motor1_ID]==0){
			//stop
			Motor_Handler(AC_Motor1,Stop);
		}else if(ST.ACT_States[AC_Motor1_ID]==1){
			//low Speed
			Motor_Handler(AC_Motor1,Medium_Speed);	
		}else if (ST.ACT_States[AC_Motor1_ID]==2)
		{
			Motor_Handler(AC_Motor1,High_Speed);
			// High Speed
		}else{}
		//--------------- A/C MOTOR2---------------
		if(ST.ACT_States[AC_Motor2_ID]==0){
			//stop
			Motor_Handler(AC_Motor2,Stop);
		}else if(ST.ACT_States[AC_Motor2_ID]==1){
			//low Speed
			Motor_Handler(AC_Motor2,Medium_Speed);
			
		}else if (ST.ACT_States[AC_Motor2_ID]==2)
		{
			Motor_Handler(AC_Motor2,High_Speed);
			// High Speed
		}else{}
			
		//===============LEDS ========================
		//---------------LED0-------------------------
		if(ST.ACT_States[LED0_ID]==HIGH){
			Led_Handler(Led0,HIGH);
		}else if(ST.ACT_States[LED0_ID]==LOW){
			Led_Handler(Led0,LOW);	
		}else{}
		//---------------LED1-------------------------
		if(ST.ACT_States[LED1_ID]==HIGH){
			Led_Handler(Led1,HIGH);
		}else if(ST.ACT_States[LED1_ID]==LOW){
			Led_Handler(Led1,LOW);
		}else{}
		//---------------LED2-------------------------
		if(ST.ACT_States[LED2_ID]==HIGH){
			Led_Handler(Led2,HIGH);
		}else if(ST.ACT_States[LED2_ID]==LOW){
			Led_Handler(Led2,LOW);
		}else{}
		//================DOOR Motors ================
		//--------------- DOOR MOTOR0---------------
		if(ST.ACT_States[Door_LED0_ID]==0){
			//stop
			Motor_Handler(Door_LED0,Stop);
		}else if(ST.ACT_States[Door_LED0_ID]==1){
			//High-speed
			Motor_Handler(Door_LED0,High_Speed);
		}else{}
		//--------------- DOOR MOTOR1---------------
		if(ST.ACT_States[Door_LED1_ID]==0){
			//stop
			Motor_Handler(Door_LED1,Stop);
		}else if(ST.ACT_States[Door_LED1_ID]==1){
			//High-speed
			Motor_Handler(Door_LED1,High_Speed);
		}else{}
		//--------------- DOOR MOTOR2---------------
		if(ST.ACT_States[Door_LED2_ID]==0){
			//stop
			Motor_Handler(Door_LED2,Stop);
		}else if(ST.ACT_States[Door_LED2_ID]==1){
			//High-speed
			Motor_Handler(Door_LED2,High_Speed);
		}else{}
		//--------------- DOOR MOTOR3---------------
		if(ST.ACT_States[Door_LED3_ID]==0){
			//stop
			Motor_Handler(Door_LED3,Stop);
		}else if(ST.ACT_States[Door_LED3_ID]==1){
			//High-speed
			Motor_Handler(Door_LED3,High_Speed);
		}else{}
		//--------------- DOOR MOTOR4---------------
		if(ST.ACT_States[Door_LED4_ID]==0){
			//stop
			Motor_Handler(Door_LED4,Stop);
		}else if(ST.ACT_States[Door_LED4_ID]==1){
			//High-speed
			Motor_Handler(Door_LED4,High_Speed);
		}else{}	
		//============================================
		 
    }
}