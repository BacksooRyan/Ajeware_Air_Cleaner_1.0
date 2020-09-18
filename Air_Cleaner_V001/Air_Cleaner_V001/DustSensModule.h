#ifndef _AC_DUSTSENS_HEADER_
#define _AC_DUSTSENS_HEADER_

#include "SoftwareSerial.h"
class DustSensModule
{
private:
	SoftwareSerial* _softwareSerial = new SoftwareSerial(4, 3);
	uint8_t _datas[32];
public:
	void Setup();
	void Loop();
private :
	void SaveData();
};

#endif // !_AC_DUSTSENS_HEADER_