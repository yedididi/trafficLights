#include "LED_Driver.h"

void redGreen()
{
	PORTF = ((1<<0) | (1<<4));
}

void redYellow()
{
	PORTF = ((1<<0) | (1<<5));
}

void greenRed()
{
	PORTF = ((1<<1) | (1<<3));
}

void yellowRed()
{
	PORTF = ((1<<2) | (1<<3));
}
