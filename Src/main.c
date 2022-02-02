#include <stdio.h>
#include "uart.h"
#include "systick.h"
#include "tim.h"

int timestamp = 0;

/* Setup : connect a jumper wire from PA5 to PA6 */
/* stm32-nucleo64_user_guide, p28 */

int main(void)
{
    tim2_pa5_output_compare(); // generates a square wave
    tim3_pa6_input_capture();

    while(1)
    {
        /*Wait until edge is captured*/
        while(!(TIM3->SR & SR_CC1IF)) {}

        /*Read capture value*/
        timestamp = TIM3->CCR1;

    }
}
