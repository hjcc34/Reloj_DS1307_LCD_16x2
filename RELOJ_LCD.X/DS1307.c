#include "CFG_DS1307.h"
#include "CFG_BCD_TO_DEC_TO_BCD.h"

//******************************************************************************
//****************************CFG DS1307 1seg***********************************
//******************************************************************************
void CFG_DS1307()
{
    I2C_Cmd(_Dir_DS1307_W,_Registro_Ctr,_Salida_1seg);                          //Configurar salida de 1seg el DS1307
    I2C_P();                                                                    //Stop de I2C
    /*
    Uart_Send_String("DS1307 Reconocido\r\n");
    */  
}
//******************************************************************************
//************************LECTURA DE TIEMPO Posicion X**************************
//******************************************************************************
void lectura_tiempo_posX(unsigned char registro_DS1307,unsigned char pos_uni,unsigned char pos_dec,unsigned char pos_D3,unsigned char caracter)
{
        I2C_Write(_Dir_DS1307_W,registro_DS1307,_Dir_DS1307_R);
        I2C_Read_8bits();
        BCD_TO_DEC(DATO_I2C_8bits);
        Lcd_pos_x(pos_uni); Lcd_Write_Char(unidades);
        Lcd_pos_x(pos_dec); Lcd_Write_Char(decenas);
        Lcd_pos_x(pos_D3);  Lcd_Write_Char(caracter);    
}      
//******************************************************************************
//************************LECTURA DE TIEMPO Posicion Y**************************
//******************************************************************************
void lectura_tiempo_posY(unsigned char registro_DS1307,unsigned char pos_uni,unsigned char pos_dec,unsigned char pos_D3,unsigned char caracter)
{
        I2C_Write(_Dir_DS1307_W,registro_DS1307,_Dir_DS1307_R);
        I2C_Read_8bits();
        BCD_TO_DEC(DATO_I2C_8bits);
        Lcd_pos_y(pos_uni); Lcd_Write_Char(unidades);
        Lcd_pos_y(pos_dec); Lcd_Write_Char(decenas);
        Lcd_pos_y(pos_D3);  Lcd_Write_Char(caracter);    
}
//******************************************************************************
//**************************LECTURA DE DS1307***********************************
//******************************************************************************
void READ_DS1307 (void)
{
    lectura_tiempo_posX(_Registro_Seg,12,11,10,':');
    lectura_tiempo_posX(_Registro_Min,9,8,7,':');
    lectura_tiempo_posX(_Registro_Hor,6,5,4,' ');
    lectura_tiempo_posY(_Registro_Ano,12,11,10,'-');
    lectura_tiempo_posY(_Registro_Mes,9,8,7,'-');
    lectura_tiempo_posY(_Registro_Dia,6,5,4,' ');
    I2C_Write(_Dir_DS1307_W,_Registro_DiaSe,_Dir_DS1307_R);
    I2C_Read_8bits();
    dia_semana(DATO_I2C_8bits);        
}
//******************************************************************************
//**************************Ajuste de reloj*************************************
//*************************MENU PRINCIPAL***************************************
void AJUSTE_DS1307(void)
{
    while (1)
    {
        mov_cursor();
        in_data_DS1307(Hora,X,pos_X,6,5,_Registro_Hor,24);
        in_data_DS1307(Minutos,X,pos_X,9,8,_Registro_Min,59);
        in_data_DS1307(Segundos,X,pos_X,12,11,_Registro_Seg,59);
        in_data_DS1307(Dia,Y,pos_Y,6,5,_Registro_Dia,31);
        in_data_DS1307(Mes,Y,pos_Y,9,8,_Registro_Mes,12);
        in_data_DS1307(Ano,Y,pos_Y,12,11,_Registro_Ano,80);
        in_data_DS1307(Dia_Semana,Y,pos_dia_sem,16,15,_Registro_DiaSe,7); 
        if (SEL_OK == 0)
        {
            break;
        }
    }    
} 
//------------------------------------------------------------------------------
//----------------------------Dia semana----------------------------------------
//------------------------------------------------------------------------------
void dia_semana(unsigned char dato_s)
{
    switch(dato_s)
    {
        case 1:
        Lcd_pos_y(15); Lcd_Write_String("Do");        
        break;
        case 2:
        Lcd_pos_y(15); Lcd_Write_String("Lu");        
        break;
        case 3:
        Lcd_pos_y(15); Lcd_Write_String("Ma");       
        break;
        case 4:
        Lcd_pos_y(15); Lcd_Write_String("Mi");        
        break;
        case 5:
        Lcd_pos_y(15); Lcd_Write_String("Ju");        
        break;
        case 6:
        Lcd_pos_y(15); Lcd_Write_String("Vi");
        break;
        case 7:
        Lcd_pos_y(15); Lcd_Write_String("Sa");
        break;
        default: break;
    }
}
//------------------------------------------------------------------------------
//----------------------MOVIMIENTO DE CURSOR------------------------------------
//------------------------------------------------------------------------------
unsigned char mov_cursor(void)
{
//***********************Incremento cursor en Y*********************************    
    if (NEXT_3 == 0 && Y >= 6 && Y <= 17)
    {
        __delay_ms(500); Y += 3; Lcd_pos_y(Y); Lcd_cmd(0x0D);
        if (Y > 17)                                                             //Si Y es mayor a 17
        {
            X = 6; Lcd_pos_x(X); Lcd_cmd(0x0D); __delay_ms(500);                //X es igual a 6
        }
    }
//***********************Incremento cursor en X*********************************    
    if (NEXT_3 == 0 && X >= 6 && X <= 17)
    {
        __delay_ms(500); X += 3; Lcd_pos_x(X); Lcd_cmd(0x0D);
        if (X > 17)                                                             //Si X es mayor a 17
        {
            Y = 6; Lcd_pos_y(Y); Lcd_cmd(0x0D); __delay_ms(500);                //Y es igual a 6
        }            
    }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------    
//***********************Decremento cursor en Y*********************************       
    if (BEFORE_4 == 0 && Y >= 6 && Y <= 17)
    {
        __delay_ms(500); Y -= 3; Lcd_pos_y(Y); Lcd_cmd(0x0D);
        if (Y < 6)                                                              //Si Y es menor a 6
        {
            X = 15; Lcd_pos_x(X); Lcd_cmd(0x0D); __delay_ms(500);                //Y es igual a 6            
        }
    }  
//***********************Decremento cursor en X*********************************
    if (BEFORE_4 == 0 && X >= 6 && X <= 17)
    {
        __delay_ms(500); X -= 3; Lcd_pos_x(X); Lcd_cmd(0x0D);
        if (X < 6)                                                              //Si X es menor a 6
        {
            Y = 15; Lcd_pos_y(Y); Lcd_cmd(0x0D); __delay_ms(500);               //Y es igual a 15
        }            
    }
    return X,Y;
}
//------------------------------------------------------------------------------
//---------------------------Funcion ajuste de reloj----------------------------
//------------------------------------------------------------------------------
void in_data_DS1307 (unsigned char variable_ajust, unsigned char X_Y, unsigned char pos_X_Y, unsigned char pos_X_Y_n_uni, unsigned char pos_X_Y_n_dec, unsigned char registro_variable, unsigned char limite)
{
    if ( variable_ajust == X_Y)
    {
        if (INC_1 == 0)
        {
            __delay_ms(500); dato_ajuste += 1;
            if (limite == dato_ajuste)
            {
                dato_ajuste = 0;
            }
            dato_ajuste_LCD = dato_ajuste; DEC_TO_LCD(dato_ajuste_LCD);
            if (pos_X_Y == 1)
            {
                Lcd_pos_x(pos_X_Y_n_uni); Lcd_Write_Char(unidades);
                Lcd_pos_x(pos_X_Y_n_dec); Lcd_Write_Char(decenas);
            }
            if (pos_X_Y == 2)
            {
                Lcd_pos_y(pos_X_Y_n_uni); Lcd_Write_Char(unidades);
                Lcd_pos_y(pos_X_Y_n_dec); Lcd_Write_Char(decenas);
            }
            if (pos_X_Y == 3)
            {
                dia_semana(dato_ajuste);
            }
            dato_ajuste_DS1307 = dato_ajuste; DEC_TO_HEX(dato_ajuste_DS1307);
            I2C_Cmd(_Dir_DS1307_W,registro_variable,DEC_BCD_RESULTADO);
            I2C_P();            
        }
//******************************************************************************        
        if (DEC_2 == 0)
        {
            __delay_ms(500); dato_ajuste -= 1;
            if (dato_ajuste <1)
            {
                dato_ajuste = limite;
            }
            dato_ajuste_LCD = dato_ajuste; DEC_TO_LCD(dato_ajuste_LCD);
            if (pos_X_Y == 1)
            {
                Lcd_pos_x(pos_X_Y_n_uni); Lcd_Write_Char(unidades);
                Lcd_pos_x(pos_X_Y_n_dec); Lcd_Write_Char(decenas);
            }
            if (pos_X_Y == 2)
            {
                Lcd_pos_y(pos_X_Y_n_uni); Lcd_Write_Char(unidades);
                Lcd_pos_y(pos_X_Y_n_dec); Lcd_Write_Char(decenas);
            }
            if (pos_X_Y == 3)
            {
                dia_semana(dato_ajuste);
            }
            dato_ajuste_DS1307 = dato_ajuste; DEC_TO_HEX(dato_ajuste_DS1307);
            I2C_Cmd(_Dir_DS1307_W,registro_variable,DEC_BCD_RESULTADO);
            I2C_P();            
        }        
    }
}