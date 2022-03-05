/*
 * IncFile1.h
 *
 * Created: 7/5/2021 15:31:26
 *  Author: jeron
 */ 


#ifndef MEF_H_
#define MEF_H_
#include <stdint.h>
typedef enum {IDLE, ING_CLAVE, ABIERTO, CLAVE_INC} MEF_state;

//Funciones generales de la MEF
void MEF_Init(uint32_t);
void MEF_Update (void);


#endif
