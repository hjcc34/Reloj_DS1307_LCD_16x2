/* 
 * File:   CFG_RS-232.h
 * Author: Familia CS
 *
 * Created on 23 de noviembre de 2024, 23:01
 */

#ifndef CFG_RS_232_H
#define	CFG_RS_232_H

#include "CFG_16F877A.h"

#define SALTOL      0x0A
#define RETORNOC    0x0D
#define CNULL       0x00


char cadena[20];

//------------------------------------------------------------------------------
void Uart_Init(int baudios);
void Uart_Send_Char(char INFO_CHAR);
void Uart_Send_String(char *INFO);
char Uart_Read(void);
void Uart_Read_String(char* Buf, unsigned int s_buf);
/*
void Uart_Read_Substring(char* cp, char* vc, int inc, int fn);
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size);
*/ 


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CFG_RS_232_H */

