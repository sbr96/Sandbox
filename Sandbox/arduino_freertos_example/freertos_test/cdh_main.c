#include "cdh_main.h"

void cdh_init()
{
  for (int ix = 0; ix < TOTAL_NUMBER_OF_TASKS; ix++)
  {
    CreateTimeDelayedTask(&CDH_TaskTable[ix]);
  }
}

