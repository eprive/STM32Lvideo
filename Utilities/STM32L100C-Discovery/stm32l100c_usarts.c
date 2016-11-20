/**
  ******************************************************************************
  * @file    stm32l100c_usarts.c
  * @author  E.J.W. Vrieze
  * @version V1.0.2
  * @date    22-12-2012
  * @brief   This file provides:
  *            - COM ports (USARTs), applicable for STM32L100RC types
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
  
/* Includes ------------------------------------------------------------------*/
#include "stm32l100c_usarts.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32L100c
  * @{
  */ 

/** @addtogroup STM32L100c_USARTs
  * @{
  */   
    
/** @defgroup STM32L100c_USARTs_LOW_LEVEL
  * @brief This file provides firmware functions to manage COM ports.
  * @{
  */ 

/** @defgroup STM32L100c_USARTs_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100c_USARTs_LOW_LEVEL_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100c_USARTs_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32L100c_USARTs_LOW_LEVEL_Private_Variables
  * @{
  */ 
USART_TypeDef* COM_USART[COMn] = {L100RC_COM1, L100RC_COM2, L100RC_COM3};

GPIO_TypeDef* COM_TX_PORT[COMn] = {L100RC_COM1_TX_GPIO_PORT, L100RC_COM2_TX_GPIO_PORT, L100RC_COM3_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {L100RC_COM1_RX_GPIO_PORT, L100RC_COM2_RX_GPIO_PORT, L100RC_COM3_RX_GPIO_PORT};

const uint32_t COM_USART_CLK[COMn] = {L100RC_COM1_CLK, L100RC_COM2_CLK, L100RC_COM3_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {L100RC_COM1_TX_GPIO_CLK, L100RC_COM2_TX_GPIO_CLK, L100RC_COM3_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {L100RC_COM1_RX_GPIO_CLK, L100RC_COM2_RX_GPIO_CLK, L100RC_COM3_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {L100RC_COM1_TX_PIN, L100RC_COM2_TX_PIN, L100RC_COM3_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {L100RC_COM1_RX_PIN, L100RC_COM2_RX_PIN, L100RC_COM3_RX_PIN};
 
const uint8_t COM_TX_PIN_SOURCE[COMn] = {L100RC_COM1_TX_SOURCE, L100RC_COM2_TX_SOURCE, L100RC_COM3_TX_SOURCE};

const uint8_t COM_RX_PIN_SOURCE[COMn] = {L100RC_COM1_RX_SOURCE, L100RC_COM2_RX_SOURCE, L100RC_COM3_RX_SOURCE};
 
const uint8_t COM_TX_AF[COMn] = {L100RC_COM1_TX_AF, L100RC_COM2_TX_AF, L100RC_COM3_TX_AF};
 
const uint8_t COM_RX_AF[COMn] = {L100RC_COM1_RX_AF, L100RC_COM2_RX_AF, L100RC_COM3_RX_AF};

DMA_InitTypeDef   sEEDMA_InitStructure;

/**
  * @}
  */ 


/** @defgroup STM32L100RC_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @}
  */ 

/** @defgroup STM32L100RC_LOW_LEVEL_Private_Functions
  * @{
  */ 
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(COM_USART[COM1], (uint8_t) ch);

  /* Loop until transmit data register is empty */
  while (USART_GetFlagStatus(COM_USART[COM1], USART_FLAG_TXE) == RESET)
  {}

  return ch;
}

void STM_L100RC_COMWait(COM_TypeDef COM)
/* The software must wait until TC=1. The TC flag remains cleared during all data
   transfers and it is set by hardware at the last frame’s end of transmission*/
{
	while (USART_GetFlagStatus(COM_USART[COM], USART_FLAG_TC) == RESET);
}


/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:    
  *     @arg COM1
  *     @arg COM2  
  *     @arg COM3
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *   contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void STM_L100RC_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  /* Enable UART clock */
  if (COM == COM1)	RCC_APB2PeriphClockCmd(COM_USART_CLK[COM1], ENABLE);
  else				RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);

  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
