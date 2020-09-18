#include "BeepModule.h"
#include "DisplayModule.h"

extern Displayer displayer;

void BeepModule::Setup(int toneHlz = 3000)
{
	_toneHlz = toneHlz;
	displayer.Print("beep");
	_lastTime = millis();
	displayer.Print(".");
	tone(2, _toneHlz);
	displayer.Print(".");
	delay(300);
	displayer.Print(".");
	noTone(2);
	sequenceFunc[0] = &BeepModule::Sequence0;
	sequenceFunc[1] = &BeepModule::Sequence1;
	displayer.Println("done");
}
void BeepModule::Loop()
{
	if (_beepCount > 0)
	{
		(this->*sequenceFunc[_sequenceIndex])();
	}
}
void BeepModule::Beeps(int count = 1)
{
	//Serial.println("Start beep.");
	count = min(count, 5);
	_beepCount = count;
	_sequenceIndex = 0;
	_elapsedTime = 0;
	_lastTime = millis();
	digitalWrite(5, LOW);
}
void BeepModule::Update()
{
	_elapsedTime += millis() - _lastTime;
	_lastTime = millis();
}
void BeepModule::Sequence0()
{
	if (_elapsedTime == 0)
	{
		tone(2, _toneHlz);
		//Serial.println("tone.");
		_elapsedTime++;
	}
	if (_elapsedTime < 150) Update();
	else
	{
		//Serial.println("end tone.");
		noTone(2);
		Next();
	}
}
void BeepModule::Sequence1()
{
	if (_elapsedTime < 150) Update();
	else
	{
		_beepCount--;
		Next();
	}
}
void BeepModule::Next()
{
	//Serial.println("Next tone.");
	_sequenceIndex++;
	if (_sequenceIndex >= 2) _sequenceIndex = 0;
	_elapsedTime = 0;
}
