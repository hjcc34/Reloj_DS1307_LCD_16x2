/* 
 * File:   AHT20_CFG.h
 * Author: Familia CS
 *
 * Created on 23 de noviembre de 2024, 21:11
 */

#ifndef AHT20_CFG_H
#define	AHT20_CFG_H

#include "CFG_16F877A.h"

#define _AHT20_W        0x70
#define _AHT20_R        0x71
#define _AHT20_ini      0xBE
#define _AHT20_act_mes  0xAC

long state,hmsb,hlsb,ht,tmsb,tlsb,crc,ST;

void ini_AHT20 (void);
/*
void Read_AHT20 (void);
*/
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* AHT20_CFG_H */

