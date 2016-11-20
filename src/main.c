/**
  * @file    PALdemo/main.c
  * @author  E.J.W. Vrieze
  * @version V1.5.1
  * @date    27-June-2016
  * @brief   Main program body
  * 		Program to demonstrate composite video generation using the
  * 		STM32L100RC on a STM32 Discovery board (MB1108).
  * 		The video signal is generated using timers and DMA. The CPU
  * 		is used to initialise the peripherals and fill / modify the
  * 		frame buffer.
 Includes -------------------------------------------------------------*/
#include <stdlib.h>
#include "stm32l1xx.h"
#include "stm32l100c_discovery.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Paused;
__IO uint32_t TimingDelay;
/* Private function prototypes -----------------------------------------------*/
void videoInit();
void show(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void DelayMs(uint32_t nTime)
{
  TimingDelay = nTime;
  while((TimingDelay != 0));
  while(Paused);
}

/**
  * @brief   RCC and Peripheral Clock configuration
  * @param   None
  * @retval  None
  */
void RCC_Configuration(void)
{
	RCC_ClocksTypeDef RCC_Clocks;
	/* The generation of a video signal requires a stable (crystal based) clock.
	 * The HSI is not suitable as it has too much jitter. So the HSE is used,
	 * which is driven by an 8 MHz external clock from the ST/Link interface,
	 * which is doubled to a Sysclk and  APB1 = 16 MHz by the PLL.
	 *
	 * GPIOA, GPIOB, GPIOC, SPI2, TIM2, TIM3, DMA1  clocks enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3|RCC_APB1Periph_SPI2, ENABLE);

	RCC_GetClocksFreq(&RCC_Clocks);			  	  /* SysTick end of count event each 1ms */
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}

/**
  * @brief   Main program
  * @param   None
  * @retval  None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */
	/* The Atollic debugger does not reset the target upon restart
	 * Therefore we do reset the I/O explicitly.
	 * Only usefull for debugging; can use the reset button instead.
	 */
	SPI_DeInit(SPI2);				// Reset video output
	TIM_DeInit(TIM2);				// Reset timing base interrupts
	TIM_DeInit(TIM3);				// Reset Hsync timer
	GPIO_DeInit(GPIOA);				// Reset clock output
	GPIO_DeInit(GPIOB);				// Reset video output
	GPIO_DeInit(GPIOC);				// Reset sync outputs
	DMA_DeInit(DMA1_Channel2);		// Reset the DMA counters
	DMA_DeInit(DMA1_Channel3);
	DMA_DeInit(DMA1_Channel5);
	DMA_DeInit(DMA1_Channel6);

	/* --------------------------- System Clocks Configuration ---------------------*/
	RCC_Configuration();			// enable peripherals
	STM_MB1108_Init();				// enable LEDs and User button on the MB1108 board
	videoInit();
	srand(SysTick->VAL);			// initialise random number generator

	while (1)	// ready to start an application
	{
/*		STM_MB1108_LEDOn(LEDblue);
		STM_MB1108_LEDOff(LEDblue); */
		show();
	}
}
