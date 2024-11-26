#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

void redGreen();
void redYellow();
void greenRed();
void yellowRed();

#endif