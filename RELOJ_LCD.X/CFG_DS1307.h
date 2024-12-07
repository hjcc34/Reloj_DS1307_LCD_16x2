/* 
 * File:   CFG_DS1307.h
 * Author: Familia CS
 *
 * Created on 10 de noviembre de 2024, 12:53
 */

#ifndef CFG_DS1307_H
#define	CFG_DS1307_H

#include "CFG_16F877A.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define   _Dir_DS1307_W     0xD0
#define   _Dir_DS1307_R     0xD1
#define   _Salida_1seg      0x90
#define   _Registro_Ctr     0x07
#define   _Registro_Seg     0x00
#define   _Registro_Min     0x01
#define   _Registro_Hor     0x02
#define   _Registro_DiaSe   0x03
#define   _Registro_Dia     0x04
#define   _Registro_Mes     0x05
#define   _Registro_Ano     0x06
#define   _Registro_Stop    0x80
#define   _Registro_Borrar  0x00
#define   _Registro_AM_PM   0x40
    
#define   Hora              6
#define   Minutos           9
#define   Segundos          12
#define   AM_PM             15
#define   Dia               6
#define   Mes               9
#define   Ano               12
#define   Dia_Semana        15
#define   pos_X             1
#define   pos_Y             2
#define   pos_dia_sem       3
#define   Hora_limite_24    23
#define   Hora_limite_12    12
#define   Minutos_limite    59
#define   Segundos_limite   59
#define   Dia_limite        31
#define   Mes_limite        12
#define   Ano_limite        80
#define   Dia_semana_limite 7
#define   AM_PM_limite      2      
    
unsigned char X,Y,dato_ajuste,dato_ajuste_LCD,dato_ajuste_DS1307;    

void CFG_DS1307 (void);
void READ_DS1307 (void);
void AJUSTE_DS1307 (void);
void lectura_tiempo_posX (unsigned char registro_DS1307,unsigned char pos_uni,unsigned char pos_dec,unsigned char pos_D3,unsigned char caracter);
void lectura_tiempo_posY (unsigned char registro_DS1307,unsigned char pos_uni,unsigned char pos_dec,unsigned char pos_D3,unsigned char caracter);
void dia_semana(unsigned char dato_s);
unsigned char mov_cursor (void);
void in_data_DS1307 (unsigned char variable_ajust, unsigned char X_Y,unsigned char pos_X_Y, unsigned char pos_X_Y_n_uni, unsigned char pos_X_Y_n_dec, unsigned char registro_variable, unsigned char limite);

#ifdef	__cplusplus
}
#endif

#endif	/* CFG_DS1307_H */

