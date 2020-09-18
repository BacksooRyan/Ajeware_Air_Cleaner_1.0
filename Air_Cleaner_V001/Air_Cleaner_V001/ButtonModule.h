#ifndef _AC_BUTTON_MODULE_HEADER_
#define _AC_BUTTON_MODULE_HEADER_

#include "Arduino.h"

class ButtonModule
{
private:
	uint8_t _modeIndex = 0;
	bool _isDown = false;
public:
	void Setup();
	void Loop();
};

#endif // !_AC_BUTTON_MODULE_HEADER_

