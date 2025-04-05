/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for MOTOR_PWM */
#define MOTOR_PWM_INST                                                     TIMG7
#define MOTOR_PWM_INST_IRQHandler                               TIMG7_IRQHandler
#define MOTOR_PWM_INST_INT_IRQN                                 (TIMG7_INT_IRQn)
#define MOTOR_PWM_INST_CLK_FREQ                                         32000000
/* GPIO defines for channel 0 */
#define GPIO_MOTOR_PWM_C0_PORT                                             GPIOA
#define GPIO_MOTOR_PWM_C0_PIN                                     DL_GPIO_PIN_26
#define GPIO_MOTOR_PWM_C0_IOMUX                                  (IOMUX_PINCM59)
#define GPIO_MOTOR_PWM_C0_IOMUX_FUNC                 IOMUX_PINCM59_PF_TIMG7_CCP0
#define GPIO_MOTOR_PWM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_MOTOR_PWM_C1_PORT                                             GPIOA
#define GPIO_MOTOR_PWM_C1_PIN                                     DL_GPIO_PIN_27
#define GPIO_MOTOR_PWM_C1_IOMUX                                  (IOMUX_PINCM60)
#define GPIO_MOTOR_PWM_C1_IOMUX_FUNC                 IOMUX_PINCM60_PF_TIMG7_CCP1
#define GPIO_MOTOR_PWM_C1_IDX                                DL_TIMER_CC_1_INDEX



/* Defines for Control */
#define Control_INST                                                     (TIMA1)
#define Control_INST_IRQHandler                                 TIMA1_IRQHandler
#define Control_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define Control_INST_LOAD_VALUE                                           (399U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for HWT101 */
#define HWT101_INST                                                        UART1
#define HWT101_INST_IRQHandler                                  UART1_IRQHandler
#define HWT101_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_HWT101_RX_PORT                                                GPIOA
#define GPIO_HWT101_TX_PORT                                                GPIOA
#define GPIO_HWT101_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_HWT101_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_HWT101_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_HWT101_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_HWT101_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_HWT101_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define HWT101_BAUD_RATE                                                (115200)
#define HWT101_IBRD_4_MHZ_115200_BAUD                                        (2)
#define HWT101_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for Hwt101 */
#define Hwt101_INST                                                        UART2
#define Hwt101_INST_IRQHandler                                  UART2_IRQHandler
#define Hwt101_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_Hwt101_RX_PORT                                                GPIOA
#define GPIO_Hwt101_TX_PORT                                                GPIOA
#define GPIO_Hwt101_RX_PIN                                        DL_GPIO_PIN_22
#define GPIO_Hwt101_TX_PIN                                        DL_GPIO_PIN_23
#define GPIO_Hwt101_IOMUX_RX                                     (IOMUX_PINCM47)
#define GPIO_Hwt101_IOMUX_TX                                     (IOMUX_PINCM53)
#define GPIO_Hwt101_IOMUX_RX_FUNC                      IOMUX_PINCM47_PF_UART2_RX
#define GPIO_Hwt101_IOMUX_TX_FUNC                      IOMUX_PINCM53_PF_UART2_TX
#define Hwt101_BAUD_RATE                                                (115200)
#define Hwt101_IBRD_4_MHZ_115200_BAUD                                        (2)
#define Hwt101_FBRD_4_MHZ_115200_BAUD                                       (11)





/* Port definition for Pin Group LED1 */
#define LED1_PORT                                                        (GPIOA)

/* Defines for PIN_21: GPIOA.21 with pinCMx 46 on package pin 17 */
#define LED1_PIN_21_PIN                                         (DL_GPIO_PIN_21)
#define LED1_PIN_21_IOMUX                                        (IOMUX_PINCM46)
/* Port definition for Pin Group Beep */
#define Beep_PORT                                                        (GPIOB)

/* Defines for PIN_2: GPIOB.2 with pinCMx 15 on package pin 50 */
#define Beep_PIN_2_PIN                                           (DL_GPIO_PIN_2)
#define Beep_PIN_2_IOMUX                                         (IOMUX_PINCM15)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for PIN_18: GPIOA.18 with pinCMx 40 on package pin 11 */
#define KEY_PIN_18_PIN                                          (DL_GPIO_PIN_18)
#define KEY_PIN_18_IOMUX                                         (IOMUX_PINCM40)
/* Defines for PIN_15: GPIOA.15 with pinCMx 37 on package pin 8 */
#define KEY_PIN_15_PIN                                          (DL_GPIO_PIN_15)
#define KEY_PIN_15_IOMUX                                         (IOMUX_PINCM37)
/* Defines for PIN_16: GPIOA.16 with pinCMx 38 on package pin 9 */
#define KEY_PIN_16_PIN                                          (DL_GPIO_PIN_16)
#define KEY_PIN_16_IOMUX                                         (IOMUX_PINCM38)
/* Defines for PIN_17: GPIOA.17 with pinCMx 39 on package pin 10 */
#define KEY_PIN_17_PIN                                          (DL_GPIO_PIN_17)
#define KEY_PIN_17_IOMUX                                         (IOMUX_PINCM39)
/* Port definition for Pin Group OLED */
#define OLED_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 33 */
#define OLED_SCL_PIN                                             (DL_GPIO_PIN_0)
#define OLED_SCL_IOMUX                                            (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 34 */
#define OLED_SDA_PIN                                             (DL_GPIO_PIN_1)
#define OLED_SDA_IOMUX                                            (IOMUX_PINCM2)
/* Port definition for Pin Group MPU */
#define MPU_PORT                                                         (GPIOA)

/* Defines for M_SDA: GPIOA.12 with pinCMx 34 on package pin 5 */
#define MPU_M_SDA_PIN                                           (DL_GPIO_PIN_12)
#define MPU_M_SDA_IOMUX                                          (IOMUX_PINCM34)
/* Defines for M_SCL: GPIOA.13 with pinCMx 35 on package pin 6 */
#define MPU_M_SCL_PIN                                           (DL_GPIO_PIN_13)
#define MPU_M_SCL_IOMUX                                          (IOMUX_PINCM35)
/* Defines for MPU_INT: GPIOA.14 with pinCMx 36 on package pin 7 */
// pins affected by this interrupt request:["MPU_INT"]
#define MPU_INT_IRQN                                            (GPIOA_INT_IRQn)
#define MPU_INT_IIDX                            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define MPU_MPU_INT_IIDX                                    (DL_GPIO_IIDX_DIO14)
#define MPU_MPU_INT_PIN                                         (DL_GPIO_PIN_14)
#define MPU_MPU_INT_IOMUX                                        (IOMUX_PINCM36)
/* Port definition for Pin Group Motor_pin */
#define Motor_pin_PORT                                                   (GPIOA)

/* Defines for AIN1: GPIOA.28 with pinCMx 3 on package pin 35 */
#define Motor_pin_AIN1_PIN                                      (DL_GPIO_PIN_28)
#define Motor_pin_AIN1_IOMUX                                      (IOMUX_PINCM3)
/* Defines for AIN2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define Motor_pin_AIN2_PIN                                      (DL_GPIO_PIN_31)
#define Motor_pin_AIN2_IOMUX                                      (IOMUX_PINCM6)
/* Defines for BIN1: GPIOA.24 with pinCMx 54 on package pin 25 */
#define Motor_pin_BIN1_PIN                                      (DL_GPIO_PIN_24)
#define Motor_pin_BIN1_IOMUX                                     (IOMUX_PINCM54)
/* Defines for BIN2: GPIOA.25 with pinCMx 55 on package pin 26 */
#define Motor_pin_BIN2_PIN                                      (DL_GPIO_PIN_25)
#define Motor_pin_BIN2_IOMUX                                     (IOMUX_PINCM55)
/* Port definition for Pin Group Encoder_Left */
#define Encoder_Left_PORT                                                (GPIOB)

/* Defines for PINB_20: GPIOB.20 with pinCMx 48 on package pin 19 */
// groups represented: ["Encoder_Right","Encoder_Left"]
// pins affected: ["PINB_18","PINB_19","PINB_20","PINB_24"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder_Left_PINB_20_IIDX                           (DL_GPIO_IIDX_DIO20)
#define Encoder_Left_PINB_20_PIN                                (DL_GPIO_PIN_20)
#define Encoder_Left_PINB_20_IOMUX                               (IOMUX_PINCM48)
/* Defines for PINB_24: GPIOB.24 with pinCMx 52 on package pin 23 */
#define Encoder_Left_PINB_24_IIDX                           (DL_GPIO_IIDX_DIO24)
#define Encoder_Left_PINB_24_PIN                                (DL_GPIO_PIN_24)
#define Encoder_Left_PINB_24_IOMUX                               (IOMUX_PINCM52)
/* Port definition for Pin Group Encoder_Right */
#define Encoder_Right_PORT                                               (GPIOB)

/* Defines for PINB_18: GPIOB.18 with pinCMx 44 on package pin 15 */
#define Encoder_Right_PINB_18_IIDX                          (DL_GPIO_IIDX_DIO18)
#define Encoder_Right_PINB_18_PIN                               (DL_GPIO_PIN_18)
#define Encoder_Right_PINB_18_IOMUX                              (IOMUX_PINCM44)
/* Defines for PINB_19: GPIOB.19 with pinCMx 45 on package pin 16 */
#define Encoder_Right_PINB_19_IIDX                          (DL_GPIO_IIDX_DIO19)
#define Encoder_Right_PINB_19_PIN                               (DL_GPIO_PIN_19)
#define Encoder_Right_PINB_19_IOMUX                              (IOMUX_PINCM45)
/* Defines for L2: GPIOA.2 with pinCMx 7 on package pin 42 */
#define Track_L2_PORT                                                    (GPIOA)
#define Track_L2_PIN                                             (DL_GPIO_PIN_2)
#define Track_L2_IOMUX                                            (IOMUX_PINCM7)
/* Defines for L1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define Track_L1_PORT                                                    (GPIOA)
#define Track_L1_PIN                                             (DL_GPIO_PIN_7)
#define Track_L1_IOMUX                                           (IOMUX_PINCM14)
/* Defines for M: GPIOB.3 with pinCMx 16 on package pin 51 */
#define Track_M_PORT                                                     (GPIOB)
#define Track_M_PIN                                              (DL_GPIO_PIN_3)
#define Track_M_IOMUX                                            (IOMUX_PINCM16)
/* Defines for R1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define Track_R1_PORT                                                    (GPIOB)
#define Track_R1_PIN                                             (DL_GPIO_PIN_6)
#define Track_R1_IOMUX                                           (IOMUX_PINCM23)
/* Defines for R2: GPIOB.7 with pinCMx 24 on package pin 59 */
#define Track_R2_PORT                                                    (GPIOB)
#define Track_R2_PIN                                             (DL_GPIO_PIN_7)
#define Track_R2_IOMUX                                           (IOMUX_PINCM24)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_MOTOR_PWM_init(void);
void SYSCFG_DL_Control_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_HWT101_init(void);
void SYSCFG_DL_Hwt101_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
