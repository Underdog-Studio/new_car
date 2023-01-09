#include "adc_drv.h"

__IO uint16_t ADC_value_arry[5] = {0};

void adc_init(void)
{
	//初始化GPIO
	gpio_init(GPIOC,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_0);//Sevro1
	gpio_init(GPIOC,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_1);//Sevro2
	gpio_init(GPIOC,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_2);//Sevro3
	gpio_init(GPIOC,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_3);//Sevro4
	gpio_init(GPIOC,GPIO_MODE_AIN,GPIO_OSPEED_50MHZ,GPIO_PIN_4);//VIN_Voltage
	//配置DMA
	dma_parameter_struct dma_data_parameter;

	rcu_periph_clock_enable(RCU_DMA0);
	
	dma_deinit(DMA0,DMA_CH0);
	
	dma_data_parameter.periph_addr=(uint32_t)(&ADC_RDATA(ADC0));
	dma_data_parameter.periph_inc=DMA_PERIPH_INCREASE_DISABLE;
	dma_data_parameter.memory_addr=(uint32_t)(ADC_value_arry);
	dma_data_parameter.memory_inc=DMA_MEMORY_INCREASE_ENABLE;

	dma_data_parameter.memory_width=DMA_MEMORY_WIDTH_16BIT;
	dma_data_parameter.periph_width=DMA_PERIPHERAL_WIDTH_16BIT;
	
	dma_data_parameter.direction=DMA_PERIPHERAL_TO_MEMORY;
	dma_data_parameter.number=5;
	dma_data_parameter.priority=DMA_PRIORITY_HIGH;
	
	dma_init(DMA0,DMA_CH0,&dma_data_parameter);
	
	dma_circulation_enable(DMA0,DMA_CH0);
	dma_memory_to_memory_disable(DMA0,DMA_CH0);
  dma_channel_enable(DMA0,DMA_CH0);

  rcu_periph_clock_enable(RCU_ADC0);
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV8); //9M
	
	
	adc_deinit(ADC0);
	
	
	adc_mode_config(ADC_MODE_FREE);

	
	adc_special_function_config(ADC0,ADC_CONTINUOUS_MODE, ENABLE); 
	adc_special_function_config(ADC0,ADC_SCAN_MODE, ENABLE);	
	
	
	adc_data_alignment_config(ADC0,ADC_DATAALIGN_RIGHT);  
	adc_channel_length_config(ADC0,ADC_REGULAR_CHANNEL,5);
	adc_regular_channel_config(ADC0,0, ADC_CHANNEL_12 , ADC_SAMPLETIME_55POINT5);    
	adc_regular_channel_config(ADC0,1, ADC_CHANNEL_11 , ADC_SAMPLETIME_55POINT5);    
	adc_regular_channel_config(ADC0,2, ADC_CHANNEL_10 , ADC_SAMPLETIME_55POINT5);    
	adc_regular_channel_config(ADC0,3, ADC_CHANNEL_13 , ADC_SAMPLETIME_55POINT5);   
	adc_regular_channel_config(ADC0,4, ADC_CHANNEL_14 , ADC_SAMPLETIME_55POINT5);   

	
	
	adc_external_trigger_config(ADC0,ADC_REGULAR_CHANNEL, ENABLE); 
	adc_external_trigger_source_config(ADC0,ADC_REGULAR_CHANNEL,ADC0_1_2_EXTTRIG_REGULAR_NONE);  
	
	
	adc_enable(ADC0);
	//delay_ms(5);
	
	adc_calibration_enable(ADC0);
	adc_dma_mode_enable(ADC0); 
	
	adc_software_trigger_enable(ADC0,ADC_REGULAR_CHANNEL);
}

uint16_t get_adc_value(uint8_t num)
{
	return ADC_value_arry[num];
}



