/** 
 *  @file init.h
 *  @brief Initialize routine for HCS12 modules.
 *  @author Madzivire Chikwanda
 *  @date 22 April 2015
 *
 *  The following modules and registers are initialized by the init routine
 *  - ADT1 Analog to Digital module
 *  - PORT A & B
 *  - TIMER module
 *  	- Pulse width modulation (PWM) registers
 *  	- Pulse Accumulator (PAC) registers 
 */


/** 
 *  @brief Initialize registers.
 *  @param void
 *  @return void
 */

void init (void){

/* Initialize A/D registers & start conversions */
  ATD1DIEN=0;      // enable analog input
  ATD1CTL2=0x80;   // ADPU=1 Enable A/D, & wait for warm up 
  wait20us();
  ATD1CTL3=0x38;   // 5 conversions per sequence 0X28
  ATD1CTL4=0xE5;   // 8 bit conversions, 7 us/conversion
  ATD1CTL5=0xB0;   // right justified, unsigned, continuos conversions, multi @ 0 

/* Initialize Ports A & B */
  DDRA=1;         // output @ PA0 & PB7 to motor direction
  DDRB=0x80;

/* Port T - enable input-capture, rising edge, 16-bit counters, no interupt */
  TIOS=0;
  TCTL4=1; 
  PACTL=0x50;       
  PBCTL=0x62;
  
  PACN10=0;       // reset pulse accumulators, (PACN10==right/PACN32==left)
  PACN32=0;
  
 /* Initialize PWM registers */
  PWMCLK=0x30;    // use clock SA on channel 4 & 5      
  PWMPRCLK=0x02;  // clock A prescale = 4
  PWMSCLA=150;    // clock SB prescale = 50
  PWMPOL=0xF0;    // output high on period start
  PWMCAE=0;       // left-alingned
  PWMCTL=0x0C;    // 8-bit mode, stop PWM in wait & freeze mode
  
  PWMPER4=200;    // set period
  PWMPER5=200;  
  PWMDTY4=0;      // set 0% duty cycle, (4=>right wheel/5=>left wheel)
  PWMDTY5=0; 
  PWMCNT4=0;      // reset counters
  PWMCNT5=0;
  PWME=0x30;      // enable channel 4 & 5
  
  
  ATD0DIEN=1;     // enable digital input on pin 0  
}
