#include "DisplayModule.h"
#include "FanModule.h"

extern MachineStatus* machineStatus;
extern Displayer displayer;

void FanModule::Setup()
{
	displayer.Print("fan");
	analogWrite(5, 255);
	for (int i = 0; i < 3; i++)
	{
		delay(1000);
		displayer.Print(".");
	}
	analogWrite(5, 0);
	displayer.Print("done");
	delay(1000);
	_lastTime = millis();
}
void FanModule::Loop()
{
	if (_restTime < 0)
	{
		_restTime += millis() - _lastTime;
		_lastTime = millis();
		if (_restTime >= 0)
		{
			_restTime = 0;
			_elapsedTime = 0;
		}
		return;
	}
	FanLoop();
}
void FanModule::FanLoop()
{
	switch (machineStatus->playMode)
	{
	case PlayMode::Manual1:
		if (_elapsedTime == 0) analogWrite(5, 255 * 0.4f);
		if (_elapsedTime >= 1800000)
		{
			if (_restTime >= 0)
			{
				_restTime = -300000;
				analogWrite(5, 0);
			}
		}
		else Update();
		break;
	case PlayMode::Manual2:
		if (_elapsedTime == 0) analogWrite(5, 255 * 0.7f);
		if (_elapsedTime >= 1800000)
		{
			if (_restTime >= 0)
			{
				_restTime = -300000;
				analogWrite(5, 0);
			}
		}
		else Update();
		break;
	case PlayMode::Manual3:
		if (_elapsedTime == 0) analogWrite(5, 255);
		if (_elapsedTime >= 1800000)
		{
			if (_restTime >= 0)
			{
				_restTime = -300000;
				analogWrite(5, 0);
			}
		}
		else Update();
		break;
	default:
		float __ratio = round(machineStatus->averRatio * 0.1) * 0.1;
		__ratio = __ratio * 255;
		__ratio = max(__ratio, 50);
		analogWrite(5, __ratio);
		break;
	}
}
void FanModule::Update()
{
	_elapsedTime = millis() - _lastTime;
	_lastTime = millis();
}
void FanModule::SetMode(PlayMode playMode)
{
	_elapsedTime = 0; // 초기화
	_restTime = 0; // 초기화
	machineStatus->playMode = playMode; // 값을 저장
}

/*
void FanModule::SetMode(PlayMode playMode)
{
	_elapsedTime = 0; // 초기화
	_restTime = 0; // 초기화
	machineStatus->playMode = playMode; // 값을 저장

	// 입력 받은 값에 따라 처리.
	switch (playMode)
	{
	case PlayMode::None:

		break;
	case PlayMode::Auto0:

		break;
	case PlayMode::Auto1:

		break;
	case PlayMode::Auto2:

		break;
	case PlayMode::Manual1:

		break;
	case PlayMode::Manual2:

		break;
	case PlayMode::Manual3:

		break;
	default:

		break;
	}
}
*/