/**
  ******************************************************************************
  * @file    stm32l100c_usarts.h
  * @author  E.J.W. Vrieze
  * @version V5.0.2
  * @date    22-12-2015
  * @brief   This file contains definitions for STM32L100RC COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L100C_USARTS_H
#define __STM32L100C_USARTS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */

/** @addtogroup STM32L100RC_USARTS
  * @{
  */
      
/** @addtogroup STM32L100RC_USARTS_LOW_LEVEL
  * @{
  */ 

/** @defgroup STM32L100RC_USARTS_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
  COM1 = 0,
  COM2 = 1,
  COM3 = 2
} COM_TypeDef;  
/**
  * @}
  */ 

/** @defgroup STM32L100RC_USARTS_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/**
  * @}
  */ 
  
/** @addtogroup STM32L100RC_USARTS_LOW_LEVEL_COM
  * @{
  */
#define COMn                             3

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define L100RC_COM1                        USART1
#define L100RC_COM1_CLK                    RCC_APB2Periph_USART1

#define L100RC_COM1_TX_PIN                 GPIO_Pin_6
#define L100RC_COM1_TX_GPIO_PORT           GPIOB
#define L100RC_COM1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define L100RC_COM1_TX_SOURCE              GPIO_PinSource6
#define L100RC_COM1_TX_AF                  GPIO_AF_USART1

#define L100RC_COM1_RX_PIN                 GPIO_Pin_7
#define L100RC_COM1_RX_GPIO_PORT           GPIOB
#define L100RC_COM1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define L100RC_COM1_RX_SOURCE              GPIO_PinSource7
#define L100RC_COM1_RX_AF                  GPIO_AF_USART1

#define L100RC_COM1_RTS_PIN                GPIO_Pin_12
#define L100RC_COM1_RTS_GPIO_PORT          GPIOA
#define L100RC_COM1_RTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define L100RC_COM1_RTS_SOURCE             GPIO_PinSource12
#define L100RC_COM1_RTS_AF                 GPIO_AF_USART1

#define L100RC_COM1_CTS_PIN                GPIO_Pin_11
#define L100RC_COM1_CTS_GPIO_PORT          GPIOA
#define L100RC_COM1_CTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define L100RC_COM1_CTS_SOURCE             GPIO_PinSource11
#define L100RC_COM1_CTS_AF                 GPIO_AF_USART1

#define L100RC_COM1_IRQn                   USART1_IRQn

/**
 * @brief Definition for COM port2, connected to USART2
 */ 
#define L100RC_COM2                        USART2
#define L100RC_COM2_CLK                    RCC_APB1Periph_USART2

#define L100RC_COM2_TX_PIN                 GPIO_Pin_2
#define L100RC_COM2_TX_GPIO_PORT           GPIOA
#define L100RC_COM2_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define L100RC_COM2_TX_SOURCE              GPIO_PinSource2
#define L100RC_COM2_TX_AF                  GPIO_AF_USART2

#define L100RC_COM2_RX_PIN                 GPIO_Pin_3
#define L100RC_COM2_RX_GPIO_PORT           GPIOA
#define L100RC_COM2_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define L100RC_COM2_RX_SOURCE              GPIO_PinSource3
#define L100RC_COM2_RX_AF                  GPIO_AF_USART2

#define L100RC_COM2_RTS_PIN                GPIO_Pin_1
#define L100RC_COM2_RTS_GPIO_PORT          GPIOA
#define L100RC_COM2_RTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define L100RC_COM2_RTS_SOURCE             GPIO_PinSource1
#define L100RC_COM2_RTS_AF                 GPIO_AF_USART2

#define L100RC_COM2_CTS_PIN                GPIO_Pin_0
#define L100RC_COM2_CTS_GPIO_PORT          GPIOA
#define L100RC_COM2_CTS_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define L100RC_COM2_CTS_SOURCE             GPIO_PinSource0
#define L100RC_COM2_CTS_AF                 GPIO_AF_USART2

#define L100RC_COM2_IRQn                   USART2_IRQn

/**
 * @brief Definition for COM port2, connected to USART3
 */ 
#define L100RC_COM3                        USART3
#define L100RC_COM3_CLK                    RCC_APB1Periph_USART3

#define L100RC_COM3_TX_PIN                 GPIO_Pin_10
#define L100RC_COM3_TX_GPIO_PORT           GPIOB
#define L100RC_COM3_TX_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define L100RC_COM3_TX_SOURCE              GPIO_PinSource10
#define L100RC_COM3_TX_AF                  GPIO_AF_USART3

#define L100RC_COM3_RX_PIN                 GPIO_Pin_11
#define L100RC_COM3_RX_GPIO_PORT           GPIOB
#define L100RC_COM3_RX_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define L100RC_COM3_RX_SOURCE              GPIO_PinSource11
#define L100RC_COM3_RX_AF                  GPIO_AF_USART3

#define L100RC_COM3_RTS_PIN                GPIO_Pin_14
#define L100RC_COM3_RTS_GPIO_PORT          GPIOB
#define L100RC_COM3_RTS_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define L100RC_COM3_RTS_SOURCE             GPIO_PinSource14
#define L100RC_COM3_RTS_AF                 GPIO_AF_USART3

#define L100RC_COM3_CTS_PIN                GPIO_Pin_13
#define L100RC_COM3_CTS_GPIO_PORT          GPIOB
#define L100RC_COM3_CTS_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define L100RC_COM3_CTS_SOURCE             GPIO_PinSource13
#define L100RC_COM3_CTS_AF                 GPIO_AF_USART3

#define L100RC_COM3_IRQn                   USART3_IRQn

/**
  * @}
  */ 


#define sEE_I2C_DMA                      DMA1   
#define sEE_I2C_DMA_CHANNEL_TX           DMA1_Channel6
#define sEE_I2C_DMA_CHANNEL_RX           DMA1_Channel7 
#define sEE_I2C_DMA_FLAG_TX_TC           DMA1_IT_TC6   
#define sEE_I2C_DMA_FLAG_TX_GL           DMA1_IT_GL6 
#define sEE_I2C_DMA_FLAG_RX_TC           DMA1_IT_TC7 
#define sEE_I2C_DMA_FLAG_RX_GL           DMA1_IT_GL7    
#define sEE_I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
#define sEE_I2C_DR_Address               ((uint32_t)0x40005410)
#define sEE_USE_DMA
   
#define sEE_I2C_DMA_TX_IRQn              DMA1_Channel6_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Channel7_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Channel6_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Channel7_IRQHandler  
#define sEE_I2C_DMA_PREPRIO              0
#define sEE_I2C_DMA_SUBPRIO              0
 
#define sEE_DIRECTION_TX                 0
#define sEE_DIRECTION_RX                 1 

/* Time constant for the delay caclulation allowing to have a millisecond 
   incrementing counter. This value should be equal to (System Clock / 1000).
   ie. if system clock = 32MHz then sEE_TIME_CONST should be 32. */
#define sEE_TIME_CONST          32 

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/** @defgroup STM32L100RC_USARTS_LOW_LEVEL_Exported_Macros
  * @{
  */  
/**
  * @}
  */ 


/** @defgroup STM32L100RC_USARTS_LOW_LEVEL_Exported_Functions
  * @{
  */
void STM_L100RC_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void STM_L100RC_COMWait(COM_TypeDef COM);
void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void);
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction);

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L100RC_USARTS_H */
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
