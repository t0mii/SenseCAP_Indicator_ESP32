#ifndef INDICATOR_SENSOR_H
#define INDICATOR_SENSOR_H

#include "config.h"
#include "view_data.h"
#include "driver/uart.h"


#ifdef __cplusplus
extern "C" {
#endif

int indicator_sensor_init(void);
int indicator_sensor_get_data(struct view_data_sensor *out_data);

#ifdef __cplusplus
}
#endif

#endif
