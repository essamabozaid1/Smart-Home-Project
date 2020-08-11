/*
 * AMIT_Project_RS.c
 *
 * Created: 4/4/2020 4:12:21 PM
 *  Author: lenovo
 */ 



#include "STD_Types.h"
#include "DIO.h"
#include "ADC.h"
#include "LM35.h"
#include "LDR.h"
#include "MotionDectection.h"
#include "EEPROM_Internal.h"
#include "Timer0.h"
#include "TWI_driver.h"
volatile uint8 Comp_Counter=0;
volatile uint8 Sensors_Reading_Flag=0;
typedef enum{
	Sensor1_ID=0,
	Sensor2_ID,
	Sensor3_ID,
	Sensor4_ID,
	Sensor5_ID,
	Sensor6_ID,
	Sensor7_ID,
	Sensor8_ID,
	Sensor9_ID,
	Sensor10_ID,
	Sensor11_ID,	
}enumSensorID_t;
int main(void)
{
	ADC_Init(0); // ADC init Without Interrupt
	
	LM35_Init(LM35_Sensor1);	 //Dio init as a infree
	LM35_Init(LM35_Sensor2);	 //Dio init as a infree
	LM35_Init(LM35_Sensor3);	 //Dio init as a infree
	
	LDR_Init(LDR_Sensor1);		 //Dio init as a infree
	LDR_Init(LDR_Sensor2);		 //Dio init as a infree
	LDR_Init(LDR_Sensor3);		 //Dio init as a infree
	
	MotionDetection_Init(MotionDetection_Sensor1);		//Dio init as a infree
	MotionDetection_Init(MotionDetection_Sensor2);		//Dio init as a infree
	MotionDetection_Init(MotionDetection_Sensor3);		//Dio init as a infree
	MotionDetection_Init(MotionDetection_Sensor4);		//Dio init as a infree
	MotionDetection_Init(MotionDetection_Sensor5);		//Dio init as a infree
	
	// LM35 Sensor Variable 							
	uint16 LM35_Value1=0;
	uint16 LM35_Value2=0;
	uint16 LM35_Value3=0;
	uint16 LM35_Last_Value1=0;
	uint16 LM35_Last_Value2=0;
	uint16 LM35_Last_Value3=0;
	// End LM35 Sensor Variable
	
	// LDR Sensor Variable
	uint16 LDR_Value1=0;
	uint16 LDR_Value2=0;
	uint16 LDR_Value3=0;
	uint16 LDR_Last_Value1=0;
	uint16 LDR_Last_Value2=0;
	uint16 LDR_Last_Value3=0;
	// End LDR Sensor Variable	
	
	// MD Sensor Variable
	uint8 MD_Values[5]={0,0,0,0,0};
	uint8 MD_Last_Values[5]={0,0,0,0,0};
	// End MD Sensor Variable
	
	EEPROM_Write(Address_LM35_Sensor1,24);
	EEPROM_Write(Address_LM35_Sensor2,24);
	EEPROM_Write(Address_LM35_Sensor3,24);
	
	EEPROM_Write(Address_LDR_Sensor1,100);
	EEPROM_Write(Address_LDR_Sensor2,100);
	EEPROM_Write(Address_LDR_Sensor3,100);
		
	uint8 Frame=0;
	//Ret_t enuRet=NOK;
	TWI_MasterInit(100,TWI_PRESC_1);
	
	TIMER0_Init(CTC);
	TIMER0_SetCompareValue(249);// for generate 200 ms with Pres= 256 and number of On compare Match Counts = 50 and OCR0=249
	TIMER0_Start(PRESC_256);
	
	
    while(1)
    {		
		/*==================================== Periodic Sensors Reading every 200ms=================================*/ 
		if(Sensors_Reading_Flag==1){
			Sensors_Reading_Flag=0;
			LM35_Value1=LM35_Read(LM35_Sensor1);  // read the current value of the LM35 Sensor	  but positive range
			LM35_Value2=LM35_Read(LM35_Sensor2);  // read the current value of the LM35 Sensor	  but positive range
			LM35_Value3=LM35_Read(LM35_Sensor3);  // read the current value of the LM35 Sensor	  but positive range
			
			LDR_Value1=LDR_Read(LDR_Sensor1);	// read the current value of the LDR Sensor
			LDR_Value2=LDR_Read(LDR_Sensor2);	// read the current value of the LDR Sensor
			LDR_Value3=LDR_Read(LDR_Sensor3);	// read the current value of the LDR Sensor
			
			MD_Values[0]=MotionDetection_Read(MotionDetection_Sensor1);
			MD_Values[1]=MotionDetection_Read(MotionDetection_Sensor2);
			MD_Values[2]=MotionDetection_Read(MotionDetection_Sensor3);
			MD_Values[3]=MotionDetection_Read(MotionDetection_Sensor4);
			MD_Values[4]=MotionDetection_Read(MotionDetection_Sensor5);
		}
		/*========================================================================================================== */
			
		if(LM35_Value1!=LM35_Last_Value1){ // check if the value changed
			LM35_Last_Value1=LM35_Value1;	//update the last value 
			if(LM35_Value1<EEPROM_Read(Address_LM35_Sensor1)){
				//Send 0 that indicate not operate A/C Motor 
				Frame=(Sensor1_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				//enuRet=NOK;
				TWI_Write(Frame);
				//enuRet =NOK;
				TWI_MasterStop();
			}else if (LM35_Value1==EEPROM_Read(Address_LM35_Sensor1))
			{
				//Send 1 that indicate operate A/C Motor with low Speed
				Frame=(Sensor1_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
				
			}else if (LM35_Value1>EEPROM_Read(Address_LM35_Sensor1))
			{
				//Send 2 that indicate operate A/C Motor with High Speed
				Frame=(Sensor1_ID<<4)| 2;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}	
		}
		//........................................................
		if(LM35_Value2!=LM35_Last_Value2){
			LM35_Last_Value2=LM35_Value2;	//update the last value 
			if(LM35_Value2<EEPROM_Read(Address_LM35_Sensor2)){
				//send 0 that indicate don't operate A/C Motor
				Frame=(Sensor2_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LM35_Value2==EEPROM_Read(Address_LM35_Sensor2))
			{
				//Send 1 that indicate operate A/C Motor with low Speed
				Frame=(Sensor2_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LM35_Value2>EEPROM_Read(Address_LM35_Sensor2))
			{
				//Send 2 that indicate operate A/C Motor with High Speed
				Frame=(Sensor2_ID<<4)| 2;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}
		}
			//........................................................
		if(LM35_Value3!=LM35_Last_Value3){
			LM35_Last_Value3=LM35_Value3;	//update the last value
			if(LM35_Value3<EEPROM_Read(Address_LM35_Sensor3)){
				//send 0 that indicate don't operate A/C Motor
				Frame=(Sensor3_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LM35_Value3==EEPROM_Read(Address_LM35_Sensor3))
			{
				//Send 1 that indicate operate A/C Motor with low Speed
				Frame=(Sensor3_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LM35_Value3>EEPROM_Read(Address_LM35_Sensor3))
			{
				//Send 2 that indicate operate A/C Motor with High Speed
				Frame=(Sensor3_ID<<4)| 2;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}
		}
		//=========================================================================
			
		if(LDR_Value1!=LDR_Last_Value1){ // check if the value changed
			LDR_Last_Value1=LDR_Value1;	//update the last value				
			if(LDR_Value1<=EEPROM_Read(Address_LDR_Sensor1)){
				//Send 0 that indicate Close the LED
				Frame=(Sensor4_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LDR_Value1>EEPROM_Read(Address_LDR_Sensor1))
			{
				//Send 1 that indicate open the LED
				Frame=(Sensor4_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}
		}
			//........................................................
		if(LDR_Value2!=LDR_Last_Value2){ // check if the value changed
			LDR_Last_Value2=LDR_Value2;	//update the last value
			if(LDR_Value2<=EEPROM_Read(Address_LDR_Sensor2)){
				
				//send 0 that indicate Close the LED
				Frame=(Sensor5_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LDR_Value2>EEPROM_Read(Address_LDR_Sensor2))
			{
				//Send 1 that indicate Open the LED
				Frame=(Sensor5_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}
		}
			//........................................................
		if(LDR_Value3!=LDR_Last_Value3){ // check if the value changed
			LDR_Last_Value3=LDR_Value3;	//update the last value
			if(LDR_Value3<=EEPROM_Read(Address_LDR_Sensor3)){
				//send 0 that indicate Close the LED
				Frame=(Sensor6_ID<<4)| 0;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else if (LDR_Value3>EEPROM_Read(Address_LDR_Sensor3))
			{
				//Send 1 that indicate open the LED
				Frame=(Sensor6_ID<<4)| 1;
				TWI_MasterStart(0x7A,WRITE);
				TWI_Write(Frame);
				TWI_MasterStop();
			}else{}
		}
		//=========================================================================
		if(	MD_Values[0]!=MD_Last_Values[0]){
			MD_Last_Values[0]= MD_Values[0];
			Frame=(Sensor7_ID<<4)| MD_Values[0];
			TWI_MasterStart(0x7A,WRITE);
			TWI_Write(Frame);
			TWI_MasterStop();	
		}else{}
		if(	MD_Values[1]!=MD_Last_Values[1]){
			MD_Last_Values[1]= MD_Values[1];
			Frame=(Sensor8_ID<<4)| MD_Values[1];
			TWI_MasterStart(0x7A,WRITE);
			TWI_Write(Frame);
			TWI_MasterStop();
		}else{}
		if(	MD_Values[2]!=MD_Last_Values[2]){
			MD_Last_Values[2]= MD_Values[2];
			Frame=(Sensor9_ID<<4)| MD_Values[2];
			TWI_MasterStart(0x7A,WRITE);
			TWI_Write(Frame);
			TWI_MasterStop();
		}else{}
		if(	MD_Values[3]!=MD_Last_Values[3]){
			MD_Last_Values[3]= MD_Values[3];
			Frame=(Sensor10_ID<<4)| MD_Values[3];
			TWI_MasterStart(0x7A,WRITE);
			TWI_Write(Frame);
			TWI_MasterStop();
		}else{}
		if(	MD_Values[4]!=MD_Last_Values[4]){
			MD_Last_Values[4]= MD_Values[4];
			Frame=(Sensor11_ID<<4)| MD_Values[4];
			TWI_MasterStart(0x7A,WRITE);
			TWI_Write(Frame);
			TWI_MasterStop();
		}else{}
    }
}


ISR(TIMER0_COMP_vect){
	Comp_Counter++;
	if(Comp_Counter==50){
		Comp_Counter=0;
		Sensors_Reading_Flag=1;
	}
}