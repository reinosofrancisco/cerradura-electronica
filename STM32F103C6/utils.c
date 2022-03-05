
#include "utils.h"
#ifndef F_CPU
#define F_CPU 72000000UL
#endif

#define CONST_FOR_US_DELAY 12
#define CONST_FOR_MS_DELAY 11998

static unsigned long ms_delay_const = CONST_FOR_MS_DELAY * (72000000UL / F_CPU); 

void delay_us(unsigned long amount){
	unsigned long i,l;
	for(i=0;i<amount;i++)
		for(l=0;l<CONST_FOR_US_DELAY;l++);
}

void delay_ms(unsigned long amount){
	unsigned long i,l;
	for(i=0;i<amount;i++)
		for(l=0;l<ms_delay_const;l++);
}
 
 //end
