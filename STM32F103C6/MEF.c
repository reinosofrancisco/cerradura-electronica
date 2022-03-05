/*
 * MEF.c
 *
 * Created: 7/5/2021 15:32:08
 *  Author: jeron
 */
 #include <stm32f103x6.h>
#include "MEF.h"
#include "keypadScan.h"
#include "lcd.h"
#include "timer.h"
#include "utils.h"
#include <stdlib.h>

// Constantes
//static const uint8_t lengthClaveAct=4;

//Variables globales privadas
static  uint8_t state_time = 0;
static MEF_state system_state;
static uint8_t claveAct[4] = {'4','3','2','1'};
static uint8_t key;
static uint8_t claveIng[4];
static uint8_t posClaveIng= 0;
static uint32_t ticksPerSecond; //Se inicializa en el init
static uint8_t actHora = 0; 
static unsigned char* hora; 
//static uint8_t ingresoDig;
static uint8_t teclaPresionada=0;


//Prototipos de funciones privadas 
static uint8_t ClaveCorrecta(void);
static uint8_t Clave_IncTime(void);
static uint8_t AbiertoTime(void);

//Funciones para modelar transiciones de estados
static void changeING_CLAVE(void);
static void ChangeABIERTO(void);
static void ChangeCLAVE_INC(void);
static void ChangeIDLE(void);


//Funciones para modelar cambios de salida de la MEF
static void Out_IngClave(void);
static void OutClaveInc(void);
static void OutAbierto(void);
static void OutIdle(void);
//static void OutMClave(void);


void MEF_Init(uint32_t tps){
	ticksPerSecond=tps;
	system_state=IDLE;
}


void MEF_Update (void)
{
	//Cuento el numero de interrupciones, para calcular el tiempo en cada estado
	state_time++;
	actHora++;
	teclaPresionada= KEYPAD_Scan(&key);
	switch (system_state)
	{
		case IDLE:
			if (teclaPresionada)
			{
				changeING_CLAVE();
				
			}
			else {
					OutIdle();
					//if actualizo hora imprimir HH:MM:SS
				 }
		break;
		case ING_CLAVE:
			if (teclaPresionada && (posClaveIng < 4))
			{
				if(key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '#' && key != '*')
				{
					Out_IngClave();
				}
			}
			if(posClaveIng == 4)
			 {
				if(ClaveCorrecta()) ChangeABIERTO();
				else ChangeCLAVE_INC();
			 }
		break;
		case CLAVE_INC:
			if(state_time == 1)
			{
				OutClaveInc();
			}
			else if(Clave_IncTime())
				{
					ChangeIDLE();
				}
		break;
		case ABIERTO:
			if(state_time == 1)
			{
				OutAbierto();
			}
			else if (AbiertoTime())
			{
				ChangeIDLE();
			}
		break;
		}
}


	/***************************************************************
		Funcion que sirve mostrar la salida del estado IDLE, en este
		caso se muestra la hora y el mensaje CERRADO
	***************************************************************/

	static void OutIdle(void)
	{
		if(state_time==1)
		{
			LCDclr();
			LCDGotoXY(4,0);
			hora = TIMER_GetHora();
			LCDstring(hora, 8);
			LCDGotoXY(4,1);
			LCDstring((uint8_t*)"CERRADO",(uint8_t) 7);
		}
		if (actHora == ticksPerSecond)
		{
			hora = TIMER_GetHora();
			LCDGotoXY(4,0);
			LCDstring(hora, 8);
			actHora=0;
		}		
	}
	/***************************************************************
		Funcion que sirve para transicionar del estado IDLE, al 
		estado ING_CLAVE, guarda el caracter ingresado por el usuario,
		cambia el estado actual e imprimer el * en el LCD
	***************************************************************/
	
	static void changeING_CLAVE (void)
	{
		state_time=0;
		system_state= ING_CLAVE;
		claveIng[posClaveIng]= key;
		posClaveIng++;
		LCDclr();
		LCDGotoXY(6,1);
		LCDsendChar('*');
	}
	
	/***************************************************************
		Funcion que sirve para guardar el dato ingresado por el usuario
		y mostrar el * en el LCD de salida del sistema
	***************************************************************/
	
	static void Out_IngClave (void)
	{
		claveIng[posClaveIng]= key;
		LCDsendChar('*');
		posClaveIng++;
	}
	
	
	/***************************************************************
		Funcion que sirve para que sirve para comparar la clave
		ingresada por el usuario con la contrase?a actual del 
		sistema
	***************************************************************/
	
	static uint8_t ClaveCorrecta(void)
	{
			uint8_t  i=0;
			for(i=0; i<4; i++)
			{
				if (claveIng[i] != claveAct[i]) return 0;
			}
			return 1;
	}
	
	static void ChangeABIERTO(void)
	{
		state_time=0;
		system_state= ABIERTO;
	}
	
	static void ChangeCLAVE_INC(void)
	{
		state_time=0;
		system_state= CLAVE_INC;
	}
	
	/***************************************************************
	Funcion que sirve para mostrar la salida de la MEF al estado
	CLAVE_INC, el mismo consiste en mostrar en el segundo renglon del
	LCD "DENEGADO" por 2 segundos
	***************************************************************/

	static void OutClaveInc(void)
	{
		LCDclr();
		LCDGotoXY(4,1);
		LCDstring((uint8_t*)"DENEGADO", 8);
	}
	
	/***************************************************************
	Funcion que determina si se cumplio el tiempo en el estado 
	CLAVE_INC, en este caso chequea si el tiempo en dicho estado (en
	ticks), es igual al tiempo tambien en ticks (por eso se multiplica
	 el valor 2 correspondiente a los seg que se debe esta en dicho 
	 estado por la cantidad de ticks por segundo) que se debe estar 
	 en dicho estado
	***************************************************************/
	
	static uint8_t Clave_IncTime(void)
	{
		if(state_time < 2*ticksPerSecond) return 0;
		else return 1;
	}
	
	static void ChangeIDLE(void)
	{
		state_time=0;
		posClaveIng=0;
		actHora=0;
		system_state= IDLE;
		LCDcursorOFF();
	}
	

	/***************************************************************
		Funcion que sirve mostrar la salida del estado ABIERTO, en este
		caso se muestra el mensaje ABIERTO
	***************************************************************/
	
	static void OutAbierto(void)
	{
		LCDclr();
		LCDGotoXY(4,1);
		LCDstring((uint8_t*)"ABIERTO",(uint8_t) 7);
	}
	
	/***************************************************************
	Funcion que determina si se cumplio el tiempo en el estado 
	ABIERTO, en este caso chequea si el tiempo en dicho estado (en
	ticks), es igual al tiempo tambien en ticks (por eso se multiplica
	 el valor 3 correspondiente a los seg que se debe esta en dicho 
	 estado por la cantidad de ticks por segundo) que se debe estar 
	 en dicho estado
	***************************************************************/
	
	static uint8_t AbiertoTime(void)
	{
		if(state_time < 3*ticksPerSecond) return 0;
		else return 1;
}
