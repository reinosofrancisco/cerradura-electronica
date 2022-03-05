/*
 * seos.c
 *
 * Created: 08-May-21 4:39:28 PM
 *  Author: fedea
 */ 

#include "seos.h"
#include "timer.h"
#include "MEF.h"

volatile unsigned char Flag_MEF=0;
static unsigned char iCont=0;
static unsigned char iClock=0;

void SEOS_Init(){
	//configuro Timer0 para interrupciones cada 4 ms
	
}

void SEOS_Dispatch_Tasks(){
	
	if(Flag_MEF==1){ //Esto corre cada 100ms
		if(++iClock==10){
			TIMER_Update();
			iClock=0;
		}
		Flag_MEF=0;
		MEF_Update();
	}	
}

void testing_timer(void){ //interrupci?n cada 4ms
	if(++iCont==25){
		Flag_MEF=1;
		iCont=0;
	}
}
