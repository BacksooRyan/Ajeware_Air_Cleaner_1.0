#ifndef _AC_BEEP_MODULE_HEADER_
#define _AC_BEEP_MODULE_HEADER_

#include "Arduino.h"

class BeepModule
{
private:
	uint32_t _elapsedTime = 0;
	uint32_t _lastTime = 0;
	uint8_t _beepCount = 0;
	uint8_t _sequenceIndex = 0;
	uint32_t _toneHlz = 0;
	void (BeepModule::*sequenceFunc[2])();
public:
	void Setup(int toneHlz = 3000);
	void Loop();
	void Beeps(int count = 1);
private:
	void Update();
	void Sequence0();
	void Sequence1();
	void Next();
};

#endif // !_AC_BEEP_MODULE_HEADER_