/* Main.c file generated by New Project wizard
 *
 * Created:   Tue Sep 7 2021
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include <stm32f1xx.h>
#include "lcd.h"
#include "utils.h" //Delay timer


 //Cabecera de funci�n privada
 void LCDputValue(uint8_t value);

/*Outputs string to LCD.
Receives the String + the size of the String in Characters*/
void LCDstring(uint8_t* data, uint8_t nBytes)	
{
uint8_t i;
   
	if (!data) return;			//check to make sure we have a good pointer
	 
	for(i=0; i<nBytes; i++){		//Print data in LCD
		LCDsendChar(data[i]);
	}
}

//Inicializacion del LCD en modo 4 bits
//��Setea los pines!!
void LCDinit(){  
   
  LCD_PORT = 0x44333333;    		/* PA0-PA7 as outputs */
  LCD_PIN_OUT &= ~(1<<LCD_EN);  	//LCD_EN=0

  delay_us(3000);              			//Delay de 3ms
  LCDsendCommand(0x33);          		//Send $33 for init
  LCDsendCommand(0x32);          		//Send $32 for init
  LCDsendCommand(0x28);          		//Init LCD 2 line, 5x7 Matrix
  LCDsendCommand(0x0e);          		//Display On, Curson On
  LCDcursorOFF();          		//Clear LCD

  delay_us(2000);              			//Delay de 2ms
  LCDsendCommand(0x06);          		//Shift Cursor Right
}

//Codigo para enviar un comando al LCD
void LCDsendCommand (uint8_t cmd)
{
   LCD_PORT_BRR = (1<<LCD_RS); /* RS = 0 for command */	
   LCDputValue(cmd);
}

//Codigo para enviar un Char al LCD
void LCDsendChar (uint8_t data)
{
   LCD_PORT_BSRR = (1<<LCD_RS); /* RS = 1 for data */
   LCDputValue(data);
}

/* Codigo para enviar valores al LCD.
Funciona en 4 bits. Primero envia la parte superior,
y luego envia la parte inferior del dato.
*/
void LCDputValue(unsigned char value)
{
   LCD_PORT_BRR = 0x0F;                 			/* clear PA0-PA3 */
   LCD_PORT_BSRR = (value>>4)&0x0F;     		/* put high nibble on PA0-PA3 */
   LCD_PIN_OUT |= (1<<LCD_EN);        	 		/* EN = 1 for H-to-L pulse */
   delay_us(1);                       					/* make EN pulse wider. You can use delay_us(2); too */
   LCD_PIN_OUT &= ~ (1<<LCD_EN);       		/* EN = 0 for H-to-L pulse */
   delay_us(1600);                       				/* wait */

   LCD_PORT_BRR = 0x0F;                 			/* clear PA0-PA3 */
   LCD_PORT_BSRR = value&0x0F;          	 	/* put low nibble on PA0-PA3 */
   LCD_PIN_OUT |= (1<<LCD_EN);         			/* EN = 1 for H-to-L pulse */
   delay_us(1);                       					/* make EN pulse wider */
   LCD_PIN_OUT &= ~(1<<LCD_EN);         		/* EN = 0 for H-to-L pulse */
   delay_us(1600);                       				/* wait */
}

//Cursor to X Y position
void LCDGotoXY(uint8_t x, uint8_t y){
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
}
//Clears LCD
void LCDclr(void){
	LCDsendCommand(1<<LCD_CLR);	
}
//Cursor OFF
void LCDcursorOFF(void){
	LCDsendCommand(0x0C);	
}
