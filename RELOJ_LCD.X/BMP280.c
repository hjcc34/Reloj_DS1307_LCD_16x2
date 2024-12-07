#include "CFG_BMP280.h"
//------------------------------------------------------------------------------
void ini_bmp280 (void)
{
    I2C_Write(_bmp280_w,_bmp280_ID,_bmp280_r);
    I2C_Read_8bits();
    if (DATO_I2C_8bits == 0x58)
    {
        Lcd_print_string(5,"BMP280",3,"Reconocido");
        Uart_Send_String("BMP280 Reconocido\r\n");
        __delay_ms(1500);
        Lcd_cmd(_LCD_CLEAR);
    }
    I2C_Cmd(_bmp280_w,_bmp280_reg_reset,_bmp280_reset);
    I2C_P();
    I2C_Cmd(_bmp280_w,_bmp280_ctrl_mes,0x33);
    I2C_P();
}
//------------------------------------------------------------------------------
/*
void CALIBRATION_BMP280(void)
{
    unsigned char i;
    for (i=88;i<0xA1;i++)
    {
    I2C_Write(0xEE,i,0xEF);
    SSPBUFmsb = DATO_I2C_8bits;
    }
//******************************************************************************    
    I2C_Write(0xEE,0x89,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x88,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_T1 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x8B,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x8A,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_T2 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x8D,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x8C,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_T3 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x8F,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x8E,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P1 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x91,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x90,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P2 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x93,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x92,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P3 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x95,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x94,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P4 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x97,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x96,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P5 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x99,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x98,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P6 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x9B,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x9A,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P7 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x9D,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x9C,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P8 = SSPBUFmsb + SSPBUFlsb;
//******************************************************************************
    I2C_Write(0xEE,0x9F,0xEF);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
    I2C_Write(0xEE,0x9E,0xEF);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits; 
    dig_P9 = SSPBUFmsb + SSPBUFlsb;     
}
*/ 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
void CALCULO_BMP280(void)
{
//******************************************************************************
    I2C_Write(0xEE,0xFA,0xEF);
    __delay_ms(7);
    I2C_Read_8bits();
    SSPBUFmsb = DATO_I2C_8bits;
//******************************************************************************
    I2C_Write(0xEE,0xFB,0xEF);
    __delay_ms(7);
    I2C_Read_8bits();
    SSPBUFlsb = DATO_I2C_8bits;
//******************************************************************************
    I2C_Write(0xEE,0xFC,0xEF);
    __delay_ms(15);
    I2C_Read_8bits();
    SSPBUFxsb = DATO_I2C_8bits;     
//******************************************************************************
    SSPBUFmsb = SSPBUFmsb <<8;
    adc_T = SSPBUFmsb | SSPBUFlsb;
    BMP280_S32_t = SSPBUFlsb + SSPBUFmsb;
//******************************************************************************     
}
*/    
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
void READ_BMP280(void)
{
//----------------------------------Temperatura---------------------------------    
    CONVERSOR_HEX_DEC(T);
    Lcd_pos_y(6);
    Lcd_Write_Char(unidad);
    Lcd_pos_y(5);
    Lcd_Write_Char(decena);
    Lcd_pos_y(4);
    Lcd_Write_Char(centena);
    Lcd_pos_y(3);
    Lcd_Write_Char(millar);
    Lcd_pos_y(2);
    Lcd_Write_Char(unmillar);
    Lcd_pos_y(1);
    Lcd_Write_Char(dosmillar); 
//---------------------------------Humedad--------------------------------------
//---------------------------------Presion ATM----------------------------------    
}
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------