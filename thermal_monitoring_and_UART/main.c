#include "m4.h"
#include <math.h>
#include <stdlib.h>

void PortF_Init()
{
  // Enables all LED pins as outputs and enables the associated clock
  RCGC_GPIO |= 0x20;
  GPIO_F_DIR = ALL_LED;
  GPIO_F_DEN = ALL;
  GPIO_F_DATA = BLACK;
  GPIO_UNLOCK = 0x4c4f434b;
  GPIO_CR = 0xff;
  GPIO_F_PUR = 0x11;
}

void Timer0_Init(int clock_speed){
  // Enables timer functionality and the associated clock
  RCGCTIMER_T0 = 0x01;
  GPTMCTL = 0x00;
  GPTMCFG = 0x00000000;
  GPTMTAMR = 0x02;
  GPTMTAILR = clock_speed; // Ensures thatthe timer times out at one second.
  GPTMIMR = 0x01;
  GPTMICR = 0x01;
  GPTMCTL = 0x21;
}

void PLL_Init(){
  // 0 Use RCC
  RCC2 |= 0x80000000;
  // 1 Bypass PLL
  RCC2 |= 0x00000800;
  // 2 Set crystal speed
  RCC = (RCC & ~0x000007c0) + 0x00000540;
  // 3 Set oscillator to main ossiclator
  RCC2 &= ~0x00000070;
  // 4 Power on PLL
  RCC2 &= ~0x00002000;
  // 5 Set PLL DIV to putput 400 MHz
  RCC2 |= 0x40000000;
  // 6 Set SYS clock Div
  RCC2 = (RCC2&~ 0x1fc00000) + (24<<22);
  // 7 Waits for PLL to lock
  while((SYSCTL_RIS &0x00000040)==0){};
  // 8 Enable PLL
  RCC2 &= ~0x00000800;
}

void ADC_Init(){
  // ENA adc clock
  RCGC_ADC |= 0x01;
  // ENA gpioe clock
  RCGC_GPIO |= 0x10;
  // GPIO setup
  GPIO_E_AFSEL |= 0x8;
  GPIO_E_DEN &= ~0x8;
  GPIO_E_AMSEL |= 0x8;
  // Disables ADC 3
  ADCACTSS &= ~0x08;
  // Always Sample ADC
  ADC_EMUX = 0x5000;
  // Sets internal temp sensor to flag at first sample in.
  ADC_SSCTL3 |= 0x6;
  ADC_SSCTL3 |= (1<<3);
  ADCACTSS |= 0x8;
  // Sets interrupt mask
  ADC_IM |= 0x08;
  // Enables interrupt for ADC
  NVIC_EN0 |= 0x00020000;
}

// Initalize UART connection
void UART_Init(int clock_speed){
  // Enable clocks
  RCGC_GPIO |= 0x01;
  RCGC_UART |= 0x01;
  // Disable before programming
  UART_DISABLE;
  // COnfigure GPIO
  GPIO_AFSEL_A |= 0x03;
  GPIO_PCTL_A |= 0x11;
  GPIO_A_DEN |= 0x03;
  // Set clock and clock divisors
  UART0_CC = 0x00;
  double brd = (double) clock_speed/(16*9600);
  int ibrd = floor(brd);
  int fbrd = ((brd - ibrd) * 64 + 0.5);
  UART0_IBRD = ibrd;
  UART0_FBRD = fbrd;
  // Set connection type
  UART0_LCRH = 0x70;
  // Enable UART
  UART0_CTL = 0x301;
}

void ADC0_Handler( void ){
  // Takes raw val @ ADC_SSFIFO3 reg
  int temp_raw = ADC_SSFIFO3;
  // Applys transform to temp reading
  double temp = (147.5 - ((75.0 * (3.3 - 0.0) * temp_raw)/4096.0));
  // Assign LED color according to the provided table in the lab spec
  if ((temp < 17) && (temp >= 0)){
    GPIO_F_DATA = RED;
  } else if ((temp < 19) && (temp >= 17)){
    GPIO_F_DATA = BLUE;
  } else if ((temp < 21) && (temp >= 19)){
    GPIO_F_DATA = VIOLET;
  } else if ((temp < 23) && (temp >= 21)){
    GPIO_F_DATA = GREEN;
  } else if ((temp < 25) && (temp >= 23)){
    GPIO_F_DATA = YELLOW;
  } else if ((temp < 27) && (temp >= 25)){
    GPIO_F_DATA = LIGHT_BLUE;
  } else if ((temp < 40) && (temp >= 27)){
    GPIO_F_DATA = WHITE;
  } else {
    GPIO_F_DATA = BLACK; // Sets all LEDs off as the default state
  }
  // CHeck UART status
  if((UART0_FLAG & 0x00000020) == 0){
    // Write MSD
    UART0_DATA = (char) temp / 10 + 48;
    // Write LSD
    UART0_DATA = (char) temp % 10 + 48;
    // Write newline
    UART0_DATA = '\r';
    UART0_DATA = '\n';
  }
  // Clears interrupts related to timer and ADC
  GPTMICR = 0x11;
  ADC_ISC = 0x08;
}

// Runs setup for the timer and LED's and then runs code to cycle throug the
// LED's at a one second intervals
int main()
{
  // Runs initialization functions
  PLL_Init();
  int clock_speed = 0x00f42400; // Default clock speed of 16 MHz
  UART_Init(clock_speed);
  ADC_Init();
  PortF_Init();
  Timer0_Init(clock_speed); // Uses clock speed input to properly set interrupt
                            // at one second intervals
  // Constantly checks button input to varry clock speed
  while(1){
    if((PF0 == 0x00) || (PF4 == 0x00)){
      UART_DISABLE;
      RCC2 |= 0x00000800;
      if (PF4 == 0x00){
        clock_speed = 0x04c4b400;
        // Set SYS clock Div to 4 + 1 = 5
        RCC2 = (RCC2&~ 0x1fc00000) + (4<<22);
      } else if(PF0 == 0x00) {
        clock_speed = 0x003d0900;
        // Set SYS clock Div to 99 + 1 = 100
        RCC2 = (RCC2&~ 0x1fc00000) + (99<<22);
      }
      // Waits for PLL to lock
      while((SYSCTL_RIS &0x00000040)==0){};
      // Enable PLL
      RCC2 &= ~0x00000800;
      Timer0_Init(clock_speed);
      UART_Init(clock_speed);
    }
  }
  return 0;
}
