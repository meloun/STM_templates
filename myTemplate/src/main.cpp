/*
* SysTick main.c
* Blikani LED pomoc� SysTick
* http://mcu.cz
* Mard 2010/10/09 ver. 1.0
*/

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stm32f10x.h"
#include "STM32vldiscovery.h"
#include "main.h"
#include <stdint.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Count;
static __IO uint32_t CasProDelay;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Inicializace(void);
void Delay(__IO uint32_t nCount);
void UbyvaniCasu_Delay(void);

/* Private functions ---------------------------------------------------------*/

Leds::Leds() {
	STM32vldiscovery_LEDInit(LED3);
	STM32vldiscovery_LEDInit(LED4);
	On();
}
Leds::~Leds() {}
void Leds::Toggle() {
	STM32vldiscovery_LEDToggle(LED3);
	STM32vldiscovery_LEDToggle(LED4);
}
void Leds::Off() {
	STM32vldiscovery_LEDOff(LED3);
	STM32vldiscovery_LEDOff(LED4);
}
void Leds::On() {
	STM32vldiscovery_LEDOn(LED3);
	STM32vldiscovery_LEDOn(LED4);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
  GPIO_Inicializace();
  Leds leds;

  /* System Clocks Configuration **********************************************/

  /* Nastaveni casovace SysTick na 1 msec preruseni  */
  if (SysTick_Config(SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }

  while (1)
    {
      // kontrola stisku USER tlacitka
      if(0 != STM32vldiscovery_PBGetState(BUTTON_USER))
	  {
	    // tj. kdy� je stisknuto tlacitko
        Count = 300;   // delsi cas
	  }
	  else
	  {
	    // tj. kdy� nen� stisknuto tlacitko
        Count = 100;   // kratsi cas
      }

      //STM32vldiscovery_LEDOn(LED3); // rozsvitime LED3 - zelena
      leds.On();
      Delay(Count);

      //STM32vldiscovery_LEDOff(LED3); // zhasnem LED3 - zelena
      leds.Off();
      Delay(Count);
    }
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval : None
  */
void GPIO_Inicializace(void)
{
  STM32vldiscovery_LEDInit(LED3);
  STM32vldiscovery_LEDInit(LED4);
  STM32vldiscovery_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  STM32vldiscovery_LEDOff(LED3);
  STM32vldiscovery_LEDOff(LED4);
}

/**
  * @brief  Inserts a delay time.
  * @param nTime: specifies the delay time length, in milliseconds.
  * @retval : None
  */
void Delay(__IO uint32_t nTick)
{
  CasProDelay = nTick;

  while(CasProDelay != 0);  // cas se snizuje pomoci preruseni
}

/**
  * @brief  Snizovani hodnoty citace pri preruseni.
  * @param  None
  * @retval : None
  */
void UbyvaniCasu_Delay(void)
{
  if (CasProDelay != 0x00)
  {
    CasProDelay--;
  }
}


