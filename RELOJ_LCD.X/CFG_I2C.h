/* 
 * File:   CFG_I2C.h
 * Author: Familia CS
 *
 * Created on 10 de noviembre de 2024, 0:14
 */

#ifndef CFG_I2C_H
#define	CFG_I2C_H

#include "CFG_16F877A.h"

unsigned char DATO_I2C_8bits,DATO_I2C_16bits;

void I2C_Check(void);                                                           
void I2C_Write(unsigned char DirW,unsigned char CmdW,unsigned char DirW2);
void I2C_Read_8bits(void);
void I2C_Read_16bits(void);
void I2C_Cmd(unsigned char Dir,unsigned char Cfg,unsigned char Cmd);
void I2C_P(void);
void I2C_Initialize(void);

#endif	/* CFG_I2C_H */

