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
	if (_softwareSerial->available() >= 32) // ������ ���� �ø����� 32�̻� �������� ���
	{
		_datas[0] = _softwareSerial->read(); // �ø��� ���� ù �����Ͱ� 0x42���� Ȯ���Ѵ�.
		if (_datas[0] != 0x42) // ���r �׷�ġ �ƴ���
		{
			while (_softwareSerial->peek() != 0x42) // 0x42�� �� ������ ���� �� ������.
			{
				_softwareSerial->read();
			}
			return; // �ϴ� �ٽ� ������ ���� ���۰� �ٽ� 32�̻� ���⸦ ��ٸ���.
		}
		// ���r 0x42�� ���� 0x4d���� Ȯ���Ѵ�.
		_datas[1] = _softwareSerial->peek();

		if (_datas[1] != 0x4d) return;
		else _softwareSerial->read();

		for (int i = 2; i < 32; i++)
		{
			_datas[i] = _softwareSerial->read(); //�о� ���δ�.
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
