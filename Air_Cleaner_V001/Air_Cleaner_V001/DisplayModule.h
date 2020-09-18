#ifndef _AC_DISPLAY_MODULE_HEADER_
#define _AC_DISPLAY_MODULE_HEADER_

//#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class Displayer
{
private:
	uint16_t _dispColor[5] = { ST7735_GREEN,
		ST7735_YELLOW * 0.75 + ST7735_RED * 0.25f,
		ST7735_YELLOW * 0.50 + ST7735_RED * 0.50f,
		ST7735_YELLOW * 0.25 + ST7735_RED * 0.75f,
		ST7735_RED
	};
	Adafruit_ST7735* _displayer = new Adafruit_ST7735(10, 8, 9);
	uint32_t _elapsedTime = 0;
	uint32_t _lastTime = 0;
public:
	void Setup();
	void Loop();
	void Clear()
	{
		_displayer->fillScreen(ST7735_BLACK);
	}
	void Print(char* msg);
	void Println(char* msg);
	void InitBG();
private:
	void DisplayInfo();
	void DisplayDust();
};

#endif // !_AC_DISPLAY_MODULE_HEADER_