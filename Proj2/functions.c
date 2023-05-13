#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "DIO.h"
#include "motorControl.h"
#include "bitwise_operation.h"
#include "types.h"
#include <semphr.h>
#include "queue.h"


extern xQueueHandle xQueuePD;
extern xTaskHandle openCloseDriverHandler;
extern xTaskHandle openCloseDriverAutoHandler;
extern xTaskHandle openClosePassengerHandler;
extern xTaskHandle openClosePassengerAutoHandler;
extern xTaskHandle controlHandler;
extern xTaskHandle ObstacleHandler;

extern xSemaphoreHandle xBinarySemaphore1;
extern xSemaphoreHandle xBinarySemaphore2;
extern xSemaphoreHandle xBinarySemaphoreDriverAuto;
extern xSemaphoreHandle xBinarySemaphorePassengerAuto;
extern xSemaphoreHandle xBinarySemaphoreObstacle;

//1 up
void Obstacle(){
	
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphoreObstacle,portMAX_DELAY); 
	motorOFF();	
	motorDOWN();
	for(int k=0; k<4000000; k++);
	motorOFF();
	for(int k=0; k<2000000; k++);
	vTaskPrioritySet(NULL,2);
	taskYIELD();
	}

	
}
void openClosePassengerAuto(){
	
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphorePassengerAuto,portMAX_DELAY);
	 
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		motorUP();
		//while(DIO_ReadPin(&GPIO_PORTB_DATA_R,2) != 1);
		while(((*(&GPIO_PORTB_DATA_R) & (1<<2))>>2) != 1 && DIO_ReadPin(&GPIO_PORTA_DATA_R,7) != 1){
		for(int i=0;i < 1000;i++){}
			
		}
		if(DIO_ReadPin(&GPIO_PORTA_DATA_R,7) == 1){
			xSemaphoreGive(xBinarySemaphoreObstacle);
			vTaskPrioritySet(ObstacleHandler, 3);
		
		}
		int x = 0;
	}
	else if(order == 0){
		
		motorDOWN();
		while(((*(&GPIO_PORTB_DATA_R) & (1<<3))>>3) != 1){
		for(int i=0;i < 1000;i++){}
		}
		int x = 0;
		
	}
	motorOFF();
	taskYIELD();
	}
}

void openCloseDriverAuto() {
	
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphoreDriverAuto,portMAX_DELAY);
	 
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		motorUP();
		//while(DIO_ReadPin(&GPIO_PORTB_DATA_R,2) != 1);
		while(((*(&GPIO_PORTB_DATA_R) & (1<<2))>>2) != 1 && DIO_ReadPin(&GPIO_PORTA_DATA_R,7) != 1){
		for(int i=0;i < 1000;i++){}
			
		}
		if(DIO_ReadPin(&GPIO_PORTA_DATA_R,7) == 1){
			xSemaphoreGive(xBinarySemaphoreObstacle);
			vTaskPrioritySet(ObstacleHandler, 3);
		
		}
		int x = 0;
	}
	else if(order == 0){
		
		motorDOWN();
		while(((*(&GPIO_PORTB_DATA_R) & (1<<3))>>3) != 1){
		for(int i=0;i < 1000;i++){}
		}
		int x = 0;
		
	}
	motorOFF();
	taskYIELD();
}
	
	
}

void openCloseDriver() {
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphore1,portMAX_DELAY);
	 
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		
		motorUP();
		while(DIO_ReadPin(&GPIO_PORTF_DATA_R,4) == 0 && DIO_ReadPin(&GPIO_PORTB_DATA_R,2) != 1 && DIO_ReadPin(&GPIO_PORTA_DATA_R,7) != 1);
		if(DIO_ReadPin(&GPIO_PORTA_DATA_R,7) == 1){
			xSemaphoreGive(xBinarySemaphoreObstacle);
			
			vTaskPrioritySet(ObstacleHandler, 3);
		
		}
	}
	else if(order == 0){
		
		motorDOWN();
		while(DIO_ReadPin(&GPIO_PORTF_DATA_R,0) == 0 && DIO_ReadPin(&GPIO_PORTB_DATA_R,3) != 1);
		
		
		
		
	}
	motorOFF();
	taskYIELD();
}
 }

 void openClosePassenger() {
	int order;
	while(1)
	{
	xSemaphoreTake(xBinarySemaphore2,portMAX_DELAY);
  xQueueReceive(xQueuePD,&order ,portMAX_DELAY);
	if(order == 1){
		
		
		motorUP();
		//while(DIO_ReadPin(&GPIO_PORTB_DATA_R,4) == 1 && DIO_ReadPin(&GPIO_PORTB_DATA_R,2) != 1 && DIO_ReadPin(&GPIO_PORTA_DATA_R,7)!=1 ){
		while(DIO_ReadPin(&GPIO_PORTB_DATA_R,4) == 1 && DIO_ReadPin(&GPIO_PORTB_DATA_R,2) != 1 && DIO_ReadPin(&GPIO_PORTA_DATA_R,7) != 1){
		
		for(int i=0;i<100;i++){}
			
		}
		if(DIO_ReadPin(&GPIO_PORTA_DATA_R,7) == 1){
			xSemaphoreGive(xBinarySemaphoreObstacle);
			vTaskPrioritySet(ObstacleHandler, 3);
		
		}
		/*if(DIO_ReadPin(&GPIO_PORTA_DATA_R,7)==1){
			xSemaphoreGive(xBinarySemaphoreObstacle);
		}*/
	}
	else if(order == 0){
		
		motorDOWN();
		while(DIO_ReadPin(&GPIO_PORTB_DATA_R,6) == 1 && DIO_ReadPin(&GPIO_PORTB_DATA_R,3) != 1){
		for(int i=0;i<100;i++){}
		}
	}
	
	motorOFF();
	taskYIELD();
}
	
}
 

void control(){
	int up =1;
	int down =0;
	xQueuePD = xQueueCreate(1 , sizeof(long));
	
	while(1){
		if(DIO_ReadPin(&GPIO_PORTF_DATA_R,4) == 0){
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphore1);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTF_DATA_R,0) == 0){
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphore1);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,0) == 1){// for Driver auto up
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphoreDriverAuto);
	
		}else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,5) == 1){// for Driver auto down
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphoreDriverAuto);
	
		}
		
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,4) == 1){// for passenger up
		//high pri
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphore2);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,6) == 1){// for passenger down
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphore2);
	
		}
		
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,1) == 1){// for passener up auto
			xQueueSend(xQueuePD, &up, 0);	
			xSemaphoreGive(xBinarySemaphorePassengerAuto);
	
		}
		else if(DIO_ReadPin(&GPIO_PORTB_DATA_R,7) == 1){// for passener up auto
			xQueueSend(xQueuePD, &down, 0);	
			xSemaphoreGive(xBinarySemaphorePassengerAuto);
	
		}
		
		
		
		
		
		
		
	}

}
	