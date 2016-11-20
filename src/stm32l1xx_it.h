/** @file    PALdemo/stm32l1xx_it.h
  * @author  E.J.W. Vrieze
  * @version V1.1.1
  * @date    13-June-2016
  * @brief   This file contains the headers of the interrupt handlers.
  */
#ifndef __STM32L1xx_IT_H
#define __STM32L1xx_IT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif /* __STM32L1xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
