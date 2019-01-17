#include "test.h"

void gpioENA()
{
  // Enables all LED pins as outputs and enables the associated clock
  FCLK = 0x20;
  GPIO_F_DIR = ALL_LED;
  GPIO_F_DEN = ALL;
  GPIO_F_DATA = 0x00;
  GPIO_UNLOCK = 0x4c4f434b;
  GPIO_CR = 0xff;
  GPIO_F_PUR = 0x11;
}

void timerENA(){
  // Enables timer functionality and the associated clock
  RCGCTIMER_T0 = 0x01;
  GPTMCTL = 0x00;
  GPTMCFG = 0x00000000;
  GPTMTAMR = 0x02;
  GPTMTAILR = 0x00f42400;
  GPTMIMR = 0x01;
  GPTMCTL = 0x01;
}

void interruptSetup(){
  // Handels setup of interrupt registers
  GPIO_F_IS &= ~0x11;
  GPIO_F_IBE |= 0x11;
  // GPIO_F_IEV = ~0x11;
  GPIO_F_ICR |= 0x11;
  GPIO_F_IM |= 0x11;
  NVIC_EN0 |= 0x40000000;
  GPTMICR = 0x01;
}

void GPIO_F_Handler( void ){
  // Handels behavior based on button input. If PF) is pressed then the timer 
  // is disabled and the red LED is lit, and if PF4 is depressed then the timer 
  // is enabled, and if nothin is depressed, all LED's are turned off and the 
  // timer is also turned off.
  if (PF0 == 0x00){
    NVIC_DIS0 &= 0x00080000;
    GPIO_F_DATA = 0x02;
  } else if (PF4 == 0x00){
    NVIC_EN0 |= 0x40080000;
  } else {
    GPIO_F_DATA = 0x00;
    NVIC_DIS0 &= 0x00080000;
  }
  GPIO_F_ICR = 0x11;
}

// Only activated if PF4 is depessed.
void Timer_Handler( void ){
  // If the blue LED is on or all LED's are off then the red LED is triggered
  if(((GPIO_F_DATA & 0x0e) == 0x00)||(GPIO_F_DATA & 0x08)){
    GPIO_F_DATA = 0x02;
  // True if the red LED is on and triggers the green LED
  } else if(GPIO_F_DATA & 0x02) {
    GPIO_F_DATA = 0x04;
  // True if the Green LED is on, and triggers the blue LED
  } else if(GPIO_F_DATA & 0x04) {
    GPIO_F_DATA = 0x08;
  }
  GPTMICR = 0x11;
}

// Runs setup for the timer and LED's and then runs code to cycle throug the 
// LED's at a one second intervals
int main()
{
  timerENA();
  gpioENA();
  interruptSetup();
  while(1){}
  return 0;
}

