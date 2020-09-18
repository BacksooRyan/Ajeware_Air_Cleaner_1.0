#ifndef _AC_STRUCTURE_HEADER_
#define _AC_STRUCTURE_HEADER_

enum class PlayMode
{
	Auto0 = 0, // 가장 많은 먼지량에 따라 자동으로 팬 속도를 조절한다.
	Auto1, // 01 먼지량 비중이 50%
	Auto2, // 03 먼지량 비중이 50%
	Auto3, // 10 먼지량 비중이 50%
	Manual1, // 40%
	Manual2, // 70%
	Manual3, // 100%
};
typedef struct MachineStatus
{
	float temporature; // 온도 저장
	float humidity; // 습도 저장
	float dust01Ratio; // PM 0.1이하 먼지 농도. 다소 부정확
	float dust03Ratio; // PM 2.5이하 먼지 농도.
	float dust10Ratio; // PM 10 이하 먼지 농도
	float averRatio; // 평균 값.
	int prorityIndex; // 최우선으로 쓸 먼지 농도
	PlayMode playMode; // 동작 모드
	//
	char* GetMode()
	{
		switch (playMode)
		{
		case PlayMode::Auto0:
			return "Auto 0";
			break;
		case PlayMode::Auto1:
			return "Auto 1";
			break;
		case PlayMode::Auto2:
			return "Auto 2";
			break;
		case PlayMode::Auto3:
			return "Auto 3";
			break;
		case PlayMode::Manual1:
			return "Manual 40%";
			break;
		case PlayMode::Manual2:
			return "Manual 70%";
			break;
		case PlayMode::Manual3:
			return "Manual 100%";
			break;
		default:
			break;
		}
	}
};

#endif // !_AC_STRUCTURE_HEADER_
