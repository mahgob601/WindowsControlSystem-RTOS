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
//xTaskHandle LockHandler;

xSemaphoreHandle xBinarySemaphore1;
xSemaphoreHandle xBinarySemaphore2;
xSemaphoreHandle xBinarySemaphoreDriverAuto;
xSemaphoreHandle xBinarySemaphorePassengerAuto;
//xSemaphoreHandle xBinarySemaphoreLock;


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
	//xBinarySemaphoreLock = xSemaphoreCreateBinary();
	
	xTaskCreate(openCloseDriver,"openCloseDriver",180,NULL,2,&openCloseDriverHandler);
	xTaskCreate(openCloseDriverAuto,"openCloseDriverAuto",180,NULL,2,&openCloseDriverAutoHandler);
	xTaskCreate(openClosePassenger,"openClosePassenger",180,NULL,2,&openClosePassengerHandler);
	
	//Obstacle task
	xTaskCreate(Obstacle,"Obstacle",180,NULL,2,&ObstacleHandler);
	
	//xTaskCreate(Lock,"Lock",180,NULL,2,&LockHandler);
	
	xTaskCreate(openClosePassengerAuto,"openClosePassengerAuto",180,NULL,2,&openClosePassengerAutoHandler);
	xTaskCreate(control,"control",180,NULL,1,&controlHandler);
	vTaskStartScheduler();
	for(;;);
	
return 0;
}