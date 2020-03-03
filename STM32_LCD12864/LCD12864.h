/************************************************************************************/
/*															LCD12864.h	Ver1.0																	*/
/*					------------------------------------------------------------------			*/
/*				��HAL������������stm32��LCD12864ST7920����																*/
/*				��ֵ��51���ڴ˻���������Щ�Ľ�����ʵ��ͼ�����ֵ���ʾ										*/
/*				ʹ��ʱ�ɸ������ж����ŵ�define																						*/
/*				Ĭ���������Ŷ�ΪPORTA��																										*/
/*				����Ҫ����PORT���ֶ�����LCD12864.c��LcdInit()��ʱ�ӵĳ�ʼ��								*/
/*					------------------------------------------------------------------			*/
/*			�������������������ϰ�����ĺֲܴڣ���Ϊ���ӣ������ٹ��ã����������Ż��ˡ�	*/
/*	CubeMXĬ�ϵ�utf-8����һ�Ȱ��Ҹ����������ı��־��ǽ�������ǧ������ʾ����		*/
/*	Ȼ��ʾ���룬������Notepad++�ѱ����ΪGB2312�ͺ��ˡ��ַ������������ĸĬ�϶���		*/
/*	8λ���룬û����ʾ����ʾ�������д��LcdGBK()��������ĸתΪGBK���롣Ŀǰ����		*/
/*	һЩӢ���ַ�û��ֱ����LcdShowStr()��ʾ���������Ҫ�Ļ����Կ�����дLcdGBK()��		*/
/*																															��������Peattie Zhang		*/
/*																																		2020/02/10		*/
/************************************************************************************/
#ifndef __LCD12864_H
#define __LCD12864_H	 
#include "main.h"

/******************************************/
/*								Functions								*/
/******************************************/
void LcdInit(void);
void LcdShowStr(unsigned char column, unsigned char row, unsigned char *str);
void LcdShowImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *img);
void LcdClearArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void LcdClearAll(void);
uint8_t* LcdGBK(uint8_t* data, uint8_t length);

/******************************************/
/*							Pin Definition						*/
/******************************************/
#ifndef LCD_RS 
#define LCD_RS LCD_RS_Pin
#endif
#ifndef LCD_RW 
#define LCD_RW LCD_RW_Pin
#endif
#ifndef LCD_E
#define LCD_E LCD_E_Pin
#endif
#ifndef LCD_D0
#define LCD_D0 LCD_D0_Pin
#endif
#ifndef LCD_D1
#define LCD_D1 LCD_D1_Pin
#endif
#ifndef LCD_D2
#define LCD_D2 LCD_D2_Pin
#endif
#ifndef LCD_D3
#define LCD_D3 LCD_D3_Pin
#endif
#ifndef LCD_D4
#define LCD_D4 LCD_D4_Pin
#endif
#ifndef LCD_D5
#define LCD_D5 LCD_D5_Pin
#endif
#ifndef LCD_D6
#define LCD_D6 LCD_D6_Pin
#endif
#ifndef LCD_D7
#define LCD_D7 LCD_D7_Pin
#endif
#define LCD_D_7_0 LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3 | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7

/******************************************/
/*					GPIO Port Definition					*/
/******************************************/
#ifndef GPIO_LCD_RS_PORT
#define GPIO_LCD_RS_PORT LCD_RS_GPIO_Port
#endif
#ifndef GPIO_LCD_RW_PORT
#define GPIO_LCD_RW_PORT LCD_RW_GPIO_Port
#endif
#ifndef GPIO_LCD_E_PORT
#define GPIO_LCD_E_PORT LCD_E_GPIO_Port
#endif
#ifndef GPIO_LCD_D_PORT
#define GPIO_LCD_D_PORT LCD_D0_GPIO_Port
#endif

/******************************************/
/*		Letter and Num Definition(GBK)			*/
/******************************************/
#define G(x) G_15_8,G##x
#define G_15_8 0xA3
#define G0 0xB0
#define G1 0xB1
#define G2 0xB2
#define G3 0xB3
#define G4 0xB4
#define G5 0xB5
#define G6 0xB6
#define G7 0xB7
#define G8 0xB8
#define G9 0xB9
#define GA 0XC1
#define GB 0XC2
#define GC 0XC3
#define GD 0XC4
#define GE 0XC5
#define GF 0XC6
#define GG 0XC7
#define GH 0XC8
#define GI 0XC9
#define GJ 0XCA
#define GK 0XCB
#define GL 0XCC
#define GM 0XCD
#define GN 0XCE
#define GO 0XCF
#define GP 0XD0
#define GQ 0XD1
#define GR 0XD2
#define GS 0XD3
#define GT 0XD4
#define GU 0XD5
#define GV 0XD6
#define GW 0XD7
#define GX 0XD8
#define GY 0XD9
#define GZ 0XDA
#define Ga 0XE1
#define Gb 0XE2
#define Gc 0XE3
#define Gd 0XE4
#define Ge 0XE5
#define Gf 0XE6
#define Gg 0XE7
#define Gh 0XE8
#define Gi 0XE9
#define Gj 0XEA
#define Gk 0XEB
#define Gl 0XEC
#define Gm 0XED
#define Gn 0XEE
#define Go 0XEF
#define Gp 0XF0
#define Gq 0XF1
#define Gr 0XF2
#define Gs 0XF3
#define Gt 0XF4
#define Gu 0XF5
#define Gv 0XF6
#define Gw 0XF7
#define Gx 0XF8
#define Gy 0XF9
#define Gz 0XFA


//#ifndef _HE_
extern uint8_t HE[];
extern uint8_t LOGO[];
extern uint8_t QRCODE[];
//#endif
 
#endif
