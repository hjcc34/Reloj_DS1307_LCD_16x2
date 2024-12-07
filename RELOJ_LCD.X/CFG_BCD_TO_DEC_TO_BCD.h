/* 
 * File:   CFG_BCD_TO_DEC_TO_BCD.h
 * Author: Familia CS
 *
 * Created on 12 de noviembre de 2024, 11:07
 */

#ifndef CFG_BCD_TO_DEC_TO_BCD_H
#define	CFG_BCD_TO_DEC_TO_BCD_H

#include "CFG_16F877A.h"

unsigned char decenas,unidades,DEC_BCD_RESULTADO,decenasH,unidadesH,decenasH10;

int variableU,variableD,variableC,variableM,variableUM,variableDM,unidad,decena,centena,millar,unmillar,dosmillar; 

unsigned char BCD_TO_DEC (unsigned char dato);
void DEC_TO_LCD (unsigned char dato);
unsigned char DEC_TO_HEX (unsigned char dato);
void CONVERSOR_HEX_DEC(int variable); 

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CFG_BCD_TO_DEC_TO_BCD_H */

