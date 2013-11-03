/*
 * main.h
 *
 *  Created on: Oct 9, 2010
 *      Author: Mard
 */

#ifndef MAIN_H_
#define MAIN_H_


#ifdef __cplusplus
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "STM32vldiscovery.h"

class Leds {
public:
	Leds();
	virtual ~Leds();
	void Toggle();
	void Off();
	void On();
};

extern "C"
{
#endif




void UbyvaniCasu_Delay(void);

#ifdef __cplusplus
}
#endif


#endif /* MAIN_H_ */
