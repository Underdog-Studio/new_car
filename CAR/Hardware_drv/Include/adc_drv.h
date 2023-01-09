#ifndef __adc_drv_H
#define __adc_drv_H

#include "gd32f30x_adc.h"
#include "System_time.h"




void adc_init(void);
uint16_t get_adc_value(uint8_t num);

#endif
