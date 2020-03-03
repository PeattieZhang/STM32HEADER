#include "lcd12864.h"
//#include "delay.h"

#define clk_per_us 8

void MY_Delay_us(uint8_t us);
void LcdOutputMode(void);
void LcdInputMode(void);
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdWrite(uint8_t data);
uint8_t LcdRead(void);
void LcdSetCursor(unsigned char x, unsigned char y);

/******************************************/
/*								外部函数								*/
/******************************************/

/*初始化LCD12864*/
void LcdInit(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 开启时钟，需要手动更改 */
  __HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 						//推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;		 					//IO口速度为50MHz
	
	HAL_GPIO_WritePin(GPIO_LCD_D_PORT, LCD_D_7_0, GPIO_PIN_SET);	//LCD_D_PORT 输出高
	GPIO_InitStructure.Pin = LCD_D_7_0;														//GPIO_LCD_D_PORT端口配置
	HAL_GPIO_Init(GPIO_LCD_D_PORT, &GPIO_InitStructure);					//根据设定参数初始化GPIO_D_PIN
	
	HAL_GPIO_WritePin(GPIO_LCD_RS_PORT, LCD_RS, GPIO_PIN_SET); 		//LCD_RS 输出高 
	GPIO_InitStructure.Pin = LCD_RS;															//LCD_RS,端口配置
	HAL_GPIO_Init(GPIO_LCD_RS_PORT, &GPIO_InitStructure);		 			//根据设定参数初始化LCD_RS
	
	HAL_GPIO_WritePin(GPIO_LCD_RW_PORT, LCD_RW, GPIO_PIN_SET); 		//LCD_RW 输出高 
	GPIO_InitStructure.Pin = LCD_RW;															//LCD_RW,端口配置
	HAL_GPIO_Init(GPIO_LCD_RW_PORT, &GPIO_InitStructure);					//根据设定参数初始化LCD_RW
	
	HAL_GPIO_WritePin(GPIO_LCD_E_PORT, LCD_E, GPIO_PIN_SET); 			//LCD_E 输出高 
	GPIO_InitStructure.Pin = LCD_E;				 												//LCD_E端口配置
	HAL_GPIO_Init(GPIO_LCD_E_PORT, &GPIO_InitStructure);					//根据设定参数初始化LCD_E
	
	LcdWriteCmd(0x30);  																					//基本指令集
	LcdWriteCmd(0x0C);  																					//显示器开，光标关闭
	LcdWriteCmd(0x06);  																					//文字不动，地址自动+1
	LcdWriteCmd(0x01);  																					//清屏
}

/* 在液晶上显示字符串，(x,y)-对应屏幕上的起始坐标，str-字符串指针 */
void LcdShowStr(unsigned char column, unsigned char row, unsigned char str[]){
	unsigned char n = 0, a;
	unsigned char *fore_str;
	LcdSetCursor(column, row);   																	//设置起始地址
	while(*str != '\0')  																					//连续写入字符串数据，直到检测到结束符
	{

		if((n + 1) % 2 == 0){																				//奇数地址
			fore_str = str - 1;
			if(*fore_str>0x80){
				LcdWriteDat(*str++);
			}
			else if(*str>0x80)			LcdWriteDat(' ');
			else if(*str <= 0x80)	LcdWriteDat(*str++);
		}
		else	LcdWriteDat(*str++); 																	//先取str指向的数据，然后str自加1
		n++;

		if((n + 2 * column) % 16 == 0){
			a = (n + 2 * column) / 16;
			if(row == 0){
				if(a == 1)	LcdWriteCmd(0x90);
				if(a == 2)	LcdWriteCmd(0x88);
				if(a == 3)	LcdWriteCmd(0x98);
				if(a == 4)	LcdWriteCmd(0x80);
			}
			if(row == 1){
				if (a == 1)	LcdWriteCmd(0x88);
				if (a == 2)	LcdWriteCmd(0x98);
				if (a == 3)	LcdWriteCmd(0x80);
				if (a == 4)	LcdWriteCmd(0x90);
			}
			if(row == 2){
				if (a == 1)	LcdWriteCmd(0x98);
				if (a == 2)	LcdWriteCmd(0x80);
				if (a == 3)	LcdWriteCmd(0x90);
				if (a == 4)	LcdWriteCmd(0x88);
			}
			if(row == 3){
				if (a == 1)	LcdWriteCmd(0x80);
				if (a == 2)	LcdWriteCmd(0x90);
				if (a == 3)	LcdWriteCmd(0x88);
				if (a == 4)	LcdWriteCmd(0x98);
			}
		}
	}
}

/*将数字和字母转化为GBK编码，仅GBK编码可用LcdShowStr()输出*/
uint8_t* LcdGBK(uint8_t* data, uint8_t length){
	static uint8_t GBK[64];
	uint8_t i=0;
	
	for(i=0; i<length;i++){
			GBK[2*i] 		= G_15_8;
		switch(data[i]){
			case '0':	GBK[2*i+1] = G0;	break;
			case '1':	GBK[2*i+1] = G1;	break;
			case '2':	GBK[2*i+1] = G2;	break;
			case '3':	GBK[2*i+1] = G3;	break;
			case '4':	GBK[2*i+1] = G4;	break;
			case '5':	GBK[2*i+1] = G5;	break;
			case '6':	GBK[2*i+1] = G6;	break;
			case '7':	GBK[2*i+1] = G7;	break;
			case '8':	GBK[2*i+1] = G8;	break;
			case '9':	GBK[2*i+1] = G9;	break;
			case 'A':	GBK[2*i+1] = GA;	break;
			case 'B':	GBK[2*i+1] = GB;	break;
			case 'C':	GBK[2*i+1] = GC;	break;
			case 'D':	GBK[2*i+1] = GD;	break;
			case 'E':	GBK[2*i+1] = GE;	break;
			case 'F':	GBK[2*i+1] = GF;	break;
			case 'G':	GBK[2*i+1] = GG;	break;
			case 'H':	GBK[2*i+1] = GH;	break;
			case 'I':	GBK[2*i+1] = GI;	break;
			case 'J':	GBK[2*i+1] = GJ;	break;
			case 'K':	GBK[2*i+1] = GK;	break;
			case 'L':	GBK[2*i+1] = GL;	break;
			case 'M':	GBK[2*i+1] = GM;	break;
			case 'N':	GBK[2*i+1] = GN;	break;
			case 'O':	GBK[2*i+1] = GO;	break;
			case 'P':	GBK[2*i+1] = GP;	break;
			case 'Q':	GBK[2*i+1] = GQ;	break;
			case 'R':	GBK[2*i+1] = GR;	break;
			case 'S':	GBK[2*i+1] = GS;	break;
			case 'T':	GBK[2*i+1] = GT;	break;
			case 'U':	GBK[2*i+1] = GU;	break;
			case 'V':	GBK[2*i+1] = GV;	break;
			case 'W':	GBK[2*i+1] = GW;	break;
			case 'X':	GBK[2*i+1] = GX;	break;
			case 'Y':	GBK[2*i+1] = GY;	break;
			case 'Z':	GBK[2*i+1] = GZ;	break;
			case 'a':	GBK[2*i+1] = Ga;	break;
			case 'b':	GBK[2*i+1] = Gb;	break;
			case 'c':	GBK[2*i+1] = Gc;	break;
			case 'd':	GBK[2*i+1] = Gd;	break;
			case 'e':	GBK[2*i+1] = Ge;	break;
			case 'f':	GBK[2*i+1] = Gf;	break;
			case 'g':	GBK[2*i+1] = Gg;	break;
			case 'h':	GBK[2*i+1] = Gh;	break;
			case 'i':	GBK[2*i+1] = Gi;	break;
			case 'j':	GBK[2*i+1] = Gj;	break;
			case 'k':	GBK[2*i+1] = Gk;	break;
			case 'l':	GBK[2*i+1] = Gl;	break;
			case 'm':	GBK[2*i+1] = Gm;	break;
			case 'n':	GBK[2*i+1] = Gn;	break;
			case 'o':	GBK[2*i+1] = Go;	break;
			case 'p':	GBK[2*i+1] = Gp;	break;
			case 'q':	GBK[2*i+1] = Gq;	break;
			case 'r':	GBK[2*i+1] = Gr;	break;
			case 's':	GBK[2*i+1] = Gs;	break;
			case 't':	GBK[2*i+1] = Gt;	break;
			case 'u':	GBK[2*i+1] = Gu;	break;
			case 'v':	GBK[2*i+1] = Gv;	break;
			case 'w':	GBK[2*i+1] = Gw;	break;
			case 'x':	GBK[2*i+1] = Gx;	break;
			case 'y':	GBK[2*i+1] = Gy;	break;
			case 'z':	GBK[2*i+1] = Gz;	break;
		}
	}
	GBK[2*i] = '\0';
	
	return GBK;
}

/*显示图像，xy为横纵坐标，wh为宽高(都以像素为单位)，xw必须为16的整数倍，y与h可以为0-63的任意值*/
void LcdShowImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *img){
	uint16_t i;
	uint8_t xi, yi;
	uint8_t xt, yt;
	
	x >>= 4;
	w >>= 4;
	i = 0;
	LcdWriteCmd(0x36); 																						//启动CGRAM操作

	for(yi = 0; yi<h; yi++){
		yt = y + yi;
		xt = x;
		if(yt >= 32){
			yt -= 32;
			xt += 8;
		}
		for(xi = 0; xi<w; xi++){
			LcdWriteCmd(0x80 | yt);
			LcdWriteCmd(0x80 | xt+xi);
			LcdWriteDat(img[i++]);
			LcdWriteDat(img[i++]);
		}
	}
}

/*清除屏幕上一个区块的区域，xywh同LcdShowImage()*/
void LcdClearArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h){
	uint8_t xi, yi;
	uint8_t xt, yt;

	x >>= 4;
	w >>= 4;
	LcdWriteCmd(0x36); 																						//启动CGRAM操作

	for(yi = 0; yi<h; yi++){
		yt = y + yi;
		xt = x;
		if(yt >= 32){
			yt -= 32;
			xt += 8;
		}
		for(xi = 0; xi<w; xi++){
			LcdWriteCmd(0x80 | yt);
			LcdWriteCmd(0x80 | xt+xi);
			LcdWriteDat(0x00);
			LcdWriteDat(0x00);
		}
	}
}
void LcdClearAll(void){
	LcdWriteCmd(0x30);
	LcdWriteCmd(0x01);  																					//清屏
}

/******************************************/
/*								内部函数								*/
/******************************************/

/*延时*/
void MY_Delay_us(uint8_t us){
	for(int i = 0; i <8*us; i++);
}

/*输出模式*/
void LcdOutputMode(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	HAL_GPIO_WritePin(GPIO_LCD_D_PORT, LCD_D_7_0, GPIO_PIN_SET);	//GPIO_LCD_D_PORT输出高
	GPIO_InitStructure.Pin = LCD_D_7_0;				 										//GPIO_LCD_D_PORT端口配置
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 						//推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;		 					//IO口速度为50MHz
	HAL_GPIO_Init(GPIO_LCD_D_PORT, &GPIO_InitStructure);					//根据设定参数初始化GPIO_LCD_D_PORT
}

/*输入模式*/
void LcdInputMode(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	HAL_GPIO_WritePin(GPIO_LCD_D_PORT, LCD_D_7_0, GPIO_PIN_SET);	//PG.0 输出高
	GPIO_InitStructure.Pin = LCD_D_7_0;				 										//GPIO_LCD_D_PORT端口配置
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 		 								//上拉输入
	GPIO_InitStructure.Pull = GPIO_PULLUP;												//上拉输入
	HAL_GPIO_Init(GPIO_LCD_D_PORT, &GPIO_InitStructure);					//根据设定参数初始化GPIO_LCD_D_PORT
}

/* 向LCD1602液晶写入一字节命令，cmd-待写入命令值 */
void LcdWriteCmd(unsigned char cmd){
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_RS_PORT, LCD_RS, GPIO_PIN_RESET);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_RW_PORT, LCD_RW, GPIO_PIN_RESET);
	MY_Delay_us(1);
	LcdWrite(cmd);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_E_PORT, LCD_E, GPIO_PIN_SET);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_E_PORT, LCD_E, GPIO_PIN_RESET);
	MY_Delay_us(1);
}

/* 向LCD1602液晶写入一字节数据，dat-待写入数据值 */
void LcdWriteDat(unsigned char dat){
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_RS_PORT, LCD_RS, GPIO_PIN_SET);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_RW_PORT, LCD_RW, GPIO_PIN_RESET);
	MY_Delay_us(1);
	LcdWrite(dat);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_E_PORT, LCD_E, GPIO_PIN_SET);
	MY_Delay_us(1);
	HAL_GPIO_WritePin(GPIO_LCD_E_PORT, LCD_E, GPIO_PIN_RESET);
	MY_Delay_us(1);
}

/*将data输出到D0~D7口*/
void LcdWrite(uint8_t data){
	uint32_t tmp = 0;
	
	if(data&0x01)tmp += LCD_D0; else tmp += LCD_D0<<16u;
	if(data&0x02)tmp += LCD_D1; else tmp += LCD_D1<<16u;
	if(data&0x04)tmp += LCD_D2; else tmp += LCD_D2<<16u;
	if(data&0x08)tmp += LCD_D3; else tmp += LCD_D3<<16u;
	if(data&0x10)tmp += LCD_D4; else tmp += LCD_D4<<16u;
	if(data&0x20)tmp += LCD_D5; else tmp += LCD_D5<<16u;
	if(data&0x40)tmp += LCD_D6; else tmp += LCD_D6<<16u;
	if(data&0x80)tmp += LCD_D7; else tmp += LCD_D7<<16u;
	
	GPIO_LCD_D_PORT->BSRR = tmp;
}

/*从D0~D7读取数值*/
uint8_t LcdRead(void){
	uint16_t tmp = (uint16_t)GPIO_LCD_D_PORT->IDR;
	uint8_t value = 0;
	
	if(tmp&LCD_D0) value += 0x01;
	if(tmp&LCD_D1) value += 0x02;
	if(tmp&LCD_D2) value += 0x04;
	if(tmp&LCD_D3) value += 0x08;
	if(tmp&LCD_D4) value += 0x10;
	if(tmp&LCD_D5) value += 0x20;
	if(tmp&LCD_D6) value += 0x40;
	if(tmp&LCD_D7) value += 0x80;
	
	return value;
}

/* 设置显示RAM起始地址，亦即光标位置，(x,y)-对应屏幕上的字符坐标 */
void LcdSetCursor(unsigned char x, unsigned char y){
	unsigned char addr;

	if(y >= 2){	   																								//显示在右半屏
		y -= 2;
		x += 8;																											//x右挪8个汉字
	}
	addr = y * 16 + x;																						
	LcdWriteCmd(0x30); 																						//启动DDRAM操作
	LcdWriteCmd(0x80 | addr);																			//设置ram地址
}

/* "和" 16 X 16 */
uint8_t HE[] = {
	0x20,0x00,0x70,0x00,0x1E,0x00,0x10,0x3E,0x10,0x22,0xFF,0x22,0x10,0x22,0x18,0x22,0x38,0x22,0x54,0x22,0x54,0x22,0x12,0x22,0x11,0x3E,0x10,0x22,0x10,0x00,0x10,0x00
};
/* LOGO 16 X 16 */
uint8_t LOGO[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x0F,0xE0,0x3F,0xE0,0x7F,0xF0,0x7F,0xF8,0x7D,0xF0,0x3C,0xD0,0x2C,0x30,0x30,0x70,0x38,0xE0,0x1F,0x00,0x00,0x00,0x00
};

/* 二维码，64 X 64 */
uint8_t QRCODE[] = {
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X01,0XD9,0X98,0XC0,0X00,0X00,0X00,0X00,0X7D,0X18,0X92,0X5F,0X00,0X00,
0X00,0X00,0X45,0X7D,0X2E,0X51,0X00,0X00,0X00,0X00,0X45,0XB6,0XDE,0X51,0X00,0X00,
0X00,0X00,0X45,0X17,0X6A,0XD1,0X00,0X00,0X00,0X00,0X7D,0X50,0X2D,0X5F,0X00,0X00,
0X00,0X00,0X01,0X55,0X55,0X40,0X00,0X00,0X00,0X00,0XFF,0X4C,0X23,0X7F,0X80,0X00,
0X00,0X00,0X2C,0XE1,0XF3,0X44,0X80,0X00,0X00,0X00,0X2B,0XA5,0XE1,0X9B,0X00,0X00,
0X00,0X00,0X9C,0XE1,0XCF,0X63,0X00,0X00,0X00,0X00,0X2E,0X01,0XE0,0X6E,0X00,0X00,
0X00,0X00,0XC9,0XCE,0X6A,0X1B,0X00,0X00,0X00,0X00,0XC3,0XAC,0XD3,0X50,0X00,0X00,
0X00,0X00,0X51,0X4D,0X90,0X9A,0X80,0X00,0X00,0X00,0X8A,0XC8,0X1A,0XF2,0X80,0X00,
0X00,0X00,0XC1,0X76,0XAA,0X17,0X00,0X00,0X00,0X00,0X32,0X53,0X7C,0X29,0X80,0X00,
0X00,0X00,0X94,0X63,0X73,0X22,0X00,0X00,0X00,0X00,0X5B,0X76,0X9B,0X83,0X80,0X00,
0X00,0X00,0X79,0X7B,0XB2,0X2A,0X80,0X00,0X00,0X00,0XFA,0X89,0XB7,0X1D,0X00,0X00,
0X00,0X00,0X09,0XB9,0X63,0X8B,0X00,0X00,0X00,0X00,0XA7,0XB8,0X59,0X6A,0X00,0X00,
0X00,0X00,0X41,0X11,0X20,0X03,0X80,0X00,0X00,0X00,0XFF,0X41,0X86,0X73,0X80,0X00,
0X00,0X00,0X01,0X77,0XF7,0X54,0X80,0X00,0X00,0X00,0X7D,0XF1,0X88,0X76,0X00,0X00,
0X00,0X00,0X45,0XC9,0X15,0X06,0X00,0X00,0X00,0X00,0X45,0X5D,0XCA,0XD0,0X00,0X00,
0X00,0X00,0X45,0XDB,0XDB,0XE0,0X00,0X00,0X00,0X00,0X7D,0X0B,0X00,0X2B,0X80,0X00,
0X00,0X00,0X01,0X25,0X7B,0X8A,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};
