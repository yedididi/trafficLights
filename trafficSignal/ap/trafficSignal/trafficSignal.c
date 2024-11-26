#include "trafficSignal.h"
#include "../../driver/LED_Driver/LED_Driver.h"

uint8_t trafficState;
uint8_t trafficModeState;
uint32_t timeTick = 0;

button_t autoButton;
button_t manualButton;
button_t nextButton; 

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
		if (Button_GetState(&nextButton) == ACT_RELEASED)
			trafficState = RED_YELLOW;
		break;

		case RED_YELLOW:
		redYellow();
		if (Button_GetState(&nextButton) == ACT_RELEASED)
			trafficState = GREEN_RED;
		break;

		case GREEN_RED:
		greenRed();
		if (Button_GetState(&nextButton) == ACT_RELEASED)
			trafficState = YELLOW_RED;
		break;

		case YELLOW_RED:
		yellowRed();
		if (Button_GetState(&nextButton) == ACT_RELEASED)
			trafficState = RED_GREEN;
		break;
	}
}

void init()
{
	trafficModeState = AUTO;
	trafficState = RED_GREEN;

    Button_init(&autoButton, &BUTTON_DDR, &BUTTON_PIN, 0);
    Button_init(&manualButton, &BUTTON_DDR, &BUTTON_PIN, 1);
    Button_init(&nextButton, &BUTTON_DDR, &BUTTON_PIN, 2);
}

void exec()
{
		if (Button_GetState(&autoButton) == ACT_RELEASED)
			trafficModeState = AUTO;
		if (Button_GetState(&manualButton) == ACT_RELEASED)
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