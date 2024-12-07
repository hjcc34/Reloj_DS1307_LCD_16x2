#include "AHT20_CFG.h"

//------------------------------------------------------------------------------
//----------------------Inicializacion AHT20------------------------------------
//------------------------------------------------------------------------------
void ini_AHT20(void)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    __delay_us(5);
    while (SSPCON2bits.SEN == 1)                                                //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = 0x70;                                                              //ingreso escritura AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 0)                                            //verifico reconocimiento
    {
        Lcd_print_string(5,"AHT20",3,"Reconocido");
        Uart_Send_String("AHT20 Reconocido\r\n");
        __delay_ms(1500);
        Lcd_cmd(_LCD_CLEAR);
        break;
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0xBE;                                                              //ingreso inicializacion AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0x08;                                                              //ingreso inicializacion AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0x00;                                                              //ingreso inicializacion AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }    
    I2C_P();
}
//------------------------------------------------------------------------------
//----------------------------Medicion del AHT20--------------------------------
//------------------------------------------------------------------------------
/*
void Read_AHT20 (void)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    __delay_us(5);
    while (SSPCON2bits.SEN == 1)                                                //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = 0x70;                                                              //ingreso escritura AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
    __delay_ms(10);
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0xAC;                                                              //ingreso activacion de medicion del AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0x33;                                                              //ingreso comando 0x33
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = 0x00;                                                              //ingreso comando 0x00
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
    I2C_P();
    __delay_ms(80);
//------------------------------------------------------------------------------
//----------------------------Lectura de AHT20----------------------------------    
//------------------------------------------------------------------------------
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    __delay_us(5);
    while (SSPCON2bits.SEN == 1)                                                //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = 0x71;                                                              //ingreso lectura AHT20
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    } 
//***************************Recepcion state************************************
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    state = SSPBUF;
//-----------------------------Recepcion MSB Humedad----------------------------
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    hmsb = SSPBUF;
//-----------------------------Recepcion LSB Humedad----------------------------    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    hlsb = SSPBUF;
//-----------------------Recepcion Humedad y Temperatura------------------------
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    ht = SSPBUF;
//------------------------Recepcion MSB Temperatura-----------------------------    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    tmsb = SSPBUF;
//------------------------Recepcion LSB Temperatura-----------------------------    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =0;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    tlsb = SSPBUF;
//-------------------------------Recepcion CRC----------------------------------
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT =1;                                                       //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    crc = SSPBUF;     
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    I2C_Check();                            //verifico el bus
    SSPCON2bits.PEN = 1;                    //activo stop
    __delay_us(5);
    while (SSPSTATbits.P == 0)              //verifico si termino el stop
    {
    }     
}
*/ 