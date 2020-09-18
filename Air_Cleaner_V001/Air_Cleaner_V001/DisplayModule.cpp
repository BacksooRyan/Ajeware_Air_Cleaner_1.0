#include "Structures.h"
#include "DisplayModule.h"

extern MachineStatus* machineStatus;

void Displayer::Setup()
{
	_displayer->initR();
	_displayer->fillScreen(ST7735_BLACK);
	_lastTime = millis();
	_displayer->println("displayer...done");
}
void Displayer::Print(char* msg)
{
	_displayer->print(msg);
}
void Displayer::Println(char* msg)
{
	_displayer->println(msg);
}
void Displayer::InitBG()
{
	_displayer->fillScreen(0x0000);
	_displayer->drawRect(3, 6, 121, 18, 0xffff);
	_displayer->drawRect(44, 6, 40, 18, 0xffff);
	_displayer->drawRect(3, 24, 121, 18, 0xffff);
	_displayer->drawRect(44, 24, 40, 18, 0xffff);

	_displayer->setCursor(13, 11);
	_displayer->print("PM01");

	_displayer->setCursor(54, 11);
	_displayer->print("PM03");

	_displayer->setCursor(93, 11);
	_displayer->print("PM10");

	_displayer->drawRect(3, 45, 122, 24, 0xffff);
	_displayer->setCursor(0, 80);
	_displayer->println(" Temp:      `C");
	_displayer->println(" Humi:      %");
	//
	_displayer->setCursor(3, 105);
	_displayer->print("Program");
	_displayer->drawLine(3, 120, 122, 120, ST7735_WHITE);
}
void Displayer::Loop()
{
	if (_elapsedTime >= 1000)
	{
		DisplayDust();
		DisplayInfo();
		_elapsedTime = 0;
	}
	//
	_elapsedTime += millis() - _lastTime;
	_lastTime = millis();
}
void Displayer::DisplayDust()
{
	// 그리려는 배경을 지웁니다.
	_displayer->fillRect(6, 26, 36, 12, 
		machineStatus->prorityIndex == 0 ? 0xff00 : 0x0000); // 우선되는 경우 빨간배경
	_displayer->setCursor(6, 29); // 커서를 이동.
	char dust01str[6]; // 버퍼
	// 실수형을 문자열로
	dtostrf(machineStatus->dust01Ratio, 5, 1, dust01str);
	_displayer->print(dust01str); // 출력

	_displayer->fillRect(47, 26, 36, 12,
		machineStatus->prorityIndex == 1 ? 0xff00 : 0x0000); // 우선되는 경우 빨간배경
	_displayer->setCursor(47, 29);
	char dust03str[6];
	dtostrf(machineStatus->dust03Ratio, 5, 1, dust03str);
	_displayer->print(dust03str);

	_displayer->fillRect(84, 26, 36, 12,
		machineStatus->prorityIndex == 2 ? 0xff00 : 0x0000); // 우선되는 경우 빨간배경
	_displayer->setCursor(87, 29);
	char dust10str[6];
	dtostrf(machineStatus->dust10Ratio, 5, 1, dust10str);
	_displayer->print(dust10str);

	int __width = machineStatus->averRatio;
	__width = constrain(__width, 0, 100);
	__width = map(__width, 0, 100, 0, 120);

	int __drawCount = floor(__width / 24);

	_displayer->fillRect(4, 46, 120, 22, 0x0000);
	for (int i = 0; i < __drawCount; i++)
	{
		_displayer->fillRect(i * 24 + 4, 46, 24, 22, _dispColor[i]);
	}
	if (__drawCount < 5)
	{
		__width = round(__width) % 24;
		_displayer->fillRect(__drawCount * 24 + 4, 46, __width, 22, _dispColor[__drawCount]);
	}
}
void Displayer::DisplayInfo()
{
	_displayer->setCursor(40, 80);
	_displayer->fillRect(40, 80, 40, 8, 0x0000);
	char tempBuffer[5];
	dtostrf(machineStatus->temporature, 4, 1, tempBuffer);
	_displayer->print(tempBuffer);

	_displayer->setCursor(40, 88);
	_displayer->fillRect(40, 88, 40, 8, 0x0000);
	char humiBuffer[5];
	dtostrf(machineStatus->humidity, 4, 1, humiBuffer);
	_displayer->print(humiBuffer);

	_displayer->setCursor(55, 105);
	_displayer->fillRect(55, 105, 65, 8, 0x0000);
	char* playMode = machineStatus->GetMode();
	_displayer->print(playMode);
}