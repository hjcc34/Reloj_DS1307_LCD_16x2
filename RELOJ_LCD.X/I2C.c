#include "CFG_I2C.h"

//------------------------------------------------------------------------------
//-------------------------Inicializar I2C--------------------------------------
//------------------------------------------------------------------------------
void I2C_Initialize(void)                                                       //Begin IIC as master
{
  TRISC3 = 1;                                                                   //Set SDA and SCL pins as input pins
  TRISC4 = 1;                                                                   //Set SDA and SCL pins as input pins
  
  SSPCON  = 0x28;                                                               //pg84/234 
  SSPCON2 = 0x00;                                                               //pg85/234
  
  SSPADD = 0x09;
  SSPSTAT = 0x80;                                                               //pg83/234
}
//------------------------------------------------------------------------------
//---------------------------I2C chequeo----------------------------------------
//------------------------------------------------------------------------------
void I2C_Check(void) 
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F))
    {
        Lcd_print_string(6,"I2C",5,"Ocupado");
    }
}
//------------------------------------------------------------------------------
//-----------------------------I2C CFG------------------------------------------
//------------------------------------------------------------------------------
void I2C_Cmd(unsigned char Dir,unsigned char Cfg,unsigned char Cmd)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    __delay_us(5);
    while (SSPCON2bits.SEN == 1)                                                //verifico el start
    {
    }
    I2C_Check();
    SSPBUF = Dir;                                                               //ingreso direccion esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
        Lcd_print_string(1,"Dispositivo I2C",2,"No reconocido");
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = Cfg;                                                               //ingreso configuracion para esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = Cmd;                                                               //ingreso comando para esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
}
//------------------------------------------------------------------------------
//-----------------------------I2C WRITE----------------------------------------
//------------------------------------------------------------------------------
void I2C_Write(unsigned char DirW,unsigned char CmdW,unsigned char DirW2)
{
    I2C_Check();
    SSPCON2bits.SEN = 1;                                                        //Activo el start
    __delay_us(5);
    while (SSPCON2bits.SEN == 1)                                                //verifico el start
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPBUF = DirW;                                                              //ingreso direccion esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
        Lcd_print_string(1,"Dispositivo I2C",2,"No reconocido");        
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = CmdW;                                                              //ingreso comando para esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RSEN = 1;                                                       //reinicio start
    __delay_us(5);
    while (SSPCON2bits.RSEN == 0)                                               //verifico el start
    {
    }
//******************************************************************************    
    I2C_Check();                                                                //verifico el bus
    SSPBUF = DirW2;                                                             //ingreso direccion esclavo
    __delay_us(500);
    while (SSPSTATbits.BF == 1)                                                 //verifico si termino la transmision
    {
    }
    I2C_Check();                                                                //verifico el bus
    while (SSPCON2bits.ACKSTAT == 1)                                            //verifico reconocimiento
    {
    }    
}
//------------------------------------------------------------------------------
//---------------------------I2C READ 8 BITS------------------------------------
//------------------------------------------------------------------------------
void I2C_Read_8bits(void)
{ 
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT = 1;                                                      //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.PEN = 1;                                                        //activo stop
    __delay_us(5);
    while (SSPSTATbits.P == 0)                                                  //verifico si termino el stop
    {
    }
    DATO_I2C_8bits = SSPBUF;
}
//------------------------------------------------------------------------------
//---------------------------I2C READ 16 BITS-----------------------------------
//------------------------------------------------------------------------------
void I2C_Read_16bits(void)
{ 
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT = 0;                                                      //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    DATO_I2C_8bits = SSPBUF;    
//******************************************************************************
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.RCEN = 1;                                                       //configuro maestro como recepcion
    __delay_us(5);
    while (SSPCON2bits.RCEN == 1)                                               //verifico si termino la recepcion
    {
    }
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKDT = 0;                                                      //acknowledge
    __delay_us(5);
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.ACKEN = 1;                                                      //Acknowledge secuencia
    __delay_us(5);
    DATO_I2C_16bits = SSPBUF;    
    I2C_Check();                                                                //verifico el bus
    SSPCON2bits.PEN = 1;                                                        //activo stop
    __delay_us(5);
    while (SSPSTATbits.P == 0)                                                  //verifico si termino el stop
    {
    }

}
//------------------------------------------------------------------------------
//-----------------------------I2C STOP-----------------------------------------
//------------------------------------------------------------------------------
void I2C_P(void)
{
    I2C_Check();
    SSPCON2bits.PEN = 1;                                                        //activo stop
    __delay_us(5);
    while (SSPSTATbits.P == 0)                                                  //verifico si termino el stop
    {
    }
}
//------------------------------------------------------------------------------