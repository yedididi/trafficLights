#ifndef TRAFFICSIGNAL_H_
#define TRAFFICSIGNAL_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define trafficButtonDDR    DDRA
#define trafficButtonPIN    PINA
#define trafficLedDDR       DDRF
#define trafficLedPORT      PORTF
#define B_AUTO              0
#define B_MANUAL            1
#define B_SWITCHING         2

#include "../../driver/Button_Driver/Button_Driver.h"

enum {AUTO, MANUAL};
enum {RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED};

void TrafficSignal_Auto();
void TrafficSignal_Manual();

// 전역 변수 외부 선언
extern uint8_t trafficState;   // trafficState 변수 외부 선언
extern uint32_t timeTick;      // timeTick 변수 외부 선언

#endif /* TRAFFICSIGNAL_H_ */