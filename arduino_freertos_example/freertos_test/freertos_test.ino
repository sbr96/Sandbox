#include <Arduino_FreeRTOS.h>
extern "C" {
  #include  "TimeDelayedTaskCreator.h"
}

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  CreateTimeDelayedTask(1000, TaskWrite, (char *)"something", 128, NULL, 1);
  CreateTimeDelayedTask(5000, TaskWrite, (char *)"something", 128, NULL, 1);
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskWrite(void *pvParams) {
  Serial.println("hello world");
}

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

  for (;;)
  {
    // read the input on analog pin 0:
    if(Serial.available() > 0) {
      Serial.println("Found input, starting task");
      input = Serial.read();
      if(input == 'a') {
        //xSemaphoreGive(superImportantLock);
      } else if(input == 'b') {
        //xSemaphoreGive(lessImportantLock);
      } else {
        Serial.println("Unknown input");
      }
    }

    vTaskDelay(1);    
  }
}
