#ifndef _AC_DHT11_MODULE_HEADER_
#define _AC_DHT11_MODULE_HEADER_

#include "Structures.h"
#include <DHT_U.h>
#include <DHT.h>

class DHT11Module
{
private:
	DHT_Unified *_dht11 = new DHT_Unified(A1, DHT11);
	uint32_t _elapsedTime = 0;
	uint32_t _lastTime = 0;
public:
	void Setup();
	void Loop();
private:
	void Update();
	void Measure();
	void MeasureTemp();
	void MeasureHumi();
};

#endif // _AC_DHT11_MODULE_HEADER_