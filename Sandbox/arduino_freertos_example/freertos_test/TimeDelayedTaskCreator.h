#ifndef TIME_DELAYED_TASK_CREATOR_H
#define TIME_DELAYED_TASK_CREATOR_H

#include <Arduino_FreeRTOS.h>

typedef struct TimeDelayedTaskParamsStruct
{
  TaskFunction_t  taskCode;              // Pointer to the function for the task.
  void            *params;               // Pointer to the parameters for the task function.
  unsigned long   timeToRun_ms;          // Time to wait before executing the task.

  TaskHandle_t    taskHandle;            // ??? "Can be optional and set to NULL"?

} TimeDelayedTaskParams;

typedef struct TimeDelayedTaskInfoStruct 
{
  // FreeRTOS related parameters
  char                  *name;                 // Name of the task, for human eyes.
  UBaseType_t           priority;              // Task priority.
  unsigned short        stackDepth;            // Amount of stack to allocate for the stack (number of words).
  
  TimeDelayedTaskParams taskParams;            // Parameters to pass to the task.

} TimeDelayedTaskInfo;


void CreateTimeDelayedTask(
  const TimeDelayedTaskInfo * info    
);

#endif
