#ifndef _AC_FANMODULE_HEADER_
#define _AC_FANMODULE_HEADER_

#include "arduino.h"
#include "Structures.h"

class FanModule
{
private:
	uint32_t _elapsedTime = 0;
	uint32_t _lastTime = 0;
	bool _restTime = 0;
public:
	void Setup();
	void Loop();
	void SetMode(PlayMode playMode);
private:
	void FanLoop();
	void Update();
};

#endif // !_AC_FANMODULE_HEADER_