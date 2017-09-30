#include "TimeDelayedTaskCreator.h"


//return timeToDelay in ms (can be negative if the time has already passed)
int calculateDelay(int timeToRun) {
	return timeToRun;
}

void taskRunner(void *pvParameters) {
	TimeDelayedTaskParams *parameters = (TimeDelayedTaskParams *) pvParameters;
	int timeToDelay = calculateDelay(parameters->timeToRun_ms);
	TaskHandle_t taskHandle;

	if(timeToDelay > 0) 
	{
		vTaskDelay(timeToDelay / portTICK_PERIOD_MS );
	}

	parameters->taskCode(parameters->params);

	taskHandle = parameters->taskHandle;
	vPortFree(parameters);
	vTaskDelete(taskHandle);

	for(;;) {}
}

void CreateTimeDelayedTask(const TimeDelayedTaskInfo * info) 
{
	xTaskCreate(taskRunner, info->name, info->stackDepth, &(info->taskParams), info->priority, info->taskParams.taskHandle);
}

