
#include "gpio_drv.h"

gpio_control gpio[16];

//GPIO0
void GPIO0_HIGH(void);
void GPIO0_LOW(void);
void GPIO0_TOGGLE(void);
uint8_t GPIO0_GET(void);
void GPIO0_MODE(uint8_t mode);
//GPIO1
void GPIO1_HIGH(void);
void GPIO1_LOW(void);
void GPIO1_TOGGLE(void);
uint8_t GPIO1_GET(void);
void GPIO1_MODE(uint8_t mode);
//GPIO2
void GPIO2_HIGH(void);
void GPIO2_LOW(void);
void GPIO2_TOGGLE(void);
uint8_t GPIO2_GET(void);
void GPIO2_MODE(uint8_t mode);
//GPIO3
void GPIO3_HIGH(void);
void GPIO3_LOW(void);
void GPIO3_TOGGLE(void);
uint8_t GPIO3_GET(void);
void GPIO3_MODE(uint8_t mode);
//GPIO4
void GPIO4_HIGH(void);
void GPIO4_LOW(void);
void GPIO4_TOGGLE(void);
uint8_t GPIO4_GET(void);
void GPIO4_MODE(uint8_t mode);
//GPIO5
void GPIO5_HIGH(void);
void GPIO5_LOW(void);
void GPIO5_TOGGLE(void);
uint8_t GPIO5_GET(void);
void GPIO5_MODE(uint8_t mode);
//GPIO6
void GPIO6_HIGH(void);
void GPIO6_LOW(void);
void GPIO6_TOGGLE(void);
uint8_t GPIO6_GET(void);
void GPIO6_MODE(uint8_t mode);
//GPIO7
void GPIO7_HIGH(void);
void GPIO7_LOW(void);
void GPIO7_TOGGLE(void);
uint8_t GPIO7_GET(void);
void GPIO7_MODE(uint8_t mode);
//GPIO8
void GPIO8_HIGH(void);
void GPIO8_LOW(void);
void GPIO8_TOGGLE(void);
uint8_t GPIO8_GET(void);
void GPIO8_MODE(uint8_t mode);
//GPIO9
void GPIO9_HIGH(void);
void GPIO9_LOW(void);
void GPIO9_TOGGLE(void);
uint8_t GPIO9_GET(void);
void GPIO9_MODE(uint8_t mode);
//GPIO10
void GPIO10_HIGH(void);
void GPIO10_LOW(void);
void GPIO10_TOGGLE(void);
uint8_t GPIO10_GET(void);
void GPIO10_MODE(uint8_t mode);
//GPIO11
void GPIO11_HIGH(void);
void GPIO11_LOW(void);
void GPIO11_TOGGLE(void);
uint8_t GPIO11_GET(void);
void GPIO11_MODE(uint8_t mode);
//GPIO12
void GPIO12_HIGH(void);
void GPIO12_LOW(void);
void GPIO12_TOGGLE(void);
uint8_t GPIO12_GET(void);
void GPIO12_MODE(uint8_t mode);
//GPIO13
void GPIO13_HIGH(void);
void GPIO13_LOW(void);
void GPIO13_TOGGLE(void);
uint8_t GPIO13_GET(void);
void GPIO13_MODE(uint8_t mode);
//GPIO14
void GPIO14_HIGH(void);
void GPIO14_LOW(void);
void GPIO14_TOGGLE(void);
uint8_t GPIO14_GET(void);
void GPIO14_MODE(uint8_t mode);
//GPIO15
void GPIO15_HIGH(void);
void GPIO15_LOW(void);
void GPIO15_TOGGLE(void);
uint8_t GPIO15_GET(void);
void GPIO15_MODE(uint8_t mode);


void all_gpio_init(void)
{
	//GPIO0 <--
	if(GPIO0_Status)
	{
		gpio_init(GPIO0_Periph,GPIO0_Mode,GPIO_OSPEED_50MHZ,GPIO0_Pin);
	}
	gpio[0].GPIO_HIGH = GPIO0_HIGH;
	gpio[0].GPIO_LOW = GPIO0_LOW;
	gpio[0].GPIO_TOGGLE = GPIO0_TOGGLE;
	gpio[0].GPIO_GET = GPIO0_GET;
	gpio[0].GPIO_MODE = GPIO0_MODE;
	gpio[0].GPIO_Status=GPIO0_Status;

	//GPIO1 <-- 
	if(GPIO1_Status)
	{
		gpio_init(GPIO1_Periph,GPIO1_Mode,GPIO_OSPEED_50MHZ,GPIO1_Pin);
	}
	gpio[1].GPIO_HIGH = GPIO1_HIGH;
	gpio[1].GPIO_LOW = GPIO1_LOW;
	gpio[1].GPIO_TOGGLE = GPIO1_TOGGLE;
	gpio[1].GPIO_GET = GPIO1_GET;
	gpio[1].GPIO_MODE = GPIO1_MODE;
	gpio[1].GPIO_Status=GPIO1_Status;
	//GPIO2 <-- 
	if(GPIO2_Status)
	{
		gpio_init(GPIO2_Periph,GPIO2_Mode,GPIO_OSPEED_50MHZ,GPIO2_Pin);
	}
	gpio[2].GPIO_HIGH = GPIO2_HIGH;
	gpio[2].GPIO_LOW = GPIO2_LOW;
	gpio[2].GPIO_TOGGLE = GPIO2_TOGGLE;
	gpio[2].GPIO_GET = GPIO2_GET;
	gpio[2].GPIO_MODE = GPIO2_MODE;
	gpio[2].GPIO_Status=GPIO2_Status;
	//GPIO3 <-- 
	if(GPIO3_Status)
	{
		gpio_init(GPIO3_Periph,GPIO3_Mode,GPIO_OSPEED_50MHZ,GPIO3_Pin);
	}
	gpio[3].GPIO_HIGH = GPIO3_HIGH;
	gpio[3].GPIO_LOW = GPIO3_LOW;
	gpio[3].GPIO_TOGGLE = GPIO3_TOGGLE;
	gpio[3].GPIO_GET = GPIO3_GET;
	gpio[3].GPIO_MODE = GPIO3_MODE;
	gpio[3].GPIO_Status=GPIO3_Status;
	//GPIO4 <-- 
	if(GPIO4_Status)
	{
		gpio_init(GPIO4_Periph,GPIO4_Mode,GPIO_OSPEED_50MHZ,GPIO4_Pin);
	}
	gpio[4].GPIO_HIGH = GPIO4_HIGH;
	gpio[4].GPIO_LOW = GPIO4_LOW;
	gpio[4].GPIO_TOGGLE = GPIO4_TOGGLE;
	gpio[4].GPIO_GET = GPIO4_GET;
	gpio[4].GPIO_MODE = GPIO4_MODE;
	gpio[4].GPIO_Status=GPIO4_Status;
	//GPIO5 <-- GPIO
	if(GPIO5_Status)
	{
		gpio_init(GPIO5_Periph,GPIO5_Mode,GPIO_OSPEED_50MHZ,GPIO5_Pin);
	}
	gpio[5].GPIO_HIGH = GPIO5_HIGH;
	gpio[5].GPIO_LOW = GPIO5_LOW;
	gpio[5].GPIO_TOGGLE = GPIO5_TOGGLE;
	gpio[5].GPIO_GET = GPIO5_GET;
	gpio[5].GPIO_MODE = GPIO5_MODE;
	gpio[5].GPIO_Status=GPIO5_Status;
	//GPIO6 <-- GPIO
	if(GPIO6_Status)
	{
		gpio_init(GPIO6_Periph,GPIO6_Mode,GPIO_OSPEED_50MHZ,GPIO6_Pin);
	}
	gpio[6].GPIO_HIGH = GPIO6_HIGH;
	gpio[6].GPIO_LOW = GPIO6_LOW;
	gpio[6].GPIO_TOGGLE = GPIO6_TOGGLE;
	gpio[6].GPIO_GET = GPIO6_GET;
	gpio[6].GPIO_MODE = GPIO6_MODE;
	gpio[6].GPIO_Status=GPIO6_Status;
	//GPIO7 <-- GPIO
	if(GPIO7_Status)
	{
  	gpio_init(GPIO7_Periph,GPIO7_Mode,GPIO_OSPEED_50MHZ,GPIO7_Pin);
	}
	gpio[7].GPIO_HIGH = GPIO7_HIGH;
	gpio[7].GPIO_LOW = GPIO7_LOW;
	gpio[7].GPIO_TOGGLE = GPIO7_TOGGLE;
	gpio[7].GPIO_GET = GPIO7_GET;
	gpio[7].GPIO_MODE = GPIO7_MODE;
	gpio[7].GPIO_Status=GPIO7_Status;
	//GPIO8 <-- GPIOF1
	if(GPIO8_Status)
	{
		gpio_init(GPIO8_Periph,GPIO8_Mode,GPIO_OSPEED_50MHZ,GPIO8_Pin);
	}
	gpio[8].GPIO_HIGH = GPIO8_HIGH;
	gpio[8].GPIO_LOW = GPIO8_LOW;
	gpio[8].GPIO_TOGGLE = GPIO8_TOGGLE;
	gpio[8].GPIO_GET = GPIO8_GET;
	gpio[8].GPIO_MODE = GPIO8_MODE;
	gpio[8].GPIO_Status=GPIO8_Status;
	//GPIO9<-- GPIO
	if(GPIO9_Status)
	{
		gpio_init(GPIO9_Periph,GPIO9_Mode,GPIO_OSPEED_50MHZ,GPIO9_Pin);
	}
	gpio[9].GPIO_HIGH = GPIO9_HIGH;
	gpio[9].GPIO_LOW = GPIO9_LOW;
	gpio[9].GPIO_TOGGLE = GPIO9_TOGGLE;
	gpio[9].GPIO_GET = GPIO9_GET;
	gpio[9].GPIO_MODE = GPIO9_MODE;
	gpio[9].GPIO_Status=GPIO9_Status;
	//GPIO10 <-- GPIO
	if(GPIO10_Status)
	{
		gpio_init(GPIO10_Periph,GPIO10_Mode,GPIO_OSPEED_50MHZ,GPIO10_Pin);
	}
	gpio[10].GPIO_HIGH = GPIO10_HIGH;
	gpio[10].GPIO_LOW = GPIO10_LOW;
	gpio[10].GPIO_TOGGLE = GPIO10_TOGGLE;
	gpio[10].GPIO_GET = GPIO10_GET;
	gpio[10].GPIO_MODE = GPIO10_MODE;
	gpio[10].GPIO_Status=GPIO10_Status;
	//GPIO11 <-- GPIO
	if(GPIO11_Status)
	{
		gpio_init(GPIO11_Periph,GPIO11_Mode,GPIO_OSPEED_50MHZ,GPIO11_Pin);
	}
	gpio[11].GPIO_HIGH = GPIO11_HIGH;
	gpio[11].GPIO_LOW = GPIO11_LOW;
	gpio[11].GPIO_TOGGLE = GPIO11_TOGGLE;
	gpio[11].GPIO_GET = GPIO11_GET;
	gpio[11].GPIO_MODE = GPIO11_MODE;
	gpio[11].GPIO_Status=GPIO11_Status;
	//GPIO12 <-- GPIO
	if(GPIO12_Status)
	{
		gpio_init(GPIO12_Periph,GPIO12_Mode,GPIO_OSPEED_50MHZ,GPIO12_Pin);
	}
	gpio[12].GPIO_HIGH = GPIO12_HIGH;
	gpio[12].GPIO_LOW = GPIO12_LOW;
	gpio[12].GPIO_TOGGLE = GPIO12_TOGGLE;
	gpio[12].GPIO_GET = GPIO12_GET;
	gpio[12].GPIO_MODE = GPIO12_MODE;
	gpio[12].GPIO_Status=GPIO12_Status;
	//GPIO13 <-- GPIO
	if(GPIO13_Status)
	{
		gpio_init(GPIO13_Periph,GPIO13_Mode,GPIO_OSPEED_50MHZ,GPIO13_Pin);
	}
	gpio[13].GPIO_HIGH = GPIO13_HIGH;
	gpio[13].GPIO_LOW = GPIO13_LOW;
	gpio[13].GPIO_TOGGLE = GPIO13_TOGGLE;
	gpio[13].GPIO_GET = GPIO13_GET;
	gpio[13].GPIO_MODE = GPIO13_MODE;
	gpio[13].GPIO_Status=GPIO13_Status;
	//GPIO14 <-- GPIO
	if(GPIO14_Status)
	{
		gpio_init(GPIO14_Periph,GPIO14_Mode,GPIO_OSPEED_50MHZ,GPIO14_Pin);
	}
	gpio[14].GPIO_HIGH = GPIO14_HIGH;
	gpio[14].GPIO_LOW = GPIO14_LOW;
	gpio[14].GPIO_TOGGLE = GPIO14_TOGGLE;
	gpio[14].GPIO_GET = GPIO14_GET;
	gpio[14].GPIO_MODE = GPIO14_MODE;
	gpio[14].GPIO_Status=GPIO14_Status;
	//GPIO15 <-- GPIO
	if(GPIO15_Status)
	{
		gpio_init(GPIO15_Periph,GPIO15_Mode,GPIO_OSPEED_50MHZ,GPIO15_Pin);
	}
	gpio[15].GPIO_HIGH = GPIO15_HIGH;
	gpio[15].GPIO_LOW = GPIO15_LOW;
	gpio[15].GPIO_TOGGLE = GPIO15_TOGGLE;
	gpio[15].GPIO_GET = GPIO15_GET;
	gpio[15].GPIO_MODE = GPIO15_MODE;
	gpio[15].GPIO_Status=GPIO15_Status;
}

void gpio_bit_toggle(uint32_t gpio_periph,uint32_t pin)
{
	if((uint32_t)RESET !=(GPIO_OCTL(gpio_periph)&(pin))){
			GPIO_BC(gpio_periph) = (uint32_t)pin;//reset
	}else{
			GPIO_BOP(gpio_periph) = (uint32_t)pin;//set
	}
	
	
	
	
}


uint32_t Gpio_IO_Input[16] = {0x00000005,0x00000003};


//GPIO0 ----------------------------------------------------------------------------
void GPIO0_HIGH(void)
{
	gpio[0].GPIO_Status?gpio_bit_set(GPIO0_Periph,GPIO0_Pin):0;
}
void GPIO0_LOW(void)
{
	gpio[0].GPIO_Status?gpio_bit_reset(GPIO0_Periph,GPIO0_Pin):0;
}
void GPIO0_TOGGLE(void)
{
	gpio[0].GPIO_Status?gpio_bit_toggle(GPIO0_Periph,GPIO0_Pin):0;
}
uint8_t GPIO0_GET(void)
{
	return gpio[0].GPIO_Status?gpio_input_bit_get(GPIO0_Periph,GPIO0_Pin):255;
}
void GPIO0_MODE(uint8_t mode)
{
	gpio[0].GPIO_Status?mode?gpio_init(GPIO0_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO0_Pin):gpio_init(GPIO0_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO0_Pin):0;
	
}
//GPIO1 ----------------------------------------------------------------------------
void GPIO1_HIGH(void)
{
	gpio[1].GPIO_Status?gpio_bit_set(GPIO1_Periph,GPIO1_Pin):0;
}
void GPIO1_LOW(void)
{
	gpio[1].GPIO_Status?gpio_bit_reset(GPIO1_Periph,GPIO1_Pin):0;
}
void GPIO1_TOGGLE(void)
{
	gpio[1].GPIO_Status?gpio_bit_toggle(GPIO1_Periph,GPIO1_Pin):0;
}
uint8_t GPIO1_GET(void)
{
	return gpio[1].GPIO_Status?gpio_input_bit_get(GPIO1_Periph,GPIO1_Pin):255;
}
void GPIO1_MODE(uint8_t mode)
{
	gpio[1].GPIO_Status?mode?gpio_init(GPIO1_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO1_Pin):gpio_init(GPIO1_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO1_Pin):0;
}
//GPIO2 ----------------------------------------------------------------------------
void GPIO2_HIGH(void)
{
	gpio[2].GPIO_Status?gpio_bit_set(GPIO2_Periph,GPIO2_Pin):0;
}
void GPIO2_LOW(void)
{
	gpio[2].GPIO_Status?gpio_bit_reset(GPIO2_Periph,GPIO2_Pin):0;
}
void GPIO2_TOGGLE(void)
{
	gpio[2].GPIO_Status?gpio_bit_toggle(GPIO2_Periph,GPIO2_Pin):0;
}
uint8_t GPIO2_GET(void)
{
	return gpio[2].GPIO_Status?gpio_input_bit_get(GPIO2_Periph,GPIO2_Pin):255;
}
void GPIO2_MODE(uint8_t mode)
{
	gpio[2].GPIO_Status?mode?gpio_init(GPIO2_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO2_Pin):gpio_init(GPIO2_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO2_Pin):0;
}
//GPIO3 ----------------------------------------------------------------------------
void GPIO3_HIGH(void)
{
	gpio[3].GPIO_Status?gpio_bit_set(GPIO3_Periph,GPIO3_Pin):0;
}
void GPIO3_LOW(void)
{
	gpio[3].GPIO_Status?gpio_bit_reset(GPIO3_Periph,GPIO3_Pin):0;
}
void GPIO3_TOGGLE(void)
{
	gpio[3].GPIO_Status?gpio_bit_toggle(GPIO3_Periph,GPIO3_Pin):0;
}
uint8_t GPIO3_GET(void)
{
	return gpio[3].GPIO_Status?gpio_input_bit_get(GPIO3_Periph,GPIO3_Pin):255;
}
void GPIO3_MODE(uint8_t mode)
{
	gpio[3].GPIO_Status?mode?gpio_init(GPIO3_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO3_Pin):gpio_init(GPIO3_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO3_Pin):0;
}
//GPIO4 ----------------------------------------------------------------------------
void GPIO4_HIGH(void)
{
	gpio[4].GPIO_Status?gpio_bit_set(GPIO4_Periph,GPIO4_Pin):0;
}
void GPIO4_LOW(void)
{
	gpio[4].GPIO_Status?gpio_bit_reset(GPIO4_Periph,GPIO4_Pin):0;
}
void GPIO4_TOGGLE(void)
{
	gpio[4].GPIO_Status?gpio_bit_toggle(GPIO4_Periph,GPIO4_Pin):0;
}
uint8_t GPIO4_GET(void)
{
	return gpio[4].GPIO_Status?gpio_input_bit_get(GPIO4_Periph,GPIO4_Pin):255;
}
void GPIO4_MODE(uint8_t mode)
{
	gpio[4].GPIO_Status?mode?gpio_init(GPIO4_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO4_Pin):gpio_init(GPIO4_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO4_Pin):0;
}
//GPIO5 ----------------------------------------------------------------------------
void GPIO5_HIGH(void)
{
	gpio[5].GPIO_Status?gpio_bit_set(GPIO5_Periph,GPIO5_Pin):0;
}
void GPIO5_LOW(void)
{
	gpio[5].GPIO_Status?gpio_bit_reset(GPIO5_Periph,GPIO5_Pin):0;
}
void GPIO5_TOGGLE(void)
{
	gpio[5].GPIO_Status?gpio_bit_toggle(GPIO5_Periph,GPIO5_Pin):0;
}
uint8_t GPIO5_GET(void)
{
	return gpio[5].GPIO_Status?gpio_input_bit_get(GPIO5_Periph,GPIO5_Pin):255;
}
void GPIO5_MODE(uint8_t mode)
{
	gpio[5].GPIO_Status?mode?gpio_init(GPIO5_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO5_Pin):gpio_init(GPIO5_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO5_Pin):0;
}
//GPIO6 ----------------------------------------------------------------------------
void GPIO6_HIGH(void)
{
	gpio[6].GPIO_Status?gpio_bit_set(GPIO6_Periph,GPIO6_Pin):0;
}
void GPIO6_LOW(void)
{
	gpio[6].GPIO_Status?gpio_bit_reset(GPIO6_Periph,GPIO6_Pin):0;
}
void GPIO6_TOGGLE(void)
{
	gpio[6].GPIO_Status?gpio_bit_toggle(GPIO6_Periph,GPIO6_Pin):0;
}
uint8_t GPIO6_GET(void)
{
	return gpio[6].GPIO_Status?gpio_input_bit_get(GPIO6_Periph,GPIO6_Pin):255;
}
void GPIO6_MODE(uint8_t mode)
{
	gpio[6].GPIO_Status?mode?gpio_init(GPIO6_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO6_Pin):gpio_init(GPIO6_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO6_Pin):0;
	
	
	
}
//GPIO7 ----------------------------------------------------------------------------
void GPIO7_HIGH(void)
{
	gpio[7].GPIO_Status?gpio_bit_set(GPIO7_Periph,GPIO7_Pin):0;
}
void GPIO7_LOW(void)
{
	gpio[7].GPIO_Status?gpio_bit_reset(GPIO7_Periph,GPIO7_Pin):0;
}
void GPIO7_TOGGLE(void)
{
	gpio[7].GPIO_Status?gpio_bit_toggle(GPIO7_Periph,GPIO7_Pin):0;
}
uint8_t GPIO7_GET(void)
{
	return gpio[7].GPIO_Status?gpio_input_bit_get(GPIO7_Periph,GPIO7_Pin):0;
}
void GPIO7_MODE(uint8_t mode)
{
	gpio[7].GPIO_Status?mode?gpio_init(GPIO7_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO7_Pin):gpio_init(GPIO7_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO7_Pin):0;
}
//GPIO8 ----------------------------------------------------------------------------
void GPIO8_HIGH(void)
{
	gpio[8].GPIO_Status?gpio_bit_set(GPIO8_Periph,GPIO8_Pin):0;
}
void GPIO8_LOW(void)
{
	gpio[8].GPIO_Status?gpio_bit_reset(GPIO8_Periph,GPIO8_Pin):0;
}
void GPIO8_TOGGLE(void)
{
	gpio[8].GPIO_Status?gpio_bit_toggle(GPIO8_Periph,GPIO8_Pin):0;
}
uint8_t GPIO8_GET(void)
{
	return gpio[8].GPIO_Status?gpio_input_bit_get(GPIO8_Periph,GPIO8_Pin):255;
}
void GPIO8_MODE(uint8_t mode)
{
	gpio[8].GPIO_Status?mode?gpio_init(GPIO8_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO8_Pin):gpio_init(GPIO8_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO8_Pin):0;
}
//GPIO9----------------------------------------------------------------------------
void GPIO9_HIGH(void)
{
	gpio[9].GPIO_Status?gpio_bit_set(GPIO9_Periph,GPIO9_Pin):0;
}
void GPIO9_LOW(void)
{
	gpio[9].GPIO_Status?gpio_bit_reset(GPIO9_Periph,GPIO9_Pin):0;
}
void GPIO9_TOGGLE(void)
{
	gpio[9].GPIO_Status?gpio_bit_toggle(GPIO9_Periph,GPIO9_Pin):0;
}
uint8_t GPIO9_GET(void)
{
	return gpio[9].GPIO_Status?gpio_input_bit_get(GPIO9_Periph,GPIO9_Pin):255;
}
void GPIO9_MODE(uint8_t mode)
{
	gpio[9].GPIO_Status?mode?gpio_init(GPIO9_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO9_Pin):gpio_init(GPIO9_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO9_Pin):0;
}
//GPIO10 ----------------------------------------------------------------------------
void GPIO10_HIGH(void)
{
	gpio[10].GPIO_Status?gpio_bit_set(GPIO10_Periph,GPIO10_Pin):0;
}
void GPIO10_LOW(void)
{
	gpio[10].GPIO_Status?gpio_bit_reset(GPIO10_Periph,GPIO10_Pin):0;
}
void GPIO10_TOGGLE(void)
{
	gpio[10].GPIO_Status?gpio_bit_toggle(GPIO10_Periph,GPIO10_Pin):0;
}
uint8_t GPIO10_GET(void)
{
	return gpio[10].GPIO_Status?gpio_input_bit_get(GPIO10_Periph,GPIO10_Pin):255;
}
void GPIO10_MODE(uint8_t mode)
{
	gpio[10].GPIO_Status?mode?gpio_init(GPIO10_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO10_Pin):gpio_init(GPIO10_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO10_Pin):0;
}
//GPIO11 ----------------------------------------------------------------------------
void GPIO11_HIGH(void)
{
	gpio[11].GPIO_Status?gpio_bit_set(GPIO11_Periph,GPIO11_Pin):0;
}
void GPIO11_LOW(void)
{
	gpio[11].GPIO_Status?gpio_bit_reset(GPIO11_Periph,GPIO11_Pin):0;
}
void GPIO11_TOGGLE(void)
{
	gpio[11].GPIO_Status?gpio_bit_toggle(GPIO11_Periph,GPIO11_Pin):0;
}
uint8_t GPIO11_GET(void)
{
	return gpio[11].GPIO_Status?gpio_input_bit_get(GPIO11_Periph,GPIO11_Pin):255;
}
void GPIO11_MODE(uint8_t mode)
{
	gpio[11].GPIO_Status?mode?gpio_init(GPIO11_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO11_Pin):gpio_init(GPIO11_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO11_Pin):0;
}
//GPIO12 ----------------------------------------------------------------------------
void GPIO12_HIGH(void)
{
	gpio[12].GPIO_Status?gpio_bit_set(GPIO12_Periph,GPIO12_Pin):0;
}
void GPIO12_LOW(void)
{
	gpio[12].GPIO_Status?gpio_bit_reset(GPIO12_Periph,GPIO12_Pin):0;
}
void GPIO12_TOGGLE(void)
{
	gpio[12].GPIO_Status?gpio_bit_toggle(GPIO12_Periph,GPIO12_Pin):0;
}
uint8_t GPIO12_GET(void)
{
	return gpio[12].GPIO_Status?gpio_input_bit_get(GPIO12_Periph,GPIO12_Pin):255;
}
void GPIO12_MODE(uint8_t mode)
{
	gpio[12].GPIO_Status?mode?gpio_init(GPIO12_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO12_Pin):gpio_init(GPIO12_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO12_Pin):0;
}
//GPIO13 ----------------------------------------------------------------------------
void GPIO13_HIGH(void)
{
	gpio[13].GPIO_Status?gpio_bit_set(GPIO13_Periph,GPIO13_Pin):0;
}
void GPIO13_LOW(void)
{
	gpio[13].GPIO_Status?gpio_bit_reset(GPIO13_Periph,GPIO13_Pin):0;
}
void GPIO13_TOGGLE(void)
{
	gpio[13].GPIO_Status?gpio_bit_toggle(GPIO13_Periph,GPIO13_Pin):0;
}
uint8_t GPIO13_GET(void)
{
	return gpio[13].GPIO_Status?gpio_input_bit_get(GPIO13_Periph,GPIO13_Pin):255;
}
void GPIO13_MODE(uint8_t mode)
{
	gpio[13].GPIO_Status?mode?gpio_init(GPIO13_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO13_Pin):gpio_init(GPIO13_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO13_Pin):0;
}
//GPIO14 ----------------------------------------------------------------------------
void GPIO14_HIGH(void)
{
	gpio[14].GPIO_Status?gpio_bit_set(GPIO14_Periph,GPIO14_Pin):0;
}
void GPIO14_LOW(void)
{
	gpio[14].GPIO_Status?gpio_bit_reset(GPIO14_Periph,GPIO14_Pin):0;
}
void GPIO14_TOGGLE(void)
{
	gpio[14].GPIO_Status?gpio_bit_toggle(GPIO14_Periph,GPIO14_Pin):0;
}
uint8_t GPIO14_GET(void)
{
	return gpio[14].GPIO_Status?gpio_input_bit_get(GPIO14_Periph,GPIO14_Pin):255;
}
void GPIO14_MODE(uint8_t mode)
{
	gpio[14].GPIO_Status?mode?gpio_init(GPIO14_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO14_Pin):gpio_init(GPIO14_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO14_Pin):0;
}
//GPIO15 ----------------------------------------------------------------------------
void GPIO15_HIGH(void)
{
	gpio[15].GPIO_Status?gpio_bit_set(GPIO15_Periph,GPIO15_Pin):0;
}
void GPIO15_LOW(void)
{
	gpio[15].GPIO_Status?gpio_bit_reset(GPIO15_Periph,GPIO15_Pin):0;
}
void GPIO15_TOGGLE(void)
{
	gpio[15].GPIO_Status?gpio_bit_toggle(GPIO15_Periph,GPIO15_Pin):0;
}
uint8_t GPIO15_GET(void)
{
	return gpio[15].GPIO_Status?gpio_input_bit_get(GPIO15_Periph,GPIO15_Pin):255;
}
void GPIO15_MODE(uint8_t mode)
{
	gpio[15].GPIO_Status?mode?gpio_init(GPIO15_Periph,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,GPIO15_Pin):gpio_init(GPIO15_Periph,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,GPIO15_Pin):0;
}



gpio_control get_gpio_struct(uint8_t num)
{
	return gpio[num];
}






