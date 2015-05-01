#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "main_asm.h" /* interface to the assembly module */

#include "vectors12.h"
#include "DBug12.h"

#define enable() __asm(cli)

interrupt void sci1_isr(void);
volatile signed short data[80];
volatile int i;
//data = {0};

void main(void) {
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
  i = 0;
  enable();
  
  
  while (1)
  {
      /* Wait for data to be received in ISR,
         then do something with it
       */
       
       printf("Last byteValue = %d\n\r",data[i]);
       printf("waiting.................\n\r............................\n\r");
  }

}

interrupt void sci1_isr(void)
{
  /* Note: To clear receiver interrupt, need to read SCI1SR1, then read SCI1DRL.
   * The following code does that
   */
   
  if ((SCI1SR1 & 0x20) == 0)
  {
    //printf("Not receiver Interrupt \n\r");
    return; /* Not receiver interrupt */  
  }
  
  data[i] = SCI1DRL;
  i = (i ==80) ? i+1 : 0;
  return;
}