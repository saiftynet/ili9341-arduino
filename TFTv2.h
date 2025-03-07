/*
 Adapted from gmtii/ili9341-arduino to be specific to NanoBench
*/
#ifndef TFTv2_h
#define TFTv2_h

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SPI.h>

//Basic Colors
#define RED		0xf800
#define GREEN	0x07e0
#define BLUE	0x001f
#define BLACK	0x0000
#define YELLOW	0xffe0
#define WHITE	0xffff

//Other Colors
#define CYAN		0x07ff	
#define BRIGHT_RED	0xf810	
#define GRAY1		0x8410  
#define GRAY2		0x4208  

//TFT resolution 240*320
#define MIN_X	0
#define MIN_Y	0
#define MAX_X	239
#define MAX_Y	319

/* for my system the nano with pins mapped as below 
D8  (pb0)  B0000001 = 0x01: TFT_DC   was d6 (pd6) B01000000 = 0x40
D10 (pb2)  B0000100 = 0x04: TFT_CS   was d5 (pd5) B00100000 = 0x20
D9  (pb1)  B0000010 = 0x02: TFT_RST  was d4 (pd4) B00010000 = 0x10

--                        : LED      was d7 (pd7) B01000000 = 0x80
D11 : MOSI
D12 : MISO
D13 : SCK
*/

#define TFT_CS_LOW  {DDRB |= 0x04;PORTB &=~ 0x04;}
#define TFT_CS_HIGH {DDRB |= 0x04;PORTB |=  0x04;}
#define TFT_DC_LOW  {DDRB |= 0x01;PORTB &=~ 0x01;}
#define TFT_DC_HIGH {DDRB |= 0x01;PORTB |=  0x01;}
#define TFT_BL_OFF  {}
#define TFT_BL_ON   {}
#define TFT_RST_OFF {DDRB |= 0x02;PORTB |=  0x02;}
#define TFT_RST_ON  {DDRB |= 0x02;PORTB &=~ 0x02;}


#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3


#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2

#ifndef INT8U
#define INT8U unsigned char
#endif
#ifndef INT16U
#define INT16U unsigned int
#endif

extern INT8U simpleFont[][8];

class TFT
{
public:
	void TFTinit (void);
	void setCol(INT16U StartCol,INT16U EndCol);
	void setPage(INT16U StartPage,INT16U EndPage);
	void setXY(INT16U poX, INT16U poY);
	void setPixel(INT16U poX, INT16U poY,INT16U color);
	void sendCMD(INT8U index);
	void WRITE_Package(INT16U *data,INT8U howmany);
	void WRITE_DATA(INT8U data);
	void sendData(INT16U data);
	INT8U Read_Register(INT8U Addr,INT8U xParameter);
	void fillScreen(INT16U XL,INT16U XR,INT16U YU,INT16U YD,INT16U color);
	void fillScreen(void);
	INT8U readID(void);

	void drawChar(INT8U ascii,INT16U poX, INT16U poY,INT16U size, INT16U fgcolor);
	void drawString(char *string,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	void fillRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);

	void drawLine(INT16U x0,INT16U y0,INT16U x1,INT16U y1,INT16U color);
	void drawVerticalLine(INT16U poX, INT16U poY,INT16U length,INT16U color);
	void drawHorizontalLine(INT16U poX, INT16U poY,INT16U length,INT16U color);
	void drawRectangle(INT16U poX, INT16U poY, INT16U length,INT16U width,INT16U color);

	void drawCircle(int poX, int poY, int r,INT16U color);
	void fillCircle(int poX, int poY, int r,INT16U color);

	void drawTriangle(int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color);
	INT8U drawNumber(long long_num,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	INT8U drawFloat(float floatNumber,INT8U decimal,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);
	INT8U drawFloat(float floatNumber,INT16U poX, INT16U poY,INT16U size,INT16U fgcolor);

};

extern TFT Tft;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
