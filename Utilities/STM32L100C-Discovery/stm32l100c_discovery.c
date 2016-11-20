/**
  ******************************************************************************
  * @file    stm32l100c_discovery.c
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    29-July-2016
  * @brief   This file provides set of firmware functions to manage Leds and
  *          push-button available on STM32L100C-Discovery Kit from STMicroelectronics.
  */
  
/* Includes ------------------------------------------------------------------*/
#include "stm32l100c_discovery.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32L100C_DISCOVERY
  * @{
  */ 
    
/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL 
  * @brief This file provides firmware functions to manage Leds and push-buttons, 
  *        available on STM32L100C_DISCOVERY evaluation board from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Private_Functions
  * @{
  */

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be:
  *     @arg BUTTON_USER: User Push Button      
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability
  * @retval None
  */
void STM_MB1108_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON Clock */
  RCC_AHBPeriphClockCmd(USER_BUTTON_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = USER_BUTTON_GPIO_PIN;
  GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);

  if (Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    SYSCFG_EXTILineConfig(USER_BUTTON_EXTI_PORT_SOURCE, USER_BUTTON_EXTI_PIN_SOURCE);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = USER_BUTTON_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    if (Button != BUTTON_USER)
    {
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    }
    else
    {
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    
    }
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = USER_BUTTON_EXTI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); 
  }
}

/**
  * @brief  Configures LED GPIO.
  * @retval None
  */
void STM_MB1108_Init()
{
  EXTI_InitTypeDef	EXTI_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON and GPIO_LED clocks */
  RCC_AHBPeriphClockCmd(USER_BUTTON_GPIO_CLK | LED3_GPIO_CLK | LED4_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = USER_BUTTON_GPIO_PIN;
  GPIO_Init(USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);

	/* Connect Button EXTI Line to Button GPIO Pin */
	SYSCFG_EXTILineConfig(USER_BUTTON_EXTI_PORT_SOURCE, USER_BUTTON_EXTI_PIN_SOURCE);

	/* Configure Button EXTI line */
	EXTI_InitStructure.EXTI_Line = USER_BUTTON_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = USER_BUTTON_EXTI_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

  /* Configure the GPIO_LED pins (using a single GPIO Port) */
  GPIO_InitStructure.GPIO_Pin = LED3_PIN | LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
  GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
