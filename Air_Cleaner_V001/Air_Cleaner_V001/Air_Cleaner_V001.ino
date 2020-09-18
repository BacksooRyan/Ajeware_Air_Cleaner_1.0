#include "Structures.h"
#include "DisplayModule.h"
#include "BeepModule.h"
#include "ButtonModule.h"
#include "DHT11Module.h"
#include "DustSensModule.h"
#include "FanModule.h"

MachineStatus* machineStatus = new MachineStatus();

Displayer displayer = Displayer();
BeepModule beepModule = BeepModule();
ButtonModule buttonModule = ButtonModule();
DHT11Module dht11Module = DHT11Module();
DustSensModule dustSensModule = DustSensModule();
FanModule fanModule = FanModule();

void setup() 
{
	PinSetup();
	ModuleSetup();
}
void PinSetup()
{
	pinMode(2, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, INPUT);
}
void ModuleSetup()
{
	displayer.Setup();
	beepModule.Setup();
	buttonModule.Setup();
	dht11Module.Setup();
	dustSensModule.Setup();
	fanModule.Setup();
	fanModule.SetMode(PlayMode::Auto0);
	delay(1000);
	displayer.InitBG();
}
void loop() 
{
	displayer.Loop();
	beepModule.Loop();
	buttonModule.Loop();
	dht11Module.Loop();
	dustSensModule.Loop();
	fanModule.Loop();
	delayMicroseconds(10);
}
void SetMode(PlayMode playMode)
{
	machineStatus->playMode = playMode;
	fanModule.SetMode(playMode);
}