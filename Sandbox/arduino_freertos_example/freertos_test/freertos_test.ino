#include <Arduino_FreeRTOS.h>
extern "C" {
  #include "cdh_main.h"
  #include "TaskWrite.h"
  #include "TimeDelayedTaskCreator.h"
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  cdh_init();
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
