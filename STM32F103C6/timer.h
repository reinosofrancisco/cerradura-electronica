#ifndef TIMER_H_
#define TIMER_H_


//Funciones para inicializar el timer
//y actualizar los segundos
void TIMER_Init(unsigned char,unsigned char,unsigned char); //pide horas,minutos y segundos para inicializar
void TIMER_Update(void);

//Funcion para conseguir la hora
//En formato hh:mm:ss
unsigned char* TIMER_GetHora(void);

//Funciones para modificar hora minutos o segundos
//En caso de ingresar valores inv?lidos no se realizar? ning?n cambio
void TIMER_ModificarHora(unsigned char);
void TIMER_ModificarMinutos(unsigned char);
void TIMER_ModificarSegundos(unsigned char);


#endif
