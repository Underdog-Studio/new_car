#ifndef __gpio_drv_H
#define __gpio_drv_H
#include "gd32f30x.h"
#include "gd32f30x_gpio.h"

#define GPIO0_Status ENABLE
#define GPIO0_Periph GPIOC
#define GPIO0_Pin    GPIO_PIN_5
#define GPIO0_Mode   GPIO_MODE_IN_FLOATING  //GPIO_MODE_OUT_PP  GPIO_MODE_IN_FLOATING

#define GPIO1_Status ENABLE
#define GPIO1_Periph GPIOC
#define GPIO1_Pin    GPIO_PIN_11
#define GPIO1_Mode   GPIO_MODE_IN_FLOATING

#define GPIO2_Status DISABLE
#define GPIO2_Periph GPIOB
#define GPIO2_Pin    GPIO_PIN_12
#define GPIO2_Mode   GPIO_MODE_OUT_PP

#define GPIO3_Status DISABLE
#define GPIO3_Periph GPIOB
#define GPIO3_Pin    GPIO_PIN_4
#define GPIO3_Mode   GPIO_MODE_OUT_PP

#define GPIO4_Status DISABLE
#define GPIO4_Periph GPIOB
#define GPIO4_Pin    GPIO_PIN_14
#define GPIO4_Mode   GPIO_MODE_OUT_PP

#define GPIO5_Status DISABLE
#define GPIO5_Periph GPIOC
#define GPIO5_Pin    GPIO_PIN_11
#define GPIO5_Mode   GPIO_MODE_IN_FLOATING

#define GPIO6_Status DISABLE
#define GPIO6_Periph GPIOC
#define GPIO6_Pin    GPIO_PIN_5
#define GPIO6_Mode   GPIO_MODE_IN_FLOATING

#define GPIO7_Status DISABLE
#define GPIO7_Periph GPIOA
#define GPIO7_Pin    GPIO_PIN_11
#define GPIO7_Mode   GPIO_MODE_OUT_PP

#define GPIO8_Status DISABLE
#define GPIO8_Periph GPIOF
#define GPIO8_Pin    GPIO_PIN_0
#define GPIO8_Mode   GPIO_MODE_OUT_PP

#define GPIO9_Status DISABLE
#define GPIO9_Periph GPIOA
#define GPIO9_Pin    GPIO_PIN_15
#define GPIO9_Mode   GPIO_MODE_OUT_PP

#define GPIO10_Status DISABLE
#define GPIO10_Periph GPIOB
#define GPIO10_Pin    GPIO_PIN_3
#define GPIO10_Mode   GPIO_MODE_OUT_PP

#define GPIO11_Status DISABLE
#define GPIO11_Periph GPIOB
#define GPIO11_Pin    GPIO_PIN_6
#define GPIO11_Mode   GPIO_MODE_OUT_PP

#define GPIO12_Status DISABLE
#define GPIO12_Periph GPIOA
#define GPIO12_Pin    GPIO_PIN_10
#define GPIO12_Mode   GPIO_MODE_OUT_PP

#define GPIO13_Status DISABLE
#define GPIO13_Periph GPIOF
#define GPIO13_Pin    GPIO_PIN_1
#define GPIO13_Mode   GPIO_MODE_OUT_PP

#define GPIO14_Status DISABLE
#define GPIO14_Periph GPIOF
#define GPIO14_Pin    GPIO_PIN_1
#define GPIO14_Mode   GPIO_MODE_OUT_PP

#define GPIO15_Status DISABLE
#define GPIO15_Periph GPIOF
#define GPIO15_Pin    GPIO_PIN_0
#define GPIO15_Mode   GPIO_MODE_OUT_PP

typedef struct
{
	uint8_t GPIO_Status;
	void(*GPIO_HIGH)(void);
	void(*GPIO_LOW)(void);
	void(*GPIO_TOGGLE)(void);
	uint8_t(*GPIO_GET)(void);
	void(*GPIO_MODE)(uint8_t);
}gpio_control;

void all_gpio_init(void);
gpio_control get_gpio_struct(uint8_t num);

#endif

