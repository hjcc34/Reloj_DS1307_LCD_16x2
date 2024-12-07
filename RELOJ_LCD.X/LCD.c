#include "CFG_LCD_16x2.h"

//------------------------------------------------------------------------------
//--------------------------INICIALIZACION 8 BITS-------------------------------
//------------------------------------------------------------------------------
void Lcd_inicio_8bits(void)
{
    __delay_ms(70);
    Lcd_cmd(_8bit_1line_58f);
    __delay_ms(4);
    __delay_us(100);
    Lcd_cmd(_8bit_1line_58f);
    __delay_us(100);
    Lcd_cmd(_8bit_1line_58f);
    __delay_us(10);
    Lcd_cmd(_8bit_2lines_58);
    __delay_us(10);
    Lcd_cmd(_dis_OFF_cur_OFF_bl_OFF);
    __delay_us(10);
    Lcd_cmd(_LCD_CLEAR);
    __delay_ms(2);
    Lcd_cmd(_LCD_MODE_SET);
    __delay_us(10);
}
//------------------------------------------------------------------------------
void Lcd_print_string(unsigned char POSx,char *String_x,unsigned char POSy,char *String_y)
{
    unsigned char a;
    a = 0x80 + POSx - 1;
    PORTD = a;
    Lcd_out_cmd();
//******************************************************************************
	int b;
	for(b=0;String_x[b]!='\0';b++)
	   Lcd_Write_Char(String_x[b]);    
//******************************************************************************
    a = 0xC0 + POSy - 1;
    PORTD = a;
    Lcd_out_cmd();
//******************************************************************************
	int c;
	for(c=0;String_y[c]!='\0';c++)
	   Lcd_Write_Char(String_y[c]);     
}
//------------------------------------------------------------------------------
void Lcd_cmd(unsigned char comando)
{
    PORTD = comando;
    Lcd_out_cmd();
}
//------------------------------------------------------------------------------
void Lcd_out_cmd(void)
{
    Dato_RS = 0;
    Dato_E = 1;
    __delay_ms(5);
    Dato_E = 0;
    __delay_ms(5);
}
//------------------------------------------------------------------------------
void Lcd_out_data(void)
{
    Dato_RS = 1;
    Dato_E = 1;
    __delay_ms(5);
    Dato_E = 0;
    __delay_ms(5);
}
//******************************************************************************
void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	Lcd_Write_Char(a[i]);
}
//******************************************************************************
void Lcd_Write_Char(unsigned char a)
{
    PORTD = a;
    Lcd_out_data();
}
//******************************************************************************
void Lcd_pos_x(unsigned char POSx)
{
    unsigned char a;
    a = 0x80 + POSx - 1;
    PORTD = a;
    Lcd_out_cmd();
}    
//******************************************************************************
void Lcd_pos_y(unsigned char POSy)
{
    unsigned char a;    
    a = 0xC0 + POSy - 1;
    PORTD = a;
    Lcd_out_cmd();    
}
//******************************************************************************