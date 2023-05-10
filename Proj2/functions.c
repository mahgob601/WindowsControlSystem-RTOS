#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include "types.h"
#include <semphr.h>
#include "queue.h"


extern xQueueHandle xQueuePD;
extern xTaskHandle openCloseDriverHandler;
extern xTaskHandle openClosePassengerHandler;
extern xTaskHandle controlHandler;
extern xSemaphoreHandle xBinarySemaphore1;
extern xSemaphoreHandle xBinarySemaphore2;


void openCloseDriver() {
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphore1,portMAX_DELAY);
	 
	//DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);	
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,1);
		while(DIO_ReadPin(&GPIO_PORTF_DATA_R,4) == 0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
	}
	else if(order == 0){
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,1);
		while(DIO_ReadPin(&GPIO_PORTF_DATA_R,0) == 0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
		
	}
	DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
	DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
	DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
	taskYIELD();
}
 }

 void openClosePassenger() {
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphore2,portMAX_DELAY);
	 
	//DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);	
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,1);
		while(DIO_ReadPin(&GPIO_PORTB_DATA_R,0) == 1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
	}
	else if(order == 0){
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,1);
		while(DIO_ReadPin(&GPIO_PORTB_DATA_R,1) == 1);
		DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
		
	}
	DIO_WritePin(&GPIO_PORTA_DATA_R,2,0);
	DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
	DIO_WritePin(&GPIO_PORTA_DATA_R,4,0);
	taskYIELD();
}
	
}
 

 
void control(){
	
	
	int up =1;
	int down =0;
	xQueuePD = xQueueCreate(1 , sizeof(long));
	
	while(1){
		//DIO_WritePin(&GPIO_PORTA_DATA_R,3,0);
		//DIO_WritePin(&GPIO_PORTA_DATA_R,4,0); 
		
		if(DIO_ReadPin(&GPIO_PORTF_DATA_R,4) == 0){
		//high pri
			//send in queue
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphore1);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTF_DATA_R,0) == 0){
		//high pri
			//send in queue
			
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphore1);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,0) == 1){// for passenger down
		//high pri
			//send in queue
			
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphore2);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,1) == 1){// for passener up
		//high pri
			//send in queue
			
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphore2);
	
		}
	}

}
	