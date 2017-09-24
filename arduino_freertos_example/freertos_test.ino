#include <Arduino_FreeRTOS.h>
#include "semphr.h"

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

SemaphoreHandle_t superImportantLock;
SemaphoreHandle_t lessImportantLock;

// the setup function runs once when you press reset or power the board
void setup() {
  //use semaphores to block the task. When they take it, they are suspended, and then the input task will unblock them when required. 
  vSemaphoreCreateBinary(superImportantLock);
  vSemaphoreCreateBinary(lessImportantLock);
  xSemaphoreTake(superImportantLock, portMAX_DELAY);
  xSemaphoreTake(lessImportantLock, portMAX_DELAY);
  
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  3  // priority
    ,  NULL );

  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1 // priority
    ,  NULL );

 xTaskCreate(
    SuperImportantThing
    ,  (const portCHAR *) "super important"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  4  // priority
    ,  NULL );

 xTaskCreate(
    LessImportantThing
    ,  (const portCHAR *) "less important"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  2  // priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters) 
{
  (void) pvParameters;

  pinMode(13, OUTPUT);

  for (;;)
  {
    digitalWrite(13, HIGH);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
    digitalWrite(13, LOW);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  char input;
  Serial.begin(9600);

  for (;;)
  {
    // read the input on analog pin 0:
    if(Serial.available() > 0) {
      Serial.println("Found input, starting task");
      input = Serial.read();
      if(input == 'a') {
        xSemaphoreGive(superImportantLock);
      } else if(input == 'b') {
        xSemaphoreGive(lessImportantLock);
      } else {
        Serial.println("Unknown input");
      }
    }

    vTaskDelay(1);    
  }
}

void SuperImportantThing(void *pvParameters){
  for(;;) {
    xSemaphoreTake(superImportantLock, portMAX_DELAY);  
    Serial.println("THIS IS A VERY IMPORTANT THING!");
  }
}

void LessImportantThing(void *pvParameters){
  for(;;) {
    xSemaphoreTake(lessImportantLock, portMAX_DELAY);  
    Serial.println("This is less important");
  }
}
