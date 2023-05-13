#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include "types.h"
#include "functions.h"
#include <semphr.h>


xQueueHandle xQueuePD;
xTaskHandle openCloseDriverHandler;
xTaskHandle openCloseDriverAutoHandler;
xTaskHandle openClosePassengerHandler;
xTaskHandle openClosePassengerAutoHandler;
xTaskHandle controlHandler;
xTaskHandle ObstacleHandler;

xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;
xSemaphoreHandle xBinarySemaphoreDriverAuto;
xSemaphoreHandle xBinarySemaphorePassengerAuto;

// semaphore obstacle
xSemaphoreHandle xBinarySemaphoreObstacle;

void vApplicationIdleHook(){
}


int main(){
	DIO_init();
	
	xBinarySemaphore1 = xSemaphoreCreateBinary();
	xBinarySemaphore2 = xSemaphoreCreateBinary();
	xBinarySemaphoreDriverAuto = xSemaphoreCreateBinary();
	xBinarySemaphorePassengerAuto= xSemaphoreCreateBinary();
	// obstacle semahore
	xBinarySemaphoreObstacle = xSemaphoreCreateBinary();
	xTaskCreate(openCloseDriver,"openCloseDriver",200,NULL,2,&openCloseDriverHandler);
	xTaskCreate(openCloseDriverAuto,"openCloseDriverAuto",200,NULL,2,&openCloseDriverAutoHandler);
	xTaskCreate(openClosePassenger,"openClosePassenger",200,NULL,2,&openClosePassengerHandler);
	
	//Obstacle task
	xTaskCreate(Obstacle,"Obstacle",200,NULL,2,&ObstacleHandler);
	
	xTaskCreate(openClosePassengerAuto,"openClosePassengerAuto",200,NULL,2,&openClosePassengerAutoHandler);
	xTaskCreate(control,"control",200,NULL,1,&controlHandler);
	vTaskStartScheduler();
	for(;;);
	
return 0;
}