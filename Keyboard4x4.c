#include "Keyboard4x4.h"

uint8_t PinX;																																//按键X坐标
uint8_t PinY;																																//按键Y坐标
uint8_t PressFlag = 0;																											//按键是否按下FLAG

void KBD_Delayms(uint8_t us);																								//内部用延时
void KBD_Status_1(void);																										//键盘引脚设置状态1，按键未按下时的状态，按键按下后可获得Y坐标
void KBD_Status_2(void);																										//键盘引脚设置状态2，按键按下后的状态，可获得X坐标

void KBD_EXTIfunction(uint16_t GPIO_Pin){
	GPIO_PinState PinTMP[12];
	GPIO_TypeDef* GPIO_PORT_TMP;
	uint8_t PinY_TMP;																													//暂存Y坐标

	if(PressFlag) return;																											//上一个按下的按键还没被读取时直接跳出
	
	switch(GPIO_Pin){
		case Y1_Pin:
			GPIO_PORT_TMP = Y1_GPIO_Port;
			PinY_TMP = 0;
			break;
		case Y2_Pin:
			GPIO_PORT_TMP = Y2_GPIO_Port;
			PinY_TMP = 1;
			break;
		case Y3_Pin:
			GPIO_PORT_TMP = Y3_GPIO_Port;
			PinY_TMP = 2;
			break;
		case Y4_Pin:
			GPIO_PORT_TMP = Y4_GPIO_Port;
			PinY_TMP = 3;
			break;
	}
	
	for(uint8_t i = 0; i < 3; i++){																						//Y坐标：每1ms读取一次引脚，去抖动用
		KBD_Delayms(1);
		PinTMP[i] = HAL_GPIO_ReadPin(GPIO_PORT_TMP, GPIO_Pin);
	}
	
	if(	PinTMP[0] == GPIO_PIN_RESET && 																				//Y坐标：抖动判定，非抖动则进行X坐标判定
			PinTMP[1] == GPIO_PIN_RESET && 
			PinTMP[2] == GPIO_PIN_RESET){
		KBD_Status_2();																													//进入引脚设置状态2
		for(uint8_t i = 0; i < 3; i++){																					//X坐标：每1ms读取一次引脚，去抖动用
			KBD_Delayms(1);
			PinTMP[4*i] = HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin);
			PinTMP[4*i+1] = HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin);
			PinTMP[4*i+2] = HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin);
			PinTMP[4*i+3] = HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin);
		}
		for(uint8_t i = 0; i<4; i++){
			if(	PinTMP[i] == GPIO_PIN_RESET && 																		//X坐标：抖动判定，非抖动则按键被按下
					PinTMP[i+4] == GPIO_PIN_RESET && 
					PinTMP[i+8] == GPIO_PIN_RESET){
				PinX = i;
				PinY = PinY_TMP;
				PressFlag = 1;
				break;
			}
		}		
		KBD_Status_1();																													//回到引脚设置状态1
	}
}

void KBD_Init(void){
  __HAL_RCC_GPIOA_CLK_ENABLE();
	
	PressFlag = 0;
	KBD_Status_1();	
}

void KBD_Status_1(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* 引脚反初始化 */
	HAL_GPIO_DeInit(X1_GPIO_Port, X1_Pin);
	HAL_GPIO_DeInit(X2_GPIO_Port, X2_Pin);
	HAL_GPIO_DeInit(X3_GPIO_Port, X3_Pin);
	HAL_GPIO_DeInit(X4_GPIO_Port, X4_Pin);
	HAL_GPIO_DeInit(Y1_GPIO_Port, Y1_Pin);
	HAL_GPIO_DeInit(Y2_GPIO_Port, Y2_Pin);
	HAL_GPIO_DeInit(Y3_GPIO_Port, Y3_Pin);
	HAL_GPIO_DeInit(Y4_GPIO_Port, Y4_Pin);
	
	/* X引脚初始化(高速输出低) */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
  GPIO_InitStruct.Pin = X1_Pin;
  HAL_GPIO_Init(X1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X2_Pin;
  HAL_GPIO_Init(X2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X3_Pin;
  HAL_GPIO_Init(X3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X4_Pin;
  HAL_GPIO_Init(X4_GPIO_Port, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(X1_GPIO_Port, X1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(X2_GPIO_Port, X2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(X3_GPIO_Port, X3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(X4_GPIO_Port, X4_Pin, GPIO_PIN_RESET);

  /* Y引脚初始化(上拉输入，下降沿检测中断) */
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	
  GPIO_InitStruct.Pin = Y1_Pin;
  HAL_GPIO_Init(Y1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y2_Pin;
  HAL_GPIO_Init(Y2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y3_Pin;
  HAL_GPIO_Init(Y3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y4_Pin;
  HAL_GPIO_Init(Y4_GPIO_Port, &GPIO_InitStruct);
	
	/* 中断开启 */
  HAL_NVIC_SetPriority(PortY_EXTI, 0, 0);
	HAL_NVIC_ClearPendingIRQ(PortY_EXTI);
  HAL_NVIC_EnableIRQ(PortY_EXTI);
}

void KBD_Status_2(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/* 中断关闭 */
  HAL_NVIC_DisableIRQ(PortY_EXTI);
	
	/* 引脚反初始化 */
	HAL_GPIO_DeInit(X1_GPIO_Port, X1_Pin);
	HAL_GPIO_DeInit(X2_GPIO_Port, X2_Pin);
	HAL_GPIO_DeInit(X3_GPIO_Port, X3_Pin);
	HAL_GPIO_DeInit(X4_GPIO_Port, X4_Pin);
	HAL_GPIO_DeInit(Y1_GPIO_Port, Y1_Pin);
	HAL_GPIO_DeInit(Y2_GPIO_Port, Y2_Pin);
	HAL_GPIO_DeInit(Y3_GPIO_Port, Y3_Pin);
	HAL_GPIO_DeInit(Y4_GPIO_Port, Y4_Pin);
	
	/* Y引脚初始化(高速输出低) */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
  GPIO_InitStruct.Pin = Y1_Pin;
  HAL_GPIO_Init(Y1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y2_Pin;
  HAL_GPIO_Init(Y2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y3_Pin;
  HAL_GPIO_Init(Y3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = Y4_Pin;
  HAL_GPIO_Init(Y4_GPIO_Port, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(Y1_GPIO_Port, Y1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Y3_GPIO_Port, Y3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Y4_GPIO_Port, Y4_Pin, GPIO_PIN_RESET);

  /* X引脚初始化(上拉输入) */
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	
  GPIO_InitStruct.Pin = X1_Pin;
  HAL_GPIO_Init(X1_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X2_Pin;
  HAL_GPIO_Init(X2_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X3_Pin;
  HAL_GPIO_Init(X3_GPIO_Port, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = X4_Pin;
  HAL_GPIO_Init(X4_GPIO_Port, &GPIO_InitStruct);
}

uint16_t KBD_GetPressedKey(void){
	uint16_t Key_TMP;
	
	if(PressFlag == 0){
		Key_TMP = 0x0000;
	}
	else{
		Key_TMP = 0x0001 << (PinX+PinY*4);
		PressFlag = 0;
	}
	return Key_TMP;
}
uint8_t KBD_GetFlag(void){
	return PressFlag;
}

void KBD_Delayms(uint8_t us){
	uint32_t i = 0;
	
	for(i = 0; i < SYSFreq; i++){
		for(uint8_t j = 0; j < us; j++);
	}
}
