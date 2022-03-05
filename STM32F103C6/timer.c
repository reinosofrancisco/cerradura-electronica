/*
 * timer.c
 *
 * Created: 08-May-21 6:03:43 PM
 *  Author: fedea
 */ 
#include <stm32f103x6.h>
#include "timer.h"

static uint8_t seconds=0;
static uint8_t minutes=0;
static uint8_t hours=0;
static unsigned char hora[8] = "hh:mm:ss";



void TIMER_Init(unsigned char h,unsigned char m,unsigned char s){
	 TIMER_ModificarHora(h);
	 TIMER_ModificarMinutos(m);
	 TIMER_ModificarSegundos(s);
}

void TIMER_Update(){
	seconds++;
	if(seconds==60){
		seconds=0;
		minutes++;
	}
	if(minutes==60){
		minutes=0;
		hours++;
	}
	if(hours==24){	//Si llego a las 24 horas, reinicio el timer 
		hours=0;
		 minutes=0;
		  seconds=0;
	}
}


unsigned char* TIMER_GetHora(){
	hora[7] = '0' + (uint8_t)seconds % 10;
	hora[6] = '0' +(seconds/10);
	hora[5] = ':';
	hora[4] = '0' + (uint8_t)minutes % 10;
	hora[3] = '0' +(minutes/10);;
	hora[2] = ':';
	hora[1] = '0' + (uint8_t)hours %10;
	hora[0] = '0' +(hours/10);
	return hora;
}

//UNSIGNED CHAR siempre son mayores que 0. Es innecesario preguntar
void TIMER_ModificarHora(unsigned char h){
	/*if(h<24 && h>=0){
		hours=h;
	}*/
	 if(h<24) hours=h;
   
}

void TIMER_ModificarMinutos(unsigned char m){
	/*if(m<60 && m>=0){
		minutes=m;
	}*/
	 if(m<60) minutes = m;
	
}
void TIMER_ModificarSegundos(unsigned char s){
	/*if(s<60 && s>=0){
		seconds=s;
	}*/
	 if (s<60) seconds=s;
}
