#ifndef M4_H_
#define M4_H_

// Lists macros, constants and derefrenced pointers to important
// locations in memory

// Constants
#define RED             ((unsigned short int)0x02)
#define GREEN           ((unsigned short int)0x08)
#define BLUE            ((unsigned short int)0x04)
#define VIOLET          ((unsigned short int)0x06)
#define YELLOW          ((unsigned short int)0x0a)
#define LIGHT_BLUE      ((unsigned short int)0x0c)
#define WHITE           ((unsigned short int)0x0e)
#define BLACK           ((unsigned short int)0x00)
#define ALL             ((unsigned short int)0x1f)
#define ALL_LED         ((unsigned short int)0x0e)

// GPIO addresses
#define RCGC_GPIO       (*((unsigned short int *)0x400fe608))
#define GPIO_F_DIR      (*((unsigned short int *)0x40025400))
#define GPIO_F_DEN      (*((unsigned short int *)0x4002551c))
#define GPIO_F_DATA     (*((volatile unsigned short int *)0x400253fc))
#define GPIO_F_PUR      (*((unsigned short int *)0x40025510))
#define GPIO_UNLOCK     (*((unsigned int *)0x40025520))
#define GPIO_CR         (*((unsigned int *)0x40025524))
#define PF0             (*((volatile unsigned short int *)0x40025004))
#define PF1             (*((volatile unsigned short int *)0x40025008))
#define PF2             (*((volatile unsigned short int *)0x40025010))
#define PF3             (*((volatile unsigned short int *)0x40025020))
#define PF4             (*((volatile unsigned short int *)0x40025040))
#define GPIO_F_IS       (*((unsigned int *)0x40025404))
#define GPIO_F_IBE      (*((unsigned int *)0x40025408))
#define GPIO_F_IEV      (*((unsigned int *)0x4002540c))
#define GPIO_F_IM       (*((unsigned int *)0x40025410))
#define GPIO_F_ICR      (*((unsigned int *)0x4002541c))
#define GPIO_E_AFSEL    (*((unsigned int *)0x40024420))
#define GPIO_E_DEN      (*((unsigned int *)0x4002451c))
#define GPIO_E_AMSEL    (*((unsigned int *)0x40024528))

// NVIC
#define NVIC_EN0        (*((unsigned int *)0xe000e100))
#define NVIC_DIS0       (*((unsigned int *)0xe000e180))
#define NVIC_PRI17      (*((unsigned int *)0xe000e41c))

// Timer addresses
#define RCGCTIMER_T0    (*((unsigned int *)0x400fe604))
#define GPTMCTL         (*((unsigned int *)0x4003000c))
#define GPTMCFG         (*((unsigned int *)0x40030000))
#define GPTMTAMR        (*((unsigned int *)0x40030004))
#define GPTMTAILR       (*((unsigned int *)0x40030028))
#define GPTMRIS         (*((unsigned int *)0x4003001c))
#define GPTMICR         (*((unsigned int *)0x40030024))
#define GPTMIMR         (*((unsigned int *)0x40030018))

// PLL Config
#define RCC             (*((unsigned int *)0x400fe060))
#define RCC2            (*((unsigned int *)0x400fe070))
#define SYSCTL_RIS      (*((unsigned int *)0x400fe050))

// ADC Config
#define RCGC_ADC        (*((unsigned int *)0x400fe638))
#define ADCACTSS        (*((unsigned int *)0x40038000))
#define ADC_EMUX        (*((unsigned int *)0x40038014))
#define ADC_SSMUX3      (*((unsigned int *)0x400380a0))
#define ADC_SSCTL3      (*((unsigned int *)0x400380a4))
#define ADC_IM          (*((unsigned int *)0x40038008))
#define ADC_PSSI        (*((unsigned int *)0x40038028))
#define ADC_ISC         (*((unsigned int *)0x4003800c))
#define ADC_SSFIFO3     (*((unsigned int *)0x400380a8))

// UART
#define RCGC_UART       (*((unsigned int *)0x400fe618))
#define GPIO_CR_A       (*((unsigned int *)0x40004524))
#define GPIO_PCTL_A     (*((unsigned int *)0x4000452c))
#define UART0_CTL       (*((unsigned int *)0x4000c030))
#define UART0_IBRD      (*((unsigned int *)0x4000c024))
#define UART0_FBRD      (*((unsigned int *)0x4000c028))
#define UART0_LCRH      (*((unsigned int *)0x4000c02c))
#define UART0_FLAG      (*((unsigned int *)0x4000c018))
#define UART0_DATA      (*((char *)0x4000c000))
#define UART0_CC        (*((unsigned int *)0x4000cfc8))
#define GPIO_AFSEL_A    (*((unsigned int *)0x40004420))
#define GPIO_A_DEN      (*((unsigned int *)0x4000451c))
#define UART_ICR        (*((unsigned int *)0x40004044))
#define UART_DISABLE    UART0_CTL = ~0x301



#endif
