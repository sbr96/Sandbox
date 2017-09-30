#ifndef CDH_MAIN_H
#define CDH_MAIN_H

#include "TaskWrite.h" // For naming convention, perhaps "Task[Function]" should be the name given to all the task functions and header files.
#include "TimeDelayedTaskCreator.h"

enum CDH_TASK_TABLE_INDICES
{
    HELLO_WORLD_1_IX,
    HELLO_WORLD_2_IX,
    TOTAL_NUMBER_OF_TASKS,
};


// All the tasks should be documented in some reference document, and then this comment can refer to that document.
const TimeDelayedTaskInfo CDH_TaskTable[TOTAL_NUMBER_OF_TASKS] =
//  name,              priority,        stack depth,     task function,    task parameters,  time to wait (ms), task handle
{
  { "Hello World 1",  (UBaseType_t) 1,          128,   {     TaskWrite,               NULL,               1000, (TaskHandle_t) NULL }  },
  { "Hello World 2",  (UBaseType_t) 1,          128,   {     TaskWrite,               NULL,               5000, (TaskHandle_t) NULL }  },
};


void cdh_init(void);


#endif
