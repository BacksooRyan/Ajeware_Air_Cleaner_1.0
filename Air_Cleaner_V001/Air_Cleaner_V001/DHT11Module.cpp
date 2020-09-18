#include "Structures.h"
#include "DisplayModule.h"
#include "DHT11Module.h"

extern MachineStatus* machineStatus;
extern Displayer displayer;

void DHT11Module::Setup()
{
	displayer.Print("DHT11");
	_lastTime = millis();
	displayer.Println("...done");
}
void DHT11Module::Loop()
{
	if (_elapsedTime >= 250)
	{
		Measure();
		_elapsedTime = 0;
	}
	else Update();
}
void DHT11Module::Update()
{
	_elapsedTime += millis() - _lastTime;
	_lastTime = millis();
}
void DHT11Module::Measure()
{
	MeasureTemp();
	MeasureHumi();
}
void DHT11Module::MeasureTemp()
{
	sensors_event_t __dht11Event;
	_dht11->temperature().getEvent(&__dht11Event);
	machineStatus->temporature = __dht11Event.temperature;
}
void DHT11Module::MeasureHumi()
{
	sensors_event_t __dht11Event;
	_dht11->humidity().getEvent(&__dht11Event);
	machineStatus->humidity = __dht11Event.relative_humidity;
}