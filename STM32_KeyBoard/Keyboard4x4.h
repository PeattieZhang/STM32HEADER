/************************************************************************************/
/*															Keyboard4x4.h	Ver1.0																*/
/*					------------------------------------------------------------------			*/
/*						用于对4x4矩阵键盘的控制																								*/
/*						适用与基于HAL库的stm32																								*/
/*						使用中断，按键不按下时对单片机无影响																	*/
/*						理论可兼容小于4x4的键盘																								*/
/*						eg: 做4x3键盘时，将Y4的Pin和Port define为Y1的即可											*/
/*					------------------------------------------------------------------			*/
/*						草草写完的东西，函数内部有点乱，但以后也不一定会去改，至少能用。			*/
/*																															————Peattie Zhang		*/
/*																																		2020/02/11		*/
/************************************************************************************/

#ifndef __KBD44_H
#define __KBD44_H
#include"main.h"

/******************************************/
/*							Pin Definition						*/
/*					默认所有Pin都在5-9范围				*/
/******************************************/
#ifndef X1_Pin
#define X1_Pin
#endif
#ifndef X2_Pin
#define X2_Pin
#endif
#ifndef X3_Pin
#define X3_Pin
#endif
#ifndef X4_Pin
#define X4_Pin
#endif
#ifndef Y1_Pin
#define Y1_Pin
#endif
#ifndef Y2_Pin
#define Y2_Pin
#endif
#ifndef Y3_Pin
#define Y3_Pin
#endif
#ifndef Y4_Pin
#define Y4_Pin
#endif
#define  PortY_EXTI EXTI9_5_IRQn

/******************************************/
/*					GPIO Port Definition					*/
/******************************************/
#ifndef X1_GPIO_Port
#define X1_GPIO_Port
#endif
#ifndef X2_GPIO_Port
#define X2_GPIO_Port
#endif
#ifndef X3_GPIO_Port
#define X3_GPIO_Port
#endif
#ifndef X4_GPIO_Port
#define X4_GPIO_Port
#endif
#ifndef Y1_GPIO_Port
#define Y1_GPIO_Port
#endif
#ifndef Y2_GPIO_Port
#define Y2_GPIO_Port
#endif
#ifndef Y3_GPIO_Port
#define Y3_GPIO_Port
#endif
#ifndef Y4_GPIO_Port
#define Y4_GPIO_Port
#endif

/******************************************/
/*							Key Definition						*/
/*					KBD_GetFlag()的返回值					*/
/******************************************/
#define KBD_1				0x0001
#define KBD_2				0x0002
#define KBD_3				0x0004
#define KBD_A				0x0008
#define KBD_4				0x0010
#define KBD_5				0x0020
#define KBD_6				0x0040
#define KBD_B				0x0080
#define KBD_7				0x0100
#define KBD_8				0x0200
#define KBD_9				0x0400
#define KBD_C				0x0800
#define KBD_STAR		0x1000
#define KBD_0				0x2000
#define KBD_NUMSIGN	0x4000
#define KBD_D				0x8000

/******************************************/
/*						Other Definition						*/
/******************************************/
#ifndef SYSFreq
#define SYSFreq 8000													//用于KBD_Delayms()，单位：kHz
#endif

/******************************************/
/*							Pin Definition						*/
/******************************************/
void KBD_EXTIfunction(uint16_t GPIO_Pin);			//置于中断里
void KBD_Init(void);													//初始化
uint8_t KBD_GetFlag(void);										//判断是否有按键按下(1为有，0为无)
uint16_t KBD_GetPressedKey(void);							//在有按键按下时返回按下的键，并复位按键FLAG

#endif
