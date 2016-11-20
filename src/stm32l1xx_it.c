/** @file    PALdemo/stm32l1xx_it.c
  * @author  E.J.W. Vrieze
  * @version V1.1.1
  * @date    13-June-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"
#include "stm32l100c_discovery.h"

/** @addtogroup STM32L1xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_PWM_Output
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t TimingDelay;
/* Private function prototypes -----------------------------------------------*/
void USERaction(void);
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if (TimingDelay != 0)
		--TimingDelay;
}

/******************************************************************************/
/*            STM32L1xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) != RESET)
	{
		/* Clear the Right Button EXTI line pending bit */
		EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
		USERaction();
	}
}

/*
	This irq is generated at the beginning of video output at x = 0

*/

void TIM3_IRQHandler()
{
	uint16_t reden = TIM3->SR;
	if (reden & TIM_IT_CC4) {		// reconfigure this Hsync timer
		GPIOA->BSRRH = GPIO_Pin_8;		// scope output on low
		TIM3->SR = 0;					// ~TIM_IT_Update;		// clear all but CC1
		GPIOA->BSRRL = GPIO_Pin_8;		// scope output on high
	} else if (reden & TIM_IT_CC1) {
		GPIOA->BSRRH = GPIO_Pin_9;		// scope output on low
		TIM3->SR = TIM_IT_CC4;// ~TIM_IT_CC1;		// clear all but Update
		GPIOA->BSRRL = GPIO_Pin_9;		// scope output on high
	} else
		TIM3->SR = 0;					// other interrupts not of interest
}
