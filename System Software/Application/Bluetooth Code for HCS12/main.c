#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main_asm.h" /* interface to the assembly module */

#include "vectors12.h"
#include "DBug12.h"

#define enable() __asm(cli)

interrupt void sci1_isr(void);
volatile unsigned short byteCount;

void main(void) {

// initalizations

        PWMPRCLK=0x22;  // clock A prescale = 4
        PWMCLK=0xF0;    // use clock SA on channel 4 & 5            
        PWMSCLA = 25;
        PWMSCLB = 25;                         
        PWMPOL=0xF0;    // output high on period start
        PWMCAE=0;       // left-alingned
        PWMCTL=0;       // 8-bit mode, stop PWM in wait & freeze mode        
        PWMPER4=200;    // set period
        PWMPER5=200;  
        PWMPER6=200;    
        PWMPER7=200;                        
        PWME=0xF0;      // enable channel 4 & 5                
         
        DDRT=0x0F;
        RDRT=0;
        PERT=0xF0;
        PPST=0; 
        
        PWMCNT4=0;
        PWMCNT5=0; 
        PWMCNT6=0; 
        PWMCNT7=0;
        
  /* put your own code here */
  SCI1BDL = 156; /* Set BAUD rate to 9,600 */
  SCI1BDH = 0;
  SCI1CR1 = 0x00; /* 0 0 0 0 0 0 0 0
                     | | | | | | | |
                     | | | | | | | \____ Even Parity
                     | | | | | | \______ Parity Disabled
                     | | | | | \________ Short IDLE line mode (not used)
                     | | | | \__________ Wakeup by IDLE line rec (not used)
                     | | | \____________ 8 data bits
                     | | \______________ Not used (loopback disabled)
                     | \________________ SCI1 enabled in wait mode
                     \__________________ Normal (not loopback) mode
                     */
                     
  SCI1CR2 = 0x24; /* 0 0 1 0 0 1 0 0
                     | | | | | | | |
                     | | | | | | | \____ No Break
                     | | | | | | \______ Not in wakeup mode (always awake)
                     | | | | | \________ Receiver enabled
                     | | | | \__________ Transmitter disabled
                     | | | \____________ No IDLE Interrupt
                     | | \______________ Receiver Interrupts used
                     | \________________ No Transmit Complete Interrupt
                     \__________________ No Transmit Ready Interrupt
                     */
                     
  UserSCI1 = (unsigned short) &sci1_isr;
  byteCount = 0;
  enable();
  
  
  while (1)
  {
      /* Wait for data to be received in ISR,
         then do something with it
       */
  }

}

interrupt void sci1_isr(void)
{
  /* Note: To clear receiver interrupt, need to read SCI1SR1, then read SCI1DRL.
   * The following code does that
   */
   
  if ((SCI1SR1 & 0x20) == 0)
  {
    return; /* Not receiver interrupt */  
  }
  
  /*
   * Recieved data is stored in register SCI1DRL
   * ByteCount alternates between 0 & 1
   *    -> when 0 - use recieved data to set right wheel duty cycle
   *    -> when 1 - use recieved data to set left wheel duty cycle
   */
 
  if(byteCount==0)
  {
    PWMDTY5=(unsigned short)SCI1DRL;
    byteCount++; 
  } 
  else
  {
    PWMDTY6=(unsigned short)SCI1DRL;
    byteCount--; 
  }
  return;
}