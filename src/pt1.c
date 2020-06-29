/*=============================================================================
 * Copyright (c) 2020, felipesarche <sarche_2004@hotmail.com>
 * All rights reserved.
 * License:  (see LICENSE.txt)
 * Date: 2020/06/28
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "pt1.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#include "sapi.h"
#include "userTasks.h"
#include "tipos.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/
tLedTecla tecla_led_config[2];
/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   boardInit();


   tecla_led_config[0].identificador = '2';
   tecla_led_config[0].tecla 	= TEC2;



   tecla_led_config[1].identificador = '1';
   tecla_led_config[1].tecla 	= TEC1;





   char vec[11];
   cola1=xQueueCreate(6,sizeof (vec));//defino los parámetro de la cola

   // Create a task in freeRTOS with dynamic memory
   xTaskCreate(
      TareaA,                     // Function that implements the task.
      (const char *)"myTask",     // Text name for the task.
      configMINIMAL_STACK_SIZE*2, // Stack size in words, not bytes.
      0,                          // Parameter passed into the task.
      tskIDLE_PRIORITY+1,         // Priority at which the task is created.
      0                           // Pointer to the task created in the system
   );
   xTaskCreate(
      TareaB,                     // Function that implements the task.
      (const char *)"fmstec2",     // Text name for the task.
      configMINIMAL_STACK_SIZE*2, // Stack size in words, not bytes.
      &tecla_led_config[0],                          // Parameter passed into the task.
      tskIDLE_PRIORITY+1,         // Priority at which the task is created.
      0                           // Pointer to the task created in the system
   );
   xTaskCreate(
      TareaB,                     // Function that implements the task.
      (const char *)"fmstec1",     // Text name for the task.
      configMINIMAL_STACK_SIZE*2, // Stack size in words, not bytes.
      &tecla_led_config[1],                          // Parameter passed into the task.
      tskIDLE_PRIORITY+1,         // Priority at which the task is created.
      0                           // Pointer to the task created in the system
   );
   xTaskCreate(
      TareaC,                     // Function that implements the task.
      (const char *)"myTask",     // Text name for the task.
      configMINIMAL_STACK_SIZE*2, // Stack size in words, not bytes.
      0,                          // Parameter passed into the task.
      tskIDLE_PRIORITY+1,         // Priority at which the task is created.
      0                           // Pointer to the task created in the system
   );
   mutex 	=  xSemaphoreCreateMutex();
   vTaskStartScheduler(); // Initialize scheduler

   while( true ); // If reach heare it means that the scheduler could not start

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
