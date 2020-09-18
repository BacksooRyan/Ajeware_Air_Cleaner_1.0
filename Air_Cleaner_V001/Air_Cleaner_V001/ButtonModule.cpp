#include "ButtonModule.h"
#include "Structures.h"
#include "BeepModule.h"
#include "FanModule.h"

extern MachineStatus* machineStatus;
extern BeepModule beepModule;
extern FanModule fanModule;

void ButtonModule::Setup()
{

}
void ButtonModule::Loop()
{
	if (digitalRead(6) != LOW && !_isDown)
	{
		_isDown = true;
		beepModule.Beeps(1);
		_modeIndex++;
		if (_modeIndex >= 7)
		{
			_modeIndex = 0;
		}
		switch (_modeIndex)
		{
		case 0:
			fanModule.SetMode(PlayMode::Auto0);
			break;
		case 1:
			fanModule.SetMode(PlayMode::Auto1);
			break;
		case 2:
			fanModule.SetMode(PlayMode::Auto2);
			break;
		case 3:
			fanModule.SetMode(PlayMode::Auto3);
			break;
		case 4:
			fanModule.SetMode(PlayMode::Manual1);
			break;
		case 5:
			fanModule.SetMode(PlayMode::Manual2);
			break;
		case 6:
			fanModule.SetMode(PlayMode::Manual3);
			break;
		}
	}
	if(digitalRead(6) != HIGH && _isDown)
	{
		_isDown = false;
	}
}