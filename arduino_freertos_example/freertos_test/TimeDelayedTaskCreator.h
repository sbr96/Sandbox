#ifndef TIME_DELAYED_TASK_CREATOR_H
#define TIME_DELAYED_TASK_CREATOR_H
#include <Arduino_FreeRTOS.h>

extern void CreateTimeDelayedTask(unsigned long time_to_run, TaskFunction_t taskCode, char *name, unsigned short stackDepth, void *params, UBaseType_t priority);

#endif
