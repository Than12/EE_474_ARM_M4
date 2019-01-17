#ifndef TEST_H_
#define TEST_H_

// Lists macros, constants and derefrenced pointers to important 
// locations in memory

// Constants
#define RED             ((unsigned short int)0x02)
#define GREEN           ((unsigned short int)0x08)
#define BLUE            ((unsigned short int)0x04)
#define ALL             ((unsigned short int)0x1f)
#define ALL_LED         ((unsigned short int)0x0e)

// GPIO addresses
#define FCLK            (*((unsigned short int*)0x400fe608))
#define GPIO_F_DIR      (*((unsigned short int*)0x40025400))
#define GPIO_F_DEN      (*((unsigned short int*)0x4002551c))
#define GPIO_F_DATA     (*((volatile unsigned short int*)0x400253fc))
#define GPIO_F_PUR      (*((unsigned short int*)0x40025510))
#define GPIO_UNLOCK     (*((unsigned int*)0x40025520))
#define GPIO_CR         (*((unsigned int*)0x40025524))
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

// NVIC
#define NVIC_EN0        (*((unsigned int *)0xe000e100))
#define NVIC_DIS0        (*((unsigned int *)0xe000e180))
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

#endif