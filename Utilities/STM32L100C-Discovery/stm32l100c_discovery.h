/**
  ******************************************************************************
  * @file    stm32l100c_discovery.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    29-July-2013
  * @brief   This file contains definitions for STM32L100C-Discovery's Leds, push-
  *          buttons hardware resources.
  ******************************************************************************
  * Definitions for STM32 Value Line Discovery Board type MB1108
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L100C_DISCOVERY_H
#define __STM32L100C_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32L100C_DISCOVERY
  * @{
  */
      
/** @addtogroup STM32L100C_DISCOVERY_LOW_LEVEL
  * @{
  */ 
 /**
  * @brief USER push-button
  */
#define USER_BUTTON_EXTI_LINE			EXTI_Line0
#define USER_BUTTON_EXTI_PORT_SOURCE	EXTI_PortSourceGPIOA
#define USER_BUTTON_EXTI_PIN_SOURCE		EXTI_PinSource0
#define USER_BUTTON_EXTI_IRQn			EXTI0_IRQn
#define USER_BUTTON_GPIO_CLK			RCC_AHBPeriph_GPIOA

 /**
  * @brief USER on board LEDs
  */
#define USER_BUTTON_GPIO_PIN			GPIO_Pin_0
#define USER_BUTTON_GPIO_PORT			GPIOA
#define USER_BUTTON_GPIO_CLK			RCC_AHBPeriph_GPIOA

#define LED3_PIN						GPIO_Pin_8
#define LED3_GPIO_PORT					GPIOC
#define LED3_GPIO_CLK					RCC_AHBPeriph_GPIOC

#define LED4_PIN						GPIO_Pin_9
#define LED4_GPIO_PORT					GPIOC
#define LED4_GPIO_CLK					RCC_AHBPeriph_GPIOC

/* The LEDs on the MB1108 are both on PortC, so no need to index them */
#define LEDS_GPIO_PORT					GPIOC

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
	BUTTON_USER = GPIO_Pin_0
} Button_TypeDef;

typedef enum 
{  
	BUTTON_MODE_GPIO = 0,
	BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;
  
typedef enum
{
	LEDblue = LED3_PIN,
	LEDgreen = LED4_PIN
} Led_TypeDef;

/**
  * @}
  */ 

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** @addtogroup STM32L100C_DISCOVERY_LOW_LEVEL_LED
  * @{
  */

/**
  * @}
  */ 

/** @addtogroup STM32L100C_DISCOVERY_LOW_LEVEL_BUTTON
  * @{
  */  

/**
  * @}
  */ 
  
    
/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Exported_Macros
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32L100C_DISCOVERY_LOW_LEVEL_Exported_Functions
  * @{
  */
void STM_MB1108_Init();
void STM_MB1108_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_USER: User Push Button
  * @retval The Button GPIO pin value.
  */
__inline__ uint32_t STM_MB1108_PBGetState()
{
  /* There is no Wakeup button on STM32L1-Discovery Kit */
  return GPIO_ReadInputDataBit(USER_BUTTON_GPIO_PORT, USER_BUTTON_GPIO_PIN);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED3_Pin / LED4_Pin / PC6_Pin/ PC7_Pin
  * @retval None
  */
__inline__ void STM_MB1108_LEDOn(Led_TypeDef Led)
{
	LEDS_GPIO_PORT->BSRRL = Led;
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED3_Pin / LED4_Pin / PC6_Pin / PC7_Pin
  * @retval None
  */
__inline__ void STM_MB1108_LEDOff(Led_TypeDef Led)
{
	LEDS_GPIO_PORT->BSRRH = Led;
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED3_Pin / LED4_Pin / PC6_Pin/ PC7_Pin
  * @retval None
  */
__inline__ void STM_MB1108_LEDToggle(Led_TypeDef Led)
{
	LEDS_GPIO_PORT->ODR ^= Led;
}

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L100C_DISCOVERY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
