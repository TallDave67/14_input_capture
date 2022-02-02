#include "stm32f4xx.h"

// RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
// stm32f401re_reference_manual, p118
#define GPIOAEN             (1U<<0)

// RCC APB1 peripheral clock enable register (RCC_APB1ENR)
// stm32f401re_reference_manual, p119
#define TIM2EN              (1u<<0)
#define TIM3EN              (1u<<1)

// TIMx control register 1 (TIMx_CR1)
// stm32f401re_reference_manual, p353
#define CR1_CEN             (1u<<0)

// TIMx capture/compare mode register 1 (TIMx_CCMR1)
// stm32f401re_reference_manual, p362
#define CCMR_OC1M_TOGGLE    ((1U<<4) | (1U<<5))
#define CCMR_CC1S           (1U<<0)

// TIMx capture/compare enable register (TIMx_CCER)
// stm32f401re_reference_manual, p366
#define CCER_CC1E           (1U<<0)

// alternate function mapping
// stm32f401re_datasheet, p45
#define AFR5_TIM            (1U<<20) // pa5
#define AFR6_TIM            (1U<<25) // pa6

void tim2_1hz_init(void)
{
    /*Enable clock access to tim2*/
    RCC->APB1ENR |= TIM2EN;

    /*Set prescaler value*/
    TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

    /*Set auto-reload value*/
    TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1 Hz

    /*Clear counter*/
    TIM2->CNT = 0;

    /*Enable timer*/
    TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_compare(void)
{
    /*Enable clock access to GPIOA*/
    RCC->AHB1ENR |= GPIOAEN;

    /*Set pa5 mode to alternate function mode*/
    GPIOA->MODER &= (~(1U<<10));
    GPIOA->MODER |= (1U<<11);

    /*Set pa5 alternate function type to TIM2_CH1 (AF01) */
    GPIOA->AFR[0] |= AFR5_TIM; //this is the new function we have given this pin, it now reacts to the timer

    /*Enable clock access to tim2*/
    RCC->APB1ENR |= TIM2EN;

    /*Set prescaler value*/
    TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000

    /*Set auto-reload value*/
    TIM2->ARR = 10000 - 1; // 10 000 / 10 000 = 1 Hz

    /*Set the compare mode (output) to toggle*/
    TIM2->CCMR1 = CCMR_OC1M_TOGGLE;

    /*Enable ch1 in compare mode (output)*/
    TIM2->CCER = CCER_CC1E;

    /*Clear counter*/
    TIM2->CNT = 0;

    /*Enable timer*/
    TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture(void)
{
    // try to capture rate of pa5 toggle

    /*Enable clock access to GPIOA*/
    RCC->AHB1ENR |= GPIOAEN;

    /*Set pa6 mode to alternate function mode*/
    GPIOA->MODER &= (~(1U<<12));
    GPIOA->MODER |= (1U<<13);

    /*Set pa6 alternate function type to TIM3_CH1 (AF02) */
    GPIOA->AFR[0] |= AFR6_TIM; //this is the new function we have given this pin, it now reacts to the timer

    /*Enable clock access to tim3*/
    RCC->APB1ENR |= TIM3EN;

    /*Set prescaler value*/
    TIM3->PSC = 16000 - 1; // 16 000 000 / 16 000 = 1 000

    /*Set the capture mode (input)*/
    TIM3->CCMR1 = CCMR_CC1S;

    /*Enable ch1 in capture mode (input)*/
    TIM3->CCER = CCER_CC1E;

    /*Enable timer*/
    TIM3->CR1 = CR1_CEN;
}
