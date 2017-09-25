#include "TimeDelayedTaskCreator.h"

typedef struct TimeDelayedTaskInfoStruct {
	unsigned long timeToRun;
	TaskHandle_t taskHandle;
	TaskFunction_t taskCode;
	void *params;
} TimeDelayedTaskInfo;

//return timeToDelay in ms (can be negative if the time has already passed)
int calculateDelay(int timeToRun) {
	return timeToRun;
}

void taskRunner(void *pvParamaters) {
	TimeDelayedTaskInfo *info = (TimeDelayedTaskInfo *)pvParamaters;
	int timeToDelay = calculateDelay(info->timeToRun);
	TaskHandle_t taskHandle;

	if(timeToDelay > 0) {
		vTaskDelay(timeToDelay / portTICK_PERIOD_MS );
	}

	info->taskCode(info->params);

	taskHandle = info->taskHandle;
	vPortFree(info);
	vTaskDelete(taskHandle);

	for(;;) {}
}

void CreateTimeDelayedTask(unsigned long timeToRun, TaskFunction_t taskCode, char *name, unsigned short stackDepth, void *params, UBaseType_t priority) {
	TimeDelayedTaskInfo *info = pvPortMalloc(sizeof(TimeDelayedTaskInfo));
	info->timeToRun = timeToRun;
	info->taskCode = taskCode;
	info->params = params;

	xTaskCreate(taskRunner, name, stackDepth, info, priority, info->taskHandle);
}
