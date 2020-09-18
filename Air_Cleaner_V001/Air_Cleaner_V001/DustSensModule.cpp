#include "DisplayModule.h"
#include "DustSensModule.h"
#include "Structures.h"

extern MachineStatus* machineStatus;
extern Displayer displayer;

void DustSensModule::Setup()
{
	_softwareSerial->begin(9600);
	displayer.Print("dusts");
	for (int i = 0; i < 10; i++)
	{
		delay(1000);
		displayer.Print(".");
	}
	bool isAvailable = _softwareSerial->available() >= 32 ? true : false;
	delay(1000);
	if(isAvailable) displayer.Println("done");
	else displayer.Println("error");
}
void DustSensModule::Loop()
{
	if (_softwareSerial->available() >= 32) // 루프를 돌며 시리얼이 32이상 찰때까지 대기
	{
		_datas[0] = _softwareSerial->read(); // 시리얼 버퍼 첫 데이터가 0x42인지 확인한다.
		if (_datas[0] != 0x42) // 마냨 그러치 아느묜
		{
			while (_softwareSerial->peek() != 0x42) // 0x42가 될 때까지 값을 다 버린다.
			{
				_softwareSerial->read();
			}
			return; // 일단 다시 루프를 돌려 버퍼가 다시 32이상 차기를 기다린다.
		}
		// 마냨 0x42라묜 이제 0x4d인지 확인한다.
		_datas[1] = _softwareSerial->peek();

		if (_datas[1] != 0x4d) return;
		else _softwareSerial->read();

		for (int i = 2; i < 32; i++)
		{
			_datas[i] = _softwareSerial->read(); //읽어 들인다.
		}
		SaveData();
	}
}

void DustSensModule::SaveData()
{
	machineStatus->dust01Ratio = _datas[9];
	machineStatus->dust03Ratio = _datas[11];
	machineStatus->dust10Ratio = _datas[13];

	float __average = 0;
	switch (machineStatus->playMode)
	{
	case PlayMode::Auto0:
		if (machineStatus->dust01Ratio > __average)
		{
			machineStatus->prorityIndex = 0;
			__average = machineStatus->dust01Ratio;
		}
		if (machineStatus->dust03Ratio > __average)
		{
			machineStatus->prorityIndex = 1;
			__average = machineStatus->dust03Ratio;
		}
		if (machineStatus->dust10Ratio > __average)
		{
			machineStatus->prorityIndex = 2;
			__average = machineStatus->dust10Ratio;
		}
		machineStatus->averRatio = __average / 400.0f * 100;
		break;
	case PlayMode::Auto1:
		__average = machineStatus->dust01Ratio;
		__average += machineStatus->dust01Ratio;
		__average += machineStatus->dust03Ratio;
		__average += machineStatus->dust10Ratio;
		__average /= 4;

		machineStatus->prorityIndex = 0;
		machineStatus->averRatio = __average / 400.0f * 100;
		break;
	case PlayMode::Auto2:
		__average = machineStatus->dust01Ratio;
		__average += machineStatus->dust03Ratio;
		__average += machineStatus->dust03Ratio;
		__average += machineStatus->dust10Ratio;
		__average /= 4;

		machineStatus->prorityIndex = 1;
		machineStatus->averRatio = __average / 400.0f * 100;

		break;
	case PlayMode::Auto3:
		__average = machineStatus->dust01Ratio;
		__average += machineStatus->dust03Ratio;
		__average += machineStatus->dust10Ratio;
		__average += machineStatus->dust10Ratio;
		__average /= 4;

		machineStatus->prorityIndex = 2;
		machineStatus->averRatio = __average / 400.0f * 100;
		break;
	default:
		__average = machineStatus->dust01Ratio;
		__average += machineStatus->dust03Ratio;
		__average += machineStatus->dust10Ratio;
		__average /= 3;

		machineStatus->prorityIndex = 3;
		machineStatus->averRatio = __average / 400.0f * 100;
		break;
	}
}
