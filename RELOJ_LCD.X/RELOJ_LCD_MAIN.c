/*
 * File:   RELOJ_LCD_MAIN.c
 * Author: Familia CS
 *
 * Created on 9 de noviembre de 2024, 21:40
 */


#include <xc.h>
#include "CFG_16F877A.h"
//-----------------------------Interrupcion-------------------------------------
/*
void __interrupt () RX_DATO (void)
{
    if (PIR1bits.RCIF == 1)
    {
    Uart_Read_String(cadena, 20);                                               // Lee la cadena recibida y la almacena
//******************************************************************************    
        if(!strcmp(cadena, "BLE_OK"))                                           // Si la cadena es "BLE_C", ENVIENDE BLE_OK el led
        {
            Uart_Send_String("BLUETOOH CONECTADO\r\n");                         // ENVIA TEXTO A LA APK BLUETOOH CONECTADO
        }
//******************************************************************************    
        if(!strcmp(cadena, "BLE_NOK"))                                          // Si la cadena es "BLE_C", ENVIENDE BLE_OK el led
        {
            Uart_Send_String("BLUETOOH CONECTADO\r\n");                         // ENVIA TEXTO A LA APK BLUETOOH CONECTADO
        }    
//******************************************************************************
        if(!strcmp(cadena, "SALIDA_BLE_1_ON"))                                  // Si la cadena es "SALIDA_BLE_1_ON", enciende el led SALIDA_1
        {
            Uart_Send_String("Salida ON\r\n");                                  // ENVIA TEXTO A LA APK DE SALIDA ON                                                     
        }
//******************************************************************************     
        if(!strcmp(cadena, "SALIDA_BLE_1_OFF"))                                 // Si la cadena es "SALIDA_BLE_1_OFF", apaga el led SALIDA_1
        {
            Uart_Send_String("Salida OFF\r\n");                                 // ENVIA TEXTO A LA APK DE SALIDA OFF
        }
    }    
    PIR1bits.RCIF = 0;
}
*/
//------------------------------------------------------------------------------
//---------------------------Inicio de CFG del micro----------------------------
//------------------------------------------------------------------------------
void main(void) 
{
    TRISA = 0;                                                                  //Puerto A todos salida               
    TRISD = 0;                                                                  //Puerto D todos salidas
    TRISE = 0;                                                                  //Puerto E todos salidas
    TRISC = 0X82;                                                               //PORTC7, PORTC1 y PORTC0 como entradas
    TRISB = 0xFF;                                                               //Todos los pines de puerto B como entradas
    CMCON = 0x07;                                                               //DESACTIVA LOS COMPARADORES
    OPTION_REGbits.nRBPU = 0;                                                   //Activar push pull en puerto B
    PORTA = 0, PORTB = 0, PORTC = 0, PORTD = 0, PORTE = 0;                      //Limpiar todos los puertos
    CMCON = 0x07;                                                               //DESACTIVA LOS COMPARADORES
    ADCON1bits.PCFG3 = 0, ADCON1bits.PCFG2 = 1, ADCON1bits.PCFG1 = 1;           //DESACTIVA Entradas analogicas
//------------------------------------------------------------------------------    
//-----------------------Inicializar LCD 16x2 4bits-----------------------------
//------------------------------------------------------------------------------    
    Lcd_inicio_8bits();                                                               //Inicializar la LCD
//*************************Mensaje de inicio LCD********************************    
    Lcd_print_string(6,"Reloj",5,"Digital");                                    //Mensaje de incio
    __delay_ms(3000);
    Lcd_cmd(_LCD_CLEAR);                                                        //Borrar LCD
//------------------------------------------------------------------------------    
//-------------------------Inicializar RS-232-----------------------------------
//------------------------------------------------------------------------------    
    /*    
    Uart_Init(9600);                                                            //CFG Rs-232
    Uart_Send_String("RS-232 incializado\r\n");                                 //Envio mensaje por UART de periferico configurado
    */
//------------------------------------------------------------------------------    
//-------------------------Inicializar I2C--------------------------------------
//------------------------------------------------------------------------------    
    I2C_Initialize();                                                           //Inicializando I2C
    /*
    Uart_Send_String("I2C incializado\r\n");                                    //Envio mensaje por UART de I2C configurado
    */ 
//------------------------------------------------------------------------------    
//-------------------------Configurar RS1307------------------------------------
//------------------------------------------------------------------------------    
    CFG_DS1307();                                                               //Configura DS1307 a salida de 1seg
//------------------------------------------------------------------------------    
//-------------------------Inicializacion BMP280--------------------------------
//------------------------------------------------------------------------------    
    /*
    ini_bmp280();                                                               //Inicializar BMP280
//------------------------------------------------------------------------------ 
//-------------------------Inicializacion AHT20---------------------------------
//------------------------------------------------------------------------------  
    ini_AHT20();                                                                //Inicializar AHT20
    */    
//------------------------------------------------------------------------------    
//---------------------------Programa de incio----------------------------------
//------------------------------------------------------------------------------    
    while (1)
    {
        READ_DS1307();                                                          //Funcion de lectura del DS1307  
        if (SEL_OK == 0)                                                        //Verifico si se pulso SEL
        {
            __delay_ms(1500);
            X = 6; Lcd_pos_x(X); Lcd_cmd(0x0D);
            AJUSTE_DS1307();                                                    //Funcion de ajuste de DS1307
            Lcd_cmd(_LCD_CLEAR);
        }          
    }
}
