#include "Button_Driver.h"

void Button_init(button_t *btn, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	btn ->DDR = ddr;		// 포변일때는 -> 사용
	btn ->PIN = pin;
	btn ->pinNum = pinNum;
	btn ->prevstate = RELEASED;
	*btn ->DDR &= (1 << btn -> pinNum);
}

uint8_t Button_GetState(button_t *btn) //*btn 주소 유효범위 button_t
{
	uint8_t curState = *btn -> PIN & (1<<btn -> pinNum);
	
	if((curState == PUSHED) && (btn->prevstate == RELEASED))
	{
		_delay_ms(10);
		btn->prevstate = PUSHED;
		return ACT_PUSHED;
	}
	else if((curState != PUSHED) && (btn->prevstate == PUSHED))
	{
		_delay_ms(10);
		btn->prevstate = RELEASED;
		return ACT_RELEASED;
		
	}
	return ACT_NONE;
}
