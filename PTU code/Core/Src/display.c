#include "display.h"
#include "serial.h"
#include "string.h"
#include "stm32f303xc.h"

int pointcalc(uint32_t distance)
{
	int points = 1000;
	if (distance < 20){
		points = 1000;
	}
	else if (distance >= 20 && distance < 40) {
		points = 2000;
	}
	else if (distance >= 40 && distance < 60) {
		points = 3000;
	}
	else if (distance >= 60 && distance < 80) {
		points = 4000;
	}
	else if (distance >= 80 && distance < 100) {
		points = 5000;
	}
	else if (distance >= 100) {
		points = 1000;
	}
	return points;
}

void outcome(uint32_t length){
	char stringbuffer[100];
	int pointswon = pointcalc(length);
	sprintf(stringbuffer, "Congratulations you made it %d centimeters, Winning %d points!\n", length, pointswon);
	SerialOutputString((uint8_t*)stringbuffer, &USART1_PORT);
}

