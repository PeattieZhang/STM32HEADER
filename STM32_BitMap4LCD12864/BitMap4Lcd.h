/************************************************************************************/
/*															BitMap4Lcd.h	Ver1.0																*/
/*					------------------------------------------------------------------			*/
/*				用于在c语言环境下制作位图，位图可通过LCD屏显示														*/
/*				适用于由ST7920驱动的LCD12864，对其它显示屏的兼容性未知										*/
/*				默认位图宽高为128*64，可改变BM_WIDTH和BM_HEIGHT两个变量改变								*/
/*					------------------------------------------------------------------			*/
/*						这个代码只是用来做电赛练习的，草草花了几分钟写的，能实现的功能有限，	*/
/*				如果后续有需要的话会继续迭代的。																					*/
/*																															————Peattie Zhang		*/
/*																																		2020/02/10		*/
/************************************************************************************/
#ifndef __BitMap_H
#define __BitMap_H
#include"main.h"

#define BM_WIDTH 128														//位图宽度
#define BM_HEIGHT 64														//位图高度
#define BM_ARRAY_LENGTH BM_WIDTH*BM_HEIGHT/8

extern uint8_t BM_BITMAP[BM_ARRAY_LENGTH];			//位图

void BM_ClearAll(void);													//清空位图
void BM_SetPoint(uint8_t x, uint8_t y);					//将指定点设为1
void BM_ClearPoint(uint8_t x, uint8_t y);				//将指定点设为0
void BM_Sine(																		//画sin！
					uint8_t X, 						//左上角坐标
					uint8_t Y, 						//左上角坐标
					uint8_t Width, 				//纵轴长度
					uint8_t Height, 			//横轴长度
					uint8_t Period_Num		//重复周期数
);

#endif
