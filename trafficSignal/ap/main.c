#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

#define trafficButtonDDR    DDRA
#define trafficButtonPIN    PINA
#define trafficLedDDR       DDRF
#define trafficLedPORT      PORTF
#define B_AUTO              0
#define B_MANUAL            1
#define B_SWITCHING         2

enum {AUTO, MANUAL};
enum {RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};

uint8_t trafficState = RED_GREEN;
uint32_t timeTick = 0;

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

void TrafficSignal_Auto()
{
	static uint32_t prevTime = 0;
	
	switch (trafficState)
	{
		case RED_GREEN:
		redGreen();
		//_delay_ms(3000);
		if (timeTick - prevTime >= 3000)
		{
			prevTime = timeTick;
			trafficState = RED_YELLOW;
		}
		break;
		
		case RED_YELLOW:
		redYellow();
		//_delay_ms(1000);
		if (timeTick - prevTime >= 1000)
		{
			prevTime = timeTick;
			trafficState = GREEN_RED;
		}
		break;
		
		case GREEN_RED:
		greenRed();
		//_delay_ms(3000);
		if (timeTick - prevTime >= 3000)
		{
			prevTime = timeTick;
			trafficState = YELLOW_RED;
		}
		break;
		
		case YELLOW_RED:
		yellowRed();
		//_delay_ms(1000);
		if (timeTick - prevTime >= 1000)
		{
			prevTime = timeTick;
			trafficState = RED_GREEN;
		}
		break;
	}
	_delay_ms(10);
	timeTick += 10;
}

void TrafficSignal_Manual()
{
	switch (trafficState)
	{
		case RED_GREEN:
		redGreen();
		if ((trafficButtonPIN & (1<<B_SWITCHING)) == 0)
			trafficState = RED_YELLOW;
		break;

		case RED_YELLOW:
		redYellow();
		if ((trafficButtonPIN & (1<<B_SWITCHING)) == 0)
			trafficState = GREEN_RED;
		break;

		case GREEN_RED:
		greenRed();
		if ((trafficButtonPIN & (1<<B_SWITCHING)) == 0)
			trafficState = YELLOW_RED;
		break;

		case YELLOW_RED:
		yellowRed();
		if ((trafficButtonPIN & (1<<B_SWITCHING)) == 0)
			trafficState = RED_GREEN;
		break;
	}
}
int main(void)
{
	trafficButtonDDR &= ~((1<<B_AUTO) | (1<<B_MANUAL) | (1<<B_SWITCHING));
	trafficLedDDR |= ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5));

	uint8_t trafficModeState = AUTO;

	while (1)
	{
		if (!(PINA & 0b00000001))
		trafficModeState = AUTO;
		if (!(PINA & 0b00000010))
		trafficModeState = MANUAL;
		
		switch(trafficModeState)
		{
			case (AUTO):
			TrafficSignal_Auto();
			break;
			
			case (MANUAL):
			TrafficSignal_Manual();
			break;
		}
	}
}

//int main(void)
//{
	//TrafficSignal_init();
	//
	//while (1)
	//{
		//traffigSignal_execute();
	//}
//}