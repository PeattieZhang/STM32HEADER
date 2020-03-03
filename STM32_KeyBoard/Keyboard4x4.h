/************************************************************************************/
/*															Keyboard4x4.h	Ver1.0																*/
/*					------------------------------------------------------------------			*/
/*						���ڶ�4x4������̵Ŀ���																								*/
/*						���������HAL���stm32																								*/
/*						ʹ���жϣ�����������ʱ�Ե�Ƭ����Ӱ��																	*/
/*						���ۿɼ���С��4x4�ļ���																								*/
/*						eg: ��4x3����ʱ����Y4��Pin��Port defineΪY1�ļ���											*/
/*					------------------------------------------------------------------			*/
/*						�ݲ�д��Ķ����������ڲ��е��ң����Ժ�Ҳ��һ����ȥ�ģ��������á�			*/
/*																															��������Peattie Zhang		*/
/*																																		2020/02/11		*/
/************************************************************************************/

#ifndef __KBD44_H
#define __KBD44_H
#include"main.h"

/******************************************/
/*							Pin Definition						*/
/*					Ĭ������Pin����5-9��Χ				*/
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
/*					KBD_GetFlag()�ķ���ֵ					*/
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
#define SYSFreq 8000													//����KBD_Delayms()����λ��kHz
#endif

/******************************************/
/*							Pin Definition						*/
/******************************************/
void KBD_EXTIfunction(uint16_t GPIO_Pin);			//�����ж���
void KBD_Init(void);													//��ʼ��
uint8_t KBD_GetFlag(void);										//�ж��Ƿ��а�������(1Ϊ�У�0Ϊ��)
uint16_t KBD_GetPressedKey(void);							//���а�������ʱ���ذ��µļ�������λ����FLAG

#endif
