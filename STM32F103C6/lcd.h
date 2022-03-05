
#ifndef LCD_H
#define LCD_H

#include <stm32f1xx.h>
#include "keypadScan.h"	//pal delay_us por ahora


#define LCD_CLR 0	//DB0: clear display‘Display ON, Cursor OFF’ (para dejar prendido el LCD pero apagar el cursor)‘Display ON, Cursor OFF’ (para dejar prendido el LCD pero apagar el cursor)‘Display ON, Cursor OFF’ (para dejar prendido el LCD pero apagar el cursor)‘Display ON, Cursor OFF’ (para dejar prendido el LCD pero apagar el cursor)

//PARA CAMBIAR EL PUERTO CAMBIAR GPIOx DONDE x CORRESPONDE AL PUERTO
#define LCD_PORT 		GPIOA->CRL
#define LCD_PIN_IN 		GPIOA->IDR			//Input Data Register
#define LCD_PIN_OUT 		GPIOA->ODR			//Output Data Register

//Since BRR and BSRR are opposite of each other, 
//you can use both if you don't want to do the bit shift left operation
#define LCD_PORT_BSRR	GPIOA->BSRR
#define LCD_PORT_BRR	GPIOA->BRR 

#define LCD_RS 4
#define LCD_RW 6
#define LCD_EN 5

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR 0x00
#define LCD_LINE1_DDRAMADDR 0x40
#define LCD_LINE2_DDRAMADDR 0x14
#define LCD_LINE3_DDRAMADDR 0x54
#define LCD_DDRAM 7	
//DB7: set DD RAM address -> 1<<LCD_DDRAM => 0x80


/*CABECERAS*/
uint8_t string_len(char* data);
void LCDinit(void);			//Initializes LCD
void LCDsendChar(uint8_t);		//forms data ready to send to 74HC164
void LCDsendCommand(uint8_t);	//forms data ready to send to 74HC164
//void lcd_putValue (uint8_t value); la moví porque es privada
void LCDstring(uint8_t*, uint8_t);	//Outputs string to LCD

//Necesarias para la MEF
void LCDGotoXY(uint8_t, uint8_t);	//Cursor to X Y position
void LCDclr(void);				//Clears LCD
void LCDcursorOFF(void);		//Cursor OFF

/*
//En un futuro tal vez
void LCDhome(void);			//LCD cursor home
void LCDescribeDato(int val,unsigned int field_length); // Agrego Funcion para escribir Enteros
void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM 
void LCDshiftRight(uint8_t);	//shift by n characters Right
void LCDshiftLeft(uint8_t);	//shift by n characters Left
void LCDcursorOn(void);		//Underline cursor ON
void LCDcursorOnBlink(void);	//Underline blinking cursor ON
void LCDblank(void);			//LCD blank but not cleared
void LCDvisible(void);			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n
*/

#endif

